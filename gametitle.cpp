#include "gametitle.h"
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icft=click_flag_title�j
// �Ȃ���saveload�t�@�C���̃R�[�h�Ɏg���Ă����̂ł��̂܂�
BOOL cft_exit_main_commu = FALSE;		// �R�~����ʂɈړ�
BOOL cft_quit_game = FALSE;				// �Q�[�����I��
BOOL cft_sound_room_main_commu = FALSE;	// �T�E���h���[����ʂɈړ�
BOOL cft_commu_list = FALSE;				// �R�~�����X�g��ʂɈړ�
//BOOL cft_commu_edit = FALSE;			// �R�~���G�f�B�b�g��ʂɈړ�

BOOL flag_next_start = FALSE;	// �j���[�Q�[���J�n���̈ړ������t���O

int next_start_frame_count = -1;	// �wSTART�x�I������̌o�߃t���[����

float coordinat_title_choice_left = 0;		// �����I�����n�_x���W
float coordinat_title_choice_right = 0;		// �E���I�����n�_x���W
float coordinat_title_choice_load_y = 0;	// �I�����wLOAD�xy���W
float coordinat_title_choice_config_y = 0;	// �I�����wCONFIG�xy���W
float coordinat_title_choice_exit_y = 0;	// �I�����wEXIT�xy���W

