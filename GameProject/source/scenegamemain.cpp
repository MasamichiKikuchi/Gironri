#include	"scenegamemain.h"
#include	"DxLib.h"
#include	"gamemain.h"
#include	"data.h"
#include	"scenetalk.h"
#include	"scenelook.h"
#include	"mymath.h"
#include	"SceneGameover.h"
#include	"utf8sjis.h"	// jsonの日本語文字を使うために必要
#include	<iostream>
#include	<string>

//菊池担当箇所　・161～237行　・393～457行　・494～510行　・767～866行　・972～987行

SceneGameMain::SceneGameMain(int chapter)
{
	// チャプター
	gameChapter = chapter;
	
	std::string img_path;
	// 画像のロード
	_cgBgAnimcnt = 0;
	_cgBgAnimpattern = 0;
	_cgBgJishouAnimpattern = 0;

	// jsonファイルの読み込み
	std::ifstream file("res/jsonfile/miss.json");
	nlohmann::json json;
	file >> json;
	int i = 0;
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
		jsonfile.at("voice").get_to(_jsonData[i].voice);
		jsonfile.at("bgY").get_to(_jsonData[i].bgY);
		jsonfile.at("bg").get_to(_jsonData[i].bg);

		// jsonの文字列を、UTF-8からShift-JISに変換
		_jsonData[i].message1 = ConvUTF8toSJIS(_jsonData[i].message1);
		_jsonData[i].message2 = ConvUTF8toSJIS(_jsonData[i].message2);
		_jsonData[i].draw = ConvUTF8toSJIS(_jsonData[i].draw);
		_jsonData[i].name = ConvUTF8toSJIS(_jsonData[i].name);
		_jsonData[i].voice = ConvUTF8toSJIS(_jsonData[i].voice);
		_jsonData[i].bg = ConvUTF8toSJIS(_jsonData[i].bg);
		i++;
	}
	messagecnt = 0;

	// 議論パート
	gGameCnt = 0;

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
	ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seBGM1);
	ChangeVolumeSoundMem(255 * BGM_VOLUME / 200, seBGM2);
	ChangeVolumeSoundMem(255 * DAMADE_SE_VOLUME / 100, seDamage);
	ChangeVolumeSoundMem(255 * TESTIMONY_SE_VOLUME / 100, seSay);
	ChangeVolumeSoundMem(255 * SHIELD_SE_VOLUME / 100, blockse);

	//フラグ関連
	flg_gameflow = 0;
	flg_shield = 0;
	Movieflg = 0;
	scenarioTestimonyCnt = 0;
	isPause = false;
	gameFinishFlag = 0;

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
	scenario.SetEnemyPosition(gameChapter);

	//シナリオのセット
	scenario.SetChapterScenario(gameChapter);
	//シナリオ内の証言数を取得
	GetScenarioTestimony(*scenario.GetScenario());
	counterFlag = 0;
	frame = 0;
	alpha = 0;
	counterGraph.scale = 1.0f;

	MovieHandle = 0;
	//動画のロード
	//自傷議論用
	if (gameChapter == 5)
	{
		MovieHandle = mvJishou_ikou;
	}
	//偽証議論用
	else
	{
		MovieHandle = mvGiron_ikou;
	}

	//動画
	SeekMovieToGraph(MovieHandle, 0);
	PlayMovieToGraph(MovieHandle);
	PlaySoundMem(seBGM1, DX_PLAYTYPE_BACK);
	//音量
	ChangeMovieVolumeToGraph(0, MovieHandle);

}

SceneGameMain::~SceneGameMain()
{
	int i;
	//シナリオの初期化
	for (int i = 0; i < WORD_MAX; i++) {
		words[i].use = 0;
	}
}

// 言葉追加
void SceneGameMain::AddWord(int wordType, int count, int cgName, int x, int y, int waitTime, int seName, int numName, int ttmCnt) {

	//チャプター３の場合、シナリオが最後までいったら終了
	if (gameChapter == 3 && wordType == -1) {
		gameFinishFlag = 1;
	}
	//シナリオが最後までいったらループ
	else if (wordType == -1) {
		gGameCnt = 0;
	}

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
				words[i].testimonyCnt = ttmCnt;

				//SE再生
				PlaySoundMem(seName, DX_PLAYTYPE_BACK);
				break;
			}
		}
	}
}

