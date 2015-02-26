
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "Sprite3D.h"

#else

#include "Base/Sprite3D.h"

#endif

namespace TapGun
{
//���̒�`�͍���قȂ�w�b�_�t�@�C���Ɉڂ��ւ��܂�
#define FALSE -1
#define TRUE 1

	//�G�l�~�[�̍U���^�C�v
	enum _ENEMY_ATK_
	{
		AI_ATK_NONE,//�U�����[�V�������s��Ȃ�
		AI_ATK_FAKE,//�Њd�U�����s��
		AI_ATK_SSHOT,//�����������s��
		AI_ATK_NUM
	};

	//�G�l�~�[�̃A�C�h�����[�V����
	enum _ENEMY_IDLE_
	{
		AI_IDLE_STOP,//���̏�Ŏ~�܂�A�C�h�����[�V����
		AI_IDLE_SIDE,//���E�ɓ����A�C�h�����[�V����
		AI_IDLE_FAKE,//�����[�V�����̘A��
		AI_IDLE_NUM
	};

	//�G�l�~�[�̏o�����@
	enum _ENEMY_APPEAR_
	{
		AI_APPEAR_RUN,//����Ȃ���o��
		AI_APPEAR_SIDE,//������
		AI_APPEAR_NUM
	};


	class Enemy
	{
	public:
		cocos2d::Vec3 standbyPos;//
		cocos2d::Vec3 targetPos;
		
		int SetAI(int idle, int atk, int appear);
		void SetNextEnemy(int num1, int num2, int num3);

		int number;
		int kind;//�G�̎��
		int alive;//�����`�F�b�N
		int nextEnemiesNum[3];//���̓G���������Ƃ��ɁA���ɏo�Ă���G
		int finishFlag;//���̓G��������Ɓi�|���A�܂��͓�����j�ƃE�F�[�u�I���iTRUE/FALSE�j

		int hitpoint;
//		int AIType;

		//
		int AIIdle;
		int AIAtk;
		int AIappear;//�o���p�^�[��

		float atkFrame;//�U���Ԋu�i�b�j
		float waitFrame;//�o�����Ă���ړ����n�߂�܂ł̎���
		float sleepTime;//
	private:

	};
}

#endif // __ENEMY_H__
