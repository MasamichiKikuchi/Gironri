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
#include	"utf8sjis.h"	// json�̓��{�ꕶ�����g�����߂ɕK�v
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

	// json�t�@�C���̓ǂݍ���
	std::ifstream file("res/jsonfile/beta.json");
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
		jsonfile.at("voice").get_to(_jsonData[i].voice);
		jsonfile.at("bgY").get_to(_jsonData[i].bgY);
		jsonfile.at("bg").get_to(_jsonData[i].bg);

		// json�̕�������AUTF-8����Shift-JIS�ɕϊ�
		_jsonData[i].message1 = ConvUTF8toSJIS(_jsonData[i].message1);
		_jsonData[i].message2 = ConvUTF8toSJIS(_jsonData[i].message2);
		_jsonData[i].draw = ConvUTF8toSJIS(_jsonData[i].draw);
		_jsonData[i].name = ConvUTF8toSJIS(_jsonData[i].name);
		_jsonData[i].voice = ConvUTF8toSJIS(_jsonData[i].voice);
		_jsonData[i].bg = ConvUTF8toSJIS(_jsonData[i].bg);
		i++;
	}

	// �摜�t�@�C���ǂݍ���
	int n;

	//�A�j���[�V�����ǂݍ���

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
	//��b�p�[�g�ɖ߂邽�тɑ̗͉�
	gHP += RECOVERY_HP;
	player.CheckPlayerLife();
	
	//�A�j���[�V������
	Anim0 = "AnimY";
	Anim1 = "AnimB";
	Anim2 = "AnimG";
	Anim3 = "AnimR";
	Anim4 = "AnimP";

	BGM0 = "BGM0";
	BGM1 = "BGM1";
	BGM2 = "BGM2";
	BGM3 = "BGM3";

	// ���b�Z�[�W�J�E���g�ǂݍ���
	messagecnt = 0;
	for (i = 0; i < JSON_MAX; i++) {
		if (_jsonData[i].command == savechapter)
		{
			messagecnt = i + 1;
			break;
		}
	}

	//BGM�Ese
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
	// �J���p
	
	/*if (gPad.gTrg & PAD_INPUT_1) {
		SceneBase* scene = new SceneGameMain(1);
		ChangeScene(scene);
	}*/
	//���O�����ύX
	if (gPad.gTrg & PAD_INPUT_3) {
		LogChange();
	}
	if (logflg == 1)
	{
		LogProcess();
	}
	else
	{
		//----�R�}���h�ʏ���----
		int save_cmd;
		switch (_jsonData[messagecnt].command)
		{
		case 6:
			//BGM����
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
			// 21:�w�i�������Â� 22:�w�i������ɈÂ� 23:�w�i���Â�
		case 21:
		case 22:
		case 23:
			if (gPad.gTrg & PAD_INPUT_2) {
				//�e�L�X�g���P�������\������Ă���ԂȂ炷�ׂĂ̕������o���؂�
				if (text_flg == 0) {
					text_flg = 1;
				}
				else
				{
					savemessage();
					//����popup�̏���
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
					//�ʏ폈��
					else
					{
						messagecnt++;		//messagecnt�𑝉�����
					}
					//�J�E���g�n�̃��Z�b�g
					gameCnt = 0;
					selectcnt = 0;
					PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
				}
			}
			break;
			// �t���b�V��
		case 24:
			if (flashcnt == 0) {
				//�t���b�V��������
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
					//�e�L�X�g���P�������\������Ă���ԂȂ炷�ׂĂ̕������o���؂�
					if (text_flg == 0) {
						text_flg = 1;
					}
					else
					{
						savemessage();
						//����popup�̏���
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
						//�ʏ폈��
						else
						{
							messagecnt++;		//messagecnt�𑝉�����
						}
						//�J�E���g�n�̃��Z�b�g
						gameCnt = 0;
						selectcnt = 0;
						PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
					}
				}
			}
			flashcnt++;
			break;
			//�Z���t��΂�����
		case 7:
			if (gPad.gTrg & PAD_INPUT_2 && !CheckSoundMem(se_voice)) {
				//�e�L�X�g���P�������\������Ă���ԂȂ炷�ׂĂ̕������o���؂�
				if (text_flg == 0) {
					text_flg = 1;
				}
				else
				{
					savemessage();
					//����popup�̏���
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
					//�ʏ폈��
					else
					{
						messagecnt++;		//messagecnt�𑝉�����
					}
					//�J�E���g�n�̃��Z�b�g
					gameCnt = 0;
					selectcnt = 0;
					PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
				}
			}
			break;
			// 61~�F�U�؋c�_
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
			// 51~�F�ɂރp�[�g
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
			switch (step)
			{
			case 0:
				// �t�F�[�h�A�E�g�J�n
				ColorMask(0, 0, 0, 0);
				ColorFadeOut(0, 0, 0, 60);
				step++;
				break;
			case 1:
				if (IsColorFade() == 0)
				{
					// �t�F�[�h�A�E�g�I��
					SceneBase* scene = new SceneLook(_jsonData[messagecnt].command - 51);
					ChangeScene(scene);
				}
				break;
			}

			// �J���[�}�X�N�̃t�F�[�h�C���A�E�g����
			ColorFadeProcess();
			break;
			// 71�F�^�C�g����
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
		case 2:	//�����̏���
		case 31:	//�s����1�̏���
		case 32:	//�s����2�̏���
		case 33:	//�s����3�̏���
		case 34:	//�s����4�̏���
			//�I���{�^��
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
					//�I�΂ꂽ�I����������
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
						//�I�΂ꂽ�I�������s����1
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
						//�I�΂ꂽ�I�������s����2
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
						//�I�΂ꂽ�I�������s����3
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
						//�I�΂ꂽ�I�������s����4
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
			// 41~44:�s�������̔���
		case 41:
		case 42:
		case 43:
		case 44:
			if (1) {
				int save_messagecnt = _jsonData[messagecnt].command;
				if (gEffect.shakecnt == 0 && shakeflg == 1) {
					messagecnt--;		//�J�E���g��߂�
					for (int i = 0; i < JSON_MAX; i++)	//�R�}���h�O�ɂȂ�܂ŃJ�E���g�����炵������
					{
						if (_jsonData[messagecnt].command == 0 || _jsonData[messagecnt].command == 21) {
							break;
						}
						messagecnt--;
					}
					shakeflg = 0;
				}
				else if (gPad.gTrg & PAD_INPUT_2 && shakeflg != 1) {
					//�e�L�X�g���P�������\������Ă���ԂȂ炷�ׂĂ̕������o���؂�
					if (text_flg == 0) {
						text_flg = 1;
					}
					else
					{
						savemessage();
						int pre_messagecnt = messagecnt;
						pre_messagecnt += 1;
						if (_jsonData[pre_messagecnt].command != save_messagecnt)	//�J�E���g�𑝂₵����̃R�}���h��41�ȊO�������ꍇ�̏���
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
			//draw�ړ�
			//�@�L�����N�^�[
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
				finishflg++;
			}
			// �w�i
			if (_jsonData[messagecnt + 1].bgY > _jsonData[messagecnt].bgY)		//���̍��W��荡�̍��W���Ⴂ�Ȃ�
			{
				_jsonData[messagecnt].bgY += speed / 3;
				if (_jsonData[messagecnt + 1].bgY <= _jsonData[messagecnt].bgY)
				{
					_jsonData[messagecnt].bgY = _jsonData[messagecnt + 1].bgY;
				}
			}
			else if (_jsonData[messagecnt + 1].bgY < _jsonData[messagecnt].bgY)	//���̍��W��荡�̍��W�������Ȃ�
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
			//�J�E���g�n�̏�����
			drawCnt1 = 0;
			drawCnt2 = 0;
			text_flg = 0;
			text_alpha = 0;

			//�摜�E�����ǂݍ���
			cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
			_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
			//BGM�͓ǂݍ��܂Ȃ�
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
				drawCnt1 += CharBytes;		// �`��J�E���^
			}
			else if (Message2_String[drawCnt2] != '\0')
			{
				CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &Message2_String[drawCnt2]);
				drawCnt2 += CharBytes;		// �`��J�E���^
			}
			else
			{
				if (_jsonData[messagecnt].command != 7 || !CheckSoundMem(se_voice)) { text_flg = 1; }
			}
		}

		if (text_flg == 0) {
			//drawcnt���̕����o��
			drawMessage1 = _jsonData[i].message1.substr(0, drawCnt1);
			drawMessage2 = _jsonData[i].message2.substr(0, drawCnt2);
		}
		else
		{
			//���ׂĂ̕����o��
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

		//�|�b�v�A�b�v�̃T�C�Y�㏸
		float pop_maxsize = 1.0;
		if (popup_size < pop_maxsize) {
			popup_size += 0.07;
			if (popup_size > pop_maxsize) {
				popup_size = pop_maxsize;
			}
		}

		//�A�j���[�V��������
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

		// ��ʗh�炵�֘A
		gEffect.ProcessShake();

		gameCnt++;

		//�̗̓k���k���ύX
		player.LifeProcess();

		//�Q�[���I�[�o�[�m�F
		if (gHP <= 0) {
			//�Q�[���I�[�o�[����
			SceneBase* scene = new SceneGameover(savechapter);
			ChangeScene(scene);
		}
	}
}

