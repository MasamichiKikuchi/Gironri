#include	"scenegameover.h"
#include	"scenetalk.h"
#include	"scenegametitle.h"
#include	"DxLib.h"
#include	"mymath.h"
#include	"gamemain.h"
#include	"scenelook.h"
#include	"scenegamemain.h"
#include	"scenegametutorial.h"
#include	"utf8sjis.h"	// json�̓��{�ꕶ�����g�����߂ɕK�v
#include	<cassert>
#include	<string>

SceneGameover::SceneGameover(int chapter)
{
	savechapter = chapter;
	_cgBg[0] = LoadGraph("res/gameover/CG_jisyou.jpg");
	_cgBg[1] = LoadGraph("res/gameover/CG_gameover.png");
	cgarrow = LoadGraph("res/gameover/gameover_arrow.png");
	cgtext = LoadGraph("res/wait_cursor.png");
	
	// json�t�@�C���̓ǂݍ���
	std::ifstream file("res/jsonfile/gameover.json");
	nlohmann::json json;
	file >> json;
	int i = 0;
	// �f�[�^��ǂݍ���
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

		// json�̕�������AUTF-8����Shift-JIS�ɕϊ�
		_jsonData[i].message1 = ConvUTF8toSJIS(_jsonData[i].message1);
		_jsonData[i].message2 = ConvUTF8toSJIS(_jsonData[i].message2);
		_jsonData[i].draw = ConvUTF8toSJIS(_jsonData[i].draw);
		_jsonData[i].name = ConvUTF8toSJIS(_jsonData[i].name);
		//_jsonData[i].voice = ConvUTF8toSJIS(_jsonData[i].voice);
		i++;
	}

	// ��F�摜�t�@�C���ǂݍ���
	int n;

	effectcnt = 0;
	gameoverflg = 0;
	gameCnt = 0;
	add = -1;
	text_alpha = 255;
	text_flg = 0;
	selectcnt = 1;

	//���b�Z�[�W�J�E���g�ǂݍ���
	messagecnt = 0;
	int GetScenario = 51;		//���u���B�����œn���Ă��炤
	for (i = 0; i < JSON_MAX; i++) {
		if (_jsonData[i].command == GetScenario)
		{
			messagecnt = i + 1;
			break;
		}
	}

	//BGM�Ese
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

	gHP = MAX_HP;		//�̗͂�S��
}




void SceneGameover::Input()
{

}

