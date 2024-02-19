#include "gamesaveload.h"
#include <string>


SaveLoadBeforeMode g_sl_bm_status = SL_BEFORE_TITLE;



float sl_coordinate_mode_icon_x = 0;						// �i���[�h�ړ��n�A�C�R��x���W
float sl_coordinate_icon_save_y = 0;						// �wSAVE�x�A�C�R��y���W
float sl_coordinate_icon_load_y = 0;						// �wLOAD�x�A�C�R��y���W
float sl_coordinate_icon_back_y = 0;						// �wBACK�x�A�C�R��y���W
float sl_coordinate_icon_title_y = 0;						// �wTITLE�x�A�C�R��y���W
float sl_coordinate_icon_exit_y = 0;						// �wEXIT�x�A�C�R��y���W
float sl_coordinate_icon_sf_page_x[SL_FILE_PAGE_NUMBER];	// �e�Z�[�u�t�@�C���y�[�W�̍��[x���W
float sl_coordinate_icon_sf_page_y = 0;						// �Z�[�u�t�@�C���y�[�W�̏�[y���W
float sl_coordinate_icon_sf_x[6];							// �e�Z�[�u�t�@�C���̍��[x���W
float sl_coordinate_icon_sf_y[6];							// �e�Z�[�u�t�@�C���̏�[y���W

//����P�ϐ�
bool cft_save = FALSE;                                   //�Z�[�u���[�h�؂�ւ�
bool cft_load = FALSE;                                   //���[�h���[�h�؂�ւ�
bool exit_switch = FALSE;                                   //EXIT���[�h����
bool CallCheckMsg;                                          //�m�F���b�Z�[�W�Ăяo��
bool cft_checkmsgYes = FALSE;                               //�m�F���b�Z�[�W�u�͂��v
bool cft_checkmsgNo = FALSE;                                //�m�F���b�Z�[�W�u�������v
bool checkmsg = FALSE;		                                //�m�F���b�Z�[�W����
bool cft_savefile_page = FALSE;                             //�Z�[�u�t�@�C���y�[�W��ύX����
bool cft_savefile_sl = FALSE;                               //�wSAVE�xor�wLOAD�x���s��

float chk_coordinate_yes_x = 0;	                        //�m�F���b�Z�[�W�w�͂��x�I����x���W
float chk_coordinate_yes_y = 0;	                        //�m�F���b�Z�[�W�I����y���W
float chk_coordinate_no_x = 0;	                        //�m�F���b�Z�[�W�w�������x�I����x���W
int temp_font3 = 0;                                     //���t�H���g
int savefile_page =0;                                   //���݂̃Z�[�u�t�@�C���y�[�W
int savefile_sl = 0;                                    //�I�𒆂̃Z�[�u�t�@�C��
int savefile_page_check = 0;                            //�N���b�N�𗣂������W�Ńy�[�W���ς���Ă��܂����ۂ̑΍�
int savefile_sl_check = 0;
int temp = 0;
int  savedata_time[2];
std::string msg_text = "�Z�Z���܂���?";
char *display_time;

