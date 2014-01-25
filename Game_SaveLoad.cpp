//�Q�[���p�̃Z�[�u�A���[�h�̊֐��{��
#include <windows.h>	//Windows�p�w�b�_�t�@�C��
#include "extern.h"		//�O���ϐ��ɂȂ��Ă���f�[�^���Z�[�u�A���[�h����̂ŁAextern.h���g���B

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void GameSave(char *pFileName)	//�@�\�F�Q�[���p�̃f�[�^���Z�[�u(�}�b�v�f�[�^�̃Z�[�u
//�������F�Z�[�u����t�@�C����
{
	HANDLE hFile;
	DWORD Dum;

	//�Z�[�u�p�Ƀt�@�C��������
	hFile = CreateFile(pFileName,GENERIC_WRITE,		//(GENERIC_WRITE)�������ݗp��
						0,NULL,CREATE_ALWAYS,		//(CREATE_ALWAYS)�t�@�C������������쐬�A�������猳�̃t�@�C���������č쐬
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFile�̖ߒl��INVALID_HANDLE_VALUE�Ȃ�G���[
	{
		MessageBox(NULL,"�ǂݍ��ݗp�t�@�C���������s","�G���[[Game_SaveLoad.cpp]",MB_OK);	//�G���[��ʒm
		return;
	}
	//�O���ϐ��ɂȂ��Ă���Q�[���f�[�^�̂����A�K�v�Ȃ��̂��Z�[�u����B
	//������͗�Ƃ��āAint x;int y;���O���ϐ��ɂ�����̂Ƃ��āA�Z�[�u����B

	WriteFile(hFile,&map_xnum,sizeof(int),&Dum,NULL);	//�}�b�v���R�`�b�v�����Z�[�u�iint�^�j
	WriteFile(hFile,&map_ynum,sizeof(int),&Dum,NULL);	//�}�b�v�^�e�`�b�v�����Z�[�u�iint�^�j
	WriteFile(hFile,&Map[0][0],sizeof(int)*map_ynum*map_xnum,&Dum,NULL);	//�}�b�v�f�[�^���Z�[�u
	//���ɂ��K�v�ȃf�[�^���AWriteFile()�ŃZ�[�u���Ă���

	//�t�@�C�������
	CloseHandle(hFile);
	MessageBox(NULL,"�Z�[�u���܂���","SAVE",MB_OK);	//�Z�[�u���ꂽ���̊m�F���b�Z�[�W
}

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void GameLoad(char *pFileName)	//�@�\�F�Q�[���p�̃f�[�^�����[�h����֐��i�}�b�v�f�[�^���[�h
//�������F���[�h����t�@�C����
{
	HANDLE hFile;
	DWORD Dum;
	hFile = CreateFile(pFileName,GENERIC_READ,	//(GENERIC_READ)�ǂݍ��ݗp��
						0,NULL,OPEN_EXISTING,	//(OPEN_EXISTING)�t�@�C�����J���A�Ȃ��ꍇ�͎��s
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFile�̖ߒl��INVALID_HANDLE_VALUE�Ȃ�G���[
	{
		MessageBox(NULL,"�ǂݍ��ݗp�t�@�C���������s","�G���[[Game_SaveLoad.cpp]",MB_OK);	//�G���[��ʒm
		return;
	}
	//�Z�[�u���Ă���f�[�^�����[�h����B�Z�[�u�������ƁA�������ԂŃ��[�h���邱�ƁB
	ReadFile(hFile,&map_xnum,sizeof(int),&Dum,NULL);	//�}�b�v���R�`�b�v�������[�h�iint�^�j
	ReadFile(hFile,&map_ynum,sizeof(int),&Dum,NULL);	//�}�b�v�^�e�`�b�v�������[�h�iint�^�j
	ReadFile(hFile,&Map[0][0],sizeof(int)*map_ynum*map_xnum,&Dum,NULL);	//�}�b�v�f�[�^�����[�h

	if(map_xnum != MAP_XNUM || map_ynum != MAP_YNUM)	//�}�N���Őݒ肵���c���̃`�b�v�̐������[�h�����c���`�b�v�̐��Ƃ���������
	{
		MessageBox(NULL,"�c���̃`�b�v�̐����ݒ�ƈႢ�܂�","map_xnum != MAP_XNUM map_ynum MAP_YNUM",MB_OK);	//�ݒ�̈Ⴂ��ʒm
		return;
	}

	//���ɂ��Z�[�u�����f�[�^������Ȃ�A�Z�[�u�������Ɠ������ԂŃ��[�h����

	CloseHandle(hFile);		//���
	MessageBox(NULL,"���[�h���܂���","LOAD",MB_OK);	//���[�h���ꂽ���̊m�F���b�Z�[�W
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EneOnPosSave(char *pFileName)	//�@�\�F�K�o���ʒu�f�[�^�Z�[�u
//�������F�Z�[�u����t�@�C����
{
	HANDLE hFile;
	DWORD Dum;

	//�Z�[�u�p�Ƀt�@�C��������
	hFile = CreateFile(pFileName,GENERIC_WRITE,		//(GENERIC_WRITE)�������ݗp��
						0,NULL,CREATE_ALWAYS,		//(CREATE_ALWAYS)�t�@�C������������쐬�A�������猳�̃t�@�C���������č쐬
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFile�̖ߒl��INVALID_HANDLE_VALUE�Ȃ�G���[
	{
		MessageBox(NULL,"�ǂݍ��ݗp�t�@�C���������s","�G���[[Game_SaveLoad.cpp]",MB_OK);	//�G���[��ʒm
		return;
	}
	//�O���ϐ��ɂȂ��Ă���Q�[���f�[�^�̂����A�K�v�Ȃ��̂��Z�[�u����B
	WriteFile(hFile,&EneOnPos_Max,sizeof(ENE_ONPOS),&Dum,NULL);					//�K�o���ʒu�ő吔���Z�[�u�i�ő吔�̓����ox�ɓ����Ă���j
	WriteFile(hFile,&EneOn[0],sizeof(ENE_ONPOS) * EneOnPos_Max.x,&Dum,NULL);	//�K�o���ʒu�f�[�^���Z�[�u
	//���ɂ��K�v�ȃf�[�^���AWriteFile()�ŃZ�[�u���Ă���

	//�t�@�C�������
	CloseHandle(hFile);
	MessageBox(NULL,"�K�o���ʒu�f�[�^���Z�[�u���܂���","SAVE",MB_OK);	//�Z�[�u���ꂽ���̊m�F���b�Z�[�W
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void EneOnPosLoad(char *pFileName)	//�@�\�F�K�o���ʒu�f�[�^�����[�h����֐�
//�������F���[�h����t�@�C����
{
	HANDLE hFile;
	DWORD Dum;
	hFile = CreateFile(pFileName,GENERIC_READ,			//(GENERIC_READ)�ǂݍ��ݗp��
						0,NULL,OPEN_EXISTING,			//(OPEN_EXISTING)�t�@�C�����J���A�Ȃ��ꍇ�͎��s
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)				//CreateFile�̖ߒl��INVALID_HANDLE_VALUE�Ȃ�G���[
	{
		MessageBox(NULL,"�ǂݍ��ݗp�t�@�C���������s","�G���[[Game_SaveLoad.cpp]",MB_OK);	//�G���[��ʒm
		return;
	}
	//�Z�[�u���Ă���f�[�^�����[�h����B�Z�[�u�������ƁA�������ԂŃ��[�h���邱�ƁB
	ReadFile(hFile,&EneOnPos_Max,sizeof(ENE_ONPOS),&Dum,NULL);				//�K�o���ʒu�ő吔�����[�h�i�ő吔�̓����ox�ɓ����Ă���j
	ReadFile(hFile,&EneOn[0],sizeof(ENE_ONPOS)*EneOnPos_Max.x,&Dum,NULL);	//�K�o���ʒu�f�[�^�����[�h
	//���ɂ��Z�[�u�����f�[�^������Ȃ�A�Z�[�u�������Ɠ������ԂŃ��[�h����

	if(EneOnPos_Max.x != ENEONPOS_MAX)	//�}�N���Őݒ肵���l�ƃ��[�h�����l������������(�܂��������m�ۂŃ��[�h�����ĂȂ��̂Ł@���b�Z�[�W�{�b�N�X�Œʒm
	{
		MessageBox(NULL,"�}�N���̒l�ƃ��[�h�����K�o���ʒu�����قȂ�܂�","�K�o���ʒu���̌x��",MB_OK);	//�ݒ�̈Ⴂ��ʒm
		return;
	}


	CloseHandle(hFile);		//���
	MessageBox(NULL,"�K�o���ʒu�f�[�^�����[�h���܂���","LOAD",MB_OK);	//���[�h���ꂽ���̊m�F���b�Z�[�W
}