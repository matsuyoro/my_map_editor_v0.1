/////////////////// Windows Skeleton Program Sample //////////////////////////////
//①include、プロトタイプ宣言、外部変数、マクロなど（１～３行目）―――――――――――――――――――――――――――――――――
#include <windows.h>				//Windows用のヘッダーファイル(windowsで使用する命令やデータ型がまとめられている)
#include "resource.h"				//リソースを使うのに必要なヘッダファイル

#include "define.h"					//マクロ用のヘッダファイル

#include "WinProc.h"				//ウィンドウプロシージャのプロトタイプ宣言が入っているヘッダファイル
#include "ChildWinProc.h"			//子ウィンドウプロシージャのプロトタイプ宣言のヘッダファイル
#include "MinMapWinProc.h"			//ミニマップ子ウィンドウのプロトタイプ宣言のヘッダファイル
#include "Global.h"					//外部変数をまとめたヘッダファイル、WinMain()のあるソースにだけインクルード
#pragma comment(lib,"winmm.lib")	//timeGetTime()を使用するのに必要なヘッダファイル

HANDLE hMutex;			//ミューテックスのハンドルをうけとる変数。外部変数にしておくとよい。

//②ＷｉｎＭａｉｎ関数～内部変数の宣言（４～７行目）―――――――――――――――――――――――――――――――――――
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpszArgs,int nWinMode)		//WinMain関数の開始。(引数は自動で値をうけとる)
//WinMain関数の開始。プログラム実行後、この関数が最初に呼び出される。引数が４つあるが、自動的に値をうけとるので、うけとるだけでよい。
{
	//HWND		hwnd;
	//ウィンドウハンドルを扱う、hwndの宣言。19行目でウィンドウハンドルをうけとり、保存する。
	MSG			msg;
	//メッセージを使う構造体msgの宣言。34～40のメッセージループで使用。
	WNDCLASS	wcls;
	//クラス定義用の構造体。ｳｨﾝﾄﾞｳｸﾗｽのパラメータを扱う構造体、wclsの宣言。８～18行目で使用

	hInst = hInstance;
	//hInstに、インスタンスハンドルのコピーをする。（ウィンドウプロシージャで使用）


	hMutex = CreateMutex(NULL,FALSE,"ミューテックス名");	//ミューテックスを作成する
	if(GetLastError() == ERROR_ALREADY_EXISTS)	//GetLastErrorは（最後に起きたエラーが）
	{	//もし同じ名前のミューテックスが存在しているためにエラーになったら
		MessageBox(NULL,"すでに起動しています","エラー",MB_OK);	//エラーを表示
		return 0;												//WinMain()終了
	}

//③ウィンドウクラス設定・作成（８～１８行目）――――――――――――――――――――――――――――――――――――
	//	ウィンドウ・クラス定義部
	wcls.hInstance = hInstance;							//インスタンスハンドル
	//WinMain()の引数のhInstanceをそのまま代入。
	wcls.lpszClassName = WIN_CLASSNAME;					//クラス名
	//３行目の文字列型配列を使う。
	wcls.lpfnWndProc = (WNDPROC)WinProc;				//ウィンドウプロシージャ
	//ウィンドウプロシージャにしたい関数の関数名。
	wcls.style = 0;										//クラスのスタイル
	//クラスのスタイル。０でよい。
	wcls.hIcon = LoadIcon(NULL,IDI_APPLICATION);		//アイコンのハンドル
	//アイコンの種類を指定する。LoadIcon()で今回は通常のアイコンを選択
	wcls.hCursor = LoadCursor(NULL,IDC_ARROW);			//カーソルのハンドル
	//カーソルの種類を指定する。LoadCursor()で今回は通常のカーソルを選択
	wcls.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);		//クラスのメニュー
	//
	wcls.cbClsExtra = 0;								//拡張用のパラメータ
	//・・・０
	wcls.cbWndExtra = 0;								//拡張用のパラメータ
	//・・・０
	
	//----------作成ウィンドウ・バックグラウンドカラー設定部---------------------------------------------
	wcls.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	//ウィンドウの背景色。GetStockObject()を使って指定。WHITE_BRUSHで、白色を指定。

	//-----------ウィンドウ・クラス作成部-------------------------------------------------------------------
	if(!RegisterClass (&wcls))	//値を代入したwclsを使って、ウィンドウクラスを設定。失敗した場合、０を戻してWindowsMain()終了
	{
		CloseHandle(hMutex);	//WinMain()を強制終了する時は、ミューテックスを解放しておく
		return 0;
	}

//④ウィンドウ作成（１９～３０行目）――――――――――――――――――――――――――――――――――――――――――――――――――――――――
	//	表示ウィンドウ・スタイル設定部


	//親ウィンドウ//
	RECT rc;
	rc.left = 0; rc.right = 640;	//rcに、クライアント領域の大きさを代入
	rc.top = 0; rc.bottom = 480;
	AdjustWindowRect(&rc,			//rcのメンバには正しいウィンドウの大きさが入る。
	WS_SYSMENU | WS_CAPTION | WS_HSCROLL | WS_VSCROLL | WS_CLIPCHILDREN,		//CreateWindow()と同じウィンドウスタイル
	FALSE);							//メニュー無しの場合、FALSE	メニュー有りの場合、TRUE

	hwnd = CreateWindow(
	//CreateWindow()で、ウィンドウを作り、hwndに、ウィンドウハンドルを保存。
						WIN_CLASSNAME,			//クラス名
						WIN_TITLE,				//ウィンドウのタイトル
						(WS_SYSMENU | WS_CAPTION | WS_HSCROLL | WS_VSCROLL ),//| WS_CLIPCHILDREN),	//ウィンドウのスタイル
						CW_USEDEFAULT,			//ウィンドウの左上Ｘ座標
						CW_USEDEFAULT,			//ウィンドウの左上Ｙ座標
						rc.right-rc.left,		//ウィンドウの幅(AdjustWindowRectで求めた値で正しい幅を指定
						rc.bottom-rc.top-15,	//ウィンドウの高さ(AdjustWindowRectで正しい高さー１５（メニューバーを表示したり非表示にする分の高さ
						NULL,					//親ウィンドウのハンドル。今回は０。
						NULL,					//メニューのハンドル。今回は０。
						hInstance,				//インスタンスハンドル(WinMain()の第１引数、hInstanceをそのまま使う)
						NULL					//拡張用のパラメータ・・・０
						);	//戻値として、作成されたウィンドウのウィンドウハンドルを戻す。（hwndに保存）
						//※CW_USEDEFAULTは、デフォルトの値を表す。ウィンドウの幅、高さなどは、各自で変更するとよい。(「640」などの定数が使える）
	
	//子ウィンドウ//
	hCwnd = CreateWindow(
	//CreateWindow()で、ウィンドウを作り、hCwndに、ウィンドウハンドルを保存。
						WIN_CLASSNAME,			//クラス名
						"子ウィンドウ",				//ウィンドウのタイトル
						(WS_POPUP | WS_OVERLAPPEDWINDOW),	//ウィンドウのスタイル
						CW_USEDEFAULT,			//ウィンドウの左上Ｘ座標
						CW_USEDEFAULT,			//ウィンドウの左上Ｙ座標
						CWIN_W,					//ウィンドウの幅
						CWIN_H,					//ウィンドウの高さ
						hwnd,					//親ウィンドウのハンドル(hwnd)
						NULL,					//メニューのハンドル。今回は０。
						hInstance,				//インスタンスハンドル(WinMain()の第１引数、hInstanceをそのまま使う)
						NULL					//拡張用のパラメータ・・・０
						);	//戻値として、作成されたウィンドウのウィンドウハンドルを戻す。（hwndに保存）
						//※CW_USEDEFAULTは、デフォルトの値を表す。ウィンドウの幅、高さなどは、各自で変更するとよい。(「640」などの定数が使える）
	SetWindowLong(hCwnd,GWL_WNDPROC,(LONG)ChildWinProc);	//hCwndにChildWinProc()を設定する。
	
	//ミニマップ子ウィンドウ//
	hMwnd = CreateWindow(
	//CreateWindow()で、ウィンドウを作り、hMwndに、ウィンドウハンドルを保存。
						WIN_CLASSNAME,			//クラス名
						"ミニマップ子ウィンドウ",				//ウィンドウのタイトル
						WS_POPUP | WS_OVERLAPPEDWINDOW,	//ウィンドウのスタイル
						CW_USEDEFAULT,			//ウィンドウの左上Ｘ座標
						CW_USEDEFAULT,			//ウィンドウの左上Ｙ座標
						MWIN_W,					//ウィンドウの幅
						MWIN_H,					//ウィンドウの高さ
						hwnd,					//親ウィンドウのハンドル(hwnd)
						NULL,					//メニューのハンドル。今回は０。
						hInstance,				//インスタンスハンドル(WinMain()の第１引数、hInstanceをそのまま使う)
						NULL					//拡張用のパラメータ・・・０
						);	//戻値として、作成されたウィンドウのウィンドウハンドルを戻す。（hwndに保存）
						//※CW_USEDEFAULTは、デフォルトの値を表す。ウィンドウの幅、高さなどは、各自で変更するとよい。(「640」などの定数が使える）
	SetWindowLong(hMwnd,GWL_WNDPROC,(LONG)MinMapWinProc);	//hCwndにChildWinProc()を設定する。
	
	//　ウィンドウ描画部
	//ウィンドウの表示開始	hwndを使って表示するウィンドウを指定している。
	//親ウィンドウ//
	ShowWindow(hwnd,nWinMode);							//ウィンドウ作成開始
	UpdateWindow(hwnd);									//ウィンドウ表示開始
	//子ウィンドウ//
	ShowWindow(hCwnd,nWinMode);							//子ウィンドウ作成開始
	UpdateWindow(hCwnd);								//子ウィンドウ表示開始
	//ミニマップ子ウィンドウ//
	ShowWindow(hMwnd,nWinMode);							//ミニマップ子ウィンドウ作成開始
	UpdateWindow(hMwnd);								//ミニマップ子ウィンドウ表示開始

//⑤メッセージ・ループ（３４～４０行目）――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
	while(GetMessage(&msg,NULL,0,0))	//メッセージの取得
	{
		TranslateMessage(&msg);		//メッセージ変換
		DispatchMessage(&msg);		//メッセージを送る
	}



	CloseHandle(hMutex);	//ミューテックスの解放
	return msg.wParam;		//終了時の戻値（msg.wParam）を戻し、WinMain終了
}