BOOL mode_save = TRUE;	// �Z�[�uor���[�h��Ԃ𔻕ʂ���
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfsl=click_flag_save_load�j
//BOOL cfsl_;		// 
// �Z�[�u�E���[�h��ʈڍs����
void GameSaveLoadNext(BOOL x, SaveLoadBeforeMode y)	// �Z�[�uor���[�h�̃t���O,�Z�[�uor���[�h��Ԉڍs�O�̏��
{
	g_gamestate = GAME_SAVELOAD;
	mode_save = x;
	g_sl_bm_status = y;
}
// GAME_SAVELOAD��Ԃ̃��C������
void GameSaveLoad()
{
	if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE;}
	//GameMainCommunicationControl();
	

	
	if (CallCheckMsg == FALSE) { GameSaveLoadControl(); }
		DrawGameSaveLoad();
	if (CallCheckMsg == TRUE) {
		CheckMessage();
		if (checkmsg == TRUE) {
			if (exit_switch == TRUE) { quit_game = TRUE; }
			if (mode_save == TRUE) { GameSave(savefile_sl); }
			if (mode_save == FALSE) { GameLoad(savefile_sl); }
			checkmsg = FALSE;
			CallCheckMsg = FALSE;
		}


	}
}
// �Z�[�u���[�h��ʑ��쏈��
void GameSaveLoadControl()
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
				//if (ClickFlagCheckF(ClickX, ClickY, , , , , TRUE, FALSE) == TRUE) { cfsl_ = TRUE; }
				
				if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }
				else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_save = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_load = TRUE; }
				if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }
				else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_exit_main_commu = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y,size_icon_auto.x ,size_icon_auto.y , TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_quit_game = TRUE; }
				// �Z�[�u�t�@�C���y�[�W�A�C�R��(�������������蔻�肨������)
				for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) { 
					if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[i] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, TRUE, FALSE) == TRUE)
					{
						cft_savefile_page = TRUE;
						savefile_page_check = i;
					}
				}
				for (int i = 0; i < SL_FILE_NUMBER; i++) {
					if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y,  TRUE, FALSE) == TRUE)
					{
						cft_savefile_sl = TRUE;
						savefile_sl_check = i;

					}
				}

			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }
				else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, FALSE, cft_save) == TRUE) {  mode_save = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, FALSE, cft_load) == TRUE) { mode_save = FALSE; }
				if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }
				else if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, FALSE, cft_exit_main_commu) == TRUE) { GameMainCommunicationNext(0); }
				if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y, size_icon_auto.x, size_icon_auto.y, FALSE, cfc_move_title) == TRUE) { GameTitleNext(); }
				if ((ClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, size_icon_auto.x, size_icon_auto.y, FALSE, cft_quit_game) == TRUE)){
					CallCheckMsg=TRUE; 
					exit_switch = TRUE;
				}
				for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) {
					if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[i] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, FALSE, cft_savefile_page) == TRUE)
					{
						if (i == savefile_page_check) {
							cft_savefile_page = TRUE;
							savefile_page = i;
						}
					}
				}
				for (int i = 0; i < SL_FILE_NUMBER; i++) {
					if (ClickFlagCheckF(ClickX, ClickY, sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, FALSE, cft_savefile_sl) == TRUE)
					{
						cft_savefile_sl = TRUE;
						CallCheckMsg = TRUE;
						exit_switch = FALSE;
						savefile_sl = i;
						if (commu_save_data[i+(savefile_page*5)].play_second <1){
							if (mode_save == FALSE) { CallCheckMsg = FALSE; }
							
							}
					}
				}
				//if (ClickFlagCheckF(ClickX, ClickY, , , , , FALSE, cfsl_) == TRUE) { }
				// �S�Ẵt���O��߂�
				//cfsl_ = FALSE;
				cft_save = FALSE;               //�Z�[�u���[�h�؂�ւ�
				cft_load = FALSE;               //���[�h���[�h�؂�ւ�
				cft_exit_main_commu = FALSE;	// �R�~����ʂɈړ�
				cfc_move_title = FALSE;			// �^�C�g����ʂֈړ�
				cft_quit_game = FALSE;			// �Q�[�����I��
				cft_savefile_page = FALSE;      //�Z�[�u�t�@�C���y�[�W��ύX����
				cft_savefile_sl = FALSE;        //�wSAVE�xor�wLOAD�x���s��
									// 
			}
		}
	}
}
// �����ɉ������ԍ��̃f�[�^�ɃZ�[�u����
void GameSave(int x)	// �Z�[�u�f�[�^�ԍ�
{
	FILE* fp;
	errno_t err;
	char c[256];
	sprintf_s(c, 256, "sr_commusave%02d.dat", x);	// �P���̏ꍇ�́w0x�x�ƂȂ�
	commu_save_data[x].play_second = commu_play_time;
	err = fopen_s(&fp, c, "wb");
	fwrite(&commu_save_data[x], sizeof(commu_save_data[x]), 1, fp);

	fclose(fp);
}
// �����ɉ������ԍ��̃f�[�^�����[�h����
void GameLoad(int x)	// 
{
	FILE* fp;
	errno_t err;
	char c[256];
	sprintf_s(c, 256, "sr_commusave%02d.dat", x);	// �P���̏ꍇ�́w0x�x�ƂȂ�
	err = fopen_s(&fp, c, "rb");
	fread(&commu_save_data[x], sizeof(commu_save_data[x]), 1, fp);
	fclose(fp);
	commu_play_time = commu_save_data[x].play_second;
	// �w��̃R�~�����n�߂铮��e�X�g
	GameMainCommunicationNext(0);
}
// �Z�[�u�E���[�h��ʂŎg���l�X�ȍ��W���i�āj��`����
void GameSaveLoadCoordinateSetting()
{
	sl_coordinate_mode_icon_x = bairitu * 200;					// �i���[�h�ړ��n�A�C�R��x���W
	sl_coordinate_icon_save_y = bairitu * 200;					// �wSAVE�x�A�C�R��y���W
	float x = size_icon_auto.y * 2.0f;							// �e�A�C�R���̊Ԋu
	sl_coordinate_icon_load_y = sl_coordinate_icon_save_y + x;	// �wLOAD�x�A�C�R��y���W
	sl_coordinate_icon_back_y = sl_coordinate_icon_load_y + x;	// �wBACK�x�A�C�R��y���W
	sl_coordinate_icon_title_y = sl_coordinate_icon_back_y + x;	// �wTITLE�x�A�C�R��y���W
	sl_coordinate_icon_exit_y = sl_coordinate_icon_title_y + x;	// �wEXIT�x�A�C�R��y���W

	chk_coordinate_yes_x = bairitu * 600;	                      //�m�F���b�Z�[�W�w�͂��x�I����x���W
	chk_coordinate_yes_y = bairitu * 600;	                      //�m�F���b�Z�[�W�w�͂��x�I����y���W
	chk_coordinate_no_x = chk_coordinate_yes_x * 1.75;	          //�m�F���b�Z�[�W�w�������x�I����x���W
	temp_font3 = CreateFontToHandle("���C���I", FONT_SIZE_ORIGINAL * screen_size_y / WINDOW_SIZE_Y*5, -1, DX_FONTTYPE_ANTIALIASING);


	// �e�Z�[�u�t�@�C���y�[�W�̍��[x���W
	for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) { sl_coordinate_icon_sf_page_x[i] = i * (size_icon_sl_file_page.x * 1.25f) + bairitu * 600; }

	sl_coordinate_icon_sf_page_y = bairitu * 60;	// �Z�[�u�t�@�C���y�[�W�̏�[y���W
	// �Z�[�u�f�[�^
	for(int i = 0; i < SL_FILE_NUMBER; i++)
	{
		sl_coordinate_icon_sf_x[i] = screen_size_x - bairitu * ((i % 2 == 0 ? size_icon_sl_file.x + 100 : 0) + size_icon_sl_file.x + 100);							// �e�Z�[�u�t�@�C���̍��[x���W
		//sl_coordinate_icon_sf_y[i] = bairitu * ((int)(i / 2) * (size_icon_sl_file.y + 50) + 100);																	// �e�Z�[�u�t�@�C���̏�[y���W
		sl_coordinate_icon_sf_y[i] = (int)(i / 2) * (size_icon_sl_file.y + bairitu * 50) + sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y + bairitu * 90;	// �e�Z�[�u�t�@�C���̏�[y���W
	}
}
// �Z�[�u�E���[�h��ʂ̕`�揈��
void DrawGameSaveLoad()
{

	

	if (mode_save == TRUE) {
		//�wSAVE�x���[�h�Ȃ�I�����W
		DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[1], TRUE);
		// �wLOAD�x�A�C�R��
		DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_load_y + size_icon_auto.y, g_imghandles.icon_load[0], TRUE);
	}
	   else	
	{
		// �i���O�̏�Ԃ��^�C�g����ʂ�������j�O���[�wSAVE�x�A�C�R��
		if (g_sl_bm_status == SL_BEFORE_TITLE) { 
			//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE); 
		}
		else
		{
			DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE);
		}
		
		// �wLOAD�x���[�h�Ȃ�I�����W
			DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_load_y + size_icon_auto.y, g_imghandles.icon_load[1], TRUE);
		
	}
		
	// �wBACK�x�A�C�R��
	if (g_sl_bm_status == SL_BEFORE_TITLE) {
		//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);
	}
	else {
		DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);

	}
	// �wTITLE�x�A�C�R��
	DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_title_y + size_icon_auto.y, g_imghandles.icon_title, TRUE);
	// �wEXIT�x�A�C�R��
	DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_exit_y + size_icon_auto.y, g_imghandles.icon_exit, TRUE);
	// �Z�[�u�t�@�C���y�[�W�A�C�R��
	for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) { DrawExtendGraphF(sl_coordinate_icon_sf_page_x[i], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[i] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, g_imghandles.icon_save_file_page[0], TRUE); }
    DrawExtendGraphF(sl_coordinate_icon_sf_page_x[savefile_page], sl_coordinate_icon_sf_page_y, sl_coordinate_icon_sf_page_x[savefile_page] + size_icon_sl_file_page.x, sl_coordinate_icon_sf_page_y + size_icon_sl_file_page.y, g_imghandles.icon_save_file_page[1], TRUE); 
	// �Z�[�u�t�@�C��
	for(int i = 0; i < SL_FILE_NUMBER; i++){ DrawExtendGraphF(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, g_imghandles.icon_save_file, TRUE); }
	for (int i = 0; i < SL_FILE_NUMBER; i++) { 
		DrawExtendGraphF(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], sl_coordinate_icon_sf_x[i] + size_icon_sl_file.x, sl_coordinate_icon_sf_y[i] + size_icon_sl_file.y, g_imghandles.icon_save_file, TRUE); 
		DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i], GetColor(255, 0, 0), temp_font3, "%02d", i + 1+(savefile_page*5));
		if (commu_save_data[i + (savefile_page * 5)].play_second > 1) {
			temp = commu_save_data[i].play_second;
			//display_time = std::to_string(int(commu_save_data[i].play_second / 360)) + ":" + std::to_string(int(commu_save_data[i].play_second/60)) + ":" +std::to_string(int(commu_save_data[i].play_second))+":";
			DrawFormatStringFToHandle(sl_coordinate_icon_sf_x[i], sl_coordinate_icon_sf_y[i] - 30, GetColor(255, 0, 0), g_font3, "%02d:%02d:%02d", int(commu_save_data[i + (savefile_page * 5)].play_second / 360), int(commu_save_data[i+(savefile_page*5)].play_second / 60), int(commu_save_data[i + (savefile_page * 5)].play_second));
		}
	}
}

