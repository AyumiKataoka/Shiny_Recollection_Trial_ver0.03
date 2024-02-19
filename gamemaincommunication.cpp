#include "gamemaincommunication.h"
CommuStatusType g_commustatus;
AltenativeNumberType g_altenativenumber;			// �\���I�����̎�ށi���j
CommuAutoType g_commuauto;							// �R�~�������i�s��Ԃ̎��
CommuCharacterFaceType g_commu_character_face[3];	// �`�悳���L�����̓���\��^�C�v

float AlternativeCoordinate::y_upper = 0;
float AlternativeCoordinate::y_under = 0;
/* TextLog�N���X ---------*/
BOOL TextLog::mode = FALSE;
int TextLog::top_id_now = 0;
int TextLog::next_input_id = 0;
int TextLog::page = 1;
const int TextLog::PAGES_LINE_NUMBER = 4;
TextLog text_log[COMMU_LINE_MAX];
// �e�L�X�g���O��������
void TextLog::Input()
{
	// �i�I������ʂ�������X�L�b�v���鏈���j

	// �䎌���O������������X�L�b�v����
	if (std::strcmp(HM[commu_number][cell_number].GetLine(), "") != 0)
	{
		sprintf_s(line, 128, HM[commu_number][cell_number].GetLine());
		// �䎌��i���݂̓L�����T���l��\�����邽�߂����Ȃ̂Œ��_������K�v�͂Ȃ��j
		sprintf_s(character, 32, "%s%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name, HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2);

		line_number = cell_number;	// �R�~�����ł̍s
		next_input_id++;
	}
}
// �`�悷��
void TextLog::Draw()
{
	// �w�i�A���S
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int i = 0; i < ImgData2::LOG_BACKGROUND_NUMBER; i++) { image_bl_background[i].DrawImage(); }

	for (int i = 0; i < 4; i++)
	{
		// �䎌
		BOOL end = FALSE;
		// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^
		int CP_A = 0;
		// ���z��ʏ�ł̕����\���J�[�\���̈ʒu
		int CursorX_A = 0;
		int CursorY_A = 0;

		int y = 0;		// �i�v���[�v���p�e�X�g�ϐ�
		int	row = 1;	// �䎌�s��
		// �I�����p���z�e�L�X�g�o�b�t�@�i���T�C�Y�i�Q�Ԗځj�̐����͓K���j
		char StringBuf[STRBUF_ALTENATIVE_HEIGHT][STRBUF_ALTENATIVE_WIDTH + 2] = {"", "", ""};
		do
		{
			char Moji = 0;
			#pragma region ver0.021���쎞�R�����g���R�[�h
			//// �����̕`��
			//Moji = text_log[i].line[CP_A];
			//switch (Moji)
			//{
			//case '@':	// ���s����
			//	// ���s��������юQ�ƕ����ʒu��������߂�
			//	CursorY_A++;
			//	CursorX_A = 0;
			//	CP_A++;
			//	row++;	// �`����W�Q�ƂɎg����s�����J�E���g����
			//	break;
			//default:	// ���̑��̕���
			//	// �P�����̃o�C�g�����擾
			//	int Bytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &HM[commu_number][cell_number].line[CP_A]);
			//	// �P�����e�L�X�g�o�b�t�@�ɑ��
			//	for (int moji_i = 0; moji_i < Bytes; moji_i++) { StringBuf[CursorY_A][CursorX_A + moji_i] = text_log[i].line[CP_A + moji_i]; }
			//	// �Q�ƕ����ʒu���P�����̃o�C�g�����i�߂�
			//	CP_A += Bytes;
			//	// �J�[�\�����ꕶ���̃o�C�g�����i�߂�
			//	CursorX_A += Bytes;
			//	// �e�L�X�g�o�b�t�@��������͂ݏo������s����
			//	if (CursorX_A >= STRBUF_ALTENATIVE_WIDTH)
			//	{
			//		CursorY_A++;
			//		CursorX_A = 0;
			//	}
			//	break;
			//}
			//// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
			//if (text_log[i].line[CP_A] == '\0') { end = TRUE; }

			//y++;
#pragma endregion
			// �����̕`��
			Moji = text_log[i + (page - 1) * PAGES_LINE_NUMBER].line[CP_A];
			switch (Moji)
			{
			case '@':	// ���s����
				// ���s��������юQ�ƕ����ʒu��������߂�
				CursorY_A++;
				CursorX_A = 0;
				CP_A++;
				row++;	// �`����W�Q�ƂɎg����s�����J�E���g����
				break;
			default:	// ���̑��̕���
				// �P�����̃o�C�g�����擾
				int Bytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &text_log[i + (page - 1) * PAGES_LINE_NUMBER].line[CP_A]);
				// �P�����e�L�X�g�o�b�t�@�ɑ��
				for (int moji_i = 0; moji_i < Bytes; moji_i++) { StringBuf[CursorY_A][CursorX_A + moji_i] = text_log[i + (page - 1) * PAGES_LINE_NUMBER].line[CP_A + moji_i]; }
				// �Q�ƕ����ʒu���P�����̃o�C�g�����i�߂�
				CP_A += Bytes;
				// �J�[�\�����ꕶ���̃o�C�g�����i�߂�
				CursorX_A += Bytes;
				// �e�L�X�g�o�b�t�@��������͂ݏo������s����
				if (CursorX_A >= STRBUF_ALTENATIVE_WIDTH)
				{
					CursorY_A++;
					CursorX_A = 0;
				}
				break;
			}
			// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
			if (text_log[i + (page - 1) * PAGES_LINE_NUMBER].line[CP_A] == '\0') { end = TRUE; }

			y++;
		} while (end == FALSE && y < 255);
		/* �`�� ---------*/
		int z = 180;

		int x = -1;
		if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "��l��") == 0) { x = 0; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "�߂���") == 0) { x = 1; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "����") == 0) { x = 2; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "����") == 0) { x = 3; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "�z��") == 0) { x = 4; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "���") == 0) { x = 5; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "�͂Â�") == 0) { x = 6; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "�Z��") == 0) { x = 7; }
		else if (std::strcmp(text_log[i + (page - 1) * PAGES_LINE_NUMBER].character, "") != 0) { x = 8; }
		/* �e�L�X�g�E�B���h�E ---------*/
		int a = 0;
		// �䎌���\�����I����Ă��āA�`�F�b�N�s�̑䎌�Łwtext_window_color�x�R�}���h���g���Ă���Ȃ�
		#pragma region ver0.031���쎞�R�����g���R�[�h
		//if (((page - 1) * PAGES_LINE_NUMBER + i < next_input_id) && std::strcmp(HM[commu_number][i + (page - 1) * PAGES_LINE_NUMBER].GetCommand(), "text_window_color") == 0)
#pragma endregion
		if (((page - 1) * PAGES_LINE_NUMBER + i < next_input_id) && std::strcmp(HM[commu_number][text_log[i + (page - 1) * PAGES_LINE_NUMBER].line_number].GetCommand(), "text_window_color") == 0)
		{
			#pragma region ver0.031���쎞�R�����g���R�[�h
			//switch (HM[commu_number][i + (page - 1) * PAGES_LINE_NUMBER].GetCommandNumber())
#pragma endregion
			switch (HM[commu_number][text_log[i + (page - 1) * PAGES_LINE_NUMBER].line_number].GetCommandNumber())
			{
			case 1: a = 4;	break;
			case 2: a = 1;	break;
			case 3: a = 2;	break;
			case 4: a = 3;	break;
			default:		break;
			}
		}
		else
		{
			if (x == 0) { a = 1; }
			else if (x >= 1 && x <= 5) { a = 2; }
			else if (x == 6 || x == 8) { a = 3; }
			else if (x == 7) { a = 4; }
		}
		// �o�b�N���O�p
		char c[256];
		sprintf_s(c, 256, "�Z���t%d�E%d\n", i + (page - 1) * PAGES_LINE_NUMBER, a);
		LogFileAdd(c);

		image_log_text_window[a].DrawImageCoordinateY((i * z + 222) * bairitu);
		/*-----------------------------*/
		// �䎌��t�h
		if (x >= 0) { image_map_character[x].DrawImageCoordinateY((i * z + 270) * bairitu); }

		if ((page - 1) * PAGES_LINE_NUMBER + i < next_input_id)
		{
			for (int j = 0; j < row; j++)
			{
				DrawFormatStringFToHandle(180 * bairitu, (i * z + j * 45 + 240) * bairitu, GetColor(0, 0, 0), g_font_commu_line, StringBuf[j]);
				//DebugLog(LogOutputType::LOG_MESSAGE);
				// �o�b�N���O�p
				//char c[256];
				//sprintf_s(c, 256, "%s\n", StringBuf[j]);
				//LogFileAdd(c);
			}
		}
		/*---------------*/
	}
	// �y�[�W��
	char c[256];
	sprintf_s(c, 256, "%d�^%d\n", page, (next_input_id - 1) / PAGES_LINE_NUMBER + 1);
	DrawFormatStringFToHandle(165 * bairitu, bairitu * 930, GetColor(0, 0, 0), g_font_commu_line, c);
	// ���A�C�R��
	for (int i = 0; i < ImgDataHJ2::TEXT_LOG_ARROW_NUMBER; i++){image_icon_text_log[i].DrawImage();}
	// BACK�A�C�R��
	image_icon_log_back.DrawImage();
}
// �y�[�W�����Z�b�g���㉺���𒴂��Ȃ��悤�C������
void TextLog::SetPage(int x)
{
	int y = (next_input_id - 1) / PAGES_LINE_NUMBER + 1;	// �ő�̃y�[�W��
	int z = page;	// �r�d����p�ύX�O�y�[�W��
	page = x;
	if (page < 1) { page = 1; }
	else if (page > y) { page = y; }
	if (page != z) { SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE)); }	// �r�d��炷

}
// ��Ԃ����Z�b�g����
void TextLog::Reset()
{
	for (int i = 0; i < COMMU_LINE_MAX; i++)
	{
		sprintf_s(text_log[i].character, 32, "");
		sprintf_s(text_log[i].line, 128, "");
		text_log[i].line_number = 0;
	}
	next_input_id = 0;
	page = 1;
}
/*------------------------*/

BOOL commu_mode_background = FALSE;	// �r�d���ς�肫��܂ŃN���b�N����ł��Ȃ��悤�ɂ���t���O
BOOL commu_mode_distance = FALSE;	// �\������Ă���L�������Q�l�̍ہA�ϓ��ɕ��ׂ邩
BOOL commu_mode_menu = FALSE;		// ���j���[�̓��e��\������
BOOL commu_mode_text_off = FALSE;	// �e�L�X�g�t�@�C���܂߂��S�Ă̂t�h���\���ɂ���
BOOL commu_before_cs = FALSE;		// �R�~���̉{�����n�߂�O�̓R�~���Z���N�g���[�h�����������ʂ���
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icft=click_flag_title�j
BOOL cfgmc_move_title = FALSE;		// �^�C�g����ʂֈړ�
#pragma region ver0.007���쎞�R�����g���R�[�h
//BOOL cfgmc_altenative[3];			// �I������I��
#pragma endregion
BOOL cfgmc_cell_count = FALSE;		// �R�~���̏������̂��̂ɂ���
BOOL cfgmc_change_auto = FALSE;		// �I�[�g���[�h�؂�ւ���
BOOL cfgmc_change_skip = FALSE;		// �X�L�b�v���[�h�؂�ւ���
BOOL cfgmc_exit_save = FALSE;		// �Z�[�u���[�h�ֈڍs
BOOL cfgmc_exit_load = FALSE;		// ���[�h���[�h�ֈڍs
BOOL cfgmc_change_menu = FALSE;		// ���j���[���[�h�؂�ւ���
BOOL cfgmc_change_text_off = FALSE;	// �e�L�X�g�I�t���[�h�؂�ւ���
BOOL cfgmc_exit_option = FALSE;		// �ݒ胂�[�h�ֈڍs

char String[][256] = 
{
	"",
	"E",
};
char* commu_bgm_name;																				// �R�~���ła�f�l���Đ����ꂽ�ہA�\������閼�O

int CursorX, CursorY;	// ���z��ʏ�ł̕����\���J�[�\���̈ʒu
int KeyWaitFlag;			// �{�^�������҂��t���O
int Count;				// �t���[���J�E���^

int commu_number = 0;					// ���ݎQ�Ƃ���Ă���R�~���h�c
int cell_number = 0;					// �Q�Ƃ����Z���̍s��
int commu_character[3];						// �`�悳���L�����h�c�i�L�����A�����A�|�[�Y���j
int commu_character_blink_limit[3];			// �܂΂��������I����܂ł̎c��t���[����
int commu_character_talk_limit[3];			// ���p�N�����I����܂ł̎c��t���[����
int commu_character_before[3];				// �؂�ւ��O�̃L�����N�^�[
int commu_character_after[3];				// �؂�ւ���̃L�����N�^�[
#pragma region ver0.00294���쎞�R�����g���R�[�h
//int commu_character_visibility_count = 0;	// �L�����N�^�[�s�����x�؂�ւ�����������܂ł̃t���[����
#pragma endregion
int commu_character_visibility_count[COMMU_CHARACTER_MAX];	// �L�����N�^�[�s�����x�؂�ւ�����������܂ł̃t���[����
int commu_background;						// �w�i
int commu_background_before;				// �؂�ւ��O�̔w�i
int commu_background_visibility_count = 0;	// �w�i�؂�ւ�����������܂ł̃t���[����
int commu_bgm_flame = 180;					// �a�f�l���؂�ւ���Ă���̌o�߃t���[����
int commu_altenative_string_line[3];		// �e�I�����̍s��
int commu_message_point = 0;				// �䎌��`�悷��ۂɕK�v�ȃ|�C���g
int commu_auto_count = 0;					// ���s�Ɏ����ōs�����߂̃J�E���g
int commu_frame_auto_count = 0;				// �wframe_auto�x�Ŏ��s�Ɏ����ōs�����߂̃J�E���g
int text_window_clear_percentage = 0;		// �e�L�X�g�E�B���h�E���ߓx
/* ������`��p�e�X�g�R�[�h---------*/
int moji_i, moji_j;
int Bytes;
/* ---------------------------------*/

