/////////////////// Windows Skeleton Program Sample //////////////////////////////
//�@include�A�v���g�^�C�v�錾�A�O���ϐ��A�}�N���Ȃǁi�P�`�R�s�ځj�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
#include <windows.h>				//Windows�p�̃w�b�_�[�t�@�C��(windows�Ŏg�p���閽�߂�f�[�^�^���܂Ƃ߂��Ă���)
#include "resource.h"				//���\�[�X���g���̂ɕK�v�ȃw�b�_�t�@�C��

#include "define.h"					//�}�N���p�̃w�b�_�t�@�C��

#include "WinProc.h"				//�E�B���h�E�v���V�[�W���̃v���g�^�C�v�錾�������Ă���w�b�_�t�@�C��
#include "ChildWinProc.h"			//�q�E�B���h�E�v���V�[�W���̃v���g�^�C�v�錾�̃w�b�_�t�@�C��
#include "MinMapWinProc.h"			//�~�j�}�b�v�q�E�B���h�E�̃v���g�^�C�v�錾�̃w�b�_�t�@�C��
#include "Global.h"					//�O���ϐ����܂Ƃ߂��w�b�_�t�@�C���AWinMain()�̂���\�[�X�ɂ����C���N���[�h
#pragma comment(lib,"winmm.lib")	//timeGetTime()���g�p����̂ɕK�v�ȃw�b�_�t�@�C��

HANDLE hMutex;			//�~���[�e�b�N�X�̃n���h���������Ƃ�ϐ��B�O���ϐ��ɂ��Ă����Ƃ悢�B

//�A�v�����l�������֐��`�����ϐ��̐錾�i�S�`�V�s�ځj�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpszArgs,int nWinMode)		//WinMain�֐��̊J�n�B(�����͎����Œl�������Ƃ�)
//WinMain�֐��̊J�n�B�v���O�������s��A���̊֐����ŏ��ɌĂяo�����B�������S���邪�A�����I�ɒl�������Ƃ�̂ŁA�����Ƃ邾���ł悢�B
{
	//HWND		hwnd;
	//�E�B���h�E�n���h���������Ahwnd�̐錾�B19�s�ڂŃE�B���h�E�n���h���������Ƃ�A�ۑ�����B
	MSG			msg;
	//���b�Z�[�W���g���\����msg�̐錾�B34�`40�̃��b�Z�[�W���[�v�Ŏg�p�B
	WNDCLASS	wcls;
	//�N���X��`�p�̍\���́B����޳�׽�̃p�����[�^�������\���́Awcls�̐錾�B�W�`18�s�ڂŎg�p

	hInst = hInstance;
	//hInst�ɁA�C���X�^���X�n���h���̃R�s�[������B�i�E�B���h�E�v���V�[�W���Ŏg�p�j


	hMutex = CreateMutex(NULL,FALSE,"�~���[�e�b�N�X��");	//�~���[�e�b�N�X���쐬����
	if(GetLastError() == ERROR_ALREADY_EXISTS)	//GetLastError�́i�Ō�ɋN�����G���[���j
	{	//�����������O�̃~���[�e�b�N�X�����݂��Ă��邽�߂ɃG���[�ɂȂ�����
		MessageBox(NULL,"���łɋN�����Ă��܂�","�G���[",MB_OK);	//�G���[��\��
		return 0;												//WinMain()�I��
	}

//�B�E�B���h�E�N���X�ݒ�E�쐬�i�W�`�P�W�s�ځj�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	//	�E�B���h�E�E�N���X��`��
	wcls.hInstance = hInstance;							//�C���X�^���X�n���h��
	//WinMain()�̈�����hInstance�����̂܂ܑ���B
	wcls.lpszClassName = WIN_CLASSNAME;					//�N���X��
	//�R�s�ڂ̕�����^�z����g���B
	wcls.lpfnWndProc = (WNDPROC)WinProc;				//�E�B���h�E�v���V�[�W��
	//�E�B���h�E�v���V�[�W���ɂ������֐��̊֐����B
	wcls.style = 0;										//�N���X�̃X�^�C��
	//�N���X�̃X�^�C���B�O�ł悢�B
	wcls.hIcon = LoadIcon(NULL,IDI_APPLICATION);		//�A�C�R���̃n���h��
	//�A�C�R���̎�ނ��w�肷��BLoadIcon()�ō���͒ʏ�̃A�C�R����I��
	wcls.hCursor = LoadCursor(NULL,IDC_ARROW);			//�J�[�\���̃n���h��
	//�J�[�\���̎�ނ��w�肷��BLoadCursor()�ō���͒ʏ�̃J�[�\����I��
	wcls.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);		//�N���X�̃��j���[
	//
	wcls.cbClsExtra = 0;								//�g���p�̃p�����[�^
	//�E�E�E�O
	wcls.cbWndExtra = 0;								//�g���p�̃p�����[�^
	//�E�E�E�O
	
	//----------�쐬�E�B���h�E�E�o�b�N�O���E���h�J���[�ݒ蕔---------------------------------------------
	wcls.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	//�E�B���h�E�̔w�i�F�BGetStockObject()���g���Ďw��BWHITE_BRUSH�ŁA���F���w��B

	//-----------�E�B���h�E�E�N���X�쐬��-------------------------------------------------------------------
	if(!RegisterClass (&wcls))	//�l��������wcls���g���āA�E�B���h�E�N���X��ݒ�B���s�����ꍇ�A�O��߂���WindowsMain()�I��
	{
		CloseHandle(hMutex);	//WinMain()�������I�����鎞�́A�~���[�e�b�N�X��������Ă���
		return 0;
	}

