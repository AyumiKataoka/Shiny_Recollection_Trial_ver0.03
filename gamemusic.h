#ifndef __GAMEMUSIC_H__
#define __GAMEMUSIC_H__

#include <DxLib.h>
#include "main.h"

#define BGM_VOLUME_ONLY_MAX 240	// �e�a�f�l���̉��ʂɊւ��ϐ��̍ő�l
// �a�f�l�̌ŗL���ʕϐ��ɑ΂���P�t���[�����̉��Z�l
#define BGM_VOLUME_FLAME_FADE_IN 1
#define BGM_VOLUME_FLAME_FADE_OUT -4
#define BGM_VOLUME_FLAME_FADE_STOP -24
// ���y�Ɋ֌W����֐��Ŏ�Ɏg����^���O���[�o���ϐ��A�萔
class GlobalStaticMusic
{
	static BOOL now_loading;		// ���݃��[�h����
	static const int BGM_NUMBER_;	// �O���[�o���萔�́wBGM_NUMBER�x�Ɣ���ăG���[���������邽�߃A���_�[���C����t���Ă���
public:
	static void SetNowLoading(BOOL x) { now_loading = x; }
	static BOOL GetNowLoading() { return now_loading; }
	static int GetBGMNumber() { return BGM_NUMBER_; }
};

extern int bgm_volume;	// �a�f�l�̉���
extern int se_volume;	// �r�d�̉���

void GameMusic();		// ���y�֌W�̃��C������
void MusicPlay(int x);	// �a�f�l���Đ�����
void SEPlay(int x);		// �r�d�Đ��A��~����
void ChangeBGMVolume();	// �S�a�f�l�̉��ʂ𒲐߂���
void ChangeSEVolume();	// �S�r�d�̉��ʂ𒲐߂���

#endif
