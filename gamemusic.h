#ifndef __GAMEMUSIC_H__
#define __GAMEMUSIC_H__

#include <DxLib.h>
#include "main.h"

#define BGM_VOLUME_ONLY_MAX 240	// 各ＢＧＭ毎の音量に関わる変数の最大値
// ＢＧＭの固有音量変数に対する１フレーム毎の加算値
#define BGM_VOLUME_FLAME_FADE_IN 1
#define BGM_VOLUME_FLAME_FADE_OUT -4
#define BGM_VOLUME_FLAME_FADE_STOP -24
// 音楽に関係する関数で主に使われる疑似グローバル変数、定数
class GlobalStaticMusic
{
	static BOOL now_loading;		// 現在ロード中か
	static const int BGM_NUMBER_;	// グローバル定数の『BGM_NUMBER』と被ってエラーが発生するためアンダーラインを付けている
public:
	static void SetNowLoading(BOOL x) { now_loading = x; }
	static BOOL GetNowLoading() { return now_loading; }
	static int GetBGMNumber() { return BGM_NUMBER_; }
};

extern int bgm_volume;	// ＢＧＭの音量
extern int se_volume;	// ＳＥの音量

void GameMusic();		// 音楽関係のメイン処理
void MusicPlay(int x);	// ＢＧＭを再生する
void SEPlay(int x);		// ＳＥ再生、停止処理
void ChangeBGMVolume();	// 全ＢＧＭの音量を調節する
void ChangeSEVolume();	// 全ＳＥの音量を調節する

#endif
