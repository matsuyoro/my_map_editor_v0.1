#if !defined __DEFINE	//もし、マクロがまだ定義されてなければ
#define __DEFINE		//マクロを定義
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#define WIN_CLASSNAME "Window Sample"	//クラス名  ※ﾃｷｽﾄP144(9,20行目で指定）
#define WIN_W 640						//ウィンドウの幅
#define WIN_H 480						//ウィンドウの高さ
#define CWIN_W 400						//子ウィンドウの幅
#define CWIN_H 360						//子ウィンドウの高さ
#define MWIN_W 320						//ミニマップ子ウィンドウの幅、高さ
#define MWIN_H 320						
#define WIN_TITLE "親ウィンドウがアクティブでスペースを押すとエネミー出現位置設定モード（F11で１つ前に戻る）"		//ウィンドウのタイトル

//マップ
#define BMPTIP_W 20		//ﾏｯﾌﾟﾁｯﾌﾟの画像元の横に並んだチップの数
#define BMPTIP_H 15		//ﾏｯﾌﾟﾁｯﾌﾟの画像元の縦に並んだチップの数	
#define TIP_MAX (20*15)		//チップの種類の数

#define TIP_W 32		//チップの幅
#define TIP_H 32		//チップの高さ
#define MAP_XNUM 640	//マップのヨコ枚数
#define MAP_YNUM 40		//マップのタテ枚数
#define WINMAP_W 20		//ウィンドウ内に表示するチップのヨコの数
#define WINMAP_H 14		//ウィンドウ内に表示するチップのタテの数

//エネミー出現ポイント
#define ENEONPOS_MAX 80	//エネミーを出現させるポイントの最大数
#define ENETYPE_MAX 18	//エネミーの種類の最大数

#define MY_DELETEDC(x) if(x != NULL) {DeleteDC(x); x = NULL;}	//HDCの解放とNULLを代入するマクロ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif