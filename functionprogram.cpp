#include "functionprogram.h"

int moji_retu_count = 0;	// 描画に必要な列数
int moji_gyou_count = 0;	// 描画に必要な行数
// フラグを切り替える
void FlagChange(BOOL *pf)
{
	if (*pf == FALSE){ *pf = TRUE; }
	else{ *pf = FALSE; }
}
// ゲージを描画する（色も変更可能な関数にしていきたい）
void DrawGauge(DrawGaugeEnd x, int y, int z, int a, int b, int c, int d, int e)	// ゲージが増える始点、又は減り終わる終点,対応する数値の最大値,対応する数値の現在値,左上座標x,左上座標y,右下座標x,右下座標y,色のRGB数値
{
	switch (x)
	{
	case GAUGE_END_LEFT:
		DrawBox(a, b, ((c - a) * z / y) + a + 1, d + 1, e, TRUE);
		break;
	case GAUGE_END_RIGHT:
		DrawBox(a + ((c - a) - (c - a) * z / y), b, c + 1, d + 1, e, TRUE);
		break;
	default:
		break;
	}
}
// メッセージウィンドウを表示する
void DrawMessageWindow(int a, int b, int c, int d)	// 左上x座標,左上y座標,右上x座標,右上y座標
{
	DrawBox(a - 5, b - 5, c + 5, d + 5, GetColor(255, 255, 255), TRUE);	// 外側の白枠
	DrawBox(a, b, c, d, GetColor(0, 0, 255), TRUE);	// 内側の青枠
}
// メッセージウィンドウを色、枠の太さも指定して表示する
void DrawMessageWindow2(int a, int b, int c, int d, int x, int co1, int co2)	// 左上x座標,左上y座標,右上x座標,右上y座標,枠の太さ,内側の色,外側の色
{
	DrawBox(a, b, c, d, co2, TRUE);	// 外側の枠
	DrawBox(a + x, b + x, c - x, d - x, co1, TRUE);	// 内側の枠
}
// String関数をつかって数字を描画する
void DrawStringNumber(int x, int y, int number, int absolute_figure, int color, int font)	// x座標、y座標、数字、０を描画する絶対的な桁数,色,フォント
{
	int figure = 1;					// 数字の桁数
	int figure_checker = number;	// 数字の桁数を調べるために数を読み込む
	// 桁数を調べる
	for (int z = 0; z < 1;)
	{
		figure_checker /= 10;
		if (figure_checker == 0){ z++; }	// 10未満だった場合、桁数を確定しループから出る
		else{ figure++; }					// 桁数を上げ、繰り返す
	}

	if (figure > absolute_figure){ absolute_figure = figure; }	// 桁数が大きい方を扱う
	// 数字を描画する
	for (int z = 0; z < absolute_figure; z++)
	{
		int a = 1;
		int b = 0;
		if (figure >= absolute_figure - z)
		{
			// 最も桁が大きい数字から描画するようにする
			for (int c = 1; c < absolute_figure - z; c++){ a *= 10; }
			// 描画する数字を求める
			b = number / a % 10;
		}
		// 数字を描画する
		if (figure == 1)	// １桁の場合、全角数字にする
		{
			switch (b)
			{
			case 0:	DrawStringToHandle(x + z * 8, y, "０", color, font);	break;
			case 1:	DrawStringToHandle(x + z * 8, y, "１", color, font);	break;
			case 2:	DrawStringToHandle(x + z * 8, y, "２", color, font);	break;
			case 3:	DrawStringToHandle(x + z * 8, y, "３", color, font);	break;
			case 4:	DrawStringToHandle(x + z * 8, y, "４", color, font);	break;
			case 5:	DrawStringToHandle(x + z * 8, y, "５", color, font);	break;
			case 6:	DrawStringToHandle(x + z * 8, y, "６", color, font);	break;
			case 7:	DrawStringToHandle(x + z * 8, y, "７", color, font);	break;
			case 8:	DrawStringToHandle(x + z * 8, y, "８", color, font);	break;
			case 9:	DrawStringToHandle(x + z * 8, y, "９", color, font);	break;
			default:														break;
			}
		}
		else
		{
			switch (b)
			{
			case 0:	DrawStringToHandle(x + z * 10, y, "0", color, font);	break;
			case 1:	DrawStringToHandle(x + z * 10, y, "1", color, font);	break;
			case 2:	DrawStringToHandle(x + z * 10, y, "2", color, font);	break;
			case 3:	DrawStringToHandle(x + z * 10, y, "3", color, font);	break;
			case 4:	DrawStringToHandle(x + z * 10, y, "4", color, font);	break;
			case 5:	DrawStringToHandle(x + z * 10, y, "5", color, font);	break;
			case 6:	DrawStringToHandle(x + z * 10, y, "6", color, font);	break;
			case 7:	DrawStringToHandle(x + z * 10, y, "7", color, font);	break;
			case 8:	DrawStringToHandle(x + z * 10, y, "8", color, font);	break;
			case 9:	DrawStringToHandle(x + z * 10, y, "9", color, font);	break;
			default:														break;
			}
		}
	}
}
// 文字を１文字ずつ描画する前に行う処理
void NextDrawCharString()
{
	// 描画位置の初期位置セット
	DrawPointX = 0;
	DrawPointY = 0;
	// 参照文字位置をセット
	SP = 0;	// １行目の
	CP = 0;	// ０文字
	// 終了フラグを倒す
	EndFlag = 0;
}
// 文字を描画するのに何列何行必要か調べる前に行う処理
void NextNDCNumberCheck()
{
	moji_retu_count = 0;
	moji_gyou_count = 0;
}

