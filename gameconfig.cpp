#include "gameconfig.h"

#pragma region ver0.0026���쎞�R�����g���R�[�h
//char* config_message_message_speed[3] = {"�������", "�ӂ�", "�͂₢"};	// �ݒ胂�[�h�ŕ`�悳���w�����X�s�[�h�x�I���̕����̎��
#pragma endregion
char* config_message_message_speed[3] = { (char*)"�������", (char*)"�ӂ�", (char*)"�͂₢" };	// �ݒ胂�[�h�ŕ`�悳���w�����X�s�[�h�x�I���̕����̎��

BOOL config_before_mc = FALSE;	// �^�C�g���ł͂Ȃ����C���R�~������ݒ胂�[�h�ɗ�����
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfc=click_flag_config�j
BOOL cfc_move_title = FALSE;// �^�C�g����ʂֈړ�
#pragma region ver0.0042���쎞�R�����g���R�[�h
//BOOL cfc_window_mode_change = FALSE;	// �E�B���h�E�A�t���X�N���[����؂�ւ���
#pragma endregion
BOOL cfc_window_mode_change[2];			// �E�B���h�E�A�t���X�N���[����؂�ւ���
BOOL cfc_screen_change_720p = FALSE;	// �E�B���h�E�𑜓x��720px�ɂ���
BOOL cfc_screen_change_1080p = FALSE;	// �E�B���h�E�𑜓x��1080px�ɂ���
BOOL cfc_bgm_down = FALSE;				// �a�f�l���ʂ�������
BOOL cfc_bgm_up = FALSE;				// �a�f�l���ʂ��グ��
BOOL cfc_se_down = FALSE;				// �r�d���ʂ�������
BOOL cfc_se_up = FALSE;					// �r�d���ʂ��グ��
BOOL cfc_message_slow = FALSE;			// ���b�Z�[�W���x��x������
BOOL cfc_message_fast = FALSE;			// ���b�Z�[�W���x�𑬂�����
BOOL cfc_dialog_change = FALSE;			// �_�C�A���O�{�b�N�X�\���t���O��؂�ւ�
BOOL cfc_text_window_clear[2];			// ���b�Z�[�W���ߓx�𑝌�

float config_retu2_x = 0;										// �Q��ڍ���X���W
float config_coordinate_icon_back_x = 0;						// �wBACK�x�A�C�R�����[x���W
float config_coordinate_icon_back_y = 0;						// �wBACK�x�A�C�R����[y���W
#pragma region ver0.0042���쎞�R�����g���R�[�h
//float config_coordinate_full_screen_switch_x = 0;				// �t���X�N���[���؂�ւ��X�C�b�`X���W
#pragma endregion
float config_coordinate_full_screen_switch_x[2];				// �t���X�N���[���؂�ւ��X�C�b�`X���W
float config_coordinate_full_screen_switch_y = 0;				// �t���X�N���[���؂�ւ��X�C�b�`Y���W
float config_coordinate_screen_resolution_switch_y = 0;			// ��ʉ𑜓x�؂�ւ��X�C�b�`Y���W
float config_coordinate_screen_resolution_switch_1920_x = 0;	// ��ʉ𑜓x�؂�ւ��X�C�b�`�i1920�~1080�jX���W
float config_bgm_message_y = 0;									// �a�f�l���ʊ֌WY���W
float config_coordinate_arrow_down_x = 0;						// ����󍶒[X���W
float config_bgm_volume_up_x = 0;								// �a�f�l�w���x����X���W
float config_se_message_y = 0;									// �r�d���ʊ֌WY���W
float config_message_speed_y = 0;								// �R�~�����b�Z�[�W���x�֌WY���W
float config_text_window_clear_y = 0;							// �e�L�X�g�E�B���h�E���ߓx�֌WY���W
float config_coordinate_message_speed_x[3];						// ���b�Z�[�W���x�I�����e���[x���W

// �ݒ胂�[�h�ڍs����
void GameConfigNext(BOOL x)	// ���C���R�~����ʂ���ڍs���Ă�����
{
	g_gamestate = GAME_CONFIG;
	config_before_mc = x;
}
// GAME_CONFIG��Ԃ̃��C������
void GameConfig()
{
	GameConfigControl();
	DrawGameConfig();
}
// �ݒ��ʎ����쏈��
void GameConfigControl()
{
	// �}�E�X�̃{�^���������ꂽ�藣���ꂽ�肵�����ǂ����̏����擾����
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0)
	{
		#pragma region ver0.0042���쎞�R�����g���R�[�h
//		// ���{�^����������Ă�����
//		if ((Button & MOUSE_INPUT_LEFT) != 0)
//		{
//			if (LogType == MOUSE_INPUT_LOG_DOWN)
//			{
//				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
//				if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_move_title = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x, config_coordinate_full_screen_switch_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_window_mode_change = TRUE; }
//				#pragma region ver0.0041���쎞�R�����g���R�[�h
//				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x, config_coordinate_screen_resolution_switch_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_screen_change_720p = TRUE; }
//				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_screen_change_1080p = TRUE; }
//#pragma endregion
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_bgm_message_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_bgm_down = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_bgm_message_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_bgm_up = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_se_message_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_se_down = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_se_message_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_se_up = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_message_slow = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfc_message_fast = TRUE; }
//				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, image_dialog[0].size_x, image_dialog[0].size_y, TRUE, FALSE) == TRUE) { cfc_dialog_change = TRUE; }
//			}
//			else if (LogType != MOUSE_INPUT_LOG_DOWN)
//			{
//				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
//				// �^�C�g����ʂֈړ�
//				if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_move_title) == TRUE){ GameTitleNext(); }
//				// �E�B���h�E�A�t���X�N���[����؂�ւ���
//				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x, config_coordinate_full_screen_switch_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_window_mode_change) == TRUE)
//				{ 
//					// �����݃E�B���h�E�Ȃ�t���X�N�ɁA�t���X�N�Ȃ�E�B���h�E�ɂ���
//					ChangeWindowMode(flag_mode_window = GetWindowModeFlag() == TRUE ? FALSE : TRUE);
//					SetMouseDispFlag(TRUE);									// �}�E�X��\����Ԃɂ���
//				}
//
//				#pragma region ver0.0041���쎞�R�����g���R�[�h
//				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x, config_coordinate_screen_resolution_switch_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_screen_change_720p) == TRUE)
//				//{ 
//				//	flag_full_hd_now = FALSE;
//				//	ScreenResolutionChange();
//				//}
//
//				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_screen_change_1080p) == TRUE)
//				//{
//				//	if(flag_full_hd_ok == TRUE)	// �t���g�c�`�悪�\�Ȃ�
//				//	{
//				//		flag_full_hd_now = TRUE;
//				//		ScreenResolutionChange();
//				//	}
//				//}
//#pragma endregion
//				// ���ʂ�������
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_bgm_message_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_bgm_down) == TRUE)
//				{ 
//					bgm_volume -= 5; 
//					ChangeBGMVolume();
//				}
//				// ���ʂ��グ��
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_bgm_message_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_bgm_up) == TRUE)
//				{ 
//					bgm_volume += 5;
//					ChangeBGMVolume();
//				}
//				// �r�d���ʂ�������
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_se_message_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_se_down) == TRUE)
//				{ 
//					se_volume -= 5;
//					ChangeSEVolume();
//				}
//				// �r�d���ʂ��グ��
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_se_message_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_se_up) == TRUE)
//				{ 
//					se_volume += 5;
//					ChangeSEVolume();
//				}
//				// ���ʕϓ��ɂ���ĉ��i��j���l���߂����ꍇ�A�C������
//				if (bgm_volume < 0){ bgm_volume = 0; }
//				else if (bgm_volume > 100){ bgm_volume = 100; }
//				if (se_volume < 0){ se_volume = 0; }
//				else if (se_volume > 100){ se_volume = 100; }
//				// ���b�Z�[�W���x��ύX����
//				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_message_slow) == TRUE){ GameConfigMessageSpeedChange(FALSE); }
//				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_message_fast) == TRUE){ GameConfigMessageSpeedChange(TRUE); }
//				// �_�C�A���O�{�b�N�X�\���t���O��؂�ւ���
//				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, image_dialog[0].size_x, image_dialog[0].size_y, FALSE, cfc_dialog_change) == TRUE) { FlagChange(&flag_dialog_appear); }
//				// �S�Ẵt���O��߂�
//				cfc_move_title = FALSE;				// �^�C�g����ʂֈړ�
//				cfc_window_mode_change = FALSE;		// �E�B���h�E�A�t���X�N���[����؂�ւ���
//				cfc_screen_change_720p = FALSE;		// �E�B���h�E�𑜓x��720px�ɂ���
//				cfc_screen_change_1080p = FALSE;	// �E�B���h�E�𑜓x��1080px�ɂ���
//				cfc_bgm_down = FALSE;				// �a�f�l���ʂ�������
//				cfc_bgm_up = FALSE;					// �a�f�l���ʂ��グ��
//				cfc_se_down = FALSE;				// �r�d���ʂ�������
//				cfc_se_up = FALSE;					// �r�d���ʂ��グ��
//				cfc_message_slow = FALSE;			// ���b�Z�[�W���x��x������
//				cfc_message_fast = FALSE;			// ���b�Z�[�W���x�𑬂�����
//				cfc_dialog_change = FALSE;			// �_�C�A���O�{�b�N�X�\���t���O��؂�ւ���
//			}
//		}
#pragma endregion
		// ���{�^����������Ă�����
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				#pragma region ver0.0043���쎞�R�����g���R�[�h
				//if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
