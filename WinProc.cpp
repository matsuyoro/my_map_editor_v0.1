/////// �C���N���[�h ///////
#include <windows.h>	//Windows�p�̃w�b�_�t�@�C��(Windows�Ŏg�p���閽�߂�f�[�^�^���܂Ƃ߂��Ă���j
#include "resource.h"	//���\�[�X���g���̂ɕK�v�ȃw�b�_�t�@�C��
#include "define.h"		//�}�N����`���܂Ƃ߂��w�b�_�t�@�C��

#include "extern.h"		//�O���ϐ����܂Ƃ߂��w�b�_�t�@�C���ifActive�Ȃǂ̐錾�j
#include "File_WriteRead.h"	//File_WriteRead.cpp�̊֐��̃v���g�^�C�v�錾�̃w�b�_�t�@�C��
#include "Game_SaveLoad.h"	//�Q�[���p�̃Z�[�u���[�h���܂Ƃ߂��w�b�_�t�@�C��
#include "ImageSetUp.h"		

//�F�E�B���h�E�֐��i�E�B���h�E�v���V�[�W���j(41�`51�s��)37�s�ڂő���ꂽ���b�Z�[�W����������B�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
LRESULT CALLBACK WinProc(
						 HWND hwnd,		//���b�Z�[�W�������̃E�B���h�E�n���h��
						 UINT message,	//�����������b�Z�[�W�̎��
						 WPARAM wParam,	//�����������b�Z�[�W���ƂɈقȂ�ׂ����f�[�^
						 LPARAM lParam)	//�����������b�Z�[�W���ƂɈقȂ�ׂ����f�[�^
{
	PAINTSTRUCT ps;			//PAINTSTRUCT�^�\����ps��錾�iBeginPaint�ȂǂŎg�p�j
	char str[256];			//�����������
	int i,j;				//�J�E���^�ϐ�
	int DumNum;				//�ϐ��̒l�����ւ��鎞�ȂǂɎg�p
	int EneOnFlagNum = 0;		//���ݔz�u�����G�̐�������
	static int DelEneOn =0;
	char EneName[][16] =	//�z�u����G�̖��O�����ꂨ���ϐ�
	{
		{"�g�p�֎~"},{"��"},{"�g�J�Q"},{"��"},{"���J��"},{"��"},{"�ΐl��"},{"�}"},{"�S��"},{"�Ώ�����"},{"�I"},{"�c�{"},{"����"},{"���{�X��"},{"���{�X�K��"},{"����"},{"���X�{�X��"},{"���X�{�X����"},{"���X�{�X�E��"}
	};

	OPENFILENAME ofn;			//�R�����_�C�A���O�̍\����
	char FileName[MAX_PATH];	//�t�@�C�����A�p�X�������Ƃ�z��

	switch(message)			//���b�Z�[�W�̎�ނŕ���B
	{
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_CREATE:			//�E�B���h�E�쐬���Ȃ�

		HDC hdc;
		HBITMAP hBit;			//�r�b�g�}�b�v�n���h��hBit��錾
		HBITMAP hMinBit;		//�~�j�}�b�v�p���z��ʂ��쐬����̂Ɏg�p����r�b�g�}�b�v�n���h��
		hdc = GetDC(hwnd);		//HDC�擾

		//-------------���j��-----------------------------
		hMenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU1)); //���j���[���������āA�n���h����hMenu�ɕۑ�
		
		//-----�����X�N���[���o�[�iHSCROLL)---------------
		HScr.cbSize = sizeof(SCROLLINFO);	//�X�N���[���o�[�̍\���̎��̂̃T�C�Y����
		HScr.fMask = SIF_POS | SIF_RANGE;	//�����f�[�^�̎��
		HScr.nMin = 0;						//�X�N���[���o�[�̍ŏ��l
		HScr.nMax = map_xnum-WINMAP_W;				//�X�N���[���o�[�̍ő�l�i�}�b�v�̃��R�̃`�b�v�������i�\���ł��閇���������j
		HScr.nPos = 0;						//�X�N���[���o�[�̏����ʒu
		SetScrollInfo(hwnd,SB_HORZ,&HScr,TRUE);	//�X�N���[���o�[�ɁA�f�[�^��ݒ�
		//-----�����X�N���[���o�[�iVSCROLL)---------------
		VScr.cbSize = sizeof(SCROLLINFO);	//�X�N���[���o�[�̍\���̎��̂̃T�C�Y����
		VScr.fMask = SIF_POS | SIF_RANGE;	//�����f�[�^�̎��
		VScr.nMin = 0;						//�X�N���[���o�[�̍ŏ��l
		VScr.nMax = map_ynum-WINMAP_H;				//�X�N���[���o�[�̍ő�l�i�}�b�v�̃^�e�̃`�b�v������(�\���ł��閇��������)
		VScr.nPos = 0;						//�X�N���[���o�[�̏����ʒu
		SetScrollInfo(hwnd,SB_VERT,&VScr,TRUE);		//�X�N���[���o�[�ɁA�f�[�^��ݒ�


		//���z��ʍ쐬
		hBit = CreateCompatibleBitmap(hdc,TIP_W*WINMAP_W,TIP_H*WINMAP_H);	//��ʂ̑傫�������w��
		hMemDC = CreateCompatibleDC(hdc);			//hMemDC�i������DC�j���쐬
		SelectObject(hMemDC,hBit);					//hMemDC��hBit��I��
		DeleteObject(hBit);							//hBit�̉��

		//�~�j�}�b�v�q�E�B���h�E�p���z��ʍ쐬
		hMinBit = CreateCompatibleBitmap(hdc,(TIP_W>>3)*WINMAP_W,(TIP_H>>3)*WINMAP_H);
		hMinMemDC = CreateCompatibleDC(hdc);		//hMinMemDC���쐬
		SelectObject(hMinMemDC,hMinBit);
		DeleteObject(hMinBit);

		if(!LoadBmp("MapTip7.bmp",hdc,&hTipDC,hInst))		//�}�b�v�`�b�v�̏������`�֐��Ŏ��s
			DestroyWindow(hwnd);							//WM_DESTROY���b�Z�[�W�𑗂�I��
		
		//8����1 hTipD�����z��ʂɕ\��(���z��ʂ�Y���W�S�W�O��艺�̕��ɕ\������ʂɂ͌����Ȃ��i�����f�Ƀ~�j�}�b�v�̃`�b�v��\��	
		for(i = 0;i < ((TIP_H>>3)*map_ynum);i++)
		{
			for(j = 0;j < ((TIP_W>>3)*map_xnum);j++)	//���RWINMAP_W��
			{
				BitBlt(hMinMemDC,j,i,1,1,
						hTipDC,j * 8,i * 8,SRCCOPY);			//�R�s�[��x���AMap���狁�߂�B
			}
		}


		ReleaseDC(hwnd,hdc);	//HDC���
		

		///// �����ݒ� ////////////////////////////////

		ZeroMemory(&Map[0][0],sizeof(int)*map_ynum*map_xnum);	//�}�b�v�`�b�v�͍ŏ��͑S�ĂO
		ZeroMemory(&EneOn[0],sizeof(ENE_ONPOS)*EneOnPos_Max.x);	//�G�l�~�[�o���ʒu�z�u�̃f�[�^���ŏ��͑S�ĂO
	

		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_RBUTTONDOWN:	//�}�E�X�̉E�{�^���������ꂽ��
		
		//mx2,my2�Ɍ��݂̃}�X�P�ʂ̃}�E�X���W��ۑ�����B
		if(ToolNum == 1)	//�l�p���I������Ă�����
		{
			MapMx2 = LOWORD(lParam) / TIP_W + MapScrX;	//���݂̃}�X�P�ʂ̃}�E�X�̍��W����
			MapMy2 = HIWORD(lParam) / TIP_H + MapScrY;
		}else
		{
			//�`�b�v�̃X�|�C�g
			TipNum = Map[HIWORD(lParam) / TIP_H+MapScrY][LOWORD(lParam) / TIP_W+MapScrX];	//�}�E�X�̎w���Ă���Ƃ���̃`�b�v���擾
		}
		InvalidateRect(hwnd,NULL,FALSE);	//��ʂ̍ĕ`��
		InvalidateRect(hCwnd,NULL,FALSE);	//�q�E�B���h�E�̍ĕ`��
		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_RBUTTONUP:	//�}�E�X�̍��{�^�������ꂽ�Ȃ�

		if(ToolNum == 1)	//�`�b�v���l�p�ɕ`�悷�郂�[�h�Ȃ�
		{
			MapMx = LOWORD(lParam) / TIP_W + MapScrX;	//�}�b�v�P�ʂł̃}�E�X���W����
			MapMy = HIWORD(lParam) / TIP_H + MapScrY;

			if(LOWORD(lParam) / TIP_W+MapScrX >= map_xnum ||	//�ύX���Ă���x,y���z����I�[�o�[���Ă�����
				HIWORD(lParam) / TIP_H+MapScrY >= map_ynum)		break;
			
			//MapMx�̕���MapMx2���傫���Ȃ�悤��MapMx��MapMx�Q�̓���ւ�
			if(MapMx < MapMx2)
			{
				DumNum = MapMx;	//�_�~�[�̕ϐ���MapMx��ۑ����Ă���
				MapMx = MapMx2;	//MapMx2�@�Ɓ@MapMx�@�����ւ�
				MapMx2 = DumNum;
			}
			//MapMy�̕���MapMy2���傫���Ȃ�悤��MapMy��MapMy�Q�̓���ւ�
			if(MapMy < MapMy2)
			{
				DumNum = MapMy;	//�_�~�[�̕ϐ���MapMy��ۑ����Ă���
				MapMy = MapMy2;	//MapMy2�@�Ɓ@MapMy�@�����ւ�
				MapMy2 = DumNum;
			}

			//R�{�^�����N���b�N���Ă͂Ȃ����Ƃ���܂ł��l�p�œh��Ԃ�
			for(i = 0;i <= (MapMy - MapMy2);i++)
			{
				for(j = 0;j <= (MapMx - MapMx2);j++)
				{			
					Map[MapMy2+i][MapMx2+j] = TipNum;	//�w��̏ꏊ���w��̃`�b�v�ɕύX
				}
			}
		}
		InvalidateRect(hwnd,NULL,FALSE);	//��ʂ̍ĕ`��
		InvalidateRect(hMwnd,NULL,FALSE);	//�~�j�}�b�v�q�E�B���h�E�̍ĕ`��
		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_LBUTTONDOWN:	//�}�E�X�̍��{�^���������ꂽ��	
		if(EneOnTool)	//�G�l�~�[�z�u�@�\��TRUE�Ȃ�
		{

			for(i = 0;i < EneOnPos_Max.x;i++)	//�G�l�~�[�ő�o�������J��Ԃ�
			{
				if(!EneOn[i].OnFlag)	//�G�l�~�[�o���|�C���g�t���O��FALSE�Ȃ�
				{
					if(LOWORD(lParam) / TIP_W+MapScrX >= map_xnum ||
					HIWORD(lParam) / TIP_H+MapScrY >= map_ynum)		//�ύX���Ă���x,y���z����I�[�o�[���Ă�����
						break;

					EneOn[i].x = LOWORD(lParam) + (MapScrX*TIP_W);	//�G�l�~�[�o���ʒu�z�u�i���Ӂ@�`�b�v�P�ʂŔz�u
					EneOn[i].y = HIWORD(lParam) + (MapScrY*TIP_H);	
					EneOn[i].type = EneTypeNum;			//�G�l�~�[�̎�ނ�ݒ�
					EneOn[i].OnFlag = TRUE;		//�ݒu�t���OTRUE

					EneOnReturn[EneRtrnCnt] = i;	//�G�l�~�[�z�u�ԍ����L�^
					EneRtrnCnt++;					//����
					if(EneRtrnCnt >= EneOnPos_Max.x) EneRtrnCnt = 0;	//�z��̍ő�𒴂��Ȃ��悤�ɂ��� 
					break;
				}
			}

		}else	//�G�l�~�[�z�u�@�\��FALSE�Ȃ�
		{
			if(LOWORD(lParam) / TIP_W+MapScrX >= map_xnum ||
			HIWORD(lParam) / TIP_H+MapScrY >= map_ynum)		//�ύX���Ă���x,y���z����I�[�o�[���Ă�����
				break;

			Map[HIWORD(lParam) / TIP_H+MapScrY][LOWORD(lParam) / TIP_W+MapScrX] = TipNum;	//�}�E�X�̎w���Ă���`�b�v��ύX
		}		
		InvalidateRect(hwnd,NULL,FALSE);	//��ʂ̍ĕ`��
		InvalidateRect(hMwnd,NULL,FALSE);	//�~�j�}�b�v�q�E�B���h�E�̍ĕ`��
		break;

	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_MOUSEMOVE:		//�}�E�X����������
		mx = LOWORD(lParam);		//�}�E�XX���W����
		my = HIWORD(lParam);		//�}�E�XY���W����

		if(!EneOnTool)	//�G�l�~�[�z�u�@�\��FALSE�Ȃ�
		{
			if(wParam & MK_LBUTTON)	//���N���b�N���ꂽ��
			{	//�}�b�v�`�b�v�z�u
				if(LOWORD(lParam) / TIP_W+MapScrX >= map_xnum ||
					HIWORD(lParam) / TIP_H+MapScrY >= map_ynum)		//�ύX���Ă���x,y���z����I�[�o�[���Ă�����
					break;
				Map[HIWORD(lParam) / TIP_H+MapScrY][LOWORD(lParam) / TIP_W+MapScrX] = TipNum;	//�}�E�X�̎w���Ă���`�b�v��ύX
			}
		}

		InvalidateRect(hwnd,NULL,FALSE);	//��ʂ̍ĕ`��
		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_KEYDOWN:		//�L�[�{�[�h����������	

		switch(wParam)	//wParam�ŉ������{�^������������
		{
		case VK_LEFT:	//�����������ꂽ��
			if(EneOnTool)		//�G�l�~�[�z�u���[�h��TRUE�Ȃ�
			{
				EneTypeNum--;		//�G�l�~�[�̎�ނ�I��
				if(EneTypeNum < 1) EneTypeNum = 1;	//�G�l�~�[�̎�ނ̌��E�𒴂��Ȃ��悤�ɂ���
			}else
			{
				TipNum--;			//TipNum�͂O�`�S�͈̔͂ŕω�����
				if(TipNum < 0)	TipNum = 0;	//�I�����Ă���`�b�v�̎�ނ����E�������Ȃ��悤�ɖ߂�
			}

			break;
		case VK_RIGHT:	//���E�������ꂽ��
			if(EneOnTool)			//�G�l�~�[�z�u���[�h��TRUE�Ȃ�
			{
				EneTypeNum++;
				if(EneTypeNum > ENETYPE_MAX)	EneTypeNum = ENETYPE_MAX;
			}else
			{
				TipNum++;				//���̔ԍ��̃`�b�v��
				TipNum %= TIP_MAX;
			}
			break;

		case VK_UP:					//���オ�����ꂽ��
			TipNum -= BMPTIP_W;
			TipNum %= TIP_MAX;
			if(TipNum < 0)	TipNum = 0;
			break;

		case VK_DOWN:				//�����������ꂽ��
			TipNum += BMPTIP_W;
			TipNum %= TIP_MAX;
			break;


		//�}�b�v�X�N���[��
		case VK_NUMPAD4:					//NUMPAD4�������ꂽ��
			HScr.nPos --;		//�X�N���[���o�[�̒l���[�P
			if(HScr.nPos < HScr.nMin)	//�ŏ��l��菬����������
				HScr.nPos = HScr.nMin;	//�ŏ��l��菬�����Ȃ�Ȃ��悤�ɂ���
			break;
		case VK_NUMPAD6:					//�����ꂽ��
			HScr.nPos++;		//�X�N���[���o�[�̒l��+1
			if(HScr.nPos > HScr.nMax)	//�ő�l���傫���Ȃ�����
				HScr.nPos = HScr.nMax;	//�ő�l���傫���Ȃ�Ȃ��悤�ɂ���
			break;
		case VK_NUMPAD8:					
			VScr.nPos --;		//�X�N���[���o�[�̒l���[�P
			if(VScr.nPos < VScr.nMin)	//�ŏ��l��菬����������
				VScr.nPos = VScr.nMin;	//�ŏ��l��菬�����Ȃ�Ȃ��悤�ɂ���
			break;
		case VK_NUMPAD2:
			VScr.nPos++;		//�X�N���[���o�[�̒l��+1
			if(VScr.nPos > VScr.nMax)	//�ő�l���傫���Ȃ�����
				VScr.nPos = VScr.nMax;	//�ő�l���傫���Ȃ�Ȃ��悤�ɂ���
			break;

		case VK_SPACE:	//�X�y�[�X�L�[�������Ɓ@�}�b�v�쐬���[�h�ƓK�z�u���[�h��؂�ւ�����
			if(!EneOnTool)	//�G�l�~�[�\���@�\��FALSE�Ȃ�
				EneOnTool = TRUE;	//�G�l�~�[�\��	
			else			
				EneOnTool = FALSE;	//�G�l�~�[��\��
			break;

		case 0x41:	//��A�L�[(�폜����G�l�~�[��I��
			if(DelEneOn > 0)	DelEneOn--;
			break;
		case 0x53:	//��S�L�[(�폜����G�l�~�[��I��
			if(DelEneOn < EneOnPos_Max.x-1)	DelEneOn++;
			break;
		case 0x44:	//��D�L�[
			ZeroMemory(&EneOn[DelEneOn],sizeof(ENE_ONPOS));	//DelEneON�Ŏw�肵���f�[�^���[��������
			break;

		case VK_F11:	//��F11�L�[�i�G�l�~�[�o���ʒu�̔z�u��߂�					

			EneRtrnCnt--;				//�P�O��
			if(EneRtrnCnt < 0)	EneRtrnCnt = EneOnPos_Max.x-1;	//0��菬�����Ȃ�Ɣz��̍ő吔��
			ZeroMemory(&EneOn[EneOnReturn[EneRtrnCnt]],sizeof(ENE_ONPOS));	//�z�u�f�[�^�����													
			break;

		case VK_F12:	//��F12�L�[			
			break;

		case VK_SUBTRACT:	//���u-�v�L�[
			SetMenu(hCwnd,NULL);	//���j���[��\���i�`�b�v�E�B���h�E
			SetMenu(hMwnd,NULL);	//���j���[��\���i�~�j�}�b�v�E�B���h�E

			//���j���[�\��//
			if(my < 25)		//�}�E�XY���W��40��菬����������
				SetMenu(hwnd,hMenu);	//���j���[�\��
			else
			{
				SetMenu(hwnd,NULL);		//���j���[��\��
			}	
			break;

		case VK_ESCAPE:				//��ESC�L�[ �i�I��
			DestroyWindow(hwnd);		//�E�B���h�E�I���B�E�B���h�E�ɁAWM_DESTROY���b�Z�[�W�������I�ɏo�����B
			break;						//switch�����ʂ���
		
		default:					//���ǂ�case�Ɉ�v���Ȃ�������
			break;						//switch�����ʂ���
		}

		SetScrollInfo(hwnd,SB_HORZ,&HScr,TRUE);	//�ύX���ꂽHScr�̃f�[�^���X�N���[���o�[��
		MapScrX = HScr.nPos;
		SetScrollInfo(hwnd,SB_VERT,&VScr,TRUE);	//�ύX���ꂽVScr�̃f�[�^���X�N���[���o�[��
		MapScrY = VScr.nPos;					//nPos�̒l��MapScrY�ɑ��

		InvalidateRect(hwnd,NULL,FALSE);	//��ʂ̍ĕ`��
		InvalidateRect(hCwnd,NULL,FALSE);	//�q�E�B���h�E�̍ĕ`��
		InvalidateRect(hMwnd,NULL,FALSE);	//�~�j�}�b�v�q�E�B���h�E�̍ĕ`��
		break;					//switch�����ʂ���
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_HSCROLL:		//�����X�N���[���o�[

		switch(LOWORD(wParam))
		{
		case SB_LINELEFT:	//[��]�������ꂽ��
			HScr.nPos --;		//�X�N���[���o�[�̒l���[�P
			if(HScr.nPos < HScr.nMin)	//�ŏ��l��菬����������
				HScr.nPos = HScr.nMin;	//�ŏ��l��菬�����Ȃ�Ȃ��悤�ɂ���
			break;
		case SB_LINERIGHT:	//[��]�������ꂽ��
			HScr.nPos++;		//�X�N���[���o�[�̒l��+1
			if(HScr.nPos > HScr.nMax)	//�ő�l���傫���Ȃ�����
				HScr.nPos = HScr.nMax;	//�ő�l���傫���Ȃ�Ȃ��悤�ɂ���
			break;
		case SB_PAGELEFT:	//[��]�ƃT���̊Ԃ������ꂽ��
			HScr.nPos -= 5;
			if(HScr.nPos < HScr.nMin)	//�ŏ��l��菬�����Ȃ�ɂ悤�ɂ���
				HScr.nPos = HScr.nMin;
			break;
		case SB_PAGERIGHT:	//[��]�ƃT���̊Ԃ������ꂽ��
			HScr.nPos += 5;
			if(HScr.nPos > HScr.nMax)	//�ő�l���傫���Ȃ�Ȃ��悤�ɂ���
				HScr.nPos = HScr.nMax;
			break;
		case SB_THUMBTRACK:	//�T�����h���b�O���h���b�v����Ă���Ȃ�
		case SB_THUMBPOSITION:
			HScr.nPos = HIWORD(wParam);		//�T���̈ʒu���AnPos�ɐݒ�
			break;
		}
		SetScrollInfo(hwnd,SB_HORZ,&HScr,TRUE);	//�ύX���ꂽHScr�̃f�[�^���X�N���[���o�[��
		MapScrX = HScr.nPos;

		InvalidateRect(hwnd,NULL,FALSE);	//��ʂ̍ĕ`��
		InvalidateRect(hMwnd,NULL,FALSE);	//�~�j�}�b�v�q�E�B���h�E�̍ĕ`��
		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_VSCROLL:		//�����X�N���[���o�[

		switch(LOWORD(wParam))
		{
		case SB_LINEUP:	//[��]�������ꂽ��
			VScr.nPos --;		//�X�N���[���o�[�̒l���[�P
			if(VScr.nPos < VScr.nMin)	//�ŏ��l��菬����������
				VScr.nPos = VScr.nMin;	//�ŏ��l��菬�����Ȃ�Ȃ��悤�ɂ���
			break;
		case SB_LINEDOWN:	//[��]�������ꂽ��
			VScr.nPos++;		//�X�N���[���o�[�̒l��+1
			if(VScr.nPos > VScr.nMax)	//�ő�l���傫���Ȃ�����
				VScr.nPos = VScr.nMax;	//�ő�l���傫���Ȃ�Ȃ��悤�ɂ���
			break;
		case SB_PAGEUP:	//[��]�ƃT���̊Ԃ������ꂽ��
			VScr.nPos -= 5;
			if(VScr.nPos < VScr.nMin)	//�ŏ��l��菬�����Ȃ�ɂ悤�ɂ���
				VScr.nPos = VScr.nMin;
			break;
		case SB_PAGEDOWN:	//[��]�ƃT���̊Ԃ������ꂽ��
			VScr.nPos += 5;
			if(VScr.nPos > VScr.nMax)	//�ő�l���傫���Ȃ�Ȃ��悤�ɂ���
				VScr.nPos = VScr.nMax;
			break;
		case SB_THUMBTRACK:	//�T�����h���b�O���h���b�v����Ă���Ȃ�
		case SB_THUMBPOSITION:
			VScr.nPos = HIWORD(wParam);		//�T���̈ʒu���AnPos�ɐݒ�
			break;
		}
		SetScrollInfo(hwnd,SB_VERT,&VScr,TRUE);	//�ύX���ꂽVScr�̃f�[�^���X�N���[���o�[��
		MapScrY = VScr.nPos;					//nPos�̒l��MapScrY�ɑ��

		InvalidateRect(hwnd,NULL,FALSE);	//��ʂ̍ĕ`��
		InvalidateRect(hMwnd,NULL,FALSE);	//�~�j�}�b�v�q�E�B���h�E�̍ĕ`��
		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_COMMAND:		//���j���[
		switch(LOWORD(wParam))	//LOWORD(wParam)�����ɕ���
		{
		case IDM_NEW:		//���V�K�쐬�������ꂽ��---------------------------------------------
			ZeroMemory(&Map[0][0],sizeof(int)*map_ynum*map_xnum);	//�}�b�v�`�b�v��S�ĂO
			break;

		case IDM_SAVE:		//���Z�[�u�������ꂽ��-------------------------------------------------

			ZeroMemory(&ofn,sizeof(OPENFILENAME));
			ZeroMemory(FileName,sizeof(char)*MAX_PATH);
			//ofn��FileName[]�̒��g����ɂ���B�����Y���ƁA�֐������s����ꍇ������B
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = "MapDataFiles [*.map]\0*.map\0\0";	//������̐擪�A�h���X�����B�����t�@�C����\��
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = FileName;	//�z��FileName[]�Ƀt�@�C�����������Ƃ�B
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "map";

			if(GetSaveFileName(&ofn))	//GetSaveFileName()�̖ߒl���O�ȊO�Ȃ�
			{
				GameSave(FileName);	//�}�b�v�f�[�^���Z�[�u
				MessageBox(hwnd,FileName,"����",MB_OK);	//�����B
			}else
			{
				MessageBox(hwnd,"�L�����Z���܂��͎��s","GetSaveFileName()",MB_OK);	//�L�����Z�����܂��͎��s�������Ƃ�ʒm
			}

			
			break;
		case IDM_LOAD:		//�����[�h�������ꂽ��-------------------------------------------------

			ZeroMemory(&ofn,sizeof(OPENFILENAME));
			ZeroMemory(FileName,sizeof(char)*MAX_PATH);
			//ofn��FileName[]�̒��g����ɂ���B�����Y���ƁA�֐������s����ꍇ������B
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = "MapDataFiles [*.map]\0*.map\0\0";	//������̐擪�A�h���X�����B�����t�@�C����\��
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = FileName;	//�z��FileName[]�Ƀt�@�C�����������Ƃ�B
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "map";

			if(GetOpenFileName(&ofn))	//GetOpenFileName()�̖ߒl���O�ȊO�Ȃ�
			{
				GameLoad(FileName);	//�}�b�v�f�[�^�����[�h
				MessageBox(hwnd,FileName,"����",MB_OK);	//�����B
			}else
			{
				MessageBox(hwnd,"�L�����Z���܂��͎��s","GetSaveFileName()",MB_OK);	//�L�����Z�����܂��͎��s�������Ƃ�ʒm
			}

			//-----�����X�N���[���o�[�iHSCROLL)-------
			HScr.nMax = map_xnum-WINMAP_W;	//�X�N���[���o�[�̍ő�l�i�}�b�v�̃��R�̃`�b�v�������i�\���ł��閇���������j
			HScr.nPos = 0;				//�X�N���[���o�[�̏����ʒu
			SetScrollInfo(hwnd,SB_HORZ,&HScr,TRUE);	//�X�N���[���o�[�ɁA�f�[�^��ݒ�
			//-----�����X�N���[���o�[�iVSCROLL)-------
			VScr.nMax = map_ynum-WINMAP_H;	//�X�N���[���o�[�̍ő�l�i�}�b�v�̃^�e�̃`�b�v������(�\���ł��閇��������)
			VScr.nPos = 0;				//�X�N���[���o�[�̏����ʒu
			SetScrollInfo(hwnd,SB_VERT,&VScr,TRUE);	//�X�N���[���o�[�ɁA�f�[�^��ݒ�
			break;

		case IDM_ENEON_SAVE:		//���K�o���ʒu�Z�[�u�������ꂽ��-------------------------------------------------

			ZeroMemory(&ofn,sizeof(OPENFILENAME));
			ZeroMemory(FileName,sizeof(char)*MAX_PATH);
			//ofn��FileName[]�̒��g����ɂ���B�����Y���ƁA�֐������s����ꍇ������B
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = "EneOnPosDataFiles [*.enp]\0*.enp\0\0";	//������̐擪�A�h���X�����B�����t�@�C����\��
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = FileName;	//�z��FileName[]�Ƀt�@�C�����������Ƃ�B
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "enp";

			if(GetSaveFileName(&ofn))	//GetSaveFileName()�̖ߒl���O�ȊO�Ȃ�
			{
				EneOnPosSave(FileName);	//�}�b�v�f�[�^���Z�[�u
				MessageBox(hwnd,FileName,"����",MB_OK);	//�����B
			}else
			{
				MessageBox(hwnd,"�L�����Z���܂��͎��s","GetSaveFileName()",MB_OK);	//�L�����Z�����܂��͎��s�������Ƃ�ʒm
			}
			break;
		case IDM_ENEON_LOAD:		//���K�o���ʒu���[�h�������ꂽ��-------------------------------------------------

			ZeroMemory(&ofn,sizeof(OPENFILENAME));
			ZeroMemory(FileName,sizeof(char)*MAX_PATH);
			//ofn��FileName[]�̒��g����ɂ���B�����Y���ƁA�֐������s����ꍇ������B
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = "MapDataFiles [*.enp]\0*.enp\0\0";	//������̐擪�A�h���X�����B�����t�@�C����\��
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = FileName;	//�z��FileName[]�Ƀt�@�C�����������Ƃ�B
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "enp";

			if(GetOpenFileName(&ofn))	//GetOpenFileName()�̖ߒl���O�ȊO�Ȃ�
			{
				EneOnPosLoad(FileName);	//�K�o���ʒu�f�[�^�����[�h
				MessageBox(hwnd,FileName,"����",MB_OK);	//�����B
			}else
			{
				MessageBox(hwnd,"�L�����Z���܂��͎��s","GetSaveFileName()",MB_OK);	//�L�����Z�����܂��͎��s�������Ƃ�ʒm
			}
			break;

		case IDM_ENEMY_ZERO:	//�K�o���ʒu�̏�����
												// ���ő�o���ʒu�������Ă���
			ZeroMemory(&EneOn[0],sizeof(ENE_ONPOS)*EneOnPos_Max.x);	//�}�b�v�`�b�v��S�ĂO
			break;

		case IDM_END:		//���I���������ꂽ��------------------------------------------------------
			if(IDYES == MessageBox(hwnd,"�{���ɏI�����܂���?","�v���O�����̏I��",MB_YESNO))
			{	//�{���ɏI�����邩�m�F����B
				DestroyWindow(hwnd);	//�E�B���h�E�����B
			}
			break;

		case IDM_TOOL_0:
			ToolNum = 0;
			InvalidateRect(hCwnd,NULL,FALSE);	//�q�E�B���h�E�̍ĕ`��
			break;

		case IDM_TOOL_1:
			ToolNum = 1;
			InvalidateRect(hCwnd,NULL,FALSE);	//�q�E�B���h�E�̍ĕ`��
			break;
		}
		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_PAINT:			//�E�B���h�E���ĕ`�悳�ꂽ��AInvalidateRect��WM_PAINT���b�Z�[�W������ꂽ��
	
		BeginPaint(hwnd,&ps);	//�`��J�n(ps�́APAINTSTRUCT�^�\���́j

/*���̃R�����g���͂����Ɠr���ŉ�ʂ������
		SetMenu(hCwnd,NULL);	//���j���[��\���i�`�b�v�E�B���h�E
		SetMenu(hMwnd,NULL);	//���j���[��\���i�~�j�}�b�v�E�B���h�E

		//���j���[�\��//
		if(my < 25)		//�}�E�XY���W��40��菬����������
			SetMenu(hwnd,hMenu);	//���j���[�\��
		else
		{
			SetMenu(hwnd,NULL);		//���j���[��\��
		}	
*/		
		//�`�b�v�\��//
		for(y = 0;y < WINMAP_H;y++)	//�^�eWINMAP_H��	//��ʂɕ\���ł��閇���������\���i20)
		{
			if(y >= map_ynum) break;//�����A�z��̗ʈȏ�ɕ\�����悤�Ƃ�����Abreak
			for(x = 0;x < WINMAP_W;x++)	//���RWINMAP_W��
			{
				if(x >= map_xnum) break;
				BitBlt(hMemDC,x * TIP_W,y * TIP_H,TIP_W,TIP_H,
					hTipDC,Map[y+MapScrY][x+MapScrX]%BMPTIP_W*TIP_W,Map[y+MapScrY][x+MapScrX]/BMPTIP_W*TIP_H,SRCCOPY);	//�R�s�[��x���AMap���狁�߂�B
			}
		}
		
		//���W�\��
		SetTextColor(hMemDC,RGB(255,255,255));	//�����̐F���w��
		SetBkMode(hMemDC,TRANSPARENT);			//�����𓧖���
		wsprintf(str,"X = %d / %d :Y = %d / %d ",MapScrX+(mx/TIP_W),MAP_XNUM,MapScrY+(my/TIP_H),MAP_YNUM);	//MapScrX�Ȃǂ𕶎���ɒu��������
		TextOut(hMemDC,0,0,str,lstrlen(str));					//�}�E�X�Ŏw���Ă���}�b�v�̍��W��\��
		
		//���ݔz�u�����G�̐��𐔂���
		for(i = 0;i < EneOnPos_Max.x;i++)
		{
			if(EneOn[i].OnFlag)
			{
				EneOnFlagNum++;
			}
		}
		wsprintf(str,"leftEnemy = %d    �폜Num = %d",EneOnPos_Max.x-EneOnFlagNum,DelEneOn);
		TextOut(hMemDC,350,0,str,lstrlen(str));

		if(EneOnTool)	//�G�l�~�[�z�u���[�h�Ȃ�
		{	//�ݒu����G�l�~�[�̎�ނ�\��
			wsprintf(str,"EnemyType = %d",EneTypeNum);
			TextOut(hMemDC,0,20,str,lstrlen(str));

			wsprintf(str,"EneOnPos_Max.x :%d",EneOnPos_Max.x);
			TextOut(hMemDC,0,210,str,lstrlen(str));

		}else			//�����łȂ��Ȃ�
		{	//�`�b�v�̎�ނ�\��
			wsprintf(str,"TipNum = %d",TipNum);
			TextOut(hMemDC,0,20,str,lstrlen(str));
		}

		//�G�l�~�[�o���ʒu�\��
		if(EneOnTool)	//�G�l�~�[�\���@�\��TRUE�Ȃ�
		{
			for(i = 0;i < EneOnPos_Max.x ;i++)	//�K�o���|�C���g�̐������J��Ԃ�
			{
				if(EneOn[i].OnFlag)	//�o���t���O��TRUE�Ȃ�
				{
					if(((EneOn[i].x > (MapScrX*TIP_W)) && (EneOn[i].x < (MapScrX*TIP_W+640)))
					&& ((EneOn[i].y > (MapScrY*TIP_H)) && (EneOn[i].y < (MapScrY*TIP_H+480))))	//�G�l�~�[�o���|�C���g����ʓ��Ȃ�
					{
						SetTextColor(hMemDC,RGB(0,255,0));	//�����̐F���w��
						SetBkMode(hMemDC,TRANSPARENT);			//�����𓧖���
						wsprintf(str,"�_En%d(%d)",EneOn[i].type,i);
						TextOut(hMemDC,EneOn[i].x-(MapScrX*TIP_W),EneOn[i].y-(MapScrY*TIP_H),str,lstrlen(str));	//�G�l�~�[�o���ʒu��"��"��\��
					}				
				}
			}
		}

		if(EneOnTool)	//�G�l�~�[�o���ʒu�z�u�@�\��TRUE�Ȃ�
		{
			SetTextColor(hMemDC,RGB(255,255,0));	
			wsprintf(str,"�_En%d(%s)",EneTypeNum,EneName[EneTypeNum]);
			TextOut(hMemDC,mx,my,str,lstrlen(str));	//�}�E�X���W�ɕ����\��
		}
		else			//�@�\��FALSE�Ȃ�
		{
			BitBlt(hMemDC,mx-(TIP_W>>1),my-(TIP_H>>1),TIP_W,TIP_H,
					hTipDC,TipNum%BMPTIP_W*TIP_W,TipNum/BMPTIP_W*TIP_H,SRCPAINT);		//���ݑI�𒆂̃`�b�v���}�E�X���W�ɕ\��
		}
		//BitBlt(hMemDC,0,0,(TIP_W>>3)*map_xnum,(TIP_H>>3)*map_ynum,hMinMemDC,0,0,SRCCOPY);	//�~�j�}�b�v�p���z��ʕ\��

		BitBlt(ps.hdc,0,0,TIP_W*WINMAP_W,TIP_H*WINMAP_H,hMemDC,0,0,SRCCOPY);			//����ʂɕ`��


		EndPaint(hwnd,&ps);					//�`��I���iBeginPaint()�Ŏ擾�����f�[�^���������j
		InvalidateRect(hMwnd,NULL,FALSE);	//�q�E�B���h�E�̍ĕ`��

		break;					//switch�����ʂ���
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_DESTROY:		//WM_DESTROY���b�Z�[�W�i�E�B���h�E�I���j�������ꍇ�BPostQuitMessage(0);�ŁA�I�����b�Z�[�W���o���B(GetMessage()���O��߂��Awhile�I���j
		MY_DELETEDC(hMemDC);		//���z��ʁi������DC�j������iNULL�����j
		MY_DELETEDC(hMinMemDC);		//�~�j�}�b�v�q�E�B���h�E�p���z��ʂ��J��
		MY_DELETEDC(hTipDC);		//�w�i�̊G������iNULL�����j
		DestroyMenu(hMenu);			//���j���[�����
		PostQuitMessage(0);			//�I���̃��b�Z�[�W�𑗂�
		break;						//switch�����ʂ���
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	default:				//�v�������������W���̏������s��
		return DefWindowProc(hwnd,message,wParam,lParam);	//�ǂ�case�ɂ����Ă͂܂�Ȃ��ꍇ�A�W���̏������s���B
	}
	return 0;						//�E�B���h�E�v���V�[�W���̖߂�l
}


