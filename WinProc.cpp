/////// インクルード ///////
#include <windows.h>	//Windows用のヘッダファイル(Windowsで使用する命令やデータ型がまとめられている）
#include "resource.h"	//リソースを使うのに必要なヘッダファイル
#include "define.h"		//マクロ定義をまとめたヘッダファイル

#include "extern.h"		//外部変数をまとめたヘッダファイル（fActiveなどの宣言）
#include "File_WriteRead.h"	//File_WriteRead.cppの関数のプロトタイプ宣言のヘッダファイル
#include "Game_SaveLoad.h"	//ゲーム用のセーブロードをまとめたヘッダファイル
#include "ImageSetUp.h"		

//⑦ウィンドウ関数（ウィンドウプロシージャ）(41～51行目)37行目で送られたメッセージを処理する。――――――――――――――――――――――――――――――――――
LRESULT CALLBACK WinProc(
						 HWND hwnd,		//メッセージ発生元のウィンドウハンドル
						 UINT message,	//発生したメッセージの種類
						 WPARAM wParam,	//発生したメッセージごとに異なる細かいデータ
						 LPARAM lParam)	//発生したメッセージごとに異なる細かいデータ
{
	PAINTSTRUCT ps;			//PAINTSTRUCT型構造体psを宣言（BeginPaintなどで使用）
	char str[256];			//文字列を扱う
	int i,j;				//カウンタ変数
	int DumNum;				//変数の値を入れ替える時などに使用
	int EneOnFlagNum = 0;		//現在配置した敵の数を扱う
	static int DelEneOn =0;
	char EneName[][16] =	//配置する敵の名前をいれおく変数
	{
		{"使用禁止"},{"犬"},{"トカゲ"},{"竜"},{"メカ兵"},{"兵"},{"火人間"},{"枝"},{"鉄犬"},{"緑小動物"},{"蜂"},{"ツボ"},{"骨口"},{"八ボス体"},{"八ボス尻尾"},{"恐竜"},{"ラスボス顔"},{"ラスボス左手"},{"ラスボス右手"}
	};

	OPENFILENAME ofn;			//コモンダイアログの構造体
	char FileName[MAX_PATH];	//ファイル名、パスをうけとる配列

	switch(message)			//メッセージの種類で分岐。
	{
	//■――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_CREATE:			//ウィンドウ作成時なら

		HDC hdc;
		HBITMAP hBit;			//ビットマップハンドルhBitを宣言
		HBITMAP hMinBit;		//ミニマップ用仮想画面を作成するのに使用するビットマップハンドル
		hdc = GetDC(hwnd);		//HDC取得

		//-------------メニュ-----------------------------
		hMenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU1)); //メニューを準備して、ハンドルをhMenuに保存
		
		//-----水平スクロールバー（HSCROLL)---------------
		HScr.cbSize = sizeof(SCROLLINFO);	//スクロールバーの構造体自体のサイズを代入
		HScr.fMask = SIF_POS | SIF_RANGE;	//扱うデータの種類
		HScr.nMin = 0;						//スクロールバーの最小値
		HScr.nMax = map_xnum-WINMAP_W;				//スクロールバーの最大値（マップのヨコのチップ数を代入（表示できる枚数を引く）
		HScr.nPos = 0;						//スクロールバーの初期位置
		SetScrollInfo(hwnd,SB_HORZ,&HScr,TRUE);	//スクロールバーに、データを設定
		//-----垂直スクロールバー（VSCROLL)---------------
		VScr.cbSize = sizeof(SCROLLINFO);	//スクロールバーの構造体自体のサイズを代入
		VScr.fMask = SIF_POS | SIF_RANGE;	//扱うデータの種類
		VScr.nMin = 0;						//スクロールバーの最小値
		VScr.nMax = map_ynum-WINMAP_H;				//スクロールバーの最大値（マップのタテのチップ数を代入(表示できる枚数を引く)
		VScr.nPos = 0;						//スクロールバーの初期位置
		SetScrollInfo(hwnd,SB_VERT,&VScr,TRUE);		//スクロールバーに、データを設定


		//仮想画面作成
		hBit = CreateCompatibleBitmap(hdc,TIP_W*WINMAP_W,TIP_H*WINMAP_H);	//画面の大きさだけ指定
		hMemDC = CreateCompatibleDC(hdc);			//hMemDC（メモリDC）を作成
		SelectObject(hMemDC,hBit);					//hMemDCにhBitを選択
		DeleteObject(hBit);							//hBitの解放

		//ミニマップ子ウィンドウ用仮想画面作成
		hMinBit = CreateCompatibleBitmap(hdc,(TIP_W>>3)*WINMAP_W,(TIP_H>>3)*WINMAP_H);
		hMinMemDC = CreateCompatibleDC(hdc);		//hMinMemDCを作成
		SelectObject(hMinMemDC,hMinBit);
		DeleteObject(hMinBit);

		if(!LoadBmp("MapTip7.bmp",hdc,&hTipDC,hInst))		//マップチップの準備を定義関数で実行
			DestroyWindow(hwnd);							//WM_DESTROYメッセージを送り終了
		
		//8分の1 hTipDを仮想画面に表示(仮想画面のY座標４８０より下の方に表示し画面には見えない（これを素にミニマップのチップを表示	
		for(i = 0;i < ((TIP_H>>3)*map_ynum);i++)
		{
			for(j = 0;j < ((TIP_W>>3)*map_xnum);j++)	//ヨコWINMAP_W枚
			{
				BitBlt(hMinMemDC,j,i,1,1,
						hTipDC,j * 8,i * 8,SRCCOPY);			//コピー元xを、Mapから求める。
			}
		}


		ReleaseDC(hwnd,hdc);	//HDC解放
		

		///// 初期設定 ////////////////////////////////

		ZeroMemory(&Map[0][0],sizeof(int)*map_ynum*map_xnum);	//マップチップは最初は全て０
		ZeroMemory(&EneOn[0],sizeof(ENE_ONPOS)*EneOnPos_Max.x);	//エネミー出現位置配置のデータを最初は全て０
	

		break;
	//■―――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_RBUTTONDOWN:	//マウスの右ボタンが押されたら
		
		//mx2,my2に現在のマス単位のマウス座標を保存する。
		if(ToolNum == 1)	//四角が選択されていたら
		{
			MapMx2 = LOWORD(lParam) / TIP_W + MapScrX;	//現在のマス単位のマウスの座標を代入
			MapMy2 = HIWORD(lParam) / TIP_H + MapScrY;
		}else
		{
			//チップのスポイト
			TipNum = Map[HIWORD(lParam) / TIP_H+MapScrY][LOWORD(lParam) / TIP_W+MapScrX];	//マウスの指しているところのチップを取得
		}
		InvalidateRect(hwnd,NULL,FALSE);	//画面の再描画
		InvalidateRect(hCwnd,NULL,FALSE);	//子ウィンドウの再描画
		break;
	//■―――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_RBUTTONUP:	//マウスの左ボタンが離れたなら

		if(ToolNum == 1)	//チップを四角に描画するモードなら
		{
			MapMx = LOWORD(lParam) / TIP_W + MapScrX;	//マップ単位でのマウス座標を代入
			MapMy = HIWORD(lParam) / TIP_H + MapScrY;

			if(LOWORD(lParam) / TIP_W+MapScrX >= map_xnum ||	//変更しているx,yが配列をオーバーしていたら
				HIWORD(lParam) / TIP_H+MapScrY >= map_ynum)		break;
			
			//MapMxの方がMapMx2より大きくなるようにMapMxとMapMx２の入れ替え
			if(MapMx < MapMx2)
			{
				DumNum = MapMx;	//ダミーの変数にMapMxを保存しておく
				MapMx = MapMx2;	//MapMx2　と　MapMx　を入れ替え
				MapMx2 = DumNum;
			}
			//MapMyの方がMapMy2より大きくなるようにMapMyとMapMy２の入れ替え
			if(MapMy < MapMy2)
			{
				DumNum = MapMy;	//ダミーの変数にMapMyを保存しておく
				MapMy = MapMy2;	//MapMy2　と　MapMy　を入れ替え
				MapMy2 = DumNum;
			}

			//Rボタンをクリックしてはなしたところまでを四角で塗りつぶす
			for(i = 0;i <= (MapMy - MapMy2);i++)
			{
				for(j = 0;j <= (MapMx - MapMx2);j++)
				{			
					Map[MapMy2+i][MapMx2+j] = TipNum;	//指定の場所を指定のチップに変更
				}
			}
		}
		InvalidateRect(hwnd,NULL,FALSE);	//画面の再描画
		InvalidateRect(hMwnd,NULL,FALSE);	//ミニマップ子ウィンドウの再描画
		break;
	//■――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_LBUTTONDOWN:	//マウスの左ボタンが押されたら	
		if(EneOnTool)	//エネミー配置機能がTRUEなら
		{

			for(i = 0;i < EneOnPos_Max.x;i++)	//エネミー最大出現数分繰り返す
			{
				if(!EneOn[i].OnFlag)	//エネミー出現ポイントフラグがFALSEなら
				{
					if(LOWORD(lParam) / TIP_W+MapScrX >= map_xnum ||
					HIWORD(lParam) / TIP_H+MapScrY >= map_ynum)		//変更しているx,yが配列をオーバーしていたら
						break;

					EneOn[i].x = LOWORD(lParam) + (MapScrX*TIP_W);	//エネミー出現位置配置（注意　チップ単位で配置
					EneOn[i].y = HIWORD(lParam) + (MapScrY*TIP_H);	
					EneOn[i].type = EneTypeNum;			//エネミーの種類を設定
					EneOn[i].OnFlag = TRUE;		//設置フラグTRUE

					EneOnReturn[EneRtrnCnt] = i;	//エネミー配置番号を記録
					EneRtrnCnt++;					//次へ
					if(EneRtrnCnt >= EneOnPos_Max.x) EneRtrnCnt = 0;	//配列の最大を超えないようにする 
					break;
				}
			}

		}else	//エネミー配置機能がFALSEなら
		{
			if(LOWORD(lParam) / TIP_W+MapScrX >= map_xnum ||
			HIWORD(lParam) / TIP_H+MapScrY >= map_ynum)		//変更しているx,yが配列をオーバーしていたら
				break;

			Map[HIWORD(lParam) / TIP_H+MapScrY][LOWORD(lParam) / TIP_W+MapScrX] = TipNum;	//マウスの指しているチップを変更
		}		
		InvalidateRect(hwnd,NULL,FALSE);	//画面の再描画
		InvalidateRect(hMwnd,NULL,FALSE);	//ミニマップ子ウィンドウの再描画
		break;

	//■―――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_MOUSEMOVE:		//マウスが動いたら
		mx = LOWORD(lParam);		//マウスX座標を代入
		my = HIWORD(lParam);		//マウスY座標を代入

		if(!EneOnTool)	//エネミー配置機能がFALSEなら
		{
			if(wParam & MK_LBUTTON)	//左クリックされたら
			{	//マップチップ配置
				if(LOWORD(lParam) / TIP_W+MapScrX >= map_xnum ||
					HIWORD(lParam) / TIP_H+MapScrY >= map_ynum)		//変更しているx,yが配列をオーバーしていたら
					break;
				Map[HIWORD(lParam) / TIP_H+MapScrY][LOWORD(lParam) / TIP_W+MapScrX] = TipNum;	//マウスの指しているチップを変更
			}
		}

		InvalidateRect(hwnd,NULL,FALSE);	//画面の再描画
		break;
	//■――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_KEYDOWN:		//キーボードを押したら	

		switch(wParam)	//wParamで押したボタンを条件分岐
		{
		case VK_LEFT:	//●左が押されたら
			if(EneOnTool)		//エネミー配置モードがTRUEなら
			{
				EneTypeNum--;		//エネミーの種類を選ぶ
				if(EneTypeNum < 1) EneTypeNum = 1;	//エネミーの種類の限界を超えないようにする
			}else
			{
				TipNum--;			//TipNumは０～４の範囲で変化する
				if(TipNum < 0)	TipNum = 0;	//選択しているチップの種類が限界をこえないように戻す
			}

			break;
		case VK_RIGHT:	//●右が押されたら
			if(EneOnTool)			//エネミー配置モードがTRUEなら
			{
				EneTypeNum++;
				if(EneTypeNum > ENETYPE_MAX)	EneTypeNum = ENETYPE_MAX;
			}else
			{
				TipNum++;				//次の番号のチップに
				TipNum %= TIP_MAX;
			}
			break;

		case VK_UP:					//●上が押されたら
			TipNum -= BMPTIP_W;
			TipNum %= TIP_MAX;
			if(TipNum < 0)	TipNum = 0;
			break;

		case VK_DOWN:				//●下が押されたら
			TipNum += BMPTIP_W;
			TipNum %= TIP_MAX;
			break;


		//マップスクロール
		case VK_NUMPAD4:					//NUMPAD4が押されたら
			HScr.nPos --;		//スクロールバーの値をー１
			if(HScr.nPos < HScr.nMin)	//最小値より小さかったら
				HScr.nPos = HScr.nMin;	//最小値より小さくならないようにする
			break;
		case VK_NUMPAD6:					//押されたら
			HScr.nPos++;		//スクロールバーの値を+1
			if(HScr.nPos > HScr.nMax)	//最大値より大きくなったら
				HScr.nPos = HScr.nMax;	//最大値より大きくならないようにする
			break;
		case VK_NUMPAD8:					
			VScr.nPos --;		//スクロールバーの値をー１
			if(VScr.nPos < VScr.nMin)	//最小値より小さかったら
				VScr.nPos = VScr.nMin;	//最小値より小さくならないようにする
			break;
		case VK_NUMPAD2:
			VScr.nPos++;		//スクロールバーの値を+1
			if(VScr.nPos > VScr.nMax)	//最大値より大きくなったら
				VScr.nPos = VScr.nMax;	//最大値より大きくならないようにする
			break;

		case VK_SPACE:	//スペースキーを押すと　マップ作成モードと適配置モードを切り替えられる
			if(!EneOnTool)	//エネミー表示機能がFALSEなら
				EneOnTool = TRUE;	//エネミー表示	
			else			
				EneOnTool = FALSE;	//エネミー非表示
			break;

		case 0x41:	//●Aキー(削除するエネミーを選択
			if(DelEneOn > 0)	DelEneOn--;
			break;
		case 0x53:	//●Sキー(削除するエネミーを選択
			if(DelEneOn < EneOnPos_Max.x-1)	DelEneOn++;
			break;
		case 0x44:	//●Dキー
			ZeroMemory(&EneOn[DelEneOn],sizeof(ENE_ONPOS));	//DelEneONで指定したデータをゼロメモリ
			break;

		case VK_F11:	//●F11キー（エネミー出現位置の配置を戻す					

			EneRtrnCnt--;				//１つ前へ
			if(EneRtrnCnt < 0)	EneRtrnCnt = EneOnPos_Max.x-1;	//0より小さくなると配列の最大数に
			ZeroMemory(&EneOn[EneOnReturn[EneRtrnCnt]],sizeof(ENE_ONPOS));	//配置データを空に													
			break;

		case VK_F12:	//●F12キー			
			break;

		case VK_SUBTRACT:	//●「-」キー
			SetMenu(hCwnd,NULL);	//メニュー非表示（チップウィンドウ
			SetMenu(hMwnd,NULL);	//メニュー非表示（ミニマップウィンドウ

			//メニュー表示//
			if(my < 25)		//マウスY座標が40より小さかったら
				SetMenu(hwnd,hMenu);	//メニュー表示
			else
			{
				SetMenu(hwnd,NULL);		//メニュー非表示
			}	
			break;

		case VK_ESCAPE:				//●ESCキー （終了
			DestroyWindow(hwnd);		//ウィンドウ終了。ウィンドウに、WM_DESTROYメッセージを強制的に出される。
			break;						//switch文をぬける
		
		default:					//●どのcaseに一致しなかったら
			break;						//switch文をぬける
		}

		SetScrollInfo(hwnd,SB_HORZ,&HScr,TRUE);	//変更されたHScrのデータをスクロールバーに
		MapScrX = HScr.nPos;
		SetScrollInfo(hwnd,SB_VERT,&VScr,TRUE);	//変更されたVScrのデータをスクロールバーに
		MapScrY = VScr.nPos;					//nPosの値をMapScrYに代入

		InvalidateRect(hwnd,NULL,FALSE);	//画面の再描画
		InvalidateRect(hCwnd,NULL,FALSE);	//子ウィンドウの再描画
		InvalidateRect(hMwnd,NULL,FALSE);	//ミニマップ子ウィンドウの再描画
		break;					//switch分をぬける
	//■――――――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_HSCROLL:		//水平スクロールバー

		switch(LOWORD(wParam))
		{
		case SB_LINELEFT:	//[←]が押されたら
			HScr.nPos --;		//スクロールバーの値をー１
			if(HScr.nPos < HScr.nMin)	//最小値より小さかったら
				HScr.nPos = HScr.nMin;	//最小値より小さくならないようにする
			break;
		case SB_LINERIGHT:	//[→]が押されたら
			HScr.nPos++;		//スクロールバーの値を+1
			if(HScr.nPos > HScr.nMax)	//最大値より大きくなったら
				HScr.nPos = HScr.nMax;	//最大値より大きくならないようにする
			break;
		case SB_PAGELEFT:	//[←]とサムの間が押されたら
			HScr.nPos -= 5;
			if(HScr.nPos < HScr.nMin)	//最小値より小さくならにようにする
				HScr.nPos = HScr.nMin;
			break;
		case SB_PAGERIGHT:	//[→]とサムの間が押されたら
			HScr.nPos += 5;
			if(HScr.nPos > HScr.nMax)	//最大値より大きくならないようにする
				HScr.nPos = HScr.nMax;
			break;
		case SB_THUMBTRACK:	//サムがドラッグ＆ドロップされているなら
		case SB_THUMBPOSITION:
			HScr.nPos = HIWORD(wParam);		//サムの位置を、nPosに設定
			break;
		}
		SetScrollInfo(hwnd,SB_HORZ,&HScr,TRUE);	//変更されたHScrのデータをスクロールバーに
		MapScrX = HScr.nPos;

		InvalidateRect(hwnd,NULL,FALSE);	//画面の再描画
		InvalidateRect(hMwnd,NULL,FALSE);	//ミニマップ子ウィンドウの再描画
		break;
	//■――――――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_VSCROLL:		//垂直スクロールバー

		switch(LOWORD(wParam))
		{
		case SB_LINEUP:	//[▲]が押されたら
			VScr.nPos --;		//スクロールバーの値をー１
			if(VScr.nPos < VScr.nMin)	//最小値より小さかったら
				VScr.nPos = VScr.nMin;	//最小値より小さくならないようにする
			break;
		case SB_LINEDOWN:	//[▼]が押されたら
			VScr.nPos++;		//スクロールバーの値を+1
			if(VScr.nPos > VScr.nMax)	//最大値より大きくなったら
				VScr.nPos = VScr.nMax;	//最大値より大きくならないようにする
			break;
		case SB_PAGEUP:	//[▼]とサムの間が押されたら
			VScr.nPos -= 5;
			if(VScr.nPos < VScr.nMin)	//最小値より小さくならにようにする
				VScr.nPos = VScr.nMin;
			break;
		case SB_PAGEDOWN:	//[→]とサムの間が押されたら
			VScr.nPos += 5;
			if(VScr.nPos > VScr.nMax)	//最大値より大きくならないようにする
				VScr.nPos = VScr.nMax;
			break;
		case SB_THUMBTRACK:	//サムがドラッグ＆ドロップされているなら
		case SB_THUMBPOSITION:
			VScr.nPos = HIWORD(wParam);		//サムの位置を、nPosに設定
			break;
		}
		SetScrollInfo(hwnd,SB_VERT,&VScr,TRUE);	//変更されたVScrのデータをスクロールバーに
		MapScrY = VScr.nPos;					//nPosの値をMapScrYに代入

		InvalidateRect(hwnd,NULL,FALSE);	//画面の再描画
		InvalidateRect(hMwnd,NULL,FALSE);	//ミニマップ子ウィンドウの再描画
		break;
	//■―――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_COMMAND:		//メニュー
		switch(LOWORD(wParam))	//LOWORD(wParam)を元に分岐
		{
		case IDM_NEW:		//●新規作成が押されたら---------------------------------------------
			ZeroMemory(&Map[0][0],sizeof(int)*map_ynum*map_xnum);	//マップチップを全て０
			break;

		case IDM_SAVE:		//●セーブが押されたら-------------------------------------------------

			ZeroMemory(&ofn,sizeof(OPENFILENAME));
			ZeroMemory(FileName,sizeof(char)*MAX_PATH);
			//ofnとFileName[]の中身を空にする。これを忘れると、関数が失敗する場合がある。
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = "MapDataFiles [*.map]\0*.map\0\0";	//文字列の先頭アドレスを代入。扱うファイルを表す
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = FileName;	//配列FileName[]にファイル名をうけとる。
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "map";

			if(GetSaveFileName(&ofn))	//GetSaveFileName()の戻値が０以外なら
			{
				GameSave(FileName);	//マップデータをセーブ
				MessageBox(hwnd,FileName,"成功",MB_OK);	//成功。
			}else
			{
				MessageBox(hwnd,"キャンセルまたは失敗","GetSaveFileName()",MB_OK);	//キャンセルかまたは失敗したことを通知
			}

			
			break;
		case IDM_LOAD:		//●ロードが押されたら-------------------------------------------------

			ZeroMemory(&ofn,sizeof(OPENFILENAME));
			ZeroMemory(FileName,sizeof(char)*MAX_PATH);
			//ofnとFileName[]の中身を空にする。これを忘れると、関数が失敗する場合がある。
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = "MapDataFiles [*.map]\0*.map\0\0";	//文字列の先頭アドレスを代入。扱うファイルを表す
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = FileName;	//配列FileName[]にファイル名をうけとる。
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "map";

			if(GetOpenFileName(&ofn))	//GetOpenFileName()の戻値が０以外なら
			{
				GameLoad(FileName);	//マップデータをロード
				MessageBox(hwnd,FileName,"成功",MB_OK);	//成功。
			}else
			{
				MessageBox(hwnd,"キャンセルまたは失敗","GetSaveFileName()",MB_OK);	//キャンセルかまたは失敗したことを通知
			}

			//-----水平スクロールバー（HSCROLL)-------
			HScr.nMax = map_xnum-WINMAP_W;	//スクロールバーの最大値（マップのヨコのチップ数を代入（表示できる枚数を引く）
			HScr.nPos = 0;				//スクロールバーの初期位置
			SetScrollInfo(hwnd,SB_HORZ,&HScr,TRUE);	//スクロールバーに、データを設定
			//-----垂直スクロールバー（VSCROLL)-------
			VScr.nMax = map_ynum-WINMAP_H;	//スクロールバーの最大値（マップのタテのチップ数を代入(表示できる枚数を引く)
			VScr.nPos = 0;				//スクロールバーの初期位置
			SetScrollInfo(hwnd,SB_VERT,&VScr,TRUE);	//スクロールバーに、データを設定
			break;

		case IDM_ENEON_SAVE:		//●適出現位置セーブが押されたら-------------------------------------------------

			ZeroMemory(&ofn,sizeof(OPENFILENAME));
			ZeroMemory(FileName,sizeof(char)*MAX_PATH);
			//ofnとFileName[]の中身を空にする。これを忘れると、関数が失敗する場合がある。
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = "EneOnPosDataFiles [*.enp]\0*.enp\0\0";	//文字列の先頭アドレスを代入。扱うファイルを表す
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = FileName;	//配列FileName[]にファイル名をうけとる。
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "enp";

			if(GetSaveFileName(&ofn))	//GetSaveFileName()の戻値が０以外なら
			{
				EneOnPosSave(FileName);	//マップデータをセーブ
				MessageBox(hwnd,FileName,"成功",MB_OK);	//成功。
			}else
			{
				MessageBox(hwnd,"キャンセルまたは失敗","GetSaveFileName()",MB_OK);	//キャンセルかまたは失敗したことを通知
			}
			break;
		case IDM_ENEON_LOAD:		//●適出現位置ロードが押されたら-------------------------------------------------

			ZeroMemory(&ofn,sizeof(OPENFILENAME));
			ZeroMemory(FileName,sizeof(char)*MAX_PATH);
			//ofnとFileName[]の中身を空にする。これを忘れると、関数が失敗する場合がある。
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFilter = "MapDataFiles [*.enp]\0*.enp\0\0";	//文字列の先頭アドレスを代入。扱うファイルを表す
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = FileName;	//配列FileName[]にファイル名をうけとる。
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_HIDEREADONLY | OFN_NONETWORKBUTTON | OFN_OVERWRITEPROMPT;
			ofn.lpstrDefExt = "enp";

			if(GetOpenFileName(&ofn))	//GetOpenFileName()の戻値が０以外なら
			{
				EneOnPosLoad(FileName);	//適出現位置データをロード
				MessageBox(hwnd,FileName,"成功",MB_OK);	//成功。
			}else
			{
				MessageBox(hwnd,"キャンセルまたは失敗","GetSaveFileName()",MB_OK);	//キャンセルかまたは失敗したことを通知
			}
			break;

		case IDM_ENEMY_ZERO:	//適出現位置の初期化
												// ↓最大出現位置が入っている
			ZeroMemory(&EneOn[0],sizeof(ENE_ONPOS)*EneOnPos_Max.x);	//マップチップを全て０
			break;

		case IDM_END:		//●終了が押されたら------------------------------------------------------
			if(IDYES == MessageBox(hwnd,"本当に終了しますか?","プログラムの終了",MB_YESNO))
			{	//本当に終了するか確認する。
				DestroyWindow(hwnd);	//ウィンドウを閉じる。
			}
			break;

		case IDM_TOOL_0:
			ToolNum = 0;
			InvalidateRect(hCwnd,NULL,FALSE);	//子ウィンドウの再描画
			break;

		case IDM_TOOL_1:
			ToolNum = 1;
			InvalidateRect(hCwnd,NULL,FALSE);	//子ウィンドウの再描画
			break;
		}
		break;
	//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_PAINT:			//ウィンドウが再描画されたら、InvalidateRectでWM_PAINTメッセージが送られたら
	
		BeginPaint(hwnd,&ps);	//描画開始(psは、PAINTSTRUCT型構造体）

/*このコメントをはずすと途中で画面がちらつく
		SetMenu(hCwnd,NULL);	//メニュー非表示（チップウィンドウ
		SetMenu(hMwnd,NULL);	//メニュー非表示（ミニマップウィンドウ

		//メニュー表示//
		if(my < 25)		//マウスY座標が40より小さかったら
			SetMenu(hwnd,hMenu);	//メニュー表示
		else
		{
			SetMenu(hwnd,NULL);		//メニュー非表示
		}	
*/		
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
		
		//座標表示
		SetTextColor(hMemDC,RGB(255,255,255));	//文字の色を指定
		SetBkMode(hMemDC,TRANSPARENT);			//文字を透明に
		wsprintf(str,"X = %d / %d :Y = %d / %d ",MapScrX+(mx/TIP_W),MAP_XNUM,MapScrY+(my/TIP_H),MAP_YNUM);	//MapScrXなどを文字列に置き換える
		TextOut(hMemDC,0,0,str,lstrlen(str));					//マウスで指しているマップの座標を表示
		
		//現在配置した敵の数を数える
		for(i = 0;i < EneOnPos_Max.x;i++)
		{
			if(EneOn[i].OnFlag)
			{
				EneOnFlagNum++;
			}
		}
		wsprintf(str,"leftEnemy = %d    削除Num = %d",EneOnPos_Max.x-EneOnFlagNum,DelEneOn);
		TextOut(hMemDC,350,0,str,lstrlen(str));

		if(EneOnTool)	//エネミー配置モードなら
		{	//設置するエネミーの種類を表示
			wsprintf(str,"EnemyType = %d",EneTypeNum);
			TextOut(hMemDC,0,20,str,lstrlen(str));

			wsprintf(str,"EneOnPos_Max.x :%d",EneOnPos_Max.x);
			TextOut(hMemDC,0,210,str,lstrlen(str));

		}else			//そうでないなら
		{	//チップの種類を表示
			wsprintf(str,"TipNum = %d",TipNum);
			TextOut(hMemDC,0,20,str,lstrlen(str));
		}

		//エネミー出現位置表示
		if(EneOnTool)	//エネミー表示機能がTRUEなら
		{
			for(i = 0;i < EneOnPos_Max.x ;i++)	//適出現ポイントの数だけ繰り返す
			{
				if(EneOn[i].OnFlag)	//出現フラグがTRUEなら
				{
					if(((EneOn[i].x > (MapScrX*TIP_W)) && (EneOn[i].x < (MapScrX*TIP_W+640)))
					&& ((EneOn[i].y > (MapScrY*TIP_H)) && (EneOn[i].y < (MapScrY*TIP_H+480))))	//エネミー出現ポイントが画面内なら
					{
						SetTextColor(hMemDC,RGB(0,255,0));	//文字の色を指定
						SetBkMode(hMemDC,TRANSPARENT);			//文字を透明に
						wsprintf(str,"＼En%d(%d)",EneOn[i].type,i);
						TextOut(hMemDC,EneOn[i].x-(MapScrX*TIP_W),EneOn[i].y-(MapScrY*TIP_H),str,lstrlen(str));	//エネミー出現位置に"●"を表示
					}				
				}
			}
		}

		if(EneOnTool)	//エネミー出現位置配置機能がTRUEなら
		{
			SetTextColor(hMemDC,RGB(255,255,0));	
			wsprintf(str,"＼En%d(%s)",EneTypeNum,EneName[EneTypeNum]);
			TextOut(hMemDC,mx,my,str,lstrlen(str));	//マウス座標に文字表示
		}
		else			//機能がFALSEなら
		{
			BitBlt(hMemDC,mx-(TIP_W>>1),my-(TIP_H>>1),TIP_W,TIP_H,
					hTipDC,TipNum%BMPTIP_W*TIP_W,TipNum/BMPTIP_W*TIP_H,SRCPAINT);		//現在選択中のチップをマウス座標に表示
		}
		//BitBlt(hMemDC,0,0,(TIP_W>>3)*map_xnum,(TIP_H>>3)*map_ynum,hMinMemDC,0,0,SRCCOPY);	//ミニマップ用仮想画面表示

		BitBlt(ps.hdc,0,0,TIP_W*WINMAP_W,TIP_H*WINMAP_H,hMemDC,0,0,SRCCOPY);			//実画面に描画


		EndPaint(hwnd,&ps);					//描画終了（BeginPaint()で取得したデータを解放する）
		InvalidateRect(hMwnd,NULL,FALSE);	//子ウィンドウの再描画

		break;					//switch文をぬける
	//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――
	case WM_DESTROY:		//WM_DESTROYメッセージ（ウィンドウ終了）だった場合。PostQuitMessage(0);で、終了メッセージを出す。(GetMessage()が０を戻し、while終了）
		MY_DELETEDC(hMemDC);		//仮想画面（メモリDC）を解放（NULLを代入）
		MY_DELETEDC(hMinMemDC);		//ミニマップ子ウィンドウ用仮想画面を開放
		MY_DELETEDC(hTipDC);		//背景の絵を解放（NULLを代入）
		DestroyMenu(hMenu);			//メニューを解放
		PostQuitMessage(0);			//終了のメッセージを送る
		break;						//switch文をぬける
	//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
	default:				//Ｗｉｎｄｏｗｓ標準の処理を行う
		return DefWindowProc(hwnd,message,wParam,lParam);	//どのcaseにも当てはまらない場合、標準の処理を行う。
	}
	return 0;						//ウィンドウプロシージャの戻り値
}