#pragma endregion
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_icon_back_x, config_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x[IO_WINDOW_TYPE_FULL_SCREEN], config_coordinate_full_screen_switch_y, image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].size_x, image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].size_y, TRUE, FALSE) == TRUE) { cfc_window_mode_change[IO_WINDOW_TYPE_FULL_SCREEN] = TRUE; }
				else if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x[IO_WINDOW_TYPE_WINDOW], config_coordinate_full_screen_switch_y, image_option_window_type[IO_WINDOW_TYPE_WINDOW].size_x, image_option_window_type[IO_WINDOW_TYPE_WINDOW].size_y, TRUE, FALSE) == TRUE) { cfc_window_mode_change[IO_WINDOW_TYPE_WINDOW] = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_bgm_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, TRUE, FALSE) == TRUE) { cfc_bgm_down = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_bgm_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, TRUE, FALSE) == TRUE) { cfc_bgm_up = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_se_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, TRUE, FALSE) == TRUE) { cfc_se_down = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_se_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, TRUE, FALSE) == TRUE) { cfc_se_up = TRUE; }

				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_text_window_clear_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, TRUE, FALSE) == TRUE) { cfc_text_window_clear[FALSE] = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_text_window_clear_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, TRUE, FALSE) == TRUE) { cfc_text_window_clear[TRUE] = TRUE; }

				if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfc_message_slow = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE) { cfc_message_fast = TRUE; }
				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, image_dialog[0].size_x, image_dialog[0].size_y, TRUE, FALSE) == TRUE) { cfc_dialog_change = TRUE; }
				else if (image_icon_config_dialog[0][0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_config_dialog[1][0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_config_text_speed[0][0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_config_text_speed[1][0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_config_text_speed[2][0].JudgementClickCheck() == TRUE) {}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				#pragma region ver0.0043���쎞�R�����g���R�[�h
				// �^�C�g����ʂֈړ�
				//if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_move_title) == TRUE) { GameTitleNext(); }
#pragma endregion
				// �ݒ��ʂ̑O�ɂ������[�h�Ɉڍs
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_icon_back_x, config_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfc_move_title) == TRUE)
				{
					if (config_before_mc == FALSE) { GameTitleNext(); }
					else{ g_gamestate = GAME_MAIN_COMMUNICATION; }
				}
				// �E�B���h�E�A�t���X�N���[����؂�ւ���
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x[IO_WINDOW_TYPE_FULL_SCREEN], config_coordinate_full_screen_switch_y, image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].size_x, image_option_window_type[IO_WINDOW_TYPE_FULL_SCREEN].size_y, FALSE, cfc_window_mode_change[IO_WINDOW_TYPE_FULL_SCREEN]) == TRUE)
				{
					// �����݃E�B���h�E�Ȃ�t���X�N�ɂ���
					if (flag_mode_window == TRUE)
					{ 
						flag_mode_window = FALSE;
						ChangeWindowMode(FALSE);
					}
					SetMouseDispFlag(TRUE);									// �}�E�X��\����Ԃɂ���
				}
				else if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_full_screen_switch_x[IO_WINDOW_TYPE_WINDOW], config_coordinate_full_screen_switch_y, image_option_window_type[IO_WINDOW_TYPE_WINDOW].size_x, image_option_window_type[IO_WINDOW_TYPE_WINDOW].size_y, FALSE, cfc_window_mode_change[IO_WINDOW_TYPE_WINDOW]) == TRUE)
				{
					// �����݃t���X�N�Ȃ�E�B���h�E�ɂ���
					if (flag_mode_window == FALSE)
					{
						flag_mode_window = TRUE;
						ChangeWindowMode(TRUE);
					}
					SetMouseDispFlag(TRUE);									// �}�E�X��\����Ԃɂ���
				}

				// ���ʂ�������
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_bgm_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, FALSE, cfc_bgm_down) == TRUE)
				{
					bgm_volume -= 5;
					ChangeBGMVolume();
				}
				// ���ʂ��グ��
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_bgm_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, FALSE, cfc_bgm_up) == TRUE)
				{
					bgm_volume += 5;
					ChangeBGMVolume();
				}
				// �r�d���ʂ�������
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_se_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_y, FALSE, cfc_se_down) == TRUE)
				{
					se_volume -= 5;
					ChangeSEVolume();
				}
				// �r�d���ʂ��グ��
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_se_message_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, FALSE, cfc_se_up) == TRUE)
				{
					se_volume += 5;
					ChangeSEVolume();
				}
				// ���b�Z�[�W�E�B���h�E���ߓx��������
				if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_arrow_down_x, config_text_window_clear_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, FALSE, cfc_text_window_clear[FALSE]) == TRUE && text_window_clear_percentage >= 20)
				{ 
					text_window_clear_percentage -= 20;
					if (text_window_clear_percentage < 0) { text_window_clear_percentage = 0; }
				}
				// ���b�Z�[�W�E�B���h�E���ߓx���グ��
				if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_text_window_clear_y, image_option_arrow[0].size_x, image_option_arrow[0].size_x, FALSE, cfc_text_window_clear[TRUE]) == TRUE && text_window_clear_percentage <= 80)
				{
					text_window_clear_percentage += 20;
					if (text_window_clear_percentage > 100) { text_window_clear_percentage = 100; }
				}
				// ���ʕϓ��ɂ���ĉ��i��j���l���߂����ꍇ�A�C������
				if (bgm_volume < 0) { bgm_volume = 0; }
				else if (bgm_volume > 100) { bgm_volume = 100; }
				if (se_volume < 0) { se_volume = 0; }
				else if (se_volume > 100) { se_volume = 100; }
				// ���b�Z�[�W���x��ύX����
				#pragma region ver0.0081���쎞�R�����g���R�[�h
				//if (ClickFlagCheckF(ClickX, ClickY, config_retu2_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_message_slow) == TRUE) { GameConfigMessageSpeedChange(FALSE); }
				//if (ClickFlagCheckF(ClickX, ClickY, config_bgm_volume_up_x, config_message_speed_y, (float)GetDrawStringWidthToHandle("��", 2, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfc_message_fast) == TRUE) { GameConfigMessageSpeedChange(TRUE); }
