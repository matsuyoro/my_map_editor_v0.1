#include <windows.h>	//windows用ヘッダファイル

//■――――――――――――――――――――――――――――――――――――――――――――――――――
void DataSave(char *pFileName,void *pData,DWORD DataSize)	//機能：セーブする関数
//●引数１：ファイル名
//●引数２：セーブしたいデータの先頭アドレス
//●引数３：セーブするデータの量
{
	HANDLE hFile;
	DWORD Dum;
	//セーブ用にファイルを準備
	hFile = CreateFile(pFileName,GENERIC_WRITE,	//(GENERIC_WRITE)書きこみ用で
						0,NULL,CREATE_ALWAYS,	//(CREATE_ALWAYS)ファイルが無かったら作成、あったら元のデータを消して、作成
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFileの戻値がINVALID_HANDLE_VALUEならエラー
	{
		//※メッセージボックス等でエラーを知らせる
		MessageBox(NULL,"書きこみ用ファイル準備失敗","エラー",MB_OK);	//エラーを通知
		return;
	}
	//データをセーブする
	WriteFile(hFile,pData,DataSize,&Dum,NULL);	//セーブ先のハンドルhFileにpDataをセーブ
	//ファイルを閉じる
	CloseHandle(hFile);							//解放
}
//■―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
void DataLoad(char *pFileName,void *pData,DWORD DataSize)	//機能：ロードする関数
//●引数１：ファイル名
//●引数２：ロードしたデータをうけとる場所の先頭アドレス
//●引数３：ロードするデータの量
{
	HANDLE hFile;
	DWORD Dum;
	//ロード用にファイルを準備
	hFile = CreateFile(pFileName,GENERIC_READ,	//(GENERIC_READ)読み込み用で
						0,NULL,OPEN_EXISTING,	//(OPEN_EXISTING)ファイルを開く、なかったら失敗
						FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)	//CreateFileの戻値がINVALID_HANDLE_VALUEならエラー
	{
		//※エラーを知らせる
		MessageBox(NULL,"読み込み用ファイル準備失敗","エラー",MB_OK);	//エラーを通知
		return;
	}
	//データをロードする
	ReadFile(hFile,pData,DataSize,&Dum,NULL);	//ロードするファイルのハンドルhFileをpDataにロード
	//ファイルを閉じる
	CloseHandle(hFile);						//解放
}