// テキストバッファの改行処理関数
void Kaigyou2(void)
{
	// 描画行位置を一つ下げる
	CursorY++;
	// 描画列を最初に戻す
	CursorX = 0;
	// もしテキストバッファ縦幅からはみ出るならテキストバッファを縦スクロールさせる
	if (CursorY >= STRBUF_HEIGHT)
	{
		int i, j;
		for (i = 1; i < STRBUF_HEIGHT; i++)
		{
			for (j = 1; j < STRBUF_WIDTH; j++)
			{
				StringBuf[i - 1][j] = String[i][j];
			}
		}
		// 描画行位置を一つあげる
		CursorY--;
	}
}

// カーソルを動かす
int CursorMove(int a, int b, int c) // 移動前の数値、移動量、移動限界値
{
	// カーソルを動かす
	a += b;
	// カーソルが０を下回れば（上限以上になれば）『上限－１』に（０に）修正する
	if (a < 0){ a = c - 1; }
	else if (a >= c){ a = 0; }

	//if (g_gamestate == GAME_CHARACTERSELECT){ SEPlay(1); }	// キャラクターセレクト時なら効果音を鳴らす
	// 移動後の数値を返す
	return a;
}
// ２人対戦画面で、線対称に描画するもののx座標を求める
int CallDrawX(int a, int b, int c, int d, int e)	// 画面全体の大きさ,画像の横サイズ,プレイヤー,中央からのずらし値,プレイヤー関係なくずらす値
{
	if (c == 0){ d = d * (-1); }
	int x = a / 2 - b / 2 + d + e;
	return x;
}
// 文字を１文字ずつ描画する（この方法は全角文字を描画することにのみ適しているため、半角文字を入力した場合、最悪フリーズする
// 。ただし入力された半角文字数が偶数なら当てはまらない）
int DrawCharString(int x, int y, int xl, char c, char c2, char c3, int color, int ms)	// 開始Ｘ座標,開始Ｙ座標,折り返し判定Ｘ座標,文字,1バイト先の文字,2バイト先の文字,色,文字サイズ
{
	switch (c)
	{
	case '@':	// 改行文字
		// 改行処理および参照文字位置を一つ進める
		Kaigyou();
		CP++;
		break;
	case 'Ｂ':	// ボタン押し待ち文字（省略）
		break;
	case 'E':	// 終了文字
		// 終了フラグを立てるおよび参照文字位置を一つ進める
		EndFlag = 1;
		CP++;
		break;
	case 'Ｃ':	// クリア文字（省略）
		break;
	default:	// その他の文字
		// １文字分抜き出す
		OneMojiBuf[0] = c;
		OneMojiBuf[1] = c2;
		OneMojiBuf[2] = '\0';
		// １文字描画
		DrawFormatStringToHandle(DrawPointX * ms + x, DrawPointY * ms + y, color, g_font1, OneMojiBuf);
		// 参照文字位置を２バイト進める
		CP += 2;
		// カーソルを一文字分進める
		DrawPointX++;
		// 画面からはみ出たら（次の文字描画座標がはみでるなら？）改行する
		if (DrawPointX * ms + ms + x > xl){ Kaigyou(); }
		break;
	}
	// 終了フラグが１だったら終了する
	//if (EndFlag == 1)return 1;
	if (EndFlag == 1 || CP > 255)return 1;
	// 参照文字列の終端まで行っていたら参照文字列を進める
	if ((c == '@' || c == 'E') ? c2 == '\0' : c3 == '\0')
	{
		SP++;
		CP = 0;
	}
	return 0;
}
int Kaigyou(void)
{
	//int TempGraph;
	// 描画行位置を一つ下げる
	DrawPointY++;
	// 描画列を最初に戻す
	DrawPointX = 0;
	// もし画面からはみ出るなら画面をスクロールさせる
	//（必要ないと判断したため省略）

	// 終了
	return 0;
}
// 文字を１文字ずつ描画するのに何列何行必要か調べる
int DCSNumberCheck(int x, int y, int xl, char c, char c2, char c3, int ms, int *retu, int *gyou)	// 開始Ｘ座標,開始Ｙ座標（使わない）,折り返し判定Ｘ座標,文字,1バイト先の文字,2バイト先の文字,文字サイズ,列数,行数
{
	switch (c)
	{
	case '@':	// 改行文字
		// 改行処理および参照文字位置を一つ進める
		Kaigyou();
		CP++;
		break;
	case 'Ｂ':	// ボタン押し待ち文字（省略）
		break;
	case 'E':	// 終了文字
		// 終了フラグを立てるおよび参照文字位置を一つ進める
		EndFlag = 1;
		CP++;
		break;
	case 'Ｃ':	// クリア文字（省略）
		break;
	default:	// その他の文字
		// １文字分抜き出す
		OneMojiBuf[0] = c;
		OneMojiBuf[1] = c2;
		OneMojiBuf[2] = '\0';
		// 参照文字位置を２バイト進める
		CP += 2;
		// カーソルを一文字分進める
		DrawPointX++;
		// 画面からはみ出たら（次の文字描画座標がはみでるなら？）改行する
		if (DrawPointX * ms + ms + x > xl)
		{
			*retu = DrawPointX;
			Kaigyou();
		}
		break;
	}
	// 終了フラグが１だったら終了する
	if (EndFlag == 1 || CP > 255)
	{
		if (DrawPointX > *retu){ *retu = DrawPointX; }
		*gyou = DrawPointY;
		return 1;
	}
	// 参照文字列の終端まで行っていたら参照文字列を進める
	if ((c == '@' || c == 'E') ? c2 == '\0' : c3 == '\0')
	{
		SP++;
		CP = 0;
	}
	return 0;
}