#pragma endregion
				else if (image_icon_config_text_speed[0][0].JudgementReleaseCheck() == TRUE) { g_commumessagespeed = COMMU_MESSAGE_SPEED_SLOW; }
				else if (image_icon_config_text_speed[1][0].JudgementReleaseCheck() == TRUE) { g_commumessagespeed = COMMU_MESSAGE_SPEED_NORMAL; }
				else if (image_icon_config_text_speed[2][0].JudgementReleaseCheck() == TRUE) { g_commumessagespeed = COMMU_MESSAGE_SPEED_FAST; }
				// �_�C�A���O�{�b�N�X�\���t���O��؂�ւ���
				//if (ClickFlagCheckF(ClickX, ClickY, config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, image_dialog[0].size_x, image_dialog[0].size_y, FALSE, cfc_dialog_change) == TRUE) { FlagChange(&flag_dialog_appear); }
				else if (image_icon_config_dialog[0][0].JudgementReleaseCheck() == TRUE) { flag_dialog_appear = TRUE; }
				else if (image_icon_config_dialog[1][0].JudgementReleaseCheck() == TRUE) { flag_dialog_appear = FALSE;}
				// �S�Ẵt���O��߂�
				cfc_move_title = FALSE;												// �^�C�g����ʂֈړ�
				#pragma region ver0.0042���쎞�R�����g���R�[�h
				//cfc_window_mode_change = FALSE;		// �E�B���h�E�A�t���X�N���[����؂�ւ���
#pragma endregion
				for (int i = 0; i < 2; i++) { cfc_window_mode_change[i] = FALSE; }	// �E�B���h�E�A�t���X�N���[����؂�ւ���
				cfc_screen_change_720p = FALSE;										// �E�B���h�E�𑜓x��720px�ɂ���
				cfc_screen_change_1080p = FALSE;									// �E�B���h�E�𑜓x��1080px�ɂ���
				cfc_bgm_down = FALSE;												// �a�f�l���ʂ�������
				cfc_bgm_up = FALSE;													// �a�f�l���ʂ��グ��
				cfc_se_down = FALSE;												// �r�d���ʂ�������
				cfc_se_up = FALSE;													// �r�d���ʂ��グ��
				cfc_message_slow = FALSE;											// ���b�Z�[�W���x��x������
				cfc_message_fast = FALSE;											// ���b�Z�[�W���x�𑬂�����
				//cfc_dialog_change = FALSE;											// �_�C�A���O�{�b�N�X�\���t���O��؂�ւ���
				// �_�C�A���O�{�b�N�X�\���t���O��؂�ւ���
				for (int i = 0; i < 2; i++) { image_icon_config_dialog[i][0].CJChange(FALSE); }

				for (int i = 0; i < 2; i++) { cfc_text_window_clear[i]; }			// ���b�Z�[�W���ߓx�𑝌�
			}
		}
	}
}
// �R�~���̕����X�s�[�h�Ɋւ���v�f��ύX����
void GameConfigMessageSpeedChange(BOOL x)	// ������x�����邩�������邩�̃t���O
{
	// �X�s�[�h��ύX����
	if (x == FALSE)
	{
		if (g_commumessagespeed == COMMU_MESSAGE_SPEED_NORMAL){ g_commumessagespeed = COMMU_MESSAGE_SPEED_SLOW; }
		else if (g_commumessagespeed == COMMU_MESSAGE_SPEED_FAST){ g_commumessagespeed = COMMU_MESSAGE_SPEED_NORMAL; }
	}
	else
	{
		if (g_commumessagespeed == COMMU_MESSAGE_SPEED_NORMAL){ g_commumessagespeed = COMMU_MESSAGE_SPEED_FAST; }
		else if (g_commumessagespeed == COMMU_MESSAGE_SPEED_SLOW){ g_commumessagespeed = COMMU_MESSAGE_SPEED_NORMAL; }
	}
}
// �Q�[���Ŏg���l�X�ȍ��W���i�āj��`����
void CoordinateSetting()
{
	GameConfigCoordinateSetting();
	GameMainCommunicationCoordinateSetting();
	GameMapCoordinateSetting();
	GameTitleCoordinateSetting();
	SoundRoomCoordinateSetting();		// �T�E���h���[��
	GameSaveLoadCoordinateSetting();	// �Z�[�u�A���[�h���
	GameCommuSelectCoordinateSetting();	// �R�~���Z���N�g���
}
// �ݒ��ʂŎg���l�X�ȍ��W���i�āj��`����
void GameConfigCoordinateSetting()
{
	config_retu2_x = bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X + GetDrawStringWidthToHandle("���b�Z�[�W���x�@", 16, g_font3);																								// �Q��ڍ���X���W
	config_coordinate_icon_back_x = screen_size_x - size_icon_auto.x - bairitu * 99;																																	// �wBACK�x�A�C�R�����[x���W
	config_coordinate_icon_back_y = bairitu * 99;																																										// �wBACK�x�A�C�R����[y���W
	#pragma region ver0.0042���쎞�R�����g���R�[�h
	//config_coordinate_full_screen_switch_x = config_retu2_x + GetDrawStringWidthToHandle("�t���X�N���[�� ", 15, g_font3);																								// �t���X�N���[���؂�ւ��X�C�b�`X���W
	//config_coordinate_full_screen_switch_y = bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y;																																	// �t���X�N���[���؂�ւ��X�C�b�`Y���W
	//config_coordinate_screen_resolution_switch_y = config_coordinate_full_screen_switch_y + bairitu * 50;																												// ��ʉ𑜓x�؂�ւ��X�C�b�`Y���W
	//config_coordinate_screen_resolution_switch_1920_x = config_coordinate_full_screen_switch_x[0/*�K��*/] + GetDrawStringWidthToHandle("1920�~1080", 10, g_font3) + bairitu * 160;													// ��ʉ𑜓x�؂�ւ��X�C�b�`�i1920�~1080�jX���W
	//config_bgm_message_y = config_coordinate_screen_resolution_switch_y + bairitu * CONFIG_LINE_SPACE * 2;																// �a�f�l���ʊ֌WY���W
#pragma endregion
	config_coordinate_screen_resolution_switch_y = bairitu * 630;																																						// ��ʉ𑜓x�؂�ւ��X�C�b�`Y���W
	config_coordinate_screen_resolution_switch_1920_x = bairitu * 1050;																																					// ��ʉ𑜓x�؂�ւ��X�C�b�`�i1920�~1080�jX���W
	config_bgm_message_y = bairitu * 339;																																												// �a�f�l���ʊ֌WY���W
	config_coordinate_arrow_down_x = image_option_arrow[0].size_x + bairitu * 1275;																																		// ����󍶒[X���W
	#pragma region ver0.0042���쎞�R�����g���R�[�h
	//config_bgm_volume_up_x = config_retu2_x + bairitu * 200;																											// �a�f�l�w���x����X���W
#pragma endregion
	config_bgm_volume_up_x = config_coordinate_arrow_down_x + bairitu * 150;																																			// �a�f�l�w���x����X���W
	config_se_message_y = config_bgm_message_y + bairitu * CONFIG_LINE_SPACE;																																			// �a�f�l���ʊ֌WY���W
	#pragma region ver0.0042���쎞�R�����g���R�[�h
	//config_message_speed_y = config_se_message_y + bairitu * CONFIG_LINE_SPACE * 2;																						// �R�~�����b�Z�[�W���x�֌WY���W
#pragma endregion
	config_text_window_clear_y = config_se_message_y + bairitu * CONFIG_LINE_SPACE;																																		// �e�L�X�g�E�B���h�E���ߓx�֌WY���W
	config_message_speed_y = config_text_window_clear_y + bairitu * CONFIG_LINE_SPACE;																																	// �R�~�����b�Z�[�W���x�֌WY���W
	for (int i = 0; i < CONFIG_MESSAGE_SPEED_NUMBER; i++) { config_coordinate_message_speed_x[i] = bairitu * 1290 + (i - 1) * image_option_message_speed[0].size_x * 1.5f - image_option_message_speed[0].size_x / 2; }	// ���b�Z�[�W���x�I�����e���[x���W
	for (int i = 0; i < 2; i++) { config_coordinate_full_screen_switch_x[i] = (i == 0 ? -0.75f : 0.75f) * image_option_window_type[i].size_x + bairitu * 1200; }														// �t���X�N���[���؂�ւ��X�C�b�`X���W
	config_coordinate_full_screen_switch_y = config_message_speed_y + bairitu * CONFIG_LINE_SPACE * 2;																													// �t���X�N���[���؂�ւ��X�C�b�`Y���W
	// �_�C�A���O�{�b�N�X�\���̃I���I�t�摜
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++) { image_icon_config_dialog[i][j].CoordinateSetting2(1302.0f + i * 105, 758); }
	}
	// �e�L�X�g���b�Z�[�W���x�摜
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			const float X = 1024.0f + (i >= 1 ? 160 : 0) + (i == 2 ? 220 : 0);	// �ǐ��P��̂��߂̒萔��
			image_icon_config_text_speed[i][j].CoordinateSetting2(
				X, 548);
		}
	}
}
// �ݒ��ʎ��`�揈��
void DrawGameConfig()
{
	// �A�C�R���ł͂Ȃ��摜
	DrawExtendGraphF(0, 0, (float)screen_size_x, (float)screen_size_y, image_option[0].Handle, TRUE);
	DrawExtendGraphF(0, 0, (float)screen_size_x, (float)screen_size_y, image_option[1].Handle, TRUE);

	DrawExtendGraphF(0, 0, (float)screen_size_x, (float)screen_size_y, image_option[2].Handle, TRUE);
	DrawExtendGraphF(0, 0, (float)screen_size_x, (float)screen_size_y, image_option[3].Handle, TRUE);
	
	#pragma region ver0.0042���쎞�R�����g���R�[�h
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y, "��ʃ��[�h", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y, "�t���X�N���[��", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_coordinate_full_screen_switch_x, config_coordinate_full_screen_switch_y, GetWindowModeFlag() == FALSE ? "��" : "��", GetColor(255, 255, 255), g_font3);
#pragma endregion
	#pragma region ver0.0041���쎞�R�����g���R�[�h
	//DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y + bairitu * 50, "1280�~720", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_coordinate_full_screen_switch_x, config_coordinate_screen_resolution_switch_y, screen_size_x == 1280 ? "��" : "��", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_coordinate_full_screen_switch_x + bairitu * 100, config_coordinate_screen_resolution_switch_y, "1920�~1080", (flag_full_hd_ok == TRUE) ? GetColor(255, 255, 255) : GetColor(128, 128, 128), g_font3);	// �t���g�c�ɂł��Ȃ����j�^�[�𑜓x�Ȃ�D�F�ɂ���
	//DrawStringFToHandle(config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, screen_size_x == 1920 ? "��" : "��", GetColor(255, 255, 255), g_font3);
