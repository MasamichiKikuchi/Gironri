#include "word.h"
#include "winmain.h"
#include "scenegamemain.h"

//�e�r�S���ӏ��@�t�@�C���S��

Word::Word()
{
	
}

Word::~Word() 
{

}

//���t�̈ړ�
void Word::Move(int wordType, int chapter)
{
	//�`���v�^�[���Ƃɐݒ肳�ꂽ���x�œ���
	switch (wordType) {
		case 1://�\��		
			switch (chapter)
			{
				//�`���[�g���A��
				case 0:
					y += THOUGHTLESSWORDS_SPEED_CHAPT0;
					break;
				//�`���v�^�[�P
				case 1:
					y += THOUGHTLESSWORDS_SPEED_CHAPT1;
					break;
				//�`���v�^�[�Q
				case 2:
					y += THOUGHTLESSWORDS_SPEED_CHAPT2;
					break;
				//�`���v�^�[�R
				case 3:
					y += THOUGHTLESSWORDS_SPEED_CHAPT3;
					break;
				//�`���v�^�[�S
				case 4:
					y += THOUGHTLESSWORDS_SPEED_CHAPT4;
					break;
				//�`���v�^�[�T
				case 5:
					y += THOUGHTLESSWORDS_SPEED_CHAPT5;
					break;
			}
		//�����̊g��
		scale += THOUGHTLESSWORDS_SCALE;
		break;

		case 2:	//�،�		
			switch (chapter)
			{
				//�`���[�g���A��
				case 0:
					y += TESTIMONY_SPEED_CHAPT0;
					break;
				//�`���v�^�[�P
				case 1:
					y += TESTIMONY_SPEED_CHAPT1;
					break;
				//�`���v�^�[�Q
				case 2:
					y += TESTIMONY_SPEED_CHAPT2;
					break;
				//�`���v�^�[�R
				case 3:
					y += TESTIMONY_SPEED_CHAPT3;
					break;
				//�`���v�^�[�S
				case 4:
					y += TESTIMONY_SPEED_CHAPT4;
					break;
				//�`���v�^�[�T
				case 5:
					y += TESTIMONY_SPEED_CHAPT5;
					break;
			}
		//�����̊g��
		scale += TESTIMONY_SCALE;
		break;
	}

}

//�g�p�������t�̏���
void Word::EraseWord()
{
	use = 0;
}
