#include <windows.h>
#
#include "extern.h"		//外部変数を扱うヘッダファイル

//子ウィンドウ用のウィンドウ関数―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
LRESULT CALLBACK MinMapWinProc(HWND hMwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	//内部変数宣言
	PAINTSTRUCT ps;
	int i,j;
	char str[50];	//文字列を扱う

	int Box_X,Box_Y,Box_W,Box_H;	//表示位置を表す四角の線の座標を扱う

	

	switch(msg)	//メッセージの種類で分岐
	{
	case WM_KEYDOWN:		//キーボードを押したら	
		switch(wParam)			//wParamで押したボタンを条件分岐
		{
		case VK_NUMPAD6:	//○NUMPADの６キーを押したら
			MinW_ScrX++;	//ミニマップ子ウィンドウを横にスクロールさせる
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
		default:					//●どのcaseに一致しなかったら
			break;						//switch文をぬける
		}
		InvalidateRect(hMwnd,NULL,FALSE);	//画面の再描画
		InvalidateRect(hwnd,NULL,FALSE);	//親ウィンドウの再描画

		break;
	//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_PAINT:	//描画
		BeginPaint(hMwnd,&ps);	//描画開始(psは、PAINTSTRUCT型構造体）
	
		HPEN hPen;		//作成したペンを扱う
		HPEN hPenOld;		//古いペンを保存する

		hPen = CreatePen(PS_DOT,1,RGB(255,0,0));
		//実線、太さ３,赤色のペンを作成し、hPenに保存
		hPenOld = (HPEN)SelectObject(ps.hdc,hPen);
		//hMemDCに、hPenを設定。それまで使っていたペンは、hPenOldに保存しておく。
		
	
		//8分の1チップ表示//
		for(i = 0;i < map_ynum - MinW_ScrY;i++)
		{
			if(i >= map_ynum) break;//もし、配列の量以上に表示しようとしたら、break
			for(j = 0;j < map_xnum - MinW_ScrX;j++)	
			{
				if(j >= map_xnum) break;
				BitBlt(ps.hdc,j * (TIP_W>>3),i * (TIP_H>>3),(TIP_W>>3),(TIP_H>>3),
					hMinMemDC,(Map[i+MinW_ScrY][j+MinW_ScrX]%BMPTIP_W)*(TIP_W>>3),((Map[i+MinW_ScrY][j+MinW_ScrX]/BMPTIP_W)*(TIP_H>>3)),SRCCOPY);	//コピー元xを、Mapから求める。
			}
		}
/*
		//チップ表示//
		for(y = 0;y < WINMAP_H;y++)	//タテWINMAP_H枚	//画面に表示できる枚数分だけ表示（20)
		{
			if(y >= map_ynum) break;//もし、配列の量以上に表示しようとしたら、break
			for(x = 0;x < WINMAP_W;x++)	//ヨコWINMAP_W枚
			{
				if(x >= map_xnum) break;
				BitBlt(hMemDC,x * TIP_W,y * TIP_H,TIP_W,TIP_H,
					hTipDC,Map[y+MapScrY][x+MapScrX]%BMPTIP_W*TIP_W,Map[y+MapScrY][x+MapScrX]/BMPTIP_W*TIP_H,SRCCOPY);	//コピー元xを、Mapから求める。
			}
		}
*/
		/*
		for(i = 0;i<TIP_W;i++)
			for(j = 0;j<TIP_H;j++)
				for(k = 0;k<2;k++)
					BitBlt(ps.hdc,(i<<1)+k,(TIP_H+(j<<1))+k,1,1,hTipDC,(TipNum*TIP_W)+i,j,SRCCOPY);	//選択中のチップを2倍で表示
		*/

		if(EneOnTool)	//エネミー表示機能がTRUEなら
		{
			for(i = 0;i < EneOnPos_Max.x ;i++)	//適出現ポイントの数だけ繰り返す
			{
				if(EneOn[i].OnFlag)	//出現フラグがTRUEなら
				{
					SetTextColor(ps.hdc,RGB(255,255,0));	//文字の色を指定
					SetBkMode(ps.hdc,TRANSPARENT);			//文字を透明に
					wsprintf(str,"＼En%d",EneOn[i].type);
					TextOut(ps.hdc,(EneOn[i].x>>3)-(MinW_ScrX*(TIP_W>>3)),(EneOn[i].y>>3)-(MinW_ScrY*(TIP_H>>3)),str,lstrlen(str));	//エネミー出現位置に"●"を表示
				}
			}
		}

/*
		//マップ変更中部分の画面の範囲をあらわす線を表示
		MoveToEx(ps.hdc,MapScrX*(TIP_W>>3),MapScrY*(TIP_W>>3),NULL);
		LineTo(ps.hdc,MapScrX*(TIP_W>>3)+(WINMAP_W*(TIP_W>>3)),MapScrY*(TIP_W>>3));
		LineTo(ps.hdc,MapScrX*(TIP_W>>3)+(WINMAP_W*(TIP_W>>3)),MapScrY*(TIP_W>>3)+(WINMAP_H*(TIP_W>>3)));
		LineTo(ps.hdc,MapScrX*(TIP_W>>3),MapScrY*(TIP_W>>3)+(WINMAP_H*(TIP_W>>3)));
		LineTo(ps.hdc,MapScrX*(TIP_W>>3),MapScrY*(TIP_W>>3));
*/
		//マップ変更中部分の画面の範囲をあらわす線を表示
		//四角の座標の計算をあらかじめしておく
		Box_X = MapScrX*(TIP_W>>3)-(MinW_ScrX*(TIP_W>>3));	//四角の左上X座標を計算しておく
		Box_W = WINMAP_W*(TIP_W>>3);						//四角の横幅を計算しておく
		Box_Y = MapScrY*(TIP_H>>3)-(MinW_ScrY*(TIP_H>>3));
		Box_H = WINMAP_H*(TIP_H>>3);

		MoveToEx(ps.hdc,Box_X		,Box_Y			,NULL);
		LineTo(ps.hdc,Box_X+Box_W	,Box_Y			);
		LineTo(ps.hdc,Box_X+Box_W	,Box_Y+Box_H	);
		LineTo(ps.hdc,Box_X			,Box_Y+Box_H	);
		LineTo(ps.hdc,Box_X			,Box_Y			);

		SetBkMode(ps.hdc,TRANSPARENT);			//文字を透明に
		wsprintf(str,"%d:%d",MinW_ScrX,MinW_ScrY);
		TextOut(ps.hdc,0,0,str,lstrlen(str));	//エネミー出現位置に"●"を表示


		//仮想メモリのミニマップチップを表示
		//BitBlt(ps.hdc,0,0,TIP_W*WINMAP_W,TIP_H*WINMAP_H,hMemDC,0,TIP_H*WINMAP_H,SRCCOPY);			//実画面に描画

		SelectObject(ps.hdc,hPenOld);	//ペンを元に戻す
		DeleteObject(hPen);			//作成したペンの削除

		EndPaint(hMwnd,&ps);		//描画終了（BeginPaint()で取得したデータを解放する）
		break;
	//■――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_LBUTTONDOWN:	//マウスの左クリックされたら
	
		if((LOWORD(lParam) / (TIP_W>>3)) >= map_xnum-WINMAP_W-MinW_ScrX)	//マップデータの横の配列をオーバーしようとしたら
			MapScrX = map_xnum-WINMAP_W;							//配列の最大を設定
		else													//配列をオーバーしてなかったら
			MapScrX = (LOWORD(lParam) / (TIP_W>>3))+MinW_ScrX;					//マウスの座標の部分を設定

		if((HIWORD(lParam) / (TIP_H>>3)) >= map_ynum-WINMAP_H-MinW_ScrY)	//変更しているマップデータの縦の配列がオーバーしていたら
			MapScrY = map_ynum-WINMAP_H;							//配列の最大を設定
		else													//配列をオーバーしてなかったら
			MapScrY = (HIWORD(lParam) / (TIP_H>>3))+MinW_ScrY;					//マウスの座標を部分を設定
		
		//変更されたVScrのデータをスクロールバーに
		VScr.nPos = MapScrY;//MapScrYの値をnPosに代入
		HScr.nPos = MapScrX;//MapScrXの値をnPosに代入

		InvalidateRect(hMwnd,NULL,FALSE);	//ミニマップ子ウィンドウ画面の再描画
		InvalidateRect(hwnd,NULL,FALSE);	//親ウィンドウ画面の再描画
		break;
	default:		//どのcase分にあてはまらなかったら
		//return CallWindowProc((int(_stdcall *)(void))WinProc,hMwnd,msg,wParam,lParam);
		return DefWindowProc(hMwnd,msg,wParam,lParam);
	}
	return 0;
}
