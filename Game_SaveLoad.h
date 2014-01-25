//ゲーム用のセーブ、ロードをまとめたヘッダファイル
#if !defined __GAME_SAVELOADMACRO
#define __GAME_SAVELOADMACRO
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include <windows.h>	//Windows用ヘッダファイル

void GameSave(char *);	//ゲームのデータセーブの関数のプロトタイプ宣言
void GameLoad(char *);	//ゲームのデータロードの関数のプロトタイプ宣言
void EneOnPosSave(char *);	//適出現位置セーブの関数のプロトタイプ宣言
void EneOnPosLoad(char *);	//適出現位置ロードの関数のプロトタイプ宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#endif