#include	"scenegameover.h"
#include	"scenetalk.h"
#include	"scenegametitle.h"
#include	"DxLib.h"
#include	"mymath.h"
#include	"gamemain.h"
#include	"scenelook.h"
#include	"scenegamemain.h"
#include	"scenegametutorial.h"
#include	"utf8sjis.h"	// jsonの日本語文字を使うために必要
#include	<cassert>
#include	<string>

SceneGameover::SceneGameover(int chapter)
{
	savechapter = chapter;
	_cgBg[0] = LoadGraph("res/gameover/CG_jisyou.jpg");
	_cgBg[1] = LoadGraph("res/gameover/CG_gameover.png");
	cgarrow = LoadGraph("res/gameover/gameover_arrow.png");
	cgtext = LoadGraph("res/wait_cursor.png");
	
	// jsonファイルの読み込み
	std::ifstream file("res/jsonfile/gameover.json");
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
		//json[i].at("voice").get_to(_jsonData[i].voice);

		// jsonの文字列を、UTF-8からShift-JISに変換
		_jsonData[i].message1 = ConvUTF8toSJIS(_jsonData[i].message1);
		_jsonData[i].message2 = ConvUTF8toSJIS(_jsonData[i].message2);
		_jsonData[i].draw = ConvUTF8toSJIS(_jsonData[i].draw);
		_jsonData[i].name = ConvUTF8toSJIS(_jsonData[i].name);
		//_jsonData[i].voice = ConvUTF8toSJIS(_jsonData[i].voice);
		i++;
	}

	// 例：画像ファイル読み込み
	int n;

	effectcnt = 0;
	gameoverflg = 0;
	gameCnt = 0;
	add = -1;
	text_alpha = 255;
	text_flg = 0;
	selectcnt = 1;

	//メッセージカウント読み込み
	messagecnt = 0;
	int GetScenario = 51;		//仮置き。引数で渡してもらう
	for (i = 0; i < JSON_MAX; i++) {
		if (_jsonData[i].command == GetScenario)
		{
			messagecnt = i + 1;
			break;
		}
	}

	//BGM・se
	se_next = LoadSoundMem("res/se/block_high.mp3");
	se_choice = LoadSoundMem("res/se/cho.mp3");
	
	ChangeVolumeSoundMem(255 * BGM_VOLUME / 100, seBGM[1]);
	PlaySoundMem(seGameOverBGM, DX_PLAYTYPE_LOOP);
}

SceneGameover::~SceneGameover()
{
	if (CheckSoundMem(seGameOverBGM)) { StopSoundMem(seGameOverBGM); }

	DeleteSoundMem(se_next); 
	DeleteSoundMem(se_choice); 
	DeleteGraph(_cgBg[0]);
	DeleteGraph(_cgBg[1]);
	DeleteGraph(cgtext);
	DeleteGraph(cgarrow);
	int n;
	for (n = 0; n < 45; n++) {
		DeleteGraph(break_efffect[n]);
	}

	gHP = MAX_HP;		//体力を全回復
}




void SceneGameover::Input()
{

}

void SceneGameover::Process()
{

	// 開発用
	/*
	if (gPad.gTrg & PAD_INPUT_1) {
		SceneBase* scene = new SceneGameMain(0);
		ChangeScene(scene);
	}*/

	//----コマンド別処理----
	int save_cmd;
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
					gameCnt = 0;
					text_alpha = 255;
					selectcnt = 1;
					PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
				}
			}
		case 21:
		case 22:
		case 23:
			break;
		case 6:
			messagecnt++;		//messagecntを増加する
			gameoverflg = 1;
			gameCnt = 0;
			break;
		case 61:
			if (1) {
				SceneBase* scene = new SceneGameMain(0);
				ChangeScene(scene);
			}
			break;
			//	case 51:
			//		SceneBase* scene = new SceneLook();
			//		ChangeScene(scene);
			//		break;
			//	case 52:
			//		SceneBase* scene = new SceneLook();
			//		ChangeScene(scene);
			//		break;
			//	case 53:
			//		SceneBase * scene = new SceneLook();
			//		ChangeScene(scene);
			//		break;
			//	case 54:
			//		SceneBase * scene = new SceneLook(4);
			//		ChangeScene(scene);
			//		break;
		case 2:	//選択「タイトルに戻る」の処理
		case 3:	//選択「リトライ」の処理
		//つながっているコマンドをすべて表示する
			save_cmd = messagecnt;
			for (int i = 0; i < 5; i++)
			{
				if (_jsonData[messagecnt].command != 2 && _jsonData[messagecnt].command != 3) 
				{
					break;
				}
				save_messagecnt[i] = messagecnt;
				messagecnt++;
			}
			messagecnt = save_cmd;

			//選択ボタン
			if (gPad.gTrg & PAD_INPUT_RIGHT) {
				PlaySoundMem(seCursor, DX_PLAYTYPE_BACK);
				selectcnt++;
				if (_jsonData[messagecnt + selectcnt].command != 2 && _jsonData[messagecnt + selectcnt].command != 3) 
				{
					selectcnt--;
				}
			}
			if (gPad.gTrg & PAD_INPUT_LEFT) {
				PlaySoundMem(seCursor, DX_PLAYTYPE_BACK);
				selectcnt--;
				if (_jsonData[messagecnt + selectcnt].command != 2 && _jsonData[messagecnt + selectcnt].command != 3) 
				{
					selectcnt++;
				}
			}

			if (gPad.gTrg & PAD_INPUT_2) {
				if (CheckSoundMem(seBGM[1])) { StopSoundMem(seBGM[1]); }
				PlaySoundMem(seDecide, DX_PLAYTYPE_BACK);
				//選ばれた選択肢がタイトル
				if (_jsonData[messagecnt + selectcnt].command == 2) {
					SceneBase* scene = new SceneGameTitle();
					ChangeScene(scene);
				}
				//選ばれた選択肢がリトライ
				if (_jsonData[messagecnt + selectcnt].command == 3) {
					if (savechapter == 300) {
						//チュートリアルパートへ
						SceneBase* scene = new SceneGameTutorial();
						ChangeScene(scene);

					}
					else if (savechapter >= 200) {
						//偽証議論パートへ
						savechapter -= 200;
						SceneBase* scene = new SceneGameMain(savechapter);
						ChangeScene(scene);

					}
					else if (savechapter >= 100) {
						//睨むパートへ
						savechapter -= 100;
						SceneBase* scene = new SceneLook(savechapter);
						ChangeScene(scene);
					}
					else
					{
						//会話パートへ
						SceneBase* scene = new SceneTalk(savechapter);
						ChangeScene(scene);
					}
				}
			}
			break;
		case 5:
			//draw移動
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
	gameCnt++;
}

void SceneGameover::Draw()
{
	DrawGraph(0, 0, _cgBg[0], FALSE); //背景

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "SceneGameTalk!!");

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


	LoadGraphScreen(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, _jsonData[messagecnt].draw.c_str(), TRUE); //キャラクター

	const char* Name_String = _jsonData[messagecnt].name.c_str();
	int nameflg = 0;
	if (Name_String[messagecnt] != '\0')
	{
		nameflg = 1;
	}
	ui.DrawTalkUI(gHP, nameflg); //UI作成

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, text_alpha);
	DrawGraph(1790, 945, cgtext, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (gameoverflg == 1) {
		DrawGraph(0, 0, _cgBg[1], FALSE); //背景
	}
	//-----------メッセージ読み込み----------------

	int massagefontsize;	//フォントサイズ
	int bt;					//行間
	int namefontsize;
	int savefontsize;
	savefontsize = GetFontSize();
	//コマンド処理
	switch (_jsonData[messagecnt].command)
	{
	case 0:
	case 21:
	case 22:
	case 23:
	case 24:
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
		//-----------メッセージ読み込み----------------
		break;
	case 2:	
	case 3:	
		DrawGraph(370 + selectcnt * 875, 725, cgarrow, TRUE);
		break;
	}
	SetFontSize(savefontsize);	//フォントサイズを戻す
	//エフェクト
	DrawGraph(0, 0, break_efffect[effectcnt / 2], TRUE);
}
