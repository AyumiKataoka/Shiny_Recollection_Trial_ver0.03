/*
���f�o�b�O�͂�قǓ��ʂȎ����Ȃ�����i�a�L�[�{����̃L�[�j�Ŏ��R�ɔ����ł���悤�ɂ��������y�Ȃ̂ł́H
*/

#include "debugprogram.h"
BOOL GlobalStaticDebug::log = FALSE;

int debug_local_int[2];	// ���[�J���ϐ�����p�ϐ��iint�j

double debug_local_double_1 = 0;	// ���[�J���ϐ�����p�ϐ��idouble�j
//�t���O
BOOL debug_load = FALSE;				// �Z�[�u�f�[�^���[�h�Ƃ͕ʂ̏������[�h�i�㏑���j����
BOOL debug_window = FALSE;				// �E�B���h�E�𑜓x��ύX����
BOOL debug_bgm_load_cut = FALSE;		// �a�f�l�̃��[�h���s��Ȃ��悤�ɂ���
BOOL debug_character_load_cut = FALSE;	// �����G�̃��[�h���s��Ȃ��悤�ɂ���
BOOL debug_escape_check = TRUE;			// �G�X�P�[�v�L�[�̓��͂ŋ����I��������
BOOL debug_keyboard = FALSE;			// �L�[�{�[�h�ɉ������f�o�b�O�������s��
BOOL debug_message = FALSE;				// ��Ԃɉ��������b�Z�[�W���o�͂���
BOOL debug_not_production = FALSE;		// �L�q�̐��Y�͂��O�ɂ���
BOOL debug_hit_judge = FALSE;			// �����蔻���\������
BOOL debug_entrance_before = FALSE;		// ���w�O�R�~���B�e���[�h�ɂ���
BOOL debug_dialog_through = TRUE;		// �𑜓x�_�C�A���O�{�b�N�X�����𖳎����Ďw�肵���𑜓x�ɂ���
// �f�o�b�O�v���O�������ʏ���
void DebugProgram(DebugType x)
{
	// �f�o�b�O���[�h�łȂ��Ȃ牽���N���Ȃ� 
	if (mode_debug == TRUE)
	{
		switch (x)
		{
		case DEBUG_MAIN:
			DebugEscapeCheck();
			DebugProgramControl();
			DebugMessage();
			break;
		case DEBUG_LOAD:
			DebugLoad();
			//DebugWindowChange();
			break;
		default:
			break;
		}
	}
}
// �Z�[�u�f�[�^�Ƃ͕ʂ̏������[�h�i�㏑���j����
void DebugLoad()
{
	if (debug_load == TRUE)
	{
	}
}
// �E�B���h�E�𑜓x��ύX����
void DebugWindowChange()
{
	#pragma region ver0.0041���쎞�R�����g���R�[�h
	//if(debug_window == TRUE)
	//{ 
	//	screen_size_x = 1280;
	//	screen_size_y = 720;
	//	bairitu = (float)screen_size_y / WINDOW_SIZE_Y;	// ������摜�̔{�����Ē�`����
	//}
#pragma endregion
	if (debug_dialog_through == TRUE) { flag_full_hd_now = FALSE; }	// �w�肵�����̃E�B���h�E�T�C�Y�ɂ���
}
// E�{X�L�[�̓��͂ŋ����I��������
void DebugEscapeCheck()
{
	if (debug_escape_check == TRUE)
	{
		#pragma region ver0.0042���쎞�R�����g���R�[�h
		//if (CheckHitKey(KEY_INPUT_E) == 1) { quit_game = TRUE; }
#pragma endregion
		if (CheckHitKey(KEY_INPUT_E) == 1 && CheckHitKey(KEY_INPUT_X) == 1) { quit_game = TRUE; }
	}
}
// �f�o�b�O���[�h���̑��쏈��
void DebugProgramControl()
{
	// �I���I�t
	if (CheckHitKey(KEY_INPUT_D) == TRUE && CheckHitKey(KEY_INPUT_B) == TRUE)
	{ 
		debug_keyboard = TRUE; 
		for (int i = 0; i < 3; i++)
		{
			//GameMainCommunicationNext(COMMU_TYPE_CHIYUKI1, FALSE, 0);
			commu_character[i] = 0;
		}
	}
	if (CheckHitKey(KEY_INPUT_0) == TRUE)
	{
		debug_keyboard = FALSE;
	}
	if (debug_keyboard == TRUE)
	{
		if (CheckHitKey(KEY_INPUT_1) == TRUE){ GameMapNext(); }
		// ���w�O�R�~���B�e���[�h�I���I�t
		if (CheckHitKey(KEY_INPUT_2) == TRUE && CheckHitKey(KEY_INPUT_O) == TRUE)
		{
			debug_entrance_before = TRUE;	// ����̂t�h����\���ɂȂ�
			GameMainCommunicationAuto();
			// �n�o��ʂ̂a�f�l���~�߂�
			if(g_gamestate == GAME_TITLE){g_bgmstate[BN_TITLE].state = BGM_STOP; }
		}
		else if (CheckHitKey(KEY_INPUT_2) == TRUE && CheckHitKey(KEY_INPUT_N) == TRUE)
		{ 
			debug_entrance_before = FALSE;
			g_commuauto = COMMU_AUTO_NORMAL;
		}
		// �Z�[�u�e�X�g
		if (CheckHitKey(KEY_INPUT_S) == TRUE) { GameSave(0); }
		// ���[�h�e�X�g
		if (CheckHitKey(KEY_INPUT_L) == TRUE) { GameLoad(0); }
		
		if (g_gamestate == GAME_MAIN_COMMUNICATION)
		{
			// �R�~���I���iCOMMU END�j
			if(CheckHitKey(KEY_INPUT_C) == 1 && CheckHitKey(KEY_INPUT_E) == 1){commu_before_cs == FALSE ? GameMainCommunicationEnd() : GameCommuSelectNext();}
			// �̌��ŏI���R�~���ֈړ�
			else if (CheckHitKey(KEY_INPUT_Q) == 1) { GameMainCommunicationNext(static_cast<int>(CommuType::TUTORIAL_END), FALSE, 0); }
		}
	}
	// �f�o�b�O���O�̃y�[�W���ύX
	if (TextLog::GetMode() == TRUE)
	{
		int key = GetJoypadInputState(DX_INPUT_KEY);
	}
	// �f�o�b�O���b�Z�[�W�I���I�t
	if((CheckHitKey(KEY_INPUT_M) == TRUE || CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) && CheckHitKey(KEY_INPUT_O) == TRUE){ debug_message = TRUE; }
	else if ((CheckHitKey(KEY_INPUT_M) == TRUE || CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) && CheckHitKey(KEY_INPUT_N) == TRUE){ debug_message = FALSE; }
}
// ���O�֌W�̏���
void DebugLog(LogOutputType x)
{
	if (GlobalStaticDebug::GetLog() == TRUE)
	{
		char c[256];
		switch (x)
		{
		case LogOutputType::LOAD_FLAG:
			sprintf_s(c, 256, "�L������ǂݍ��܂Ȃ��f�o�b�O�t���O�F%d�A�f�o�b�O�t���O�F%d\n", debug_character_load_cut, mode_debug);
			break;
		case LogOutputType::LOAD_CHECK:		sprintf_s(c, 256, "�L�����摜���F%d�A�|�[�Y���F%d�A�ߑ��摜���F%d\n", CharacterImage::CHARACTER_NUMBER, CharacterImage::PAUSE_NUMBER, CharacterImage::CLOTHES_NUMBER);	break;
		case LogOutputType::CELL_CHARACTER:
			sprintf_s(c, 256, "%d�s�ځA�R�}���h�F%s�A�L������ID�F%d�A�L������ID�F%d�A�L�����EID�F%d\n", cell_number + 2, HM[commu_number][cell_number].GetCommand(), commu_character[0], commu_character[1], commu_character[2]);				
			break;
		case LogOutputType::LOG_MESSAGE:
			sprintf_s(c, 256, "%s\n", text_log[1].GetLine());
			break;
		case LogOutputType::NOT_USE_BACKGROUND:
			LogFileAdd("�g���ĂȂ��w�i\n");
			for (int i = 0; i < bgimage[0].GetNumber(); i++)
			{
				if (bgimage[i].GetUse() == FALSE)
				{
					char c2[256];
					sprintf_s(c2, 256, "%d�F%s\n", i + 1, bgimage[i].GetName());
					LogFileAdd(c2);
				}
			}
			break;
		default:
			break;
		}

		LogFileAdd(c);
	}
}
// ��Ԃɉ��������b�Z�[�W���o�͂���
void DebugMessage()
{
	clsDx();
	// �i���w�O�j�R�~���B�e���[�h�Ȃ�S�Ẵf�o�b�O���b�Z�[�W���\���ɂ���
	if (debug_entrance_before == FALSE)
	{
		if (debug_message == TRUE)
		{
			printfDx("shift or M�{N�F�f�o�b�O���b�Z�[�W��\��\n");
			printfDx("�����G�ǂݍ��݃^�C�~���O����C�F�����G�ǂݍ��݃X�L�b�v\n");
			printfDx("��ʉ𑜓x�E%d�F%d\n", monitor_resolution_x, monitor_resolution_y);
			printfDx("�ŋ߃N���b�N���W�E%d�F%d\n", ClickX, ClickY);	// �O��N���b�N�����ۂ̍��W
			printfDx("�}�E�X���W�F%d�E%d\n", MouseX, MouseY);
			printfDx("���݂̃t���g�c�t���O�F%d\n", flag_full_hd_now);
			printfDx("E+X�F�����I��\n");
			printfDx("progress_frame_time�F%d\n", progress_frame_time);
			printfDx("progress_frame_need_time�F%d\n", progress_frame_need_time);
			printfDx("GetNowCount()�F%d\n", GetNowCount());
			printfDx("GetNowCount() - progress_frame_time�F%d\n", GetNowCount() - progress_frame_time);
			if (debug_keyboard == FALSE){ printfDx("D+B�F�f�o�b�O����\\n"); }
			else
			{
				printfDx("�f�o�b�O����i");
				if (g_gamestate == GAME_TITLE){ printfDx("1�F�}�b�v��ʂֈړ��A"); }
				if (g_gamestate == GAME_MAIN_COMMUNICATION) { printfDx("C+E�F�R�~���I���A"); }
				if (debug_entrance_before == FALSE){ printfDx("2+O�F���w�O�R�~���B�e���[�hON�A"); }
				else{ printfDx("2+N�F���w�O�R�~���B�e���[�hOFF�A"); }
				printfDx("0�F�f�o�b�O�����ԉ����j\n");
			}
			//printfDx("�T�C�Y�ϊ��{���F%f\n", bairitu);
			printfDx("���݂̏�ԁF");

			BOOL jump = FALSE;
			BOOL jump_save[6] = {};
			// �}�b�v���S����̃}�E�X���W��
			float m_x = MouseX - 1038 * bairitu;
			float m_y = MouseY - 600 * bairitu;

			switch (g_gamestate)
			{
			case GAME_TITLE:
				printfDx("�^�C�g��\n");
				printfDx("�{�[�_�[�摜�F%d\n", ImgDataHJTitle::GetCountFrame() % ImaDataName::GetTitleBorderNumber());
				printfDx("���G�f�B�b�g�L�����ǂݍ��݃t���O�i�Ή������L�[�{shift��ON�Actrl��OFF�j\n");
				for (int i = 0; i < CharacterImage::GetCharacterMember(); i++)
				{
					char c[256] = "";
					switch (i)
					{
					case 0:	sprintf_s(c, 256, "�E1:�߂���");	break;
					case 1:	sprintf_s(c, 256, "�E2:�����@");	break;
					case 2:	sprintf_s(c, 256, "�E3:�����@");	break;
					case 3:	sprintf_s(c, 256, "�E4:�z���@");	break;
					case 4:	sprintf_s(c, 256, "�E5:���@");	break;
					case 5:	sprintf_s(c, 256, "�E6:�͂Â�");	break;
					case 6:	sprintf_s(c, 256, "�E7:�Z���@");	break;
					default:									break;
					}
					printfDx("%s�F%s\n", c, CharacterImage::GetLoadEdit(i) == TRUE ? "ON" : "OFF");
				}
				break;
			case GAME_MAIN_COMMUNICATION:
				printfDx("���C���i�R�~���j\n");
				printfDx("�v���C���ԁF%f\n", commu_play_time);
				//printfDx("�wAUTO�xx���F%f\n", size_icon_auto.x);
				//printfDx("�wAUTO�xx���W�F%f\n", commu_coordinate_icon_auto_x);
				printfDx("�R�~���^�C�g���F%s\n", commu_data[commu_number].GetTitle());
				printfDx("�G�f�B�b�g���̍s�F%d\n", cell_number + 2);
				printfDx("���L�����N�^�[�h�c�F%d\n", commu_character[0]);
				printfDx("�����L�����N�^�[�h�c�F%d\n", commu_character[1]);
				printfDx("�E�L�����N�^�[�h�c�F%d\n", commu_character[2]);
				printfDx("�L�����ϓ����t���O�F%d\n", commu_mode_distance);
				printfDx("�L�����N�^�[�؂�ւ��t���[�����F%d\n", commu_character_visibility_count[1]);
				// �s�W�����v����
				printfDx("���s�W�����v����\n");
				for (int i = 0; i < GlobalStaticVariable::GetCellLimit(); i++)
				{
					if (state::GetAlternativeMoveNumber(i) != 0)
					{
						jump = TRUE;
						printfDx("�E%d�s�ځF%d�s�փW�����v\n", i + 2, state::GetAlternativeMoveNumber(i) + 2);
					}
				}
				if (jump == FALSE) { printfDx("�E�Ȃ�\n"); }
				printfDx("�ǂݍ��ݔw�i�h�c�F%d\n", HM[commu_number][cell_number].background - 1);
				if (TextLog::GetMode() == FALSE) { printfDx("�o�b�N���O�\���I�t\n"); }
				else
				{
					printfDx("���o�b�N���O���݃y�[�W�F%d\n", TextLog::GetPage());
					for (int i = 0; i < TextLog::GetPagesLineNumber(); i++)
					{
						printfDx("�E�Z���t%d�F%s\n", i + 1, text_log[(TextLog::GetPage() - 1) * 4 + i].GetLine());
					}
				}
				break;
			case GAME_MAP:
				printfDx("���C���i�}�b�v�j\n");				
				printfDx("�}�b�v���S����̃}�E�X���W���F%f�E%f\n", m_x, m_y);
				printfDx("���ݔN�����F%d��%d�T\n", game_week_number / 4 + 1, game_week_number % 4 + 1);
				for (int i = 0; i < 3; i++)
				{
					printfDx("�R�~��%d�f�[�^�F�h�c�E%d�F�^�C�g���E%s�F�o���^�C�~���O�E%d�F�A�C�R�����[x���W�E%f�F�A�C�R����[y���W�E%f\n", i, commu_data[i].id, commu_data[i].path, commu_data[i].appear_timing, draw_map_character_icon_x[i], draw_map_character_icon_y[i]);
				}
				for (int i = 0; i < 10; i++)
				{
					printfDx("�\���R�~��%d�f�[�^�F�h�c�E%d�F�^�C�g���E%s�F�o���^�C�~���O�E%d�Fx���W�E%f�Fy���W�E%f\n",
						i, commu_data_map[i].id, commu_data_map[i].path, commu_data_map[i].appear_timing, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i]);
				}
				printfDx("�w�������x�I����x���W�F%d\n", draw_map_commu_choice_x[1]);
				printfDx("�O��tips������F%s\n", tips_string[0].string);
				printfDx("���tips������F%s\n", tips_string[1].string);
				for (int i = 0; i < 3; i++) { printfDx("tips%d�h�c�F%d\n", i, tips_data[i].id); }
				printfDx("�A�C�R���P�^�C�g���F%s\n", commu_data_map[0].GetTitle());
				printfDx("�I�𒆃^�C�g���F%s\n", commu_data_map_choice.GetTitle());
				// �ꎞ�I�Ɋm�F�������
				printfDx("�L�����A�C�R�������F%f\n", size_ui_map_icon2.x);
				printfDx("�����o���F%f\n", size_ui_map_hukidasi[0].x);
				// �}�b�v��ʈړ��m�F�p�摜X���W
				//for (int i = 0; i < ImgDataMapQuestion::GetNumber(); i++){printfDx("�}�b�v��ʈړ��m�F�p�摜X���W�F%f�AY���W�F%f\n", image_map_question[i].GetCoordinateX(), image_map_question[i].GetCoordinateY());}
				// �w�������x�����蔻��
				printfDx("�w�������x�����蔻��X���W�F%f�AY���W�F%f\n",
					image_icon_map_collision_detection.GetCoordinateX(),
					image_icon_map_collision_detection.GetCoordinateY());
				break;
			case GAME_SAVELOAD:
				if (mode_save == TRUE) { printfDx("�Z�[�u\n"); }
				else { printfDx("���[�h\n"); }
				break;
			case GAME_CONFIG:
				printfDx("�ݒ�\n");
				break;
			case GAME_COMMU_SELECT:
				printfDx("�I�����P�F���[x���W�E%f�A��[y���W�E%f�A�����E%f�A�c���E%f\n", commu_select_coordinate_alternative_x, commu_select_coordinate_alternative_y[0], size_ui_cs_alternative.x, size_ui_cs_alternative.y);
				break;
			case GAME_COMMU_EDIT:
				printfDx("�R�~���쐬\n");
				printfDx("���͒��̃R�}���h�n������%d\n", g_commandinputstring);
				for(int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						printfDx("%d�s��%d��ڂh�c�F%d\n", i + 1, j + 1, edit_character_id[i][j]);
					}
				}
				break;
			default:
				printfDx("�s��\n");
				break;
			}

		}
		else
		{
			clsDx();
			if (g_gamestate == GAME_FIRST_LOAD)
			{
				printfDx("C�F�����G���[�h�����Ȃ�\nB�F�a�f�l���[�h�����Ȃ�\n");
				//printfDx("�f�ޓǂݍ��݃J�E���g�F%d\n", GetNowCount() - ImgData2::GetNoticeCount());
			}
			printfDx("(shift or M)�{O�F�f�o�b�O���b�Z�[�W�\��\n");
		}
	}
}
// �N���b�N����p�`��֐�
void DebugDrawClickJudge(int x1, int y1, int x2, int y2, int r, int g, int b)	// ���[,��[,��,����,��,��,��
{
	DrawBox(x1, y1, x1 + x2, y1 + y2, GetColor(r, g, b), FALSE);
}
// �����G���[�h���s�����m�F����
BOOL DebugLoadCheckCharacter()
{
	if (CheckHitKey(KEY_INPUT_C) == TRUE) { debug_character_load_cut = TRUE; }
	else { debug_character_load_cut = FALSE; }
	return debug_character_load_cut;
}
// �a�f�l���[�h���s�����m�F����
BOOL DebugLoadCheckBGM()
{
	if (CheckHitKey(KEY_INPUT_B) == TRUE) { debug_bgm_load_cut = TRUE; }
	return debug_bgm_load_cut;
}
