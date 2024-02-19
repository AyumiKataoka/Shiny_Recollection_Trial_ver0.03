#include "gamecommuselect.h"

CommuUpperState g_commuupperstate = CPS_COMMON;	// �\�������R�~���̎��

// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfcs=click_flag_commu_select�j
BOOL cfcs_move_title = FALSE;										// �^�C�g����ʂֈړ�
BOOL cfcs_commu_type_change[COMMU_SELECT_C_TYPE_NUMBER];			// �\������R�~���̎�ނ̐؂�ւ���
BOOL cfcs_commu_character_change[COMMU_SELECT_CHARACTER_NUMBER];	// �\������R�~���̎�ނ̐؂�ւ���

int commu_select_display = 0	;// �\����������R�~���̌�

float commu_select_coordinate_title_x;										// �wTITLE�x�A�C�R�����[x���W
float commu_select_coordinate_title_y;										// �wTITLE�x�A�C�R����[y���W
float commu_select_coordinate_c_type_x[COMMU_SELECT_C_TYPE_NUMBER];			// �R�~����ޑI�������[x���W
float commu_select_coordinate_c_type_y;										// �R�~����ޑI������[y���W
float commu_select_coordinate_alternative_x;								// �R�~���I�������[x���W�iY���W��main.h�j
float commu_select_coordinate_character_x;									// �L�����A�C�R�����[x���W
float commu_select_coordinate_character_y[COMMU_SELECT_CHARACTER_NUMBER];	// �L�����A�C�R����[y���W
// �R�~���Z���N�g��ʈڍs����
void GameCommuSelectNext()
{
	if (g_gamestate != GAME_TITLE) { MusicPlay(BN_TITLE); }			// �^�C�g���a�f�l���Đ�����
	g_gamestate = GAME_COMMU_SELECT;
	GameCommuSelectAlternativeCheck();
	// ����������
	commu_before_cs = FALSE;	// �R�~���̉{�����n�߂�O�̓R�~���Z���N�g���[�h�����������ʂ���t���O
}
// GameCommuSelect��Ԃ̃��C������
void GameCommuSelect()
{
	GameCommuSelectControl();
	DrawGameCommuSelect();
}
// �R�~���Z���N�g��ʑ��쏈��
void GameCommuSelectControl()
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
				if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_title_x, commu_select_coordinate_title_y, size_icon_auto.x * bairitu, size_icon_auto.y * bairitu, TRUE, FALSE) == TRUE) { cfcs_move_title = TRUE; }
				else if (GameMapControlCTYPECheck(TRUE)){}
				else if(GameMapControlCCharacterCheck(TRUE)){}
				else if (GameMapControlCAlternativeCheck(TRUE)) {}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				// �^�C�g���ɖ߂�
				if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_title_x, commu_select_coordinate_title_y, size_icon_auto.x * bairitu, size_icon_auto.y * bairitu, FALSE, cfcs_move_title) == TRUE) { g_gamestate = GAME_TITLE; }
				// �\��������R�~�����Ċm�F�A�\��������
				else if (GameMapControlCTYPECheck(FALSE)) {}
				else if (GameMapControlCCharacterCheck(FALSE)) {}
				else if (GameMapControlCAlternativeCheck(FALSE)) {}
				// �S�Ẵt���O��߂�
				cfcs_move_title = FALSE;																			// �^�C�g����ʂֈړ�
				for (int i = 0; i < 2; i++) { cfcs_commu_type_change[i] = FALSE; }									// �\������R�~���̎�ނ̐؂�ւ�
				for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++) { cfcs_commu_character_change[i] = FALSE; }	// �\������R�~���̃L�����̐؂�ւ�
				for (int i = 0; i < CS_COMMU_LIMIT; i++) { cfcs_move_commu[i] = FALSE; }							// �I�����ꂽ�R�~�����{������
			}
		}
	}
}
// �\��������R�~������������
void GameCommuSelectAlternativeCheck()
{
	commu_select_display = 0;
	// ����O�Ɉ�x�v�f�����Z�b�g����
	for (int i = 0; i < CS_COMMU_LIMIT; i++) { cs_displat_commu[i].StateReset(); }
	// ���ݕ\�����������R�~���̗񋓒萔�ƈ�v���Ă�����̂�S�R�~���̒����猟�����A��v���Ă�����\���̂ɉ�����
	for (int i = 0; i < GlobalStaticVariable::GetCommuNumber(); i++)
	{
		if(g_commuupperstate == commu_data[i].character_icon)
		{
			cs_displat_commu[commu_select_display].StateChange(&commu_data[i]);
			commu_select_display++;
		}
	}
}
// �R�~���Z���N�g��ʂŎg���l�X�ȍ��W���i�āj��`����
void GameCommuSelectCoordinateSetting()
{
	commu_select_coordinate_title_x = 48 * bairitu;																										// �wTITLE�x�A�C�R�����[x���W
	commu_select_coordinate_title_y = 48 * bairitu;																										// �wTITLE�x�A�C�R����[y���W
	// �R�~����ޑI�������[x���W�i�Ԋu�������̂ŏ����X�y�[�X�������Ă���j
	for (int i = 0; i < COMMU_SELECT_C_TYPE_NUMBER; i++) { commu_select_coordinate_c_type_x[i] = (float)(screen_size_x * (i + 1) / (COMMU_SELECT_C_TYPE_NUMBER + 1)) - size_ui_cs_alternative_type.x / 2 + (i - 1) * 99 * bairitu; }	

	commu_select_coordinate_c_type_y = bairitu * 99;
	commu_select_coordinate_alternative_x = bairitu * 300;																								// �R�~���I�������[x���W
	for (int i = 0; i < CS_COMMU_LIMIT; i++) { commu_select_coordinate_alternative_y[i] = i * size_ui_cs_alternative.y * 1.5f + bairitu * 240; };		// �R�~���I������[y���W
	commu_select_coordinate_character_x = bairitu * 99;																									// �L�����A�C�R�����[x���W
	for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++) { commu_select_coordinate_character_y[i] = i * size_ui_map_icon2.y * 1.5f + bairitu * 240; }	// �L�����A�C�R����[y���W
}
// �R�~���Z���N�g���̕`�揈��
void DrawGameCommuSelect()
{
	// �wTITLE�x
	DrawExtendGraphF(commu_select_coordinate_title_x, commu_select_coordinate_title_y, commu_select_coordinate_title_x + size_icon_auto.x * bairitu, commu_select_coordinate_title_y + size_icon_auto.y * bairitu, g_imghandles.icon_title, TRUE);
	// �L���������G
	if (g_commuupperstate >= CPS_MEGURU && g_commuupperstate < CPS_TEST)
	{
		float x = bairitu * 330;	// �L���������G�f�ނ��E�ɂ��炷�l
		float y = bairitu * 132;	// �L���������G�f�ނ����ɂ��炷�l
		DrawExtendGraphF(x, y, (float)screen_size_x + x, (float)screen_size_y + y, g_imghandles.character_body[g_commuupperstate - 1][0][0], TRUE);
		DrawExtendGraphF(x, y, (float)screen_size_x + x, (float)screen_size_y + y, g_imghandles.character_face[g_commuupperstate - 1][0][0][1][2], TRUE);
		DrawExtendGraphF(x, y, (float)screen_size_x + x, (float)screen_size_y + y, g_imghandles.character_eyebrow[g_commuupperstate - 1][0][0][1][2], TRUE);	// ���сi�e�X�g�j
		DrawExtendGraphF(x, y, (float)screen_size_x + x, (float)screen_size_y + y, g_imghandles.character_face[g_commuupperstate - 1][0][0][1][6], TRUE);
	}

	#pragma region ver0.00399���쎞�R�����g���R�[�h
	//for (int i = 0; i < 2; i++)
#pragma endregion
	for (int i = 0; i < COMMU_SELECT_C_TYPE_NUMBER; i++)
	{
		DrawExtendGraphF(commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, commu_select_coordinate_c_type_x[i] + size_ui_cs_alternative_type.x, commu_select_coordinate_c_type_y + size_ui_cs_alternative_type.y, g_imghandles.commu_select_type, TRUE); 
		char c[256];
		const char* s = "";
		switch (i)
		{
		case 0: s = "MAIN COMMU";	break;
		case 1: s = "CHARACTER";	break;
		case 2: s = "TEST";			break;
		default:					break;
		}
		sprintf_s(c, 256, "%s", s);
		DrawStringFToHandle(commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, "", DrawTitleStringColor(config_bgm_volume_up_x, config_message_speed_y, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
		DrawFormatStringFToHandle(commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, GetColor(0, 0, 0), g_font3, "%s", c);
	}
	// �R�~���I����
	for (int i = 0; i < CS_COMMU_LIMIT; i++) 
	{
		// �R�~���h�c��1�ȏ�i�R�~�������݂��Ă���j�Ȃ�t�h��\��������
		if (cs_displat_commu[i].id >= 1)
		{
			DrawExtendGraphF(commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[i], commu_select_coordinate_alternative_x + size_ui_cs_alternative.x, commu_select_coordinate_alternative_y[i] + size_ui_cs_alternative.y, g_imghandles.commu_select, TRUE);
			DrawFormatStringFToHandle(commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[i], GetColor(0, 0, 0), g_font3, "%s", cs_displat_commu[i].name);
		}
	}
	// �L�����A�C�R���i�\���R�~�����L�����N�^�[�̂��̂Ȃ�j
	if (g_commuupperstate >= CPS_MEGURU && g_commuupperstate < CPS_TEST)
	{
		for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++) { DrawExtendGraphF(commu_select_coordinate_character_x, commu_select_coordinate_character_y[i], commu_select_coordinate_character_x + size_ui_map_icon2.x, commu_select_coordinate_character_y[i] + size_ui_map_icon2.y, g_imghandles.ui_map_icon[i], TRUE); }
	}
}
// �R�~����ޑI�����N���b�N�m�F�p�֐�
BOOL GameMapControlCTYPECheck(BOOL x)
{
	for (int i = 0; i < COMMU_SELECT_C_TYPE_NUMBER; i++)
	{
		if (x == TRUE)
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, size_ui_cs_alternative_type.x, size_ui_cs_alternative_type.y, TRUE, FALSE) == TRUE)
			{
				cfcs_commu_type_change[i] = TRUE;
				return TRUE;
			}
		}
		else
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_c_type_x[i], commu_select_coordinate_c_type_y, size_ui_cs_alternative_type.x, size_ui_cs_alternative_type.y, FALSE, cfcs_commu_type_change[i]) == TRUE)
			{
				// �\��������R�~�����Ċm�F�A�\��������
				switch (i)
				{
				case 0: g_commuupperstate = CPS_COMMON; break;
				case 1: g_commuupperstate = CPS_MEGURU; break;
				case 2: g_commuupperstate = CPS_TEST;	break;
				default:								break;
				}
				GameCommuSelectAlternativeCheck();
				return TRUE;
			}
		}
	}
	return FALSE;
}
// �R�~���L�����I�����N���b�N�m�F�p�֐�
BOOL GameMapControlCCharacterCheck(BOOL x)
{
	for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++)
	{
		if (x == TRUE)
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_character_x, commu_select_coordinate_character_y[i], size_ui_map_icon2.x, size_ui_map_icon2.y, TRUE, FALSE) == TRUE)
			{
				cfcs_commu_character_change[i] = TRUE;
				return TRUE;
			}
		}
		else
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_character_x, commu_select_coordinate_character_y[i], size_ui_map_icon2.x, size_ui_map_icon2.y, FALSE, cfcs_commu_character_change[i]) == TRUE && g_commuupperstate >= CPS_MEGURU && g_commuupperstate < CPS_TEST)
			{
				// �\��������R�~�����Ċm�F�A�\��������
				g_commuupperstate = static_cast<CommuUpperState>(i + 1);
				GameCommuSelectAlternativeCheck();
				return TRUE;
			}
		}
	}
	return FALSE;
}
// �R�~���I�����N���b�N�m�F�p�֐�
BOOL GameMapControlCAlternativeCheck(BOOL x)
{
	for (int i = 0; i < CS_COMMU_LIMIT; i++)
	{
		if (x == TRUE)
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[i], size_ui_cs_alternative.x, size_ui_cs_alternative.y, TRUE, FALSE) == TRUE)
			{
				cfcs_move_commu[i] = TRUE;
				return TRUE;
			}
		}
		else
		{
			if (ClickFlagCheckF(ClickX, ClickY, commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[i], size_ui_cs_alternative.x, size_ui_cs_alternative.y, FALSE, cfcs_move_commu[i]) == TRUE)
			{
				// �i���݂��Ă���΁j�R�~�����{������
				if (cs_displat_commu[i].id >= 1) { GameMainCommunicationNext(cs_displat_commu[i].id - 1, TRUE, 0); }
				return TRUE;
			}
		}
	}
	return FALSE;
}