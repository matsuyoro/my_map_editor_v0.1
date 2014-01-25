//ゲームのメイン処理をまとめる
#include <windows.h>	//Windows用ヘッダファイル
#include "extern.h"		//WinMain()以外で外部変数を使うためのヘッダファイル
#include "ImageSetUp.h"	//アニメーション関数のプロトタイプ宣言(CharAnime())
/*------------------------------------------------------------------------------------------------------
　　ゲームのメイン処理をまとめた関数メッセージループ内、PeekMessageのif文のelse部分で実行
　　引数　：　HWND・・・ウィンドウのハンドル
------------------------------------------------------------------------------------------------------*/
void GameMain(HWND hwnd)
{
	HDC hdc;
	char str[256];	//文字列を扱う変数
	//int i;			//カウンタ変数
	int Dum;		//十字キーをビット単位のフラグで扱う（現在の十字キーを扱う）
	//int Dum2;		//十字キーのデータを扱う(前回の十字キーを扱う）
	static int A;	//Aボタンを押した瞬間に＋１される
	static int B;
	static int C;
	static int D;
	int AniPtnDum;	//CharAnime()の戻値を保存しておくの使う
	static int Map[4][5];	//タテ４枚、ヨコ５枚のマップ
	ZeroMemory(&Map[0][0],sizeof(int)*4*5);	//最小は全て０


	//ジョイスティックなど、入力の取得
	MMRESULT ret;
	JoyData2 = JoyData;							//前回の値として、JoyDataを保存
	ret = joyGetPosEx(JOYSTICKID1,&JoyData);	//JoyDataの中にジョイスティックのデータが入る（JoyDataを更新）
	if(ret != JOYERR_NOERROR)					//retがJOYERR_NOERRORじゃなかったら
		MessageBox(NULL,"ジョイスティックの取得に失敗","エラー",MB_OK);	//エラー表示
	Dum = 0;					//Dumは0（0000 [0]）でスタート
	if(JoyData.dwXpos <= 10000)	//左が押されていたら
		Dum |= 1;					//０ビット目を１に（0001 [1]）
	if(JoyData.dwYpos <= 10000)	//上が押されていたら
		Dum |= (1<<1);				//１ビット目を１に（0010 [2]）
	if(JoyData.dwXpos >= 50000)	//右が押されていたら
		Dum |= (1<<2);				//２ビット目を１に（0100 [4]）
	if(JoyData.dwYpos >= 50000)	//下が押されていたら
		Dum |= (1<<3);				//３ビット目を１に（1000 [8]）
	
	//Ａボタンを押した瞬間
	if((JoyData.dwButtons & 1) && !(JoyData2.dwButtons & 1))	//今回(押)で、かつ前回(離)だったら
	{
		A++;	//押した瞬間の処理
	}
	//離した瞬間
	if(!(JoyData.dwButtons & 1) && (JoyData2.dwButtons & 1))	//今回(離)で、かつ前回(押)だったら
	{
		B++;	//離した瞬間の処理
	}
	//押しっぱなし
	if((JoyData.dwButtons & 1) && (JoyData2.dwButtons & 1))		//今回(押)で、かつ前回(押)だったら
	{
		C++;	//押しっぱなしの処理
	}
	//離しっぱなし
	if(!(JoyData.dwButtons & 1) && !(JoyData2.dwButtons & 1))	//今回(離)で、かつ前回(離)だったら
	{
		D++;	//離しっぱなしの処理
	}

	//ゲームのデータ処理
	x %= 640;	//0～640
	y %= 480;	//0～480
	AniPtnDum = 128*CharAnime(AniPtn,15,2);	//CharAnime()の戻値を代入(128は1枚の絵のサイズ)

	//判定など（今は特に無し）

	//描画
	hdc = GetDC(hwnd);		//HDC取得


	/*
	BitBlt(hMemDC,0,0,640,480,hBackDC,0,0,SRCCOPY);		//仮想画面に背景を描画
	BitBlt(hMemDC,x,y,128,128,hCharMaskDC,AniPtnDum,0,SRCAND);	//仮想画面にキャラマスクを描画
	BitBlt(hMemDC,x,y,128,128,hCharDC,AniPtnDum,0,SRCPAINT);	//仮想画面にキャラを描画
	*/
	

	//フレームレート表示
	SetBkMode(hMemDC,TRANSPARENT);						//文字背景を透明に
	wsprintf(str,"FPS_Disp [ %d ]",FPS_Disp);			//FPS_Dispを文字列に置き換える
	TextOut(hMemDC,10,10,str,lstrlen(str));				//仮想画面にstr表示
	
	
	ReleaseDC(hwnd,hdc);	//HDC解放
}




