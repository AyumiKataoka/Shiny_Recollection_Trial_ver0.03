#include "gamesaveload.h"
#include <string>
#include <vector> 

SaveLoadBeforeMode g_sl_bm_status = SL_BEFORE_TITLE;

using namespace std;//���O��Ԃ��w��

int GlobalStaticSaveLoad::samune_background_id = 0;	// �T���l�w�i�ۑ��̂��߂ɕK�v�Ȃh�c�ϐ�

float sl_coordinate_mode_icon_x = 0;						// �i���[�h�ړ��n�A�C�R��x���W
float sl_coordinate_icon_save_y = 0;						// �wSAVE�x�A�C�R��y���W
float sl_coordinate_icon_load_y = 0;						// �wLOAD�x�A�C�R��y���W
float sl_coordinate_icon_back_y = 0;						// �wBACK�x�A�C�R��y���W
float sl_coordinate_icon_title_y = 0;						// �wTITLE�x�A�C�R��y���W
float sl_coordinate_icon_exit_y = 0;						// �wEXIT�x�A�C�R��y���W
float sl_coordinate_icon_sf_x[6];							// �e�Z�[�u�t�@�C���̍��[x���W
float sl_coordinate_icon_sf_y[6];							// �e�Z�[�u�t�@�C���̏�[y���W

bool cft_save = FALSE;                                      //�Z�[�u���[�h�؂�ւ�
bool cft_load = FALSE;                                      //���[�h���[�h�؂�ւ�
bool exit_switch = FALSE;                                   //EXIT���[�h����
bool CallCheckMsg;                                          //�m�F���b�Z�[�W�Ăяo��
bool cft_checkmsgYes = FALSE;                               //�m�F���b�Z�[�W�u�͂��v
bool cft_checkmsgNo = FALSE;                                //�m�F���b�Z�[�W�u�������v
bool checkmsg = FALSE;		                                //�m�F���b�Z�[�W����
bool cft_savefile_page[SL_FILE_PAGE_NUMBER];                //�Z�[�u�t�@�C���y�[�W��ύX����

float chk_coordinate_yes_x = 0;	                            //�m�F���b�Z�[�W�w�͂��x�I����x���W
float chk_coordinate_yes_y = 0;	                            //�m�F���b�Z�[�W�I����y���W
float chk_coordinate_no_x = 0;	                            //�m�F���b�Z�[�W�w�������x�I����x���W
int temp_font3 = 0;                                         //���t�H���g
int savefile_page =0;                                       //���݂̃Z�[�u�t�@�C���y�[�W
int savefile_sl = 0;                                        //�I�𒆂̃Z�[�u�t�@�C��
std::string msg_text = "�Z�Z���܂���?";                     //�m�F���b�Z�[�W�e�L�X�g
char *display_time;											//�Z�[�u�t�@�C���̃v���C���ԕ\��
//-------------------------------------------------------------------------------

//�f�o�b�N�p-----------------
int temp = 0;
extern std::string debug_var;
bool DrawClickFlag = FALSE;
int p_count;
vector<vector<string>> xy(3, vector<string>(3, "abc"));

//---------------------------

BOOL mode_save = TRUE;	// �Z�[�uor���[�h��Ԃ𔻕ʂ���
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfsl=click_flag_save_load�j
//BOOL cfsl_;		// 
// �Z�[�u�E���[�h��ʈڍs����
void GameSaveLoadNext(BOOL x, SaveLoadBeforeMode y)	// �Z�[�uor���[�h�̃t���O,�Z�[�uor���[�h��Ԉڍs�O�̏��
{
	g_gamestate = GAME_SAVELOAD;
	mode_save = x;
	g_sl_bm_status = y;
	// �T���l�̃n���h����ǂݍ���
	for (int i = 0; i < SL_FILE_PAGE_NUMBER * SL_FILE_NUMBER; i++){ save_data_image[i].LoadHandel(i);}
}
// GAME_SAVELOAD��Ԃ̃��C������
void GameSaveLoad()
{
	if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE;}
	//GameMainCommunicationControl();
	
	if (CallCheckMsg == FALSE) { GameSaveLoadControl(); }
	DrawGameSaveLoad();
    //CallCheckMs==TRUE�Ŋm�F���b�Z�[�W��\������
	if (CallCheckMsg == TRUE) 
	{
		CheckMessage();		//�m�F���b�Z�[�W����
		if (checkmsg == TRUE)	//�m�F���b�Z�[�W�u�͂��v��I�������ꍇ
		{
			if (exit_switch == TRUE)	//EXIT���[�h������
			{
				quit_game = TRUE;	//�Q�[���I��
				mode_save = FALSE;	//�t���O��߂�
			}
			else if (mode_save == TRUE) { GameSave(savefile_sl); }	//SAVE���[�h������
			else { GameLoad(savefile_sl); }		//LOAD���[�h������

			//�S�Ẵt���O��߂�
			exit_switch = FALSE;
			checkmsg = FALSE;
			CallCheckMsg = FALSE; //�m�F���b�Z�[�W�\���t���O��߂�
		}


	}
	//dbClickgamesaveload(CallCheckMsg);	//�f�o�b�N�p

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
				//�uSAVE�v�A�C�R������
				if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }//�^�C�g������̏ꍇ
				else if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::SAVE)].JudgementClickCheck() == TRUE) {}
				//�uLOAD�v�A�C�R������
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::LOAD)].JudgementClickCheck() == TRUE) {}
				//�uBACK�v�A�C�R������
				if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }//�^�C�g������̏ꍇ
				else if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::BACK)].JudgementClickCheck() == TRUE) {}
				//�uTITLE�v�A�C�R������
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::TITLE)].JudgementClickCheck() == TRUE) {}
				//�uEXIT�v�A�C�R������
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::EXIT)].JudgementClickCheck() == TRUE) {}
				// �Z�[�u�t�@�C���y�[�W�A�C�R������
				for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++)
				{
					if(image_icon_sl_page[i].JudgementClickCheck() == TRUE){}
				}
				// �Z�[�u�t�@�C������
				for (int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
				{
					if (image_icon_save_file[i][0].JudgementClickCheck() == TRUE) {}
				}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				//�uSAVE�v�A�C�R������
				if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }//�^�C�g������̏ꍇ
				else if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::SAVE)].JudgementReleaseCheck() == TRUE)
				{ 
					// ���[�h���[�h�Ȃ���ʉ���炷
					if (mode_save == FALSE) { SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE)); }

					mode_save = TRUE;
				}
				//�uLOAD�v�A�C�R������
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::LOAD)].JudgementReleaseCheck() == TRUE)
				{ 
					// �Z�[�u���[�h�Ȃ���ʉ���炷
					if (mode_save == TRUE) { SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE)); }

					mode_save = FALSE; 
				}
				//�uBACK�v�A�C�R������
				if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }//�^�C�g������̏ꍇ
				else if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::BACK)].JudgementReleaseCheck() == TRUE)
				{ 
					if(g_sl_bm_status == SL_BEFORE_COMMU){g_gamestate = GAME_MAIN_COMMUNICATION; }	//�R�~���ɖ߂�
					else if (g_sl_bm_status == SL_BEFORE_MAP) { g_gamestate = GAME_MAP; }			// �}�b�v�ɖ߂�
					SEPlay(static_cast<int>(SEData::IDName::ALTERNATIVE));
					//�t���O��߂�
					mode_save = FALSE;
					exit_switch = FALSE;
				}
				//�uTITLE�v�A�C�R������
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::TITLE)].JudgementReleaseCheck() == TRUE) { GameTitleNext(); }
				//�uEXIT�v�A�C�R������
				if (image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::EXIT)].JudgementReleaseCheck() == TRUE)
				{
					CallCheckMsg=TRUE;	//�m�F���b�Z�[�W�Ăяo���t���O
					exit_switch = TRUE;	//�uEXIT�v���[�h�t���O
				}
				// �Z�[�u�t�@�C���y�[�W�A�C�R������
				for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++)
				{
					//�I�������y�[�W�����i�[
					if (image_icon_sl_page[i].JudgementReleaseCheck() == TRUE) { savefile_page = i; }
				}
				// �Z�[�u�t�@�C������
				for (int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
				{
					if (image_icon_save_file[i][0].JudgementReleaseCheck() == TRUE)
					{
						CallCheckMsg = TRUE;	//�m�F���b�Z�[�W�Ăяo���t���O
						exit_switch = FALSE;	//�uEXIT�v���[�h�̃t���O��߂�
						savefile_sl = i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber());	//�I�������Z�[�u�t�@�C��"1�`6"+(�y�[�W��*1�y�[�W���̕\���Z�[�u�f�[�^��"6")
						if (commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second < 1)  //�Z�[�u����f�[�^�̃v���C���Ԃ�1�b�����̏ꍇ
						{
							if (mode_save == FALSE) { CallCheckMsg = FALSE; }	//�t���O��߂��Z�[�u�����𔭐������Ȃ�
						}
						// ���[�h���[�h���ɑ��݂��Ȃ��t�@�C�����N���b�N�����ꍇ�łȂ���Ό��ʉ���炷
						if (commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second > 1 || mode_save == TRUE) { SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE)); }
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
				for (int i = 0; i < SL_FILE_NUMBER; i++) { cft_savefile_page[i] = FALSE; }     //�Z�[�u�t�@�C���y�[�W��ύX����
				//�wSAVE�xor�wLOAD�x���s��
				for (int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++) {image_icon_save_file[i][0].CJChange(FALSE); }
				for (int i = 0; i < ImgDataHJ2::GetOptionIconNumber(); i++) { image_icon_new_option[i].CJChange(FALSE); }	// �e�R�}���h�����s����
				for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++) { image_icon_sl_page[i].CJChange(FALSE); }
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
	commu_save_data[x].ChangeTimeString();
	commu_save_data[x].ChangeSaveData(game_week_number, commu_number + 1, cell_number, static_cast<int>(CommuData::GetGMapUpperType()));
	for (int i = 0; i < CommuSaveData::GetCharacterNumber(); i++) { commu_save_data[x].SetNumberMet(i, commu_look_count[i]); }
	commu_save_data[x].SetLineJump();
	for (int i = 0; i < CommuSaveData::GetCharacterNumber(); i++) { commu_save_data[x].SetTrialStillViewed(i, GlobalStaticMap::GetTrialCommuViewed(i)); }
	err = fopen_s(&fp, c, "wb");
	//���̃R�[�h�Ōx������������
	//if (fp != NULL)
	//{
		fwrite(&commu_save_data[x], sizeof(commu_save_data[x]), 1, fp);
		fclose(fp);
	//}

	// �摜�ۑ��e�X�g�i�����Ɉُ킪�����ă}�b�v�ɖ߂����ۍ��}�b�v���c���Ă���j
	save_data_image[x].Blend(x, commu_save_data[x].GetCommuID() != 0 ? FALSE : TRUE);
}
// �����ɉ������ԍ��̃f�[�^�����[�h����
void GameLoad(int x)	// 
{
	FILE* fp;
	errno_t err;
	char c[256];
	sprintf_s(c, 256, "sr_commusave%02d.dat", x);	// �P���̏ꍇ�́w0x�x�ƂȂ�
	err = fopen_s(&fp, c, "rb");
	//���̃R�[�h�Ōx������������
	//if (fp != NULL)
	//{
	fread(&commu_save_data[x], sizeof(commu_save_data[x]), 1, fp);
	fclose(fp);
	//}
	commu_play_time = commu_save_data[x].play_second;
	game_week_number = commu_save_data[x].GetWeek();
	commu_number = commu_save_data[x].GetCommuID();
	for(int i = 0; i < CommuSaveData::GetCharacterNumber(); i++)
	{
		commu_look_count[i] = commu_save_data[x].GetNumberMet(i);
		GlobalStaticMap::SetTrialCommuViewed(i, commu_save_data[x].GetTrialStillViewed(i));
	}
	// �}�b�v�o���^�C�~���O�̐��l�͕ϊ����Ďg��
	CommuData::SetGMapUpperType(static_cast<CommuData::MapUpperType>(commu_save_data[x].GetMapAppearID()));

	// �w��̃R�~�����n�߂�i0�Ȃ�}�b�v��ʁj
	if (commu_number > 0)
	{
		GameMainCommunicationNext(commu_number - 1, FALSE, 0); 
		// �R�~���������Z�[�u�f�[�^����ǂݍ���
		for (int i = 0; i < GlobalStaticVariable::GetCellLimit(); i++){state::SetAlternativeMoveNumber(i, commu_save_data[x].GetLineJump(i));}

		int loop_limit = commu_save_data[x].GetCell();
		// �ړI�̍s�ɑI����������ꍇ�A�w�ړI�̍s�x��1���炷
		if (std::strcmp(HM[commu_number][loop_limit].GetCommand(), "altenative_2") == 0 || std::strcmp(HM[commu_number][loop_limit].GetCommand(), "altenative_3") == 0) { loop_limit--; }
		// ���[�h���t���O�𗧂Ă�
		GlobalStaticMusic::SetNowLoading(TRUE);
		// �ړI�̍s�܂ōs������J��Ԃ�
		for (int i = 0; i < loop_limit; i++) 
		{
			// �s�𒵂�
			if (state::GetAlternativeMoveNumber(i) != 0)
			{
				int y = state::GetAlternativeMoveNumber(i) - 1;
				i = y;
				cell_number = y;
			}

			GameMainCommunicationNextLine();
			// �Y���s�ȑO�̂r�d��炳�Ȃ�
			if (i < loop_limit - 1) { SEPlay(-2); }
		}
		// �����x����ւ��̐��l��0�ɂ���
		for (int i = 0; i < 3; i++) { commu_character_visibility_count[i] = 0; }
		commu_background_visibility_count = 0;
		commu_mode_background = FALSE;
		// �I�����A�w��t���[���㎩���i�s��Ԃ𔭐������Ȃ�
		if (g_commustatus == COMMU_STATUS_ALTENATIVE || g_commustatus == COMMU_STATUS_AUTO || 
			(g_commustatus == COMMU_STATUS_SE && strcmp(HM[commu_number][cell_number].command, "auto_se") != 0)) { g_commustatus = COMMU_STATUS_NORMAL; }
		//	if (strcmp(HM[commu_number][cell_number].command, "auto_se") == 0){ g_commustatus = COMMU_STATUS_SE; }	// ���s�Z���R�}���h���wauto_se�x�Ȃ玟�s�r�d�Đ����I���܂ő��삪�����ɂȂ�t���O�𗧂Ă�
		// ���[�h���t���O�����낷
		GlobalStaticMusic::SetNowLoading(FALSE);
	}
	else 
	{ 
		// �T��i�߂Ȃ��悤�ɂ��ă}�b�v��ʂֈڍs
		game_week_number--;
		GameMapNext(); 
	}
}
// �Z�[�u�E���[�h��ʂŎg���l�X�ȍ��W���i�āj��`����
void GameSaveLoadCoordinateSetting()
{
	sl_coordinate_mode_icon_x = bairitu * 1800;					// �i���[�h�ړ��n�A�C�R��x���W
	sl_coordinate_icon_save_y = bairitu * 596;					// �wSAVE�x�A�C�R��y���W
	float x = size_icon_auto.y * 2.0f;							// �e�A�C�R���̊Ԋu
	sl_coordinate_icon_load_y = sl_coordinate_icon_save_y + x;	// �wLOAD�x�A�C�R��y���W
	sl_coordinate_icon_back_y = sl_coordinate_icon_load_y + x;	// �wBACK�x�A�C�R��y���W
	sl_coordinate_icon_title_y = sl_coordinate_icon_back_y + x;	// �wTITLE�x�A�C�R��y���W
	sl_coordinate_icon_exit_y = sl_coordinate_icon_title_y + x;	// �wEXIT�x�A�C�R��y���W

	chk_coordinate_yes_x = bairitu * 600;	                      //�m�F���b�Z�[�W�w�͂��x�I����x���W
	chk_coordinate_yes_y = bairitu * 600;	                      //�m�F���b�Z�[�W�w�͂��x�I����y���W
	chk_coordinate_no_x = chk_coordinate_yes_x * 1.75f;	          //�m�F���b�Z�[�W�w�������x�I����x���W
	for(int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++)
	{
		const float X = 200.0f * (i == 0 ? -1 : 1);	// �ǐ�����̂��ߑ��
		image_icon_check[i].CoordinateSetting2(X - image_icon_check[i].GetOriginalSizeX() / 2 + GlobalStaticVariable::GetRSOriginalX() / 2,600);
	}

	temp_font3 = CreateFontToHandle("���C���I", FONT_SIZE_ORIGINAL * screen_size_y / WINDOW_SIZE_Y*5, -1, DX_FONTTYPE_ANTIALIASING);
	// �Z�[�u���[�h�y�[�W
	for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++) { image_icon_sl_page[i].CoordinateSetting2(i % GlobalStaticSaveLoad::GetFilePageNumber() * image_icon_sl_page[i].GetOriginalSizeX() * 1.25f + 1440, 951); }
	// �Z�[�u�f�[�^
	for(int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
	{
		// static_cast�ɂ��Ă����΃R���p�C�����ɃG���[�`�F�b�N���s���Ă����
		image_icon_save_file[i][0].CoordinateSetting2(i % 5 * (image_icon_save_file[i][0].GetOriginalSizeX() * 1.1f) + 102.0f, static_cast<int>(i / 5) * (image_icon_save_file[i][0].GetOriginalSizeY() * 1.25f) + 186);
		image_icon_save_file[i][1].CoordinateSetting2(i % 5 * (image_icon_save_file[i][1].GetOriginalSizeX() * 1.1f) + 102.0f, static_cast<int>(i / 5) * (image_icon_save_file[i][1].GetOriginalSizeY() * 1.25f) + 186);
	}
	// �i�V�����j�A�C�R���iCoordinateSetting2�Ŕ{����������̂ŃI���W�i���T�C�Y���`����j
	const float X = 1800;
	const float Y = 783;
	for(int i = 0; i < ImgDataHJ2::GetOptionIconNumber(); i++)
	{ 
		image_icon_new_option[i].CoordinateSetting2(X, i * image_icon_new_option[i].GetOriginalSizeY() * 1.2f + Y);
	}
}
// �Z�[�u�E���[�h��ʂ̕`�揈��
void DrawGameSaveLoad()
{
	// �w�i
	if (mode_save == TRUE){bgimage[static_cast<int>(ImgDataBG::EnumConstant::STAFF_ROOM)].DrawImage();}
	else { bgimage_room_teacher.DrawImage(); }
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, screen_size_x, screen_size_y, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// ���[�h�\��
	image_saveload_mode[mode_save].DrawImage();

	if (mode_save == TRUE) 
	{
		// �wLOAD�x�A�C�R��
		image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::LOAD)].DrawImage();
	}
	// ���[�h���
	else	
	{
		// �i���O�̏�Ԃ��^�C�g����ʂ�������j�O���[�wSAVE�x�A�C�R��
		if (g_sl_bm_status == SL_BEFORE_TITLE) 
		{ 
			//�f�ޖ�����
			//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_save_y + size_icon_auto.y, g_imghandles.icon_save[0], TRUE); 
		}
		else
		{
			//�wSAVE�x�A�C�R��
			image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::SAVE)].DrawImage();
		}
	}		
	// �i���O�̏�Ԃ��^�C�g����ʂ�������j�O���[�wBACK�x�A�C�R��
	if (g_sl_bm_status == SL_BEFORE_TITLE)
	{
		//�f�ޖ�����
		//DrawExtendGraphF(sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, sl_coordinate_mode_icon_x + size_icon_auto.x, sl_coordinate_icon_back_y + size_icon_auto.y, g_imghandles.icon_back, TRUE);
	}
	else
	{
		//�wBACK�x�A�C�R��
		image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::BACK)].DrawImage();
	}
	// �wTITLE�x�A�C�R��
	image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::TITLE)].DrawImage();
	// �wEXIT�x�A�C�R��
	image_icon_new_option[static_cast<int>(ImgDataHJ2::SaveLoadIconType::EXIT)].DrawImage();
	// �i�V�����j�A�C�R���i�e�X�g�Ŗ��Ȃ���Ώ����j
	//for (int i = 0; i < ImgDataHJ2::GetOptionIconNumber(); i++) { image_icon_new_option[i].DrawImage(); }
	// �Z�[�u�t�@�C���y�[�W�A�C�R��
	for (int i = 0; i < GlobalStaticSaveLoad::GetFilePageNumber(); i++) { image_icon_sl_page[i].DrawImage(); }

	for(int i = 0; i < GlobalStaticSaveLoad::GetFileNumber(); i++)
	{
		int x = i + savefile_page * GlobalStaticSaveLoad::GetFileNumber();
		// ��̃Z�[�u�t�@�C��or�T���l��`��
		if (commu_save_data[x].play_second > 0)
		{
			image_icon_save_file[i][1].DrawImage();
			const float X = bairitu * 42;
			DrawExtendGraphF(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() + X, image_icon_save_file[i][0].GetCoordinateX() + image_icon_save_file[i][0].GetSizeX(), image_icon_save_file[i][0].GetCoordinateY() + X + image_icon_save_file[i][0].GetSizeX() / 16 * 9, save_data_image[x].GetHandle(), TRUE);
		}
		else{ image_icon_save_file[i][0].DrawImage(); }

		DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() + bairitu * 9, GetColor(0, 0, 0), g_font3, "No.%02d", 1 + x);
		if (commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second >= 1) //�Z�[�u����f�[�^�̃v���C���Ԃ�1�b�ȏ�̏ꍇ�`��
		{
			// �X�`���̌��łł͕\�������Ȃ�
			if (GlobalStaticVariable::GetModeTrial() == FALSE){DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX() + bairitu * 210, image_icon_save_file[i][0].GetCoordinateY() + bairitu * 9, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::SAVE_DATA)].GetHandle(), "%d��%d�T", commu_save_data[x].GetWeek() / 4 + 1, commu_save_data[x].GetWeek() % 4 + 1);}
			// �T�u�^�C�g��
			if (commu_save_data[x].GetCommuID() > 0)
			{
				// �������r���s��
				if(strlen(commu_data[commu_save_data[x].GetCommuID() - 1].GetTitle()) > 18)
				{
					char c[22];	// �k���I�_�p��+1�o�C�g
					sprintf_s(c, 22, "%.18s...", commu_data[commu_save_data[x].GetCommuID() - 1].GetTitle());
					DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].GetSizeX() / 16 * 9 + bairitu * 45, GetColor(0, 0, 0), g_font3, c);
				}
				else{DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX(), image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].GetSizeX() / 16 * 9 + bairitu * 45, GetColor(0, 0, 0), g_font3, commu_data[commu_save_data[x].GetCommuID() - 1].GetTitle());}
			}
			const float X = image_icon_save_file[i][0].GetCoordinateX();
			const float Y_PLAY_TIME = image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * (60 + 3);
			const float Y_SAVE_TIME = image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * (30 + 3);
			const float Z = bairitu * 15;
			DrawLineAA(X + Z, Y_PLAY_TIME, X + image_icon_save_file[i][0].GetSizeX() - Z, Y_PLAY_TIME, GetColor(0, 0, 0));
			DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX() + Z, image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * 60, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::SAVE_DATA)].GetHandle(), "Play time�\%02d:%02d:%02d", int((commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second) / 3600), int(fmod((commu_save_data[x].play_second) / 60, 60)), int(fmod((commu_save_data[i + (savefile_page * GlobalStaticSaveLoad::GetFileNumber())].play_second), 60)));
			DrawLineAA(X + Z, Y_SAVE_TIME, X + image_icon_save_file[i][0].GetSizeX() - Z, Y_SAVE_TIME, GetColor(0, 0, 0));
			DrawFormatStringFToHandle(image_icon_save_file[i][0].GetCoordinateX() + Z, image_icon_save_file[i][0].GetCoordinateY() + image_icon_save_file[i][0].size_y - bairitu * 30, GetColor(0, 0, 0), font[static_cast<int>(FontData::Type::SAVE_DATA)].GetHandle(), commu_save_data[x].GetTimeString());
		}
	}
}
// �m�F���b�Z�[�W��Ԃ̃��C������
void CheckMessage() 
{
	CheckMessageControl();
		DrawCheckMessage();
}
// �m�F���b�Z�[�W���쏈��
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
				if (image_icon_check[0].JudgementClickCheck() == TRUE) {}
				else if (image_icon_check[1].JudgementClickCheck() == TRUE) {}
			}
			else if (LogType != MOUSE_INPUT_LOG_DOWN)
			{
				BOOL x = FALSE;	// �ȍ~�̏������甲���o���ϐ�
				//�u�͂��v����
				if (image_icon_check[0].JudgementReleaseCheck() == TRUE)
				{
					checkmsg= TRUE;		//�u�͂��v�t���O
					CallCheckMsg = FALSE;	//�m�F���b�Z�[�W�����
					SEPlay(static_cast<int>(SEData::IDName::SENTAKUSHI));
				}
				//�u�������v����
				else if (image_icon_check[1].JudgementReleaseCheck() == TRUE)
				{
						checkmsg= FALSE;	//�u�������v�t���O
						CallCheckMsg = FALSE;	//�m�F���b�Z�[�W�����
						SEPlay(static_cast<int>(SEData::IDName::STARTSCEAN_NOTE));
				}
				// �S�Ẵt���O��߂�
				cft_checkmsgYes = FALSE;                               //�m�F���b�Z�[�W�u�͂��v
				cft_checkmsgNo = FALSE;                                //�m�F���b�Z�[�W�u�������v
				for (int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++) { image_icon_check[i].CJChange(FALSE); }								
			}
		}
	}
}
// �m�F���b�Z�[�W�̕`�揈��
void DrawCheckMessage()
{
	//�m�F���b�Z�[�W���e(�e���[�h�̔���)

	//���f�ނ̂��ߔz�u�K���A�C�R���T�C�Y��3�{
	//�m�F���b�Z�[�W�E�B���h�E
	//DrawExtendGraphF((screen_size_x - bairitu * size_ui_map_check.x) / 2, (screen_size_y - bairitu * size_ui_map_check.y) / 2, (screen_size_x + bairitu * size_ui_map_check.x) / 2, (screen_size_y + bairitu * size_ui_map_check.y) / 2, g_imghandles.ui_map_check, TRUE);
	// ������
	if (exit_switch == TRUE)
	{ 
		image_finish_check.DrawImage();
	}
	else
	{
		if (mode_save == TRUE) { image_sl_check_message[static_cast<int>(ImgDataSLCheck::Type::SAVE)].DrawImage(); }
		if (mode_save == FALSE) { image_sl_check_message[static_cast<int>(ImgDataSLCheck::Type::LOAD)].DrawImage(); }
	}
	// �I�����A�C�R��
	for (int i = 0; i < ImgDataIconCheck::GetImageNumber(); i++) { image_icon_check[i].DrawImage(); }
}


