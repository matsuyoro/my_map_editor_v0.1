#include <windows.h>
#
#include "extern.h"		//�O���ϐ��������w�b�_�t�@�C��

//�q�E�B���h�E�p�̃E�B���h�E�֐��\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
LRESULT CALLBACK MinMapWinProc(HWND hMwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//�����ϐ��錾
	PAINTSTRUCT ps;
	int i,j;
	char str[50];	//�����������

	int Box_X,Box_Y,Box_W,Box_H;	//�\���ʒu��\���l�p�̐��̍��W������

	

	switch(msg)	//���b�Z�[�W�̎�ނŕ���
	{
	case WM_KEYDOWN:		//�L�[�{�[�h����������	
		switch(wParam)			//wParam�ŉ������{�^������������
		{
		case VK_NUMPAD6:	//��NUMPAD�̂U�L�[����������
			MinW_ScrX++;	//�~�j�}�b�v�q�E�B���h�E�����ɃX�N���[��������
			if(MinW_ScrX > map_xnum)	MinW_ScrX = map_xnum;
			break;
		case VK_NUMPAD4:
			MinW_ScrX--;
			if(MinW_ScrX < 0)	MinW_ScrX = 0;
			break;
		case VK_NUMPAD8:
			MinW_ScrY--;
			if(MinW_ScrY < 0)	MinW_ScrY = 0;
			break;
		case VK_NUMPAD2:
			MinW_ScrY++;
			if(MinW_ScrY > map_ynum)	MinW_ScrY = map_ynum;
			break;
		default:					//���ǂ�case�Ɉ�v���Ȃ�������
			break;						//switch�����ʂ���
		}
		InvalidateRect(hMwnd,NULL,FALSE);	//��ʂ̍ĕ`��
		InvalidateRect(hwnd,NULL,FALSE);	//�e�E�B���h�E�̍ĕ`��

		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_PAINT:	//�`��
		BeginPaint(hMwnd,&ps);	//�`��J�n(ps�́APAINTSTRUCT�^�\���́j
	
		HPEN hPen;		//�쐬�����y��������
		HPEN hPenOld;		//�Â��y����ۑ�����

		hPen = CreatePen(PS_DOT,1,RGB(255,0,0));
		//�����A�����R,�ԐF�̃y�����쐬���AhPen�ɕۑ�
		hPenOld = (HPEN)SelectObject(ps.hdc,hPen);
		//hMemDC�ɁAhPen��ݒ�B����܂Ŏg���Ă����y���́AhPenOld�ɕۑ����Ă����B
		
	
		//8����1�`�b�v�\��//
		for(i = 0;i < map_ynum - MinW_ScrY;i++)
		{
			if(i >= map_ynum) break;//�����A�z��̗ʈȏ�ɕ\�����悤�Ƃ�����Abreak
			for(j = 0;j < map_xnum - MinW_ScrX;j++)	
			{
				if(j >= map_xnum) break;
				BitBlt(ps.hdc,j * (TIP_W>>3),i * (TIP_H>>3),(TIP_W>>3),(TIP_H>>3),
					hMinMemDC,(Map[i+MinW_ScrY][j+MinW_ScrX]%BMPTIP_W)*(TIP_W>>3),((Map[i+MinW_ScrY][j+MinW_ScrX]/BMPTIP_W)*(TIP_H>>3)),SRCCOPY);	//�R�s�[��x���AMap���狁�߂�B
			}
		}
/*
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
*/
		/*
		for(i = 0;i<TIP_W;i++)
			for(j = 0;j<TIP_H;j++)
				for(k = 0;k<2;k++)
					BitBlt(ps.hdc,(i<<1)+k,(TIP_H+(j<<1))+k,1,1,hTipDC,(TipNum*TIP_W)+i,j,SRCCOPY);	//�I�𒆂̃`�b�v��2�{�ŕ\��
		*/

		if(EneOnTool)	//�G�l�~�[�\���@�\��TRUE�Ȃ�
		{
			for(i = 0;i < EneOnPos_Max.x ;i++)	//�K�o���|�C���g�̐������J��Ԃ�
			{
				if(EneOn[i].OnFlag)	//�o���t���O��TRUE�Ȃ�
				{
					SetTextColor(ps.hdc,RGB(255,255,0));	//�����̐F���w��
					SetBkMode(ps.hdc,TRANSPARENT);			//�����𓧖���
					wsprintf(str,"�_En%d",EneOn[i].type);
					TextOut(ps.hdc,(EneOn[i].x>>3)-(MinW_ScrX*(TIP_W>>3)),(EneOn[i].y>>3)-(MinW_ScrY*(TIP_H>>3)),str,lstrlen(str));	//�G�l�~�[�o���ʒu��"��"��\��
				}
			}
		}

/*
		//�}�b�v�ύX�������̉�ʂ͈̔͂�����킷����\��
		MoveToEx(ps.hdc,MapScrX*(TIP_W>>3),MapScrY*(TIP_W>>3),NULL);
		LineTo(ps.hdc,MapScrX*(TIP_W>>3)+(WINMAP_W*(TIP_W>>3)),MapScrY*(TIP_W>>3));
		LineTo(ps.hdc,MapScrX*(TIP_W>>3)+(WINMAP_W*(TIP_W>>3)),MapScrY*(TIP_W>>3)+(WINMAP_H*(TIP_W>>3)));
		LineTo(ps.hdc,MapScrX*(TIP_W>>3),MapScrY*(TIP_W>>3)+(WINMAP_H*(TIP_W>>3)));
		LineTo(ps.hdc,MapScrX*(TIP_W>>3),MapScrY*(TIP_W>>3));
*/
		//�}�b�v�ύX�������̉�ʂ͈̔͂�����킷����\��
		//�l�p�̍��W�̌v�Z�����炩���߂��Ă���
		Box_X = MapScrX*(TIP_W>>3)-(MinW_ScrX*(TIP_W>>3));	//�l�p�̍���X���W���v�Z���Ă���
		Box_W = WINMAP_W*(TIP_W>>3);						//�l�p�̉������v�Z���Ă���
		Box_Y = MapScrY*(TIP_H>>3)-(MinW_ScrY*(TIP_H>>3));
		Box_H = WINMAP_H*(TIP_H>>3);

		MoveToEx(ps.hdc,Box_X		,Box_Y			,NULL);
		LineTo(ps.hdc,Box_X+Box_W	,Box_Y			);
		LineTo(ps.hdc,Box_X+Box_W	,Box_Y+Box_H	);
		LineTo(ps.hdc,Box_X			,Box_Y+Box_H	);
		LineTo(ps.hdc,Box_X			,Box_Y			);

		SetBkMode(ps.hdc,TRANSPARENT);			//�����𓧖���
		wsprintf(str,"%d:%d",MinW_ScrX,MinW_ScrY);
		TextOut(ps.hdc,0,0,str,lstrlen(str));	//�G�l�~�[�o���ʒu��"��"��\��


		//���z�������̃~�j�}�b�v�`�b�v��\��
		//BitBlt(ps.hdc,0,0,TIP_W*WINMAP_W,TIP_H*WINMAP_H,hMemDC,0,TIP_H*WINMAP_H,SRCCOPY);			//����ʂɕ`��

		SelectObject(ps.hdc,hPenOld);	//�y�������ɖ߂�
		DeleteObject(hPen);			//�쐬�����y���̍폜

		EndPaint(hMwnd,&ps);		//�`��I���iBeginPaint()�Ŏ擾�����f�[�^���������j
		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_LBUTTONDOWN:	//�}�E�X�̍��N���b�N���ꂽ��
	
		if((LOWORD(lParam) / (TIP_W>>3)) >= map_xnum-WINMAP_W-MinW_ScrX)	//�}�b�v�f�[�^�̉��̔z����I�[�o�[���悤�Ƃ�����
			MapScrX = map_xnum-WINMAP_W;							//�z��̍ő��ݒ�
		else													//�z����I�[�o�[���ĂȂ�������
			MapScrX = (LOWORD(lParam) / (TIP_W>>3))+MinW_ScrX;					//�}�E�X�̍��W�̕�����ݒ�

		if((HIWORD(lParam) / (TIP_H>>3)) >= map_ynum-WINMAP_H-MinW_ScrY)	//�ύX���Ă���}�b�v�f�[�^�̏c�̔z�񂪃I�[�o�[���Ă�����
			MapScrY = map_ynum-WINMAP_H;							//�z��̍ő��ݒ�
		else													//�z����I�[�o�[���ĂȂ�������
			MapScrY = (HIWORD(lParam) / (TIP_H>>3))+MinW_ScrY;					//�}�E�X�̍��W�𕔕���ݒ�
		
		//�ύX���ꂽVScr�̃f�[�^���X�N���[���o�[��
		VScr.nPos = MapScrY;//MapScrY�̒l��nPos�ɑ��
		HScr.nPos = MapScrX;//MapScrX�̒l��nPos�ɑ��

		InvalidateRect(hMwnd,NULL,FALSE);	//�~�j�}�b�v�q�E�B���h�E��ʂ̍ĕ`��
		InvalidateRect(hwnd,NULL,FALSE);	//�e�E�B���h�E��ʂ̍ĕ`��
		break;
	default:		//�ǂ�case���ɂ��Ă͂܂�Ȃ�������
		//return CallWindowProc((int(_stdcall *)(void))WinProc,hMwnd,msg,wParam,lParam);
		return DefWindowProc(hMwnd,msg,wParam,lParam);
	}
	return 0;
}