// �^�C�g����ʏ�Ԉȍ~����
void GameTitleNext()
{
	g_gamestate = GAME_TITLE;
	if (ImgDataHJTitle::GetCountFrame() > 0) { MusicPlay(BN_TITLE); }	// �^�C�g���a�f�l���Đ�����
	SEPlay(-2);															// ���[�v���ʉ����~����
	flag_next_start = FALSE;											// �j���[�Q�[���I�����t���O�����Z�b�g����
	next_start_frame_count = -1;										// �wSTART�x�I������̌o�߃t���[���������Z�b�g����
}
// GameTitle��Ԃ̃��C������
void GameTitle()
{
	GameTitleControl();
	GameTitleFlame();
	DrawGameTitle();
}
// �^�C�g����ʑ��쏈��
void GameTitleControl()
{
	// �}�E�X�̃{�^���������ꂽ�藣���ꂽ�肵�����ǂ����̏����擾����
	if (GetMouseInputLog2(&Button, &ClickX, &ClickY, &LogType, TRUE) == 0 && flag_next_start == FALSE)
	{
		// ���{�^����������Ă�����
		if ((Button & MOUSE_INPUT_LEFT) != 0)
		{
			if (LogType == MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::START)][0].JudgementClickCheck() == TRUE) {}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::EXIT)][0].JudgementClickCheck() == TRUE && mode_debug == TRUE) {}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::LOAD)][0].JudgementClickCheck() == TRUE && mode_debug == TRUE) {}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::OPTION)][0].JudgementClickCheck() == TRUE && mode_debug == TRUE) {}
				else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, START_MESSEAGE_Y * bairitu, (float)GetDrawStringWidthToHandle("SOUNDROOM", 9, g_font3), FONT_SIZE_ORIGINAL * bairitu, TRUE, FALSE) == TRUE) { cft_sound_room_main_commu = TRUE; }
				else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, coordinat_title_choice_load_y, size_icon_commu_list.x, size_icon_commu_list.y, TRUE, FALSE) == TRUE) { cft_commu_list = TRUE; }
				//else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, coordinat_title_choice_config_y, size_icon_commu_list.x, size_icon_commu_list.y, TRUE, FALSE) == TRUE) { cft_commu_edit = TRUE; }	// �摜�����R�~�����X�g�̂��̂��g���Ă���
				else if (hjimage_title.JudgementClickCheck() == TRUE) {}	// �摜�����R�~�����X�g�̂��̂��g���Ă���
				else { ImgDataHJTitle::SetFlagCount(TRUE); }
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�

				// �R�~����ʂֈړ�
				if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::START)][0].JudgementReleaseCheck() == TRUE)
				{
					flag_next_start = TRUE;															// �j���[�Q�[��������Ԃ̃t���O�𗧂Ă�
					SEPlay(static_cast<int>(SEData::IDName::START));
					MusicPlay(-1);																	// �a�f�l��~�^�C�~���O�e�X�g
					for (int i = 0; i < COMMU_CHARACTER_NUMBER; i++) { commu_look_count[i] = 0; }	// �L�����ʃR�~���{���񐔂����Z�b�g����
					CommuData::SetGMapUpperType(CommuData::MapUpperType::DEFAULT);	//	����R�~���\���^�C�~���O������
					// �J�����_�[������
					game_week_number = GlobalStaticMap::GetWeekInitialValue();
				}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::EXIT)][0].JudgementReleaseCheck() == TRUE) { quit_game = TRUE; }
				// ���[�h��ʂֈړ�
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::LOAD)][0].JudgementReleaseCheck() == TRUE)
				{
					GameSaveLoadNext(FALSE, SL_BEFORE_TITLE);
					SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE));
				}
				else if (image_title_menu[static_cast<int>(ImgDataHJTitle::TYPE::OPTION)][0].JudgementReleaseCheck() == TRUE)
				{
					GameConfigNext(FALSE);
					SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE));
				}
				// �T�E���h���[���ֈړ�
				else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, START_MESSEAGE_Y * bairitu, (float)GetDrawStringWidthToHandle("SOUNDROOM", 9, g_font3), FONT_SIZE_ORIGINAL * bairitu, FALSE, cft_sound_room_main_commu) == TRUE && mode_debug == TRUE){ g_gamestate = GAME_SOUNDROOM; }
				// �R�~�����X�g�ֈړ�
				else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, coordinat_title_choice_load_y, size_icon_commu_list.x, size_icon_commu_list.y, FALSE, cft_commu_list) == TRUE && mode_debug == TRUE)
				{ 
					GameCommuSelectNext();
					// �����G�ǂݍ���
					for (int i = 0; i < COMMU_SELECT_CHARACTER_NUMBER; i++) { image_character[i][0][0].SetLoadFlag(1); }
					CharacterImage::Load();
				}
				// �R�~���G�f�B�b�g���[�h�ֈړ�
				//else if (ClickFlagCheckF(ClickX, ClickY, coordinat_title_choice_right, coordinat_title_choice_config_y, size_icon_commu_list.x, size_icon_commu_list.y, FALSE, cft_commu_edit) == TRUE) { g_gamestate = GAME_COMMU_EDIT; }	// �摜�����R�~�����X�g�̂��̂��g���Ă���
				else if (hjimage_title.JudgementReleaseCheck() == TRUE && mode_debug == TRUE)	// �摜�����R�~�����X�g�̂��̂��g���Ă���
				{ 
					g_gamestate = GAME_COMMU_EDIT; 
					MusicPlay(-1);	// �a�f�l��~
					// �����G��ǂݍ���
					CharacterImage::SetFlagAll(TRUE);
					CharacterImage::Load();
					// �a�f�l��ǂݍ���
					BGMData::SetLoadAll(TRUE);
					BGMData::Load();
				}
				else if (ImgDataHJTitle::GetFlagCount() == TRUE)
				{
					if(ImgDataHJTitle::GetCountFrame() < 9999){ImgDataHJTitle::SetCountFrame(9999);}
					SEPlay(-2);	// ���[�v���ʉ����~����
				}
				// �S�Ẵt���O��߂�
				cft_commu_list = FALSE;					// �R�~�����X�g��ʂɈړ�����
				//cft_commu_edit = FALSE;			// �R�~���G�f�B�b�g��ʂɈړ�
				ImgDataHJTitle::SetFlagCount(FALSE);	// �^�C�g����ʌo�߃t���[�����𑦍ő�ɂ���
				// �e�I����
				for (int i = 0; i < ImgDataHJTitle::GetMenuNumber(); i++) { image_title_menu[i][0].CJChange(FALSE); }
					
				hjimage_title.CJChange(FALSE);	// �R�~���G�f�B�b�g��ʂɈړ�
			}
		}
	}
	/* �}�E�X�z�C�[���֌W ---------*/
	//if (MouseX >= MAIN_MENU_X && MouseX < WINDOW_SIZE_X - MAIN_BUILDING_SIZE_X - DIVIDE_X)
	//{
	//	draw_status_plus_y += GetMouseWheelRotVol() * 15;
	//	if (draw_status_plus_y > 0){ draw_status_plus_y = 0; }
	//}
	//// �E���
	//else if (MouseX >= WINDOW_SIZE_X - MAIN_BUILDING_SIZE_X && draw_window_right_length > WINDOW_SIZE_Y)
	//{
	//	draw_wr_plus_y += GetMouseWheelRotVol() * 15;
	//	if (draw_wr_plus_y > 0){ draw_wr_plus_y = 0; }
	//	else if (draw_wr_plus_y < WINDOW_SIZE_Y - draw_window_right_length){ draw_wr_plus_y = WINDOW_SIZE_Y - draw_window_right_length; }
	//}
	/* �G�f�B�b�g���[�h�L�����ʓǂݍ��݃t���O�؂�ւ� ---------*/
	if (mode_debug == TRUE)
	{
		if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)
		{
			for (int i = 0; i < CharacterImage::GetCharacterMember(); i++)
			{
				if (CheckHitKey(KEY_INPUT_1 + i) == TRUE){CharacterImage::SetLoadEdit(i, TRUE);}
			}
		}
		else if (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE)
		{
			for (int i = 0; i < CharacterImage::GetCharacterMember(); i++)
			{
				if (CheckHitKey(KEY_INPUT_1 + i) == TRUE) { CharacterImage::SetLoadEdit(i, FALSE); }
			}
		}
	}
}
// �^�C�g�����[�h���P�t���[�����ɍs���鏈��
void GameTitleFlame()
{
	// �j���[�Q�[���������Ȃ�J�E���g���s���A�K��l�ȏ�ɂȂ�����R�~�����[�h�ɂ���
	if (flag_next_start == TRUE)
	{
		next_start_frame_count++;
		if (next_start_frame_count >= TITLE_MOVE_START_MAX_FLAME)
		{
			// �̌��ł̃I���I�t�ōŏ��̃R�~�����e���ς��
			if (GlobalStaticVariable::GetModeTrial() == FALSE) { GameMainCommunicationNext(0, FALSE, 0); }
			else
			{
				GlobalStaticMap::TrialCommuViewedReset();
				GameMainCommunicationNext(static_cast<int>(CommuType::STILL_OP), FALSE, 0);
			}
			
			commu_play_time = 0;	// �v���C���Ԃ�������
		}
	}
}
// �^�C�g����ʂŎg���l�X�ȍ��W���i�āj��`����
void GameTitleCoordinateSetting()
{
	coordinat_title_choice_left = bairitu * TITLE_MENU_MESSAGE_X;
	coordinat_title_choice_right = screen_size_x - TITLE_MENU_MESSAGE_X * bairitu - GetDrawStringWidthToHandle("SOUNDROOM", 9, g_font3);	// �E���I�����n�_x���W
	coordinat_title_choice_load_y = bairitu * (START_MESSEAGE_Y + TITLE_MENU_MESSAGE_SPACE_Y);												// �I�����wLOAD�xy���W
	coordinat_title_choice_config_y = coordinat_title_choice_load_y + bairitu * TITLE_MENU_MESSAGE_SPACE_Y;									// �I�����wCONFIG�xy���W
	coordinat_title_choice_exit_y = coordinat_title_choice_config_y + bairitu * TITLE_MENU_MESSAGE_SPACE_Y;									// �I�����wEXIT�xy���W
	hjimage_title.CoordinateSetting(screen_size_x - hjimage_title.GetSizeX(), coordinat_title_choice_load_y);											// �w�wCommu Edit�x�x��x�Ay���W
	// �^�C�g�����S��X���W
	image_title_logo.CoordinateSetting(screen_size_x - image_title_logo.GetSizeX(), 0);	
}
// �^�C�g����ʂ̕`�揈��
void DrawGameTitle()
{
	// �֘A�摜
	ImgDataHJTitle::DrawTitleImage();
	if (mode_debug == TRUE)
	{
		// �T�E���h�e�X�g�i�f�o�b�O�j
		DrawStringFToHandle(coordinat_title_choice_right, START_MESSEAGE_Y * bairitu, "SOUNDROOM", DrawTitleStringColor(coordinat_title_choice_right, START_MESSEAGE_Y * bairitu, GetDrawStringWidthToHandle("SOUNDROOM", 9, g_font3), FONT_SIZE_ORIGINAL * bairitu), g_font3);
		// �R�~�����X�g�i���݂̓f�o�b�O�p�r�j
		DrawExtendGraphF(coordinat_title_choice_right, coordinat_title_choice_load_y, coordinat_title_choice_right + size_icon_commu_list.x, coordinat_title_choice_load_y + size_icon_commu_list.y, g_imghandles.commu_list, TRUE);
		// �R�~���G�f�B�b�g�i�f�o�b�O�A�E�����W���R�~�����X�g�̂܂܂ɂ��Ă���̂Ńo�O���N���邩������Ȃ��j
		hjimage_title.DrawImage();
	}
	// �j���[�Q�[�����̔��w�i
	if (flag_next_start == TRUE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, next_start_frame_count * 255 / TITLE_MOVE_START_MAX_FLAME);
		DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(255, 255, 255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
// �^�C�g�����j���[�̕����F��Ԃ�
int DrawTitleStringColor(float x, float y, int breadth, float length)	// �n�_x���W,�n�_y���W,�����͈�,�c���͈�
{
	int color = MouseX >= x && MouseX < x + breadth && MouseY >= y && MouseY < y + length ? GetColor(255, 255, 255) : GetColor(128, 128, 128);
	return color;
}
