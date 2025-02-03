#include	"DxLib.h"
#include	"gamemain.h"
#include	"data.h"
#include	"scenetalk.h"
#include	"scenegametutorial.h"
#include	"scenelook.h"
#include	"mymath.h"
#include	"SceneGameover.h"
#include	<iostream>
#include	<string>
#include	"utf8sjis.h"	// jsonの日本語文字を使うために必要

SceneGameTutorial::SceneGameTutorial()
{
	// チャプター
	gameChapter = 0;
	
	int i;
	std::string img_path;
	// 画像のロード
	_cgBgAnimcnt = 0;
	_cgBgAnimpattern = 0;

	// 議論パート
	gGameCnt = 0;

	cgCounter = LoadGraph("res/Scenegamemain/cutin_counter.png");
	cgCounter_x = LoadGraph("res/Scenegamemain/cutin_counter_X.png");

	// エフェクト
	//efectType 0:ダメージエフェクト 1:ダメージ演出 2:ガード演出


	// 反論パート
	// 取得カード画像
	// 反論カード画像
	// 正解のカード画像

	// 間違った場合の画像
	cgHanronMiss = LoadGraph("res/Scenegamemain/gisyou_miss_text.png");

	// 裏返し用画像

	// カードの設定
	myDeck.answer_card = tblAnsCard[gameChapter].answerNum;
	myDeck.flg_ans = 0;
	have_card = 0;

	// スポットライト

	//防御エフェクト
	blockse = LoadSoundMem("res/se/block_high.mp3");

	//音声のロード

	// 音量調整
	ChangeVolumeSoundMem(255 * TUTORIAL_BGM_VOLUME / 100, seBGM1);
	ChangeVolumeSoundMem(255 * TUTORIAL_BGM_VOLUME / 200, seBGM2);
	ChangeVolumeSoundMem(255 * DAMADE_SE_VOLUME / 100, seDamage);
	ChangeVolumeSoundMem(255 * TESTIMONY_SE_VOLUME / 100, seSay);
	ChangeVolumeSoundMem(255 * SHIELD_SE_VOLUME / 100, blockse);

	text_flg = 0;
	flg_gameflow = 0;
	flg_shield = 0;
	Movieflg = 0;
	scenarioTestimonyCnt = 0;
	isPause = true;

	// エフェクト情報の初期化
	gEffect.InitEffect();

	//カットイン関係の初期化
	cutInFlag = 0;
	cutInCount = 0;

	// ガード
	gardCount = 0;
	LockInterval = 0;

	// 反論パート正解時エフェクト
	endEffectCnt = 0;
	endEffectpattern = 0;

	//反論パート失敗演出のフラグカウント
	misDirectionFlagCnt = 0;

	//フラッシュ関連
	flashcnt = 0;
	flash_alpha = 0;

	//敵の位置をセット
	scenario.SetEnemyPosition(0);

	//シナリオのセット
	scenario.SetChapterScenario(0);
	//シナリオ内の証言数を取得
	GetScenarioTestimony(*scenario.GetScenario());
	counterFlag = 0;
	frame = 0;
	alpha = 0;
	counterGraph.scale = 1.0f;

	gameCnt = 0;

	std::ifstream file("res/jsonfile/tutorial.json");
	nlohmann::json json;
	file >> json;
	i = 0;
	// データを読み込む
	for (auto jsonfile : json)
	{
		jsonfile.at("message1").get_to(_jsonData[i].message1);
		jsonfile.at("message2").get_to(_jsonData[i].message2);
		jsonfile.at("chara").get_to(_jsonData[i].draw);
		jsonfile.at("charaX").get_to(_jsonData[i].drawX);
		jsonfile.at("charaY").get_to(_jsonData[i].drawY);
		jsonfile.at("command").get_to(_jsonData[i].command);
		jsonfile.at("name").get_to(_jsonData[i].name);
		//json[i].at("voice").get_to(_jsonData[i].voice);
		//json[i].at("bgY").get_to(_jsonData[i].bgY);

		// jsonの文字列を、UTF-8からShift-JISに変換
		_jsonData[i].message1 = ConvUTF8toSJIS(_jsonData[i].message1);
		_jsonData[i].message2 = ConvUTF8toSJIS(_jsonData[i].message2);
		_jsonData[i].draw = ConvUTF8toSJIS(_jsonData[i].draw);
		_jsonData[i].name = ConvUTF8toSJIS(_jsonData[i].name);
		//_jsonData[i].voice = ConvUTF8toSJIS(_jsonData[i].voice);
		i++;
	}

	//メッセージカウント読み込み
	messagecnt = 0;

	cgchara = 0;

	//動画のロード
	MovieHandle = LoadGraph("res/movie/haikei_ikou.mp4");

	ChangeMovieVolumeToGraph(0, MovieHandle);

	//動画
	PlayMovieToGraph(MovieHandle);
	PlaySoundMem(seBGM1, DX_PLAYTYPE_BACK);
}

SceneGameTutorial::~SceneGameTutorial()
{
	int i;
	// データの削除
	// 画像

	//音声
	DeleteSoundMem(MovieHandle);

	//シナリオの初期化
	for (int i = 0; i < WORD_MAX; i++) {
		words[i].use = 0;
	}
}

// 言葉追加
void SceneGameTutorial::AddWord(int wordType, int count, int cgName, int x, int y, int waitTime, int seName, int numName, int ttmCnt) {

	if (wordType == -1) { gGameCnt = 0; }

	//すでに取得している証言は出さない
	if (wordType == 2 && myDeck.CheckCard(numName, ttmCnt)) {

	}
	else {
		// 使っていない配列を探す
		for (int i = 0; i < WORD_MAX; i++)
		{
			// 使っていない。ここを使う
			if (words[i].use == 0)
			{
				words[i].use = 1;
				words[i].x = x;
				words[i].y = y;
				words[i].scale = 0.65;
				words[i].wordType = wordType;
				words[i].cgName = cgName;
				words[i].count = count;
				words[i].waitTime = waitTime;
				words[i].numName = numName;

				//SE再生
				PlaySoundMem(seName, DX_PLAYTYPE_BACK);
				break;
			}
		}
	}
}

// 言葉の出現シナリオ
void SceneGameTutorial::SetScenario(const std::vector<Scenario::SCENARIO>& scenario)
{
	int i = 0;
	while (scenario[i].gamecnt != -1) {	// データの最後までをループ
		if (scenario[i].gamecnt == gGameCnt) {
			// シナリオデータのgamecntが一致した
			AddWord(scenario[i].wordType, scenario[i].gamecnt, scenario[i].cgName, scenario[i].x, scenario[i].y, scenario[i].waitTime, scenario[i].seName, scenario[i].numName, scenario[i].testimonyCnt);
			PlaySoundMem(scenario[i].seName, DX_PLAYTYPE_BACK);
		}
		i++;
	}
}

//シナリオと手札の証言が一致しているかの確認
bool SceneGameTutorial::CheckTestimony() {

	if (scenarioTestimonyCnt == myDeck.cards.size()) {
		return true;
	}
}

//シナリオ内の証言数の取得
void SceneGameTutorial::GetScenarioTestimony(const std::vector<Scenario::SCENARIO>& scenario) {
	for (int i = 0; i < scenario.size(); i++) {
		if (scenario[i].wordType == 2) {
			scenarioTestimonyCnt++;
		}
	}
}

