//�Q�[���̃��C���������܂Ƃ߂�
#include <windows.h>	//Windows�p�w�b�_�t�@�C��
#include "extern.h"		//WinMain()�ȊO�ŊO���ϐ����g�����߂̃w�b�_�t�@�C��
#include "ImageSetUp.h"	//�A�j���[�V�����֐��̃v���g�^�C�v�錾(CharAnime())
/*------------------------------------------------------------------------------------------------------
�@�@�Q�[���̃��C���������܂Ƃ߂��֐����b�Z�[�W���[�v���APeekMessage��if����else�����Ŏ��s
�@�@�����@�F�@HWND�E�E�E�E�B���h�E�̃n���h��
------------------------------------------------------------------------------------------------------*/
void GameMain(HWND hwnd)
{
	HDC hdc;
	char str[256];	//������������ϐ�
	//int i;			//�J�E���^�ϐ�
	int Dum;		//�\���L�[���r�b�g�P�ʂ̃t���O�ň����i���݂̏\���L�[�������j
	//int Dum2;		//�\���L�[�̃f�[�^������(�O��̏\���L�[�������j
	static int A;	//A�{�^�����������u�ԂɁ{�P�����
	static int B;
	static int C;
	static int D;
	int AniPtnDum;	//CharAnime()�̖ߒl��ۑ����Ă����̎g��
	static int Map[4][5];	//�^�e�S���A���R�T���̃}�b�v
	ZeroMemory(&Map[0][0],sizeof(int)*4*5);	//�ŏ��͑S�ĂO


	//�W���C�X�e�B�b�N�ȂǁA���͂̎擾
	MMRESULT ret;
	JoyData2 = JoyData;							//�O��̒l�Ƃ��āAJoyData��ۑ�
	ret = joyGetPosEx(JOYSTICKID1,&JoyData);	//JoyData�̒��ɃW���C�X�e�B�b�N�̃f�[�^������iJoyData���X�V�j
	if(ret != JOYERR_NOERROR)					//ret��JOYERR_NOERROR����Ȃ�������
		MessageBox(NULL,"�W���C�X�e�B�b�N�̎擾�Ɏ��s","�G���[",MB_OK);	//�G���[�\��
	Dum = 0;					//Dum��0�i0000 [0]�j�ŃX�^�[�g
	if(JoyData.dwXpos <= 10000)	//����������Ă�����
		Dum |= 1;					//�O�r�b�g�ڂ��P�Ɂi0001 [1]�j
	if(JoyData.dwYpos <= 10000)	//�オ������Ă�����
		Dum |= (1<<1);				//�P�r�b�g�ڂ��P�Ɂi0010 [2]�j
	if(JoyData.dwXpos >= 50000)	//�E��������Ă�����
		Dum |= (1<<2);				//�Q�r�b�g�ڂ��P�Ɂi0100 [4]�j
	if(JoyData.dwYpos >= 50000)	//����������Ă�����
		Dum |= (1<<3);				//�R�r�b�g�ڂ��P�Ɂi1000 [8]�j
	
	//�`�{�^�����������u��
	if((JoyData.dwButtons & 1) && !(JoyData2.dwButtons & 1))	//����(��)�ŁA���O��(��)��������
	{
		A++;	//�������u�Ԃ̏���
	}
	//�������u��
	if(!(JoyData.dwButtons & 1) && (JoyData2.dwButtons & 1))	//����(��)�ŁA���O��(��)��������
	{
		B++;	//�������u�Ԃ̏���
	}
	//�������ςȂ�
	if((JoyData.dwButtons & 1) && (JoyData2.dwButtons & 1))		//����(��)�ŁA���O��(��)��������
	{
		C++;	//�������ςȂ��̏���
	}
	//�������ςȂ�
	if(!(JoyData.dwButtons & 1) && !(JoyData2.dwButtons & 1))	//����(��)�ŁA���O��(��)��������
	{
		D++;	//�������ςȂ��̏���
	}

	//�Q�[���̃f�[�^����
	x %= 640;	//0�`640
	y %= 480;	//0�`480
	AniPtnDum = 128*CharAnime(AniPtn,15,2);	//CharAnime()�̖ߒl����(128��1���̊G�̃T�C�Y)

	//����Ȃǁi���͓��ɖ����j

	//�`��
	hdc = GetDC(hwnd);		//HDC�擾


	/*
	BitBlt(hMemDC,0,0,640,480,hBackDC,0,0,SRCCOPY);		//���z��ʂɔw�i��`��
	BitBlt(hMemDC,x,y,128,128,hCharMaskDC,AniPtnDum,0,SRCAND);	//���z��ʂɃL�����}�X�N��`��
	BitBlt(hMemDC,x,y,128,128,hCharDC,AniPtnDum,0,SRCPAINT);	//���z��ʂɃL������`��
	*/
	

	//�t���[�����[�g�\��
	SetBkMode(hMemDC,TRANSPARENT);						//�����w�i�𓧖���
	wsprintf(str,"FPS_Disp [ %d ]",FPS_Disp);			//FPS_Disp�𕶎���ɒu��������
	TextOut(hMemDC,10,10,str,lstrlen(str));				//���z��ʂ�str�\��
	
	
	ReleaseDC(hwnd,hdc);	//HDC���
}




