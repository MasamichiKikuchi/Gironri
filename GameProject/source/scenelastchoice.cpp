#include	"SceneLastChoice.h"
#include	"DxLib.h"
#include	"mymath.h"
#include	"data.h"
#include	"gamemain.h"
#include	"scenelook.h"
#include	"scenetalk.h"
#include	"scenegamemain.h"
#include	"SceneGameover.h"
#include	"scenegametitle.h"
#include	"scenegametutorial.h"
#include	"utf8sjis.h"	// jsonの日本語文字を使うために必要
#include	<cassert>
#include	<string>

SceneLastChoice::SceneLastChoice(int chapter)
{
	savechapter = chapter;

	cgChoiceBg = LoadGraph("res/JishouChoicepart/CG_jisyou.jpg");
	cgtext = LoadGraph("res/wait_cursor.png");
	cgchoice[0] = LoadGraph("res/JishouChoicepart/UI_nonselect.png");
	cgchoice[1] = LoadGraph("res/JishouChoicepart/UI_select.png");
	cg_popup = LoadGraph("");
	cg_UI_talk[0] = LoadGraph("res/UI/UI_kaiwa.png");
	cg_UI_talk[1] = LoadGraph("res/UI/UI_jiysou.png");

	for (int n = 0; n < 15; n++)
	{
		std::string img = "res/JishouChoicepart/correctEffect/CG_gisyou_";
		img += std::to_string(n + 1);
		img += ".png";
		cgCorrectEffect[n] = LoadGraph(img.c_str());
	}

	int i;
	// jsonファイルの読み込み
	std::ifstream file("res/jsonfile/LastChoice.json");
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
	for (int i = 0; i < LAST_CHOICE_MAX; i++)
	{
		save_messagecnt[i] = 0;
	}
	// 画像ファイル読み込み
	int n;

	//アニメーション読み込み

	popupflg = 0;

	animcnt = 0;
	animflg = 0;
	animnum = -1;
	flash_alpha = 0;
	effectcnt = 0;
	flashcnt = 999;
	gameCnt = 0;
	CorrectEffectflg = 0;
	add = -1;
	text_alpha = 0;
	popup_size = 0.0f;
	text_flg = 0;
	blackflg = 0;
	backTalkpartflg = 0;
	CorrectEffectcnt = 0;
	CorrectEffectnum = 1;
	step = 0;
	canskip_UI_flg = 0;
	//アニメーション名
	Anim0 = "AnimY";
	Anim1 = "AnimB";
	Anim2 = "AnimG";
	Anim3 = "AnimR";
	Anim4 = "AnimP";

	BGM0 = "BGM0";
	BGM1 = "BGM1";
	BGM2 = "BGM2";
	BGM3 = "BGM3";

	// メッセージカウント読み込み
	messagecnt = 0;

	//BGM・se
	se_next = LoadSoundMem("res/se/se_seikai.mp3");
	se_choice = LoadSoundMem("res/se/cho.mp3");
	se_voice = 0;
	ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, se_choiceBGM[0]);
	PlaySoundMem(se_choiceBGM[0], DX_PLAYTYPE_LOOP);
}

SceneLastChoice::~SceneLastChoice()
{
	for (int i = 0; i < 5; i++) {
		if (CheckSoundMem(seBGM[i])) { StopSoundMem(seBGM[i]); }
	}
	for (int i = 0; i < 6; i++) {
		if (CheckSoundMem(se_choiceBGM[i])) { StopSoundMem(se_choiceBGM[i]); }
	}
	DeleteSoundMem(se_next);
	DeleteSoundMem(se_choice);
	DeleteSoundMem(se_voice);
	DeleteGraph(cgtext);
	DeleteGraph(cg_popup);
	DeleteGraph(cgchoice[0]);
	DeleteGraph(cgchoice[1]);
	for (int n = 0; n < 15; n++)
	{
		DeleteGraph(cgCorrectEffect[n]);
	}
}

void SceneLastChoice::Flash() {
	if (flashcnt == 0) {
		//フラッシュ初期化
		flash_alpha = 0;
	}
	else if (flashcnt < FRASH_MAX_NUM / 4) {
		flash_alpha += 255 * 4 / FRASH_MAX_NUM;
	}
	else if (flashcnt < FRASH_MAX_NUM) {
		flash_alpha -= 255 * 2 / FRASH_MAX_NUM;
	}
	else
	{
		flash_alpha = 0;
		flashcnt = 999;
	}

	if (flash_alpha < 0) {
		flash_alpha = 0;
	}
	if (flash_alpha > 255) {
		flash_alpha = 255;
	}

	if (flashcnt < 999) {
		flashcnt++;
	}
}

void SceneLastChoice::savemessage()
{
	for (int i = 0; i < MAX_LOGSAVE; i++) {
		if (logsave[i].use == 0) {
			logsave[i].use = 1;
			logsave[i].message1 = _jsonData[messagecnt].message1.c_str();
			logsave[i].message2 = _jsonData[messagecnt].message2.c_str();
			logsave[i].name = _jsonData[messagecnt].name.c_str();
			break;
		}
	}
}

void SceneLastChoice::Input()
{

}
void SceneLastChoice::Process()
{
	switch (step)
	{
	case 0:
		// フェードアウト開始
		ColorMask(0, 0, 0, 255);
		ColorFadeIn(60);
		step++;
		break;
	case 1:
		if (IsColorFade() == 0)
		{
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
				if (blackflg != 1) {
					//----コマンド別処理----
					int save_cmd;
					switch (_jsonData[messagecnt].command)
					{
					case 6:
						//BGM処理
						if (_jsonData[messagecnt].voice.c_str() == BGM0) {
							for (int i = 0; i < 5; i++) {
								if (CheckSoundMem(seBGM[i])) { StopSoundMem(seBGM[i]); }
							}
							PlaySoundMem(seBGM[0], DX_PLAYTYPE_LOOP);
							ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seBGM[0]);
						}
						else if (_jsonData[messagecnt].voice.c_str() == BGM1) {
							for (int i = 0; i < 5; i++) {
								if (CheckSoundMem(seBGM[i])) { StopSoundMem(seBGM[i]); }
							}
							PlaySoundMem(seBGM[1], DX_PLAYTYPE_LOOP);
							ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seBGM[1]);
						}
						else if (_jsonData[messagecnt].voice.c_str() == BGM2) {
							for (int i = 0; i < 5; i++) {
								if (CheckSoundMem(seBGM[i])) { StopSoundMem(seBGM[i]); }
							}
							PlaySoundMem(seBGM[2], DX_PLAYTYPE_LOOP);
							ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seBGM[2]);
						}
						else if (_jsonData[messagecnt].voice.c_str() == BGM3) {
							for (int i = 0; i < 5; i++) {
								if (CheckSoundMem(seBGM[i])) { StopSoundMem(seBGM[i]); }
							}
							PlaySoundMem(seBGM[3], DX_PLAYTYPE_LOOP);
							ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seBGM[3]);
						}
						messagecnt++;
						gameCnt = 0;
						break;
					case 0:
						// 21:背景を少し暗く 22:背景をさらに暗く 23:背景を暗く
					case 21:
					case 22:
					case 23:
						if (gPad.gTrg & PAD_INPUT_4 && canskip_UI_flg == 1) {
							SceneBase* scene = new SceneLastChoice(savechapter);
							ChangeScene(scene);
						}
						if (gPad.gTrg & PAD_INPUT_2) {
							//テキストが１文字ずつ表示されている間ならすべての文字を出し切る
							if (text_flg == 0) {
								text_flg = 1;
							}
							else {
								savemessage();
								//次がpopupの処理
								if (_jsonData[messagecnt + 1].command == 91) {
									cg_popup = LoadGraph(_jsonData[messagecnt + 1].draw.c_str());
									messagecnt += 2;
									popupflg = 1;
									popup_size = 0.0f;
								}
								else if (_jsonData[messagecnt + 1].command == 92) {
									messagecnt += 2;
									popupflg = 0;
								}
								//通常処理
								else
								{
									messagecnt++;		//messagecntを増加する
								}
								//カウント系のリセット
								gameCnt = 0;
								selectcnt = 0;
								PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
							}
						}
						break;
						// フラッシュ
					case 24:
						if (flashcnt == 0) {
							//フラッシュ初期化
							flash_alpha = 0;
						}
						else if (flashcnt < FRASH_MAX_NUM / 4) {
							flash_alpha += 255 * 4 / FRASH_MAX_NUM;
						}
						else if (flashcnt < FRASH_MAX_NUM) {
							flash_alpha -= 255 * 2 / FRASH_MAX_NUM;
						}
						else
						{
							if (gPad.gTrg & PAD_INPUT_2) {
								savemessage();
								messagecnt++;
								gameCnt = 0;
								selectcnt = 0;
								flashcnt = 0;
								flash_alpha = 0;
								PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
							}
						}
						flashcnt++;
						break;
					case 71:
						if (flashcnt == 0) {
							//フラッシュ初期化
							flash_alpha = 0;
						}
						else if (flashcnt < FRASH_MAX_NUM / 4) {
							flash_alpha += 255 * 4 / FRASH_MAX_NUM;
						}
						else
						{
							SceneBase* scene = new SceneGameTitle();
							ChangeScene(scene);
						}
						flashcnt++;
						break;
					case 72:
						if (1) {
							lastchoice_skipflg = 1;
							SceneBase* scene = new SceneLastChoice(savechapter);
							ChangeScene(scene);
						}
						break;
					case 2:	//正解の処理
					case 3:	//不正解の処理
					case 4:	//不正解の処理
						//つながっているコマンドをすべて表示する
						save_cmd = messagecnt;
						for (int i = 0; i < LAST_CHOICE_MAX; i++)
						{
							if (_jsonData[messagecnt].command != 2 && _jsonData[messagecnt].command != 3 && _jsonData[messagecnt].command != 4) {
								break;
							}
							save_messagecnt[i] = messagecnt;
							messagecnt++;
						}
						messagecnt = save_cmd;

						//選択ボタン
						if (gPad.gTrg & PAD_INPUT_RIGHT) {
							selectcnt++;
							if (_jsonData[messagecnt + selectcnt].command != 2 && _jsonData[messagecnt + selectcnt].command != 3 && _jsonData[messagecnt + selectcnt].command != 4) {
								selectcnt--;
							}
							else
							{
								PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
							}
						}
						if (gPad.gTrg & PAD_INPUT_LEFT) {
							selectcnt--;
							if (_jsonData[messagecnt + selectcnt].command != 2 && _jsonData[messagecnt + selectcnt].command != 3 && _jsonData[messagecnt + selectcnt].command != 4) {
								selectcnt++;
							}
							else
							{
								PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
							}
						}

						if (gPad.gTrg & PAD_INPUT_2)
						{
							//選ばれた選択肢が部分正解
							if (_jsonData[messagecnt + selectcnt].command == 2) {
								gameCnt = 0;
								selectcnt = 0;
								CorrectEffectflg = 1;
								CorrectEffectcnt = 0;
								flashcnt = 0;
								if (CheckSoundMem(se_choiceBGM[CorrectEffectnum - 1])) { StopSoundMem(se_choiceBGM[CorrectEffectnum - 1]); }
								PlaySoundMem(se_choiceBGM[CorrectEffectnum], DX_PLAYTYPE_LOOP);
								ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, se_choiceBGM[CorrectEffectnum]);
								CorrectEffectnum++;
								for (int i = 0; i < JSON_MAX; i++)
								{
									if (_jsonData[messagecnt].command != 0) {
										messagecnt++;
										gameCnt = 0;
										continue;
									}
									break;
								}
								PlaySoundMem(se_next, DX_PLAYTYPE_BACK);
							}
							else if (_jsonData[messagecnt + selectcnt].command == 3)
							{
								//選ばれた選択肢が不正解
								gameCnt = 0;
								selectcnt = 0;

								for (int i = 0; i < JSON_MAX; i++)
								{
									if (_jsonData[messagecnt].command != 31) {
										messagecnt++;
										gameCnt = 0;
										continue;
									}
									break;
								}
							}
							else if (_jsonData[messagecnt + selectcnt].command == 4)
							{
								//選ばれた選択肢が完全正解
								gameCnt = 0;
								selectcnt = 0;
								blackflg = 1;
								flashcnt = 0;
								backTalkpartflg = 1;
								CorrectEffectflg = 1;
								PlaySoundMem(se_next, DX_PLAYTYPE_BACK);
							}

						}
						break;
					case 31:
						if (gPad.gTrg & PAD_INPUT_2) {
							//テキストが１文字ずつ表示されている間ならすべての文字を出し切る
							if (text_flg == 0) {
								text_flg = 1;
							}
							else {
								savemessage();
								messagecnt++;
								gameCnt = 0;
								if (_jsonData[messagecnt].command != 31)	//カウントを増やした先のコマンドが31以外だった場合の処理
								{
									for (int i = 0; i < JSON_MAX; i++)
									{
										if (_jsonData[messagecnt].command != 1) {
											messagecnt++;
											continue;
										}
										break;
									}
									blackflg = 1;
									flashcnt = 0;
									CorrectEffectnum = 99;
								}
								PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
							}
						}
						break;
					case 5:
						int finishflg = 0;
						//draw移動
						//　キャラクター
						int speed = 12;
						if (_jsonData[messagecnt + 1].drawY > _jsonData[messagecnt].drawY)		//次の座標より今の座標が低いなら
						{
							_jsonData[messagecnt].drawY += speed;
							if (_jsonData[messagecnt + 1].drawY <= _jsonData[messagecnt].drawY)
							{
								_jsonData[messagecnt].drawY = _jsonData[messagecnt + 1].drawY;
							}
						}
						else if (_jsonData[messagecnt + 1].drawY < _jsonData[messagecnt].drawY)	//次の座標より今の座標が高いなら
						{
							_jsonData[messagecnt].drawY -= 4 * speed;
							if (_jsonData[messagecnt + 1].drawY >= _jsonData[messagecnt].drawY)
							{
								_jsonData[messagecnt].drawY = _jsonData[messagecnt + 1].drawY;
							}
						}
						else
						{
							finishflg++;
						}
						// 背景
						if (_jsonData[messagecnt + 1].bgY > _jsonData[messagecnt].bgY)		//次の座標より今の座標が低いなら
						{
							_jsonData[messagecnt].bgY += speed / 3;
							if (_jsonData[messagecnt + 1].bgY <= _jsonData[messagecnt].bgY)
							{
								_jsonData[messagecnt].bgY = _jsonData[messagecnt + 1].bgY;
							}
						}
						else if (_jsonData[messagecnt + 1].bgY < _jsonData[messagecnt].bgY)	//次の座標より今の座標が高いなら
						{
							_jsonData[messagecnt].bgY -= 4 * speed / 3;
							if (_jsonData[messagecnt + 1].bgY >= _jsonData[messagecnt].bgY)
							{
								_jsonData[messagecnt].bgY = _jsonData[messagecnt + 1].bgY;
							}
						}
						else
						{
							finishflg++;
						}

						if (finishflg == 2)
						{
							//次の座標と今の座標が同じなら
							gameCnt = 0;
							messagecnt++;
						}
						break;
					}

					// 会話パート処理
					const char* Message1_String = _jsonData[messagecnt].message1.c_str();
					const char* Message2_String = _jsonData[messagecnt].message2.c_str();

					if (gameCnt == 0) {
						drawCnt1 = 0;
						drawCnt2 = 0;
						text_flg = 0;
						text_alpha = 0;
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
						//すべての文字出力
						drawMessage1 = _jsonData[i].message1;
						drawMessage2 = _jsonData[i].message2;
					}

					//テキスト画像を出現させるか
					if (text_flg == 1) {
						// アルファ値が 0 か 255 になったら変化の方向を反転する
						if (text_alpha < 0 || text_alpha >= 255)
						{
							add = -add;
						}
						// アルファ値を変化
						text_alpha += add * 12;
					}


					//ポップアップのサイズ上昇
					if (popup_size < 0.75) {
						popup_size += 0.07;
					}

					//アニメーション処理
					if (_jsonData[messagecnt].draw.c_str() == Anim0) {
						animflg = 1;
						animnum = 0;
						animcnt++;
					}
					else if (_jsonData[messagecnt].draw.c_str() == Anim1) {
						animflg = 1;
						animnum = 1;
						animcnt++;
					}
					else if (_jsonData[messagecnt].draw.c_str() == Anim2) {
						animflg = 1;
						animnum = 2;
						animcnt++;
					}
					else if (_jsonData[messagecnt].draw.c_str() == Anim3) {
						animflg = 1;
						animnum = 3;
						animcnt++;
					}
					else if (_jsonData[messagecnt].draw.c_str() == Anim4) {
						animflg = 1;
						animnum = 4;
						animcnt++;
					}
					else
					{
						animflg = 0;
						animcnt = 0;
					}

					//画像読み込み
					if (gameCnt == 0) {
						cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
						_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
						if (_jsonData[messagecnt].command != 6) {
							DeleteSoundMem(se_voice);
							se_voice = LoadSoundMem(_jsonData[messagecnt].voice.c_str());
							PlaySoundMem(se_voice, DX_PLAYTYPE_BACK);
						}
					}
					gameCnt++;
					Flash();
				}

				//ブラックアウト処理
				if (blackflg == 1) {
					int blackMax = 120;
					if (flashcnt == 0) {
						//フラッシュ初期化
						flash_alpha = 0;
					}
					else if (flashcnt < blackMax / 2) {
						flash_alpha += 255 * 16 / blackMax;
					}
					else if (flashcnt == blackMax / 2) {
						if (lastchoice_skipflg == 1) { canskip_UI_flg = 1; }
						if (backTalkpartflg == 1) {
							SceneBase* scene = new SceneTalk(savechapter);
							ChangeScene(scene);
						}
						else
						{
							for (int i = 0; i < 6; i++) {
								if (CheckSoundMem(se_choiceBGM[i])) { StopSoundMem(se_choiceBGM[i]); }
							}
							PlaySoundMem(seBGM[0], DX_PLAYTYPE_LOOP);
							ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seBGM[0]);
							messagecnt++;
						}
					}
					else if (flashcnt < blackMax) {
						flash_alpha -= 255 * 2 / blackMax;
					}
					else {
						blackflg = 0;
						flash_alpha = 0;
						gameCnt = 0;
						flashcnt = 999;
					}
					if (flash_alpha < 0) {
						flash_alpha = 0;
					}
					if (flash_alpha > 255) {
						flash_alpha = 255;
					}
					if (flashcnt < 999) {
						flashcnt++;
					}
				}
			}
		}
	}

	//体力ヌルヌル変更
	player.LifeProcess();

	CorrectEffectcnt++;
	// カラーマスクのフェードインアウト処理
	ColorFadeProcess();
}

void SceneLastChoice::Draw()
{
	DrawGraph(0, _jsonData[messagecnt].bgY, _cgBg, FALSE); //背景

	if (CorrectEffectnum != 99) {
		DrawGraph(0, _jsonData[messagecnt].bgY, jisyou_cgBg[(CorrectEffectcnt * CorrectEffectnum) / 3 % 72], FALSE); //背景
	}

	//背景のみを暗くする
	switch (_jsonData[messagecnt].command)
	{
	case 21:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case 22:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case 23:
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
		break;
	}

	//キャラクターの描画
	if (animflg == 1) {
		//アニメーション
		switch (animnum)
		{
		case 0:
			DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_anim[animnum][animcnt / 4 % 24], TRUE);
			break;
		case 1:
			DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_anim[animnum][animcnt / 4 % 24], TRUE);
			break;
		case 2:
			DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_anim[animnum][animcnt / 4 % 24], TRUE);
			break;
		case 3:
			DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_anim[animnum][animcnt / 4 % 24], TRUE);
			break;
		case 4:
			DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_anim[animnum][animcnt / 4 % 24], TRUE);
			break;
		}
	}
	else
	{
		//一枚絵の画像
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
	}

	//アイテムポップアップ
	if (popupflg == 1) {
		DrawRotaGraph(960, 420, popup_size, 0, cg_popup, TRUE);
	}

	const char* Name_String = _jsonData[messagecnt].name.c_str();
	int nameflg = 0;
	if (Name_String[0] != '\0')
	{
		nameflg = 1;
	}
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
	savefontsize = GetFontSize();	//元のフォントサイズを保存
	int choice_w = GetDrawStringWidth(_jsonData[messagecnt].message1.c_str(), strlen((_jsonData[messagecnt].message1.c_str())));	// 描画する文字の横サイズを得る
	//コマンド処理
	switch (_jsonData[messagecnt].command)
	{

	case 0:
	case 21:
	case 22:
	case 23:
	case 24:
	case 31:
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
	case 5:
		DrawPosString(230, 890, 0, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());
		break;
	case 2:
	case 3:
	case 4:
		massagefontsize = 62;		//フォントサイズ
		bt = 20;					//行間
		SetFontSize(massagefontsize);
		DrawFormatString(400, 850, GetColor(255, 255, 255), _jsonData[messagecnt - 1].message1.c_str());							//一行目
		DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), _jsonData[messagecnt - 1].message2.c_str());		//二行目
		//-----------選択肢----------------
		if (choice_w > 100) {
			massagefontsize = 42;		//フォントサイズ
			SetFontSize(massagefontsize);
			DrawGraph(20, 604, cgchoice[1 - selectcnt], TRUE);
			DrawGraph(937, 604, cgchoice[1 * selectcnt], TRUE);
			DrawPosString(20 + 483, 604 + 66, 0, GetColor(255, 255, 255), _jsonData[messagecnt].message1.c_str());
			DrawPosString(937 + 483, 604 + 66, 0, GetColor(255, 255, 255), _jsonData[messagecnt + 1].message1.c_str());
		}
		else
		{
			massagefontsize = 62;		//フォントサイズ
			SetFontSize(massagefontsize);
			DrawGraph(20, 604, cgchoice[1 - selectcnt], TRUE);
			DrawGraph(937, 604, cgchoice[1 * selectcnt], TRUE);
			DrawPosString(20 + 483, 604 + 57, 0, GetColor(255, 255, 255), _jsonData[messagecnt].message1.c_str());
			DrawPosString(937 + 483, 604 + 57, 0, GetColor(255, 255, 255), _jsonData[messagecnt + 1].message1.c_str());
		}
		break;
	}

	SetFontSize(savefontsize);	//フォントサイズを戻す

	//ボタン系UI
	if (canskip_UI_flg == 1) {
		DrawGraph(1434, 792, cg_UI_talk[1], TRUE);
	}
	else
	{
		DrawGraph(1556, 792, cg_UI_talk[0], TRUE);
	}


	//フラッシュ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flash_alpha);
	if (blackflg != 1) {
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 200), TRUE);
	}
	else
	{
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//ログ描画
	if (logflg == 1)
	{
		LogDraw();
	}

	// カラーマスクのフェードインアウト描画
	ColorFadeDraw();
}