void SceneTalk::Draw()
{
	DrawGraph(gEffect.shakespead * gEffect.shake, _jsonData[messagecnt].bgY, _cgBg, FALSE); //�w�i

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

	//�L�����N�^�[�̕`��
	if (animflg == 1) {
		//�A�j���[�V����
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
		//�ꖇ�G�̉摜
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
	}

	//�A�C�e���|�b�v�A�b�v
	if (popupflg == 1) {

		DrawRotaGraph(960, 420, popup_size, 0, cg_popup, TRUE);
	}

	//�I�����̊ԈÂ�
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
	ui.DrawTalkUI(reHP, nameflg); //UI�쐬

	//�e�L�X�g����摜�̓_��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, text_alpha);
	DrawGraph(1790, 945, cgtext, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//-----------���b�Z�[�W�ǂݍ���----------------

	int massagefontsize;	//�t�H���g�T�C�Y
	int bt;					//�s��
	int namefontsize;
	int savefontsize;
	savefontsize = GetFontSize();	//���̃t�H���g�T�C�Y��ۑ�

	int choice_num = 0;
	//�R�}���h����
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
		//-----------�I����----------------
		massagefontsize = 62;		//�t�H���g�T�C�Y
		bt = 20;					//�s��
		SetFontSize(massagefontsize);
		DrawFormatString(400, 850, GetColor(255, 255, 255), _jsonData[messagecnt - 1].message1.c_str());							//��s��
		DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), _jsonData[messagecnt - 1].message2.c_str());		//��s��
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
		// �ɂރp�[�g
	case 51:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
		// �J���[�}�X�N�̃t�F�[�h�C���A�E�g�`��
		ColorFadeDraw();
		break;
	}

	DrawGraph(1556, 792, cg_UI_talk, TRUE);
	SetFontSize(savefontsize);	//�t�H���g�T�C�Y��߂�

	//�t���b�V��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flash_alpha);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�G�t�F�N�g
	DrawGraph(0, 0, break_efffect[effectcnt / DRAW_EFFECT_COUNT], TRUE);

	//���O�`��
	if (logflg == 1)
	{
		LogDraw();
	}
}
	