// 言葉の出現シナリオ
void SceneGameMain::SetScenario(const std::vector<Scenario::SCENARIO>& scenario)
{
	int i = 0;
	while (scenario[i].gamecnt != -1) {	// データの最後までをループ
		if (scenario[i].gamecnt == gGameCnt) {
			// シナリオデータのgamecntが一致した
			AddWord(scenario[i].wordType, scenario[i].gamecnt, scenario[i].cgName, scenario[i].x, scenario[i].y, scenario[i].waitTime, scenario[i].seName, scenario[i].numName, scenario[i].testimonyCnt);
		}
		i++;
	}
}

//シナリオと手札の証言が一致しているかの確認
bool SceneGameMain::CheckTestimony() {

	if (scenarioTestimonyCnt == myDeck.cards.size()) {
		return true;
	}
}

//シナリオ内の証言数の取得
void SceneGameMain::GetScenarioTestimony(const std::vector<Scenario::SCENARIO>& scenario) {
	for (int i = 0; i < scenario.size(); i++) {
		if (scenario[i].wordType == 2) {
			scenarioTestimonyCnt++;
		}
	}
}

//カットインフラグのゲッター
int SceneGameMain::GetCutinFlag()
{
	return cutInFlag;
}

// ライトのマスデータに円のスポットライトを入れる
void SceneGameMain::SpotLight(int cx, int cy, int cr, int baseA)
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

void SceneGameMain::Input()
{
	// 何もしない
}

