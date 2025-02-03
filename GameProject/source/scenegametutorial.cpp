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
#include	"utf8sjis.h"	// json�̓��{�ꕶ�����g�����߂ɕK�v

SceneGameTutorial::SceneGameTutorial()
{
	// �`���v�^�[
	gameChapter = 0;
	
	int i;
	std::string img_path;
	// �摜�̃��[�h
	_cgBgAnimcnt = 0;
	_cgBgAnimpattern = 0;

	// �c�_�p�[�g
	gGameCnt = 0;

	cgCounter = LoadGraph("res/Scenegamemain/cutin_counter.png");
	cgCounter_x = LoadGraph("res/Scenegamemain/cutin_counter_X.png");

	// �G�t�F�N�g
	//efectType 0:�_���[�W�G�t�F�N�g 1:�_���[�W���o 2:�K�[�h���o


	// ���_�p�[�g
	// �擾�J�[�h�摜
	// ���_�J�[�h�摜
	// �����̃J�[�h�摜

	// �Ԉ�����ꍇ�̉摜
	cgHanronMiss = LoadGraph("res/Scenegamemain/gisyou_miss_text.png");

	// ���Ԃ��p�摜

	// �J�[�h�̐ݒ�
	myDeck.answer_card = tblAnsCard[gameChapter].answerNum;
	myDeck.flg_ans = 0;
	have_card = 0;

	// �X�|�b�g���C�g

	//�h��G�t�F�N�g
	blockse = LoadSoundMem("res/se/block_high.mp3");

	//�����̃��[�h

	// ���ʒ���
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

	// �G�t�F�N�g���̏�����
	gEffect.InitEffect();

	//�J�b�g�C���֌W�̏�����
	cutInFlag = 0;
	cutInCount = 0;

	// �K�[�h
	gardCount = 0;
	LockInterval = 0;

	// ���_�p�[�g�������G�t�F�N�g
	endEffectCnt = 0;
	endEffectpattern = 0;

	//���_�p�[�g���s���o�̃t���O�J�E���g
	misDirectionFlagCnt = 0;

	//�t���b�V���֘A
	flashcnt = 0;
	flash_alpha = 0;

	//�G�̈ʒu���Z�b�g
	scenario.SetEnemyPosition(0);

	//�V�i���I�̃Z�b�g
	scenario.SetChapterScenario(0);
	//�V�i���I���̏،������擾
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
		//json[i].at("bgY").get_to(_jsonData[i].bgY);

		// json�̕�������AUTF-8����Shift-JIS�ɕϊ�
		_jsonData[i].message1 = ConvUTF8toSJIS(_jsonData[i].message1);
		_jsonData[i].message2 = ConvUTF8toSJIS(_jsonData[i].message2);
		_jsonData[i].draw = ConvUTF8toSJIS(_jsonData[i].draw);
		_jsonData[i].name = ConvUTF8toSJIS(_jsonData[i].name);
		//_jsonData[i].voice = ConvUTF8toSJIS(_jsonData[i].voice);
		i++;
	}

	//���b�Z�[�W�J�E���g�ǂݍ���
	messagecnt = 0;

	cgchara = 0;

	//����̃��[�h
	MovieHandle = LoadGraph("res/movie/haikei_ikou.mp4");

	ChangeMovieVolumeToGraph(0, MovieHandle);

	//����
	PlayMovieToGraph(MovieHandle);
	PlaySoundMem(seBGM1, DX_PLAYTYPE_BACK);
}

SceneGameTutorial::~SceneGameTutorial()
{
	int i;
	// �f�[�^�̍폜
	// �摜

	//����
	DeleteSoundMem(MovieHandle);

	//�V�i���I�̏�����
	for (int i = 0; i < WORD_MAX; i++) {
		words[i].use = 0;
	}
}

// ���t�ǉ�
void SceneGameTutorial::AddWord(int wordType, int count, int cgName, int x, int y, int waitTime, int seName, int numName, int ttmCnt) {

	if (wordType == -1) { gGameCnt = 0; }

	//���łɎ擾���Ă���،��͏o���Ȃ�
	if (wordType == 2 && myDeck.CheckCard(numName, ttmCnt)) {

	}
	else {
		// �g���Ă��Ȃ��z���T��
		for (int i = 0; i < WORD_MAX; i++)
		{
			// �g���Ă��Ȃ��B�������g��
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

				//SE�Đ�
				PlaySoundMem(seName, DX_PLAYTYPE_BACK);
				break;
			}
		}
	}
}

// ���t�̏o���V�i���I
void SceneGameTutorial::SetScenario(const std::vector<Scenario::SCENARIO>& scenario)
{
	int i = 0;
	while (scenario[i].gamecnt != -1) {	// �f�[�^�̍Ō�܂ł����[�v
		if (scenario[i].gamecnt == gGameCnt) {
			// �V�i���I�f�[�^��gamecnt����v����
			AddWord(scenario[i].wordType, scenario[i].gamecnt, scenario[i].cgName, scenario[i].x, scenario[i].y, scenario[i].waitTime, scenario[i].seName, scenario[i].numName, scenario[i].testimonyCnt);
			PlaySoundMem(scenario[i].seName, DX_PLAYTYPE_BACK);
		}
		i++;
	}
}

//�V�i���I�Ǝ�D�̏،�����v���Ă��邩�̊m�F
bool SceneGameTutorial::CheckTestimony() {

	if (scenarioTestimonyCnt == myDeck.cards.size()) {
		return true;
	}
}

//�V�i���I���̏،����̎擾
void SceneGameTutorial::GetScenarioTestimony(const std::vector<Scenario::SCENARIO>& scenario) {
	for (int i = 0; i < scenario.size(); i++) {
		if (scenario[i].wordType == 2) {
			scenarioTestimonyCnt++;
		}
	}
}

// ���C�g�̃}�X�f�[�^�ɉ~�̃X�|�b�g���C�g������
void SceneGameTutorial::SpotLight(int cx, int cy, int cr, int baseA)
{
	int x, y;

	// ���C�g�}�b�v�S�̂���(255)�ɂ���
	for (y = 0; y < LIGHTMAP_H; y++) {
		for (x = 0; x < LIGHTMAP_W; x++) {
			_mapLight[y * LIGHTMAP_W + x] = baseA;
		}
	}

	// pixel�P�ʂ���}�b�v�P�ʂɕϊ�
	cx /= LIGHTSIZE_W;
	cy /= LIGHTSIZE_H;
	cr /= LIGHTSIZE_W;

	// ���S���W(cx,cy)���A���ar�ň͂������`��͈͂Ƃ���
	for (y = cy - cr; y < cy + cr; y++) {
		if (0 <= y && y < LIGHTMAP_H) {		// �}�b�v���ɓ����Ă��邩
			for (x = cx - cr; x < cx + cr; x++) {
				if (0 <= x && x < LIGHTMAP_W) {		// �}�b�v���ɓ����Ă��邩

					// ���S���W(cx,cy)����̋��������߁A�A���t�@�l�����߂�
					// �{����sqrt()���g���̂����A����͏d���̂ŁA�g��Ȃ��v�Z�ɂ���
					//int len = (int)sqrt((float)((cx - x)*(cx - x) + (cy - y)*(cy - y)));
					int len = (int)(((cx - x) * (cx - x) + (cy - y) * (cy - y)));

					// cr�������l�Ȃ̂ŁAlen/cr�ŃA���t�@�����܂�
					int a = len * baseA / (cr * cr);	// sqrt()���g��Ȃ��̂ŁAcr^2�Ŋ����ď�������
					if (a > baseA) { a = baseA; }

					// �A���t�@�̒l�Ō���������
					_mapLight[y * LIGHTMAP_W + x] = a;

				}
			}
		}
	}
}

//�J�b�g�C���t���O�̃Q�b�^�[
int SceneGameTutorial::GetCutinFlag()
{
	return cutInFlag;
}


void SceneGameTutorial::Input()
{
	// �������Ȃ�
}

