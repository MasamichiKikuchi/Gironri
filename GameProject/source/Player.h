#pragma once
#include "ObjectBase.h"
#include "DxLib.h"

#define	NOMAL_DAMAGE		10	//�ʏ��ԂŎ󂯂�_���[�W
#define	SHIELD_DAMAGE		7	//�K�[�h��Ԃ�AT���󂯂�_���[�W
#define	GET_IP		50			//�V�[���h��ԂŎ�ɓ���IP
#define MAX_AT		(50 * 2)		//�ő�AT

#define AT_SPEED		100		//AT�񕜃X�s�[�h
#define AT_INTERVAL		120.0	//AT�񕜃C���^�[�o��

class Player : public ObjectBase {
public:
	Player();
	virtual ~Player();

	void	LifeProcess();		//�̗̓k���k���ύX
	void	CheckPlayerLife();

	float AT;
	
protected:

	
};