#include	"scenetalk.h"
#include	"DxLib.h"
#include	"mymath.h"
#include	"data.h"
#include	"Player.h"
#include	"gamemain.h"
#include	"scenelook.h"
#include	"SceneCredit.h"
#include	"scenegamemain.h"
#include	"SceneGameover.h"
#include	"scenegametitle.h"
#include	"SceneLastChoice.h"
#include	"scenegametutorial.h"
#include	"utf8sjis.h"	// jsonの日本語文字を使うために必要
#include	<cassert>
#include	<string>

SceneTalk::SceneTalk(int chapter)
{
	savechapter = chapter;

	cgtext = LoadGraph("res/wait_cursor.png");
	cgchoice[0] = LoadGraph("res/choice/choice_inside.png");
	cgchoice[1] = LoadGraph("res/choice/choice_outside.png");
	cg_popup = LoadGraph("");
	cg_UI_talk = LoadGraph("res/UI/UI_kaiwa.png");

	// jsonファイルの読み込み
	std::ifstream file("res/jsonfile/beta.json");
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

	// 画像ファイル読み込み
	int n;

	//アニメーション読み込み

	popupflg = 0;
	shakeflg = 0;
	animcnt = 0;
	animflg = 0;
	animnum = -1;

	flash_alpha = 0;
	effectcnt = 0;
	flashcnt = 0;
	gameCnt = 0;
	add = -1;
	text_alpha = 0;
	popup_size = 0.0f;
	text_flg = 0;
	step = 0;
	selectflg = 0;
	logflg = 0;
	//会話パートに戻るたびに体力回復
	gHP += RECOVERY_HP;
	player.CheckPlayerLife();
	
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
	for (i = 0; i < JSON_MAX; i++) {
		if (_jsonData[i].command == savechapter)
		{
			messagecnt = i + 1;
			break;
		}
	}

	//BGM・se
	se_next = LoadSoundMem("res/se/se_seikai.mp3");
	se_choice = LoadSoundMem("res/se/cho.mp3");
	se_selectchoice = LoadSoundMem("res/se/se_cursor_move.mp3");
	se_voice = 0;
	PlaySoundMem(seBGM[0], DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seBGM[0]);
}

SceneTalk::~SceneTalk()
{
	for (int i = 0; i < 5; i++) {
		if (CheckSoundMem(seBGM[i])) { StopSoundMem(seBGM[i]); }
	}
	DeleteSoundMem(se_next);
	DeleteSoundMem(se_choice);
	DeleteSoundMem(se_selectchoice);
	DeleteSoundMem(se_voice);
	DeleteGraph(_cgBg);
	DeleteGraph(cgtext);
	DeleteGraph(cg_popup);
	DeleteGraph(cgchoice[0]);
	DeleteGraph(cgchoice[1]);
}

void SceneTalk::savemessage()
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

void SceneTalk::Input()
{

}

