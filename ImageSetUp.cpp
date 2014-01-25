////////インクルード///////////
#include <windows.h>	//Windows用のヘッダーファイル(windowsで使用する命令やデータ型がまとめられている)

/////////関数本体/////////////////
//■――――――――――――――――――――――――――――――――――――――――――――――――――――――――
BOOL LoadBmp(char *pFileName,HDC hdc,HDC *phBmpDC,HINSTANCE hInst)	//機能：BMPファイルを準備する関数
//●引数１：読み込むファイル名
//●引数２：ウィンドウのHDC
//●引数３：作成されたHDCをうけとるアドレス
//●引数４：LoadImageで使用するインスタンスハンドル
{
//内部変数宣言
HBITMAP hBit;	//ビットマップハンドルhBitを宣言
char str[256];	//エラーメッセージで扱う文字列を扱う変数

//絵のデータ準備
hBit = (HBITMAP)LoadImage(hInst,pFileName,			//引数１のファイル名(pFIleName)のデータを読み込む
						  IMAGE_BITMAP,0,0,			//0,0で自動で読み込む画像の大きさを自動で設定
						  LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//読み込みフラグ
if(!hBit)		//LoadImage()に失敗したら(NULLなら)
{
	wsprintf(str,"%sの用意に失敗(LoadImage)",pFileName);	//LoadImageに失敗したファイル名を文字列に置き換える
	MessageBox(NULL,str,"エラー",MB_OK);					//エラーをメッセージボックスで表示
	return FALSE;											//FALSEを戻す
}

*phBmpDC = CreateCompatibleDC(hdc);		//hCharDC（メモリDC）を作成
if(!*phBmpDC)	//CreateCompatibleDC()に失敗したら(NULLなら)
{
	wsprintf(str,"%sのHDC作成に失敗(CreateCompatibleDC)",pFileName);	//CreateComaptibleDCに失敗したファイル名を文字列に置き換える
	MessageBox(NULL,str,"エラー",MB_OK);								//エラーをメッセージボックスで表示
	DeleteObject(hBit);													//成功したLoadImage()のhBitは解放
	return FALSE;														//FALSEを戻す
}

SelectObject(*phBmpDC,hBit);		//hCharDCにビットマップハンドルを選択
DeleteObject(hBit);					//ビットマップハンドルhBitを解放
return TRUE;						//成功したらTRUEを渡す
}

//■―――――――――――――――――――――――――――――――――――――――――――――――――――――
int CharAnime(int *pCharHai,int HaiMax,int LoopAni)	//キャラアニメーション
//●引数１：キャラアニメの配列の先頭アドレス
//●引数２：配列の要素数
//●引数３：アニメーションを表示し終わって戻るループ先
{
	static int AniTime;	//１枚の絵の表示時間を扱う
	static int HaiNum;	//配列の要素番号を扱う

	AniTime--;		//１枚の絵の表示時間を毎回ー１
	if(AniTime < 0)
	{
		HaiNum++;	//次の要素番号へ
		if(HaiNum >= (HaiMax))	HaiNum = LoopAni;	//限界を超えないようにループ
		AniTime = pCharHai[HaiNum];	//指定した配列の要素番号の値を代入
	}
	return(HaiNum);	//配列の要素番号を戻す
}