//�ȉ��f�o�b�N�p--------------------------------------------------------------------------------------------------------------------

bool dbClickFlagCheckF(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a, std::string massage)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBoxAA(Jx, Jy, Jx + breadth, Jy + length, GetColor(255, 0, 255), TRUE);
	//if (ClickFlagCheckF(ClickX, ClickY, Jx, Jy, breadth, length, TRUE, FALSE)) { debug_var = flag; }
	//else { debug_var = "�t���O�Ȃ�"; }
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 150);
	return FALSE;
}

void dbClickgamesaveload(bool p1, bool p2, bool p3) 
{

	if (p1 == TRUE) { p_count = 1; }
	if (p2 == TRUE) { p_count = 2; }
	if (p3 == TRUE) { p_count = 3; }
	switch(p_count) 
	{
	case 1:

			//if (ClickFlagCheckF(ClickX, ClickY, , , , , TRUE, FALSE) == TRUE) { cfsl_ = TRUE; }


			if (dbClickFlagCheckF(ClickX, ClickY, chk_coordinate_yes_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, TRUE, FALSE) == TRUE) { cft_checkmsgYes = TRUE; }
			if (dbClickFlagCheckF(ClickX, ClickY, chk_coordinate_no_x, chk_coordinate_yes_y, size_icon_auto.x * 3, size_icon_auto.y * 3, TRUE, FALSE) == TRUE) { cft_checkmsgNo = TRUE; }

		break;
	default:

		if (g_sl_bm_status == SL_BEFORE_TITLE) { mode_save = FALSE; }
		else if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_save_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_save = TRUE; }
		if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_load_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_load = TRUE; }
		if (g_sl_bm_status == SL_BEFORE_TITLE) { cft_exit_main_commu = FALSE; }
		else if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_back_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_exit_main_commu = TRUE; }
		if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_title_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cfc_move_title = TRUE; }
		if (dbClickFlagCheckF(ClickX, ClickY, sl_coordinate_mode_icon_x, sl_coordinate_icon_exit_y, size_icon_auto.x, size_icon_auto.y, TRUE, FALSE) == TRUE) { cft_quit_game = TRUE; }

		// �Z�[�u�t�@�C���y�[�W�A�C�R��
		for (int i = 0; i < SL_FILE_PAGE_NUMBER; i++) 
		{
			// �ĂѕK�v�ɂȂ�����C������
		}
		for (int i = 0; i < SL_FILE_NUMBER; i++) 
		{
			// �ĂѕK�v�ɂȂ�����C������
		}
		break;
	}
	p_count = 0;
}
