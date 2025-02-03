#include	"Scenario.h"
#include	"scenegamemain.h"
#include	"gamemain.h"
#include	"data.h"

//�e�r�S���ӏ��@�t�@�C���S��

Scenario::Scenario()
{
	
}

Scenario::~Scenario()
{

}

//�G�̈ʒu���Z�b�g
void Scenario::SetEnemyPosition(int chapter)
{
	//�`���v�^�[�T�͓G�̈ʒu��S�Ē�����
	if (chapter == 5)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			gikai[i].X = SCREEN_W / 2;
			gikai[i].Y = 150;
		}
	}
	else
	{
		// �G�̈ʒu�ݒ�
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			gikai[i].X = SCREEN_W / 2 + (i - ENEMY_MAX / 2) * 300;
			gikai[i].Y = 150;
		}
	}
}

//�Q�[���V�[���p�V�i���I�̃Q�b�^�[
std::vector<Scenario::SCENARIO>* Scenario::GetScenario()
{
	return &scenarioList;
}

//�Q�[���V�[���p�̃V�i���I�ɒ��g��ǉ�����
void Scenario::AddScenario(SCENARIO* scenario, size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		scenarioList.push_back(scenario[i]);
	}
}

//�`���v�^�[���Ƃ̃V�i���I��������
void Scenario::SetChapterScenario(int chapter) {
	// �،��Ҕԍ�, �،��J�E���g,�o���^�C�~���O,	�o���ʒu, 	���t�̎��,	�摜��,	�o���ォ�瓮���o������, ������
	// numName,	  testimonyCnt,	gamecnt,		x,y,	    wordType,	cgName,	waitTime,			    seName
	//�`���[�g���A���V�i���I
	SCENARIO scenario0[] = {
	// �l�i�G���F�s���N�u�������v
	{ 4, 2,   90, gikai[4].X - 120, gikai[4].Y + 270, 1, cgPinkThoughtlessWords[chapter][0][0], 170, sePinkLaugh },
	{ 4, 2,  120, gikai[4].X,       gikai[4].Y + 250, 1, cgPinkThoughtlessWords[chapter][0][1], 190},
	{ 4, 2,  150, gikai[4].X + 120, gikai[4].Y + 270, 1, cgPinkThoughtlessWords[chapter][0][2], 210},
	
	// �l�i�G���F�ԁu����������ˁv
	{ 0, 2,  500, gikai[0].X - 240, gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][0][0], 70, seRedLaugh},
	{ 0, 2,  510, gikai[0].X - 120, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][0][1], 75},
	{ 0, 2,  520, gikai[0].X,		gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][0][2], 80},
	{ 0, 2,  530, gikai[0].X + 120, gikai[0].Y + 270, 1, cgRedThoughtlessWords[chapter][0][3], 85},
	{ 0, 2,  540, gikai[0].X + 240, gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][0][4], 90},
	{ 0, 2,  550, gikai[0].X + 360, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][0][5], 95},
	
	// �l�i�G���F�s���N�u�������v
	{ 4, 2,  710, gikai[4].X - 120, gikai[4].Y + 270, 1, cgPinkThoughtlessWords[chapter][0][0],	60, sePinkLaugh},
	{ 4, 2,  730, gikai[4].X,	    gikai[4].Y + 250, 1, cgPinkThoughtlessWords[chapter][0][1], 75},
	{ 4, 2,  750, gikai[4].X + 120, gikai[4].Y + 270, 1, cgPinkThoughtlessWords[chapter][0][2], 90},
	
	// �،��F�ԁu�e�F�͍߂�F�߂Ă���̂�v
	{ 0, 0,  900, gikai[0].X,		      gikai[0].Y + 200, 2, cgTestimony[chapter][0][0], 50, sePinkLaugh},

	// �l�i�G���F�u���Ԃ̖��ʂł��ˁv
	{ 3, 2, 1520, gikai[3].X - 360, gikai[3].Y + 260, 1, cgBlueThoughtlessWords[chapter][0][0], 100,},
	{ 3, 2, 1530, gikai[3].X - 240, gikai[3].Y + 280, 1, cgBlueThoughtlessWords[chapter][0][1], 110,},
	{ 3, 2, 1540, gikai[3].X - 120, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][2], 120,},
	{ 3, 2, 1550, gikai[3].X,	    gikai[3].Y + 270, 1, cgBlueThoughtlessWords[chapter][0][3], 130,},
	{ 3, 2, 1560, gikai[3].X + 120, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][4], 140,},
	{ 3, 2, 1570, gikai[3].X + 240, gikai[3].Y + 280, 1, cgBlueThoughtlessWords[chapter][0][5], 150,},
	{ 3, 2, 1580, gikai[3].X + 360, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][6], 160,},
	{ 3, 2, 1590, gikai[3].X + 480, gikai[3].Y + 270, 1, cgBlueThoughtlessWords[chapter][0][7], 170,},

	// �l�i�G���F���u�����I���ł���������v
	{ 2, 2, 1100, gikai[2].X - 360, gikai[2].Y + 240, 1, cgYellowThoughtlessWords[chapter][0][0], 100,},
	{ 2, 2, 1110, gikai[2].X - 240, gikai[2].Y + 270, 1, cgYellowThoughtlessWords[chapter][0][1], 110,},
	{ 2, 2, 1120, gikai[2].X - 120, gikai[2].Y + 250, 1, cgYellowThoughtlessWords[chapter][0][2], 120,},
	{ 2, 2, 1130, gikai[2].X,		gikai[2].Y + 260, 1, cgYellowThoughtlessWords[chapter][0][3], 130,},
	{ 2, 2, 1140, gikai[2].X + 120, gikai[2].Y + 240, 1, cgYellowThoughtlessWords[chapter][0][4], 140,},
	{ 2, 2, 1150, gikai[2].X + 240, gikai[2].Y + 260, 1, cgYellowThoughtlessWords[chapter][0][5], 150,},
	{ 2, 2, 1160, gikai[2].X + 360, gikai[2].Y + 280, 1, cgYellowThoughtlessWords[chapter][0][6], 160,},
	{ 2, 2, 1170, gikai[2].X + 480, gikai[2].Y + 260, 1, cgYellowThoughtlessWords[chapter][0][7], 170,},
	{ 2, 2, 1180, gikai[2].X + 600, gikai[2].Y + 270, 1, cgYellowThoughtlessWords[chapter][0][8], 180,},
	{ 2, 2, 1190, gikai[2].X + 720, gikai[2].Y + 240, 1, cgYellowThoughtlessWords[chapter][0][9], 190,},
	{ 2, 2, 1200, gikai[2].X + 840, gikai[2].Y + 260, 1, cgYellowThoughtlessWords[chapter][0][10],200,},
	
	// �،��F�s���N�u���̑{���͊�������v
	{ 4, 0, 1100, gikai[4].X,		      gikai[4].Y + 200, 2, cgTestimony[chapter][4][0], 300, sePinkLaugh},

	{ 5, 3, 1900, 0, 0, -1 },	// �V�i���I���[�v
	{ 5, 3, -1 },	// �Ō��gamecnt = -1

	};

	//�`���v�^�[�P�V�i���I
	SCENARIO scenario1[] = {
	// �l�i�G���F��1�u�M�����Ɛl�Ō��܂�ˁv
	{ 0, 2,  50, gikai[0].X - 240, gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][0][0], 100, seRedLaugh},
	{ 0, 2,  60, gikai[0].X - 120, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][0][1], 145},
	{ 0, 2,  70, gikai[0].X,       gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][0][2], 185},
	{ 0, 2,  80, gikai[0].X + 120, gikai[0].Y + 270, 1, cgRedThoughtlessWords[chapter][0][3], 215},
	{ 0, 2,  90, gikai[0].X + 240, gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][0][4], 235},
	{ 0, 2, 100, gikai[0].X + 360, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][0][5], 255},
	{ 0, 2, 110, gikai[0].X + 480, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][0][6], 275},
	{ 0, 2, 120, gikai[0].X + 600, gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][0][7], 295},
	{ 0, 2, 130, gikai[0].X + 720, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][0][8], 315},
	{ 0, 2, 140, gikai[0].X + 840, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][0][9], 335},

	// �،��F���u����ŐR���͏I���ł��ˁv
	{ 2, 0,  450, gikai[2].X,            gikai[2].Y + 200, 2,cgTestimony[gameChapter][2][0],50, seYellowLaugh},

	// �l�i�G���F��1�u��̋M�d�Ȏ��Ԃ��v
	{ 3, 2, 545, gikai[3].X - 840, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][0],  200, seBlueLaugh},
	{ 3, 2, 555, gikai[3].X - 720, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][1],  190},
	{ 3, 2, 565, gikai[3].X - 600, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][2],  180},
	{ 3, 2, 575, gikai[3].X - 480, gikai[3].Y + 270, 1, cgBlueThoughtlessWords[chapter][0][3],  170},
	{ 3, 2, 585, gikai[3].X - 360, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][4],  160},
	{ 3, 2, 595, gikai[3].X - 240, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][5],  150},
	{ 3, 2, 605, gikai[3].X - 120, gikai[3].Y + 280, 1, cgBlueThoughtlessWords[chapter][0][6],  140},
	{ 3, 2, 615, gikai[3].X      , gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][7],  130},
	{ 3, 2, 625, gikai[3].X + 120, gikai[3].Y + 270, 1, cgBlueThoughtlessWords[chapter][0][8],  120},
	{ 3, 2, 635, gikai[3].X + 240, gikai[3].Y + 250, 1, cgBlueThoughtlessWords[chapter][0][9],  110},

	// �l�i�G���F��1�u���悤�Ȃ�v
	{ 1, 2, 765, gikai[1].X - 120, gikai[1].Y + 250, 1, cgGreenThoughtlessWords[chapter][0][0], 75, seGreenLaugh},
	{ 1, 2, 780, gikai[1].X,       gikai[1].Y + 280, 1, cgGreenThoughtlessWords[chapter][0][1], 75},
	{ 1, 2, 795, gikai[1].X + 120, gikai[1].Y + 250, 1, cgGreenThoughtlessWords[chapter][0][2], 75},
	{ 1, 2, 810, gikai[1].X + 240, gikai[1].Y + 270, 1, cgGreenThoughtlessWords[chapter][0][3], 75},
	{ 1, 2, 825, gikai[1].X + 360, gikai[1].Y + 250, 1, cgGreenThoughtlessWords[chapter][0][4], 75},

	// �،��F�s���N�u�i�C�t���������Ă����Ȃ�Ăˁv
	{ 4, 0, 1140, gikai[4].X,      gikai[4].Y + 200, 2, cgTestimony[gameChapter][4][0],150, sePinkLaugh},

	// �l�i�G���F��2�u���������Ă��������v
	{ 3, 2,  965, gikai[3].X,       gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][0],  150, seBlueLaugh},
	{ 3, 2,  980, gikai[3].X + 120, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][1],  145,},
	{ 3, 2,  995, gikai[3].X + 240, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][2],  145},
	{ 3, 2, 1010, gikai[3].X + 360, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][1][3],  145},
	{ 3, 2, 1025, gikai[3].X + 480, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][4],  145},

	// �l�i�G���F��2�u�܂�Ŏ��łˁv
	{ 0, 2,  975, gikai[0].X - 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][0], 150, seRedLaugh},
	{ 0, 2,  985, gikai[0].X - 120, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][1], 155},
	{ 0, 2,  995, gikai[0].X,       gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][2], 160},
	{ 0, 2, 1005, gikai[0].X + 120, gikai[0].Y + 270,1, cgRedThoughtlessWords[chapter][1][3], 165},
	{ 0, 2, 1015, gikai[0].X + 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][4], 170},
	{ 0, 2, 1025, gikai[0].X + 360, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][5], 175},

	// �l�i�G���F��1�u���_�ł��Ȃ��̂ł́v
	{ 2, 2, 1550, gikai[2].X - 600, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][0], 50, seYellowLaugh},
	{ 2, 2, 1555, gikai[2].X - 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][1], 50,},
	{ 2, 2, 1560, gikai[2].X - 360, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][2], 50},
	{ 2, 2, 1565, gikai[2].X - 240, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][0][3], 50},
	{ 2, 2, 1570, gikai[2].X - 120, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][4], 50},
	{ 2, 2, 1575, gikai[2].X,       gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][5], 50},
	{ 2, 2, 1580, gikai[2].X + 120, gikai[2].Y + 280,1, cgYellowThoughtlessWords[chapter][0][6], 50},
	{ 2, 2, 1585, gikai[2].X + 240, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][7], 50},
	{ 2, 2, 1590, gikai[2].X + 360, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][0][8], 50},
	{ 2, 2, 1595, gikai[2].X + 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][9], 50},

	// �l�i�G���F�s���N2�u�M�����P�Ԃ̈������v
	{ 4, 2, 1710, gikai[4].X - 620, gikai[4].Y + 250, 1, cgPinkThoughtlessWords[chapter][1][0], 70, sePinkLaugh},
	{ 4, 2, 1720, gikai[4].X - 500, gikai[4].Y + 250, 1, cgPinkThoughtlessWords[chapter][1][1], 70,},
	{ 4, 2, 1730, gikai[4].X - 380, gikai[4].Y + 250, 1, cgPinkThoughtlessWords[chapter][1][2], 70},
	{ 4, 2, 1740, gikai[4].X - 260, gikai[4].Y + 270, 1, cgPinkThoughtlessWords[chapter][1][3], 70},
	{ 4, 2, 1750, gikai[4].X - 140, gikai[4].Y + 250, 1, cgPinkThoughtlessWords[chapter][1][4], 70},
	{ 4, 2, 1760, gikai[4].X -  20, gikai[4].Y + 250, 1, cgPinkThoughtlessWords[chapter][1][5], 70},
	{ 4, 2, 1770, gikai[4].X + 100, gikai[4].Y + 280, 1, cgPinkThoughtlessWords[chapter][1][6], 70},

	// �،��F�ԁu�����n�����o�����󂢂�v
	{ 0, 0, 1800,            gikai[0].X, gikai[0].Y + 200,2, cgTestimony[gameChapter][0][0], 50, seRedLaugh},

	{ 5, 3, 2200, 0, 0, -1 },	//�V�i���I���[�v
	{ 5, 3, -1 },	// �Ō��gamecnt = -1
	};

	//�`���v�^�[2�V�i���I
	SCENARIO scenario2[] = {
	// �l�i�G���F�ԁu�߂��C��t���Ȃ��Łv
	{ 0, 2,   50, gikai[0].X - 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][0], 70, seRedLaugh},
	{ 0, 2,   60, gikai[0].X - 120, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][1], 75},
	{ 0, 2,   70, gikai[0].X,       gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][2], 80},
	{ 0, 2,   80, gikai[0].X + 120, gikai[0].Y + 270,1, cgRedThoughtlessWords[chapter][0][3], 85},
	{ 0, 2,   90, gikai[0].X + 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][4], 90},
	{ 0, 2,  100, gikai[0].X + 360, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][5], 95},
	{ 0, 2,  110, gikai[0].X + 480, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][6], 100},
	{ 0, 2,  120, gikai[0].X + 600, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][7], 105},
	{ 0, 2,  130, gikai[0].X + 720, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][8], 110},

	// �l�i�G���F���u����ȏ�͖��Ӗ����Ɓv
	{ 2, 2,  270, gikai[2].X - 600, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][0], 100, seYellowLaugh},
	{ 2, 2,  280, gikai[2].X - 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][1], 100,},
	{ 2, 2,  290, gikai[2].X - 360, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][2], 100},
	{ 2, 2,  300, gikai[2].X - 240, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][0][3], 100},
	{ 2, 2,  310, gikai[2].X - 120, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][4], 100},
	{ 2, 2,  320, gikai[2].X      , gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][5], 100},
	{ 2, 2,  330, gikai[2].X + 120, gikai[2].Y + 280,1, cgYellowThoughtlessWords[chapter][0][6], 100},
	{ 2, 2,  340, gikai[2].X + 240, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][7], 100},
	{ 2, 2,  350, gikai[2].X + 360, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][0][8], 100},
	{ 2, 2,  360, gikai[2].X + 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][9], 100},

	// �،��F���u�����͊m���ɍs��ꂽ�v
	{ 2, 0,  470, gikai[2].X,       gikai[2].Y + 200,2, cgTestimony[chapter][2][0],               50, seYellowLaugh},

	// �l�i�G���F�u����Ȃ��v
	{ 3, 2,  470, gikai[3].X - 120, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][0],   70, seBlueLaugh},
	{ 3, 2,  475, gikai[3].X,       gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][1],   70,},
	{ 3, 2,  480, gikai[3].X + 120, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][2],  195},
	{ 3, 2,  485, gikai[3].X + 240, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][0][3],  195},

	// �،��F�u�w����o�Ă��܂����ˁv
	{ 3, 0,  670, gikai[3].X,       gikai[3].Y + 200,2, cgTestimony[chapter][3][0],             30, seBlueLaugh},

	// �l�i�G���F�s���N�u�����I���H�v
	{ 4, 2,  890, gikai[4].X - 600, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][0],   70, sePinkLaugh},
	{ 4, 2,  900, gikai[4].X - 480, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][1],   70,},
	{ 4, 2,  910, gikai[4].X - 360, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][2],  180},
	{ 4, 2,  920, gikai[4].X - 240, gikai[4].Y + 270,1, cgPinkThoughtlessWords[chapter][0][3],  180},
	{ 4, 2,  930, gikai[4].X - 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][4],  180},
	{ 4, 2,  940, gikai[4].X      , gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][5],  180},

	// �،��F�ԁu���͂�����΂��ݏ����������ˁv
	{ 0, 0,  890, gikai[0].X,       gikai[0].Y + 200,2, cgTestimony[chapter][3][0],             50, seRedLaugh},

	// �،��F�΁u�i�C�t������Ȃɐ[�X�Ɓv
	{ 1, 0, 1160, gikai[1].X,       gikai[1].Y + 200,2, cgTestimony[chapter][1][0],             50, seGreenLaugh},

	// �l�i�G���F�΁u�c���Ȑl�v
	{ 1, 2, 1360, gikai[1].X - 120, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][0], 10, seGreenLaugh},
	{ 1, 2, 1362, gikai[1].X      , gikai[1].Y + 280,1, cgGreenThoughtlessWords[chapter][0][1], 10},
	{ 1, 2, 1364, gikai[1].X + 120, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][2], 10},
	{ 1, 2, 1366, gikai[1].X + 240, gikai[1].Y + 270,1, cgGreenThoughtlessWords[chapter][0][3], 10},

	{ 5, 3, 1700, 0, 0, -1 }, //�V�i���I���[�v
	{ 5, 3, -1 },	// �Ō��gamecnt = -1
	};

	//�`���v�^�[3�V�i���I
	SCENARIO scenario3[] = {

	// �l�i�G���F��2�u�����M����ȁv
	{ 3, 2,   50, gikai[3].X - 840, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][0],  50, seBlueLaugh },
	{ 3, 2,   55, gikai[3].X - 720, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][1],  50},
	{ 3, 2,   60, gikai[3].X - 600, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][2],  50},
	{ 3, 2,   65, gikai[3].X - 480, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][1][3],  50},
	{ 3, 2,   70, gikai[3].X - 360, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][4],  50},
	{ 3, 2,   75, gikai[3].X - 240, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][5],  50},
	{ 3, 2,   80, gikai[3].X - 120, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][1][6],  50},
	{ 3, 2,   85, gikai[3].X,       gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][7],  50},


	// �l�i�G���F��3�u�����͕���Ȃ��v
	{ 3, 2,  150, gikai[3].X - 840, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][2][0],  15, seBlueLaugh },
	{ 3, 2,  152, gikai[3].X - 720, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][2][1],  15},
	{ 3, 2,  154, gikai[3].X - 600, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][2][2],  15},
	{ 3, 2,  156, gikai[3].X - 480, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][2][3],  15},
	{ 3, 2,  158, gikai[3].X - 360, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][2][4],  15},
	{ 3, 2,  160, gikai[3].X - 240, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][2][5],  15},
	{ 3, 2,  162, gikai[3].X - 120, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][2][6],  15},

	// �l�i�G���F��3�u���̃A�I�C��y���c�v
	{ 0, 2,  230, gikai[0].X - 240, gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][2][0], 130, seRedLaugh},
	{ 0, 2,  235, gikai[0].X - 120, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][2][1], 130},
	{ 0, 2,  240, gikai[0].X,       gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][2][2], 130},
	{ 0, 2,  245, gikai[0].X + 120, gikai[0].Y + 270, 1, cgRedThoughtlessWords[chapter][2][3], 130},
	{ 0, 2,  250, gikai[0].X + 240, gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][2][4], 130},
	{ 0, 2,  255, gikai[0].X + 360, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][2][5], 130},
	{ 0, 2,  260, gikai[0].X + 480, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][2][6], 130},
	{ 0, 2,  265, gikai[0].X + 600, gikai[0].Y + 250, 1, cgRedThoughtlessWords[chapter][2][7], 130},
	{ 0, 2,  270, gikai[0].X + 720, gikai[0].Y + 280, 1, cgRedThoughtlessWords[chapter][2][8], 130},

	// �l�i�G���F��1�u���[���v
	{ 1, 2,  420, gikai[1].X - 120, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][0], 40, seGreenLaugh},
	{ 1, 2,  420, gikai[1].X,           gikai[1].Y + 280,1, cgGreenThoughtlessWords[chapter][0][1], 40},
	{ 1, 2,  420, gikai[1].X + 120, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][2], 40},

	// �l�i�G���F�s���N1�u�����܂�Ȃ��v
	{ 4, 2,  500, gikai[4].X - 600, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][0], 70, sePinkLaugh},
	{ 4, 2,  510, gikai[4].X - 480, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][1], 70},
	{ 4, 2,  520, gikai[4].X - 360, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][2], 70},
	{ 4, 2,  530, gikai[4].X - 240, gikai[4].Y + 270,1, cgPinkThoughtlessWords[chapter][0][3], 70},
	{ 4, 2,  540, gikai[4].X - 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][4], 70},
	{ 4, 2,  550, gikai[4].X,       gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][5], 70},
	{ 4, 2,  560, gikai[4].X + 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][6], 70},

	// �l�i�G���F��2�u�撣����������ˁv
	{ 1, 2,  575, gikai[1].X - 120,  gikai[1].Y + 250, 1, cgGreenThoughtlessWords[chapter][1][0], 80, seGreenLaugh},
	{ 1, 2,  585, gikai[1].X,           gikai[1].Y + 280, 1, cgGreenThoughtlessWords[chapter][1][1], 80},
	{ 1, 2,  595, gikai[1].X + 120, gikai[1].Y + 250, 1, cgGreenThoughtlessWords[chapter][1][2], 80},
	{ 1, 2,  605, gikai[1].X + 240, gikai[1].Y + 250, 1, cgGreenThoughtlessWords[chapter][1][3], 80},
	{ 1, 2,  615, gikai[1].X + 360, gikai[1].Y + 280, 1, cgGreenThoughtlessWords[chapter][1][4], 80},
	{ 1, 2,  625, gikai[1].X + 480, gikai[1].Y + 250, 1, cgGreenThoughtlessWords[chapter][1][5], 80},
	{ 1, 2,  635, gikai[1].X + 600, gikai[1].Y + 250, 1, cgGreenThoughtlessWords[chapter][1][6], 80},
	{ 1, 2,  645, gikai[1].X + 720, gikai[1].Y + 280, 1, cgGreenThoughtlessWords[chapter][1][7], 80},

	// �l�i�G���F��1�u�֌W�Ȃ����Ƃ΂���v
	{ 0, 2,  765, gikai[0].X - 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][0],  180, seRedLaugh},
	{ 0, 2,  785, gikai[0].X - 120, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][1],  160},
	{ 0, 2,  805, gikai[0].X      , gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][2],  180},
	{ 0, 2,  825, gikai[0].X + 120, gikai[0].Y + 270,1, cgRedThoughtlessWords[chapter][0][3],  160},
	{ 0, 2,  845, gikai[0].X + 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][4],  180},
	{ 0, 2,  865, gikai[0].X + 360, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][5],  160},
	{ 0, 2,  885, gikai[0].X + 480, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][6],  180},
	{ 0, 2,  905, gikai[0].X + 600, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][7],  160},
	{ 0, 2,  925, gikai[0].X + 720, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][8],  140},

	// �l�i�G���F�s���N3�u������΂���v
	{ 4, 2,  870, gikai[4].X - 360, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][2][0],  35, sePinkLaugh },
	{ 4, 2,  875, gikai[4].X - 240, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][2][1],  30 },
	{ 4, 2,  880, gikai[4].X - 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][2][2],  25 },
	{ 4, 2,  885, gikai[4].X ,      gikai[4].Y + 270,1, cgPinkThoughtlessWords[chapter][2][3],  20 },
	{ 4, 2,  895, gikai[4].X + 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][2][5],  10 },
	{ 4, 2,  900, gikai[4].X + 240, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][2][6],  5 },

	// �l�i�G���F��1�u�Y���͕����O���܂����v
	{ 3, 2, 1120, gikai[3].X - 840, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][0],  120, seBlueLaugh},
	{ 3, 2, 1130, gikai[3].X - 720, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][1],  120},
	{ 3, 2, 1140, gikai[3].X - 600, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][2],  120},
	{ 3, 2, 1150, gikai[3].X - 480, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][0][3],  120},
	{ 3, 2, 1160, gikai[3].X - 360, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][4],  120},
	{ 3, 2, 1170, gikai[3].X - 240, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][5],  120},
	{ 3, 2, 1180, gikai[3].X - 120, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][0][6],  120},
	{ 3, 2, 1190, gikai[3].X      , gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][7],  120},
	{ 3, 2, 1200, gikai[3].X + 120, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][8],  120},
	{ 3, 2, 1210, gikai[3].X + 240, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][0][9],  120},

	// �l�i�G���F��3�u�����܌�墂��v
	{ 2, 2, 1390, gikai[2].X - 600, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][2][0], 70, seYellowLaugh},
	{ 2, 2, 1400, gikai[2].X - 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][2][1], 75},
	{ 2, 2, 1410, gikai[2].X - 360, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][2][2], 85},
	{ 2, 2, 1420, gikai[2].X - 240, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][2][3], 90},
	{ 2, 2, 1430, gikai[2].X - 120, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][2][4], 95},
	{ 2, 2, 1440, gikai[2].X      , gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][2][5], 100},

	// �l�i�G���F��1�u�ǂ��Ȃ�̂�����ˁv
	{ 2, 2, 1570, gikai[2].X - 600, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][0],  30, seYellowLaugh},
	{ 2, 2, 1572, gikai[2].X - 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][1],  30},
	{ 2, 2, 1574, gikai[2].X - 360, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][2],  30},
	{ 2, 2, 1576, gikai[2].X - 240, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][0][3],  30},
	{ 2, 2, 1578, gikai[2].X - 120, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][4],  30},
	{ 2, 2, 1580, gikai[2].X      , gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][5],  30},
	{ 2, 2, 1582, gikai[2].X + 120, gikai[2].Y + 280,1, cgYellowThoughtlessWords[chapter][0][6],  30},
	{ 2, 2, 1584, gikai[2].X + 240, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][7],  30},
	{ 2, 2, 1586, gikai[2].X + 360, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][0][8],  30},

	// �l�i�G���F��2�u�b����炷�̂����ˁv
	{ 0, 2, 1670, gikai[0].X - 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][0],  140, seRedLaugh},
	{ 0, 2, 1675, gikai[0].X - 120, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][1],  140},
	{ 0, 2, 1680, gikai[0].X      , gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][2],  140},
	{ 0, 2, 1685, gikai[0].X + 120, gikai[0].Y + 270,1, cgRedThoughtlessWords[chapter][1][3],  140},
	{ 0, 2, 1690, gikai[0].X + 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][4],  140},
	{ 0, 2, 1695, gikai[0].X + 360, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][5],  140},
	{ 0, 2, 1700, gikai[0].X + 480, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][6],  140},
	{ 0, 2, 1705, gikai[0].X + 600, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][7],  140},
	{ 0, 2, 1710, gikai[0].X + 720, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][8],  140},
	{ 0, 2, 1715, gikai[0].X + 840, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][9],  140},

	// �l�i�G���F��2�u�����ɂł͂Ȃ���ł��v
	{ 2, 2, 1880, gikai[2].X - 600, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][0], 100, seYellowLaugh},
	{ 2, 2, 1890, gikai[2].X - 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][1],  90,},
	{ 2, 2, 1900, gikai[2].X - 360, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][2], 100},
	{ 2, 2, 1910, gikai[2].X - 240, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][1][3],  90},
	{ 2, 2, 1920, gikai[2].X - 120, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][4],  80},
	{ 2, 2, 1930, gikai[2].X      , gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][5], 100},
	{ 2, 2, 1940, gikai[2].X + 120, gikai[2].Y + 280,1, cgYellowThoughtlessWords[chapter][1][6],  90},
	{ 2, 2, 1950, gikai[2].X + 240, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][7],  80},
	{ 2, 2, 1960, gikai[2].X + 360, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][1][8],  70},
	{ 2, 2, 1970, gikai[2].X + 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][9],  60},

	// �l�i�G���F�s���N2�u���ԕԂ��Ă�v
	{ 4, 2, 2100, gikai[4].X - 360, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][0],  30, sePinkLaugh },
	{ 4, 2, 2102, gikai[4].X - 240, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][1],  28},
	{ 4, 2, 2104, gikai[4].X - 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][2],  26},
	{ 4, 2, 2106, gikai[4].X,       gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][3],  24},
	{ 4, 2, 2108, gikai[4].X + 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][4],  22},
	{ 4, 2, 2110, gikai[4].X + 240, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][5],  20},

	// �l�i�G���F��3�u���������Ă����H�v
	{ 1, 2, 2130, gikai[1].X - 120, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][2][0], 70, seGreenLaugh},
	{ 1, 2, 2140, gikai[1].X,       gikai[1].Y + 280,1, cgGreenThoughtlessWords[chapter][2][1], 75},
	{ 1, 2, 2150, gikai[1].X + 120, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][2][2], 80},
	{ 1, 2, 2160, gikai[1].X + 240, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][2][3], 70},
	{ 1, 2, 2170, gikai[1].X + 360, gikai[1].Y + 280,1, cgGreenThoughtlessWords[chapter][2][4], 75},
	{ 1, 2, 2180, gikai[1].X + 480, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][2][5], 80},
	{ 1, 2, 2190, gikai[1].X + 600, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][2][6], 70},
	{ 1, 2, 2200, gikai[1].X + 720, gikai[1].Y + 280,1, cgGreenThoughtlessWords[chapter][2][7], 75},
	{ 1, 2, 2210, gikai[1].X + 840, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][2][8], 80},

	{ 5, 3, 2800, 0, 0, -1 }, //�V�i���I���[�v
	{ 5, 3, -1 },	// �Ō��gamecnt = -1
	};

	//�`���v�^�[4�V�i���I
	SCENARIO scenario4[] = {
	// �،��F��1�u�܊��݂Ǝ����Ɋ֘A���͂Ȃ���v
	{ 1, 0,   50, gikai[1].X,       gikai[2].Y + 200,2, cgTestimony[chapter][1][0],             50, seGreenLaugh },

	// �l�i�G���F�s���N1�u���񂽂��I��肾�i��j�v
	{ 4, 2,  105, gikai[4].X - 600, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][0],  20, sePinkLaugh},
	{ 4, 2,  107, gikai[4].X - 480, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][1],  18},
	{ 4, 2,  109, gikai[4].X - 360, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][2],  16},
	{ 4, 2,  111, gikai[4].X - 240, gikai[4].Y + 270,1, cgPinkThoughtlessWords[chapter][0][3],  14},
	{ 4, 2,  113, gikai[4].X - 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][4],  12},
	{ 4, 2,  115, gikai[4].X      , gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][5],  10},
	{ 4, 2,  117, gikai[4].X + 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][6],   8},
	{ 4, 2,  119, gikai[4].X + 240, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][0][7],   6},

	// �l�i�G���F��1�u��y���^���Ȃ�āv
	{ 0, 2,  170, gikai[0].X - 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][0],  100, seRedLaugh},
	{ 0, 2,  180, gikai[0].X - 120, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][1],  100},
	{ 0, 2,  190, gikai[0].X      , gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][2],  100},
	{ 0, 2,  200, gikai[0].X + 120, gikai[0].Y + 270,1, cgRedThoughtlessWords[chapter][0][3],  100},
	{ 0, 2,  210, gikai[0].X + 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][4],  100},
	{ 0, 2,  220, gikai[0].X + 360, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][5],  100},
	{ 0, 2,  230, gikai[0].X + 480, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][0][6],  100},
	{ 0, 2,  240, gikai[0].X + 600, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][0][7],  100},

	// �l�i�G���F��1�u�����ɍ������Ȃ��ł��v
	{ 3, 2,  360, gikai[3].X - 840, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][0],  80, seBlueLaugh},
	{ 3, 2,  362, gikai[3].X - 720, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][1],  78},
	{ 3, 2,  364, gikai[3].X - 600, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][2],  76},
	{ 3, 2,  366, gikai[3].X - 480, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][0][3],  74},
	{ 3, 2,  368, gikai[3].X - 360, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][4],  72},
	{ 3, 2,  370, gikai[3].X - 240, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][5],  70},
	{ 3, 2,  372, gikai[3].X - 120, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][0][6],  68},
	{ 3, 2,  374, gikai[3].X      , gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][7],  66},
	{ 3, 2,  376, gikai[3].X + 120, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][0][8],  64},
	{ 3, 2,  378, gikai[3].X + 240, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][0][9],  62},

	// �l�i�G���F��1�u�N���[�����Ȃ���v
	{ 1, 2,  475, gikai[1].X - 120, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][0], 50, seGreenLaugh},
	{ 1, 2,  477, gikai[1].X      , gikai[1].Y + 280,1, cgGreenThoughtlessWords[chapter][0][1], 48},
	{ 1, 2,  479, gikai[1].X + 120, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][2], 46},
	{ 1, 2,  481, gikai[1].X + 240, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][3], 44},
	{ 1, 2,  483, gikai[1].X + 360, gikai[1].Y + 280,1, cgGreenThoughtlessWords[chapter][0][4], 42},
	{ 1, 2,  485, gikai[1].X + 480, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][5], 40},
	{ 1, 2,  487, gikai[1].X + 600, gikai[1].Y + 250,1, cgGreenThoughtlessWords[chapter][0][6], 38},
	{ 1, 2,  489, gikai[1].X + 720, gikai[1].Y + 280,1, cgGreenThoughtlessWords[chapter][0][7], 36},

	// �l�i�G���F��2�u�M���������܂ł�����v
	{ 2, 2,  660, gikai[2].X - 600, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][0],  70, seYellowLaugh},
	{ 2, 2,  665, gikai[2].X - 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][1],  70,},
	{ 2, 2,  670, gikai[2].X - 360, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][2],  70},
	{ 2, 2,  675, gikai[2].X - 240, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][1][3],  70},
	{ 2, 2,  680, gikai[2].X - 120, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][4],  70},
	{ 2, 2,  685, gikai[2].X      , gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][5],  70},
	{ 2, 2,  690, gikai[2].X + 120, gikai[2].Y + 280,1, cgYellowThoughtlessWords[chapter][1][6],  70},
	{ 2, 2,  695, gikai[2].X + 240, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][7], 160},
	{ 2, 2,  700, gikai[2].X + 360, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][1][8], 160},
	{ 2, 2,  705, gikai[2].X + 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][1][9], 160},

	// �،��F�s���N�u���͈����Ȃ��I�v
	{ 4, 0,  650, gikai[4].X + 60,  gikai[4].Y + 200,2, cgTestimony[chapter][4][0],             50, sePinkLaugh },

	// �l�i�G���F�s���N2�u�����ׂꂽ�����v
	{ 4, 2,  900, gikai[4].X - 600, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][0],  50, sePinkLaugh },
	{ 4, 2,  905, gikai[4].X - 480, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][1],  50 },
	{ 4, 2,  910, gikai[4].X - 360, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][2],  50 },
	{ 4, 2,  915, gikai[4].X - 240, gikai[4].Y + 270,1, cgPinkThoughtlessWords[chapter][1][3],  50 },
	{ 4, 2,  920, gikai[4].X - 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][4],  50 },
	{ 4, 2,  925, gikai[4].X      , gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][5],  50 },
	{ 4, 2,  930, gikai[4].X + 120, gikai[4].Y + 250,1, cgPinkThoughtlessWords[chapter][1][6],  50 },

	// �l�i�G���F��2�u���t���o�i�Ă��j�Ȃ��̂ˁv
	{ 0, 2,  905, gikai[0].X - 240, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][0],  70, seRedLaugh},
	{ 0, 2,  915, gikai[0].X - 120, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][1],  70},
	{ 0, 2,  925, gikai[0].X      , gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][2],  70},
	{ 0, 2,  935, gikai[0].X + 120, gikai[0].Y + 270,1, cgRedThoughtlessWords[chapter][1][3],  70},
	{ 0, 2,  945, gikai[0].X + 240, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][6],  70},
	{ 0, 2,  955, gikai[0].X + 360, gikai[0].Y + 250,1, cgRedThoughtlessWords[chapter][1][7],  70},
	{ 0, 2,  965, gikai[0].X + 480, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][8],  70},
	{ 0, 2,  975, gikai[0].X + 600, gikai[0].Y + 280,1, cgRedThoughtlessWords[chapter][1][9],  70},

	// �l�i�G���F��1�u���낻��I��肩����v
	{ 2, 2, 1150, gikai[2].X - 600, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][0],  70, seYellowLaugh},
	{ 2, 2, 1160, gikai[2].X - 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][1],  70},
	{ 2, 2, 1170, gikai[2].X - 360, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][2],  70},
	{ 2, 2, 1180, gikai[2].X - 240, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][0][3],  70},
	{ 2, 2, 1190, gikai[2].X - 120, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][4],  70},
	{ 2, 2, 1200, gikai[2].X      , gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][5],  70},
	{ 2, 2, 1210, gikai[2].X + 120, gikai[2].Y + 280,1, cgYellowThoughtlessWords[chapter][0][6],  70},
	{ 2, 2, 1220, gikai[2].X + 240, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][7],  70},
	{ 2, 2, 1230, gikai[2].X + 360, gikai[2].Y + 270,1, cgYellowThoughtlessWords[chapter][0][8],  70},
	{ 2, 2, 1240, gikai[2].X + 480, gikai[2].Y + 250,1, cgYellowThoughtlessWords[chapter][0][9],  70},

	// �،��F��2�u���ƋM���ɐړ_�͂���܂���v
	{ 1, 1, 1250, gikai[1].X,       gikai[2].Y + 200,2, cgTestimony[chapter][1][1],             30, seGreenLaugh },

	// �،��F�u�M�Ղ͈�v���Ă��邪
	{ 3, 0, 1400, gikai[3].X,       gikai[3].Y + 200,2, cgTestimony[chapter][3][0],             30,seBlueLaugh },

	// �l�i�G���F��2�u(���܂��)���������Ȃ��v
	{ 3, 2, 1490, gikai[3].X - 240, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][4], 12, seBlueLaugh },
	{ 3, 2, 1492, gikai[3].X - 120, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][5], 10},
	{ 3, 2, 1494, gikai[3].X ,      gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][1][6],  8},
	{ 3, 2, 1496, gikai[3].X + 120, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][7],  6},
	{ 3, 2, 1498, gikai[3].X + 240, gikai[3].Y + 250,1, cgBlueThoughtlessWords[chapter][1][8],  4},
	{ 3, 2, 1500, gikai[3].X + 360, gikai[3].Y + 270,1, cgBlueThoughtlessWords[chapter][1][9],  2},

	{ 5, 3, 1820, 0, 0, -1 }, //�V�i���I���[�v
	{ 5, 3, -1 },	// �Ō��gamecnt = -1
	};

	//�����c�_�V�i���I
	SCENARIO scenario5[] = {
	// �،�1�F�u�i�C�t�͎��̕��������v
	{ 1, 0,   60, gikai[2].X,       gikai[2].Y + 300,2,cgTestimony[chapter][1][0],               180},

	// �l�i�G���F�u�v�l���~�߂�v
	{ 2, 2,  100, gikai[2].X - 740, gikai[2].Y + 380,1,cgSetsunaThoughtlessWords[chapter][4][0], 170,seSetsunaRough},
	{ 2, 2,  110, gikai[2].X - 620, gikai[2].Y + 400,1,cgSetsunaThoughtlessWords[chapter][4][1], 160},
	{ 2, 2,  120, gikai[2].X - 500, gikai[2].Y + 390,1,cgSetsunaThoughtlessWords[chapter][4][2], 150},
	{ 2, 2,  130, gikai[2].X - 380, gikai[2].Y + 410,1,cgSetsunaThoughtlessWords[chapter][4][3], 140},
	{ 2, 2,  140, gikai[2].X - 260, gikai[2].Y + 380,1,cgSetsunaThoughtlessWords[chapter][4][4], 130},
	{ 2, 2,  150, gikai[2].X - 140, gikai[2].Y + 400,1,cgSetsunaThoughtlessWords[chapter][4][5], 120},

	// �l�i�G���F�u�l����ȁv
	{ 2, 2,  170, gikai[2].X + 360, gikai[2].Y - 50,1,cgSetsunaThoughtlessWords[chapter][2][0], 40,seSetsunaRough},
	{ 2, 2,  180, gikai[2].X + 480, gikai[2].Y - 50,1,cgSetsunaThoughtlessWords[chapter][2][1], 40},
	{ 2, 2,  190, gikai[2].X + 600, gikai[2].Y - 50,1,cgSetsunaThoughtlessWords[chapter][2][2], 40},
	{ 2, 2,  200, gikai[2].X + 720, gikai[2].Y - 50,1,cgSetsunaThoughtlessWords[chapter][2][3], 40},

	// �l�i�G���F�u�^���ȂǂȂ��v
	{ 2, 2,  220, gikai[2].X - 720, gikai[2].Y ,1,cgSetsunaThoughtlessWords[chapter][3][0], 140,seSetsunaRough},
	{ 2, 2,  230, gikai[2].X - 600, gikai[2].Y ,1,cgSetsunaThoughtlessWords[chapter][3][1], 140},
	{ 2, 2,  240, gikai[2].X - 480, gikai[2].Y ,1,cgSetsunaThoughtlessWords[chapter][3][2], 140},
	{ 2, 2,  250, gikai[2].X - 360, gikai[2].Y ,1,cgSetsunaThoughtlessWords[chapter][3][3], 140},
	{ 2, 2,  260, gikai[2].X - 240, gikai[2].Y ,1,cgSetsunaThoughtlessWords[chapter][3][4], 140,seSetsunaRough},
	{ 2, 2,  270, gikai[2].X - 120, gikai[2].Y ,1,cgSetsunaThoughtlessWords[chapter][3][5], 140},

	// �l�i�G���F�u�I��点��v
	{ 2, 2,  280, gikai[2].X + 240, gikai[2].Y + 200,1,cgSetsunaThoughtlessWords[chapter][1][0], 160,seSetsunaRough},
	{ 2, 2,  290, gikai[2].X + 360, gikai[2].Y + 200,1,cgSetsunaThoughtlessWords[chapter][1][1], 160},
	{ 2, 2,  300, gikai[2].X + 480, gikai[2].Y + 200,1,cgSetsunaThoughtlessWords[chapter][1][2], 160},
	{ 2, 2,  310, gikai[2].X + 600, gikai[2].Y + 200,1,cgSetsunaThoughtlessWords[chapter][1][3], 160,seSetsunaRough},
	{ 2, 2,  320, gikai[2].X + 720, gikai[2].Y + 200,1,cgSetsunaThoughtlessWords[chapter][1][4], 160},

	// �،�2�F�u�����V�I���͎E���ꂽ�v
	{ 0, 0,  325, gikai[2].X - 480, gikai[2].Y + 200,2,cgTestimony[chapter][0][0],               175,seSetsunaRough},

	// �l�i�G���F�u��߂āv
	{ 2, 2,  330, gikai[2].X - 720, gikai[2].Y + 400,1,cgSetsunaThoughtlessWords[chapter][6][0], 185,seSetsunaRough},
	{ 2, 2,  350, gikai[2].X - 600, gikai[2].Y + 400,1,cgSetsunaThoughtlessWords[chapter][6][1], 165},
	{ 2, 2,  370, gikai[2].X - 480, gikai[2].Y + 400,1,cgSetsunaThoughtlessWords[chapter][6][2], 145,seSetsunaRough},


	// �l�i�G���F�u�l����ȁv
	{ 2, 2,  500, gikai[2].X - 180, gikai[2].Y + 290,1,cgSetsunaThoughtlessWords[chapter][2][0], 60,seSetsunaRough},
	{ 2, 2,  510, gikai[2].X -  60, gikai[2].Y + 310,1,cgSetsunaThoughtlessWords[chapter][2][1], 50,},
	{ 2, 2,  520, gikai[2].X +  60, gikai[2].Y + 300,1,cgSetsunaThoughtlessWords[chapter][2][2], 40,},
	{ 2, 2,  530, gikai[2].X + 180, gikai[2].Y + 320,1,cgSetsunaThoughtlessWords[chapter][2][3], 30,seSetsunaRough},

	// �،�3�F�u�����͎h�E����Ȃ��v
	{ 3, 0,  540, gikai[2].X + 480, gikai[2].Y + 250,2,cgTestimony[chapter][3][0],               15,seSetsunaRough},

	// �l�i�G���F�u�I��肽���v
	{ 2, 2,  540, gikai[2].X - 700, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][0][0], 70,seSetsunaRough},
	{ 2, 2,  540, gikai[2].X - 540, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][0][1], 75},
	{ 2, 2,  540, gikai[2].X - 380, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][0][2], 80},
	{ 2, 2,  540, gikai[2].X - 220, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][0][3], 85},
	{ 2, 2,  540, gikai[2].X -  60, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][0][4], 90},

	// �l�i�G���F�u��߂āv
	{ 2, 2,  600, gikai[2].X + 360, gikai[2].Y + 250,1,cgSetsunaThoughtlessWords[chapter][6][0], 180,seSetsunaRough},
	{ 2, 2,  610, gikai[2].X + 480, gikai[2].Y + 270,1,cgSetsunaThoughtlessWords[chapter][6][1], 170,},
	{ 2, 2,  620, gikai[2].X + 600, gikai[2].Y + 260,1,cgSetsunaThoughtlessWords[chapter][6][2], 160,},

	// �l�i�G���F�u�v�l���~�߂�v
	{ 2, 2,  620, gikai[2].X + 240, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][4][0], 5,},
	{ 2, 2,  625, gikai[2].X + 360, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][4][1], 5,},
	{ 2, 2,  630, gikai[2].X + 480, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][4][2], 5,seSetsunaRough},
	{ 2, 2,  635, gikai[2].X + 600, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][4][3], 5,},
	{ 2, 2,  640, gikai[2].X + 720, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][4][4], 5,},
	{ 2, 2,  645, gikai[2].X + 840, gikai[2].Y - 220,1,cgSetsunaThoughtlessWords[chapter][4][5], 5,seSetsunaRough},

	// �،�4�F�u��؃`�O�T�͍��胆�E���D���v
	{ 4, 0,  730, gikai[2].X - 600, gikai[2].Y + 250,2,cgTestimony[chapter][4][0],               30,seSetsunaRough},

	// �،�5�F�u��؃`�O�T���Ɛl���v
	{ 2, 0, 1080, gikai[2].X,       gikai[2].Y + 200,2,cgTestimony[chapter][2][0],               550,},

	// �l�i�G���F�u���O�͊Ԉ���Ă���v
	{ 2, 2, 1190, gikai[2].X - 480, gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][0], 170,},
	{ 2, 2, 1190, gikai[2].X - 360, gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][1], 170},
	{ 2, 2, 1190, gikai[2].X - 240, gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][2], 170},
	{ 2, 2, 1190, gikai[2].X - 120, gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][3], 170},
	{ 2, 2, 1190, gikai[2].X ,      gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][4], 170},
	{ 2, 2, 1190, gikai[2].X + 120, gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][5], 170},
	{ 2, 2, 1190, gikai[2].X + 240, gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][6], 170},
	{ 2, 2, 1190, gikai[2].X + 360, gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][7], 170},
	{ 2, 2, 1190, gikai[2].X + 480, gikai[2].Y + 350,1,cgSetsunaThoughtlessWords[chapter][5][8], 170},

	// �l�i�G���F�u�I��点��v
	{ 2, 2, 1305, gikai[2].X - 240, gikai[2].Y + 500,1,cgSetsunaThoughtlessWords[chapter][1][0], 225,},
	{ 2, 2, 1305, gikai[2].X - 120, gikai[2].Y + 500,1,cgSetsunaThoughtlessWords[chapter][1][1], 225},
	{ 2, 2, 1305, gikai[2].X ,      gikai[2].Y + 500,1,cgSetsunaThoughtlessWords[chapter][1][2], 225},
	{ 2, 2, 1305, gikai[2].X + 120, gikai[2].Y + 500,1,cgSetsunaThoughtlessWords[chapter][1][3], 225},
	{ 2, 2, 1305, gikai[2].X + 240, gikai[2].Y + 500,1,cgSetsunaThoughtlessWords[chapter][1][4], 225},

	{ 5, 3, 2000, 0, 0, -1 },//�V�i���I���[�v
	{ 5, 3, -1 },	// �Ō��gamecnt = -1
	};

	int i = 0;
	
	//�`���v�^�[�ɉ��������g���Q�[���V�[���p�̃V�i���I�ɓ����
	switch (chapter)
	{
	case 0:
		AddScenario(scenario0, sizeof(scenario0) / sizeof(scenario0[0]));
		break;
	case 1:
		AddScenario(scenario1, sizeof(scenario1) / sizeof(scenario1[0]));
		break;
	case 2:
		AddScenario(scenario2, sizeof(scenario2) / sizeof(scenario2[0]));
		break;
	case 3:
		AddScenario(scenario3, sizeof(scenario3) / sizeof(scenario3[0]));
		break;
	case 4:
		AddScenario(scenario4, sizeof(scenario4) / sizeof(scenario4[0]));
		break;
	case 5:
		AddScenario(scenario5, sizeof(scenario5) / sizeof(scenario5[0]));
		break;
	}
}
