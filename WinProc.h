
#if !defined __WINPROC	//もし、マクロが定義されていなければ
#define __WINPROC		//マクロを定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	#include <windows.h>	//Windows用ヘッダファイル（Windowsで使用する命令やデータ型がまとめられている）
	
   ///プロトタイプ宣言///
	LRESULT CALLBACK WinProc(HWND,UINT,WPARAM,LPARAM);	//ウィンドウプロシージャ(WinProcのプロトタイプ宣言）//WinProc()のプロトタイプ宣言（本体は41～51）
	
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif