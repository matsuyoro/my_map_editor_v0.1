#if !defined __GLOBALMACRO
#define __GLOBALMACRO
//��������������������������������������������������������������������������������������������������������������
#include <windows.h>	//Windows�p�w�b�_�t�@�C��
#include "define.h"		//�}�N����`���܂Ƃ߂��w�b�_�t�@�C��
#include "GameStruct.h"	//�\���̂̌^�̒�`�w�b�_

//�����ɁA�Q�[���Ŏg���O���ϐ���錾�i�G��HDC��A�L�����A�}�b�v���̃f�[�^�������ϐ��j
HWND hwnd;	//�E�B���h�E�n���h��

HINSTANCE hInst;		//�C���X�^���X�n���h�����R�s�[���Ă����O���ϐ�
HWND hCwnd;				//�q�E�B���h�E�̃n���h��
HWND hMwnd;				//�~�j�}�b�v�E�B���h�E�̃n���h��
JOYINFOEX JoyData;		//JOYINFOEX�^�\���́i���݂̃W���C�X�e�B�b�N�̃f�[�^�j
JOYINFOEX JoyData2;		//�i�O��̃W���C�X�e�B�b�N�̃f�[�^�j
HMENU hMenu;			//���j���[�̃n���h��������
SCROLLINFO HScr;		//�����X�N���[���o�[�p
SCROLLINFO VScr;		//�����X�N���[���o�[�p

HDC hMemDC;		//���z��ʂ�HDC
HDC hMinMemDC;	//�~�j�}�b�v�p���z��ʂ�HDC
HDC hTipDC;		//�}�b�v�`�b�v��HDC

int TipNum;											//�`�b�v�̎�ނ�����
int ToolNum;										//�I�𒆂̋@�\������
int mx,my;											//�}�E�X���W
int MapMx,MapMy;										//�}�b�v�P�ʂł̃}�E�X�̍��W������
int MapMx2,MapMy2;										//�h���b�O�������̃{�^�����������������̃}�E�X�̍��W������
int MapScrX=0,MapScrY=0;							//�}�b�v���X�N���[�������Ƃ���x,y�ɒǉ�					
int map_xnum=MAP_XNUM,map_ynum=MAP_YNUM;			//�}�b�v�̃^�e���R�̃`�b�v��������
int Map[MAP_YNUM][MAP_XNUM];						//�^�eMAP_YNUM���A���RMAP_XNUM���̃}�b�v

int MinW_ScrX = 0;	//�~�j�}�b�v�q�E�B���h�E�̉��X�N���[���ʂ�����
int MinW_ScrY = 0;	//�V�c�X�N���[���ʂ�����

//�G�l�~�[�o���ʒu
struct ENE_ONPOS EneOnPos_Max =	{ENEONPOS_MAX,0,0,FALSE};//�G�l�~�[�o���ʒu��(ENE_ONPOS�^�\���̂̃����o��x���g���ēK�o���ʒu���̐�������
struct ENE_ONPOS EneOn[ENEONPOS_MAX] =	//�G�l�~�[�̏o������|�C���g���P�O�O�܂Őݒ�
{
	{650,400,1,FALSE},				//�G�l�~�[�P��650,400�̃|�C���g�ɏo��������
};
BOOL EneOnTool = FALSE;	//�G�l�~�[�\���@�\�������iTRUE�ŕ\��
int EneOnReturn[ENEONPOS_MAX];	//�G�l�~�[�z�u�����Ԃ��L�^����z��i�O��ݒu�����G�l�~�[��߂������肷��̂Ɏg�p
int EneRtrnCnt = 0;				//EneOnReturn�̗v�f�ԍ������Ɉ����ϐ�
int EneTypeNum = 1;				//�G�l�~�[�̎�ނ�����	

int x,y;			
BOOL Flag = FALSE;	//�������m�ۂ̃t���O
int *pi = NULL;		//�������m�ۂ���ϐ�
//��������������������������������������������������������������������������������������������������������������������
#endif