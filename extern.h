//外部変数を、WinMain()のあるソースファイル以外で使用するためのヘッダファイル
#if !defined __EXTERNMACRO
#define __EXTERNMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include <windows.h>	//Windows用ヘッダファイル
#include "define.h"		//マクロ定義をまとめたヘッダファイル
#include "GameStruct.h"	//構造体の型の定義ヘッダ

extern HWND hwnd;	//ウィンドウハンドル

extern HINSTANCE hInst;	//インスタンスハンドルをコピーしておく外部変数
extern HWND hCwnd;				//子ウィンドウのハンドル
extern HWND hMwnd;				//ミニマップウィンドウのハンドル
extern JOYINFOEX JoyData;		//JOYINFOEX型構造体（現在のジョイスティックのデータ）
extern JOYINFOEX JoyData2;		//（前回のジョイスティックのデータ）
extern HMENU hMenu;	//メニューのハンドルを扱う
extern SCROLLINFO HScr;			//水平スクロールバー用
extern SCROLLINFO VScr;			//垂直スクロールバー用

extern HDC hMemDC;		//仮想画面のHDC
extern HDC hMinMemDC;	//ミニマップ用仮想画面のHDC
extern HDC hTipDC;		//マップチップのHDC


extern int TipNum;					//チップの種類を扱う
extern int ToolNum;										//選択中の機能を扱う
extern int mx,my;					//マウス座標
extern int MapMx,MapMy;			//マップ単位でのマウスの座標を扱う
extern int MapMx2,MapMy2;			//ドラッグした時のボタンを押しさげた時のマウスの座標を扱う
extern int MapScrX,MapScrY;			//
extern int map_xnum,map_ynum;			//マップのタテヨコのチップ数を入れる
extern int Map[MAP_YNUM][MAP_XNUM];	//タテMAP_YNUM枚、ヨコMAP_XNUM枚

extern int MinW_ScrX;	//ミニマップ子ウィンドウの横スクロール量を扱う
extern int MinW_ScrY;	//〃縦スクロール量を扱う


//エネミー出現位置
extern struct ENE_ONPOS EneOnPos_Max;	//エネミー出現位置数
extern struct ENE_ONPOS EneOn[ENEONPOS_MAX];	//エネミーの出現するポイントを１００個まで設定
extern BOOL EneOnTool;	//エネミー表示機能を扱う（TRUEで表示
extern int EneOnReturn[ENEONPOS_MAX];	//エネミー配置を順番を記録する配列
extern int EneRtrnCnt;				//EneOnReturnの要素番号を順に扱う変数
extern int EneTypeNum;				//エネミーの種類を扱う	


extern int x,y;	
extern BOOL Flag;
extern int *pi;
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif

