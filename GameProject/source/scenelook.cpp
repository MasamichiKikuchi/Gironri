#include	"scenelook.h"
#include	"DxLib.h"
#include	"gamemain.h"
#include	"scenetalk.h"
#include	"scenegamemain.h"
#include	"mymath.h"
#include	"data.h"
#include	"SceneGameover.h"

SceneLook::SceneLook(int chapter)
{
	gameChapter = chapter;
	int i = 0;

	flgAnswer = 0;

	vSpotLight = VGet(tblLookPoint[gameChapter].initX, tblLookPoint[gameChapter].initY, 0);
	spotlightSize = SPOTLIGHT_SIZE_MAX;
	ansLightSize = 0;
	vInputR = VGet(0, 0, 0);
	vUnitR = VGet(1, 1, 1);
	vDirR = VGet(0, 0, 0);

	talkCnt = 0;
	flgAllTalk = 0;
	allTalkCnt = 0;
	lineflg = 0;

	// �G�t�F�N�g���̏�����
	gEffect.InitEffect();

	lightCnt = 0;
	step = 0;

	flgLook = 0;
	UniqueNoAnsCnt = 0;

	// BGM�Ese
	// ���ʒ���
	ChangeVolumeSoundMem(255 * LOOK_BGM_VOLUME / 100, seLookBGM);
	ChangeVolumeSoundMem(255 * LOOK_SE_VOLUME / 100, seLookDamage);
	ChangeVolumeSoundMem(255 * LOOK_SE_VOLUME / 100, seLookHazure);
	ChangeVolumeSoundMem(255 * LOOK_SE_VOLUME / 100, seLookSeikai);
	// BGM�Đ�
	PlaySoundMem(seLookBGM, DX_PLAYTYPE_LOOP);
}

SceneLook::~SceneLook()
{
	
}

// ���C�g�}�b�v�̒l�̃Z�b�g
void SceneLook::SetLightMap()
{
	int x, y;

	// ���C�g�}�b�v�S�̂�ALPHA_VALUE�̒l�ɂ���
	for (y = 0; y < LIGHTMAP_H; y++) {
		for (x = 0; x < LIGHTMAP_W; x++) {
			mapLight[y * LIGHTMAP_W + x] = ALPHA_VALUE;
		}
	}
	// ����p���C�g�}�b�v�S�̂̒l��0�ɂ���
	for (y = 0; y < LIGHTMAP_H; y++) {
		for (x = 0; x < LIGHTMAP_W; x++) {
			mapAnsLight[y * LIGHTMAP_W + x] = 0;
		}
	}
}

// ���C�g�̃}�X�f�[�^�ɉ~�̃X�|�b�g���C�g������
void SceneLook::SpotLight(int cx, int cy, int cr, int alpha, int typeAns)
{
	int x, y, a;

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
					int len = (int)(((cx - x) * (cx - x) + (cy - y) * (cy - y)));

					// cr�������l�Ȃ̂ŁAlen/cr�ŃA���t�@�����܂�
					a = len * alpha / (cr * cr);	// sqrt()���g��Ȃ��̂ŁAcr^2�Ŋ����ď�������
					if (a > alpha) { a = alpha; }

					switch (typeAns)
					{
					case 0:
						// �A���t�@�̒l�Ō���������
						mapLight[y * LIGHTMAP_W + x] = a;

						break;
					case 1:
						// �X�|�b�g���C�g�̒��S���甒���Ȃ��Ă���
						mapAnsLight[y * LIGHTMAP_W + x] = alpha - a;
						break;
					}
				}
			}
		}
	}
}

// �E�X�e�B�b�N�̓��͒l�̐��K��
void SceneLook::NormInput(XINPUT_STATE xinput)
{
	vInputR = VGet(xinput.ThumbLX, -xinput.ThumbLY, 0);
	vUnitR = VNorm(vInputR);
}

// �~�̈ړ�
void SceneLook::splMove(XINPUT_STATE xinput)
{
	// �ړ������̌v�Z
	if (abs(xinput.ThumbLX) > 10000 || abs(xinput.ThumbLY) > 10000)
	{
		NormInput(xinput);
		vDirR = VScale(vUnitR, SPOTLIGHT_SPEED);
	}
	else
	{
		vDirR = VGet(0, 0, 0);
	}

	// �ړ������̉��Z
	vSpotLight = VAdd(vSpotLight, vDirR);
	
	// �ړ��\�͈͂ɂ�鐧��
	// x���W
	if (vSpotLight.x < 0) { vSpotLight.x = 0; }
	else if (vSpotLight.x > SCREEN_W) { vSpotLight.x = SCREEN_W; }
	// y���W
	if (vSpotLight.y < 0) { vSpotLight.y = 0; }
	else if (vSpotLight.y > 806) { vSpotLight.y = 806; }
}

// �~�̃T�C�Y�ύX�i�g��k���j
void SceneLook::splScale(XINPUT_STATE xinput)
{
	// ���g���K�[�Ŋg��
	if (xinput.LeftTrigger > 100)
	{
		spotlightSize += LIGHTSIZE_W;
		if (spotlightSize > SPOTLIGHT_SIZE_MAX) { spotlightSize = SPOTLIGHT_SIZE_MAX; }
	}
	// �E�g���K�[�ŏk��
	if (xinput.RightTrigger > 100)
	{
		spotlightSize -= LIGHTSIZE_W;
		if (spotlightSize < SPOTLIGHT_SIZE_MIN) { spotlightSize = SPOTLIGHT_SIZE_MIN; }
	}
}

// �ɂ񂾉ӏ��̃`�F�b�N
void SceneLook::CheckPoint(float px, float py)
{
	int i;

	// �����蔻��͈̔͂��~
	if (tblLookPoint[gameChapter].hittype == 0)
	{
		// �������ӏ��̉~���ɃX�|�b�g���C�g�̒��S�����邩�ǂ���
		if (IsHitPointCircle(px, py,
			tblLookPoint[gameChapter].x, tblLookPoint[gameChapter].y, tblLookPoint[gameChapter].r))
		{
			flgAnswer = 1;	// ����
		}
		else
		{
			flgAnswer = 2;	// �s����
		}
	}
	// �����蔻��͈̔͂���`
	else
	{
		// �������ӏ��̋�`���ɃX�|�b�g���C�g�̒��S�����邩�ǂ���
		if (IsHitPointBox(px, py,
			tblLookPoint[gameChapter].x, tblLookPoint[gameChapter].y, tblLookPoint[gameChapter].w, tblLookPoint[gameChapter].h))
		{
			flgAnswer = 1;	// ����
		}
		else
		{
			flgAnswer = 2;	// �s����
		}
	}

	// �s�����̎��A����s������
	if (flgAnswer == 2)
	{
		// ����s����
		for (i = 0; i < 6; i++)
		{
			if (tblLookEaster[gameChapter][i].hittype == 0)
			{
				// �������ӏ��̉~���ɃX�|�b�g���C�g�̒��S�����邩�ǂ���
				if (IsHitPointCircle(px, py,
					tblLookEaster[gameChapter][i].x, tblLookEaster[gameChapter][i].y, tblLookEaster[gameChapter][i].r))
				{
					flgAnswer = 3;	// ����s����
					UniqueNoAnsNum = i;
					break;
				}
				else
				{
					flgAnswer = 2;	// �s����
				}
			}
			else
			{
				// �������ӏ��̋�`���ɃX�|�b�g���C�g�̒��S�����邩�ǂ���
				if (IsHitPointBox(px, py,
					tblLookEaster[gameChapter][i].x, tblLookEaster[gameChapter][i].y, tblLookEaster[gameChapter][i].w, tblLookEaster[gameChapter][i].h))
				{
					flgAnswer = 3;	// ����s����
					UniqueNoAnsNum = i;
					break;
				}
				else
				{
					flgAnswer = 2;	// �s����
				}
			}
		}
	}

	if (flgAnswer == 3 && gameChapter == 2 && UniqueNoAnsNum > 0)
	{
		UniqueNoAnsCnt++;
	}

	// �G�t�F�N�g�ESE
	if (flgAnswer == 1)
	{
		// ����
		PlaySoundMem(seLookSeikai, DX_PLAYTYPE_BACK);
	}
	else if (flgAnswer >= 2)
	{
		// �n�Y���E����s����
		PlaySoundMem(seLookHazure, DX_PLAYTYPE_BACK);

		// �G�t�F�N�g�ǉ�
		gEffect.AddEffect(1, SCREEN_W / 2, SCREEN_H / 2);
		gEffect.shakecnt = 30;
		gEffect.shakespead = 10;
		gHP -= 20;	// HP����
	}
}

// �������ӏ���I�����̃Z���t
void SceneLook::lookTalk()
{
	int i, ansNum = 0;
	for (i = 0; i < tblLPSize; i++)
	{
		if (tblLookPoint[i].chapter == gameChapter) { ansNum = i; }
	}

	int drawCnt = (talkCnt / DRAW_MESSAGE_COUNT) * 2;
	std::string message[3];
	const char* messageByte[3];
	switch (flgAnswer)
	{
	case 0:
		message[0] = tblLookPoint[ansNum].lookingMessage;
		messageByte[0] = tblLookPoint[ansNum].lookingMessage.c_str();
		break;
	case 1:
		message[0] = tblLookPoint[ansNum].trueMessage;
		messageByte[0] = tblLookPoint[ansNum].trueMessage.c_str();
		break;
	case 2:
		message[0] = tblLookPoint[ansNum].falseMessage;
		messageByte[0] = tblLookPoint[ansNum].falseMessage.c_str();
		break;
	case 3:
		if (!tblLookEaster[gameChapter][UniqueNoAnsNum].message1.empty())
		{
			message[0] = tblLookEaster[gameChapter][UniqueNoAnsNum].message1;
			messageByte[0] = tblLookEaster[gameChapter][UniqueNoAnsNum].message1.c_str();
		}
		if (!tblLookEaster[gameChapter][UniqueNoAnsNum].message2.empty())
		{
			message[1] = tblLookEaster[gameChapter][UniqueNoAnsNum].message2;
			messageByte[1] = tblLookEaster[gameChapter][UniqueNoAnsNum].message2.c_str();
		}
		if (!tblLookEaster[gameChapter][UniqueNoAnsNum].message3.empty())
		{
			message[2] = tblLookEaster[gameChapter][UniqueNoAnsNum].message3;
			messageByte[2] = tblLookEaster[gameChapter][UniqueNoAnsNum].message3.c_str();
		}
	}
	
	int msize[3];
	for (i = 0; i < 3; i++) { msize[i] = message[i].size(); }
	int CharBytes;

	// �ُ����s����
	if (gameChapter == 2 && flgAnswer == 3 && UniqueNoAnsNum > 0)
	{
		if (drawCnt <= 0)
		{
			drawMessage1.clear();
		}
		else if (msize[UniqueNoAnsCnt - 1] > drawCnt)
		{
			CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &messageByte[UniqueNoAnsCnt - 1][drawCnt1]);
			drawCnt1 += CharBytes;
			drawMessage1 = message[UniqueNoAnsCnt - 1].substr(0, drawCnt1);
		}
		else if (msize[UniqueNoAnsCnt - 1] <= drawCnt)
		{
			drawMessage1 = message[UniqueNoAnsCnt - 1];
			drawCnt -= msize[UniqueNoAnsCnt - 1];
			allTalkCnt++;
		}
	}
	// �ʏ����s����
	else
	{
		if (drawCnt <= 0)
		{
			drawMessage1.clear();
			drawMessage2.clear();
			lineflg = 0;
			drawCnt1 = 0;
			drawCnt2 = 0;
		}
		// 1�s��
		else if (messageByte[0][drawCnt1] != '\0')
		{
			CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &messageByte[0][drawCnt1]);
			drawCnt1 += CharBytes;
			drawMessage1 = message[0].substr(0, drawCnt1);
		}
		else
		{
			drawMessage1 = message[0];
			drawCnt -= msize[0];
			if (drawMessage2.empty()) { allTalkCnt++; }
			else { lineflg = 1; }
		}
		if (lineflg == 1)
		{
			// 2�s��
			if (messageByte[1][drawCnt2] != '\0')
			{
				CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &messageByte[1][drawCnt2]);
				drawCnt2 += CharBytes;
				drawMessage2 = message[1].substr(0, drawCnt2);
			}
			else
			{
				drawMessage2 = message[1];
				allTalkCnt++;
			}
		}
	}

	talkCnt++;
}

void SceneLook::Input()
{

}

void SceneLook::Process()
{
	switch (step)
	{
	case 0:
		// �t�F�[�h�C���J�n
		ColorFadeIn(60);
		step++;
		break;
	case 1:
		if (IsColorFade() == 0)
		{
			// �t�F�[�h�C���I��
			step++;
		}
		break;
	case 2:
		// �ʏ폈��

		int x, y;
		
		switch(flgLook)
		{
		case 0:
			if (abs(gPad.xinput_pad1.ThumbLX) > 10000 || abs(gPad.xinput_pad1.ThumbLY) > 10000)
			{
				flgLook = 1;
				spotlightSize = SCREEN_W;
			}
			break;
		case 1:
			if (spotlightSize > SPOTLIGHT_SIZE_MAX)
			{
				spotlightSize -= (SCREEN_W - SPOTLIGHT_SIZE_MAX) / 30;
			}
			else
			{
				flgLook = 2;
				spotlightSize = SPOTLIGHT_SIZE_MAX;
			}

			SetLightMap();
			// �X�|�b�g���C�g
			SpotLight(vSpotLight.x, vSpotLight.y, spotlightSize, ALPHA_VALUE, 0);
			break;
		case 2:
			SetLightMap();

			if (flgAnswer == 1)		// ����
			{
				// �����ɃX�|�b�g���C�g�̒��S�����ʂ������Ȃ��Ă���
				SpotLight(vSpotLight.x, vSpotLight.y, ansLightSize, 255, 1);
				ansLightSize += 40;
			}
			else
			{
				splMove(gPad.xinput_pad1);		// �X�|�b�g���C�g�ړ�
				splScale(gPad.xinput_pad1);

				// B�{�^�����������Ƃŉ������ӏ���I��
				if (gPad.gTrg & PAD_INPUT_2)
				{
					CheckPoint(vSpotLight.x, vSpotLight.y);
					talkCnt = 0;
					allTalkCnt = 0;
				}

				// ����Q�[���I�[�o�[
				if (gameChapter == 2)
				{
					if (UniqueNoAnsCnt == 3 && allTalkCnt == 60)
					{
						PlaySoundMem(seLookDamage, DX_PLAYTYPE_BACK);	// se
						// �G�t�F�N�g�ǉ�
						gEffect.AddEffect(1, SCREEN_W / 2, SCREEN_H / 2);
						gEffect.shakecnt = 30;
						gEffect.shakespead = 10;
						gHP = 0;
					}
					else if (UniqueNoAnsCnt > 3)
					{
						UniqueNoAnsCnt = 3;
						gHP = 0;
					}
				}

				if (flgAnswer != 0 && allTalkCnt == 60)
				{
					flgAnswer = 0;
					talkCnt = 0;
					allTalkCnt = 0;
				}
			}

			// �X�|�b�g���C�g
			SpotLight(vSpotLight.x, vSpotLight.y, spotlightSize, ALPHA_VALUE, 0);

			// ���C�g�}�b�v�̂ǂ̂��炢�������Ȃ��Ă��邩�`�F�b�N
			lightCnt = 0;
			for (y = 0; y < LIGHTMAP_H; y++) {
				for (x = 0; x < LIGHTMAP_W; x++) {
					if (mapAnsLight[y * LIGHTMAP_W + x] >= 200) { lightCnt++; }
				}
			}
			if (lightCnt == LIGHTMAP_W * LIGHTMAP_H)
			{
				// �����ɂ���ʑJ��
				if (CheckSoundMem(seLookBGM)) { StopSoundMem(seLookBGM); }
				SceneBase* scene = new SceneTalk(gameChapter + 51);
				ChangeScene(scene);
			}

			// ��ʗh�炵����
			gEffect.ProcessShake();
			// �G�t�F�N�g����
			gEffect.ProcessEffect();

			break;
		}
		// �Z���t
		lookTalk();
		break;
	}

	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g����
	ColorFadeProcess();

	//�̗̓k���k���ύX
	player.LifeProcess();

	//�Q�[���I�[�o�[�m�F
	if (gHP <= 0) {
		//�Q�[���I�[�o�[����
		if (CheckSoundMem(seLookBGM)) { StopSoundMem(seLookBGM); }
		SceneBase* scene = new SceneGameover(100 + gameChapter);
		ChangeScene(scene);
	}
}

