#include "soundroom.h"

// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfsr=click_flag_sound_room�j
BOOL cfsr_play_music[SR_BGM_ALTERNATIVE_NUMBER];	// �a�f�l���Đ�����
BOOL cfsr_play_se[SE_NUMBER + 1];	// �r�d���Đ�����i�o�O���N���Ȃ����v�m�F�j
BOOL cfsr_move_title = FALSE;		// �^�C�g����ʂֈړ�
BOOL cfsr_bgm_down = FALSE;			// �a�f�l���ʂ�������
BOOL cfsr_bgm_up = FALSE;			// �a�f�l���ʂ��グ��
BOOL cfsr_se_down = FALSE;			// �r�d���ʂ�������
BOOL cfsr_se_up = FALSE;			// �r�d���ʂ��グ��

float sound_room_coordinate_alternative_x[SR_BGM_ALTERNATIVE_NUMBER];	// BGM�I������{x���W
float sound_room_coordinate_alternative_y[SR_BGM_ALTERNATIVE_NUMBER];	// BGM�I������{y���W
float sound_room_coordinate_alternative_se_x[SE_NUMBER + 1];	// �r�d�I������{x���W
float sound_room_coordinate_alternative_se_y[SE_NUMBER + 1];	// �r�d�I������{y���W�i�o�O���N���Ȃ����v�m�F�j
float sound_room_size_alternative_x = 0;						// BGM�I������{x��
float sound_room_size_alternative_y = 0;						// BGM�I������{y��
float sound_room_coordinate_string_title_x = 0;					// �wTITLE�xx���W
float sound_room_coordinate_string_title_y = 0;					// �wTITLE�xy���W
float sound_room_coordinate_bgm_message_y = 0;					// BGM���ʊ֌WY���W
float sound_room_coordinate_bgm_volume_up_x = 0;				// BGM�w���x����X���W
float sound_room_coordinate_bgm_volume_up_y = 0;				// BGM�w���x����Y���W
float sound_room_coordinate_se_message_y = 0;					// SE���ʊ֌WY���W
float sound_room_coordinate_se_volume_up_x = 0;					// SE�w���x����X���W
float sound_room_coordinate_se_volume_up_y = 0;					// SE�w���x����Y���W
// SoundRoom��Ԃ̃��C������
void SoundRoom()
{
	SoundRoomControl();
	DrawSoundRoom();
}
// �R�~����ʑ��쏈��
void SoundRoomControl()
{
	// �}�E�X�̃{�^���������ꂽ�藣���ꂽ�肵�����ǂ����̏����擾����
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
	{
		// ���{�^����������Ă�����
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_volume_up_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfsr_bgm_down = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_bgm_volume_up_x, sound_room_coordinate_bgm_volume_up_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfsr_bgm_up = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_se_volume_up_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfsr_se_down = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_se_volume_up_x, sound_room_coordinate_se_volume_up_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfsr_se_up = TRUE; }
				// �a�f�l�I����
				for (int i = 0; i < SR_BGM_ALTERNATIVE_NUMBER; i++)
				{
					if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_alternative_x[i], sound_room_coordinate_alternative_y[i], sound_room_size_alternative_x, sound_room_size_alternative_y, TRUE, FALSE) == TRUE) { cfsr_play_music[i] = TRUE; }
				}
				// �r�d�I����
				for (int i = 0; i < SEData::GetNumber() + 1; i++)
				{
					if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_alternative_se_x[i], sound_room_coordinate_alternative_se_y[i], sound_room_size_alternative_x, sound_room_size_alternative_y, TRUE, FALSE) == TRUE){ cfsr_play_se[i] = TRUE; }
				}
				// �wTITLE�x������
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_string_title_y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfsr_move_title = TRUE; }
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				// ���ʂ�������
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_volume_up_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_bgm_down) == TRUE)
				{
					bgm_volume -= 5;
					ChangeBGMVolume();
				}
				// ���ʂ��グ��
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_bgm_volume_up_x, sound_room_coordinate_bgm_volume_up_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_bgm_up) == TRUE)
				{
					bgm_volume += 5;
					ChangeBGMVolume();
				}
				// �r�d���ʂ�������
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_se_volume_up_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_se_down) == TRUE) 
				{
					se_volume -= 5;
					ChangeSEVolume();
				}
				// �r�d���ʂ��グ��
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_se_volume_up_x, sound_room_coordinate_se_volume_up_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_se_up) == TRUE) 
				{
					se_volume += 5;
					ChangeSEVolume();
				}
				// ���ʕϓ��ɂ���ĉ��i��j���l���߂����ꍇ�A�C������
				if (bgm_volume < 0) { bgm_volume = 0; }
				else if (bgm_volume > 100) { bgm_volume = 100; }
				if (se_volume < 0) { se_volume = 0; }
				else if (se_volume > 100) { se_volume = 100; }
				// �a�f�l���Đ�����i�v���g�^�C�v�j
				#pragma region ver0.0051���쎞�R�����g���R�[�h
				for (int i = 0; i < SR_BGM_ALTERNATIVE_NUMBER; i++)
				{
					if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_alternative_x[i], sound_room_coordinate_alternative_y[i], sound_room_size_alternative_x, sound_room_size_alternative_y, FALSE, cfsr_play_music[i]) == TRUE){ MusicPlay(i - 1); }
				}
				// �r�d���Đ��i�A��~�j����i�v���g�^�C�v�j
				for (int i = 0; i < SEData::GetNumber() + 1; i++)
				{
					if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_alternative_se_x[i], sound_room_coordinate_alternative_se_y[i], sound_room_size_alternative_x, sound_room_size_alternative_y, FALSE, cfsr_play_se[i]) == TRUE)
					{ 
						if(i == 0){ SEPlay(-2); }
						else{ SEPlay(i - 1); }
					}
				}
				// �^�C�g����ʂɖ߂�
				if (ClickFlagCheckF(ClickX, ClickY, sound_room_coordinate_string_title_x, sound_room_coordinate_string_title_y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfsr_move_title) == TRUE){ GameTitleNext(); }
				// �S�Ẵt���O��߂�
				for (int i = 0; i < BGM_NUMBER; i++){ cfsr_play_music[i] = FALSE; }	// �a�f�l���Đ�����
				for (int i = 0; i < SEData::GetNumber() + 1; i++){ cfsr_play_se[i] = FALSE; }	// �r�d���Đ�����
				cfsr_move_title = FALSE;											// �^�C�g����ʂֈړ�
				cfsr_bgm_down = FALSE;												// �a�f�l���ʂ�������
				cfsr_bgm_up = FALSE;												// �a�f�l���ʂ��グ��
				cfsr_se_down = FALSE;												// �r�d���ʂ�������
				cfsr_se_up = FALSE;													// �r�d���ʂ��グ��
			}
		}
	}
	/* �}�E�X�z�C�[���֌W ---------*/
}
// �T�E���h���[����ʂŎg���l�X�ȍ��W���i�āj��`����
void SoundRoomCoordinateSetting()
{
	// ��������e�X�g
	for (int i = -1; i < BGM_NUMBER; i++) { i == -1 ? music_string_stop.NameChange(i) : music_string[i].NameChange(i); }
	// BGM�֌W�I�������W
	sound_room_size_alternative_x = 330 * bairitu;																						// BGM�I������{x��
	sound_room_size_alternative_y = 35 * bairitu;																						// BGM�I������{y��
	// �a�f�l�֌W�I�������W
	for (int i = 0; i < SR_BGM_ALTERNATIVE_NUMBER; i++)
	{
		sound_room_coordinate_alternative_x[i] = sound_room_size_alternative_x * (i % 2 == 0 ? 0 : 1.0f) + 400 * bairitu;	// BGM�I������{x���W
		sound_room_coordinate_alternative_y[i] = 100 * bairitu + sound_room_size_alternative_y * (i / 2);// BGM�I������{y���W
	}
	// �r�d�֌W�I�������W
	for (int i = 0; i < SEData::GetNumber() + 1; i++)
	{
		sound_room_coordinate_alternative_se_x[i] = sound_room_coordinate_alternative_x[0] + sound_room_size_alternative_x * (i % 2 == 0 ? 2.5f : 3.5f);
		sound_room_coordinate_alternative_se_y[i] = 100 * bairitu + sound_room_size_alternative_y * (i / 2); // SE�I������{y���W
	}
	// �wTITLE�x������
	sound_room_coordinate_string_title_x = 90 * bairitu;
	sound_room_coordinate_string_title_y = 180 * bairitu;
	// �wBGM���ʁx������
	sound_room_coordinate_bgm_message_y = 250 * bairitu;
	sound_room_coordinate_bgm_volume_up_x = sound_room_coordinate_string_title_x + bairitu * 130;
	sound_room_coordinate_bgm_volume_up_y = 40 * bairitu + sound_room_coordinate_bgm_message_y;
	// �wSE���ʁx������
	sound_room_coordinate_se_message_y = 330 * bairitu;
	sound_room_coordinate_se_volume_up_x = sound_room_coordinate_string_title_x + bairitu * 130;
	sound_room_coordinate_se_volume_up_y = 40 * bairitu + sound_room_coordinate_se_message_y;
}
// �T�E���h���[���̕`�揈��
void DrawSoundRoom()
{
	DrawStringFToHandle(90 * bairitu, 100 * bairitu, "SoundRoom", GetColor(255, 255, 255), g_font3);
	// BGM�{�^���i�v���g�^�C�v�j
	for (int i = -1; i < BGM_NUMBER; i++)
	{
		int color_x = (i + 2) / 2 % 2 == 1 ? GetColor(128, 128, 128) : GetColor(0, 225, 225);	// ��ڂ͊D�F�A�����ڂ͐��F
		DrawBoxAA(sound_room_coordinate_alternative_x[i + 1], sound_room_coordinate_alternative_y[i + 1], sound_room_coordinate_alternative_x[i + 1] + sound_room_size_alternative_x - 1, sound_room_coordinate_alternative_y[i + 1] + sound_room_size_alternative_y - 1, color_x, TRUE);
		if(i == -1)
		{ 
			DrawFormatStringFToHandle(sound_room_coordinate_alternative_x[i + 1], sound_room_coordinate_alternative_y[i + 1] + bairitu * 10, GetColor(255, 255, 255), g_font3, music_string_stop.name);	// ����
		}
		else
		{
			DrawFormatStringFToHandle(sound_room_coordinate_alternative_x[i + 1], sound_room_coordinate_alternative_y[i + 1] + bairitu * 10, GetColor(255, 255, 255), g_font3, music_string[i].name);	// ����
		}
	}
	// �r�d�{�^���i�v���g�^�C�v�j
	for (int i = 0; i < SEData::GetNumber() + 1; i++)
	{
		int color_x = (i + 1) / 2 % 2 == 1 ? GetColor(128, 128, 128) : GetColor(0, 225, 225);	// ��ڂ͊D�F�A�����ڂ͐��F�i�����s�ڂ͓���ւ��j
		DrawBoxAA(sound_room_coordinate_alternative_se_x[i], sound_room_coordinate_alternative_se_y[i], sound_room_coordinate_alternative_se_x[i] + sound_room_size_alternative_x - 1, sound_room_coordinate_alternative_se_y[i] + sound_room_size_alternative_y - 1, color_x, TRUE);
		DrawFormatStringFToHandle(sound_room_coordinate_alternative_se_x[i], sound_room_coordinate_alternative_se_y[i] + bairitu * 10, GetColor(255, 255, 255), g_font3, i == 0 ? "SE��~" : se[i - 1].GetName());	// ����
	}
	// �wTITLE�x
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_string_title_y, "TITLE", DrawTitleStringColor(sound_room_coordinate_string_title_x, sound_room_coordinate_string_title_y, GetDrawStringWidthToHandle("TITLE", 5, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	// �w�a�f�l�x
	DrawStringFToHandle(sound_room_coordinate_alternative_x[0], sound_room_coordinate_alternative_y[0] - bairitu * 30, "�a�f�l", GetColor(255, 255, 255), g_font3);
	// �w�r�d�x
	DrawStringFToHandle(sound_room_coordinate_alternative_se_x[0], sound_room_coordinate_alternative_y[0] - bairitu * 30, "�r�d", GetColor(255, 255, 255), g_font3);
	// �wBGM���ʁx
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_message_y, "BGM����", GetColor(255, 255, 255), g_font3);
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_volume_up_y, "��", DrawTitleStringColor(sound_room_coordinate_string_title_x, sound_room_coordinate_bgm_volume_up_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	DrawFormatStringFToHandle((sound_room_coordinate_string_title_x + sound_room_coordinate_bgm_volume_up_x + GetDrawStringWidthToHandle("��", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%d��", bgm_volume) / 2, sound_room_coordinate_bgm_volume_up_y, GetColor(255, 255, 255), g_font3, "%d��", bgm_volume);
	DrawStringFToHandle(sound_room_coordinate_bgm_volume_up_x, sound_room_coordinate_bgm_volume_up_y, "��", DrawTitleStringColor(sound_room_coordinate_bgm_volume_up_x, sound_room_coordinate_bgm_volume_up_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	// �wSE���ʁx
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_se_message_y, "SE����", GetColor(255, 255, 255), g_font3);
	DrawStringFToHandle(sound_room_coordinate_string_title_x, sound_room_coordinate_se_volume_up_y, "��", DrawTitleStringColor(sound_room_coordinate_string_title_x, sound_room_coordinate_se_volume_up_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	DrawFormatStringFToHandle((sound_room_coordinate_string_title_x + sound_room_coordinate_se_volume_up_x + GetDrawStringWidthToHandle("��", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%d��", se_volume) / 2, sound_room_coordinate_se_volume_up_y, GetColor(255, 255, 255), g_font3, "%d��", se_volume);
	DrawStringFToHandle(sound_room_coordinate_se_volume_up_x, sound_room_coordinate_se_volume_up_y, "��", DrawTitleStringColor(sound_room_coordinate_se_volume_up_x, sound_room_coordinate_se_volume_up_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
}
