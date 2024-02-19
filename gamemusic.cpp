#include "gamemusic.h"

BOOL GlobalStaticMusic::now_loading = FALSE;	// ���݃��[�h����
const int GlobalStaticMusic::BGM_NUMBER_ = BGM_NUMBER;

int bgm_volume = 50;	// �a�f�l�̉���
int se_volume = 50;		// �r�d�̉���
// ���y�֌W�̃��C������
void GameMusic()
{
	// ��Ԃɉ����Ăa�f�l���ʂɊւ��ϐ��𑝌�������
	for (int i = 0; i < BGM_NUMBER; i++)
	{
		switch (g_bgmstate[i].state)
		{
		case BGM_FADE_IN:	g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_IN;		break;
		case BGM_FADE_OUT:	g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_OUT;		break;
		case BGM_STOP:		g_bgmstate[i].vol += BGM_VOLUME_FLAME_FADE_STOP;	break;
		default:																break;
		} 
		// 0or�ő�l����͂ݏo���ꍇ�͏C������Ԃ�ς���
		if (g_bgmstate[i].vol <= 0)
		{
			g_bgmstate[i].vol = 0;
			g_bgmstate[i].state = BGM_STANDBY;
			#pragma region ver0.017���쎞�R�����g���R�[�h
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

	ChangeBGMVolume();	// �ϐ��ɉ����ĉ��ʂ�ω�������
}
// �a�f�l���Đ�����
void MusicPlay(int x)
{
	// ���ݗ���Ă���S�Ă̂a�f�l���~�����ԂɌ����킹��
	for (int i = 0; i < BGM_NUMBER; i++)
	{ 
		//StopSoundMem(g_sndhandles.BGM[i]); 
		if (g_bgmstate[i].vol > 0)
		{
			if (HM[commu_number][cell_number].bgm_change == BGM_CHANGE_FO_P || HM[commu_number][cell_number].bgm_change == BGM_CHANGE_FO_FI || g_gamestate != GAME_MAIN_COMMUNICATION){ g_bgmstate[i].state = BGM_FADE_OUT; }
			else{ g_bgmstate[i].state = BGM_STOP; }
		}
		// �R�~�������[�h�����ۃ��[�h�s�a�f�l���ȑO�ɖ炳��Ă����a�f�l����u�Ȃ��Ă��܂��s��̏C��
		if (GlobalStaticMusic::GetNowLoading() == TRUE)
		{ 
			g_bgmstate[i].vol = 0;
			g_bgmstate[i].state = BGM_STANDBY;
			#pragma region ver0.017���쎞�R�����g���R�[�h
			//StopSoundMem(g_sndhandles.BGM[i]);
#pragma endregion
			StopSoundMem(bgm[i].GetHandle());
		}
	}	

	#pragma region ver0.0072���쎞�R�����g���R�[�h
	//if (x >= 0)
#pragma endregion
	if (x >= 0 && x < GlobalStaticMusic::GetBGMNumber())
	{
		// ��~����ȂƍĐ�����Ȃ������ꍇ�A��x�Ȃ𑦒�~������
		#pragma region ver0.017���쎞�R�����g���R�[�h
		//if (g_bgmstate[x].vol > 0)
		//{
		//	StopSoundMem(g_sndhandles.BGM[x]);
		//	g_bgmstate[x].vol = 0;
		//}
		//PlaySoundMem(g_sndhandles.BGM[x], DX_PLAYTYPE_LOOP);
		// �i���ވāj�R���t�B�O���I�����Ă��a�f�l���ĂэĐ�����Ȃ��悤�ɂ���
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
// �r�d�Đ��A��~����
void SEPlay(int x)
{
	switch (x)
	{
	#pragma region ver0.00607���쎞�R�����g���R�[�h
	//case -2:			for (int i = 0; i < SE_NUMBER; i++){ StopSoundMem(g_sndhandles.SE[i]); };	break;	// �S�i���[�v�j�r�d��~
	//	// ���[�v�Đ�
	//case SN_BASKETBALL_DRIBBLE:
	//case SN_FOOT_STEP_LOOP:
	//case SN_KEYBOARD_TYPING:
	//case SN_PHONE_CALL:
	//	PlaySoundMem(g_sndhandles.SE[x], DX_PLAYTYPE_LOOP);
	//	break;

	//default:			PlaySoundMem(g_sndhandles.SE[x], DX_PLAYTYPE_BACK);							break;
#pragma endregion
	#pragma region ver0.00707���쎞�R�����g���R�[�h
	//case -2:			for (int i = 0; i < SE_NUMBER; i++) { StopSoundMem(se[i].GetHandle()); };	break;	// �S�i���[�v�j�r�d��~
#pragma endregion
	case -2:			for (int i = 0; i < SEData::GetNumber(); i++) { StopSoundMem(se[i].GetHandle()); };	break;	// �S�i���[�v�j�r�d��~
	default:			se[x].Play();																break;
	}
}
// �S�a�f�l�̉��ʂ𒲐߂���
void ChangeBGMVolume()
{
	int x = 255 * bgm_volume / 100;	// ���ʕύX�֐��Ɏg�����l�ɕϊ�����

	//ChangeVolumeSoundMem(x, g_sndhandles.main_theme);	// �^�C�g���a�f�l
	//ChangeVolumeSoundMem(x, g_sndhandles.BGM[BN_TITLE]);	// �^�C�g���a�f�l
	for (int i = 0; i < BGM_NUMBER; i++)
	{ 
		//ChangeVolumeSoundMem(x, g_sndhandles.BGM[i]); 
		ChangeVolumeSoundMem(x * g_bgmstate[i].vol / BGM_VOLUME_ONLY_MAX, bgm[i].GetHandle());
	}
}
// �S�r�d�̉��ʂ𒲐߂���
void ChangeSEVolume()
{
	int x = 255 * se_volume / 100;	// ���ʕύX�֐��Ɏg�����l�ɕϊ�����
	#pragma region ver0.00607���쎞�R�����g���R�[�h
	//for (int i = 0; i < SE_NUMBER; i++){ ChangeVolumeSoundMem(x, g_sndhandles.SE[i]); }
#pragma endregion
	for (int i = 0; i < SEData::GetNumber(); i++) { ChangeVolumeSoundMem(x, se[i].GetHandle()); }
}
