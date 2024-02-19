#ifndef __FUNCTIONPROGRAM_H__
#define __FUNCTIONPROGRAM_H__

#include <DxLib.h>
#include "main.h"
//　ゲージの始点
enum DrawGaugeEnd
{
	GAUGE_END_LEFT,		// 左が始点
	GAUGE_END_RIGHT		// 右が始点
};

extern int moji_retu_count;	// 描画に必要な列数
extern int moji_gyou_count;	// 描画に必要な行数
// よく使われる関数
void FlagChange(BOOL *pf);																		// フラグを切り替える
void DrawGauge(DrawGaugeEnd x, int y, int z, int a, int b, int c, int d, int e);				// ゲージを描画する
void DrawMessageWindow(int a, int b, int c, int d);												// メッセージウィンドウを表示する
void DrawMessageWindow2(int a, int b, int c, int d, int x, int co1, int co2);					// メッセージウィンドウを色、枠の太さも指定して表示する
void DrawStringNumber(int x, int y, int number, int absolute_figure, int color, int font);		// String関数をつかって数字を描画する
void NextDrawCharString();																		// 文字を１文字ずつ描画する前に行う処理
void NextNDCNumberCheck();																			// 文字を描画するのに何列何行必要か調べる前に行う処理

void Kaigyou2();	// テキストバッファの改行処理関数

int CursorMove(int a, int b, int c);															// カーソルを動かす
int CallDrawX(int a, int b, int c, int d, int e);												// ２人対戦画面で、線対称に描画するもののx座標を求める
int DrawCharString(int x, int y, int xl, char c, char c2, char c3, int color, int ms);			// 文字を１文字ずつ描画する								
int Kaigyou(void);
int DCSNumberCheck(int x, int y, int xl, char c, char c2, char c3, int ms, int *retu, int *gyou);	// 文字を描画するのに何列何行必要か調べ、代入する

#endif