void SceneGameover::Process()
{

	// �J���p
	/*
	if (gPad.gTrg & PAD_INPUT_1) {
		SceneBase* scene = new SceneGameMain(0);
		ChangeScene(scene);
	}*/

	//----�R�}���h�ʏ���----
	int save_cmd;
		switch (_jsonData[messagecnt].command)
		{
		case 0:
			if (gPad.gTrg & PAD_INPUT_2) {
				//�e�L�X�g���P�������\������Ă���ԂȂ炷�ׂĂ̕������o���؂�
				if (text_flg == 0) {
					text_flg = 1;
				}
				else
				{
					//�ʏ폈��
					messagecnt++;		//messagecnt�𑝉�����
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
			messagecnt++;		//messagecnt�𑝉�����
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
		case 2:	//�I���u�^�C�g���ɖ߂�v�̏���
		case 3:	//�I���u���g���C�v�̏���
		//�Ȃ����Ă���R�}���h�����ׂĕ\������
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

			//�I���{�^��
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
				//�I�΂ꂽ�I�������^�C�g��
				if (_jsonData[messagecnt + selectcnt].command == 2) {
					SceneBase* scene = new SceneGameTitle();
					ChangeScene(scene);
				}
				//�I�΂ꂽ�I���������g���C
				if (_jsonData[messagecnt + selectcnt].command == 3) {
					if (savechapter == 300) {
						//�`���[�g���A���p�[�g��
						SceneBase* scene = new SceneGameTutorial();
						ChangeScene(scene);

					}
					else if (savechapter >= 200) {
						//�U�؋c�_�p�[�g��
						savechapter -= 200;
						SceneBase* scene = new SceneGameMain(savechapter);
						ChangeScene(scene);

					}
					else if (savechapter >= 100) {
						//�ɂރp�[�g��
						savechapter -= 100;
						SceneBase* scene = new SceneLook(savechapter);
						ChangeScene(scene);
					}
					else
					{
						//��b�p�[�g��
						SceneBase* scene = new SceneTalk(savechapter);
						ChangeScene(scene);
					}
				}
			}
			break;
		case 5:
			//draw�ړ�
			int speed = 12;
			if (_jsonData[messagecnt + 1].drawY > _jsonData[messagecnt].drawY)		//���̍��W��荡�̍��W���Ⴂ�Ȃ�
			{
				_jsonData[messagecnt].drawY += speed;
				if (_jsonData[messagecnt + 1].drawY <= _jsonData[messagecnt].drawY)
				{
					_jsonData[messagecnt].drawY = _jsonData[messagecnt + 1].drawY;
				}
			}
			else if (_jsonData[messagecnt + 1].drawY < _jsonData[messagecnt].drawY)	//���̍��W��荡�̍��W�������Ȃ�
			{
				_jsonData[messagecnt].drawY -= 4 * speed;
				if (_jsonData[messagecnt + 1].drawY >= _jsonData[messagecnt].drawY)
				{
					_jsonData[messagecnt].drawY = _jsonData[messagecnt + 1].drawY;
				}
			}
			else
			{
				//���̍��W�ƍ��̍��W�������Ȃ�
				gameCnt = 0;
				messagecnt++;
			}
			break;
	}


	// ��b�p�[�g����
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
			drawCnt1 += CharBytes;		// �`��J�E���^
		}
		else if (Message2_String[drawCnt2] != '\0')
		{
			CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &Message2_String[drawCnt2]);
			drawCnt2 += CharBytes;		// �`��J�E���^
		}
		else
		{
			text_flg = 1;
		}
	}

	if (text_flg == 0) {
		//drawcnt���̕����o��
		drawMessage1 = _jsonData[i].message1.substr(0, drawCnt1);
		drawMessage2 = _jsonData[i].message2.substr(0, drawCnt2);
	}
	else
	{
		drawMessage1 = _jsonData[i].message1;
		drawMessage2 = _jsonData[i].message2;
	}
	
	//�e�L�X�g�摜���o�������邩
	if (text_flg == 1) {
		// �A���t�@�l�� 0 �� 255 �ɂȂ�����ω��̕����𔽓]����
		if (text_alpha < 0 || text_alpha >= 255)
		{
			add = -add;
		}
		// �A���t�@�l��ω�
		text_alpha += add * 12;
	}
	gameCnt++;
}

void SceneGameover::Draw()
{
	DrawGraph(0, 0, _cgBg[0], FALSE); //�w�i

	//DrawFormatString(100, 100, GetColor(255, 255, 255), "SceneGameTalk!!");

	//�w�i�݂̂��Â�����
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


	LoadGraphScreen(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, _jsonData[messagecnt].draw.c_str(), TRUE); //�L�����N�^�[

	const char* Name_String = _jsonData[messagecnt].name.c_str();
	int nameflg = 0;
	if (Name_String[messagecnt] != '\0')
	{
		nameflg = 1;
	}
	ui.DrawTalkUI(gHP, nameflg); //UI�쐬

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, text_alpha);
	DrawGraph(1790, 945, cgtext, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (gameoverflg == 1) {
		DrawGraph(0, 0, _cgBg[1], FALSE); //�w�i
	}
	//-----------���b�Z�[�W�ǂݍ���----------------

	int massagefontsize;	//�t�H���g�T�C�Y
	int bt;					//�s��
	int namefontsize;
	int savefontsize;
	savefontsize = GetFontSize();
	//�R�}���h����
	switch (_jsonData[messagecnt].command)
	{
	case 0:
	case 21:
	case 22:
	case 23:
	case 24:
		//-----------���b�Z�[�W�ǂݍ���----------------
		massagefontsize = 62;		//�t�H���g�T�C�Y
		bt = 20;					//�s��

		namefontsize = 48;
		SetFontSize(namefontsize);
		//DrawFormatString(165, 860, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());			//���O�\��
		DrawPosString(230, 890, 0, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());
		SetFontSize(massagefontsize);

		DrawFormatString(400, 850, GetColor(255, 255, 255), drawMessage1.c_str());							//��s��

		DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), drawMessage2.c_str());	//��s��
		//-----------���b�Z�[�W�ǂݍ���----------------
		break;
	case 2:	
	case 3:	
		DrawGraph(370 + selectcnt * 875, 725, cgarrow, TRUE);
		break;
	}
	SetFontSize(savefontsize);	//�t�H���g�T�C�Y��߂�
	//�G�t�F�N�g
	DrawGraph(0, 0, break_efffect[effectcnt / 2], TRUE);
}