void SceneLook::Draw()
{
	int i, x, y, w, h;
	// �w�i
	DrawGraph(gEffect.shakespead * gEffect.shake, 0, tblLookPoint[gameChapter].img, FALSE);

	// ���C�g�}�b�v���ォ�甼�����`��
	int LightMapColor = GetColor(0, 0, 0);
	for (int y = 0; y < LIGHTMAP_H; y++) {
		for (int x = 0; x < LIGHTMAP_W; x++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, mapLight[y * LIGHTMAP_W + x]);		// �������`��w��
			DrawBox(x * LIGHTSIZE_W, y * LIGHTSIZE_H, x * LIGHTSIZE_W + LIGHTSIZE_W, y * LIGHTSIZE_H + LIGHTSIZE_H, LightMapColor, TRUE);	// ��
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��

	gEffect.DrawEffect();	// �G�t�F�N�g�`��

	// ����
	int LightAnsMapColor = GetColor(255, 255, 200);		// ��
	if (flgAnswer == 1)
	{
		for (int y = 0; y < LIGHTMAP_H; y++) {
			for (int x = 0; x < LIGHTMAP_W; x++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, mapAnsLight[y * LIGHTMAP_W + x]);		// �������`��w��
				DrawBox(x * LIGHTSIZE_W, y * LIGHTSIZE_H, x * LIGHTSIZE_W + LIGHTSIZE_W, y * LIGHTSIZE_H + LIGHTSIZE_H, LightAnsMapColor, TRUE);	// ��
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �s�����`��w��
	}

	DrawGraph(1530, 768, cgLookButtonUI, TRUE);
	ui.DrawTalkUI(reHP, 0); //UI�쐬

	// ����
	int bt = 20;						//�s��
	int massagefontsize = 62;			// �Z���t�̃t�H���g�T�C�Y
	int namefontsize = 48;				// ���O�̃t�H���g�T�C�Y
	int savefontsize = GetFontSize();	// ���̃t�H���g�T�C�Y��ۑ�

	// �Z���t
	SetFontSize(massagefontsize);
	DrawFormatString(400, 850, GetColor(255, 255, 255), drawMessage1.c_str());
	DrawFormatString(400, 850 + massagefontsize + bt, GetColor(255, 255, 255), drawMessage2.c_str());
	SetFontSize(savefontsize);
	
	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g�`��
	ColorFadeDraw();
}
