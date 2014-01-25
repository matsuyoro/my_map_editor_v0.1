//ゲーム用のセーブ、ロードの関数本体
#include <windows.h>	//Windows用ヘッダファイル
#include "extern.h"		//外部変数になっているデータをセーブ、ロードするので、extern.hを使う。

//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void GameSave(char *pFileName)	//機能：ゲーム用のデータをセーブ(マップデータのセーブ
//●引数：セーブするファイル名
{
	HANDLE hFile;
	DWORD Dum;

	//セーブ用にファイルを準備
	hFile = CreateFile(pFileName,GENERIC_WRITE,		//(GENERIC_WRITE)書きこみ用で
						0,NULL,CREATE_ALWAYS,		//(CREATE_ALWAYS)ファイル無かったら作成、あったら元のファイルを消して作成
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFileの戻値がINVALID_HANDLE_VALUEならエラー
	{
		MessageBox(NULL,"読み込み用ファイル準備失敗","エラー[Game_SaveLoad.cpp]",MB_OK);	//エラーを通知
		return;
	}
	//外部変数になっているゲームデータのうち、必要なものをセーブする。
	//※今回は例として、int x;int y;が外部変数にあるものとして、セーブする。

	WriteFile(hFile,&map_xnum,sizeof(int),&Dum,NULL);	//マップヨコチップ数をセーブ（int型）
	WriteFile(hFile,&map_ynum,sizeof(int),&Dum,NULL);	//マップタテチップ数をセーブ（int型）
	WriteFile(hFile,&Map[0][0],sizeof(int)*map_ynum*map_xnum,&Dum,NULL);	//マップデータをセーブ
	//他にも必要なデータを、WriteFile()でセーブしておく

	//ファイルを閉じる
	CloseHandle(hFile);
	MessageBox(NULL,"セーブしました","SAVE",MB_OK);	//セーブされたかの確認メッセージ
}

//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void GameLoad(char *pFileName)	//機能：ゲーム用のデータをロードする関数（マップデータロード
//●引数：ロードするファイル名
{
	HANDLE hFile;
	DWORD Dum;
	hFile = CreateFile(pFileName,GENERIC_READ,	//(GENERIC_READ)読み込み用で
						0,NULL,OPEN_EXISTING,	//(OPEN_EXISTING)ファイルを開く、ない場合は失敗
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFileの戻値がINVALID_HANDLE_VALUEならエラー
	{
		MessageBox(NULL,"読み込み用ファイル準備失敗","エラー[Game_SaveLoad.cpp]",MB_OK);	//エラーを通知
		return;
	}
	//セーブしてあるデータをロードする。セーブした時と、同じ順番でロードすること。
	ReadFile(hFile,&map_xnum,sizeof(int),&Dum,NULL);	//マップヨコチップ数をロード（int型）
	ReadFile(hFile,&map_ynum,sizeof(int),&Dum,NULL);	//マップタテチップ数をロード（int型）
	ReadFile(hFile,&Map[0][0],sizeof(int)*map_ynum*map_xnum,&Dum,NULL);	//マップデータをロード

	if(map_xnum != MAP_XNUM || map_ynum != MAP_YNUM)	//マクロで設定した縦横のチップの数がロードした縦横チップの数とちがったら
	{
		MessageBox(NULL,"縦横のチップの数が設定と違います","map_xnum != MAP_XNUM map_ynum MAP_YNUM",MB_OK);	//設定の違いを通知
		return;
	}

	//他にもセーブしたデータがあるなら、セーブした時と同じ順番でロードする

	CloseHandle(hFile);		//解放
	MessageBox(NULL,"ロードしました","LOAD",MB_OK);	//ロードされたかの確認メッセージ
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void EneOnPosSave(char *pFileName)	//機能：適出現位置データセーブ
//●引数：セーブするファイル名
{
	HANDLE hFile;
	DWORD Dum;

	//セーブ用にファイルを準備
	hFile = CreateFile(pFileName,GENERIC_WRITE,		//(GENERIC_WRITE)書きこみ用で
						0,NULL,CREATE_ALWAYS,		//(CREATE_ALWAYS)ファイル無かったら作成、あったら元のファイルを消して作成
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFileの戻値がINVALID_HANDLE_VALUEならエラー
	{
		MessageBox(NULL,"読み込み用ファイル準備失敗","エラー[Game_SaveLoad.cpp]",MB_OK);	//エラーを通知
		return;
	}
	//外部変数になっているゲームデータのうち、必要なものをセーブする。
	WriteFile(hFile,&EneOnPos_Max,sizeof(ENE_ONPOS),&Dum,NULL);					//適出現位置最大数をセーブ（最大数はメンバxに入っている）
	WriteFile(hFile,&EneOn[0],sizeof(ENE_ONPOS) * EneOnPos_Max.x,&Dum,NULL);	//適出現位置データをセーブ
	//他にも必要なデータを、WriteFile()でセーブしておく

	//ファイルを閉じる
	CloseHandle(hFile);
	MessageBox(NULL,"適出現位置データをセーブしました","SAVE",MB_OK);	//セーブされたかの確認メッセージ
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void EneOnPosLoad(char *pFileName)	//機能：適出現位置データをロードする関数
//●引数：ロードするファイル名
{
	HANDLE hFile;
	DWORD Dum;
	hFile = CreateFile(pFileName,GENERIC_READ,			//(GENERIC_READ)読み込み用で
						0,NULL,OPEN_EXISTING,			//(OPEN_EXISTING)ファイルを開く、ない場合は失敗
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)				//CreateFileの戻値がINVALID_HANDLE_VALUEならエラー
	{
		MessageBox(NULL,"読み込み用ファイル準備失敗","エラー[Game_SaveLoad.cpp]",MB_OK);	//エラーを通知
		return;
	}
	//セーブしてあるデータをロードする。セーブした時と、同じ順番でロードすること。
	ReadFile(hFile,&EneOnPos_Max,sizeof(ENE_ONPOS),&Dum,NULL);				//適出現位置最大数をロード（最大数はメンバxに入っている）
	ReadFile(hFile,&EneOn[0],sizeof(ENE_ONPOS)*EneOnPos_Max.x,&Dum,NULL);	//適出現位置データをロード
	//他にもセーブしたデータがあるなら、セーブした時と同じ順番でロードする

	if(EneOnPos_Max.x != ENEONPOS_MAX)	//マクロで設定した値とロードした値がちがったら(まだメモリ確保でロードをしてないので　メッセージボックスで通知
	{
		MessageBox(NULL,"マクロの値とロードした適出現位置数が異なります","適出現位置数の警告",MB_OK);	//設定の違いを通知
		return;
	}


	CloseHandle(hFile);		//解放
	MessageBox(NULL,"適出現位置データをロードしました","LOAD",MB_OK);	//ロードされたかの確認メッセージ
}