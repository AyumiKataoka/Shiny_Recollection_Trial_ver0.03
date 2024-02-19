#include "gamemap.h"

MapDestinationType g_map_destination = MAP_DESTINATION_LEFT;								// �ړ���}�b�v�̏��

TipsStringData tips_string[2];
/* TipsData�N���X ---------*/
int TipsData::number = 0;
#pragma region ver0.00708���쎞�R�����g���R�[�h
//TipsData tips_data[TIPS_NUMBER];		// tips�֌W�̍\����
#pragma endregion
TipsData tips_data[TipsData::LOAD_LIMIT];	// tips�֌W�̍\����
/*-------------------------*/
BOOL GlobalStaticMap::trial_commu_viewed[COMMU_CHARACTER_NUMBER] = { FALSE, FALSE, FALSE , FALSE , FALSE };
void GlobalStaticMap::TrialCommuViewedReset()
{
	for (int i = 0; i < COMMU_CHARACTER_NUMBER; i++) { trial_commu_viewed[i] = FALSE; }
}
#pragma region ver0.00704���쎞�R�����g���R�[�h
//CommuData commu_data[COMMU_NUMBER], commu_data_map[COMMU_MAP_LIMIT], commu_data_map_choice;	// �R�~���̃X�e�[�^�X
#pragma endregion
/* CommuData�N���X ---------*/
CommuData::MapUpperType CommuData::g_mapuppertype = CommuData::MapUpperType::DEFAULT;
CommuData commu_data[COMMU_NUMBER_MAX], commu_data_map[COMMU_MAP_LIMIT], commu_data_map_choice;	// �R�~���̃X�e�[�^�X
// �l�X�ȃf�[�^���Z�b�g����
void CommuData::SetData(int x, int y) // �����}�b�v�f�[�^�h�c�A������R�~���h�c
{
	commu_data_map[x].id = commu_data[y].id;
	sprintf_s(commu_data_map[x].path, 256, "%s", commu_data[y].path);
	sprintf_s(commu_data_map[x].title, 256, "%s", commu_data[y].title);
	commu_data_map[x].appear_timing = commu_data[y].appear_timing;
	commu_data_map[x].character_icon = commu_data[y].character_icon;
	commu_data_map[x].map_zone = commu_data[y].map_zone;
	commu_data_map[x].map_coordinate_x = commu_data[y].map_coordinate_x;
	commu_data_map[x].map_coordinate_y = commu_data[y].map_coordinate_y;
}
/*--------------------------*/
BOOL map_move_commu_check = FALSE; // �I�������R�~�����{�����邩�m�F����t���O
BOOL map_commu_upper[3][2];	// �}�b�v��ʂɃR�~���A�C�R�����o�����邩
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfgm=click_flag_game_map�j
//BOOL cfgm_move_left = FALSE;			// ���}�b�v�ֈړ�
//BOOL cfgm_move_right = FALSE;			// �E�}�b�v�ֈړ�
#pragma region ver0.0038���쎞�R�����g���R�[�h
//BOOL cfgm_commu_check = FALSE;		// �I���R�~���{����ʂ�\������
#pragma endregion
BOOL cfgm_commu_check[COMMU_MAP_LIMIT];	// �I���R�~���{����ʂ�\������
BOOL cfgm_commu_check_ok = FALSE;		// �I���R�~���ֈڍs����
BOOL cfgm_commu_check_no = FALSE;		// �I���R�~���{����ʂ���������

int game_week_number = GlobalStaticMap::WEEK_INITIAL_VALUE;	// �Q�[�����̌��A�T���Q�Ƃ���ϐ��i11���R���S�T�j
int commu_look_count[COMMU_CHARACTER_NUMBER];	// �}�b�v��ʂ���A�C�R����I�����A�i�t�����h�R�~���ȊO�́j�e�L�����̃R�~����������
//int select_map_number = 1;	// �I�΂�Ă���}�b�v�t�h
int map_font_arrow;								// �}�b�v��ʖ��̃t�H���g�T�C�Y

