#pragma once
#include <tchar.h>
// �{�v���O�����̑S�ẴI�u�W�F�N�g�̊��N���X
class ObjectBase {
public:
    ObjectBase(); // �R���X�g���N�^
    ObjectBase(const TCHAR* fileName); // �R���X�g���N�^�͈�����ς���Ή��ł��쐬�\
    virtual ~ObjectBase(); // �f�X�g���N�^

    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetW() const { return w; }
    int GetH() const { return h; }

    int x;
    int y;
    int w;
    int h;

protected:
    // protected �ɂ��Čp����N���X�Ŏg�p�\�ɂ���
    // ���L�̃����oh�ϐ����A����̊��ɑ���������ނƐ݌v����
    
};