#pragma endregion
	#pragma region ver0.0042���쎞�R�����g���R�[�h
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, config_coordinate_screen_resolution_switch_y, "���݉𑜓x", GetColor(255, 255, 255), g_font3);
	////DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y + bairitu * 50, (flag_full_hd_now == FALSE) ? "1280�~720" : "1920�~1080", GetColor(255, 255, 255), g_font3);
	//if (flag_full_hd_now == FALSE) { DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y + bairitu * 50, "1280�~720", GetColor(255, 255, 255), g_font3); }
	//else { DrawStringFToHandle(config_retu2_x, bairitu * CONFIG_MESSEAGE_GRAPH_MODE_Y + bairitu * 50, "1920�~1080", GetColor(255, 255, 255), g_font3); }
#pragma endregion
	float image_pixel_size = image_option[flag_full_hd_now == FALSE ? IMG_OPTION_PIXEL_720 : IMG_OPTION_PIXEL_1080].size_x;
	DrawExtendGraphF(1290 * bairitu - image_pixel_size / 2, 627 * bairitu, 1290 * bairitu + image_pixel_size / 2, image_option[IMG_OPTION_PIXEL_720].size_y + 627 * bairitu, image_option[flag_full_hd_now == FALSE ? IMG_OPTION_PIXEL_720 : IMG_OPTION_PIXEL_1080].Handle, TRUE);
	//DrawExtendGraphF(config_coordinate_screen_resolution_switch_1920_x, config_coordinate_screen_resolution_switch_y, config_coordinate_screen_resolution_switch_1920_x + image_dialog[0].size_x, config_coordinate_screen_resolution_switch_y + image_dialog[0].size_y, image_dialog[flag_dialog_appear == FALSE ? 0 : 1].Handle, TRUE);
	#pragma region ver0.0043���쎞�R�����g���R�[�h
	//DrawStringFToHandle(screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, "TITLE", DrawTitleStringColor(screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * CONFIG_MESSEAGE_TITLE_Y, GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL), g_font3);
#pragma endregion
	#pragma region ver0.0042���쎞�R�����g���R�[�h
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, config_bgm_message_y, "�a�f�l����", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_retu2_x, config_bgm_message_y, "��", DrawTitleStringColor(config_retu2_x, config_bgm_message_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);

	//// �i���W������Ȃ��j
	////DrawFormatStringFToHandle(config_retu2_x + bairitu * 100 + GetDrawStringWidthToHandle("��", 2, g_font3) - GetDrawFormatStringWidthToHandle(g_font3, "%d��", bgm_volume) / 2, config_bgm_message_y, GetColor(255, 255, 255), g_font3, "%d��", bgm_volume);
	////�i���ނo�����āj
	//DrawFormatStringFToHandle((config_retu2_x + config_bgm_volume_up_x + GetDrawStringWidthToHandle("��", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%d��", bgm_volume) / 2, config_bgm_message_y, GetColor(255, 255, 255), g_font3, "%d��", bgm_volume);

	//DrawStringFToHandle(config_bgm_volume_up_x, config_bgm_message_y, "��", DrawTitleStringColor(config_bgm_volume_up_x, config_bgm_message_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	//// �r�d
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, config_se_message_y, "�r�d����", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_retu2_x, config_se_message_y, "��", DrawTitleStringColor(config_retu2_x, config_se_message_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);

	//// �i���W������Ȃ��j
	////DrawFormatStringFToHandle(config_retu2_x + bairitu * 100 + GetDrawStringWidthToHandle("��", 2, g_font3) - GetDrawFormatStringWidthToHandle(g_font3, "%d��", se_volume) / 2, config_se_message_y, GetColor(255, 255, 255), g_font3, "%d��", se_volume);
	////�i���ނo�����āj
	//DrawFormatStringFToHandle((config_retu2_x + config_bgm_volume_up_x + GetDrawStringWidthToHandle("��", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%d��", se_volume) / 2, config_se_message_y, GetColor(255, 255, 255), g_font3, "%d��", se_volume);

	//DrawStringFToHandle(config_bgm_volume_up_x, config_se_message_y, "��", DrawTitleStringColor(config_bgm_volume_up_x, config_se_message_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
