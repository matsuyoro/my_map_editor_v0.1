#include <windows.h>	//windows�p�w�b�_�t�@�C��

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void DataSave(char *pFileName,void *pData,DWORD DataSize)	//�@�\�F�Z�[�u����֐�
//�������P�F�t�@�C����
//�������Q�F�Z�[�u�������f�[�^�̐擪�A�h���X
//�������R�F�Z�[�u����f�[�^�̗�
{
	HANDLE hFile;
	DWORD Dum;
	//�Z�[�u�p�Ƀt�@�C��������
	hFile = CreateFile(pFileName,GENERIC_WRITE,	//(GENERIC_WRITE)�������ݗp��
						0,NULL,CREATE_ALWAYS,	//(CREATE_ALWAYS)�t�@�C��������������쐬�A�������猳�̃f�[�^�������āA�쐬
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFile�̖ߒl��INVALID_HANDLE_VALUE�Ȃ�G���[
	{
		//�����b�Z�[�W�{�b�N�X���ŃG���[��m�点��
		MessageBox(NULL,"�������ݗp�t�@�C���������s","�G���[",MB_OK);	//�G���[��ʒm
		return;
	}
	//�f�[�^���Z�[�u����
	WriteFile(hFile,pData,DataSize,&Dum,NULL);	//�Z�[�u��̃n���h��hFile��pData���Z�[�u
	//�t�@�C�������
	CloseHandle(hFile);							//���
}
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void DataLoad(char *pFileName,void *pData,DWORD DataSize)	//�@�\�F���[�h����֐�
//�������P�F�t�@�C����
//�������Q�F���[�h�����f�[�^�������Ƃ�ꏊ�̐擪�A�h���X
//�������R�F���[�h����f�[�^�̗�
{
	HANDLE hFile;
	DWORD Dum;
	//���[�h�p�Ƀt�@�C��������
	hFile = CreateFile(pFileName,GENERIC_READ,	//(GENERIC_READ)�ǂݍ��ݗp��
						0,NULL,OPEN_EXISTING,	//(OPEN_EXISTING)�t�@�C�����J���A�Ȃ������玸�s
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFile�̖ߒl��INVALID_HANDLE_VALUE�Ȃ�G���[
	{
		//���G���[��m�点��
		MessageBox(NULL,"�ǂݍ��ݗp�t�@�C���������s","�G���[",MB_OK);	//�G���[��ʒm
		return;
	}
	//�f�[�^�����[�h����
	ReadFile(hFile,pData,DataSize,&Dum,NULL);	//���[�h����t�@�C���̃n���h��hFile��pData�Ƀ��[�h
	//�t�@�C�������
	CloseHandle(hFile);						//���
}
