#include <windows.h>
#include "extern.h"		//外部変数を扱うヘッダファイル

//子ウィンドウ用のウィンドウ関数―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
LRESULT CALLBACK ChildWinProc(HWND hCwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//内部変数宣言
	PAINTSTRUCT ps;
	//char str[50];	//文字列を扱う
	int TNrgb = 0;	//文字色を扱う


	switch(msg)	//メッセージの種類で分岐
	{
	//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_PAINT:	//描画
		BeginPaint(hCwnd,&ps);	//描画開始(psは、PAINTSTRUCT型構造体）

		BitBlt(ps.hdc,0,0,TIP_W*BMPTIP_W,TIP_H*BMPTIP_H,hTipDC,0,0,SRCCOPY);	//チップを描画

		//選択中のチップを指す文字
		SetTextColor(ps.hdc,RGB(255,TipNum*50%255,0));	//文字の色を指定
		SetBkMode(ps.hdc,TRANSPARENT);			//文字を透明に
		TextOut(ps.hdc,TipNum%BMPTIP_W*TIP_W+(TIP_W/2-8),TipNum/BMPTIP_W*TIP_H-8,"▼",lstrlen("▼"));	//文字表示
		TextOut(ps.hdc,TipNum%BMPTIP_W*TIP_W+(TIP_W/2-8),TipNum/BMPTIP_W*TIP_H+(TIP_H-8),"▲",lstrlen("▲"));	//文字表示

		SetBkMode(ps.hdc,TRANSPARENT);		//文字を透明に

		SetTextColor(ps.hdc,RGB(120,120,120));					//文字に色を指定
		TextOut(ps.hdc,TIP_W*BMPTIP_W,0,"ペン",lstrlen("ペン"));		//文字表示
		SetTextColor(ps.hdc,RGB(120,120,120));					//文字に色を指定
		TextOut(ps.hdc,TIP_W*BMPTIP_W,20,"四角",lstrlen("四角"));		//文字表示

		switch(ToolNum)	//ToolNumを元に分岐
		{
		case 0:	//ペンが選択されていたら
			SetTextColor(ps.hdc,RGB(255,255,255));					//文字に色を指定
			TextOut(ps.hdc,TIP_W*BMPTIP_W,0,"ペン",lstrlen("ペン"));		//文字表示
			SetTextColor(ps.hdc,RGB(0,0,0));					//文字に色を指定
			SetBkMode(ps.hdc,OPAQUE);		//文字を非透明に
			TextOut(ps.hdc,0,TIP_H*BMPTIP_H,"左クリックでチップを設置",lstrlen("左クリックでチップを設置"));
			break;
		case 1:	//四角が選択されていたら
			SetTextColor(ps.hdc,RGB(255,255,255));					//文字に色を指定
			TextOut(ps.hdc,TIP_W*BMPTIP_W,20,"四角",lstrlen("四角"));		//文字表示
			SetTextColor(ps.hdc,RGB(0,0,0));					//文字に色を指定
			SetBkMode(ps.hdc,OPAQUE);		//文字を非透明に
			TextOut(ps.hdc,0,TIP_H*BMPTIP_H,"右ドラッグで四角くチップを設置",lstrlen("右ドラッグで四角くチップを描画"));
			break;
		}

		/*
		for(i = 0;i<TIP_W;i++)
			for(j = 0;j<TIP_H;j++)
				for(k = 0;k<2;k++)
					BitBlt(ps.hdc,(i<<1)+k,(TIP_H+(j<<1))+k,1,1,hTipDC,(TipNum*TIP_W)+i,j,SRCCOPY);	//選択中のチップを2倍で表示
		*/

		EndPaint(hCwnd,&ps);		//描画終了（BeginPaint()で取得したデータを解放する）
		break;
	//■――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_LBUTTONDOWN:	//マウスの左クリックされたら
		
		TipNum = (LOWORD(lParam) / TIP_W)+(HIWORD(lParam) / TIP_W *BMPTIP_W);	//チップを取得
		if(TipNum > TIP_MAX)	TipNum = TIP_MAX;	//限界を作る
		
		InvalidateRect(hCwnd,NULL,FALSE);	//子ウィンドウ画面の再描画
		InvalidateRect(hwnd,NULL,FALSE);	//親ウィンドウ画面の再描画
		break;
	default:		//どのcase分にあてはまらなかったら
		//return CallWindowProc((int(_stdcall *)(void))WinProc,hCwnd,msg,wParam,lParam);
		return DefWindowProc(hCwnd,msg,wParam,lParam);
	}
	return 0;

}