#pragma endregion
	DrawExtendGraphF(config_coordinate_icon_back_x, config_coordinate_icon_back_y, config_coordinate_icon_back_x + size_icon_auto.x, config_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);

	DrawOptionArrow(bgm_volume, 5, config_bgm_message_y, FALSE);
	float number_x = bairitu * 1371;	// �a�f�l���ʒl���̒��Sx���W
	DrawFormatStringFToHandle(number_x - GetDrawFormatStringWidthToHandle(g_font3, "%d", bgm_volume) / 2, config_bgm_message_y + bairitu * 12, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::CONFIG_VOLUME)].GetHandle(), "%d", bgm_volume);
	DrawOptionArrow(bgm_volume, 5, config_bgm_message_y, TRUE);
	// �r�d
	DrawOptionArrow(se_volume, 5, config_se_message_y, FALSE);
	DrawFormatStringFToHandle(number_x - GetDrawFormatStringWidthToHandle(g_font3, "%d", se_volume) / 2, config_se_message_y + bairitu * 12, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::CONFIG_VOLUME)].GetHandle(), "%d", se_volume);
	DrawOptionArrow(se_volume, 5, config_se_message_y, TRUE);
	// ���b�Z�[�W�E�B���h�E���ߓx
	DrawOptionArrow(text_window_clear_percentage, 20, config_text_window_clear_y, FALSE);
	DrawFormatStringFToHandle(number_x - GetDrawFormatStringWidthToHandle(g_font3, "%d", text_window_clear_percentage) / 2, config_text_window_clear_y + bairitu * 12, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::CONFIG_VOLUME)].GetHandle(), "%d", text_window_clear_percentage);
	DrawOptionArrow(text_window_clear_percentage, 20, config_text_window_clear_y, TRUE);
	// ���b�Z�[�W���x
	#pragma region ver0.0042���쎞�R�����g���R�[�h
	//DrawStringFToHandle(bairitu * CONFIG_MESSEAGE_GRAPH_MODE_X, config_message_speed_y, "���b�Z�[�W���x", GetColor(255, 255, 255), g_font3);
	//DrawStringFToHandle(config_retu2_x, config_message_speed_y, "��", DrawTitleStringColor(config_retu2_x, config_message_speed_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	//DrawFormatStringFToHandle(config_retu2_x + GetDrawStringWidthToHandle("��", 2, g_font3) + (config_bgm_volume_up_x - config_retu2_x - GetDrawStringWidthToHandle("��", 2, g_font3)) / 2 - GetDrawFormatStringWidthToHandle(g_font3, "%s", config_message_message_speed[g_commumessagespeed]) / 2, config_message_speed_y, GetColor(255, 255, 255), g_font3, "%s", config_message_message_speed[g_commumessagespeed]);
	//DrawStringFToHandle(config_bgm_volume_up_x, config_message_speed_y, "��", DrawTitleStringColor(config_bgm_volume_up_x, config_message_speed_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
#pragma endregion
	//for (int i = 0; i < CONFIG_MESSAGE_SPEED_NUMBER; i++) { DrawExtendGraphF(config_coordinate_message_speed_x[i], config_message_speed_y, config_coordinate_message_speed_x[i] + image_option_message_speed[i].size_x, config_message_speed_y + image_option_message_speed[0].size_y, image_option_message_speed[i].Handle, TRUE); }
	image_icon_config_text_speed[0][g_commumessagespeed == COMMU_MESSAGE_SPEED_SLOW ? 1 : 0].DrawImage();
	image_icon_config_text_speed[1][g_commumessagespeed == COMMU_MESSAGE_SPEED_NORMAL ? 1 : 0].DrawImage();
	image_icon_config_text_speed[2][g_commumessagespeed == COMMU_MESSAGE_SPEED_FAST ? 1 : 0].DrawImage();
	// ��ʃ��[�h�I����
	for (int i = 0; i < 2; i++) { DrawExtendGraphF(config_coordinate_full_screen_switch_x[i], config_coordinate_full_screen_switch_y, config_coordinate_full_screen_switch_x[i] + image_option_window_type[i].size_x, config_coordinate_full_screen_switch_y + image_option_window_type[i].size_y, image_option_window_type[i].Handle, TRUE); }
	// �N�����_�C�A���O�{�b�N�X�\��
	image_icon_config_dialog[0][flag_dialog_appear].DrawImage();
	image_icon_config_dialog[1][flag_dialog_appear == FALSE ? 1 : 0].DrawImage();
}
// �ݒ胂�[�h�̖���`�悷��ۂ̋��ʏ���
void DrawOptionArrow(int x, int y, float z, BOOL a)	// ���ݐ��l�A����\�����邽�߂ɕK�v�Ȍ��E�l�Ƃ̐��l���Ay���W�A���͉E�������A
{
	if(a == FALSE && x >= y){ DrawExtendGraphF(config_coordinate_arrow_down_x, z, config_coordinate_arrow_down_x + image_option_arrow[0].size_x, z + image_option_arrow[0].size_y, image_option_arrow[0].Handle, TRUE); }
	else if(x + y <= 100){ DrawExtendGraphF(config_bgm_volume_up_x, z, config_bgm_volume_up_x + image_option_arrow[0].size_x, z + image_option_arrow[0].size_y, image_option_arrow[1].Handle, TRUE); }
}