float draw_map_plus_x;				// �}�b�v�t�h�ɉ��Z����x���W�l
//float map_arrow_left_x;				// �����ɍs������x���W�l
//float map_arrow_right_x;			// �E���ɍs������x���W�l
float draw_map_space;				// �e�}�b�v�Ԃ̌���
#pragma region ver0.0038���쎞�R�����g���R�[�h
//float draw_map_character_icon_x;	// �L�����A�C�R��x���W�n�_
//float draw_map_character_icon_y;	// �L�����A�C�R��y���W�n�_
#pragma endregion
//float draw_map_character_icon_x[COMMU_MAP_LIMIT];		// �L�����A�C�R��x���W�n�_
float draw_map_character_icon_x[COMMU_MAP_LIMIT] = { -300, -300, -300 , -300 , -300 , -300 , -300 , -300 , -300 , -300 };		// �L�����A�C�R��x���W�n�_
float draw_map_character_icon_y[COMMU_MAP_LIMIT];		// �L�����A�C�R��y���W�n�_
float draw_map_coordinate_hukidasi_x[COMMU_MAP_LIMIT];	// �����o��x���W�n�_
float draw_map_coordinate_hukidasi_y[COMMU_MAP_LIMIT];	// �����o��y���W�n�_
float draw_map_commu_choice_x[2];						// �R�~���ړ��I����x���W�n�_
float draw_map_commu_choice_y;							// �R�~���ړ��I����y���W�n�_
// �}�b�v��ʈڍs����
void GameMapNext()
{
	MusicPlay(BN_MAP);
	SEPlay(-2);	//	�R�~���I���Ƃ������̓��[�v�r�d���~�����邽�߂̏���
	g_gamestate = GAME_MAP;
	//select_map_number = 1;
	g_map_destination = MAP_DESTINATION_LEFT;
	map_move_commu_check = FALSE;
	//draw_map_plus_x = 0;	// �}�b�v�t�h�ɉ��Z����x���W�l
	draw_map_plus_x = size_ui_map.x * bairitu + draw_map_space;	// �}�b�v�t�h�ɉ��Z����x���W�l
	game_week_number++;	// �P�T�i�߂�
	// �}�b�v�̃R�~���f�[�^������������
	for (int i = 0; i < COMMU_MAP_LIMIT; i++)
	{
		commu_data_map[i].id = 0;
		sprintf_s(commu_data_map[i].path, 256, "");
		commu_data_map[i].SetTitle((char*)"");
		commu_data_map[i].appear_timing = 0;
		commu_data_map[i].character_icon = 0;
		commu_data_map[i].map_zone = 0;
		commu_data_map[i].map_coordinate_x = 0;
		commu_data_map[i].map_coordinate_y = bairitu * -255;
		// �}�b�v��ɃA�C�R���̓����蔻�肪�c�葱����o�O��������邽�߂̏���
		draw_map_coordinate_hukidasi_y[i] = commu_data_map[i].map_coordinate_y;
	}
	// �S�ẴR�~�����猻�݂̌��A�T�Əo����������v����R�~����T���i�Y�����Ă�����̂��p�̍\���̂ɑ������H�j
	// �̌��ł̏ꍇ�A�܂����Ă��Ȃ�����̃R�~����\��������
	int x = 0;
	if (GlobalStaticVariable::GetModeTrial() == FALSE)
	{
		#pragma region ver0.0039���쎞�R�����g���R�[�h
		//int c[3] = {};	// �R�~���m�F�p�ϐ�
#pragma endregion
		int c[COMMU_CHARACTER_NUMBER] = {};	// �R�~���m�F�p�ϐ�
		#pragma region ver0.00704���쎞�R�����g���R�[�h
//for (int i = 0; i < COMMU_NUMBER; i++)
#pragma endregion
		for (int i = 0; i < GlobalStaticVariable::GetCommuNumber(); i++)
		{
			// �R�~�����߂���`����p�̃R�~���Ȃ�
			#pragma region ver0.00706���쎞�R�����g���R�[�h
//if (commu_data[i].character_icon != 0 && commu_data[i].character_icon < 6)	// �i�A�v������~���Ȃ�����ɐ����o���͂��邪�A�C�R�����\������Ȃ��j
#pragma endregion
			if (GameMapUpperCheck(commu_data[i].character_icon, i) == TRUE)
			{
				//	�L�������̂��̃��[�v��ʂ�����		�L�������̃R�~����������																						
				if (c[commu_data[i].character_icon - 1] == commu_look_count[commu_data[i].character_icon - 1])
				{
					commu_data_map[x].id = commu_data[i].id;
					#pragma region ver0.00706���쎞�R�����g���R�[�h
					//sprintf_s(commu_data_map[i].path, 256, "%s", commu_data[i].path);
#pragma endregion
					sprintf_s(commu_data_map[x].path, 256, "%s", commu_data[i].path);
					sprintf_s(commu_data_map[x].title, 256, "%s", commu_data[i].title);
					commu_data_map[x].appear_timing = commu_data[i].appear_timing;
					commu_data_map[x].character_icon = commu_data[i].character_icon;
					commu_data_map[x].map_zone = commu_data[i].map_zone;
					commu_data_map[x].map_coordinate_x = commu_data[i].map_coordinate_x;
					commu_data_map[x].map_coordinate_y = commu_data[i].map_coordinate_y;
					x++;
				}
				c[commu_data[i].character_icon - 1]++;
			}
			// �t�����h�b�f�R�~���o����ԂȂ�
			else if (CommuData::GetGMapUpperType() == CommuData::MapUpperType::FRIEND_CG_MEGURU && i == static_cast<int>(CommuType::FRIEND))
			{
				commu_data_map[x].id = commu_data[i].id;
				sprintf_s(commu_data_map[x].path, 256, "%s", commu_data[i].path);
				sprintf_s(commu_data_map[x].title, 256, "%s", commu_data[i].title);
				commu_data_map[x].appear_timing = commu_data[i].appear_timing;
				// �Ȃ���CommuData::MapUpperType�ɐ��l������������Ă���
				commu_data_map[x].character_icon = static_cast<int>(CommuData::MapUpperType::FRIEND_CG_MEGURU) - 4;

				commu_data_map[x].map_zone = commu_data[i].map_zone;
				commu_data_map[x].map_coordinate_x = commu_data[i].map_coordinate_x;
				commu_data_map[x].map_coordinate_y = commu_data[i].map_coordinate_y;
				x++;
			}
		}
	}
	else
	{
		for (int i = 0; i < COMMU_CHARACTER_NUMBER; i++)
		{
			if (GlobalStaticMap::GetTrialCommuViewed(i) == FALSE)
			{
				// i�̒l�ɉ������h�c�̃R�~���f�[�^��������
				int y = 0;
				switch (i)
				{
				case 0: y = static_cast<int>(CommuType::MEGURU5);		break;
				case 1: y = static_cast<int>(CommuType::KOGANE_STILL);	break;
				case 2: y = static_cast<int>(CommuType::JURI_STILL);	break;
				case 3: y = static_cast<int>(CommuType::RINZE0);		break;
				case 4: y = static_cast<int>(CommuType::CHIYUKI_STILL);	break;
				default:												break;
				}
				CommuData::SetData(x, y);
				x++;
			}
		}
	}
	commu_number = -1;	// ���[�h������}�b�v�Ɉړ�����f�[�^��s��Ȃ��Z�[�u�ł���悤�R�~���h�c������������
}
// GAME_MAP��Ԃ̃��C������
void GameMap()
{
	GameMapControl();
	GameMapFlame();
	DrawGameMap();
}
// �}�b�v��ʑ��쏈��
void GameMapControl()
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
				#pragma region ver0.0053���쎞�R�����g���R�[�h
				//if (ClickFlagCheckF(ClickX, ClickY, map_arrow_left_x, screen_size_y / 2.0f, (float)GetDrawStringWidthToHandle("��", 2, map_font_arrow), bairitu * FONT_SIZE_ORIGINAL_COMMU_NAME, TRUE, FALSE) == TRUE){ cfgm_move_left = TRUE; }
				//else if (ClickFlagCheckF(ClickX, ClickY, map_arrow_right_x, screen_size_y / 2.0f, (float)GetDrawStringWidthToHandle("��", 2, map_font_arrow), bairitu * FONT_SIZE_ORIGINAL_COMMU_NAME, TRUE, FALSE) == TRUE){ cfgm_move_right = TRUE; }
