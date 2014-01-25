#if !defined __GLOBALMACRO
#define __GLOBALMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include <windows.h>	//Windows用ヘッダファイル
#include "define.h"		//マクロ定義をまとめたヘッダファイル
#include "GameStruct.h"	//構造体の型の定義ヘッダ

//ここに、ゲームで使う外部変数を宣言（絵のHDCや、キャラ、マップ等のデータを扱う変数）
HWND hwnd;	//ウィンドウハンドル

HINSTANCE hInst;		//インスタンスハンドルをコピーしておく外部変数
HWND hCwnd;				//子ウィンドウのハンドル
HWND hMwnd;				//ミニマップウィンドウのハンドル
JOYINFOEX JoyData;		//JOYINFOEX型構造体（現在のジョイスティックのデータ）
JOYINFOEX JoyData2;		//（前回のジョイスティックのデータ）
HMENU hMenu;			//メニューのハンドルを扱う
SCROLLINFO HScr;		//水平スクロールバー用
SCROLLINFO VScr;		//垂直スクロールバー用

HDC hMemDC;		//仮想画面のHDC
HDC hMinMemDC;	//ミニマップ用仮想画面のHDC
HDC hTipDC;		//マップチップのHDC

int TipNum;											//チップの種類を扱う
int ToolNum;										//選択中の機能を扱う
int mx,my;											//マウス座標
int MapMx,MapMy;										//マップ単位でのマウスの座標を扱う
int MapMx2,MapMy2;										//ドラッグした時のボタンを押しさげた時のマウスの座標を扱う
int MapScrX=0,MapScrY=0;							//マップをスクロールしたときにx,yに追加					
int map_xnum=MAP_XNUM,map_ynum=MAP_YNUM;			//マップのタテヨコのチップ数を入れる
int Map[MAP_YNUM][MAP_XNUM];						//タテMAP_YNUM枚、ヨコMAP_XNUM枚のマップ

int MinW_ScrX = 0;	//ミニマップ子ウィンドウの横スクロール量を扱う
int MinW_ScrY = 0;	//〃縦スクロール量を扱う

//エネミー出現位置
struct ENE_ONPOS EneOnPos_Max =	{ENEONPOS_MAX,0,0,FALSE};//エネミー出現位置数(ENE_ONPOS型構造体のメンバのxを使って適出現位置数の数を扱う
struct ENE_ONPOS EneOn[ENEONPOS_MAX] =	//エネミーの出現するポイントを１００個まで設定
{
	{650,400,1,FALSE},				//エネミー１を650,400のポイントに出現させる
};
BOOL EneOnTool = FALSE;	//エネミー表示機能を扱う（TRUEで表示
int EneOnReturn[ENEONPOS_MAX];	//エネミー配置を順番を記録する配列（前回設置したエネミーを戻すしたりするのに使用
int EneRtrnCnt = 0;				//EneOnReturnの要素番号を順に扱う変数
int EneTypeNum = 1;				//エネミーの種類を扱う	

int x,y;			
BOOL Flag = FALSE;	//メモリ確保のフラグ
int *pi = NULL;		//メモリ確保する変数
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif