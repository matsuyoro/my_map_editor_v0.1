#include <windows.h>
#include "extern.h"		//�O���ϐ��������w�b�_�t�@�C��

//�q�E�B���h�E�p�̃E�B���h�E�֐��\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
LRESULT CALLBACK ChildWinProc(HWND hCwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//�����ϐ��錾
	PAINTSTRUCT ps;
	//char str[50];	//�����������
	int TNrgb = 0;	//�����F������


	switch(msg)	//���b�Z�[�W�̎�ނŕ���
	{
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_PAINT:	//�`��
		BeginPaint(hCwnd,&ps);	//�`��J�n(ps�́APAINTSTRUCT�^�\���́j

		BitBlt(ps.hdc,0,0,TIP_W*BMPTIP_W,TIP_H*BMPTIP_H,hTipDC,0,0,SRCCOPY);	//�`�b�v��`��

		//�I�𒆂̃`�b�v���w������
		SetTextColor(ps.hdc,RGB(255,TipNum*50%255,0));	//�����̐F���w��
		SetBkMode(ps.hdc,TRANSPARENT);			//�����𓧖���
		TextOut(ps.hdc,TipNum%BMPTIP_W*TIP_W+(TIP_W/2-8),TipNum/BMPTIP_W*TIP_H-8,"��",lstrlen("��"));	//�����\��
		TextOut(ps.hdc,TipNum%BMPTIP_W*TIP_W+(TIP_W/2-8),TipNum/BMPTIP_W*TIP_H+(TIP_H-8),"��",lstrlen("��"));	//�����\��

		SetBkMode(ps.hdc,TRANSPARENT);		//�����𓧖���

		SetTextColor(ps.hdc,RGB(120,120,120));					//�����ɐF���w��
		TextOut(ps.hdc,TIP_W*BMPTIP_W,0,"�y��",lstrlen("�y��"));		//�����\��
		SetTextColor(ps.hdc,RGB(120,120,120));					//�����ɐF���w��
		TextOut(ps.hdc,TIP_W*BMPTIP_W,20,"�l�p",lstrlen("�l�p"));		//�����\��

		switch(ToolNum)	//ToolNum�����ɕ���
		{
		case 0:	//�y�����I������Ă�����
			SetTextColor(ps.hdc,RGB(255,255,255));					//�����ɐF���w��
			TextOut(ps.hdc,TIP_W*BMPTIP_W,0,"�y��",lstrlen("�y��"));		//�����\��
			SetTextColor(ps.hdc,RGB(0,0,0));					//�����ɐF���w��
			SetBkMode(ps.hdc,OPAQUE);		//������񓧖���
			TextOut(ps.hdc,0,TIP_H*BMPTIP_H,"���N���b�N�Ń`�b�v��ݒu",lstrlen("���N���b�N�Ń`�b�v��ݒu"));
			break;
		case 1:	//�l�p���I������Ă�����
			SetTextColor(ps.hdc,RGB(255,255,255));					//�����ɐF���w��
			TextOut(ps.hdc,TIP_W*BMPTIP_W,20,"�l�p",lstrlen("�l�p"));		//�����\��
			SetTextColor(ps.hdc,RGB(0,0,0));					//�����ɐF���w��
			SetBkMode(ps.hdc,OPAQUE);		//������񓧖���
			TextOut(ps.hdc,0,TIP_H*BMPTIP_H,"�E�h���b�O�Ŏl�p���`�b�v��ݒu",lstrlen("�E�h���b�O�Ŏl�p���`�b�v��`��"));
			break;
		}

		/*
		for(i = 0;i<TIP_W;i++)
			for(j = 0;j<TIP_H;j++)
				for(k = 0;k<2;k++)
					BitBlt(ps.hdc,(i<<1)+k,(TIP_H+(j<<1))+k,1,1,hTipDC,(TipNum*TIP_W)+i,j,SRCCOPY);	//�I�𒆂̃`�b�v��2�{�ŕ\��
		*/

		EndPaint(hCwnd,&ps);		//�`��I���iBeginPaint()�Ŏ擾�����f�[�^���������j
		break;
	//���\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	case WM_LBUTTONDOWN:	//�}�E�X�̍��N���b�N���ꂽ��
		
		TipNum = (LOWORD(lParam) / TIP_W)+(HIWORD(lParam) / TIP_W *BMPTIP_W);	//�`�b�v���擾
		if(TipNum > TIP_MAX)	TipNum = TIP_MAX;	//���E�����
		
		InvalidateRect(hCwnd,NULL,FALSE);	//�q�E�B���h�E��ʂ̍ĕ`��
		InvalidateRect(hwnd,NULL,FALSE);	//�e�E�B���h�E��ʂ̍ĕ`��
		break;
	default:		//�ǂ�case���ɂ��Ă͂܂�Ȃ�������
		//return CallWindowProc((int(_stdcall *)(void))WinProc,hCwnd,msg,wParam,lParam);
		return DefWindowProc(hCwnd,msg,wParam,lParam);
	}
	return 0;

}