float commu_play_time = 0;					// �v���C���ԁi�b�j
#pragma region ver0.007���쎞�R�����g���R�[�h
//float commu_altenative_x[3];				// �I����x���W
#pragma endregion
#pragma region ver0.00704���쎞�R�����g���R�[�h
//float commu_altenative_y_upper = 0;			// �㑤�I����y���W
//float commu_altenative_y_under = 0;			// �����I����y���W
#pragma endregion
float commu_altenative_string_center_x[3];	// �I���������񒆐Sx���W
float commu_coordinate_icon_auto_x = 0;		// �wauto�x�A�C�R��x���W
float commu_coordinate_icon_auto_y = 0;		// �wauto�x�A�C�R��y���W
float commu_coordinate_icon_skip_y = 0;		// �wSKIP�x�A�C�R����[y���W
float commu_coordinate_icon_save_y = 0;		// �wSAVE�x�A�C�R����[y���W
float commu_coordinate_icon_load_y = 0;		// �wLOAD�x�A�C�R����[y���W
float commu_coordinate_icon_option_y = 0;	// �wOPTION�x�A�C�R����[y���W
float commu_coordinate_icon_menu_y = 0;		// �wMENU�x�A�C�R����[y���W
float commu_coordinate_icon_tf_x = 0;		// �wTEXT OFF�x�A�C�R�����[x���W

// �R�~����ʈڍs����
#pragma region ver0.00396���쎞�R�����g���R�[�h
//void GameMainCommunicationNext(int x)	// �Q�Ƃ����R�~��ID
#pragma endregion
void GameMainCommunicationNext(int x, BOOL y, int z)	// �Q�Ƃ����R�~��ID, �R�~���Z���N�g��ʂ��痈����,�Z���ԍ�
{
	g_gamestate = GAME_MAIN_COMMUNICATION;
	MusicPlay(-1);	// �a�f�l��~
	// �`��ʒu�̏����ʒu�Z�b�g
	CursorX = 0;
	CursorY = 0;
	// �Q�ƕ����ʒu���Z�b�g
	SP = 0;	// �P�s�ڂ�
	CP = 0;	// �O����
	// �t�H���g�̃T�C�Y�Z�b�g
	SetFontSize(MOJI_SIZE);
	// �t���[���J�E���^������
	Count = 0;
	// �ǂݍ��݃Z���s��������
	//cell_number = 0;
	#pragma region ver0.00607���쎞�R�����g���R�[�h
	//cell_number = -1;	// �ʂ̏����ł����w0�x�ɂȂ�̂ŁA�Y���h�~
#pragma endregion
	cell_number = z - 1;	// �ʂ̏����ł����w0�x�ɂȂ�̂ŁA�Y���h�~

	commu_number = x;		// ���ݎQ�ƃR�~��ID��ύX

	// �����G�ǂݍ��݃e�X�g
	CharacterImage::SetFlagAll(FALSE);
	CharacterImage::LoadFlagCheck();
	if (mode_debug == FALSE) { CharacterImage::DeleteAll(); }	// �f�o�b�O���[�h�Ȃ��X�����Ȃ�
	#pragma region ver0.0091���쎞�R�����g���R�[�h
	//CharacterImage::Load();
#pragma endregion
	if (CharacterImage::Load() == FALSE) { quit_game = TRUE; }
	// �a�f�l�ǂݍ���
	BGMData::SetLoadAll(FALSE);									// �ǂݍ��ݑO�̃��Z�b�g����
	BGMData::LoadFlagCheck();									// �ǂ��ǂݍ��ނ��`�F�b�N
	if (mode_debug == FALSE) { BGMData::DeleteAll(); }			// �s�K�v�Ȃa�f�l���폜�i�f�o�b�O���[�h�Ȃ��X�����Ȃ��j
	BGMData::Load();											// �ǂݍ���

	DebugLog(LogOutputType::LOAD_FLAG);

	commu_before_cs = y;	// �ǂ̃��[�h���痈�����L��
	// ���Z�b�g������
	for (int i = 0; i < 3; i++){ commu_character[i] = 0; }	// �L�����N�^�[�̗����G���
	commu_mode_distance = FALSE;							// �\������Ă���L�������Q�l�̍ہA�ϓ��ɕ��ׂ邩
	TextLog::Reset();										// �e�L�X�g���O
	// �}�b�v��ʂ̃R�~���X�^�[�g�r�d�����Ă�����胋�[�v��������
	while (SEData::CheckCommuStartTime() == FALSE) {}

	GameMainCommunicationNextLine();						// �ŏ��̍s�v�f��ǂݍ���
	g_commustatus = COMMU_STATUS_NORMAL;					// �R�~���̏��
	commu_message_point = 0;								// �䎌��`�悷��ۂɕK�v�ȃ|�C���g
	// �I�����̃W�����v�旚��
	for (int i = 0; i < COMMU_LINE_MAX; i++) { state::SetAlternativeMoveNumber(i, 0); }	

	#pragma region ver0.0033���쎞�R�����g���R�[�h
	//commu_mode_distance = FALSE;							// �\������Ă���L�������Q�l�̍ہA�ϓ��ɕ��ׂ邩
#pragma endregion
	#pragma region ver0.00704���쎞�R�����g���R�[�h
	//g_commuauto = COMMU_AUTO_NORMAL;						// �R�~�������i�s���
#pragma endregion
	if (g_commuauto == COMMU_AUTO_SKIP) { g_commuauto = COMMU_AUTO_NORMAL; }	// �R�~�������i�s���
	// �`���[�g���A�����[�h�ɕK�v�ȗv�f�����Z�b�g����
	ImgDataBGTutorial::Reset();
	// �i�f�o�b�O�p�j�g����w�i�̃t���O�𗧂Ă�
	for (int i = 0; i < COMMU_LINE_MAX; i++) 
	{ 
		if (HM[commu_number][i].GetBackground() > 0) { bgimage[HM[commu_number][i].GetBackground() - 1].SetUse(TRUE); }
	}
}
// GameMainCommunication��Ԃ̃��C������
void GameMainCommunication()
{
	GameMainCommunicationControl();
	GameMainCommunicationFlame();
	DrawGameMainCommunication();
}
// �R�~����ʑ��쏈��
void GameMainCommunicationControl()
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
				#pragma region ver0.0081���쎞�R�����g���R�[�h
//				if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * COMMU_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, TRUE, FALSE) == TRUE){ cfgmc_move_title = TRUE; }
//				#pragma region ver0.007���쎞�R�����g���R�[�h
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[0], commu_altenative_y_upper, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, TRUE, FALSE) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ cfgmc_altenative[0] = TRUE; }
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[1], commu_altenative_y_under, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, TRUE, FALSE) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ cfgmc_altenative[1] = TRUE; }
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[2], commu_altenative_y_under, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, TRUE, FALSE) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ cfgmc_altenative[2] = TRUE; }
//#pragma endregion
//				else if (hjimage_alternative[0].JudgementClickCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) {}
#pragma endregion
				// �o�b�N���O�\�����͊�{�I�ȑ��삪�ł��Ȃ�
				if (TextLog::GetMode() == FALSE)
				{
					if (hjimage_alternative[0].JudgementClickCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) {}
					else if (hjimage_alternative[1].JudgementClickCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) {}
					else if (hjimage_alternative[2].JudgementClickCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) {}
					#pragma region ver0.0028���쎞�R�����g���R�[�h
					//else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE){ cfgmc_change_auto = TRUE; }
					//else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE){ cfgmc_change_skip = TRUE; }
					//else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cfgmc_exit_save = TRUE; }
					//else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cfgmc_exit_load = TRUE; }
#pragma endregion
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_change_auto = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_change_skip = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_exit_save = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_exit_load = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_option_y, image_icon_option.size_x, image_icon_option.size_y, TRUE, FALSE, CFC_COMMU_MENU) == TRUE) { cfgmc_exit_option = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_menu_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE, CFC_COMMU_TEXT) == TRUE) { cfgmc_change_menu = TRUE; }
					else if (ClickFlagCheckF2(ClickX, ClickY, commu_coordinate_icon_tf_x, commu_coordinate_icon_menu_y, size_icon_text_off.x, size_icon_text_off.y, TRUE, FALSE, CFC_COMMU_TEXT) == TRUE) { cfgmc_change_text_off = TRUE; }
					// ���O
					else if (image_icon_log.JudgementClickCheckFlag(commu_mode_menu == TRUE && commu_mode_text_off == FALSE) == TRUE) {}
					else { cfgmc_cell_count = TRUE; }
				}
				// �o�b�N���O�\����
				else
				{
					if(image_icon_log_back.JudgementClickCheck() == TRUE){}
					else if(image_icon_text_log[0].JudgementClickCheck() == TRUE){}
					else if (image_icon_text_log[1].JudgementClickCheck() == TRUE) {}
					else if (image_icon_text_log[2].JudgementClickCheck() == TRUE) {}
					else if (image_icon_text_log[3].JudgementClickCheck() == TRUE) {}
				}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				#pragma region ver0.0081���쎞�R�����g���R�[�h
//				// �^�C�g����ʂֈړ�
//				if (ClickFlagCheckF(ClickX, ClickY, screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * COMMU_MESSEAGE_TITLE_Y, (float)GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL, FALSE, cfgmc_move_title) == TRUE){ GameTitleNext(); }
//				// �I�����ɑΉ������s�ɃW�����v����i�w�W�����v��̍s�|�P�x�s�ڂ܂Ŕ�񂾌�AGameMainCommunicationNextLine�֐����Ăяo���j
//				// �i�I������I�񂾂�e�L�X�g�I�t�@�\�����������悤�ɂ���H�j
//				#pragma region ver0.007���쎞�R�����g���R�[�h
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[0], commu_altenative_y_upper, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, FALSE, cfgmc_altenative[0]) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ GameMainCommunicationAltenative(0); }
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[1], commu_altenative_y_under, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, FALSE, cfgmc_altenative[1]) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ GameMainCommunicationAltenative(1); }
//				//else if ((ClickFlagCheckF(ClickX, ClickY, commu_altenative_x[2], commu_altenative_y_under, bairitu * size_commu_altenative.x, bairitu * size_commu_altenative.y, FALSE, cfgmc_altenative[2]) == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) == TRUE){ GameMainCommunicationAltenative(2); }
//#pragma endregion
//				else if (hjimage_alternative[0].JudgementReleaseCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) { GameMainCommunicationAltenative(0); }
#pragma endregion
				// �o�b�N���O�\�����͊�{�I�ȑ��삪�ł��Ȃ�
				if (TextLog::GetMode() == FALSE)
				{
					if (hjimage_alternative[0].JudgementReleaseCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) { GameMainCommunicationAltenative(0); }
					else if (hjimage_alternative[1].JudgementReleaseCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) { GameMainCommunicationAltenative(1); }
					else if (hjimage_alternative[2].JudgementReleaseCheck() == TRUE && g_commustatus == COMMU_STATUS_ALTENATIVE) { GameMainCommunicationAltenative(2); }
					#pragma region ver0.0028���쎞�R�����g���R�[�h
					// �I�[�g���[�h��؂�ւ�
	//				else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_auto) == TRUE)
	//				{ 
	//					// �ʏ�A�X�L�b�v��ԂȂ�
	//					if (g_commuauto != COMMU_AUTO_ON)
	//					{
	//						#pragma region ver0.0024���쎞�R�����g���R�[�h
	//						//g_commuauto = COMMU_AUTO_ON;
	//						//commu_auto_count;
	//#pragma endregion
	//						GameMainCommunicationAuto();
	//					}
	//					// �I�[�g���[�h�Ȃ�ʏ�ɖ߂�
	//					else{ g_commuauto = COMMU_AUTO_NORMAL; }
	//					// �r�d��炷
	//					SEPlay(SN_ALTERNATIVE);
	//				}
	//				// �X�L�b�v���[�h�؂�ւ�
	//				else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_skip) == TRUE)
	//				{
	//					// �ʏ�A�I�[�g��ԂȂ�X�L�b�v���[�h�ɂ���
	//					if (g_commuauto != COMMU_AUTO_SKIP){ g_commuauto = COMMU_AUTO_SKIP; }
	//					// �X�L�b�v���[�h�Ȃ�ʏ�ɖ߂�
	//					else{ g_commuauto = COMMU_AUTO_NORMAL; }
	//					// �r�d��炷
	//					SEPlay(SN_ALTERNATIVE);
	//				}
	//				// �Z�[�u���[�h�ֈڍs
	//				else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_exit_save) == TRUE) { GameSaveLoadNext(TRUE, SL_BEFORE_COMMU); }
	//				// ���[�h���[�h�ֈڍs
	//				else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_exit_load) == TRUE) { GameSaveLoadNext(FALSE, SL_BEFORE_COMMU); }
#pragma endregion
					// �I�[�g���[�h��؂�ւ�
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_auto) == TRUE && commu_mode_menu == TRUE)
					{
						// �ʏ�A�X�L�b�v��ԂȂ�
						if (g_commuauto != COMMU_AUTO_ON) { GameMainCommunicationAuto(); }
						// �I�[�g���[�h�Ȃ�ʏ�ɖ߂�
						else { g_commuauto = COMMU_AUTO_NORMAL; }
						// �r�d��炷
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					}
					// �X�L�b�v���[�h�؂�ւ�
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_skip) == TRUE && commu_mode_menu == TRUE)
					{
						// �ʏ�A�I�[�g��ԂȂ�X�L�b�v���[�h�ɂ���
						if (g_commuauto != COMMU_AUTO_SKIP) { g_commuauto = COMMU_AUTO_SKIP; }
						// �X�L�b�v���[�h�Ȃ�ʏ�ɖ߂�
						else { g_commuauto = COMMU_AUTO_NORMAL; }
						// �r�d��炷
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					}
					// �Z�[�u���[�h�ֈڍs
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_exit_save) == TRUE && commu_mode_menu == TRUE)
					{
						GameSaveLoadNext(TRUE, SL_BEFORE_COMMU);
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// �r�d��炷
					}
					// ���[�h���[�h�ֈڍs
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_exit_load) == TRUE && commu_mode_menu == TRUE)
					{
						GameSaveLoadNext(FALSE, SL_BEFORE_COMMU);
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// �r�d��炷
					}
					// �I�v�V�������[�h�ֈڍs
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_option_y, image_icon_option.size_x, image_icon_option.size_y, FALSE, cfgmc_exit_option) == TRUE && commu_mode_menu == TRUE)
					{
						GameConfigNext(TRUE);
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// �r�d��炷
					}
					// ���j���[���[�h��؂�ւ���
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_auto_x, commu_coordinate_icon_menu_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfgmc_change_menu) == TRUE)
					{
						FlagChange(&commu_mode_menu);
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// �r�d��炷
					}
					// ��ʂ̂t�h���\���ɂ���i�e�L�X�g�I�t���[�h�ɂ���j
					else if (ClickFlagCheckF(ClickX, ClickY, commu_coordinate_icon_tf_x, commu_coordinate_icon_menu_y, size_icon_text_off.x, size_icon_text_off.y, FALSE, cfgmc_change_text_off) == TRUE)
					{
						g_commuauto = COMMU_AUTO_NORMAL;	// �I�[�g�A�X�L�b�v���[�h����������
						commu_mode_text_off = TRUE;
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));	// �r�d��炷
					}
					// ���O
					else if (image_icon_log.JudgementReleaseCheck() == TRUE) 
					{ 
						TextLog::SetMode(TRUE); 
						TextLog::SetPage((TextLog::GetNIID() - 1) / TextLog::GetPagesLineNumber() + 1);
						// �r�d��炷
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					}

					else if (cfgmc_cell_count == TRUE && g_commustatus == COMMU_STATUS_NORMAL && commu_mode_background == FALSE)
					{
						// �e�L�X�g�I�t���[�h�Ȃ炻�����������
						if (commu_mode_text_off == TRUE) { commu_mode_text_off = FALSE; }
						// �����`�悳�ꂫ���Ă��Ȃ���ΑS�ĕ`�悵�A���ɂ���Ă���Ȃ玟�̍s�֍s��
						#pragma region ver0.0028���쎞�R�����g���R�[�h
//GameMainCommunicationNextLine();
//if (EndFlag == 0){ GameMainCommunicationMoji(TRUE); }
#pragma endregion
						else if (EndFlag == 0) { GameMainCommunicationMoji(TRUE); }
						else { GameMainCommunicationNextLine(); }
					}
				}
				// �o�b�N���O�\����
				else
				{
					if (image_icon_log_back.JudgementReleaseCheck() == TRUE) 
					{
						TextLog::SetMode(FALSE); 
						// �r�d��炷
						SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					}
					else if (image_icon_text_log[0].JudgementReleaseCheck() == TRUE) { TextLog::SetPage(1); }
					else if (image_icon_text_log[1].JudgementReleaseCheck() == TRUE) { TextLog::SetPage(TextLog::GetPage() - 1); }
					else if (image_icon_text_log[2].JudgementReleaseCheck() == TRUE) { TextLog::SetPage(TextLog::GetPage() + 1); }
					else if (image_icon_text_log[3].JudgementReleaseCheck() == TRUE) { TextLog::SetPage(TextLog::GetNIID() / TextLog::GetPagesLineNumber() + 1); }


					// shift�L�[��������Ă���Β[�܂ňړ�
					//BOOL x = (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT)) ? TRUE : FALSE;
					//if (KeyTrigger::Trigger(key, KeyTrigger::Type::LEFT) == TRUE) { TextLog::SetPage(x == FALSE ? TextLog::GetPage() - 1 : 1); }
					//else if (KeyTrigger::Trigger(key, KeyTrigger::Type::RIGHT) == TRUE) { TextLog::SetPage(x == FALSE ? TextLog::GetPage() + 1 : TextLog::GetNIID() / TextLog::GetPagesLineNumber() + 1); }
				}
				// �S�Ẵt���O��߂�
				cfgmc_move_title = FALSE;												// �^�C�g����ʂֈړ�
				#pragma region ver0.007���쎞�R�����g���R�[�h
				//for (int i = 0; i < 3; i++){ cfgmc_altenative[i] = FALSE; }	// �I������I��
#pragma endregion
				for (int i = 0; i < 3; i++) { hjimage_alternative[i].CJChange(FALSE); }	// �I������I��
				cfgmc_cell_count = FALSE;				// �R�~���̏������̂��̂ɂ���
				cfgmc_change_auto = FALSE;				// �I�[�g���[�h�؂�ւ�
				cfgmc_change_skip = FALSE;				// �X�L�b�v���[�h�؂�ւ�
				cfgmc_exit_save = FALSE;				// �Z�[�u���[�h�ڍs
				cfgmc_exit_load = FALSE;				// ���[�h���[�h�ڍs
				cfgmc_exit_option = FALSE;				// �ݒ胂�[�h�ֈڍs
				cfgmc_change_menu = FALSE;				// ���j���[���[�h�؂�ւ�
				cfgmc_change_text_off = FALSE;			// �e�L�X�g�I�t���[�h�؂�ւ�
				image_icon_log.CJChange(FALSE);			// �e�L�X�g���O�\��
				image_icon_log_back.CJChange(FALSE);	// �o�b�N���O�p�wBACK�x
			}
		}
	}
}
//	�I�[�g���[�h���n�m�ɂȂ�ۂ̏���
void GameMainCommunicationAuto()
{
	// �I�[�g���[�h�ɂ��A��p�̃J�E���g������������
	g_commuauto = COMMU_AUTO_ON;
	commu_auto_count;
}
// �R�~�����[�h���P�t���[�����ɍs���鏈��
void GameMainCommunicationFlame()
{
	commu_bgm_flame++;	// �a�f�l���`��p�o�߃t���[�������J�E���g����
	// �wauto_se�x���[�h�Ȃ�r�d����I�������`�F�b�N���A��I����Ă���Ȃ玟�̍s�ɐi�ށi�P�Ȃ�Đ��A-1�Ȃ�G���[�j
	#pragma region ver0.00607���쎞�R�����g���R�[�h
	//if (g_commustatus == COMMU_STATUS_SE && CheckSoundMem(g_sndhandles.SE[HM[commu_number][cell_number].se - 1]) == 0)
#pragma endregion
	if (g_commustatus == COMMU_STATUS_SE && CheckSoundMem(se[HM[commu_number][cell_number].se - 1].GetHandle()) == 0)
	{
		g_commustatus = COMMU_STATUS_NORMAL;
		GameMainCommunicationNextLine();
	}
	// �wCOMMU_STATUS_AUTO�x�Ȃ�J�E���g�_�E�����s���A0�ɂȂ����玟�̍s�ɐi��
	if (g_commustatus == COMMU_STATUS_AUTO)
	{
		// �X�L�b�v���[�h�Ȃ�A�����ɃJ�E���g��0�ɂ��邪�X�L�b�v�{���̏����Ŏ��s�ɂ������邽�ߎ��s�ɍs���������΂�
		if (g_commuauto == COMMU_AUTO_SKIP) { commu_frame_auto_count = 0; }
		else { commu_frame_auto_count--; }
		if (commu_frame_auto_count == 0)
		{
			g_commustatus = COMMU_STATUS_NORMAL;
			//if(g_commuauto != COMMU_AUTO_SKIP){ GameMainCommunicationNextLine(); }			
			if (g_commuauto != COMMU_AUTO_SKIP && commu_number >= 0) { GameMainCommunicationNextLine(); }
		}
	}
	// �o�����Ă���L�����ɁA�u���Ɋւ��鏈�����s��
	#pragma region ver0.00294���쎞�R�����g���R�[�h
//	if (commu_character[1] > 0)
//	{
//		#pragma region ver0.00291���쎞�R�����g���R�[�h
//		// �u�������I���Ă����ԂȂ�c�莞�Ԃ��ăZ�b�g����
//		//if (commu_character_blink_limit[1]-- <= 0){ commu_character_blink_limit[1] = 180; }
//#pragma endregion
//		// �u�������I���Ă����ԂȂ�c�莞�Ԃ��ăZ�b�g����
//		commu_character_blink_limit[1]-- ;
//		if (g_commu_character_face[1] == CCF_CLOSE_EYE || g_commu_character_face[1] == CCF_CLOSE_EYE_SMILE)
//		{
//			if (commu_character_blink_limit[1] > COMMU_EYE_ANIMATION_FLAME * 3) { commu_character_blink_limit[1] = COMMU_EYE_ANIMATION_FLAME * 3; }
//			else if (commu_character_blink_limit[1] < COMMU_EYE_ANIMATION_FLAME + 1) { commu_character_blink_limit[1] = COMMU_EYE_ANIMATION_FLAME + 1; }
//		}
//		else if(commu_character_blink_limit[1] <= 0){ commu_character_blink_limit[1] = 180; }
//	}
#pragma endregion
	for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
	{
		if (commu_character[i] > 0)
		{
			// �u�������I���Ă����ԂȂ�c�莞�Ԃ��ăZ�b�g����
			commu_character_blink_limit[i]--;
			if (g_commu_character_face[i] == CCF_CLOSE_EYE || g_commu_character_face[i] == CCF_CLOSE_EYE_SMILE)
			{
				if (commu_character_blink_limit[i] > COMMU_EYE_ANIMATION_FLAME * 3) { commu_character_blink_limit[i] = COMMU_EYE_ANIMATION_FLAME * 3; }
				else if (commu_character_blink_limit[i] < COMMU_EYE_ANIMATION_FLAME + 1) { commu_character_blink_limit[i] = COMMU_EYE_ANIMATION_FLAME + 1; }
			}
			else if (commu_character_blink_limit[i] <= 0) { commu_character_blink_limit[i] = 180; }
		}
	}
	// �ݒ�ɉ����āA�䎌��`�悷��ۂɕK�v�ȃ|�C���g�����Z����
	#pragma region ver0.0021���쎞�R�����g���R�[�h
	//if (g_commumessagespeed == COMMU_MESSAGE_SPEED_SLOW){ commu_message_point += COMMU_COUNT_SLOW; }
#pragma endregion
	if (g_commuauto == COMMU_AUTO_SKIP){ commu_message_point += COMMU_COUNT_FAST * 4; }
	else if (g_commumessagespeed == COMMU_MESSAGE_SPEED_SLOW){ commu_message_point += COMMU_COUNT_SLOW; }
	else if (g_commumessagespeed == COMMU_MESSAGE_SPEED_NORMAL){ commu_message_point += COMMU_COUNT_NORMAL; }
	else{ commu_message_point += COMMU_COUNT_FAST; }
	// �䎌��ƕ`�悳��Ă���L�������`�F�b�N���i�߂��邪�P�j����ׂ肪�I����ĂȂ��Ȃ���p�N�̃J�E���g�����ăZ�b�g����
	for (int i = 0; i < 3; i++)
	{
		if (commu_character_talk_limit[i] >= 1){ commu_character_talk_limit[i]--; }
	}
	for (int i = 0; i < 3; i++)
	{
		const char* x = "";
		#pragma region ver0.0029���쎞�R�����g���R�[�h
		//switch (commu_character[i] / 10 - 1)
#pragma endregion
		switch (commu_character[i] / 1000 - 1)
		{
		case 0: x = "�߂���";	break;
		case 1: x = "����";		break;
		case 2: x = "����";		break;
		case 3: x = "�z��";		break;
		case 4: x = "���";		break;
		case 5: x = "�͂Â�";	break;
		case 6: x = "�Z��";		break;
		default:				break;
		}

		// �J�����ςȂ�
		if (HM[commu_number][cell_number].line_mouse == 2)
		{
			if (commu_character_talk_limit[i] < COMMU_MOUSE_ANIMATION_FLAME){ commu_character_talk_limit[i] = COMMU_MOUSE_ANIMATION_FLAME * 4 - 1; }
			else if (commu_character_talk_limit[i] == COMMU_MOUSE_ANIMATION_FLAME * 2){ commu_character_talk_limit[i]++; }
		}
		// �y�`�悳��Ă���L�����N�^�[�Ƒ䎌�傪��v���Ă���A�䎌���p�N�^�C�v���w����A�J�����ςȂ��x�ȊO�ł���z�������ʏ���
		#pragma region ver0.0029���쎞�R�����g���R�[�h
		//else if (commu_character[i] / 10 == 1 && strcmp(HM[commu_number][cell_number].name, "�߂���") == 0 && HM[commu_number][cell_number].line_mouse != -1)
#pragma endregion
		#pragma region ver0.00605���쎞�R�����g���R�[�h
		//else if (/*commu_character[i] / 10 == 1 &&*/ strcmp(HM[commu_number][cell_number].name, x) == 0 && HM[commu_number][cell_number].line_mouse != -1)
#pragma endregion
		else if ((strcmp(HM[commu_number][cell_number].name, x) == 0 && HM[commu_number][cell_number].line_mouse != -1) || HM[commu_number][cell_number].line_mouse == 3)
		{
			if (EndFlag == 0)
			{
				// ���p�N
				if ((HM[commu_number][cell_number].line_mouse == 0 || HM[commu_number][cell_number].line_mouse == 3)&& commu_character_talk_limit[i] <= 0){ commu_character_talk_limit[i] = COMMU_MOUSE_ANIMATION_NUMBER * COMMU_MOUSE_ANIMATION_FLAME - 1; }
				// �䎌�I���܂ŊJ��
				else if (HM[commu_number][cell_number].line_mouse == 1)
				{ 
					if (commu_character_talk_limit[i] < COMMU_MOUSE_ANIMATION_FLAME){ commu_character_talk_limit[i] = COMMU_MOUSE_ANIMATION_FLAME * 4 - 1; }
					else if(commu_character_talk_limit[i] == COMMU_MOUSE_ANIMATION_FLAME * 2){ commu_character_talk_limit[i]++; }
				}
			}
		}
	}
	// �L�����N�^�[�ύX�Ɋւ��ϐ��̃J�E���g�����炵�A0�ɂȂ����玟�̍s�֐i��
	#pragma region ver0.00294���쎞�R�����g���R�[�h
	//if (commu_character_visibility_count > 0)
	//{
	//	commu_character_visibility_count--;
	//	if (commu_character_visibility_count <= 0)
	//	{
	//		commu_mode_background = FALSE;
	//		GameMainCommunicationNextLine();
	//	}
	//}
#pragma endregion
	BOOL flag_x = FALSE;	// �����̃L������ς���ꍇ�A���ԍs�����Q�ȏ�ɂȂ��Ă��܂����߁A�t���O���ɂ��Ă���
	for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
	{
		if (commu_character_visibility_count[i] > 0)
		{
			commu_character_visibility_count[i]--;
			if (commu_character_visibility_count[i] <= 0) { flag_x = TRUE; }
		}
	}
	if (flag_x == TRUE)
	{
		commu_mode_background = FALSE;
		GameMainCommunicationNextLine();
	}
	// �w�i�ύX�Ɋւ��ϐ��̃J�E���g�����炵�A�O�ɂȂ����玟�̍s�֐i��
	if (commu_background_visibility_count > 0)
	{ 
		commu_background_visibility_count--; 
		//if (commu_background_visibility_count <= 0)
		if (commu_background_visibility_count <= 0 && commu_number >= 0)
		{
			commu_mode_background = FALSE;
			GameMainCommunicationNextLine();
		}
	}
	// �R�~�������^�C�v���ʏ�ł͂Ȃ��A�r�d�I�[�g�Đ�or�I������Ԃł͂Ȃ��A�L�����N�^�[�ύX�A�w�i�ύX���s���Ȃ��A�������`�悳�ꂫ������ԂȂ�J�E���g��i�߁A��萔�ɂȂ����玟�s�ɍs��
	if (g_commuauto != COMMU_AUTO_NORMAL && g_commustatus == COMMU_STATUS_NORMAL && commu_mode_background == FALSE && EndFlag == 1)
	{
		if (g_commuauto == COMMU_AUTO_ON)
		{
			commu_auto_count++;
			#pragma region ver0.021���쎞�R�����g���R�[�h
			//if (commu_auto_count > 40)
#pragma endregion
			if (commu_auto_count > 80)
			{
				commu_auto_count = 1;
				//GameMainCommunicationNextLine();

				if (commu_number >= 0) { GameMainCommunicationNextLine(); }
			}
		}
		// �X�L�b�v���[�h�Ȃ�J�E���g�Ȃ��Ŏ��s�ɍs��
		//else { GameMainCommunicationNextLine(); }
		else if(commu_number >= 0){ GameMainCommunicationNextLine(); }
	}
	// �I�����o�����A�v���C���Ԃɉ����đI������X���W��ς���iY���W�͂��̂܂܂Ȃ̂œ����l�j
	// �}�b�v�ړ����̍��W���i�āj��`����
	//float x = screen_size_x * 0.54f;
	//float y = bairitu * 705;														// �����̒��S����̂���
	//float z = (22.5f - (progress_frame % 45)) * bairitu;
	//hjimage_map[0].CoordinateSetting(x - y - hjimage_map[0].size_x / 2 - abs(z), screen_size_y / 2.0f);
	//hjimage_map[1].CoordinateSetting(x + y - hjimage_map[1].size_x / 2 + abs(z), screen_size_y / 2.0f);
	// �I����x���W
	//float x = hjimage_alternative[0].size_x * bairitu / 2;																	// �摜�̒��S���獶�[�̂���
	float x = hjimage_alternative[0].size_x / 2;																	// �摜�̒��S���獶�[�̂���
	float y = bairitu * (150 + abs(22.5f - (progress_frame % 45)));																								// �I����y���W�x�_
	#pragma region ver0.00704���쎞�R�����g���R�[�h
//commu_altenative_y_under = y + bairitu * hjimage_alternative[0].size_y * 2 / 3;	//�i �{���̂������傤���Q�������Ă�H�j���I����y���W
	//commu_altenative_y_under = y + hjimage_alternative[0].size_y * 2 / 3;	//�i �{���̂������傤���Q�������Ă�H�j���I����y���W
	//commu_altenative_y_upper = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_y_under : y;					// �㑤�I����y���W�i�Q�����A�����Ɠ���y���W�ɂȂ�j
#pragma endregion
	AlternativeCoordinate::SetYUnder(y + hjimage_alternative[0].size_y * 2 / 3);
	AlternativeCoordinate::SetYUpper(g_altenativenumber == ALTENATIVE_NUMBER_2 ? AlternativeCoordinate::GetYUnder() : y);
	//float z = bairitu * (hjimage_alternative[0].size_x + 54);																		// �R�����A���A�E�I�������Sx���W�́A��������̂���
	float z = hjimage_alternative[0].size_x + bairitu * 54;																		// �R�����A���A�E�I�������Sx���W�́A��������̂���
	#pragma region ver0.00704���쎞�R�����g���R�[�h
	//hjimage_alternative[2].CoordinateSetting(screen_size_x / 2 - x + z, commu_altenative_y_under);
	//hjimage_alternative[1].CoordinateSetting(g_altenativenumber == ALTENATIVE_NUMBER_2 ? hjimage_alternative[2].GetCoordinateX() : screen_size_x / 2 - x - z, commu_altenative_y_under);
	//hjimage_alternative[0].CoordinateSetting(g_altenativenumber == ALTENATIVE_NUMBER_2 ? screen_size_x / 2 - x - z : screen_size_x / 2 - x, commu_altenative_y_upper);
#pragma endregion
	hjimage_alternative[2].CoordinateSetting(screen_size_x / 2 - x + z, AlternativeCoordinate::GetYUnder());
	hjimage_alternative[1].CoordinateSetting(g_altenativenumber == ALTENATIVE_NUMBER_2 ? hjimage_alternative[2].GetCoordinateX() : screen_size_x / 2 - x - z, AlternativeCoordinate::GetYUnder());
	hjimage_alternative[0].CoordinateSetting(g_altenativenumber == ALTENATIVE_NUMBER_2 ? screen_size_x / 2 - x - z : screen_size_x / 2 - x, AlternativeCoordinate::GetYUpper());
	// �I���������񒆐Sx���W
	float a = (float)(screen_size_x / 2);
	commu_altenative_string_center_x[0] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? a - z : (float)(screen_size_x / 2);
	commu_altenative_string_center_x[2] = a + z;
	commu_altenative_string_center_x[1] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_string_center_x[2] : a - z;

	//float x = (22.5f - (progress_frame % 45)) * bairitu;
	//for (int i = 0; i < ALTENATIVE_MAX_NUMBER; i++) { hjimage_alternative[i].CoordinateSetting(); }

	commu_play_time += 1.0f / 60;		// �v���C���Ԃ�60���̂P�b�J�E���g����
	// �}�b�v�����R�~���ŃX�N���[�����グ��������
	if (commu_number == static_cast<int>(CommuType::TUTORIAL)) { ImgDataBGTutorial::ScreenYMove(); }
}
// �R�~����ԂŁA���s�̏������s��
void GameMainCommunicationNextLine()
{
	cell_number++;
	// ���s�Z���R�}���h���wmove_sell�x�Ȃ�w��s�ɒ���
	if (strcmp(HM[commu_number][cell_number].command, "move_sell") == 0)
	{
		// �s�W�����v�������L������
		state::SetAlternativeMoveNumber(cell_number - 2, HM[commu_number][cell_number].GetCommandNumber());

		cell_number = HM[commu_number][cell_number].move_commu_number - 2;
	}	
	if (strcmp(HM[commu_number][cell_number].command, "auto_se") == 0){ g_commustatus = COMMU_STATUS_SE; }	// ���s�Z���R�}���h���wauto_se�x�Ȃ玟�s�r�d�Đ����I���܂ő��삪�����ɂȂ�t���O�𗧂Ă�
	// ���s�Z���R�}���h���wframe_auto�x�Ȃ�w�w��t���[�����ꎟ�s�ɍs����ԁx�ɂ���
	else if (strcmp(HM[commu_number][cell_number].command, "frame_auto") == 0)
	{ 
		g_commustatus = COMMU_STATUS_AUTO; 
		commu_frame_auto_count = HM[commu_number][cell_number].move_commu_number;
	}
	// ���s�Z���R�}���h���wend�x�Ȃ�R�~�����I��������
	#pragma region ver0.00706���쎞�R�����g���R�[�h
//	else if (strcmp(HM[commu_number][cell_number].command, "end") == 0)
//	{ 
//		// �R�~���Z���N�g�ɂ��{���̏ꍇ�A�R�~���Z���N�g��ʂɖ߂�
//		#pragma region ver0.00396���쎞�R�����g���R�[�h
//		//GameMapNext();
//#pragma endregion
//		//commu_before_cs == FALSE ? GameMapNext() : GameCommuSelectNext();
//		if (commu_before_cs == FALSE)
//		{
//			switch (commu_number)
//			{
//			case COMMU_TYPE_OP:	GameMainCommunicationNext(COMMU_TYPE_TUTORIAL, FALSE, 0);	break;
//			case COMMU_TYPE_TUTORIAL:
//				GameMainCommunicationNext(COMMU_TYPE_TUTORIAL, FALSE, 0);
//				break;
//			case COMMU_TYPE_MEGURU0:
//				CommuData::SetGMapUpperType(CommuData::MapUpperType::RINZE0);
//			default:			GameMapNext();												break;
//			}			
//		}
//		else { GameCommuSelectNext(); }
//	}
#pragma endregion
	else if (strcmp(HM[commu_number][cell_number].command, "end") == 0)
	{ 
		GameMainCommunicationEnd();
		return;
	}
	// ���s�Z���R�}���h���wmove_commu�x�Ȃ玟��̔ԍ��ɉ������R�~���Ɉړ�����
	else if (strcmp(HM[commu_number][cell_number].command, "move_commu") == 0)
	{ 
		// �R�~���Z���N�g�ɂ��{���̏ꍇ�A�R�~���Z���N�g��ʂɖ߂�
		#pragma region ver0.00607���쎞�R�����g���R�[�h
		//commu_before_cs == FALSE ? GameMainCommunicationNext(HM[commu_number][cell_number].move_commu_number, FALSE) : GameCommuSelectNext();
#pragma endregion
		commu_before_cs == FALSE ? GameMainCommunicationNext(HM[commu_number][cell_number].move_commu_number, FALSE, 0) : GameCommuSelectNext();
	}
	// ���s�Z���R�}���h���waltenative�x�Ȃ�I������I�ׂ��Ԃɂ���
	else if (strcmp(HM[commu_number][cell_number].command, "altenative_2") == 0 || strcmp(HM[commu_number][cell_number].command, "altenative_3") == 0)
	{ 
		g_commustatus = COMMU_STATUS_ALTENATIVE;
		g_altenativenumber = strcmp(HM[commu_number][cell_number].command, "altenative_2") == 0 ? ALTENATIVE_NUMBER_2 : ALTENATIVE_NUMBER_3;
		// �I���������`��ɕK�v�ȏ������s��
		for (int i = 0; i < g_altenativenumber + 2; i++)
		{
			commu_altenative_string_line[i] = 1;																	// �I���������̍s��������������
			#pragma region ver0.00704���쎞�R�����g���R�[�h
			//for (int j = 0; j < STRBUF_ALTENATIVE_HEIGHT; j++) { sprintf_s(StringBufAltenative[i][j], 64, ""); }	// �����񏉊���
#pragma endregion
			// �����񏉊���
			for (int j = 0; j < STRBUF_ALTENATIVE_HEIGHT; j++)
			{
				// �O���[�o���ϐ���char����������������ۂ�sprintf_s�łȂ�0��������K�v������
				for (int k = 0; k < STRBUF_ALTENATIVE_WIDTH + 2; k++){StringBufAltenative[i][j][k] = 0;}
			}	
			GameMainCommunicationMojiAltenative(i);
		}
		// �I�������ɉ����Ċ֌W������W���Ē�`����
		GameMainCommunicationCoordinateSetting();
	}
	// �L���������G�ύX�`�F�b�N
	for (int i = 0; i < 3; i++)
	{
		#pragma region ver0.0072���쎞�R�����g���R�[�h
		//if (HM[commu_number][cell_number].character[i] != 0)
#pragma endregion
		if (HM[commu_number][cell_number].character[i] != 0)
		{
			// ����\������Z�b�g����
			g_commu_character_face[i] = CCF_NORMAL;

			#pragma region ver0.0021���쎞�R�����g���R�[�h
			// �i�L�����N�^�[�؂�ւ����@���s�����x����ւ��Ȃ�j���O�i����j�̃L�����N�^�[�摜����������
			//if (HM[commu_number][cell_number].character_change == 0)
#pragma endregion
			// �i�L�����N�^�[�؂�ւ����@���s�����x����ւ��ŁA�X�L�b�v���[�h�łȂ���΁j���O�i����j�̃L�����N�^�[�摜����������
			#pragma region ver0.007���쎞�R�����g���R�[�h
			//if (HM[commu_number][cell_number].character_change == 0 && g_commuauto != COMMU_AUTO_SKIP)
#pragma endregion
			if (HM[commu_number][cell_number].character_change != CCC_INSTANT && g_commuauto != COMMU_AUTO_SKIP)
			{
				commu_character_talk_limit[i] = 0;	// �����x����ւ��L�����ύX�̍ہA�����J�����ςȂ��ɂȂ�o�O�𒼂�����
				#pragma region ver0.0029���쎞�R�����g���R�[�h
				//if (commu_character[i] >= 2)
				//{
				//	LoadGameImageCharacterBody(commu_character[i] % 10, &commu_character_before[i]);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 10 - 1][commu_character[i] % 10][0][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 10 - 1][commu_character[i] % 10][0][DrawGameMainCommunicationMouseAnimation()], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_eyebrow[commu_character[i] / 10 - 1][commu_character[i] % 10][0][2], 255, DX_GRAPH_BLEND_NORMAL);
				//}
				//else{ DeleteGraph(commu_character_before[i]); }
				//// ����̃L�����N�^�[
				//if (HM[commu_number][cell_number].character[i] + 1 >= 2)
				//{
				//	int x = HM[commu_number][cell_number].character[i];
				//	LoadGameImageCharacterBody(x % 10, &commu_character_after[i]);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 10 - 1][x % 10][0][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 10 - 1][x % 10][0][DrawGameMainCommunicationMouseAnimation()], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_eyebrow[x / 10 - 1][x % 10][0][2], 255, DX_GRAPH_BLEND_NORMAL);
				//}
				//else{ DeleteGraph(commu_character_after[i]); }
#pragma endregion
				#pragma region ver0.00291���쎞�R�����g���R�[�h
				// �i�ߑ��͂߂���Ȃ�Q�����͂S�ŉ������j
				//if (commu_character[i] >= 2)	// ���݂͖��Ȃ����w2�x�ł����̂��͕s��
				//{
				//	LoadGameImageCharacterBody(commu_character[i] / 100 % 10, &commu_character_before[i], load_name[commu_character[i] / 1000 - 1], commu_character[i] / 10 % 10);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][DrawGameMainCommunicationMouseAnimation(i)], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_before[i], g_imghandles.character_eyebrow[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][2], 255, DX_GRAPH_BLEND_NORMAL);
				//}
				//else { DeleteGraph(commu_character_before[i]); }
				//// ����̃L�����N�^�[�i���������̏ꂵ�̂��̏����ɂȂ��Ă���\��������H�j
				//if (HM[commu_number][cell_number].character[i] + 1 >= 2)
				//{
				//	int x = HM[commu_number][cell_number].character[i];
				//	LoadGameImageCharacterBody(x / 100 % 10, &commu_character_after[i], load_name[x / 1000 - 1], x / 10 % 10);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][DrawGameMainCommunicationMouseAnimation(i)], 255, DX_GRAPH_BLEND_NORMAL);
				//	GraphBlend(commu_character_after[i], g_imghandles.character_eyebrow[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][2], 255, DX_GRAPH_BLEND_NORMAL);
				//}
#pragma endregion
				if (commu_character[i] >= 2)	// ���݂͖��Ȃ����w2�x�ł����̂��͕s��
				{
					LoadGameImageCharacterBody(commu_character[i] / 100 % 10, &commu_character_before[i], load_name[commu_character[i] / 1000 - 1], commu_character[i] / 10 % 10);
					GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
					//																																														commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2;
					GraphBlend(commu_character_before[i], g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][DrawGameMainCommunicationMouseAnimation(i)], 255, DX_GRAPH_BLEND_NORMAL);
					GraphBlend(commu_character_before[i], g_imghandles.character_eyebrow[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				}
				else { DeleteGraph(commu_character_before[i]); }
				// ����̃L�����N�^�[�i���������̏ꂵ�̂��̏����ɂȂ��Ă���\��������H�j
				if (HM[commu_number][cell_number].character[i] + 1 >= 2)
				{
					int x = HM[commu_number][cell_number].character[i];
					LoadGameImageCharacterBody(x / 100 % 10, &commu_character_after[i], load_name[x / 1000 - 1], x / 10 % 10);
					#pragma region ver0.0039���쎞�R�����g���R�[�h
					//GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2], 255, DX_GRAPH_BLEND_NORMAL);
#pragma endregion
					// ��
					int y = (commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= 3) ? commu_character_blink_limit[i] % 2 : 2;
					if (HM[commu_number][cell_number].character_face_etc[i] == 1) { y = 0; }
					else if (HM[commu_number][cell_number].character_face_etc[i] == 2) { y = 3; }
					GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][y], 255, DX_GRAPH_BLEND_NORMAL);

					GraphBlend(commu_character_after[i], g_imghandles.character_face[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][DrawGameMainCommunicationMouseAnimation(i)], 255, DX_GRAPH_BLEND_NORMAL);

					// ���сi����or�Ί���ڂȂ�0�ɂ���j
					#pragma region ver0.0039���쎞�R�����g���R�[�h
					//GraphBlend(commu_character_after[i], g_imghandles.character_eyebrow[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][2], 255, DX_GRAPH_BLEND_NORMAL);
#pragma endregion
					GraphBlend(commu_character_after[i], g_imghandles.character_eyebrow[x / 1000 - 1][x / 100 % 10][x / 10 % 10][x % 10][HM[commu_number][cell_number].character_face_etc[i] >= 1 ? 0 : 2], 255, DX_GRAPH_BLEND_NORMAL);
				}
				else { DeleteGraph(commu_character_after[i]); }
			}

			commu_character[i] = HM[commu_number][cell_number].character[i];
			#pragma region ver0.007���쎞�R�����g���R�[�h
			//if (HM[commu_number][cell_number].character_change == 0)
#pragma endregion
			if (HM[commu_number][cell_number].character_change != CCC_INSTANT)
			{
				//	�����x����ւ��p�̃t���[����
				int x = (HM[commu_number][cell_number].GetCC() == CCC_TRANSPARENCY_NORMAL) ? COMMU_CHARACTER_CHANGE_MAX : COMMU_CHARACTER_CHANGE_MAX_FAST;

				commu_mode_background = TRUE;	// �L�����N�^�[����ւ��������I���܂ő���ł��Ȃ��悤�ɂ���
				// �L�����؂�ւ��ɕK�v�ȃt���[�������Z�b�g����i�X�L�b�v���[�h�Ȃ�c��P�e�ɂ���j
				#pragma region ver0.00294���쎞�R�����g���R�[�h
				//commu_character_visibility_count = g_commuauto != COMMU_AUTO_SKIP ? COMMU_CHARACTER_CHANGE_MAX + 1 : 1;
#pragma endregion
				#pragma region ver0.007���쎞�R�����g���R�[�h
				//commu_character_visibility_count[i] = g_commuauto != COMMU_AUTO_SKIP ? COMMU_CHARACTER_CHANGE_MAX + 1 : 1;
#pragma endregion
				commu_character_visibility_count[i] = g_commuauto != COMMU_AUTO_SKIP ? x + 1 : 1;
			}
		}
		// ����\����m�F�E�ύX����iswitch���Ȃ�G���[�͋N���Ȃ��H�j
		//if (HM[commu_number][cell_number].character_face_etc[i] != 0) { HM[commu_number][cell_number].character_face_etc[i] == -1 ? g_commu_character_face[i] = CCF_NORMAL : g_commu_character_face[i] = HM[commu_number][cell_number].character_face_etc[i]; }
		switch (HM[commu_number][cell_number].character_face_etc[i])
		{
		case -1:					g_commu_character_face[i] = CCF_NORMAL;				break;
		case CCF_CLOSE_EYE:			g_commu_character_face[i] = CCF_CLOSE_EYE;			break;
		case CCF_CLOSE_EYE_SMILE:	g_commu_character_face[i] = CCF_CLOSE_EYE_SMILE;	break;
		default:																		break;
		}
	}
	// �L�����N�^�[�����ψꃂ�[�h�ύX�`�F�b�N
	if (HM[commu_number][cell_number].character_even_distance != 0){ commu_mode_distance = (HM[commu_number][cell_number].character_even_distance == 1 ? TRUE : FALSE); }
	// �w�i�ύX�`�F�b�N
	if (HM[commu_number][cell_number].background != 0)
	{
		if (cell_number != 0)
		{
			commu_mode_background = TRUE;											// �w�i���ς�肫��܂ő���ł��Ȃ��悤�ɂ���
			commu_background_visibility_count = COMMU_BACKGROUND_FLAME_MAX + 1;		// �w�i�؂�ւ��ɕK�v�ȃt���[�������Z�b�g����
			commu_background_before = commu_background;								// ���O�̔w�i���L������
			g_backgroundchange = HM[commu_number][cell_number].background_change;	// �w�i�ύX�^�C�v��������
		}
		if (cell_number == 75 - 2)
		{
			quit_game = TRUE;
			return;
		}
		if (HM[commu_number][cell_number].background == -1)
		{
			commu_background = 0;
			GlobalStaticSaveLoad::SetSamuneBackgroundID(0);	// �Z�[�u���ɃT���l����Ȃ��ۑ��ł���悤�ɂ��鏈��
		}
		else
		{ 
			// �o�O���p�̕ϐ�
			int x = (HM[commu_number][cell_number].background - 1 >= 0 ? HM[commu_number][cell_number].background - 1 : 0);
			commu_background = bgimage[x].Handle; 

			GlobalStaticSaveLoad::SetSamuneBackgroundID(x + 1);	// �Z�[�u���ɃT���l����Ȃ��ۑ��ł���悤�ɂ��鏈��
		}
	}
	// �a�f�l�ύX�`�F�b�N
	if (HM[commu_number][cell_number].bgm != 0)
	{
		// -1�Ȃ�BGM��~
		if (HM[commu_number][cell_number].bgm == -1){ MusicPlay(HM[commu_number][cell_number].bgm - 1); }
		else
		{
			MusicPlay(HM[commu_number][cell_number].bgm - 1); // �����ɑΉ�����BGM�ɕύX����
			// �a�f�l����\�����邽�߂ɕK�v�ȗv�f��������
			commu_bgm_name = bgm_name[HM[commu_number][cell_number].bgm - 1];
			commu_bgm_flame = -1;
		}
	}
	// �r�d�Đ��`�F�b�N�iSKIP���[�h�Ȃ�Đ����Ȃ��j
	#pragma region ver0.00393���쎞�R�����g���R�[�h
	//if (HM[commu_number][cell_number].se != 0){ SEPlay(HM[commu_number][cell_number].se - 1); }
#pragma endregion
	#pragma region ver0.017���쎞�R�����g���R�[�h
	//if (HM[commu_number][cell_number].se != 0 && g_commuauto != COMMU_AUTO_SKIP) { SEPlay(HM[commu_number][cell_number].se - 1); }
#pragma endregion
	if (HM[commu_number][cell_number].se != 0 && (g_commuauto != COMMU_AUTO_SKIP || HM[commu_number][cell_number].se == -1)) { SEPlay(HM[commu_number][cell_number].se - 1); }

	sprintf_s(String[0], 256, "%sE", HM[commu_number][cell_number].line);	// ��������
	/* �i�I�����\����ԂłȂ���΁j�䎌�`��Ɋւ���v�f������������---------*/
	if (g_commustatus != COMMU_STATUS_ALTENATIVE)
	{
		// ���z�e�L�X�g�o�b�t�@
		for (moji_i = 0; moji_i < STRBUF_HEIGHT; moji_i++)
		{
			for (moji_j = 0; moji_j < STRBUF_WIDTH + 2; moji_j++)
			{
				StringBuf[moji_i][moji_j] = 0;
			}
		}
		//�`�敶���ʒu
		CursorY = 0;
		CursorX = 0;
		// �Q�ƕ����ʒu
		SP = 0;	// �P�s�ڂ�
		CP = 0;	// �O����

		EndFlag = 0;	// �I���t���O
	}
	/*----------------------------------------------------------------------*/
	// �e�L�X�g���O
	text_log[TextLog::GetNIID()].Input();

	DebugLog(LogOutputType::CELL_CHARACTER);
}
// �R�~���I������
void GameMainCommunicationEnd()
{
	// �R�~���Z���N�g�ɂ��{���̏ꍇ�A�R�~���Z���N�g��ʂɖ߂�
	if (commu_before_cs == FALSE)
	{
		// ���̌��ł̋���
		if (GlobalStaticVariable::GetModeTrial() == FALSE)
		{
			switch (commu_number)
			{
			case static_cast<int>(CommuType::OP):	GameMainCommunicationNext(static_cast<int>(CommuType::TUTORIAL), FALSE, 0);	break;
			case static_cast<int>(CommuType::TUTORIAL):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::MEGURU0);
				GameMapNext();
				// �̌���0.01�̃f�[�^�łR���S�T�̃f�[�^�����[�h�����ەs����N���Ȃ��悤�ɂ��鏈�������˂Ă���
				if (game_week_number > GlobalStaticMap::GetWeekInitialValue()) { game_week_number--; }
				break;
			case static_cast<int>(CommuType::MEGURU0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::RINZE0);
				GameMapNext();
				game_week_number--;
				break;
			case static_cast<int>(CommuType::KOGANE0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::CHIYUKI0);
				GameMapNext();
				game_week_number--;
				break;
			case static_cast<int>(CommuType::JURI0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::DEFAULT);
				GameMapNext();
				break;
			case static_cast<int>(CommuType::RINZE0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::KOGANE0);
				GameMapNext();
				break;
			case static_cast<int>(CommuType::CHIYUKI0):
				CommuData::SetGMapUpperType(CommuData::MapUpperType::JURI0);
				GameMapNext();
				game_week_number--;
				break;
			case static_cast<int>(CommuType::FRIEND):			GameMainCommunicationNext(static_cast<int>(CommuType::TUTORIAL_END), FALSE, 0);	break;
			case static_cast<int>(CommuType::TUTORIAL_END):
				g_gamestate = GAME_TUTORIAL_END;
				ImgDataTutorialEnd::CountReset();
				MusicPlay(-2);
				break;
			default:
				#pragma region ver0.00904���쎞�R�����g���R�[�h
				//if (game_week_number == 17) { GameMainCommunicationNext(COMMU_TYPE_FRIEND, FALSE, 0); }
#pragma endregion
				if (game_week_number == 17)
				{
					// �R�~�������������^�C�~���O���T���Q�T�Ȃ�߂���t�����h�b�f�R�~�������I���ł���
					CommuData::SetGMapUpperType(CommuData::MapUpperType::FRIEND_CG_MEGURU);
					GameMapNext();
					game_week_number--;
				}
				else { GameMapNext(); }
				break;
			}
		}
		// �̌��ł̋���
		else
		{
			game_week_number--;	// �X�`���̌��łł̓J�����_�[�@�\�͕K�v�Ȃ�
			// ����̃R�~�����{�����I������{���t���O�𗧂Ă�
			switch (commu_number)
			{
			case static_cast<int>(CommuType::MEGURU5):			GlobalStaticMap::SetTrialCommuViewed(0, TRUE);	break;
			case static_cast<int>(CommuType::KOGANE_STILL):		GlobalStaticMap::SetTrialCommuViewed(1, TRUE);	break;
			case static_cast<int>(CommuType::JURI_STILL):		GlobalStaticMap::SetTrialCommuViewed(2, TRUE);	break;
			case static_cast<int>(CommuType::RINZE0):			GlobalStaticMap::SetTrialCommuViewed(3, TRUE);	break;
			case static_cast<int>(CommuType::CHIYUKI_STILL):	GlobalStaticMap::SetTrialCommuViewed(4, TRUE);	break;
			default:																							break;
			}

			BOOL x = TRUE;
			for (int i = 0; i < COMMU_CHARACTER_NUMBER; i++)
			{
				if (GlobalStaticMap::GetTrialCommuViewed(i) == FALSE) { x = FALSE; }
			}
			if(x == FALSE){ GameMapNext(); }
			// �X�`���̌��ŏI���R�~�����{�����I������̌��ł��I������
			else if (commu_number == static_cast<int>(CommuType::TUTORIAL_STILL_END))
			{
				g_gamestate = GAME_TUTORIAL_END;
				ImgDataTutorialEnd::CountReset();
				MusicPlay(-2);
			}
			// �S�Ă̓���R�~�����{�����I������X�`���̌��ŏI���R�~�����J�n����
			else{ GameMainCommunicationNext(static_cast<int>(CommuType::TUTORIAL_STILL_END), FALSE, 0); }
		}
	}
	else { GameCommuSelectNext(); }

	SEPlay(-2);	//�r�d���~����
}
// �I������I�񂾍ۂ̋��ʏ���
void GameMainCommunicationAltenative(int x)	// �I�����h�c
{
	int y = HM[commu_number][cell_number].altenative_jump[x] - 3;
	state::SetAlternativeMoveNumber(cell_number, y + 1);	// �Z�[�u�f�[�^�p���l�ɐ��l��ۑ�����
	cell_number = y;
	g_commustatus = COMMU_STATUS_NORMAL;
	SEPlay(static_cast<int>(SEData::IDName::SENTAKUSHI));
	GameMainCommunicationNextLine();
}
// �R�~����ʂŎg���I�����֌W�iand�A�C�R���j�̍��W���i�āj��`���鏈��
void GameMainCommunicationCoordinateSetting()
{
	#pragma region ver0.007���쎞�R�����g���R�[�h

	//float x = size_commu_altenative.x * bairitu / 2;																		// �摜�̒��S���獶�[�̂���
	//float y = bairitu * 150;																								// �I����y���W�x�_
	//commu_altenative_y_under = y + bairitu * size_commu_altenative.y * 2 / 3;												// ���I����y���W
	//commu_altenative_y_upper = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_y_under : y;					// �㑤�I����y���W�i�Q�����A�����Ɠ���y���W�ɂȂ�j
	//float z = bairitu * (size_commu_altenative.x + 54);																		// �R�����A���A�E�I�������Sx���W�́A��������̂���
	//commu_altenative_x[2] = screen_size_x / 2 - x + z;																		// �I�����Rx���W
	//commu_altenative_x[1] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_x[2] : screen_size_x / 2 - x - z;	// �I�����Qx���W
	//commu_altenative_x[0] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? screen_size_x / 2 - x - z : screen_size_x / 2 - x;	// �I�����Px���W
	//// �I���������񒆐Sx���W
	//float a = (float)(screen_size_x / 2);
	//commu_altenative_string_center_x[0] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? a - z : (float)(screen_size_x / 2);
	//commu_altenative_string_center_x[2] = a + z;
	//commu_altenative_string_center_x[1] = g_altenativenumber == ALTENATIVE_NUMBER_2 ? commu_altenative_string_center_x[2] : a - z;
#pragma endregion
	// �wauto�x�A�C�R���i���W�͉��j
	commu_coordinate_icon_auto_x = screen_size_x - bairitu * 48 - size_icon_auto.x;
	commu_coordinate_icon_auto_y = screen_size_y - bairitu * 375 - size_icon_auto.y;
	// �wSKIP�x�A�C�R���i���W�͉��j
	#pragma region ver0.0028���쎞�R�����g���R�[�h
	//commu_coordinate_icon_skip_y = screen_size_y - bairitu * 240 + size_icon_auto.y / 2;
#pragma endregion
	commu_coordinate_icon_skip_y = commu_coordinate_icon_auto_y + size_icon_auto.y * 1.5f;
	// �wSAVE�x�A�C�R���i���W�͉��j
	commu_coordinate_icon_save_y = commu_coordinate_icon_skip_y + size_icon_auto.y * 1.5f;
	// �wLOAD�x�A�C�R���i���W�͉��j
	commu_coordinate_icon_load_y = commu_coordinate_icon_save_y + size_icon_auto.y * 1.5f;
	// �wOPTION�x�A�C�R���i���W�͉��j
	commu_coordinate_icon_option_y = commu_coordinate_icon_load_y + size_icon_auto.y * 1.5f;
	// �wMENU�x�A�C�R��
	commu_coordinate_icon_menu_y = screen_size_y - bairitu * 48 - size_icon_auto.y;
	// �wTEXT OFF�x�A�C�R��
	commu_coordinate_icon_tf_x = bairitu * 15;
	// �e�L�X�g�p���O�i���݂̐��i�łȂ�N���b�N�ł��Ȃ��ʒu�ɒu���j
	//if(mode_debug == TRUE){image_icon_log.CoordinateSetting(commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y - size_icon_auto.y * 1.5f);}
	//else{ image_icon_log.CoordinateSetting2(-2048, -2048);}
	image_icon_log.CoordinateSetting(commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y - size_icon_auto.y * 1.5f);	// �o�b�N���O�p�wBACK�x
	image_icon_log_back.CoordinateSetting2(1825, 957);
	// �o�b�N���O�p���
	for (int i = 0; i < ImgDataHJ2::TEXT_LOG_ARROW_NUMBER; i++)
	{
		int x = i - 2 + (i < 2 ? 0 : 1);
		image_icon_text_log[i].CoordinateSetting2(WINDOW_SIZE_X / 2 + image_icon_text_log[0].GetSizeX() * 2 * x - image_icon_text_log[0].GetSizeX() / 2, 945);
	}
	// �o�b�N���O�p�e�L�X�g�E�B���h�E�i�����摜�𕡐���g���\��������̂�X���W�����ł����j
	float tl_ui_x = 27;
	for (int i = 0; i < ImgData2::LOG_TEXT_WINDOW_NUMBER; i++){image_log_text_window[i].CoordinateSetting2(tl_ui_x, 0);}
	// �e�L�X�g���O�p�L�����t�h
	for(int i = 0; i < ImgData2::IMC_NUMBER; i++){image_map_character[i].CoordinateSetting2(tl_ui_x, 0);}
}
// �R�~����ʂŕ�����`�悷�邽�߂ɍs������
//void GameMainCommunicationMoji()
void GameMainCommunicationMoji(BOOL x)	// �u���ɑS�Ă̕���\��������t���O
{
	/* ������`��p�e�X�g�R�[�h---------*/
	// �T�E���h�m�x����������`����s��
	// �������I���t���O���P�������ꍇ�͏��������Ȃ�
	// �i���O�\�����͏����𖳎�����j
	if (TextLog::GetMode() == FALSE)
	{
		do
		{
			if (EndFlag == 0)
			{
				char Moji = 0;

				// �{�^�������҂��t���O�������Ă����ꍇ�̓{�^�����������܂ł����ŏI��
				if (KeyWaitFlag == 1)
				{
					if (ProcessMessage() == 0 && CheckHitKeyAll() != 0) { KeyWaitFlag = 0; }	// �{�^����������Ă��������
				}
				else
				{
					// �����̕`��
					Moji = String[SP][CP];
					switch (Moji)
					{
					case '@':	// ���s����
						// ���s��������юQ�ƕ����ʒu��������߂�
						Kaigyou2();
						CP++;
						break;
					case 'B':	// �{�^�������҂�����
						// �{�^�����������܂ő҂�
						while (ProcessMessage() == 0 && CheckHitKeyAll() != 0) {}
						// �{�^�������҂��t���O�����Ă�
						KeyWaitFlag = 1;
						CP++;
						break;
					case 'E':	// �I������
						// �I���t���O�𗧂Ă邨��юQ�ƕ����ʒu����i�߂�
						EndFlag = 1;
						CP++;
						break;
					case 'C':	// �N���A����
						// ���z�e�L�X�g�o�b�t�@�����������ĕ`�敶���ʒu�������ʒu�ɖ߂�����юQ�ƕ����ʒu����i�߂�
						for (moji_i = 0; moji_i < STRBUF_HEIGHT; moji_i++)
						{
							for (moji_j = 0; moji_j < STRBUF_WIDTH + 2; moji_j++) { StringBuf[moji_i][moji_j] = 0; }
						}
						CursorY = 0;
						CursorX = 0;
						CP++;
						break;
					default:	// ���̑��̕���
						// �P�����̃o�C�g�����擾
						Bytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &String[SP][CP]);
						// �P�����e�L�X�g�o�b�t�@�ɑ��
						for (moji_i = 0; moji_i < Bytes; moji_i++) { StringBuf[CursorY][CursorX + moji_i] = String[SP][CP + moji_i]; }
						// �Q�ƕ����ʒu���P�����̃o�C�g�����i�߂�
						CP += Bytes;
						// �J�[�\�����ꕶ���̃o�C�g�����i�߂�
						CursorX += Bytes;
						// �e�L�X�g�o�b�t�@��������͂ݏo������s����
#pragma region ver0.0034���쎞�R�����g���R�[�h
//if (CursorX >= STRBUF_WIDTH){ Kaigyou2(); }
#pragma endregion
						if (CursorX > STRBUF_WIDTH) { Kaigyou2(); }

						break;
					}
					// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
					if (String[SP][CP] == '\0')
					{
						SP++;
						CP = 0;
					}
				}
			}
		} while (x == TRUE && EndFlag == 0);
	}
	/*----------------------------------*/
}
// �R�~����ʂőI�����p������`�悷�邽�߂ɍs������
void GameMainCommunicationMojiAltenative(int x)	// �w�肳�ꂽ�I����
{
	BOOL end = FALSE;
	// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^
	//int SP_A = 0;
	int CP_A = 0;
	// ���z��ʏ�ł̕����\���J�[�\���̈ʒu
	int CursorX_A = 0;
	int CursorY_A = 0;

	int y = 0;			// �i�v���[�v���p�e�X�g�ϐ�
	do
	{
		char Moji;

		// �����̕`��
		Moji = HM[commu_number][cell_number].altenative_message[x][CP_A];
		switch (Moji)
		{
		case '@':	// ���s����
			// ���s��������юQ�ƕ����ʒu��������߂�
			CursorY_A++;
			CursorX_A = 0;
			CP_A++;
			commu_altenative_string_line[x]++;	// �`����W�Q�ƂɎg����s�����J�E���g����
			break;
		//case 'E':	// �I������
		//	// �I���t���O�𗧂Ă邨��юQ�ƕ����ʒu����i�߂�
		//	EndFlag = 1;
		//	CP++;
		//	break;
		default:	// ���̑��̕���
			// �P�����̃o�C�g�����擾
			Bytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &HM[commu_number][cell_number].altenative_message[x][CP_A]);
			// �P�����e�L�X�g�o�b�t�@�ɑ��
			for (moji_i = 0; moji_i < Bytes; moji_i++){ StringBufAltenative[x][CursorY_A][CursorX_A + moji_i] = HM[commu_number][cell_number].altenative_message[x][CP_A + moji_i]; }
			// �Q�ƕ����ʒu���P�����̃o�C�g�����i�߂�
			CP_A += Bytes;
			// �J�[�\�����ꕶ���̃o�C�g�����i�߂�
			CursorX_A += Bytes;
			// �e�L�X�g�o�b�t�@��������͂ݏo������s����
			if (CursorX_A >= STRBUF_ALTENATIVE_WIDTH)
			{ 
				CursorY_A++;
				CursorX_A = 0;
			}
			break;
		}
		// �Q�ƕ�����̏I�[�܂ōs���Ă�����Q�ƕ������i�߂�
		if (HM[commu_number][cell_number].altenative_message[x][CP_A] == '\0'){ end = TRUE; }

		y++;
	} while (end == FALSE && y < 255);
}
// �R�~����ʂ̕`�揈��
void DrawGameMainCommunication()
{
	/* �w�i ---------*/
	#pragma region ver0.0022���쎞�R�����g���R�[�h
	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_background, TRUE);
#pragma endregion
	// �}�b�v�������������i���ݔw�i�̏u������ւ��@�\���Ȃ��̂Ŏ���́j
	#pragma region ver0.00904���쎞�R�����g���R�[�h
	//if (commu_number == COMMU_TYPE_TUTORIAL) 
#pragma endregion
	if (commu_number == static_cast<int>(CommuType::TUTORIAL))
	{
		int x = cell_number + 2;
		if (x == 28) { commu_background = bgimage[44].GetHandle(); }
		else if(x == 122){ commu_background = bgimage[43].GetHandle(); }
	}

	DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, (g_backgroundchange != BACKGROUND_CHANGE_VISIBILITY && commu_background_visibility_count > COMMU_BACKGROUND_FLAME_MAX / 2) ? commu_background_before : commu_background, TRUE);

	ImgDataBGTutorial::DIMCheck(cell_number + 2);
	#pragma region ver0.00904���쎞�R�����g���R�[�h
	//if(commu_number == COMMU_TYPE_TUTORIAL)
#pragma endregion
	if (commu_number == static_cast<int>(CommuType::TUTORIAL))
	{
		int x = cell_number + 2;
		if (x <= 55 || x >= 62) { tutorial_image[0].DrawImageTutorial(ImgDataBGTutorial::GetScreenY()); }
		if (ImgDataBGTutorial::GetDrawImageNumber() > 0) { tutorial_image[ImgDataBGTutorial::GetDrawImageNumber()].DrawImageTutorial(ImgDataBGTutorial::GetScreenY()); }
	}
	/*---------------*/
	#pragma region ver0.0022���쎞�R�����g���R�[�h
	//if (g_backgroundchange == BACKGROUND_CHANGE_VISIBILITY)
	//{
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_background_visibility_count * 255 / COMMU_BACKGROUND_FLAME_MAX);
	//	DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_background_before, TRUE);
	//}
	//else
	//{
	//	int background_color = g_backgroundchange == BACKGROUND_CHANGE_BLACKOUT ? GetColor(0, 0, 0) : GetColor(255, 255, 255);
	//	if (commu_background_visibility_count > COMMU_BACKGROUND_FLAME_MAX / 2){ DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_background_before, TRUE); }	// �u���b�N�i�z���C�g�j�A�E�g������܂Œ��O�̔w�i���f��
	//	int x = (COMMU_BACKGROUND_FLAME_MAX / 2 - commu_background_visibility_count) * (COMMU_BACKGROUND_FLAME_MAX / 2 - commu_background_visibility_count < 0 ? -1 : 1);
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COMMU_BACKGROUND_FLAME_MAX / 2 - x) * 255 / (COMMU_BACKGROUND_FLAME_MAX / 2));
	//	DrawBox(0, 0, screen_size_x, screen_size_y, background_color, TRUE);
	//}
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#pragma endregion

	#pragma region ver0.0021���쎞�R�����g���R�[�h
	// �w��̕ϐ���60�ȏ�ɂȂ����當���������o��
	//if (commu_message_point >= 60)