void CheckMessage() {
	CheckMessageControl();
		DrawCheckMessage();
}
void CheckMessageControl()
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
				//if (ClickFlagCheckF(ClickX, ClickY, , , , , TRUE, FALSE) == TRUE) { cfsl_ = TRUE; }


				if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_yes_x, chk_coordinate_yes_y,  size_icon_auto.x*3 ,  size_icon_auto.y*3 , TRUE, FALSE) == TRUE) { cft_checkmsgYes = TRUE; }
				if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_no_x, chk_coordinate_yes_y,  size_icon_auto.x *3,  size_icon_auto.y*3 , TRUE, FALSE) == TRUE) { cft_checkmsgNo = TRUE; }
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�

				if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_yes_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, FALSE, cft_checkmsgYes) == TRUE) {
					checkmsg= TRUE; 
					CallCheckMsg = FALSE;
				}
					if (ClickFlagCheckF(ClickX, ClickY, chk_coordinate_no_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, FALSE, cft_checkmsgNo) == TRUE) {
						checkmsg= FALSE;
						CallCheckMsg = FALSE;
					}
			
				//if (ClickFlagCheckF(ClickX, ClickY, , , , , FALSE, cfsl_) == TRUE) { }
				// �S�Ẵt���O��߂�
				//cfsl_ = FALSE;
				cft_checkmsgYes = FALSE;                               //�m�F���b�Z�[�W�u�͂��v
				cft_checkmsgNo = FALSE;                                //�m�F���b�Z�[�W�u�������v
								
			}
		}
	}
}
// �m�F���b�Z�[�W�̕`�揈��
void DrawCheckMessage()
{
	if (exit_switch == TRUE) { msg_text = "�I�����܂���?"; }
	else {
		if (mode_save == TRUE) { msg_text = "�Z�[�u���܂���?"; }
		if (mode_save == FALSE) { msg_text = "���[�h���܂���?"; }
	}

	//���f�ނ̂��ߔz�u�K���A�C�R���T�C�Y��3�{
	//�m�F���b�Z�[�W�E�B���h�E
	//DrawExtendGraphF((screen_size_x - bairitu * size_ui_map_check.x) / 2, (screen_size_y - bairitu * size_ui_map_check.y) / 2, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, g_imghandles.ui_map_check, TRUE);
	DrawBox((screen_size_x - bairitu * size_ui_map_check.x) / 2, (screen_size_y - bairitu * size_ui_map_check.y) / 2, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, GetColor(0, 255, 0), TRUE);

	//�w�͂��x�A�C�R��
	DrawExtendGraphF(chk_coordinate_yes_x, chk_coordinate_yes_y, chk_coordinate_yes_x + size_icon_auto.x*3, chk_coordinate_yes_y + size_icon_auto.y*3, g_imghandles.ui_map_check_choice[0], TRUE);
	//�w�������x�A�C�R��
	DrawExtendGraphF(chk_coordinate_no_x, chk_coordinate_yes_y, chk_coordinate_no_x + size_icon_auto.x * 3, chk_coordinate_yes_y + size_icon_auto.y * 3, g_imghandles.ui_map_check_choice[1], TRUE);
	DrawStringFToHandle(screen_size_x / 2 - bairitu * GetDrawFormatStringWidthToHandle(temp_font3, "%s", msg_text.c_str())/2,( (screen_size_y - bairitu * size_ui_map_check.y) / 2+( screen_size_y  / 2- GetDrawFormatStringWidthToHandle(temp_font3, "%c", msg_text.c_str()))/2), msg_text.c_str(), GetColor(0, 0, 0), temp_font3);
}