#pragma endregion
				if(hjimage_map[0].JudgementClickCheck() == TRUE){}
				else if(hjimage_map[1].JudgementClickCheck() == TRUE){}
				else if (hjimage_map[2].JudgementClickCheck() == TRUE) {}
				else if (hjimage_map[3].JudgementClickCheck() == TRUE) {}
				#pragma region ver0.0038���쎞�R�����g���R�[�h
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x, draw_map_character_icon_y, size_ui_map_icon.x * bairitu, size_ui_map_icon.y * bairitu, TRUE, FALSE) == TRUE){ cfgm_commu_check = TRUE; }
#pragma endregion
				else if (GameMapControlCommuCheck(TRUE)){}
				#pragma region ver0.00393���쎞�R�����g���R�[�h
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[0], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, TRUE, FALSE) == TRUE){ cfgm_commu_check_ok = TRUE; }
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[1], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, TRUE, FALSE) == TRUE){ cfgm_commu_check_no = TRUE; }
#pragma endregion
				#pragma region ver0.0081���쎞�R�����g���R�[�h
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[0], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, TRUE, FALSE) == TRUE && map_move_commu_check == TRUE) { cfgm_commu_check_ok = TRUE; }
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[1], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, TRUE, FALSE) == TRUE && map_move_commu_check == TRUE) { cfgm_commu_check_no = TRUE; }
#pragma endregion
				else if (image_icon_check[0].JudgementClickCheck() == TRUE && map_move_commu_check == TRUE) {}
				else if (image_icon_check[1].JudgementClickCheck() == TRUE && map_move_commu_check == TRUE) {}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				// �}�b�v���ړ�����
				#pragma region ver0.0053���쎞�R�����g���R�[�h
				//if (ClickFlagCheckF(ClickX, ClickY, map_arrow_left_x, screen_size_y / 2.0f, (float)GetDrawStringWidthToHandle("��", 2, map_font_arrow), bairitu * FONT_SIZE_ORIGINAL_COMMU_NAME, FALSE, cfgm_move_left) == TRUE)
				//{
				//	if (map_move_commu_check == FALSE)
				//	{
				//		if (g_map_destination == MAP_DESTINATION_CENTER){ g_map_destination = MAP_DESTINATION_LEFT; }
				//		else if (g_map_destination == MAP_DESTINATION_RIGHT){ g_map_destination = MAP_DESTINATION_CENTER; }
				//	}
				//}
				//else if (ClickFlagCheckF(ClickX, ClickY, map_arrow_right_x, screen_size_y / 2.0f, (float)GetDrawStringWidthToHandle("��", 2, map_font_arrow), bairitu * FONT_SIZE_ORIGINAL_COMMU_NAME, FALSE, cfgm_move_right) == TRUE)
				//{ 
				//	if (map_move_commu_check == FALSE)
				//	{
				//		if (g_map_destination == MAP_DESTINATION_CENTER){ g_map_destination = MAP_DESTINATION_RIGHT; }
				//		else if (g_map_destination == MAP_DESTINATION_LEFT){ g_map_destination = MAP_DESTINATION_CENTER; }
				//	}
				//}
#pragma endregion
				if (hjimage_map[0].JudgementReleaseCheck() == TRUE)
				{
					if (map_move_commu_check == FALSE)
					{
						if (g_map_destination == MAP_DESTINATION_CENTER){ g_map_destination = MAP_DESTINATION_LEFT; }
						else if (g_map_destination == MAP_DESTINATION_RIGHT){ g_map_destination = MAP_DESTINATION_CENTER; }
					}
				}
				else if (hjimage_map[1].JudgementReleaseCheck() == TRUE)
				{
					if (map_move_commu_check == FALSE)
					{
						if (g_map_destination == MAP_DESTINATION_CENTER){ g_map_destination = MAP_DESTINATION_RIGHT; }
						else if (g_map_destination == MAP_DESTINATION_LEFT){ g_map_destination = MAP_DESTINATION_CENTER; }
					}
				}
				else if (hjimage_map[2].JudgementReleaseCheck() == TRUE) 
				{ 
					GameSaveLoadNext(TRUE, SL_BEFORE_MAP); 
					SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
				}
				else if (hjimage_map[3].JudgementReleaseCheck() == TRUE) 
				{ 
					GameSaveLoadNext(FALSE, SL_BEFORE_MAP);
					SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
				}
				#pragma region ver0.0038���쎞�R�����g���R�[�h
				// �R�~���ړ��m�F��Ԃɂ���
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x, draw_map_character_icon_y, size_ui_map_icon.x, size_ui_map_icon.y, FALSE, cfgm_commu_check) == TRUE){ map_move_commu_check = TRUE; }
				// �I�������R�~�����{������
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[0], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, FALSE, cfgm_commu_check_ok) == TRUE){ GameMainCommunicationNext(2); }
#pragma endregion
				// �R�~���ړ��m�F��Ԃɂ���
				else if (GameMapControlCommuCheck(FALSE)) {}
				// �I�������R�~�����{������
				else if (image_icon_check[0].JudgementReleaseCheck() == TRUE && map_move_commu_check == TRUE)
				#pragma region ver0.0081���쎞�R�����g���R�[�h
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[0], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, FALSE, cfgm_commu_check_ok) == TRUE)
#pragma endregion
				{
					// �i�f�o�b�O�F�R�~�������݂��ĂȂ������狭���I��������j
					if (commu_data_map[0].id == 0) { quit_game = TRUE; }
					#pragma region ver0.00607���쎞�R�����g���R�[�h
					//else { GameMainCommunicationNext(commu_data_map_choice.id - 1, FALSE); }
#pragma endregion
					else 
					{ 
						SEPlay(static_cast<int>(SEData::IDName::COMMU_START));	// �r�d��炷
						SEData::SetCommuStartTime();
						GameMainCommunicationNext(commu_data_map_choice.id - 1, FALSE, 0);
					}

					commu_look_count[commu_data_map_choice.character_icon - 1]++;	// �L�����ʃR�~�������񐔂��J�E���g����
				}
				// �R�~���ړ��m�F��ʂ�����
				#pragma region ver0.0081���쎞�R�����g���R�[�h
				//else if (ClickFlagCheckF(ClickX, ClickY, draw_map_commu_choice_x[1], draw_map_commu_choice_y, size_ui_map_check_choice.x * bairitu, size_ui_map_check_choice.y * bairitu, FALSE, cfgm_commu_check_no) == TRUE){ map_move_commu_check = FALSE; }
#pragma endregion
				else if (image_icon_check[1].JudgementReleaseCheck() == TRUE && map_move_commu_check == TRUE) { map_move_commu_check = FALSE; }
				// �S�Ẵt���O��߂�
				#pragma region ver0.0053���쎞�R�����g���R�[�h
				//cfgm_move_left = FALSE;														// ���}�b�v�ֈړ�
				//cfgm_move_right = FALSE;													// �E�}�b�v�ֈړ�
#pragma endregion
				for (int i = 0; i < HIT_JUDGEMENT_IMAGE_NUMBER_MAP; i++) { hjimage_map[i].CJChange(FALSE); }
				#pragma region ver0.0038���쎞�R�����g���R�[�h
				//cfgm_commu_check = FALSE;		// �I���R�~���{����ʂ�\������
#pragma endregion
				for (int i = 0; i < COMMU_MAP_LIMIT; i++) { cfgm_commu_check[i] = FALSE; }	// �I���R�~���{����ʂ�\������
				cfgm_commu_check_ok = FALSE;												// �I���R�~���ֈڍs����
				cfgm_commu_check_no = FALSE;												// �I���R�~���{����ʂ���������
				for (int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++) { image_icon_check[i].CJChange(FALSE); }
			}
		}
	}
}
// �}�b�v���[�h���P�t���[�����ɍs���鏈��
void GameMapFlame()
{
	// tips�������X���W�𓮂���
	for (int i = 0; i < 2; i++)
	{ 
		#pragma region ver0.021���쎞�R�����g���R�[�h
		//if (i == 0 || tips_string[0].x < screen_size_x - GetDrawFormatStringWidthToHandle(g_font_tips, tips_string[0].string) - bairitu * 256){ tips_string[i].x -= 3; }
#pragma endregion
		if (i == 0 || tips_string[0].x < screen_size_x - GetDrawFormatStringWidthToHandle(g_font_tips, tips_string[0].string) - bairitu * 256) { tips_string[i].x -= 2; }
	}
	// tips������[0]�����ʒu�܂ŗ�����GameMapTipsSubstitution�֐����Ăяo��
	if (tips_string[0].x < screen_size_x - GetDrawFormatStringWidthToHandle(g_font_tips, tips_string[0].string) - screen_size_x * 2 / 3){ GameMapTipsSubstitution(); }

	float s = bairitu * 120;	// �ړ����x���[�J���ϐ�
	// �s���߂������W���C������i�ړI�n���j
	if (g_map_destination == MAP_DESTINATION_CENTER && draw_map_plus_x >= (-s) && draw_map_plus_x <= s){ draw_map_plus_x = 0; }
	// �^�[�Q�b�g�̃}�b�v��draw_map_plus_x�̒l�ɉ�����draw_map_plus_x�ɐ��l���������A���W���Ē�`����
	if ((g_map_destination == MAP_DESTINATION_LEFT && draw_map_plus_x < size_ui_map.x * bairitu + draw_map_space) || (g_map_destination == MAP_DESTINATION_CENTER && draw_map_plus_x < 0)){ draw_map_plus_x += s; }
	if ((g_map_destination == MAP_DESTINATION_RIGHT && draw_map_plus_x > (size_ui_map.x * bairitu + draw_map_space) * (-1)) || (g_map_destination == MAP_DESTINATION_CENTER && draw_map_plus_x > 0)){ draw_map_plus_x -= s; }
	// �s���߂������W���C������i�ړI�n���E�j
	if (g_map_destination == MAP_DESTINATION_LEFT && draw_map_plus_x > size_ui_map.x * bairitu + draw_map_space){ draw_map_plus_x = size_ui_map.x * bairitu + draw_map_space; }
	if (g_map_destination == MAP_DESTINATION_RIGHT && draw_map_plus_x < (size_ui_map.x * bairitu + draw_map_space) * (-1)){ draw_map_plus_x = (size_ui_map.x * bairitu + draw_map_space) * (-1); }
	// draw_map_plus_x�ɂ���ĕω�������W���Ē�`����
	#pragma region ver0.0038���쎞�R�����g���R�[�h
	//draw_map_character_icon_x = screen_size_x / 2 - size_ui_map_icon.x * bairitu / 2 + draw_map_plus_x + (commu_data_map[0].map_zone - 2) * (size_ui_map.x * bairitu + draw_map_space) + commu_data_map[0].map_coordinate_x;	// �L�����A�C�R��x���W�n�_
	//draw_map_character_icon_y = screen_size_y / 2 - size_ui_map_icon.y * bairitu / 2 + commu_data_map[0].map_coordinate_y;																										// �L�����A�C�R��y���W�n�_
#pragma endregion
	for (int i = 0; i < COMMU_MAP_LIMIT; i++)
	{
		if (commu_data_map[i].id != 0)
		{
			draw_map_character_icon_x[i] =		screen_size_x / 2 - size_ui_map_icon2.x * bairitu / 2 + draw_map_plus_x + (commu_data_map[i].map_zone - 2) * (size_ui_map.x * bairitu + draw_map_space) + commu_data_map[i].map_coordinate_x + bairitu * 82;				// �L�����A�C�R��x���W�n�_
			draw_map_character_icon_y[i] = screen_size_y / 2 - size_ui_map_icon2.y * bairitu / 2 + commu_data_map[i].map_coordinate_y - bairitu * 45;																												// �L�����A�C�R��y���W�n�_
			#pragma region ver0.0081���쎞�R�����g���R�[�h
			//draw_map_coordinate_hukidasi_x[i] = screen_size_x / 2 - size_ui_map_hukidasi[0].x * bairitu / 2 + draw_map_plus_x + (commu_data_map[i].map_zone - 2) * (size_ui_map.x * bairitu + draw_map_space) + commu_data_map[i].map_coordinate_x + bairitu * 82;	// �����o��x���W�n�_
			//draw_map_coordinate_hukidasi_y[i] = screen_size_y / 2 - size_ui_map_hukidasi[0].y * bairitu * 2 / 5 + commu_data_map[i].map_coordinate_y - bairitu * 45;																									// �����o��y���W�n�_
#pragma endregion
			// 
			const float X = (commu_data_map[i].id == static_cast<int>(CommuType::FRIEND) + 1 ? image_icon_map_character[static_cast<int>(CommuData::MapUpperType::FRIEND_CG_MEGURU) - 5].GetSizeX() / 2 : image_icon_map_character[0].GetSizeX() / 2);

			draw_map_coordinate_hukidasi_x[i] = screen_size_x / 2 - X + draw_map_plus_x + (commu_data_map[i].map_zone - 2) * (size_ui_map.x * bairitu + draw_map_space) + commu_data_map[i].map_coordinate_x + bairitu * 82;	// �����o��x���W�n�_
			draw_map_coordinate_hukidasi_y[i] = screen_size_y / 2 - image_icon_map_character[0].GetSizeY() * 2 / 5 + commu_data_map[i].map_coordinate_y - bairitu * 45;																									// �����o��y���W�n�_
		}
	}
	// �}�b�v�ړ����̍��W���i�āj��`����
	float x = screen_size_x * 0.54f;
	float y = bairitu * 705;														// �����̒��S����̂���
	float z = (22.5f - (progress_frame % 45)) * bairitu;
	hjimage_map[0].CoordinateSetting(x - y - hjimage_map[0].size_x / 2 - abs(z), screen_size_y / 2.0f);
	hjimage_map[1].CoordinateSetting(x + y - hjimage_map[1].size_x / 2 + abs(z), screen_size_y / 2.0f);
}
// tips������f�[�^��������
void GameMapTipsSubstitution()
{
	// [1]�̃f�[�^��[0]�ɑ������
	tips_string[0].string = tips_string[1].string;
	tips_string[0].x = tips_string[1].x;
	// ���݂���S�Ă�tips�̒�����܂��o�����Ă��Ȃ����̂𒲂ׂ�i�S�ďo���ς݂̏ꍇ�̓t���O�����Z�b�g���A[0]�̎��̂h�c�̂��̂�[1]�ɑ��������H�j
	for (int j = (tips_string[0].string == NULL ? 0 : 1); j < 2; j++)
	{
		int x = 0;	// ���o��tips�J�E���g�p�ϐ�
		#pragma region ver0.00706���쎞�R�����g���R�[�h
		//int y[TIPS_NUMBER];
		//char* c[TIPS_NUMBER];
#pragma endregion
		#pragma region ver0.00708���쎞�R�����g���R�[�h
		//int y[TIPS_NUMBER] = {0, 0, 0};
		//char* c[TIPS_NUMBER] = {};
		//do
		//{
		//	for (int i = 0; i < TIPS_NUMBER; i++)
		//	{
		//		if (tips_data[i].appear == FALSE)
		//		{
		//			c[x] = tips_data[i].tips;
		//			y[x] = tips_data[i].id;
		//			x++;
		//		}
		//	}
		//	if (x == 0)
		//	{
		//		for (int i = 0; i < TIPS_NUMBER; i++){ tips_data[i].appear = FALSE; }
		//	}
		//} while (x == 0);	// x��0�̌��胋�[�v
#pragma endregion
		int y[TipsData::LOAD_LIMIT];
		char* c[TipsData::LOAD_LIMIT];
		//int y[3];
		//char* c[3];
		do
		{
			for (int i = 0; i < TipsData::GetNumber(); i++)
			{
				if (tips_data[i].appear == FALSE)
				{
					c[x] = tips_data[i].tips;
					y[x] = tips_data[i].id;
					x++;
				}
			}
			if (x == 0)
			{
				for (int i = 0; i < TipsData::GetNumber(); i++) { tips_data[i].appear = FALSE; }
			}
		} while (x == 0);	// x��0�̌��胋�[�v
		// �o�����Ă��Ȃ����̂��烉���_���ɂP�I�сA�����ʒu�܂߂�����[1]�i����Ȃ�[0]�j�ɑ������
		//�i�P���̏I���ƂQ���̍ŏ��Ŕ��\��������̂ŁA[1]��I�ԍہA[0]�Ɣ�������蒼���A�Ƃ�������������Ă��������j
		int z = GetRand(x - 1);	// �����p�ϐ�
		tips_string[j].string = c[z];

		tips_string[j].x = (float)screen_size_x;
		// �iy�̒l��Minus�ɂȂ�s����N���Ă���j
		tips_data[y[z]].appear = TRUE;
	}
}
// �}�b�v��ʂŎg���l�X�ȍ��W���i�āj��`����
void GameMapCoordinateSetting()
{
	// �t�H���g����`����
	map_font_arrow = g_font_commu_name;	// �}�b�v��ʖ��̃t�H���g�T�C�Y

	#pragma region ver0.0051���쎞�R�����g���R�[�h
	//float x = screen_size_x / 2.0f;
	//float y = bairitu * 600;														// �����̒��S����̂���
	//map_arrow_left_x = x - y - GetDrawStringWidthToHandle("��", 2, g_font3);		// �����ɍs������x���W�l
#pragma endregion

	draw_map_space = bairitu * 360;													// �e�}�b�v�Ԃ̌���
	// �R�~���ړ��I����x���W�n�_
	float z = size_ui_map_check_choice.x * bairitu / 2 + 90;	// ���I�����ň����鐔�l�̃��[�J���ϐ�
	draw_map_commu_choice_x[0] = (screen_size_x - size_ui_map_check_choice.x * bairitu) / 2 - z;
	draw_map_commu_choice_x[1] = (screen_size_x - size_ui_map_check_choice.x * bairitu) / 2 + z;

	draw_map_commu_choice_y = (screen_size_y + size_ui_map_check.y * bairitu) / 2 - size_ui_map_check_choice.y * bairitu - 120;	// �R�~���ړ��I����y���W�n�_�i�������j
	// �Z�[�u�A���[�h�A�C�R��
	float x = 24 * bairitu;
	hjimage_map[2].CoordinateSetting(x, screen_size_y - hjimage_map[2].GetSizeY() * 4);
	hjimage_map[3].CoordinateSetting(x, screen_size_y - hjimage_map[3].GetSizeY() * 2);
	// �R�~���ړ��I����
	for (int i = 0; i < 2; i++)
	{
		image_icon_map_move_alternative[i].CoordinateSetting2(
			image_icon_map_move_alternative[i].GetOriginalSizeX() * (i - 1) + 19 * (i == 0 ? 1 : -1) + 1034.0f,
			675.0f);
	}
	// �R�~���ړ��m�F�����̑I�����́w�������x�����蔻��p
	image_icon_map_collision_detection.CoordinateSetting2(
	1008, 861.0f - image_icon_map_collision_detection.GetOriginalSizeY());
}
// �}�b�v���[�h���`�揈��
void DrawGameMap()
{
	// �}�b�v�w�i
	image_map_background.DrawImage();
	// �}�b�v
	DrawExtendGraphF(screen_size_x / 2 - size_ui_map.x * bairitu * 1.5f - draw_map_space + draw_map_plus_x, screen_size_y / 2 - size_ui_map.y * bairitu / 2, (screen_size_x - size_ui_map.x * bairitu) / 2 - draw_map_space + draw_map_plus_x, (screen_size_y + size_ui_map.y * bairitu) / 2, g_imghandles.ui_map[0], TRUE);
	DrawExtendGraphF(screen_size_x / 2 - size_ui_map.x * bairitu / 2 + draw_map_plus_x, screen_size_y / 2 - size_ui_map.y * bairitu / 2, (screen_size_x + size_ui_map.x * bairitu) / 2 + draw_map_plus_x, (screen_size_y + size_ui_map.y * bairitu) / 2, g_imghandles.ui_map[1], TRUE);
	DrawExtendGraphF(screen_size_x / 2 + size_ui_map.x * bairitu / 2 + draw_map_space + draw_map_plus_x, screen_size_y / 2 - size_ui_map.y * bairitu / 2, screen_size_x / 2 + size_ui_map.x * bairitu * 1.5f + draw_map_space + draw_map_plus_x, (screen_size_y + size_ui_map.y * bairitu) / 2, g_imghandles.ui_map[2], TRUE);
	// �L�����A�C�R��
	for (int i = 0; i < COMMU_MAP_LIMIT; i++)
	{
		if (commu_data_map[i].id != 0)
		{
			// �����o���i���݂͂P�l�p�ŌŒ�A��X�R�~���ɉ������傫���̃A�C�R���ɕω�������K�v������j
			#pragma region ver0.0081���쎞�R�����g���R�[�h
//			DrawExtendGraphF(draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i],draw_map_coordinate_hukidasi_x[i] + size_ui_map_hukidasi[0].x * bairitu, draw_map_coordinate_hukidasi_y[i] + size_ui_map_hukidasi[0].y * bairitu, g_imghandles.ui_map_hukidasi[0], TRUE);
//			#pragma region ver0.0042���쎞�R�����g���R�[�h
//			//DrawExtendGraphF(draw_map_character_icon_x[i], draw_map_character_icon_y[i], draw_map_character_icon_x[i] + size_ui_map_icon.x * bairitu, draw_map_character_icon_y[i] + size_ui_map_icon.y * bairitu, g_imghandles.ui_map_icon[commu_data_map[i].character_icon - 1], TRUE);
//#pragma endregion
//			DrawExtendGraphF(draw_map_character_icon_x[i], draw_map_character_icon_y[i],draw_map_character_icon_x[i] + size_ui_map_icon2.x * bairitu, draw_map_character_icon_y[i] + size_ui_map_icon2.y * bairitu, g_imghandles.ui_map_icon[commu_data_map[i].character_icon - 1], TRUE);
#pragma endregion
			#pragma region ver0.0081���쎞�R�����g���R�[�h
			//DrawExtendGraphF(draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], draw_map_coordinate_hukidasi_x[i] + size_ui_map_hukidasi[0].x, draw_map_coordinate_hukidasi_y[i] + size_ui_map_hukidasi[0].y, g_imghandles.ui_map_hukidasi[0], TRUE);
			//DrawExtendGraphF(draw_map_character_icon_x[i], draw_map_character_icon_y[i], draw_map_character_icon_x[i] + size_ui_map_icon2.x, draw_map_character_icon_y[i] + size_ui_map_icon2.y, g_imghandles.ui_map_icon[commu_data_map[i].character_icon - 1], TRUE);
#pragma endregion
			#pragma region ver0.00904���쎞�R�����g���R�[�h
			//DrawExtendGraphF(draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], draw_map_coordinate_hukidasi_x[i] + image_icon_map_character[0].GetSizeX(), draw_map_coordinate_hukidasi_y[i] + image_icon_map_character[0].GetSizeY(), image_icon_map_character[commu_data_map[i].character_icon - 1].GetHandle(), TRUE);
#pragma endregion
			DrawExtendGraphF(draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], draw_map_coordinate_hukidasi_x[i] + image_icon_map_character[(commu_data_map[i].GetID() == static_cast<int>(CommuType::FRIEND) + 1) ? static_cast<int>(CommuData::MapUpperType::FRIEND_CG_MEGURU) - 5 : 0].GetSizeX(), draw_map_coordinate_hukidasi_y[i] + image_icon_map_character[0].GetSizeY(), image_icon_map_character[commu_data_map[i].character_icon - 1].GetHandle(), TRUE);
		}
	}

	#pragma region ver0.0039���쎞�R�����g���R�[�h
	//DrawExtendGraphF(screen_size_x - size_ui_tips.x * bairitu, 0, WINDOW_SIZE_X * bairitu, size_ui_tips.y * bairitu, g_imghandles.ui_tips, TRUE);	// tips�t�h

	//// ����e�X�g
	//for (int i = 0; i < 2; i++){ DrawFormatStringFToHandle(tips_string[i].x, 50, GetColor(0, 0, 0), g_font_tips, tips_string[i].string); }

	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.ui_month, TRUE);	// ���t�h
#pragma endregion
	DrawExtendGraphF(screen_size_x - size_ui_tips.x * bairitu, 0, WINDOW_SIZE_X * bairitu, size_ui_tips.y * bairitu, g_imghandles.ui_tips, TRUE);	// tips�t�h
	#pragma region ver0.00391���쎞�R�����g���R�[�h

	//for (int i = 0; i < 2; i++) { DrawFormatStringFToHandle(tips_string[i].x, 50, GetColor(0, 0, 0), g_font_tips, tips_string[i].string); }

#pragma endregion
	for (int i = 0; i < 2; i++) { DrawFormatStringFToHandle(tips_string[i].x, bairitu * 24, GetColor(0, 0, 0), g_font_tips, tips_string[i].string); }
	#pragma region ver0.00706���쎞�R�����g���R�[�h
	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.ui_month, TRUE);	// ���t�h
#pragma endregion
	// ���݌��t�h
	if (GlobalStaticVariable::GetModeTrial() == FALSE) { ui_map_month[game_week_number - 12].DrawImage(); }
	else { bgimage_non_month.DrawImage(); }
	// ���
	//DrawStringFToHandle(map_arrow_left_x, screen_size_y / 2.0f, "��", DrawTitleStringColor(map_arrow_left_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("��", 2, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
	if (map_move_commu_check == FALSE)
	{
		#pragma region ver0.0038���쎞�R�����g���R�[�h
		//if (g_map_destination != MAP_DESTINATION_LEFT){ DrawStringFToHandle(map_arrow_left_x, screen_size_y / 2.0f, "��", DrawTitleStringColor(map_arrow_left_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("��", 2, map_font_arrow), FONT_SIZE_ORIGINAL_COMMU_NAME * bairitu), map_font_arrow); }
		//if (g_map_destination != MAP_DESTINATION_RIGHT){ DrawStringFToHandle(map_arrow_right_x, screen_size_y / 2.0f, "��", DrawTitleStringColor(map_arrow_right_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("��", 2, map_font_arrow), FONT_SIZE_ORIGINAL_COMMU_NAME * bairitu), map_font_arrow); }
#pragma endregion
		// ���𓮂������߂ɕK�v�Ȑ�ΐ��H
		#pragma region ver0.0051���쎞�R�����g���R�[�h
		//float x = 22.5f - (progress_frame % 45) * bairitu;
#pragma endregion
		#pragma region ver0.0053���쎞�R�����g���R�[�h
		//float x = (22.5f - (progress_frame % 45)) * bairitu;

		//if (g_map_destination != MAP_DESTINATION_LEFT) { DrawStringFToHandle(map_arrow_left_x - abs(x), screen_size_y / 2.0f, "��", DrawTitleStringColor(map_arrow_left_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("��", 2, map_font_arrow), FONT_SIZE_ORIGINAL_COMMU_NAME * bairitu), map_font_arrow); }
		//if (g_map_destination != MAP_DESTINATION_RIGHT) { DrawStringFToHandle(map_arrow_right_x + abs(x), screen_size_y / 2.0f, "��", DrawTitleStringColor(map_arrow_right_x, screen_size_y / 2.0f, GetDrawStringWidthToHandle("��", 2, map_font_arrow), FONT_SIZE_ORIGINAL_COMMU_NAME * bairitu), map_font_arrow); }
#pragma endregion
		if (g_map_destination != MAP_DESTINATION_LEFT) { hjimage_map[0].DrawImage(); }
		if (g_map_destination != MAP_DESTINATION_RIGHT) { hjimage_map[1].DrawImage(); }
	}
	// �R�~���ړ��m�F�t�h
	if (map_move_commu_check == TRUE)
	{ 
		#pragma region ver0.013���쎞�R�����g���R�[�h
		const float X = (screen_size_x - bairitu * size_ui_map_check.x) / 2;
		const float Y = (screen_size_y - bairitu * size_ui_map_check.y) / 2;
		DrawExtendGraphF(X, Y, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, g_imghandles.ui_map_check, TRUE); 
#pragma endregion
		// �e
		//const float Z = bairitu * 495;
		//const float A = bairitu * 270;
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192);
		//DrawFormatStringFToHandle(Z + bairitu * 3, A + bairitu * 3, GetColor(20, 20, 20), font[static_cast<int>(FontData::Type::MAP_TITLE)].GetHandle(), commu_data_map_choice.GetTitle());
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		// �T�u�^�C�g��
		//DrawFormatStringFToHandle(Z, A, GetColor(255, 255, 255), font[static_cast<int>(FontData::Type::MAP_TITLE)].GetHandle(), commu_data_map_choice.GetTitle());

		#pragma region ver0.0042���쎞�R�����g���R�[�h
		//DrawExtendGraphF((screen_size_x - bairitu * size_ui_map_icon.x) / 2, (screen_size_y - bairitu * size_ui_map_icon.y) / 2 - bairitu * 150, (screen_size_x + bairitu * size_ui_map_icon.x) / 2, (screen_size_y + bairitu * size_ui_map_icon.y) / 2 - bairitu * 150, g_imghandles.ui_map_icon[commu_data_map_choice.character_icon - 1], TRUE);	// �A�C�R���i���j
#pragma endregion
		#pragma region ver0.0081���쎞�R�����g���R�[�h
		//DrawExtendGraphF((screen_size_x - bairitu * size_ui_map_icon2.x) / 2, (screen_size_y - bairitu * size_ui_map_icon2.y) / 2 - bairitu * 150, (screen_size_x + bairitu * size_ui_map_icon2.x) / 2, (screen_size_y + bairitu * size_ui_map_icon2.y) / 2 - bairitu * 150, g_imghandles.ui_map_icon[commu_data_map_choice.character_icon - 1], TRUE);	// �A�C�R���i���j
#pragma endregion
		// �t�����h�߂���R�~���̏ꍇ�T�l�̃A�C�R����\��������
		#pragma region ver0.013���쎞�R�����g���R�[�h
		if (commu_data_map_choice.GetID() != static_cast<int>(CommuType::FRIEND) + 1)
		{
			DrawExtendGraphF((screen_size_x - size_ui_map_icon2.x) / 2, (screen_size_y - size_ui_map_icon2.y) / 2 - bairitu * 150, (screen_size_x + size_ui_map_icon2.x) / 2, (screen_size_y + size_ui_map_icon2.y) / 2 - bairitu * 150, g_imghandles.ui_map_icon[commu_data_map_choice.character_icon - 1], TRUE);	// �A�C�R���i���j
		}
		else
		{
			// �T�l�S���̃A�C�R����\��������
			for (int i = 0; i < 5; i++)
			{
				// �A�C�R���̂���
				const float X = (i - 2) * bairitu * 108;

				DrawExtendGraphF((screen_size_x - size_ui_map_icon2.x) / 2 + X,
					(screen_size_y - size_ui_map_icon2.y) / 2 - bairitu * 150,
					(screen_size_x + size_ui_map_icon2.x) / 2 + X, (screen_size_y + size_ui_map_icon2.y) / 2 - bairitu * 150, g_imghandles.ui_map_icon[i], TRUE);	// �A�C�R���i���j
			}
		}
#pragma endregion
		//if (commu_data_map_choice.GetID() != static_cast<int>(CommuType::FRIEND) + 1) { image_map_question[commu_data_map_choice.character_icon - 1].DrawImage(); }
		//else { image_map_question[static_cast<int>(ImgDataMapQuestion::Type::FRIEND_ALL)].DrawImage(); }
		#pragma region ver0.0081���쎞�R�����g���R�[�h
		//for (int i = 0; i < 2; i++){ DrawExtendGraphF(draw_map_commu_choice_x[i], draw_map_commu_choice_y, draw_map_commu_choice_x[i] + size_ui_map_check_choice.x * bairitu, draw_map_commu_choice_y + size_ui_map_check_choice.y * bairitu, g_imghandles.ui_map_check_choice[i], TRUE); }
#pragma endregion
		// �I�����A�C�R��
		for (int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++) { image_icon_check[i].DrawImage(); }
		//for (int i = 0; i < 2; i++) { image_icon_map_move_alternative[i].DrawImage(); }
		// �f�o�b�O�p�����蔻��
		//image_icon_map_collision_detection.DrawImage();
	}
	// �Z�[�u�E���[�h�A�C�R��
	for(int i = 2; i < 4; i++){hjimage_map[i].DrawImage(); }
}
// �Ή�����L�����R�~�����o�����邩�`�F�b�N����
BOOL GameMapUpperCheck(int x, int y)	// �L�����N�^�[,�R�~���h�c
{
	// �t�����h�b�f�R�~��
	//if (game_week_number == 17)
	//{
	//	if (y == COMMU_TYPE_FRIEND) { return TRUE; }
	//}
	//// �ʃR�~��
	//else if (x != 0 && x < 6)
	if (x != 0 && x < 6)
	{
		// �^�C�~���O����ŕ\������R�~��
		switch (CommuData::GetGMapUpperType())
		{
		case CommuData::MapUpperType::MEGURU0:	if (x == 1) { return TRUE; }	break;
		case CommuData::MapUpperType::KOGANE0:	if (x == 2) { return TRUE; }	break;
		case CommuData::MapUpperType::JURI0:	if (x == 3) { return TRUE; }	break;
		case CommuData::MapUpperType::RINZE0:	if (x == 4) { return TRUE; }	break;
		case CommuData::MapUpperType::CHIYUKI0:	if (x == 5) { return TRUE; }	break;
		case CommuData::MapUpperType::FRIEND_CG_MEGURU:							break;
		default:								return TRUE;					break;
		}
	}
	return FALSE;
}
// �}�b�v�A�C�R���N���b�N�m�F�p�֐�
BOOL GameMapControlCommuCheck(BOOL x)	// �����^�C�~���O�iTRUE�Ȃ牟�������j
{
	if (map_move_commu_check == FALSE)
	{
		for (int i = 0; i < COMMU_MAP_LIMIT; i++)
		{
			const int Y = (commu_data_map[i].GetID() == static_cast<int>(CommuType::FRIEND) + 1) ? static_cast<int>(CommuData::MapUpperType::FRIEND_CG_MEGURU) - 5 : 0;
			if (x == TRUE)
			{
				#pragma region ver0.0081���쎞�R�����g���R�[�h
				//if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x[i], draw_map_character_icon_y[i], size_ui_map_icon2.x * bairitu, size_ui_map_icon2.y * bairitu, TRUE, FALSE) == TRUE)
#pragma endregion
				#pragma region ver0.00904���쎞�R�����g���R�[�h
//if (ClickFlagCheckF(ClickX, ClickY, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], image_icon_map_character[0].GetSizeX(), image_icon_map_character[0].GetSizeY(), TRUE, FALSE) == TRUE)
#pragma endregion
				if (ClickFlagCheckF(ClickX, ClickY, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], image_icon_map_character[Y].GetSizeX(), image_icon_map_character[0].GetSizeY(), TRUE, FALSE) == TRUE)
				{
					cfgm_commu_check[i] = TRUE;
					return TRUE;
				}
			}
			else
			{
				#pragma region ver0.00393���쎞�R�����g���R�[�h
				//if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x[i], draw_map_character_icon_y[i], size_ui_map_icon.x, size_ui_map_icon.y, FALSE, cfgm_commu_check[i]) == TRUE)
#pragma endregion
				#pragma region ver0.0081���쎞�R�����g���R�[�h
//if (ClickFlagCheckF(ClickX, ClickY, draw_map_character_icon_x[i], draw_map_character_icon_y[i], size_ui_map_icon2.x, size_ui_map_icon2.y, FALSE, cfgm_commu_check[i]) == TRUE && map_move_commu_check == FALSE)
#pragma endregion
				#pragma region ver0.00904���쎞�R�����g���R�[�h
//if (ClickFlagCheckF(ClickX, ClickY, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], image_icon_map_character[0].GetSizeX(), image_icon_map_character[0].GetSizeY(), FALSE, cfgm_commu_check[i]) == TRUE && map_move_commu_check == FALSE)
#pragma endregion
				if (ClickFlagCheckF(ClickX, ClickY, draw_map_coordinate_hukidasi_x[i], draw_map_coordinate_hukidasi_y[i], image_icon_map_character[Y].GetSizeX(), image_icon_map_character[0].GetSizeY(), FALSE, cfgm_commu_check[i]) == TRUE && map_move_commu_check == FALSE)
				{
					map_move_commu_check = TRUE;
					// �I��p�R�~���X�e�[�^�X�ɕK�v�ȗv�f��������
					commu_data_map_choice.id = commu_data_map[i].id;
					commu_data_map_choice.SetTitle(commu_data_map[i].GetTitle());
					commu_data_map_choice.character_icon = commu_data_map[i].character_icon;
					// �r�d��炷
					SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE));

					return TRUE;
				}
			}
		}
	}
	return FALSE;
}