#pragma endregion
	// �w��̕ϐ���60�ȏ�ɂȂ��Ă�����蕶���������o��
	while (commu_message_point >= 60)
	{
		commu_message_point -= 60;
		GameMainCommunicationMoji(FALSE);
	}
	// �L���������G
	// �L�������Q�l���L�����ԋϓ����I�������ׂ�
	BOOL same_distance_left = FALSE;	// �����̃L�������������܂��Ă邩���ʂ���t���O
	int draw_character_now = 0;
	for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
	{
		if (commu_character[i] > 0){ draw_character_now++; }
	}

	#pragma region ver0.007���쎞�R�����g���R�[�h
	//for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
#pragma endregion
	for (int j = 0; j < COMMU_CHARACTER_MAX; j++)
	{
		// �^�񒆂̃L�������őO�ʂɒu�����߂̕ϐ�
		int i = 0;
		if (j == 1) { i = 2; }
		else if (j == 2) { i = 1; }

		#pragma region ver0.00604���쎞�R�����g���R�[�h
		//float x = (i * 630 - 630.0f) * bairitu;	// �L�����̔z�u�ꏊ�ɂ���ĕς��x���W
#pragma endregion
		float x = (i * COMMU_CHARACTER_SPACE - COMMU_CHARACTER_SPACE) * bairitu;	// �L�����̔z�u�ꏊ�ɂ���ĕς��x���W
		// �L�������Q�l���L�����ԋϓ����I���Ȃ狭���I�ɍ��W��ς���
		if (draw_character_now == 2 && commu_mode_distance == TRUE)
		{ 
			x = (same_distance_left == FALSE ? -1 : 1) * 360.0f * bairitu;
			if (same_distance_left == FALSE){ same_distance_left = TRUE; }
		}	
		#pragma region ver0.0021���쎞�R�����g���R�[�h
		//if (commu_character_visibility_count >= 1)
#pragma endregion
		#pragma region ver0.00294���쎞�R�����g���R�[�h
		//if (commu_character_visibility_count >= 1 && g_commuauto != COMMU_AUTO_SKIP)	// �X�L�b�v���[�h�̏ꍇ�A���O����̂��ߓ���ւ��p�̉摜���쐬���Ȃ��悤�ɂ��Ă���̂ł��̏������΂�
		//{
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_character_visibility_count * 255 / COMMU_CHARACTER_CHANGE_MAX);
		//	DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_before[i], TRUE);
		//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COMMU_CHARACTER_CHANGE_MAX - commu_character_visibility_count) * 255 / COMMU_CHARACTER_CHANGE_MAX);
		//	DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_after[i], TRUE);
		//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//}
#pragma endregion
		if (commu_character_visibility_count[i] >= 1 && g_commuauto != COMMU_AUTO_SKIP)	// �X�L�b�v���[�h�̏ꍇ�A���O����̂��ߓ���ւ��p�̉摜���쐬���Ȃ��悤�ɂ��Ă���̂ł��̏������΂�
		{
			// �����x����ւ��J�n���̃t���[����
			int y = (HM[commu_number][cell_number].GetCC() == CCC_TRANSPARENCY_NORMAL) ? COMMU_CHARACTER_CHANGE_MAX : COMMU_CHARACTER_CHANGE_MAX_FAST;

			#pragma region ver0.007���쎞�R�����g���R�[�h
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_character_visibility_count[i] * 255 / COMMU_CHARACTER_CHANGE_MAX);
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_before[i], TRUE);
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COMMU_CHARACTER_CHANGE_MAX - commu_character_visibility_count[i]) * 255 / COMMU_CHARACTER_CHANGE_MAX);
#pragma endregion
			// 255�ɋ߂��قǕ`�悵�悤�Ƃ��Ă�����̂��Z���`�悳���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_character_visibility_count[i] * 255 / y);
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_before[i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (y - commu_character_visibility_count[i]) * 255 / y);
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_character_after[i], TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (commu_character[i] >= 1)
		{
			#pragma region ver0.0029���쎞�R�����g���R�[�h
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_body[commu_character[i] / 10 - 1][commu_character[i] % 10][0], TRUE);
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 10 - 1][commu_character[i] % 10][0][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], TRUE);
			//// ���сi�e�X�g�j
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_eyebrow[commu_character[i] / 10 - 1][commu_character[i] % 10][0][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], TRUE);

			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 10 - 1][commu_character[i] % 10][0][DrawGameMainCommunicationMouseAnimation()], TRUE);
#pragma endregion
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_body[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10], TRUE);
			#pragma region ver0.00291���쎞�R�����g���R�[�h
			////																																																							 �܂΂��������I����܂ł̃t���[������1�ȏ㊎�A18�i6�~3�j�ȉ��Ȃ�A										 �c��t���[������5�𑫂������l��6�Ŋ�������A2�Ŋ������ۂ̗]���Ԃ��A����Ă����2��Ԃ��i�t���[����19�ȏ�Ȃ�J�����ςȂ��j	
			//DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], TRUE);

#pragma endregion
			int y = (commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2;	// �ڃp�[�c�Ɏg���ϐ��i�܂΂��������I����܂ł̃t���[������1�ȏ㊎�A18�i6�~3�j�ȉ��Ȃ�A�c��t���[������5�𑫂������l��6�Ŋ�������A2�Ŋ������ۂ̗]���Ԃ��A����Ă����2��Ԃ��i�t���[����19�ȏ�Ȃ�J�����ςȂ��j�j
			if (g_commu_character_face[i] == CCF_CLOSE_EYE_SMILE && y == 0) { y = 3; }																																					// ����\��w�Ί���ځx�Ȃ�ʏ�̕��ڂ̎��ɍ����ւ���
			for (int k = 0; k < 3; k++)
			{
				if(commu_character[k] < -1000 || commu_character[k] >= 10000)
				{
					quit_game = TRUE;
					return;
				}
			}
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][y], TRUE);

			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_eyebrow[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][(commu_character_blink_limit[i] >= 1 && commu_character_blink_limit[i] <= COMMU_EYE_ANIMATION_FLAME * 3) ? (commu_character_blink_limit[i] + COMMU_EYE_ANIMATION_FLAME - 1) / COMMU_EYE_ANIMATION_FLAME % 2 : 2], TRUE);	// ���сi�e�X�g�j
			DrawExtendGraphF(x, 0, x + WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.character_face[commu_character[i] / 1000 - 1][commu_character[i] / 100 % 10][commu_character[i] / 10 % 10][commu_character[i] % 10][DrawGameMainCommunicationMouseAnimation(i)], TRUE);
		}
	}
	// �R�~���I�v�V�����A�C�R��
	//DrawExtendGraphF(screen_size_x - (45 * bairitu) - size_commu_option.x * bairitu, screen_size_y - 45 * bairitu - size_commu_option.y * bairitu, screen_size_x - 45 * bairitu, screen_size_y - bairitu * 45, g_imghandles.icon_commu_option, TRUE);	

	if (g_backgroundchange == BACKGROUND_CHANGE_VISIBILITY)
	{
		// �����x����ւ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, commu_background_visibility_count * 255 / COMMU_BACKGROUND_FLAME_MAX);
		DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, commu_background_before, TRUE);
	}
	else
	{
		// �u���b�N�A�E�g�A�z���C�g�A�E�g
		int background_color = g_backgroundchange == BACKGROUND_CHANGE_BLACKOUT ? GetColor(0, 0, 0) : GetColor(255, 255, 255);
		int x = (COMMU_BACKGROUND_FLAME_MAX / 2 - commu_background_visibility_count) * (COMMU_BACKGROUND_FLAME_MAX / 2 - commu_background_visibility_count < 0 ? -1 : 1);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (COMMU_BACKGROUND_FLAME_MAX / 2 - x) * 255 / (COMMU_BACKGROUND_FLAME_MAX / 2));
		DrawBox(0, 0, screen_size_x, screen_size_y, background_color, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �R�~���I����
	if (g_commustatus == COMMU_STATUS_ALTENATIVE)
	{
		// �I�������̂t�h�ȊO�̂��̂��Â�����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		#pragma region ver0.007���쎞�R�����g���R�[�h
		//DrawExtendGraphF(commu_altenative_x[0], commu_altenative_y_upper, commu_altenative_x[0] + size_commu_altenative.x * bairitu, commu_altenative_y_upper + size_commu_altenative.y * bairitu, g_imghandles.altenative[0], TRUE);
		//DrawExtendGraphF(commu_altenative_x[1], commu_altenative_y_under, commu_altenative_x[1] + size_commu_altenative.x * bairitu, commu_altenative_y_under + size_commu_altenative.y * bairitu, g_imghandles.altenative[1], TRUE);
		//if (g_altenativenumber == ALTENATIVE_NUMBER_3){ DrawExtendGraphF(commu_altenative_x[2], commu_altenative_y_under, commu_altenative_x[2] + size_commu_altenative.x * bairitu, commu_altenative_y_under + size_commu_altenative.y * bairitu, g_imghandles.altenative[2], TRUE); }
#pragma endregion		
		for (int i = 0; i < g_altenativenumber + 2; i++)
		{
			hjimage_alternative[i].DrawImage();
			// �I������������P�s���ɒ�������������ŕ`�悷��
			#pragma region ver0.007���쎞�R�����g���R�[�h
//for (int j = 0; j < commu_altenative_string_line[i]; j++){ DrawFormatStringFToHandle(commu_altenative_string_center_x[i] - GetDrawFormatStringWidthToHandle(g_font3, StringBufAltenative[i][j]) / 2, (i == 0 ? commu_altenative_y_upper : commu_altenative_y_under) + bairitu * size_commu_altenative.y / 2 - bairitu * FONT_SIZE_ORIGINAL / 2 - (commu_altenative_string_line[i] - 1) * FONT_SIZE_ORIGINAL / 2 + j * FONT_SIZE_ORIGINAL, GetColor(0, 0, 0), g_font3, StringBufAltenative[i][j]); }
#pragma endregion
			#pragma region ver0.00704���쎞�R�����g���R�[�h
			//for (int j = 0; j < commu_altenative_string_line[i]; j++) { DrawFormatStringFToHandle(commu_altenative_string_center_x[i] - GetDrawFormatStringWidthToHandle(g_font_commu_line, StringBufAltenative[i][j]) / 2, (i == 0 ? commu_altenative_y_upper : commu_altenative_y_under) + bairitu * hjimage_alternative[0].size_y / 2 - bairitu * FONT_SIZE_ORIGINAL_COMMU_LINE / 2 - (commu_altenative_string_line[i] - 1) * FONT_SIZE_ORIGINAL_COMMU_LINE / 2 + j * FONT_SIZE_ORIGINAL_COMMU_LINE, GetColor(0, 0, 0), g_font_commu_line, StringBufAltenative[i][j]); }
#pragma endregion
			//																																																				��{Y���W�A																			�I�����̒��S�Ɋ񂹂鐔�l						�t�H���g�T�C�Y�����炷���l																																						
			for (int j = 0; j < commu_altenative_string_line[i]; j++) { DrawFormatStringFToHandle(commu_altenative_string_center_x[i] - GetDrawFormatStringWidthToHandle(g_font_commu_line, StringBufAltenative[i][j]) / 2, (i == 0 ? AlternativeCoordinate::GetYUpper() : AlternativeCoordinate::GetYUnder()) + /*bairitu **/ hjimage_alternative[0].size_y / 2 - FONT_SIZE_ORIGINAL_COMMU_LINE / 2 * bairitu - (commu_altenative_string_line[i] - 1) * FONT_SIZE_ORIGINAL_COMMU_LINE / 2 * bairitu + j * FONT_SIZE_ORIGINAL_COMMU_LINE * bairitu, GetColor(0, 0, 0), g_font_commu_line, StringBufAltenative[i][j]); }
		}
	}
	if (commu_mode_text_off == FALSE && TextLog::GetMode() == FALSE)
	{
		#pragma region ver0.0042���쎞�R�����g���R�[�h
		// �e�L�X�g�E�B���h�E�i�����x�e�X�g���j
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 90 * 255 / 100);
		//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, g_imghandles.text_window, TRUE);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#pragma endregion
		/* �e�L�X�g�E�B���h�E ---------*/
		int x[2] = {0, 0};
		for (int i = 0; i < 2; i++)
		{
			char c[256] = "";	// �䎌��
			if (i == 0) { sprintf_s(c, 256, HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name); }
			else { sprintf_s(c, 256, HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2); }
			if (strcmp(c, "�߂���") == 0 || strcmp(c, "����") == 0 || strcmp(c, "����") == 0 || strcmp(c, "�z��") == 0 || strcmp(c, "���") == 0)
			{
				int y = 0;
				x[i] = 1; 
			}
			else if (strcmp(c, "��l��") == 0) { x[i] = 2; }
			else if (strcmp(c, "�͂Â�") == 0) { x[i] = 3; }
			else if (strcmp(c, "�Z��") == 0) { x[i] = 4; }
			else if (strcmp(c, "") != 0) { x[i] = 5; }
		}
		// �R�}���h���wtext_window_color�x�Ȃ�R�}���h�p�̒l�ɉ����ċ����I�ɐF��ς���
		if(strcmp(HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].GetCommand(), "text_window_color") == 0)
		{
			switch (HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].GetCommandNumber())
			{
			case 2:		DrawTextWindow(1);	break;
			case 3:		DrawTextWindow(2);	break;
			case 4:		DrawTextWindow(3);	break;
			default:	DrawTextWindow(0);	break;
			}			
		}
		else if (x[0] == 1 || x[1] == 1) { DrawTextWindow(2); }	// �q���C���̖��O������΃s���N
		else if (x[0] == 2 || x[1] == 2) { DrawTextWindow(1); }	// ��l���̖��O������ΐ��F
		else if (x[0] == 3 || x[1] == 3) { DrawTextWindow(3); }	// �͂Â��̖��O������Η�
		else if (x[0] == 4 || x[1] == 4) { DrawTextWindow(0); }	// �Z���̖��O���̂���ΊD�F
		else if (x[0] == 5 || x[1] == 5) { DrawTextWindow(3); }	// ���u�̖��O���̂���Η�
		else { DrawTextWindow(1); }								// ���O���Ȃ��n�̕��̎��Ȃǂ͐��F
		/*-----------------------------*/
		// �䎌��A�䎌�i�I�����o�����͂P�O�̑䎌�ɂȂ�j
		#pragma region ver0.0111���쎞�R�����g���R�[�h
		//DrawFormatStringFToHandle(bairitu * 270, bairitu * 726, GetColor(20, 20, 20), g_font_commu_name, "%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name);
		////DrawFormatStringFToHandle(bairitu * 270, bairitu * 726, GetColor(20, 20, 20), g_font_commu_name, "%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name);
		////if (HM[commu_number][cell_number].name2 != NULL){ DrawFormatStringFToHandle(bairitu * 240 + GetDrawFormatStringWidthToHandle(g_font3, HM[commu_number][cell_number].name), bairitu * 720, GetColor(0, 0, 0), g_font3, "�E%s", HM[commu_number][cell_number].name2); }
		////if (HM[commu_number][cell_number].name2[0] != NULL){ DrawFormatStringFToHandle(bairitu * 240 + GetDrawFormatStringWidthToHandle(g_font3, HM[commu_number][cell_number].name), bairitu * 720, GetColor(0, 0, 0), g_font3, "�E%s", HM[commu_number][cell_number].name2); }	// �������������łȂ��Ƃ��܂������Ȃ�
		//if (HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2[0] != NULL){ DrawFormatStringFToHandle(bairitu * 270 + GetDrawFormatStringWidthToHandle(g_font_commu_name, "%s",HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name), bairitu * 726, GetColor(0, 0, 0), g_font_commu_name, "�E%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2); }	// �������������łȂ��Ƃ��܂������Ȃ�
#pragma endregion
		if (commu_number >= 0)
		{
			DrawFormatStringFToHandle(bairitu * 270, bairitu * 726, GetColor(20, 20, 20), g_font_commu_name, "%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name);
			// name2[0] = name2��1�o�C�g��
			if (HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2[0] != NULL) { DrawFormatStringFToHandle(bairitu * 270 + GetDrawFormatStringWidthToHandle(g_font_commu_name, "%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name), bairitu * 726, GetColor(0, 0, 0), g_font_commu_name, "�E%s", HM[commu_number][cell_number + (g_commustatus != COMMU_STATUS_ALTENATIVE ? 0 : -1)].name2); }	// �������������łȂ��Ƃ��܂������Ȃ�
		}
		// �e�L�X�g�o�b�t�@�̕`��
		for (moji_i = 0; moji_i < STRBUF_HEIGHT; moji_i++)
		{ 
			// �����̉e
			//DrawFormatStringFToHandle(bairitu * (255 + 1.5f), moji_i * bairitu * FONT_SIZE_ORIGINAL_COMMU_LINE * 1.5f + bairitu * (840 + 1.5f), GetColor(40, 40, 40), g_font_commu_line, StringBuf[moji_i]);
			// ����
			DrawFormatStringFToHandle(bairitu * 255, moji_i * bairitu * FONT_SIZE_ORIGINAL_COMMU_LINE * 1.5f + bairitu * 840, GetColor(20, 20, 20), g_font_commu_line, StringBuf[moji_i]); 
		}
	}
	// �������t�h
	else if(commu_mode_text_off == TRUE)
	{
		#pragma region ver0.0072���쎞�R�����g���R�[�h
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		//bgimage_sukashi.DrawImage();
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
#pragma endregion
		bgimage_sukashi.DrawImage();
	}
	// �a�f�l���i��`���ԁj
	float bgm_y = (commu_bgm_flame >= 20 && commu_bgm_flame < 160) ? 0 : commu_bgm_flame - 90.0f;
	if (bgm_y >= 1){ bgm_y *= -1; }
	if (bgm_y <= -1){ bgm_y += 70; }
	//if (commu_bgm_name != NULL){ DrawFormatStringFToHandle(0, bgm_y * (FONT_SIZE_ORIGINAL * screen_size_y / WINDOW_SIZE_Y) / 20, GetColor(255, 255, 255), g_font3, commu_bgm_name); }
	// ���w�O�R�~���B�e���͔�\���ɂ������
	if ((debug_entrance_before == FALSE && commu_mode_text_off == FALSE) && (TextLog::GetMode() == FALSE))
	{
		// �E��́wTITLE�x
		//DrawStringFToHandle(screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * COMMU_MESSEAGE_TITLE_Y, "TITLE", DrawTitleStringColor(screen_size_x - GetDrawStringWidthToHandle("TITLE", 5, g_font3) - bairitu * 100, bairitu * COMMU_MESSEAGE_TITLE_Y, GetDrawStringWidthToHandle("TITLE", 5, g_font3), bairitu * FONT_SIZE_ORIGINAL), g_font3);

		if (commu_mode_menu == TRUE)
		{
			// �wLOG�x�A�C�R��
			image_icon_log.DrawImage();
			// �wauto�x�A�C�R��
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_auto_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_auto_y + size_icon_auto.y, g_commuauto != COMMU_AUTO_ON ? g_imghandles.icon_auto[0] : g_imghandles.icon_auto[1], TRUE);
			// �wSKIP�x�A�C�R��
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_skip_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_skip_y + size_icon_auto.y, g_commuauto != COMMU_AUTO_SKIP ? g_imghandles.icon_skip[0] : g_imghandles.icon_skip[1], TRUE);
			// �wSAVE�x�A�C�R��
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_save_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE);
			// �wLOAD�x�A�C�R��
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_load_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_load_y + size_icon_auto.y, g_imghandles.icon_load[0], TRUE);
			// �wOPTION�x�A�C�R��
			DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_option_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_option_y + size_icon_auto.y, image_icon_option.Handle, TRUE);
		}
		// �wMENU�x�A�C�R���i���摜�j
		DrawExtendGraphF(commu_coordinate_icon_auto_x, commu_coordinate_icon_menu_y, commu_coordinate_icon_auto_x + size_icon_auto.x, commu_coordinate_icon_menu_y + size_icon_auto.y, g_imghandles.icon_menu[commu_mode_menu], TRUE);
		// �wTEXT OFF�x�A�C�R��
		DrawExtendGraphF(commu_coordinate_icon_tf_x, commu_coordinate_icon_menu_y, commu_coordinate_icon_tf_x + size_icon_text_off.x, commu_coordinate_icon_menu_y + size_icon_text_off.y, g_imghandles.icon_text_off, TRUE);
	}
	// �e�L�X�g���O
	if (TextLog::GetMode() == TRUE) { TextLog::Draw(); }
}
// �e�L�X�g�E�B���h�E��`�悷��
void DrawTextWindow(int x)	// �E�B���h�E�̐F
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (100 - text_window_clear_percentage) * 255 / 100);
	#pragma region ver0.00605���쎞�R�����g���R�[�h
	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, image_text_window[0][0].Handle, TRUE);
	//DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, image_text_window[1][0].Handle, TRUE);
#pragma endregion
	DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, image_text_window[0][x].Handle, TRUE);
	DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu, WINDOW_SIZE_Y * bairitu, image_text_window[1][x].Handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
// �`�悷����p�N�̉摜�𔻕ʂ���
int DrawGameMainCommunicationMouseAnimation(int i)	// ����L�����N�^�[�̈ʒu
{
	int x = 3;
	switch (commu_character_talk_limit[i] / COMMU_MOUSE_ANIMATION_FLAME % COMMU_MOUSE_ANIMATION_NUMBER)
	{
	case 0: x = 3;															break;
	case 1: x = 4;															break;
	case 2: x = 5;															break;
	case 3: x = 4;															break;
	case 4: x = 5;															break;
	case 5: x = 4;															break;
	case 6: x = 3;	if (EndFlag == 1){ commu_character_talk_limit[i] = 0; }	break;	// ���ɑ䎌���I����Ă���ꍇ�͌����J���Ȃ��悤�ɂ���
	case 7: x = 5;															break;
	case 8: x = 4;															break;
	case 9: x = 5;															break;
	case 10: x = 4;															break;
	case 11: x = 5;															break;
	case 12: x = 4;															break;
	default:																break;
	}

	#pragma region ver0.00291���쎞�R�����g���R�[�h
	//return x;
#pragma endregion
	return x + CHARACTER_GRAPH_EYE_NUMBER - 3;
}
