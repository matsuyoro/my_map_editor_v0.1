////////�C���N���[�h///////////
#include <windows.h>	//Windows�p�̃w�b�_�[�t�@�C��(windows�Ŏg�p���閽�߂�f�[�^�^���܂Ƃ߂��Ă���)

/////////�֐��{��/////////////////
//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BOOL LoadBmp(char *pFileName,HDC hdc,HDC *phBmpDC,HINSTANCE hInst)	//�@�\�FBMP�t�@�C������������֐�
//�������P�F�ǂݍ��ރt�@�C����
//�������Q�F�E�B���h�E��HDC
//�������R�F�쐬���ꂽHDC�������Ƃ�A�h���X
//�������S�FLoadImage�Ŏg�p����C���X�^���X�n���h��
{
//�����ϐ��錾
HBITMAP hBit;	//�r�b�g�}�b�v�n���h��hBit��錾
char str[256];	//�G���[���b�Z�[�W�ň���������������ϐ�

//�G�̃f�[�^����
hBit = (HBITMAP)LoadImage(hInst,pFileName,			//�����P�̃t�@�C����(pFIleName)�̃f�[�^��ǂݍ���
						  IMAGE_BITMAP,0,0,			//0,0�Ŏ����œǂݍ��މ摜�̑傫���������Őݒ�
						  LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//�ǂݍ��݃t���O
if(!hBit)		//LoadImage()�Ɏ��s������(NULL�Ȃ�)
{
	wsprintf(str,"%s�̗p�ӂɎ��s(LoadImage)",pFileName);	//LoadImage�Ɏ��s�����t�@�C�����𕶎���ɒu��������
	MessageBox(NULL,str,"�G���[",MB_OK);					//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��
	return FALSE;											//FALSE��߂�
}

*phBmpDC = CreateCompatibleDC(hdc);		//hCharDC�i������DC�j���쐬
if(!*phBmpDC)	//CreateCompatibleDC()�Ɏ��s������(NULL�Ȃ�)
{
	wsprintf(str,"%s��HDC�쐬�Ɏ��s(CreateCompatibleDC)",pFileName);	//CreateComaptibleDC�Ɏ��s�����t�@�C�����𕶎���ɒu��������
	MessageBox(NULL,str,"�G���[",MB_OK);								//�G���[�����b�Z�[�W�{�b�N�X�ŕ\��
	DeleteObject(hBit);													//��������LoadImage()��hBit�͉��
	return FALSE;														//FALSE��߂�
}

SelectObject(*phBmpDC,hBit);		//hCharDC�Ƀr�b�g�}�b�v�n���h����I��
DeleteObject(hBit);					//�r�b�g�}�b�v�n���h��hBit�����
return TRUE;						//����������TRUE��n��
}

//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
int CharAnime(int *pCharHai,int HaiMax,int LoopAni)	//�L�����A�j���[�V����
//�������P�F�L�����A�j���̔z��̐擪�A�h���X
//�������Q�F�z��̗v�f��
//�������R�F�A�j���[�V������\�����I����Ė߂郋�[�v��
{
	static int AniTime;	//�P���̊G�̕\�����Ԃ�����
	static int HaiNum;	//�z��̗v�f�ԍ�������

	AniTime--;		//�P���̊G�̕\�����Ԃ𖈉�[�P
	if(AniTime < 0)
	{
		HaiNum++;	//���̗v�f�ԍ���
		if(HaiNum >= (HaiMax))	HaiNum = LoopAni;	//���E�𒴂��Ȃ��悤�Ƀ��[�v
		AniTime = pCharHai[HaiNum];	//�w�肵���z��̗v�f�ԍ��̒l����
	}
	return(HaiNum);	//�z��̗v�f�ԍ���߂�
}
