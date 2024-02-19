#ifndef __SOUNDROOM_H__
#define __SOUNDROOM_H__

#include <DxLib.h>
#include "main.h"

#define SR_BGM_ALTERNATIVE_NUMBER 34 + 1	// �T�E���h���[�����ł̂a�f�l�I�������i�wBGM_NUMBER + 1�x�j

// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfsr=click_flag_sound_room�j
extern BOOL cfsr_play_music[];	// �a�f�l���Đ�����i�o�O���N���Ȃ����v�m�F�j
extern BOOL cfsr_play_se[];		// �a�f�l���Đ�����i�o�O���N���Ȃ����v�m�F�j
extern BOOL cfsr_move_title;	// �^�C�g����ʂֈړ�
extern BOOL cfsr_bgm_down;		// �a�f�l���ʂ�������
extern BOOL cfsr_bgm_up;		// �a�f�l���ʂ��グ��
extern BOOL cfsr_se_down;		// �r�d���ʂ�������
extern BOOL cfsr_se_up;			// �r�d���ʂ��グ��

extern float sound_room_coordinate_alternative_x[];		// BGM�I������{x���W
extern float sound_room_coordinate_alternative_y[];		// BGM�I������{y���W�i�o�O���N���Ȃ����v�m�F�j
extern float sound_room_coordinate_alternative_se_x[];	// �r�d�I������{x���W
extern float sound_room_coordinate_alternative_se_y[];	// �r�d�I������{y���W�i�o�O���N���Ȃ����v�m�F�j
extern float sound_room_size_alternative_x;				// BGM�I������{x��
extern float sound_room_size_alternative_y;				// BGM�I������{y��
extern float sound_room_coordinate_string_title_x;		// �wTITLE�xx���W
extern float sound_room_coordinate_string_title_y;		// �wTITLE�xy���W
extern float sound_room_coordinate_bgm_message_y;		// BGM���ʊ֌WY���W
extern float sound_room_coordinate_bgm_volume_up_x;		// BGM�w���x����X���W
extern float sound_room_coordinate_bgm_volume_up_y;		// BGM�w���x����Y���W
extern float sound_room_coordinate_se_message_y;		// SE���ʊ֌WY���W
extern float sound_room_coordinate_se_volume_up_x;		// SE�w���x����X���W
extern float sound_room_coordinate_se_volume_up_y;		// SE�w���x����Y���W

void SoundRoom();					// SoundRoom��Ԃ̃��C������
void SoundRoomControl();			// �T�E���h���[����ʑ��쏈��
void SoundRoomCoordinateSetting();	// �T�E���h���[����ʂŎg���l�X�ȍ��W���i�āj��`����
void DrawSoundRoom();				// �T�E���h���[���̕`�揈��

#endif