void SceneGameTutorial::Process()
{
	int i;

	if (!GetMovieStateToGraph(MovieHandle)) 
	{
		// �|�[�Y
		if (gPad.gTrg & PAD_INPUT_12 && tutorial_flg != 9) {
			isPause = !isPause;
		}
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
			if (isPause == true && tutorial_flg != 9)
			{
				if (Movieflg != 1 && !CheckSoundMem(seBGM1)) {
					Movieflg = 1;
					PlaySoundMem(seBGM2, DX_PLAYTYPE_LOOP);
				}

				//----�R�}���h�ʏ���----
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
							//�J�E���g�n�̃��Z�b�g
							gameCnt = 0;
							selectcnt = 0;
							cgchara = LoadGraph(_jsonData[messagecnt].draw.c_str());
							PlaySoundMem(se_choice, DX_PLAYTYPE_BACK);
						}
					}
					break;
				case 1:
					tutorial_flg = 1;
					tutorial_cnt = 225;		//�u�l�i�G�������ł���v�̑ҋ@�t���[����
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
					tutorial_cnt = 242;		//�u���̕���������v�̑ҋ@�t���[����
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
					tutorial_cnt = 345;		//�u�S�̔����J����v�̑ҋ@�t���[����
					isPause = false;
					gameCnt = 0;
					messagecnt++;
					break;
				case 6:
					tutorial_flg = 6;
					tutorial_cnt = 500;		//�u�S�̔����J����v�̑ҋ@�t���[����
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


				// ��b�p�[�g����
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
				gameCnt++;
			}
			else
			{
				switch (flg_gameflow)
				{
					//---------- �c�_�p�[�g ----------
				case 0:
					// ���t�̏o��
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

							//�v���C���[���C���ɗ������̏���
							if (words[i].y >= PLAYER_GET_LINE)
							{
								if (words[i].wordType != 2)
								{
									PlaySoundMem(seDamage, DX_PLAYTYPE_BACK);
								}
								//���t�̏���
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

								//�K�[�h��
								if (flg_shield == 1)
								{
									//�K�[�h��Ԃ̏���
									//�\��
									if (words[i].wordType == 1) {
										player.AT -= SHIELD_DAMAGE;		//AT����
										player.CheckPlayerLife();		//0�ȉ��Ȃ�0�ɂ���
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
									//�،�
									else
									{
										PlaySoundMem(seTestimonyBreak, DX_PLAYTYPE_BACK);
										gEffect.AddEffect(2, words[i].x, words[i].y);	// // �_���[�W�G�t�F�N�g
									}
									break;
								}
								else
								{
									//�ʏ��Ԃ̏���
									if (words[i].wordType == 1) {
										gHP -= NOMAL_DAMAGE;		//�̗͌���
										player.CheckPlayerLife();		//0�ȉ��Ȃ�0�ɂ���
										gEffect.AddEffect(0, words[i].x, words[i].y - 100);	// // �_���[�W�G�t�F�N�g
										gEffect.shakecnt = 20;
										gEffect.shakespead = 10;
										gEffect.AddEffect(1, SCREEN_W / 2, SCREEN_H / 2);	// �_���[�W���o
									}
									//�،�
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

					//��D�ɏ،���������
					if (scenarioTestimonyCnt == have_card) {
						if (tutorial_flg == 7)
						{
							isPause = TRUE;
						}
						else
						{
							//���t�̓������~
							//gGameCnt = 0;
							//���_�p�[�g�ڍs�̃t���O
							counterFlag = 1;

							//���_�p�[�g�J�ڂ̉摜�\��
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
						//�{�^�����������甽�_�p�[�g��
						if (tutorial_flg == 8 && gPad.gTrg & PAD_INPUT_2) {

							flg_gameflow = 1;
							PlaySoundMem(seCardGathering, DX_PLAYTYPE_BACK, TRUE);
						}

					}

					// �V�[���h����
					if (tutorial_flg == 4)
					{
						flg_shield = 1;
					}
					else if (tutorial_flg > 3)
					{
						if (gPad.gKey & PAD_INPUT_5 && LockInterval == 0 && counterFlag != 1)
						{
							//�{�^���������Ă�ԃV�[���h�̃J�E���g���v���X
							gardCount++;
							// �V�[���h
							if (gardCount >= GARD_COUNT)
							{
								flg_shield = 1;
								//�V�[���h�����ʉ�
								if (gardCount == GARD_COUNT)
								{
									PlaySoundMem(blockse, DX_PLAYTYPE_BACK, TRUE);
								}
							}
						}
						// �V�[���h����
						else
						{
							//AT����
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
						// �Q�[�����J�E���^�{1
						gGameCnt++;
					}

					if (tutorial_cnt > 0)
					{
						tutorial_cnt--;
					}

					break;
					//---------- ���_�p�[�g ----------
				case 1:
					//���_�ڍs���̉��o������
					counterFlag = 0;

					if (myDeck.cardMoveFlag != 1)
					{
						// �J�[�h�̑I��
						myDeck.MotionCard(flg_gameflow);
					}

					if (tutorial_flg == 8 && myDeck.flg_selectCard == 3)
					{
						isPause = TRUE;
					}

					//������
					if (myDeck.flg_ans == 1)
					{
						//�J�b�g�C���J�n
						cutInFlag = 1;

						// �J�b�g�C���{�C�X�Đ�
						if (cutInCount == 10) { PlaySoundMem(seCutinVoice, DX_PLAYTYPE_BACK); }

						//�t���b�V���J�n
						int flashnum = 20;
						if (flashcnt == 0) {
							//�t���b�V��������
							flash_alpha = 0;
						}
						else if (flashcnt < flashnum / 2) {
							flash_alpha += 255 * 2 / flashnum;
						}
						else if (flashcnt < flashnum) {
							flash_alpha -= 255 * 2 / flashnum;
						}
						flashcnt++;

						//��莞�ԕ\��������J�b�g�C��������
						if (cutInCount > CUTIN_COUNT)
						{
							cutInFlag = 0;
							myDeck.SetCutInFlag(GetCutinFlag());

							if (cutInCount > CUTIN_COUNT + REVERSAL_CARD_COUNT)
							{
								myDeck.cardMoveFlag = 1;
							}

						}
						//�J�b�g�C���J�E���g
						cutInCount++;
					}
					// �s�������i���_�p�[�g���p���j
					if (myDeck.flg_ans == 2) {
						//��莞�Ԃ����Ȃ��Ɣ������Ȃ�
						if (misDirectionFlagCnt > 30) {
							//�{�^������������_���[�W���o
							if (gPad.gTrg & PAD_INPUT_2) {
								PlaySoundMem(seDamage, DX_PLAYTYPE_BACK);
								gHP -= NOMAL_DAMAGE;		//�̗͌���
								player.CheckPlayerLife();		//0�ȉ��Ȃ�0�ɂ���
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

					// �I�������J�[�h�̈ړ�
					if (myDeck.cardMoveFlag == 1 && cutInFlag != 1) { myDeck.MoveCard(flg_gameflow); }

					break;

					//---------- �I�� ----------
				case 2:
					// ����
					if (myDeck.flg_ans == 1)
					{
						gEffect.shakecnt = 20;
						gEffect.shakespead = 10;

						int waitflame = 15;
						if (endEffectCnt == 0)
						{
							PlaySoundMem(seHitTestimony, DX_PLAYTYPE_BACK, TRUE);
							endEffect_waitCnt = waitflame;
							gEffect.AddEffect(2, gikai[4].X, gikai[4].Y);	// // �_���[�W�G�t�F�N�g
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
							//�t���b�V���J�n
							int flashnum = 20;
							if (flashcnt == 0) {
								//�t���b�V��������
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

				// �Q�[���󋵂ɍ��킹�ăJ�[�h��ύX
				myDeck.SetDrawCard(flg_gameflow);


				// ��ʗh�炵�֘A
				gEffect.ProcessShake();

				// �G�t�F�N�g����
				gEffect.ProcessEffect();

				//�h��A�j���[�V�����p
				if (flg_shield == 1 && player.AT != 0) {
					if (lockCnt < 10) {
						lockCnt++;
					}
				}
				else
				{
					//�K�[�h�f�B���C��
					if (gardCount > 0) {
						if (lockCnt < 3) {
							lockCnt++;
						}
					}
					else if (LockInterval > 0)	//�K�[�h�j���̃f�B���C��
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
						//lockCnt�����炵�Â���
						if (lockCnt > 0) {
							lockCnt--;
						}
					}
				}
			}
			// �w�i�A�j���[�V����
			_cgBgAnimcnt++;
			_cgBgAnimpattern = anim.cgAnimPattern(_cgBgAnimcnt, CGBGANIM_SPEED, CGBGANIM_PATTERN_MAX);
		}
	}

	//�̗̓k���k���ύX
	player.LifeProcess();

	//�Q�[���I�[�o�[�m�F
	if (gHP <= 0) {
		if (CheckSoundMem(seBGM1)) { StopSoundMem(seBGM1); }
		if (CheckSoundMem(seBGM2)) { StopSoundMem(seBGM2); }
		//�Q�[���I�[�o�[����
		SceneBase* scene = new SceneGameover(300);
		ChangeScene(scene);
	}
}

void SceneGameTutorial::Draw()
{
	// �w�i
	//�t�B�j�b�V�����͉f���Ȃ�
	if (flg_gameflow != 2) {
		if (flg_shield == 1 && flg_gameflow == 0) { DrawGraph(0, 0, gGlobal->_cgBg[_cgBgAnimpattern], FALSE); }
		else { DrawGraph(gEffect.shakespead * gEffect.shake, 0, gGlobal->_cgBg[_cgBgAnimpattern], FALSE); }
	}

	int i;
	int center = myDeck.GetCenterCard();		// �I�𒆂̃J�[�h�ʒu
	// �Q�[�����[�h
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

		//�h��A�j���[�V�����`��
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

	// �X�|�b�g���C�g
	if (flg_gameflow > 0)
	{
		if (myDeck.flg_selectCard == 3)
		{
			for (i = 0; i < ENEMY_MAX; i++)
			{
				if (i == myDeck.cards[center].num)
				{
					SpotLight(gikai[i].X, gikai[i].Y, 170, 150);
					// ���C�g�}�b�v���ォ�甼�����`��
					for (int y = 0; y < LIGHTMAP_H; y++) {
						for (int x = 0; x < LIGHTMAP_W; x++) {
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, _mapLight[y * LIGHTMAP_W + x]);		// �������`��w��
							DrawBox(x * LIGHTSIZE_W, y * LIGHTSIZE_H, x * LIGHTSIZE_W + LIGHTSIZE_W, y * LIGHTSIZE_H + LIGHTSIZE_H, GetColor(0, 0, 0), TRUE);	// ��
						}
					}
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��
				}
			}
		}
	}

	gEffect.DrawEffect();

	// �{�^��UI
	if (myDeck.flg_selectCard == 3)
	{
		DrawGraph(1757, 956, cgHanronButtonUI, TRUE);
	}

	//���_�ڍs��
	if (counterFlag == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(counterGraph.x, 406, cgCounter, TRUE);
		DrawRotaGraph(counterGraph.x + 1157 + 69, 471 + 69, counterGraph.scale, 0, cgCounter_x, 1, 0, 0);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��

	// �J�[�h�i��D�j
	myDeck.DrawCard(flg_gameflow);		// �J�[�h�i��D�j�`��

	if (flg_gameflow == 2)
	{
		DrawGraph(0, 0, cgEndEffect[endEffectpattern], TRUE);
		gEffect.DrawEffect();
	}
	else
	{
		// UI
		if (isPause == true) {
			//------------��b��----------
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
				ui.DrawGamemainUI(reHP); //UI�쐬
			}
			else
			{
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
				savefontsize = GetFontSize(); //���̃t�H���g�T�C�Y��ۑ�
				//�R�}���h����
				switch (_jsonData[messagecnt].command)
				{
				case 0:
					//-----------���b�Z�[�W�ǂݍ���----------------
					massagefontsize = 62;		//�t�H���g�T�C�Y
					bt = 20;					//�s��

					namefontsize = 48;
					SetFontSize(namefontsize);
					DrawPosString(230, 890, 0, GetColor(255, 255, 255), _jsonData[messagecnt].name.c_str());
					SetFontSize(massagefontsize);

					DrawFormatString(400, 850, GetColor(255, 255, 255), drawMessage1.c_str());							//��s��

					DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), drawMessage2.c_str());	//��s��
					break;
				}

				SetFontSize(savefontsize);	//�t�H���g�T�C�Y��߂�
			}
		}
		else
		{
			ui.DrawGamemainUI(reHP);	//UI�Ăяo��;
		}
	}

	//�t���b�V��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, flash_alpha);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//����`��
	if (GetMovieStateToGraph(MovieHandle)) {
		DrawGraph(0, 0, MovieHandle, FALSE);
	}

	//�J�b�g�C���\��
	if (cutInFlag == 1)
	{
		int t = cutInCount / 4;
		if (t < 30)
		{
			DrawGraph(0, 0, cgCutIn[t], TRUE);
		}
	}

	//���_���s��
	if (myDeck.flg_ans == 2) {
		DrawGraph(0, 826, cgHanronMiss, FALSE);
	}

	//���O�`��
	if (logflg == 1)
	{
		LogDraw();
	}

}
