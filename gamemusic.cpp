#include "gamemusic.h"

BOOL GlobalStaticMusic::now_loading = FALSE;	// Œ»İƒ[ƒh’†‚©
const int GlobalStaticMusic::BGM_NUMBER_ = BGM_NUMBER;

int bgm_volume = 50;	// ‚a‚f‚l‚Ì‰¹—Ê
int se_volume = 50;		// ‚r‚d‚Ì‰¹—Ê
// ‰¹ŠyŠÖŒW‚ÌƒƒCƒ“ˆ—
void GameMusic()
{
	// ó‘Ô‚É‰‚¶‚Ä‚a‚f‚l‰¹—Ê‚ÉŠÖ‚í‚é•Ï”‚ğ‘Œ¸‚³‚¹‚é
	for (int i = 0; i < BGM_NUMBER; i++)
	{
		switch (g_bgmstate[i].state)
		{
		case BGM_FADE_IN:	g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_IN;		break;
		case BGM_FADE_OUT:	g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_OUT;		break;
		case BGM_STOP:		g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_STOP;	break;
		default:																break;
		} 
		// 0orÅ‘å’l‚©‚ç‚Í‚İo‚½ê‡‚ÍC³‚µó‘Ô‚ğ•Ï‚¦‚é
		if (g_bgmstate[i].vol <= 0)
		{
			g_bgmstate[i].vol = 0;
			g_bgmstate[i].state = BGM_STANDBY;
			StopSoundMem(bgm[i].GetHandle());
		}
		else if (g_bgmstate[i].vol >= BGM_VOLUME_ONLY_MAX)
		{
			g_bgmstate[i].vol = BGM_VOLUME_ONLY_MAX;
			g_bgmstate[i].state = BGM_PLAY;
		}
	}

	ChangeBGMVolume();	// •Ï”‚É‰‚¶‚Ä‰¹—Ê‚ğ•Ï‰»‚³‚¹‚é
}
// ‚a‚f‚l‚ğÄ¶‚·‚é
void MusicPlay(int x)
{
	// Œ»İ—¬‚ê‚Ä‚¢‚é‘S‚Ä‚Ì‚a‚f‚l‚ğ’â~‚·‚éó‘Ô‚ÉŒü‚©‚í‚¹‚é
	for (int i = 0; i < BGM_NUMBER; i++)
	{ 
		//StopSoundMem(g_sndhandles.BGM[i]); 
		if (g_bgmstate[i].vol > 0)
		{
			if (HM[commu_number][cell_number].bgm_change == BGM_CHANGE_FO_P || HM[commu_number][cell_number].bgm_change == BGM_CHANGE_FO_FI || g_gamestate != GAME_MAIN_COMMUNICATION){ g_bgmstate[i].state = BGM_FADE_OUT; }
			else{ g_bgmstate[i].state = BGM_STOP; }
		}
		// ƒRƒ~ƒ…‚ğƒ[ƒh‚µ‚½Ûƒ[ƒhs‚a‚f‚l‚æ‚èˆÈ‘O‚É–Â‚ç‚³‚ê‚Ä‚¢‚½‚a‚f‚l‚ªˆêu‚È‚Á‚Ä‚µ‚Ü‚¤•s‹ï‡‚ÌC³
		if (GlobalStaticMusic::GetNowLoading() == TRUE)
		{ 
			g_bgmstate[i].vol = 0;
			g_bgmstate[i].state = BGM_STANDBY;
			StopSoundMem(bgm[i].GetHandle());
		}
	}	

	if (x >= 0 && x < GlobalStaticMusic::GetBGMNumber())
	{
		// ’â~‚·‚é‹È‚ÆÄ¶‚·‚é‹È‚ª“¯‚¶ê‡Aˆê“x‹È‚ğ‘¦’â~‚³‚¹‚é
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
// ‚r‚dÄ¶A’â~ˆ—
void SEPlay(int x)
{
	switch (x)
	{
	case -2:			for (int i = 0; i < SEData::GetNumber(); i++) { StopSoundMem(se[i].GetHandle()); };	break;	// ‘Siƒ‹[ƒvj‚r‚d’â~
	default:			se[x].Play();																break;
	}
}
// ‘S‚a‚f‚l‚Ì‰¹—Ê‚ğ’²ß‚·‚é
void ChangeBGMVolume()
{
	int x = 255 * bgm_volume / 100;	// ‰¹—Ê•ÏXŠÖ”‚Ég‚¤”’l‚É•ÏŠ·‚·‚é

	//ChangeVolumeSoundMem(x, g_sndhandles.main_theme);	// ƒ^ƒCƒgƒ‹‚a‚f‚l
	//ChangeVolumeSoundMem(x, g_sndhandles.BGM[BN_TITLE]);	// ƒ^ƒCƒgƒ‹‚a‚f‚l
	for (int i = 0; i < BGM_NUMBER; i++)
	{ 
		//ChangeVolumeSoundMem(x, g_sndhandles.BGM[i]); 
		ChangeVolumeSoundMem(x * g_bgmstate[i].vol / BGM_VOLUME_ONLY_MAX, bgm[i].GetHandle());
	}
}
// ‘S‚r‚d‚Ì‰¹—Ê‚ğ’²ß‚·‚é
void ChangeSEVolume()
{
	int x = 255 * se_volume / 100;	// ‰¹—Ê•ÏXŠÖ”‚Ég‚¤”’l‚É•ÏŠ·‚·‚é
	for (int i = 0; i < SEData::GetNumber(); i++) { ChangeVolumeSoundMem(x, se[i].GetHandle()); }
}