// ライトのマスデータに円のスポットライトを入れる
void SceneGameTutorial::SpotLight(int cx, int cy, int cr, int baseA)
{
	int x, y;

	// ライトマップ全体を黒(255)にする
	for (y = 0; y < LIGHTMAP_H; y++) {
		for (x = 0; x < LIGHTMAP_W; x++) {
			_mapLight[y * LIGHTMAP_W + x] = baseA;
		}
	}

	// pixel単位からマップ単位に変換
	cx /= LIGHTSIZE_W;
	cy /= LIGHTSIZE_H;
	cr /= LIGHTSIZE_W;

	// 中心座標(cx,cy)を、半径rで囲う正方形を範囲とする
	for (y = cy - cr; y < cy + cr; y++) {
		if (0 <= y && y < LIGHTMAP_H) {		// マップ内に入っているか
			for (x = cx - cr; x < cx + cr; x++) {
				if (0 <= x && x < LIGHTMAP_W) {		// マップ内に入っているか

					// 中心座標(cx,cy)からの距離を求め、アルファ値を決める
					// 本来はsqrt()を使うのだが、これは重いので、使わない計算にする
					//int len = (int)sqrt((float)((cx - x)*(cx - x) + (cy - y)*(cy - y)));
					int len = (int)(((cx - x) * (cx - x) + (cy - y) * (cy - y)));

					// crが減衰値なので、len/crでアルファが決まる
					int a = len * baseA / (cr * cr);	// sqrt()を使わないので、cr^2で割って処理する
					if (a > baseA) { a = baseA; }

					// アルファの値で穴をあける
					_mapLight[y * LIGHTMAP_W + x] = a;

				}
			}
		}
	}
}

//カットインフラグのゲッター
int SceneGameTutorial::GetCutinFlag()
{
	return cutInFlag;
}


void SceneGameTutorial::Input()
{
	// 何もしない
}

void SceneGameTutorial::Process()
{
	int i;

	if (!GetMovieStateToGraph(MovieHandle)) 
	{
		// ポーズ
		if (gPad.gTrg & PAD_INPUT_12 && tutorial_flg != 9) {
			isPause = !isPause;
		}
		//ログ中か変更
		if (gPad.gTrg & PAD_INPUT_3) {
			LogChange();
		}
		if (logflg == 1)
		{
			LogProcess();
		}
		else
		{
			if (isPause == true && tutorial_flg != 9)
			{
				if (Movieflg != 1 && !CheckSoundMem(seBGM1)) {
					Movieflg = 1;
					PlaySoundMem(seBGM2, DX_PLAYTYPE_LOOP);
				}

				//----コマンド別処理----
				switch (_jsonData[messagecnt].command)
				{
				case 0:
					if (gPad.gTrg & PAD_INPUT_2) {
						//テキストが１文字ずつ表示されている間ならすべての文字を出し切る
						if (text_flg == 0) {
							text_flg = 1;
						}
						else
						{
							//通常処理
							messagecnt++;		//messagecntを増加する
							//カウント系のリセット
							gameCnt = 0;
							selectcnt = 0;
							cgchara = LoadGraph(_jsonData[messagecnt].draw.c_str());
							PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
						}
					}
					break;
				case 1:
					tutorial_flg = 1;
					tutorial_cnt = 225;		//「罵詈雑言が飛んでくる」の待機フレーム数
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					break;
				case 2:
					tutorial_flg = 2;
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					break;
				case 3:
					tutorial_flg = 3;
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					tutorial_cnt = 242;		//「次の文字が迫る」の待機フレーム数
					break;
				case 4:
					tutorial_flg = 4;
					tutorial_cnt = 180;
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					break;
				case 5:
					tutorial_flg = 5;
					tutorial_cnt = 345;		//「心の扉を開ける」の待機フレーム数
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					break;
				case 6:
					tutorial_flg = 6;
					tutorial_cnt = 500;		//「心の扉を開ける」の待機フレーム数
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					break;
				case 7:
					tutorial_flg = 7;
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					break;
				case 8:
					tutorial_flg = 8;
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					cgchara = LoadGraph(_jsonData[messagecnt].draw.c_str());
					break;
				case 9:
					tutorial_flg = 9;
					isPause = false;
					gameCnt = 0;
					break;
				}


				// 会話パート処理
				const char* Message1_String = _jsonData[messagecnt].message1.c_str();
				const char* Message2_String = _jsonData[messagecnt].message2.c_str();

				if (gameCnt == 0) {
					drawCnt1 = 0;
					drawCnt2 = 0;
					text_alpha = 0;
					text_flg = 0;
				}
				int i = messagecnt;

				if (gameCnt % DRAW_STRING_COUNT == DRAW_STRING_COUNT - 1) {
					int CharBytes;
					if (Message1_String[drawCnt1] != '\0')
					{
						CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &Message1_String[drawCnt1]);
						drawCnt1 += CharBytes;		// 描画カウンタ
					}
					else if (Message2_String[drawCnt2] != '\0')
					{
						CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &Message2_String[drawCnt2]);
						drawCnt2 += CharBytes;		// 描画カウンタ
					}
					else
					{
						text_flg = 1;
					}
				}
				if (text_flg == 0) {
					//drawcnt分の文字出力
					drawMessage1 = _jsonData[i].message1.substr(0, drawCnt1);
					drawMessage2 = _jsonData[i].message2.substr(0, drawCnt2);
				}
				else
				{
					drawMessage1 = _jsonData[i].message1;
					drawMessage2 = _jsonData[i].message2;
				}
				gameCnt++;
			}
			else
			{
				switch (flg_gameflow)
				{
					//---------- 議論パート ----------
				case 0:
					// 言葉の出現
					SetScenario(*scenario.GetScenario());
					for (int i = 0; i < WORD_MAX; i++)
					{
						if (words[i].use == 1) {
							if (gGameCnt > words[i].count + words[i].waitTime && counterFlag != 1) {
								words[i].Move(words[i].wordType, gameChapter);
							}

							if (tutorial_flg == 1 && tutorial_cnt <= 0) {
								isPause = TRUE;
								break;
							}
							if (tutorial_flg == 3 && tutorial_cnt <= 0) {
								isPause = TRUE;
								break;
							}
							if (tutorial_flg == 5 && tutorial_cnt <= 0) {
								isPause = TRUE;
								break;
							}

							//プレイヤーラインに来た時の処理
							if (words[i].y >= PLAYER_GET_LINE)
							{
								if (words[i].wordType != 2)
								{
									PlaySoundMem(seDamage, DX_PLAYTYPE_BACK);
								}
								//言葉の消去
								words[i].EraseWord();
								if (tutorial_flg == 2) {
									if (tutorial_cnt == 0)
									{
										isPause = TRUE;
									}
									else
									{
										tutorial_cnt == 60;
									}
								}

								//ガード時
								if (flg_shield == 1)
								{
									//ガード状態の処理
									//暴言
									if (words[i].wordType == 1) {
										player.AT -= SHIELD_DAMAGE;		//AT減少
										player.CheckPlayerLife();		//0以下なら0にする
										if (player.AT == 0) {
											lockCnt = 0;
											LockInterval = AT_INTERVAL;
										}
										gEffect.shakecnt = 10;
										gEffect.shakespead = 3;
										if (tutorial_flg == 4)
										{
											isPause = TRUE;
										}
										gEffect.AddEffect(3, words[i].x, words[i].y - 25);
									}
									//証言
									else
									{
										PlaySoundMem(seTestimonyBreak, DX_PLAYTYPE_BACK);
										gEffect.AddEffect(2, words[i].x, words[i].y);	// // ダメージエフェクト
									}
									break;
								}
								else
								{
									//通常状態の処理
									if (words[i].wordType == 1) {
										gHP -= NOMAL_DAMAGE;		//体力減少
										player.CheckPlayerLife();		//0以下なら0にする
										gEffect.AddEffect(0, words[i].x, words[i].y - 100);	// // ダメージエフェクト
										gEffect.shakecnt = 20;
										gEffect.shakespead = 10;
										gEffect.AddEffect(1, SCREEN_W / 2, SCREEN_H / 2);	// ダメージ演出
									}
									//証言
									else if (words[i].wordType == 2) {
										PlaySoundMem(seGetTestimony, DX_PLAYTYPE_BACK);
										if (have_card < deckMax[gameChapter]) {
											if (!myDeck.CheckCard(words[i].numName, words[i].testimonyCnt))
											{
												myDeck.GetCard(words[i].numName, cgStockCard[gameChapter][words[i].numName][words[i].testimonyCnt], words[i].x, words[i].y, words[i].scale, words[i].testimonyCnt);
												have_card++;
												if (tutorial_flg == 6)
												{
													isPause = TRUE;
												}
											}
										}
									}

									break;
								}
							}
						}
					}
					myDeck.MotionCard(flg_gameflow);

					//手札に証言が揃った
					if (scenarioTestimonyCnt == have_card) {
						if (tutorial_flg == 7)
						{
							isPause = TRUE;
						}
						else
						{
							//言葉の動きを停止
							//gGameCnt = 0;
							//反論パート移行のフラグ
							counterFlag = 1;

							//反論パート遷移の画像表示
							if (counterFlag == 1) {

								if (frame <= 3) {
									counterGraph.x = EasingOutSine(frame, -960, 0, 3.0f);
									alpha = EasingOutSine(frame, 0.0f, 255.0f, 3.0f);
									frame += 0.1f;
								}
								else if (frame > 3)
								{
									counterGraph.scale = EasingOutSine(frame, 0.8f, 1.0f, 2.0f);
									frame += 0.1f;
								}
							}

						}
						//ボタンを押したら反論パートへ
						if (tutorial_flg == 8 && gPad.gTrg & PAD_INPUT_2) {

							flg_gameflow = 1;
							PlaySoundMem(seCardGathering, DX_PLAYTYPE_BACK, TRUE);
						}

					}

					// シールド入力
					if (tutorial_flg == 4)
					{
						flg_shield = 1;
					}
					else if (tutorial_flg > 3)
					{
						if (gPad.gKey & PAD_INPUT_5 && LockInterval == 0 && counterFlag != 1)
						{
							//ボタンを押してる間シールドのカウントをプラス
							gardCount++;
							// シールド
							if (gardCount >= GARD_COUNT)
							{
								flg_shield = 1;
								//シールド時効果音
								if (gardCount == GARD_COUNT)
								{
									PlaySoundMem(blockse, DX_PLAYTYPE_BACK, TRUE);
								}
							}
						}
						// シールド解除
						else
						{
							//AT増加
							if (player.AT < MAX_AT && LockInterval == 0) {
								player.AT += AT_SPEED;
								player.CheckPlayerLife();
							}
							flg_shield = 0;
							gardCount = 0;
						}
					}
					if (counterFlag != 1)
					{
						// ゲーム中カウンタ＋1
						gGameCnt++;
					}

					if (tutorial_cnt > 0)
					{
						tutorial_cnt--;
					}

					break;
					//---------- 反論パート ----------
				case 1:
					//反論移行時の演出を消す
					counterFlag = 0;

					if (myDeck.cardMoveFlag != 1)
					{
						// カードの選択
						myDeck.MotionCard(flg_gameflow);
					}

					if (tutorial_flg == 8 && myDeck.flg_selectCard == 3)
					{
						isPause = TRUE;
					}

					//正解時
					if (myDeck.flg_ans == 1)
					{
						//カットイン開始
						cutInFlag = 1;

						// カットインボイス再生
						if (cutInCount == 10) { PlaySoundMem(seCutinVoice, DX_PLAYTYPE_BACK); }

						//フラッシュ開始
						int flashnum = 20;
						if (flashcnt == 0) {
							//フラッシュ初期化
							flash_alpha = 0;
						}
						else if (flashcnt < flashnum / 2) {
							flash_alpha += 255 * 2 / flashnum;
						}
						else if (flashcnt < flashnum) {
							flash_alpha -= 255 * 2 / flashnum;
						}
						flashcnt++;

						//一定時間表示したらカットインを消す
						if (cutInCount > CUTIN_COUNT)
						{
							cutInFlag = 0;
							myDeck.SetCutInFlag(GetCutinFlag());

							if (cutInCount > CUTIN_COUNT + REVERSAL_CARD_COUNT)
							{
								myDeck.cardMoveFlag = 1;
							}

						}
						//カットインカウント
						cutInCount++;
					}
					// 不正解時（反論パートを継続）
					if (myDeck.flg_ans == 2) {
						//一定時間たたないと反応しない
						if (misDirectionFlagCnt > 30) {
							//ボタンを押したらダメージ演出
							if (gPad.gTrg & PAD_INPUT_2) {
								PlaySoundMem(seDamage, DX_PLAYTYPE_BACK);
								gHP -= NOMAL_DAMAGE;		//体力減少
								player.CheckPlayerLife();		//0以下なら0にする
								myDeck.cardMoveFlag = 0;
								gEffect.shakecnt = 20;
								gEffect.shakespead = 10;
								misDirectionFlagCnt = 0;
								flg_gameflow = 1;
								myDeck.flg_ans = 0;
							}
						}
						misDirectionFlagCnt++;
					}

					// 選択したカードの移動
					if (myDeck.cardMoveFlag == 1 && cutInFlag != 1) { myDeck.MoveCard(flg_gameflow); }

					break;

					//---------- 終了 ----------
				case 2:
					// 正解
					if (myDeck.flg_ans == 1)
					{
						gEffect.shakecnt = 20;
						gEffect.shakespead = 10;

						int waitflame = 15;
						if (endEffectCnt == 0)
						{
							PlaySoundMem(seHitTestimony, DX_PLAYTYPE_BACK, TRUE);
							endEffect_waitCnt = waitflame;
							gEffect.AddEffect(2, gikai[4].X, gikai[4].Y);	// // ダメージエフェクト
							endEffectCnt++;
						}
						if (endEffectpattern == ENDEFFECT_PATTERN_MAX - 1)
						{
							if (CheckSoundMem(seBGM1)) { StopSoundMem(seBGM1); }
							if (CheckSoundMem(seBGM2)) { StopSoundMem(seBGM2); }
							SceneBase* scene = new SceneTalk(61);
							ChangeScene(scene);
						}
						else
						{
							//フラッシュ開始
							int flashnum = 20;
							if (flashcnt == 0) {
								//フラッシュ初期化
								flash_alpha = 0;
							}
							else if (flashcnt < flashnum / 2) {
								flash_alpha += 255 * 2 / flashnum;
							}
							else if (flashcnt < flashnum) {
								flash_alpha -= 255 * 2 / flashnum;
							}
							flashcnt++;

							if (endEffect_waitCnt > 0) {
								endEffect_waitCnt--;
							}
							else {
								endEffectCnt++;
							}
						}
						endEffectpattern = anim.cgAnimPattern(endEffectCnt, ENDEFFECT_SPEED, ENDEFFECT_PATTERN_MAX);
					}
					break;
				}

				// ゲーム状況に合わせてカードを変更
				myDeck.SetDrawCard(flg_gameflow);


				// 画面揺らし関連
				gEffect.ProcessShake();

				// エフェクト処理
				gEffect.ProcessEffect();

				//防御アニメーション用
				if (flg_shield == 1 && player.AT != 0) {
					if (lockCnt < 10) {
						lockCnt++;
					}
				}
				else
				{
					//ガードディレイ中
					if (gardCount > 0) {
						if (lockCnt < 3) {
							lockCnt++;
						}
					}
					else if (LockInterval > 0)	//ガード破壊後のディレイ中
					{
						LockInterval--;
						if (lockCnt < 60) {
							lockCnt++;
						}
						if (LockInterval == 0)
						{
							lockCnt = 0;
						}
					}
					else {
						//lockCntを減らしつづける
						if (lockCnt > 0) {
							lockCnt--;
						}
					}
				}
			}
			// 背景アニメーション
			_cgBgAnimcnt++;
			_cgBgAnimpattern = anim.cgAnimPattern(_cgBgAnimcnt, CGBGANIM_SPEED, CGBGANIM_PATTERN_MAX);
		}
	}

	//体力ヌルヌル変更
	player.LifeProcess();

	//ゲームオーバー確認
	if (gHP <= 0) {
		if (CheckSoundMem(seBGM1)) { StopSoundMem(seBGM1); }
		if (CheckSoundMem(seBGM2)) { StopSoundMem(seBGM2); }
		//ゲームオーバー処理
		SceneBase* scene = new SceneGameover(300);
		ChangeScene(scene);
	}
}

