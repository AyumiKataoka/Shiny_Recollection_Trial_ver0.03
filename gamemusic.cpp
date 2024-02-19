#include "gamemusic.h"

BOOL GlobalStaticMusic::now_loading = FALSE;	// 現在ロード中か
const int GlobalStaticMusic::BGM_NUMBER_ = BGM_NUMBER;

int bgm_volume = 50;	// ＢＧＭの音量
int se_volume = 50;		// ＳＥの音量
// 音楽関係のメイン処理
void GameMusic()
{
	// 状態に応じてＢＧＭ音量に関わる変数を増減させる
	for (int i = 0; i < BGM_NUMBER; i++)
	{
		switch (g_bgmstate[i].state)
		{
		case BGM_FADE_IN:	g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_IN;		break;
		case BGM_FADE_OUT:	g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_OUT;		break;
		case BGM_STOP:		g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_STOP;	break;
		default:																break;
		} 
		// 0or最大値からはみ出た場合は修正し状態を変える
		if (g_bgmstate[i].vol <= 0)
		{
			g_bgmstate[i].vol = 0;
			g_bgmstate[i].state = BGM_STANDBY;
			#pragma region ver0.017制作時コメント化コード
			//StopSoundMem(g_sndhandles.BGM[i]);
#pragma endregion
			StopSoundMem(bgm[i].GetHandle());
		}
		else if (g_bgmstate[i].vol >= BGM_VOLUME_ONLY_MAX)
		{
			g_bgmstate[i].vol = BGM_VOLUME_ONLY_MAX;
			g_bgmstate[i].state = BGM_PLAY;
		}
	}

	ChangeBGMVolume();	// 変数に応じて音量を変化させる
}
// ＢＧＭを再生する
void MusicPlay(int x)
{
	// 現在流れている全てのＢＧＭを停止する状態に向かわせる
	for (int i = 0; i < BGM_NUMBER; i++)
	{ 
		//StopSoundMem(g_sndhandles.BGM[i]); 
		if (g_bgmstate[i].vol > 0)
		{
			if (HM[commu_number][cell_number].bgm_change == BGM_CHANGE_FO_P || HM[commu_number][cell_number].bgm_change == BGM_CHANGE_FO_FI || g_gamestate != GAME_MAIN_COMMUNICATION){ g_bgmstate[i].state = BGM_FADE_OUT; }
			else{ g_bgmstate[i].state = BGM_STOP; }
		}
		// コミュをロードした際ロード行ＢＧＭより以前に鳴らされていたＢＧＭが一瞬なってしまう不具合の修正
		if (GlobalStaticMusic::GetNowLoading() == TRUE)
		{ 
			g_bgmstate[i].vol = 0;
			g_bgmstate[i].state = BGM_STANDBY;
			#pragma region ver0.017制作時コメント化コード
			//StopSoundMem(g_sndhandles.BGM[i]);
#pragma endregion
			StopSoundMem(bgm[i].GetHandle());
		}
	}	

	#pragma region ver0.0072制作時コメント化コード
	//if (x >= 0)
#pragma endregion
	if (x >= 0 && x < GlobalStaticMusic::GetBGMNumber())
	{
		// 停止する曲と再生する曲が同じ場合、一度曲を即停止させる
		#pragma region ver0.017制作時コメント化コード
		//if (g_bgmstate[x].vol > 0)
		//{
		//	StopSoundMem(g_sndhandles.BGM[x]);
		//	g_bgmstate[x].vol = 0;
		//}
		//PlaySoundMem(g_sndhandles.BGM[x], DX_PLAYTYPE_LOOP);
		// （将伍案）コンフィグを終了してもＢＧＭが再び再生されないようにする
		//if (g_bgmstate[x].vol == 0)
		//{
		//	PlaySoundMem(g_sndhandles.BGM[x], DX_PLAYTYPE_LOOP);
		//}
#pragma endregion
		if (g_bgmstate[x].vol > 0)
		{
			StopSoundMem(bgm[x].GetHandle());
			g_bgmstate[x].vol = 0;
		}
		PlaySoundMem(bgm[x].GetHandle(), DX_PLAYTYPE_LOOP);


		if (HM[commu_number][cell_number].bgm_change == BGM_CHANGE_FO_P || HM[commu_number][cell_number].bgm_change == BGM_CHANGE_S_P || g_gamestate != GAME_MAIN_COMMUNICATION)
		{
			g_bgmstate[x].state = BGM_PLAY;
			g_bgmstate[x].vol = BGM_VOLUME_ONLY_MAX;
		}
		else{ g_bgmstate[x].state = BGM_FADE_IN; }
	}
}
// ＳＥ再生、停止処理
void SEPlay(int x)
{
	switch (x)
	{
	#pragma region ver0.00607制作時コメント化コード
	//case -2:			for (int i = 0; i < SE_NUMBER; i++){ StopSoundMem(g_sndhandles.SE[i]); };	break;	// 全（ループ）ＳＥ停止
	//	// ループ再生
	//case SN_BASKETBALL_DRIBBLE:
	//case SN_FOOT_STEP_LOOP:
	//case SN_KEYBOARD_TYPING:
	//case SN_PHONE_CALL:
	//	PlaySoundMem(g_sndhandles.SE[x], DX_PLAYTYPE_LOOP);
	//	break;

	//default:			PlaySoundMem(g_sndhandles.SE[x], DX_PLAYTYPE_BACK);							break;
#pragma endregion
	#pragma region ver0.00707制作時コメント化コード
	//case -2:			for (int i = 0; i < SE_NUMBER; i++) { StopSoundMem(se[i].GetHandle()); };	break;	// 全（ループ）ＳＥ停止
#pragma endregion
	case -2:			for (int i = 0; i < SEData::GetNumber(); i++) { StopSoundMem(se[i].GetHandle()); };	break;	// 全（ループ）ＳＥ停止
	default:			se[x].Play();																break;
	}
}
// 全ＢＧＭの音量を調節する
void ChangeBGMVolume()
{
	int x = 255 * bgm_volume / 100;	// 音量変更関数に使う数値に変換する

	//ChangeVolumeSoundMem(x, g_sndhandles.main_theme);	// タイトルＢＧＭ
	//ChangeVolumeSoundMem(x, g_sndhandles.BGM[BN_TITLE]);	// タイトルＢＧＭ
	for (int i = 0; i < BGM_NUMBER; i++)
	{ 
		//ChangeVolumeSoundMem(x, g_sndhandles.BGM[i]); 
		ChangeVolumeSoundMem(x * g_bgmstate[i].vol / BGM_VOLUME_ONLY_MAX, bgm[i].GetHandle());
	}
}
// 全ＳＥの音量を調節する
void ChangeSEVolume()
{
	int x = 255 * se_volume / 100;	// 音量変更関数に使う数値に変換する
	#pragma region ver0.00607制作時コメント化コード
	//for (int i = 0; i < SE_NUMBER; i++){ ChangeVolumeSoundMem(x, g_sndhandles.SE[i]); }
#pragma endregion
	for (int i = 0; i < SEData::GetNumber(); i++) { ChangeVolumeSoundMem(x, se[i].GetHandle()); }
}