void SceneTalk::Process()
{
	// 開発用
	
	/*if (gPad.gTrg & PAD_INPUT_1) {
		SceneBase* scene = new SceneGameMain(1);
		ChangeScene(scene);
	}*/
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
			else
			{
				for (int i = 0; i < 5; i++) {
					if (CheckSoundMem(seBGM[i])) { StopSoundMem(seBGM[i]); }
				}
			}
			messagecnt++;
			gameCnt = 0;
			break;
		case 0:
			// 21:背景を少し暗く 22:背景をさらに暗く 23:背景を暗く
		case 21:
		case 22:
		case 23:
			if (gPad.gTrg & PAD_INPUT_2) {
				//テキストが１文字ずつ表示されている間ならすべての文字を出し切る
				if (text_flg == 0) {
					text_flg = 1;
				}
				else
				{
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
					//テキストが１文字ずつ表示されている間ならすべての文字を出し切る
					if (text_flg == 0) {
						text_flg = 1;
					}
					else
					{
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
			}
			flashcnt++;
			break;
			//セリフ飛ばし無効
		case 7:
			if (gPad.gTrg & PAD_INPUT_2 && !CheckSoundMem(se_voice)) {
				//テキストが１文字ずつ表示されている間ならすべての文字を出し切る
				if (text_flg == 0) {
					text_flg = 1;
				}
				else
				{
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
			// 61~：偽証議論
		case 61:
			if (effectcnt / DRAW_EFFECT_COUNT == 44) {
				SceneBase* scene = new SceneGameTutorial();
				ChangeScene(scene);
			}
			else {
				effectcnt++;
			}
			break;
		case 62:
		case 63:
		case 64:
		case 65:
		case 66:
			if (effectcnt / DRAW_EFFECT_COUNT == 44) {
				SceneBase* scene = new SceneGameMain(_jsonData[messagecnt].command - 61);
				ChangeScene(scene);
			}
			else {
				effectcnt++;
			}
			break;
			// 51~：睨むパート
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
			switch (step)
			{
			case 0:
				// フェードアウト開始
				ColorMask(0, 0, 0, 0);
				ColorFadeOut(0, 0, 0, 60);
				step++;
				break;
			case 1:
				if (IsColorFade() == 0)
				{
					// フェードアウト終了
					SceneBase* scene = new SceneLook(_jsonData[messagecnt].command - 51);
					ChangeScene(scene);
				}
				break;
			}

			// カラーマスクのフェードインアウト処理
			ColorFadeProcess();
			break;
			// 71：タイトルへ
		case 71:
			if (1) {
				SceneBase* scene = new SceneCredit();
				ChangeScene(scene);
			}
			break;
		case 72:
			if (effectcnt / DRAW_EFFECT_COUNT == 44) {
				SceneBase* scene = new SceneLastChoice(72);
				ChangeScene(scene);
			}
			else {
				effectcnt++;
			}
			break;
		case 2:	//正解の処理
		case 31:	//不正解1の処理
		case 32:	//不正解2の処理
		case 33:	//不正解3の処理
		case 34:	//不正解4の処理
			//選択ボタン
			if (selectflg == 0) {
				if (gPad.gTrg & PAD_INPUT_DOWN || gPad.gTrg & PAD_INPUT_UP) {
					selectflg = 1;
					PlaySoundMem(se_selectchoice, DX_PLAYTYPE_BACK);
				}
			}
			else
			{
				if (gPad.gTrg & PAD_INPUT_DOWN) {
					selectcnt++;
					if (_jsonData[messagecnt + selectcnt].command != 2 && _jsonData[messagecnt + selectcnt].command != 31
						&& _jsonData[messagecnt + selectcnt].command != 32 && _jsonData[messagecnt + selectcnt].command != 33
						&& _jsonData[messagecnt + selectcnt].command != 34) {
						selectcnt--;
					}
					else
					{
						PlaySoundMem(se_selectchoice, DX_PLAYTYPE_BACK);
					}
				}
				if (gPad.gTrg & PAD_INPUT_UP) {
					selectcnt--;
					if (_jsonData[messagecnt + selectcnt].command != 2 && _jsonData[messagecnt + selectcnt].command != 31
						&& _jsonData[messagecnt + selectcnt].command != 32 && _jsonData[messagecnt + selectcnt].command != 33
						&& _jsonData[messagecnt + selectcnt].command != 34) {
						selectcnt++;
					}
					else
					{
						PlaySoundMem(se_selectchoice, DX_PLAYTYPE_BACK);
					}
				}

				if (gPad.gTrg & PAD_INPUT_2) {
					selectflg = 0;
					//選ばれた選択肢が正解
					if (_jsonData[messagecnt + selectcnt].command == 2) {
						gameCnt = 0;
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
					else {
						PlaySoundMem(seHazure, DX_PLAYTYPE_BACK, TRUE);
						//選ばれた選択肢が不正解1
						if (_jsonData[messagecnt + selectcnt].command == 31) {
							gameCnt = 0;
							for (int i = 0; i < JSON_MAX; i++)
							{
								if (_jsonData[messagecnt].command != 41) {
									messagecnt++;
									gameCnt = 0;
									continue;
								}
								break;
							}
						}
						//選ばれた選択肢が不正解2
						if (_jsonData[messagecnt + selectcnt].command == 32) {
							gameCnt = 0;
							for (int i = 0; i < JSON_MAX; i++)
							{
								if (_jsonData[messagecnt].command != 42) {
									messagecnt++;
									gameCnt = 0;
									continue;
								}
								break;
							}
						}
						//選ばれた選択肢が不正解3
						if (_jsonData[messagecnt + selectcnt].command == 33) {
							gameCnt = 0;
							for (int i = 0; i < JSON_MAX; i++)
							{
								if (_jsonData[messagecnt].command != 43) {
									messagecnt++;
									gameCnt = 0;
									continue;
								}
								break;
							}
						}
						//選ばれた選択肢が不正解4
						if (_jsonData[messagecnt + selectcnt].command == 34) {
							gameCnt = 0;
							for (int i = 0; i < JSON_MAX; i++)
							{
								if (_jsonData[messagecnt].command != 44) {
									messagecnt++;
									gameCnt = 0;
									continue;
								}
								break;
							}
						}
					}
				}
			}
			break;
			// 41~44:不正解時の発言
		case 41:
		case 42:
		case 43:
		case 44:
			if (1) {
				int save_messagecnt = _jsonData[messagecnt].command;
				if (gEffect.shakecnt == 0 && shakeflg == 1) {
					messagecnt--;		//カウントを戻す
					for (int i = 0; i < JSON_MAX; i++)	//コマンド０になるまでカウントを減らし続ける
					{
						if (_jsonData[messagecnt].command == 0 || _jsonData[messagecnt].command == 21) {
							break;
						}
						messagecnt--;
					}
					shakeflg = 0;
				}
				else if (gPad.gTrg & PAD_INPUT_2 && shakeflg != 1) {
					//テキストが１文字ずつ表示されている間ならすべての文字を出し切る
					if (text_flg == 0) {
						text_flg = 1;
					}
					else
					{
						savemessage();
						int pre_messagecnt = messagecnt;
						pre_messagecnt += 1;
						if (_jsonData[pre_messagecnt].command != save_messagecnt)	//カウントを増やした先のコマンドが41以外だった場合の処理
						{
							PlaySoundMem(seDamage, DX_PLAYTYPE_BACK);
							gHP -= TALK_MISS_HP;
							gEffect.shakecnt = 20;
							gEffect.shakespead = 10;
							shakeflg = 1;
						}
						else
						{
							messagecnt++;
							gameCnt = 0;
							PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
						}
					}
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
			//カウント系の初期化
			drawCnt1 = 0;
			drawCnt2 = 0;
			text_flg = 0;
			text_alpha = 0;

			//画像・音声読み込み
			cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
			_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
			//BGMは読み込まない
			if (_jsonData[messagecnt].command != 6) {
				DeleteSoundMem(se_voice);
				se_voice = LoadSoundMem(_jsonData[messagecnt].voice.c_str());
				PlaySoundMem(se_voice, DX_PLAYTYPE_BACK);
			}
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
				if (_jsonData[messagecnt].command != 7 || !CheckSoundMem(se_voice)) { text_flg = 1; }
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
		float pop_maxsize = 1.0;
		if (popup_size < pop_maxsize) {
			popup_size += 0.07;
			if (popup_size > pop_maxsize) {
				popup_size = pop_maxsize;
			}
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

		// 画面揺らし関連
		gEffect.ProcessShake();

		gameCnt++;

		//体力ヌルヌル変更
		player.LifeProcess();

		//ゲームオーバー確認
		if (gHP <= 0) {
			//ゲームオーバー処理
			SceneBase* scene = new SceneGameover(savechapter);
			ChangeScene(scene);
		}
	}
}

void SceneTalk::Draw()
{
	DrawGraph(gEffect.shakespead * gEffect.shake, _jsonData[messagecnt].bgY, _cgBg, FALSE); //背景

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

	//選択肢の間暗く
	switch (_jsonData[messagecnt].command)
	{
	case 2:
	case 31:
	case 32:
	case 33:
	case 34:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
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

	int choice_num = 0;
	//コマンド処理
	switch (_jsonData[messagecnt].command)
	{

	case 0:
	case 7:
	case 21:
	case 22:
	case 23:
	case 24:
	case 41:
	case 42:
	case 43:
	case 44:
		//-----------メッセージ読み込み----------------
		massagefontsize = 62;		//フォントサイズ
		bt = 20;					//行間

		namefontsize = 48;
		SetFontSize(namefontsize);
		//DrawFormatString(165, 860, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());			//名前表示
		DrawPosString(230, 890, 0, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());
		SetFontSize(massagefontsize);

		DrawFormatString(400, 850, GetColor(255, 255, 255), drawMessage1.c_str());							//一行目

		DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), drawMessage2.c_str());	//二行目
		break;
	case 5:
		namefontsize = 48;
		SetFontSize(namefontsize);
		DrawPosString(230, 890, 0, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());
		break;
	case 2:
	case 31:
	case 32:
	case 33:
	case 34:
		//-----------選択肢----------------
		massagefontsize = 62;		//フォントサイズ
		bt = 20;					//行間
		SetFontSize(massagefontsize);
		DrawFormatString(400, 850, GetColor(255, 255, 255), _jsonData[messagecnt - 1].message1.c_str());							//一行目
		DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), _jsonData[messagecnt - 1].message2.c_str());		//二行目
		for (int i = 0; i < CHOICE_MAX; i++)
		{
			if (_jsonData[messagecnt + i].command != 2 && _jsonData[messagecnt + i].command != 31
				&& _jsonData[messagecnt + i].command != 32 && _jsonData[messagecnt + i].command != 33
				&& _jsonData[messagecnt + i].command != 34) {
				break;
			}
			choice_num++;
		}
		switch (choice_num)
		{
		case 2:
			for (int i = 0; i < choice_num; i++)
			{
				DrawGraph(537, 124 + 65 + 129 + i * 129, cgchoice[0], TRUE);
				DrawPosString(SCREEN_W / 2, 132 + 65 + 129 + i * 129, 0, GetColor(0, 0, 0), _jsonData[messagecnt + i].message1.c_str());
			}
			if (selectflg == 1) { DrawGraph(524, 110 + 65 + 129 + selectcnt * 129, cgchoice[1], TRUE); }
			break;
		case 3:
			for (int i = 0; i < choice_num; i++)
			{
				DrawGraph(537, 124 + 129 + i * 129, cgchoice[0], TRUE);
				DrawPosString(SCREEN_W / 2, 132 + 129 + i * 129, 0, GetColor(0, 0, 0), _jsonData[messagecnt + i].message1.c_str());
			}
			if (selectflg == 1) { DrawGraph(524, 110 + 129 + selectcnt * 129, cgchoice[1], TRUE); }
			break;
		case 4:
			for (int i = 0; i < choice_num; i++)
			{
				DrawGraph(537, 124 + 65 + i * 129, cgchoice[0], TRUE);
				DrawPosString(SCREEN_W / 2, 132 + 65 + i * 129, 0, GetColor(0, 0, 0), _jsonData[messagecnt + i].message1.c_str());
			}
			if (selectflg == 1) { DrawGraph(524, 110 + 65 + selectcnt * 129, cgchoice[1], TRUE); }
			break;
		case 5:
			for (int i = 0; i < choice_num; i++)
			{
				DrawGraph(537, 124 + i * 129, cgchoice[0], TRUE);
				DrawPosString(SCREEN_W / 2, 132 + i * 129, 0, GetColor(0, 0, 0), _jsonData[messagecnt + i].message1.c_str());
			}
			if (selectflg == 1) { DrawGraph(524, 110 + selectcnt * 129, cgchoice[1], TRUE); }
			break;
		}
		break;
		// 睨むパート
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
		// カラーマスクのフェードインアウト描画
		ColorFadeDraw();
		break;
	}

	DrawGraph(1556, 792, cg_UI_talk, TRUE);
	SetFontSize(savefontsize);	//フォントサイズを戻す

	//フラッシュ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flash_alpha);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//エフェクト
	DrawGraph(0, 0, break_efffect[effectcnt / DRAW_EFFECT_COUNT], TRUE);

	//ログ描画
	if (logflg == 1)
	{
		LogDraw();
	}
}
	