void SceneGameTutorial::Draw()
{
	// 背景
	//フィニッシュ中は映さない
	if (flg_gameflow != 2) {
		if (flg_shield == 1 && flg_gameflow == 0) { DrawGraph(0, 0, gGlobal->_cgBg[_cgBgAnimpattern], FALSE); }
		else { DrawGraph(gEffect.shakespead * gEffect.shake, 0, gGlobal->_cgBg[_cgBgAnimpattern], FALSE); }
	}

	int i;
	int center = myDeck.GetCenterCard();		// 選択中のカード位置
	// ゲームモード
	switch (flg_gameflow) {
	case 0:
		
		for (int i = 0; i < WORD_MAX; i++)
		{
			if (words[i].use != 0)
			{
				if (words[i].wordType == 1) DrawRotaGraph(words[i].x, words[i].y, words[i].scale, 0, words[i].cgName, 1, 0);
				if (words[i].wordType == 2) DrawRotaGraph(words[i].x, words[i].y, words[i].scale, 0, cgTestimony[gameChapter][words[i].numName][words[i].testimonyCnt], 1, 0);
			}
			
		}

		//防御アニメーション描画
		if (MAX_AT / 5 * 4 < player.AT) {
			if (lockCnt <= 5 && isPause == true) {
				DrawGraph(0, -50, LockEffect[0][lockCnt], TRUE);
			}
			else if (lockCnt <= 5) {
				DrawGraph(0 + rand() % 10 - 10, -50 + rand() % 10 - 10, LockEffect[0][lockCnt], TRUE);
			}
			else if (isPause == true) {
				DrawGraph(0, -50, LockEffect[0][lockCnt], TRUE);
			}
			else
			{
				DrawGraph(gEffect.shakespead * gEffect.shake * rand() % 10 - 10, -50, LockEffect[0][lockCnt], TRUE);
			}
		}
		else if (MAX_AT / 5 * 3 < player.AT)
		{
			if (isPause == true)
			{
				DrawGraph(0, -50, LockEffect[1][lockCnt], TRUE);
			}
			else
			{
				DrawGraph(gEffect.shakespead * gEffect.shake * rand() % 10 - 10, -50, LockEffect[1][lockCnt], TRUE);
			}
		}
		else if (MAX_AT / 5 * 2 < player.AT)
		{
			if (isPause == true)
			{
				DrawGraph(0, -50, LockEffect[2][lockCnt], TRUE);
			}
			else
			{
				DrawGraph(gEffect.shakespead * gEffect.shake * rand() % 10 - 10, -50, LockEffect[2][lockCnt], TRUE);
			}
		}
		else if (player.AT != 0)
		{
			if (isPause == true)
			{
				DrawGraph(0, -50, LockEffect[3][lockCnt], TRUE);
			}
			else
			{
				DrawGraph(gEffect.shakespead * gEffect.shake * rand() % 10 - 10, -50, LockEffect[3][lockCnt], TRUE);
			}
		}
		else
		{
			DrawGraph(0, -50, LockEffect[4][lockCnt / 6], TRUE);
		}
		break;
	
	}

	// スポットライト
	if (flg_gameflow > 0)
	{
		if (myDeck.flg_selectCard == 3)
		{
			for (i = 0; i < ENEMY_MAX; i++)
			{
				if (i == myDeck.cards[center].num)
				{
					SpotLight(gikai[i].X, gikai[i].Y, 170, 150);
					// ライトマップを上から半透明描画
					for (int y = 0; y < LIGHTMAP_H; y++) {
						for (int x = 0; x < LIGHTMAP_W; x++) {
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, _mapLight[y * LIGHTMAP_W + x]);		// 半透明描画指定
							DrawBox(x * LIGHTSIZE_W, y * LIGHTSIZE_H, x * LIGHTSIZE_W + LIGHTSIZE_W, y * LIGHTSIZE_H + LIGHTSIZE_H, GetColor(0, 0, 0), TRUE);	// 黒
						}
					}
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定
				}
			}
		}
	}

	gEffect.DrawEffect();

	// ボタンUI
	if (myDeck.flg_selectCard == 3)
	{
		DrawGraph(1757, 956, cgHanronButtonUI, TRUE);
	}

	//反論移行時
	if (counterFlag == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(counterGraph.x, 406, cgCounter, TRUE);
		DrawRotaGraph(counterGraph.x + 1157 + 69, 471 + 69, counterGraph.scale, 0, cgCounter_x, 1, 0, 0);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定

	// カード（手札）
	myDeck.DrawCard(flg_gameflow);		// カード（手札）描画

	if (flg_gameflow == 2)
	{
		DrawGraph(0, 0, cgEndEffect[endEffectpattern], TRUE);
		gEffect.DrawEffect();
	}
	else
	{
		// UI
		if (isPause == true) {
			//------------会話中----------
			const char* Name_String = _jsonData[messagecnt].name.c_str();
			const char* draw_String = _jsonData[messagecnt].draw.c_str();
			int nameflg = 0;
			if (Name_String[messagecnt] != '\0')
			{
				nameflg = 1;
			}

			if (draw_String[messagecnt] != '\0')
			{
				DrawGraph(0, 0, cgchara, TRUE);
				ui.DrawGamemainUI(reHP); //UI作成
			}
			else
			{
				ui.DrawTalkUI(reHP, nameflg); //UI作成
				//テキスト送り画像の点滅
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, text_alpha);
				DrawGraph(1790, 945, cgtext, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				//-----------メッセージ読み込み----------------

				int massagefontsize;	//フォントサイズ
				int bt;					//行間
				int namefontsize;
				int savefontsize;
				savefontsize = GetFontSize(); //元のフォントサイズを保存
				//コマンド処理
				switch (_jsonData[messagecnt].command)
				{
				case 0:
					//-----------メッセージ読み込み----------------
					massagefontsize = 62;		//フォントサイズ
					bt = 20;					//行間

					namefontsize = 48;
					SetFontSize(namefontsize);
					DrawPosString(230, 890, 0, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());
					SetFontSize(massagefontsize);

					DrawFormatString(400, 850, GetColor(255, 255, 255), drawMessage1.c_str());							//一行目

					DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), drawMessage2.c_str());	//二行目
					break;
				}

				SetFontSize(savefontsize);	//フォントサイズを戻す
			}
		}
		else
		{
			ui.DrawGamemainUI(reHP);	//UI呼び出し;
		}
	}

	//フラッシュ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flash_alpha);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//動画描画
	if (GetMovieStateToGraph(MovieHandle)) {
		DrawGraph(0, 0, MovieHandle, FALSE);
	}

	//カットイン表示
	if (cutInFlag == 1)
	{
		int t = cutInCount / 4;
		if (t < 30)
		{
			DrawGraph(0, 0, cgCutIn[t], TRUE);
		}
	}

	//反論失敗時
	if (myDeck.flg_ans == 2) {
		DrawGraph(0, 826, cgHanronMiss, FALSE);
	}

	//ログ描画
	if (logflg == 1)
	{
		LogDraw();
	}

}