void SceneGameMain::Process()
{
	int i;

	if (!GetMovieStateToGraph(MovieHandle)) {
		if (Movieflg != 1 && !CheckSoundMem(seBGM1)) {
			Movieflg = 1;
			PlaySoundMem(seBGM2, DX_PLAYTYPE_LOOP);
		}
		// ポーズ
		if (gPad.gTrg & PAD_INPUT_8) {
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
			//ポーズ状態でない
			if (isPause != true)
			{
				switch (flg_gameflow)
				{
					//---------- 議論パート ----------
				case 0:
					// 言葉の出現
					SetScenario(*scenario.GetScenario());
					for (int i = 0; i < WORD_MAX; i++)
					{
						//言葉は使用可能か
						if (words[i].use == 1) {
							//出現から一定時間たったら移動
							if (gGameCnt > words[i].count + words[i].waitTime && counterFlag != 1) {
								words[i].Move(words[i].wordType, gameChapter);
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
					if (scenarioTestimonyCnt == have_card && gameChapter != 3) {
						//言葉の動きを停止
						//gGameCnt = 0;
						//反論パート移行のフラグ
						counterFlag = 1;

						//反論パート遷移の画像表示
						if (counterFlag == 1) {

							//画像の表示
							if (frame <= 3) {
								counterGraph.x = EasingOutSine(frame, -960, 0, 3.0f);
								alpha = EasingOutSine(frame, 0.0f, 255.0f, 3.0f);
								frame += 0.1f;
							}
							//ボタンの大きさを変える
							else if (frame > 3)
							{
								counterGraph.scale = EasingOutSine(frame, 0.8f, 1.0f, 2.0f);
								frame += 0.1f;
							}
						}


						//ボタンを押したら反論パートへ
						if (gPad.gTrg & PAD_INPUT_2) {

							flg_gameflow = 1;
							PlaySoundMem(seCardGathering, DX_PLAYTYPE_BACK, TRUE);
						}

					}

					// シールド入力
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
					if (counterFlag != 1)
					{
						// ゲーム中カウンタ＋1
						gGameCnt++;
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
						// IPを減らし続ける
						//if (myDeck.flg_selectCard == 3 ) { player.IP--; }
					}

					//正解時
					if (myDeck.flg_ans == 1)
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

						//カットイン開始
						cutInFlag = 1;

						// カットインボイス再生
						if (cutInCount == 10) { PlaySoundMem(seCutinVoice, DX_PLAYTYPE_BACK); }

						//一定時間表示したらカットインを消す
						if (cutInCount > CUTIN_COUNT)
						{
							cutInFlag = 0;
							myDeck.SetCutInFlag(GetCutinFlag());

							if (cutInCount > CUTIN_COUNT + REVERSAL_CARD_COUNT)
							{
								myDeck.cardMoveFlag = 1;
								flashcnt = 0;//フラッシュカウント初期化
							}
						}
						//カットインカウント
						cutInCount++;
					}
					// 不正解時（反論パートを継続）
					if (myDeck.flg_ans == 2) {
						if (misDirectionFlagCnt == 0) {

							for (int i = 0; i < 999; i++) {
								if (_jsonData[messagecnt].command == gameChapter * 100
									+ myDeck.cards[myDeck.cards.size() / 2].num * 10
									+ myDeck.cards[myDeck.cards.size() / 2].testimonyCnt * 1) {
									break;
								}
								messagecnt++;
							}
							drawCnt1 = 0;
							drawCnt2 = 0;
							text_flg = 0;
						}

						// 会話パート処理
						const char* Message1_String = _jsonData[messagecnt].message1.c_str();
						const char* Message2_String = _jsonData[messagecnt].message2.c_str();


						if (misDirectionFlagCnt % DRAW_STRING_COUNT == DRAW_STRING_COUNT - 1) {
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
							drawMessage1 = _jsonData[messagecnt].message1.substr(0, drawCnt1);
							drawMessage2 = _jsonData[messagecnt].message2.substr(0, drawCnt2);
						}
						else
						{
							//すべての文字出力
							drawMessage1 = _jsonData[messagecnt].message1;
							drawMessage2 = _jsonData[messagecnt].message2;
						}
						misDirectionFlagCnt++;
						//ボタンを押したらダメージ演出
						if (gPad.gTrg & PAD_INPUT_2) {
							//一定時間たたないと反応しない
							if (text_flg == 1) {
								if (_jsonData[messagecnt + 1].command != gameChapter * 100
									+ myDeck.cards[myDeck.cards.size() / 2].num * 10
									+ myDeck.cards[myDeck.cards.size() / 2].testimonyCnt * 1)
								{
									PlaySoundMem(seDamage, DX_PLAYTYPE_BACK);
									gHP -= NOMAL_DAMAGE;		//体力減少
									player.CheckPlayerLife();		//0以下なら0にする
									myDeck.cardMoveFlag = 0;
									gEffect.shakecnt = 20;
									gEffect.shakespead = 10;
									misDirectionFlagCnt = 0;
									flg_gameflow = 1;
									myDeck.flg_ans = 0;
									messagecnt = 0;
								}
								else
								{
									misDirectionFlagCnt = 0;
									messagecnt++;
								}
							}
							else
							{
								text_flg = 1;
							}
						}
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
							gEffect.AddEffect(2, gikai[tblAnsCard[gameChapter].answerNum].X, gikai[tblAnsCard[gameChapter].answerNum].Y);	// // ダメージエフェクト
							endEffectCnt++;
						}
						if (endEffectpattern == ENDEFFECT_PATTERN_MAX - 1)
						{
							if (CheckSoundMem(seBGM1)) { StopSoundMem(seBGM1); }
							if (CheckSoundMem(seBGM2)) { StopSoundMem(seBGM2); }
							SceneBase* scene = new SceneTalk(gameChapter + 61);
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

				// ゲーム終了フラグが有効の場合、次のシーンへ
				if (gameFinishFlag == 1)
				{
					if (CheckSoundMem(seBGM1)) { StopSoundMem(seBGM1); }
					if (CheckSoundMem(seBGM2)) { StopSoundMem(seBGM2); }
					SceneBase* scene = new SceneTalk(gameChapter + 61);
					ChangeScene(scene);
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
						if (LockInterval == 1 && gPad.gKey & PAD_INPUT_5) {
							// シールド入力中はLockIntervalを０にしない
						}
						else
						{
							LockInterval--;
						}

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
			if (gameChapter == 5)
			{
				_cgBgJishouAnimpattern = anim.cgAnimPattern(_cgBgAnimcnt, CGBGANIM_SPEED, CG_JISHOU_BGANIM_PATTERN_MAX);

			}
			else
			{
				_cgBgAnimpattern = anim.cgAnimPattern(_cgBgAnimcnt, CGBGANIM_SPEED, CGBGANIM_PATTERN_MAX);
			}
		}
	}

	//体力ヌルヌル変更
	player.LifeProcess();

	//ゲームオーバー確認
	if (gHP <= 0) {
		if (CheckSoundMem(seBGM1)) { StopSoundMem(seBGM1); }
		if (CheckSoundMem(seBGM2)) { StopSoundMem(seBGM2); }
		//ゲームオーバー処理
		SceneBase* scene = new SceneGameover(200 + gameChapter);
		ChangeScene(scene);
	}
}

void SceneGameMain::Draw()
{
	// 背景
	//フィニッシュ中は映さない
	if (flg_gameflow != 2) {
		//自傷議論
		if (gameChapter == 5)
		{
			//シールド時は揺らさない
			if (flg_shield == 1 && flg_gameflow == 0) { DrawGraph(0, 0, gGlobal->_cgJishouBg[_cgBgJishouAnimpattern], FALSE); }
			//通常状態ダメージ時揺らす
			else { DrawGraph(gEffect.shakespead * gEffect.shake, 0, gGlobal->_cgJishouBg[_cgBgJishouAnimpattern], FALSE); }
		}
		//偽証議論
		else
		{
			//シールド時は揺らさない
			if (flg_shield == 1 && flg_gameflow == 0) { DrawGraph(0, 0, gGlobal->_cgBg[_cgBgAnimpattern], FALSE); }
			//通常状態ダメージ時揺らす
			else { DrawGraph(gEffect.shakespead * gEffect.shake, 0, gGlobal->_cgBg[_cgBgAnimpattern], FALSE); }
		}
	}
	
	int i;
	int center = myDeck.GetCenterCard();		// 選択中のカード位置
	// ゲームモード
	switch (flg_gameflow){
	case 0:
		
		//言葉の描画
		for (int i = 0; i < WORD_MAX; i++)
		{
			if (words[i].use != 0)
			{
				//暴言
				if (words[i].wordType == 1) DrawRotaGraph(words[i].x, words[i].y, words[i].scale, 0, words[i].cgName, 1, 0);
				//証言
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
			else if (isPause == true)
			{
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
		//防御回復アニメーション描画
		//防御のアニメーションが出てる間は描画しない
		if ((flg_shield != 1) && (gardCount >= GARD_COUNT) || gardCount == 0 && lockCnt == 0 || (flg_shield != 1) && lockCnt > 3) {

			if (LockInterval >= 16) {
				DrawGraph(0, -50, gateReset[0], TRUE);
			}
			else if (LockInterval > 14) {
				DrawGraph(0, -50, gateReset[1], TRUE);
			}
			else if (LockInterval > 12) {
				DrawGraph(0, -50, gateReset[2], TRUE);
			}
			else if (LockInterval > 10) {
				DrawGraph(0, -50, gateReset[3], TRUE);
			}
			else if (LockInterval > 8) {
				DrawGraph(0, -50, gateReset[4], TRUE);
			}
			else if (LockInterval > 6) {
				DrawGraph(0, -50, gateReset[5], TRUE);
			}
			else if (LockInterval > 4) {
				DrawGraph(0, -50, gateReset[6], TRUE);
			}
			else if (LockInterval > 2) {
				DrawGraph(0, -50, gateReset[7], TRUE);
			}
			else {
				DrawGraph(0, -50, gateReset[8], TRUE);
			}

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

	//エフェクトの描画
	gEffect.DrawEffect();

	// ボタンUI
	if (flg_gameflow == 0)
	{
		DrawGraph(1717, 956, cgGironButtonUI, TRUE);
	}
	else if (myDeck.flg_selectCard == 3)
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

	// フィニッシュ
	if (flg_gameflow == 2)
	{
		//背景エフェクト
		//自傷議論
		if (gameChapter == 5)
		{
			DrawGraph(0, 0, cgJisyou_EndEffect[endEffectpattern], TRUE);
		}
		//偽証議論
		else
		{
			DrawGraph(0, 0, cgEndEffect[endEffectpattern], TRUE);
		}
		gEffect.DrawEffect();
	}
	else
	{
		// UI
		ui.DrawGamemainUI(reHP);			//UI呼び出し
	}

	//フラッシュ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flash_alpha);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//動画描画
	if (GetMovieStateToGraph(MovieHandle)) {
		DrawGraph(0, 0, MovieHandle, FALSE);
	}

	//反論失敗時
	if (myDeck.flg_ans == 2) {
		const char* Name_String = _jsonData[messagecnt].name.c_str();
		int nameflg = 0;
		if (Name_String[0] != '\0')
		{
			nameflg = 1;
		}
		// UI
		ui.DrawTalkUI(reHP, nameflg); //UI作成

		int massagefontsize = 62;		//フォントサイズ
		int bt = 20;					//行間

		int namefontsize = 48;
		SetFontSize(namefontsize);
		DrawPosString(230, 890, 0, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());			//名前表示
		SetFontSize(massagefontsize);

		DrawFormatString(400, 850, GetColor(255, 255, 255), drawMessage1.c_str());							//一行目

		DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), drawMessage2.c_str());	//二行目
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

	//ポーズ時
	if (isPause == true)
	{
		//操作説明
		DrawGraph(0, 0, cgPlayguide, TRUE);
	}

	//ログ描画
	if (logflg == 1)
	{
		LogDraw();
	}

}