//�C�E�B���h�E�쐬�i�P�X�`�R�O�s�ځj�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	//	�\���E�B���h�E�E�X�^�C���ݒ蕔


	//�e�E�B���h�E//
	RECT rc;
	rc.left = 0; rc.right = 640;	//rc�ɁA�N���C�A���g�̈�̑傫������
	rc.top = 0; rc.bottom = 480;
	AdjustWindowRect(&rc,			//rc�̃����o�ɂ͐������E�B���h�E�̑傫��������B
	WS_SYSMENU | WS_CAPTION | WS_HSCROLL | WS_VSCROLL | WS_CLIPCHILDREN,		//CreateWindow()�Ɠ����E�B���h�E�X�^�C��
	FALSE);							//���j���[�����̏ꍇ�AFALSE	���j���[�L��̏ꍇ�ATRUE

	hwnd = CreateWindow(
	//CreateWindow()�ŁA�E�B���h�E�����Ahwnd�ɁA�E�B���h�E�n���h����ۑ��B
						WIN_CLASSNAME,			//�N���X��
						WIN_TITLE,				//�E�B���h�E�̃^�C�g��
						(WS_SYSMENU | WS_CAPTION | WS_HSCROLL | WS_VSCROLL ),//| WS_CLIPCHILDREN),	//�E�B���h�E�̃X�^�C��
						CW_USEDEFAULT,			//�E�B���h�E�̍���w���W
						CW_USEDEFAULT,			//�E�B���h�E�̍���x���W
						rc.right-rc.left,		//�E�B���h�E�̕�(AdjustWindowRect�ŋ��߂��l�Ő����������w��
						rc.bottom-rc.top-15,	//�E�B���h�E�̍���(AdjustWindowRect�Ő����������[�P�T�i���j���[�o�[��\���������\���ɂ��镪�̍���
						NULL,					//�e�E�B���h�E�̃n���h���B����͂O�B
						NULL,					//���j���[�̃n���h���B����͂O�B
						hInstance,				//�C���X�^���X�n���h��(WinMain()�̑�P�����AhInstance�����̂܂܎g��)
						NULL					//�g���p�̃p�����[�^�E�E�E�O
						);	//�ߒl�Ƃ��āA�쐬���ꂽ�E�B���h�E�̃E�B���h�E�n���h����߂��B�ihwnd�ɕۑ��j
						//��CW_USEDEFAULT�́A�f�t�H���g�̒l��\���B�E�B���h�E�̕��A�����Ȃǂ́A�e���ŕύX����Ƃ悢�B(�u640�v�Ȃǂ̒萔���g����j
	
	//�q�E�B���h�E//
	hCwnd = CreateWindow(
	//CreateWindow()�ŁA�E�B���h�E�����AhCwnd�ɁA�E�B���h�E�n���h����ۑ��B
						WIN_CLASSNAME,			//�N���X��
						"�q�E�B���h�E",				//�E�B���h�E�̃^�C�g��
						(WS_POPUP | WS_OVERLAPPEDWINDOW),	//�E�B���h�E�̃X�^�C��
						CW_USEDEFAULT,			//�E�B���h�E�̍���w���W
						CW_USEDEFAULT,			//�E�B���h�E�̍���x���W
						CWIN_W,					//�E�B���h�E�̕�
						CWIN_H,					//�E�B���h�E�̍���
						hwnd,					//�e�E�B���h�E�̃n���h��(hwnd)
						NULL,					//���j���[�̃n���h���B����͂O�B
						hInstance,				//�C���X�^���X�n���h��(WinMain()�̑�P�����AhInstance�����̂܂܎g��)
						NULL					//�g���p�̃p�����[�^�E�E�E�O
						);	//�ߒl�Ƃ��āA�쐬���ꂽ�E�B���h�E�̃E�B���h�E�n���h����߂��B�ihwnd�ɕۑ��j
						//��CW_USEDEFAULT�́A�f�t�H���g�̒l��\���B�E�B���h�E�̕��A�����Ȃǂ́A�e���ŕύX����Ƃ悢�B(�u640�v�Ȃǂ̒萔���g����j
	SetWindowLong(hCwnd,GWL_WNDPROC,(LONG)ChildWinProc);	//hCwnd��ChildWinProc()��ݒ肷��B
	
	//�~�j�}�b�v�q�E�B���h�E//
	hMwnd = CreateWindow(
	//CreateWindow()�ŁA�E�B���h�E�����AhMwnd�ɁA�E�B���h�E�n���h����ۑ��B
						WIN_CLASSNAME,			//�N���X��
						"�~�j�}�b�v�q�E�B���h�E",				//�E�B���h�E�̃^�C�g��
						WS_POPUP | WS_OVERLAPPEDWINDOW,	//�E�B���h�E�̃X�^�C��
						CW_USEDEFAULT,			//�E�B���h�E�̍���w���W
						CW_USEDEFAULT,			//�E�B���h�E�̍���x���W
						MWIN_W,					//�E�B���h�E�̕�
						MWIN_H,					//�E�B���h�E�̍���
						hwnd,					//�e�E�B���h�E�̃n���h��(hwnd)
						NULL,					//���j���[�̃n���h���B����͂O�B
						hInstance,				//�C���X�^���X�n���h��(WinMain()�̑�P�����AhInstance�����̂܂܎g��)
						NULL					//�g���p�̃p�����[�^�E�E�E�O
						);	//�ߒl�Ƃ��āA�쐬���ꂽ�E�B���h�E�̃E�B���h�E�n���h����߂��B�ihwnd�ɕۑ��j
						//��CW_USEDEFAULT�́A�f�t�H���g�̒l��\���B�E�B���h�E�̕��A�����Ȃǂ́A�e���ŕύX����Ƃ悢�B(�u640�v�Ȃǂ̒萔���g����j
	SetWindowLong(hMwnd,GWL_WNDPROC,(LONG)MinMapWinProc);	//hCwnd��ChildWinProc()��ݒ肷��B
	
	//�@�E�B���h�E�`�敔
	//�E�B���h�E�̕\���J�n	hwnd���g���ĕ\������E�B���h�E���w�肵�Ă���B
	//�e�E�B���h�E//
	ShowWindow(hwnd,nWinMode);							//�E�B���h�E�쐬�J�n
	UpdateWindow(hwnd);									//�E�B���h�E�\���J�n
	//�q�E�B���h�E//
	ShowWindow(hCwnd,nWinMode);							//�q�E�B���h�E�쐬�J�n
	UpdateWindow(hCwnd);								//�q�E�B���h�E�\���J�n
	//�~�j�}�b�v�q�E�B���h�E//
	ShowWindow(hMwnd,nWinMode);							//�~�j�}�b�v�q�E�B���h�E�쐬�J�n
	UpdateWindow(hMwnd);								//�~�j�}�b�v�q�E�B���h�E�\���J�n

//�D���b�Z�[�W�E���[�v�i�R�S�`�S�O�s�ځj�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	while(GetMessage(&msg,NULL,0,0))	//���b�Z�[�W�̎擾
	{
		TranslateMessage(&msg);		//���b�Z�[�W�ϊ�
		DispatchMessage(&msg);		//���b�Z�[�W�𑗂�
	}



	CloseHandle(hMutex);	//�~���[�e�b�N�X�̉��
	return msg.wParam;		//�I�����̖ߒl�imsg.wParam�j��߂��AWinMain�I��
}



