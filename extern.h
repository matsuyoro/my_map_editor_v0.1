//�O���ϐ����AWinMain()�̂���\�[�X�t�@�C���ȊO�Ŏg�p���邽�߂̃w�b�_�t�@�C��
#if !defined __EXTERNMACRO
#define __EXTERNMACRO
//������������������������������������������������������������������������������������������������������������
#include <windows.h>	//Windows�p�w�b�_�t�@�C��
#include "define.h"		//�}�N����`���܂Ƃ߂��w�b�_�t�@�C��
#include "GameStruct.h"	//�\���̂̌^�̒�`�w�b�_

extern HWND hwnd;	//�E�B���h�E�n���h��

extern HINSTANCE hInst;	//�C���X�^���X�n���h�����R�s�[���Ă����O���ϐ�
extern HWND hCwnd;				//�q�E�B���h�E�̃n���h��
extern HWND hMwnd;				//�~�j�}�b�v�E�B���h�E�̃n���h��
extern JOYINFOEX JoyData;		//JOYINFOEX�^�\���́i���݂̃W���C�X�e�B�b�N�̃f�[�^�j
extern JOYINFOEX JoyData2;		//�i�O��̃W���C�X�e�B�b�N�̃f�[�^�j
extern HMENU hMenu;	//���j���[�̃n���h��������
extern SCROLLINFO HScr;			//�����X�N���[���o�[�p
extern SCROLLINFO VScr;			//�����X�N���[���o�[�p

extern HDC hMemDC;		//���z��ʂ�HDC
extern HDC hMinMemDC;	//�~�j�}�b�v�p���z��ʂ�HDC
extern HDC hTipDC;		//�}�b�v�`�b�v��HDC


extern int TipNum;					//�`�b�v�̎�ނ�����
extern int ToolNum;										//�I�𒆂̋@�\������
extern int mx,my;					//�}�E�X���W
extern int MapMx,MapMy;			//�}�b�v�P�ʂł̃}�E�X�̍��W������
extern int MapMx2,MapMy2;			//�h���b�O�������̃{�^�����������������̃}�E�X�̍��W������
extern int MapScrX,MapScrY;			//
extern int map_xnum,map_ynum;			//�}�b�v�̃^�e���R�̃`�b�v��������
extern int Map[MAP_YNUM][MAP_XNUM];	//�^�eMAP_YNUM���A���RMAP_XNUM��

extern int MinW_ScrX;	//�~�j�}�b�v�q�E�B���h�E�̉��X�N���[���ʂ�����
extern int MinW_ScrY;	//�V�c�X�N���[���ʂ�����


//�G�l�~�[�o���ʒu
extern struct ENE_ONPOS EneOnPos_Max;	//�G�l�~�[�o���ʒu��
extern struct ENE_ONPOS EneOn[ENEONPOS_MAX];	//�G�l�~�[�̏o������|�C���g���P�O�O�܂Őݒ�
extern BOOL EneOnTool;	//�G�l�~�[�\���@�\�������iTRUE�ŕ\��
extern int EneOnReturn[ENEONPOS_MAX];	//�G�l�~�[�z�u�����Ԃ��L�^����z��
extern int EneRtrnCnt;				//EneOnReturn�̗v�f�ԍ������Ɉ����ϐ�
extern int EneTypeNum;				//�G�l�~�[�̎�ނ�����	


extern int x,y;	
extern BOOL Flag;
extern int *pi;
//��������������������������������������������������������������������������������������������������������������������
#endif

