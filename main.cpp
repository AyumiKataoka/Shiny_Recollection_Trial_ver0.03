/*
���K�v����
����������
���v�C��
*/
#pragma region �ŗL����
/*
*/
#pragma endregion
#pragma region
#pragma endregion
//���i���ۑ�����
/*
���w�b�_�t�@�C���̕ϐ����̕��тɋK����������������������
�E�i�\���̓��̕ϐ��錾��enum���g�����Ƃ�����̂ŉ��L�̏��Ԃɂ���j
�E�C���N���[�h�錾
�E�萔�錾
�Eenum
�Estruct
�Eclass
�Echar
�Eint
�Efloat
�Edouble
�EBOOL
�Evoid�֐��i����n�Ə����n�̏��Ԃ͖��Ȃ����H�j
�@�E�Q�[���N�����ɍs����ǂݍ���
�@�E���C���֐�
�@�E����n
�@�E�����n
�@�E�`��n
�E���̑��̊֐�
���萔�̎����g���萔�͊��ʂň͂񂾕��������H
�E�w�萔x y + z�x�́wy + z�x���i�[���Ă��邾���Łwy + z�x�̒l�ł͂Ȃ��̂ŁA�w100 - x�x�́w100 - y + z�x�ƂȂ�z�̒l�����Z����Ă��܂�
��ID�Ȃǂŏ��Ԃɒ萔������ꍇ�i�A�����Č�X���̏��Ԃ������\��������ꍇ�j�ɁA�񋓑́ienum�j��t����̂��K���Ă���
���R�����g�������R�[�h�����̍ۂ͈ȉ��̗v�_�ɋC������
�E���o�[�W������Ɠ��ŃR�����g���ɂ����R�[�h�i�����̃~�X�j�͏����Ă��悢
�E�C���Ƃ��ăR�����g�ɂ����ȑO�̃o�[�W�����̃R�[�h�͎c���Ă����A��Ƃ��{�i�I�Ɉ�i�������ۂɏ������ǂ������߂�
�@�E�����݁A�R�����g�ň͂�Ő܂肽���݂ł���@�\�A����сwregion�x�@�\������̂ŁA���̂܂܎c���Ă����Ă�����
�E���f�B�A�A�R�[�h�����ŃA�v���t�H���_�̍쐬�́A��L�̍Z���R�����g���������ۂ������ꂩ�̃��f�B�A���������A�܂��͏ꏊ��ς����ۂɍs���̂������̂�������Ȃ�
�������s���̃R�����g�́A�͂�ŃR�����g���ɂ���Ί֐��̂悤�ɊJ���邱�Ƃ��ł���
�E�w#pragma region�x�ł��\
���Q�[���̃^�C�g����ύX����ꍇ
�E�w14�΂���͂��߂�i�����j�x�̂o132�`134�Q��
�E�s���X�e�[�^�X������������Ă��܂��̂ŁA�s���ꍇ�̓o�[�W�����A�b�v��Ƃ̂͂��߂ɍs�����ق�������
���I���̕�����R�����g�ň͂߂΁A�܂肽����ł�R�[�h���J����Ȃ�
���֐��Ɉ����𑝂₷�����̍�Ƃł�region�ɂ��o�b�N�A�b�v���쐬����
�E�����𑝂₷�O�̏������m�F���悤�Ƃ������A�R�����g���̉����ł͂Ȃ���X�����������Ȃ���΂����Ȃ����ԂɊׂ�̂�h������
���G���[���N���Ă��܂��̂ŁAstruct�Aenum�������ϐ���cpp�t�@�C���̕��Œ�`����
��40�s�𒴂���v�f�̃R�[�h��region�ň͂�ł�����
���ϐ���Ԃ��֐��ɂ���ĕϐ���ς���ꍇ�A�֐���P�ƂŋL�������������N���Ȃ��~�X���悭����̂ŁA�K���v�Z���ɂȂ��Ă��邩�m�F����
���萔�錾��\���̂Ȃǂ́A��������͂���w�b�_�t�@�C���̈Ⴂ�ɂ���ăG���[���N����̂Œ��ӂ��邱��
�E��P�F�`�̃w�b�_�t�@�C���Ő錾�����\���̂͂a�̃w�b�_�t�@�C���Ő錾�����֐��̈����Ɏg�����Ƃ��Ă��ł���`����Ă��Ȃ������ɂȂ�G���[���N����
�@�E���̏ꍇ�A��ɐ錾�����֐��Ȃǂ��C���̂��߈ړ������Ȃ���΂����Ȃ��̂Ŏ�ԂɂȂ�
�E��Q�F�\���̂̕ϐ��ɔz����g�����Ƃ��A���̐�����萔�i���H�j�ɂ���ꍇ�A�㕔�Ő�ɐ錾���Ă����Ȃ��ƒ�`����Ă��Ȃ������ɂȂ�G���[���N����
�E�������Ƃ��Ă�main.h�ȂǁA�\�߁w��L�̂悤�Ȃ��Ƃ��N����\���̓����i�[���邽�߂̏ꏊ�x��p�ӂ��Ă����΂����H
��char�͓ǂݍ��݂̍ۂɂ悭�G���[���N����̂ŁA�i�z��Ȃ�for�����g���āj�K������������
���R�[�h��ǂ񂾍ۂ�enum�̖ړI�����������ł���悤�Aenum class�͊֌W����N���X��
�@���ɓ��ꂽ�����ǂ�
��if���́wif(x == TRUE)�x�Ƃ���if(x)�����ł����Ȃ��Bx��int�ł��������A0�Ȃ�
�@FALSE�A0�ȊO�Ȃ�Q�ȏ�ł��|�P�ȉ��ł�TRUE�ɂȂ�
���e���v�����b�Z�[�W
// ver0.021���쎞�Z���R�����g
#pragma region ver0.031���쎞�R�����g���R�[�h
#pragma endregion
�Eregion�́wver0.001beta_b�x�̂悤�Ɂw.�x�̌�ɐ擪�ɐ���������p����p����ƃG���[���N����i�wver0.001(beta)�x�Ȃ���Ȃ��j
��ver0.021�Z���R�����g���݃t�@�C��
*/
//���R�����g��������
/* �i�����Ƀ��b�Z�[�W�j ---------*/
/*-------------------------------*/

#pragma region �����[�X��Ǝ菇
/*
�P�F�i�e�X�g�v���C���[�p�łȂ���΁j�wdebug_mode�x��FALSE�ɂ���
�Q�F�����[�X�ŃA�v�����r���h����i�̌��ł̓�����m�F�������ꍇ�́A���̕����r���h����j
�R�F�imedia�t�H���_�̓��e���ς�����Ȃ�jmedia.dat�t�@�C�����쐬����
�S�F������m�F����i�œK�����邪�̂�debug�łł͋N����Ȃ������o�O���N����\��������j
�������[�X�Ńf�o�b�O�v���C�m�F�v��
���{���Ȃ�N���b�N���Ă��Ӗ��̂Ȃ��ꏊ���N���b�N���Ă݂�
�������Y��Ă��܂��̂ŁA�s������m�F�����ۂ͑����ɋL�ڂ��Ă���
���^��@�\������Windows10�Ŋm�F���邱�Ƃ𐄏�����
�T�F�폜�R�[�h�A���f�B�A���������Asitagaki�Anewproject�̃R�[�h��K���ȃt�@�C���Ɉڂ�
�U�F�i�폜�������̂����������A�R�[�h����L�̃t�@�C������ړ��������Ȃ�j�����[�X�ŃA�v�����Ăуr���h����
�U�`�F������m�F����
�V�F�����Ɠ��e���L������i�Œ��ł�20���ȓ��Ŋ�������\���������w�X���[���S�[���x���ӎ������^�X�N���R���j
�W�F��ƃt�H���_���R�s�y���A��Ƃ��Ă����o�[�W�������l���L������
��visualstudio�̍�Ɗ����e������̂ŁA�w.vs�x�t�H���_�ȊO�̃f�[�^���i�c�h���C�u�ɁH�j�R�s�[����A�Ƃ������@����ԓK���ł���
�X�F�^�u�Ƃ��ďo�Ă���S�ẴR�[�h���ł��邾���܂肽���݁Amain.cpp�Adebugprogram.cpp�Asitagaki�Anewproject
�@�@�ȊO�̍�ƃt�@�C���̃s�����O���A�u�b�N�}�[�N���폜����
10�F�A�v���^�C�g���A�R�����g�A���M�I���p�R�����g�R�[�h�̃o�[�W�������l��ύX����
�������J�A�o�T���邱�ƂɂȂ��Ă������悤�ɁA�A�v���^�C�g�����ڎ��ł��镔���͌��J����ۂ̐����ɌJ��グ��
11�F�r���h�����wDebug�x�ɖ߂�
*/
#pragma endregion
//�����݂̕s��i�ً}�x���j
/*
*/
//�A�b�v�f�[�g����--------
/*
���V�����A�b�v�f�[�g���e���v�����Ă��A���ݍ�ƒ��̃o�[�W�����ɑg�ݍ��܂Ȃ��悤�ɂ���
�����݃o�[�W�����ɓ��ڂ��悤�Ƃ��Ă܂����ĂȂ��A�b�v�f�[�g���e�����̃o�[�W�����œ��ڂ��悤�Ƃ���̂͂���
�������_��R�ʂ̐��l�́A��O�҂ɃA�v����������i�������j�ۂɐ؂�ւ���
*/
#pragma region �ȍ~�ړI��ƌv��
/*
*/
#pragma endregion
#pragma region �錾�n��
#include "main.h"
// �O���[�o���ϐ�
// ���Ԍv���p�ϐ�
int g_lasttime = 0;
float g_frametime = 0;
int g_timerstart;
// ����
int Ransu = 0;

GameState g_gamestate = GAME_FIRST_LOAD;
SaveFileID g_saveid = SAVE_ID_001;
CommuMessageSpeedType g_commumessagespeed = COMMU_MESSAGE_SPEED_NORMAL; // ���b�Z�\�W���x�̎��

//ConfigData Data;
SystemData system_data;
CSDisplayCommuState cs_displat_commu[CS_COMMU_LIMIT];
/* CommuSaveData�N���X ---------*/
CommuSaveData commu_save_data[SAVE_DATA_NUMBER], commu_save_data_memory;	// �R�~���Z�[�u�f�[�^�\���́i���j
void CommuSaveData::SetLineJump()
{
	for (int i = 0; i < CELL_LIMIT; i++) { line_jump[i] = state::GetAlternativeMoveNumber(i); }
}
/*------------------------------*/
/* KeyTrigger�N���X ---------*/
BOOL KeyTrigger::key_prev[KeyTrigger::KEY_NUMBER] = {};
BOOL KeyTrigger::Trigger(int key, KeyTrigger::Type y)
{
	int z = 0;
	switch (y)
	{
	case KeyTrigger::Type::LEFT:	z = KEY_INPUT_LEFT;		break;
	case KeyTrigger::Type::RIGHT:	z = KEY_INPUT_RIGHT;	break;
	default:												break;
	}
	if (key & z)
	{
		if (key_prev[static_cast<int>(y)] == FALSE)
		{
			key_prev[static_cast<int>(y)] = TRUE;
			return TRUE;
		}
	}
	else { key_prev[static_cast<int>(y)] = FALSE; }
	return FALSE;
}
/*---------------------------*/
/* GlobalStaticVariable�N���X ---------*/
int GlobalStaticVariable::commu_number = 0;
const BOOL GlobalStaticVariable::mode_trial = TRUE;
const int GlobalStaticVariable::RESOLUTION_SIZE_ORIGINAL_X = 1920;
/*-------------------------------------*/
#pragma region BOOL�ϐ�
BOOL g_upkey_prev[2];		// ���O�̂`�{�^���̏��
BOOL g_downkey_prev[2];		// ���O�̉��L�[�̏��
BOOL g_leftkey_prev[2];		// ���O�̍��L�[�̏��
BOOL g_rightkey_prev[2];	// ���O�̉E�L�[�̏��
BOOL g_enterkey_prev[2];	// ���O�̃G���^�[�L�[�̏��
BOOL quit_game = FALSE;			// �Q�[�����I�������邩���ʂ���t���O
BOOL flag_full_hd_ok = TRUE;	// �t���g�c�ɂ��v���C���\�����ʂ���
BOOL flag_full_hd_now = TRUE;	// ���݂̉𑜓x���t���g�c�����ʂ���
BOOL flag_mode_window = TRUE;	// �t���X�N���[���A�E�B���h�E�̏�Ԃ𔻕ʂ���t���O
BOOL flag_dialog_appear = TRUE;	// �_�C�A���O�{�b�N�X���o��������t���O
// �R�~���Z���N�g�p
BOOL cfcs_move_commu[CS_COMMU_LIMIT];	// �I�����ꂽ�R�~�����{������t���O
// �̌��Ń��[�h��p
//BOOL mode_trial = FALSE;	// ���݃g���C�A�����[�h�����ʂ���
// �f�o�b�O���[�h��p
BOOL mode_debug = TRUE;	// ���݃f�o�b�O���[�h�����ʂ���
#pragma endregion

char OneMojiBuf[3];	// �P�������ꎞ�L���z��

char StringBuf[STRBUF_HEIGHT][STRBUF_WIDTH + 2];	// ���z�e�L�X�g�o�b�t�@
// �J�[�\��
int select_cursor = 0;
int mode_cursor = 2;

int title_wait_time = 0;		// �^�C�g����ʂɐ؂�ւ��������
int now_title_wait_time = 0;	// �^�C�g����ʂɐ؂�ւ���Ă���o�߂�������
int demo_count = 0;				// �f����ʂɐ؂�ւ������
int InputHandle;			// ��������͂���ۂɕK�v�ȃn���h��
int monitor_resolution_x = 0;	// ���C�����j�^�[X���W
int monitor_resolution_y = 0;	// ���C�����j�^�[Y���W

int MouseX, MouseY;						// �}�E�X���W�擾�ɕK�v�ȕϐ�
int StringSizeX, StringSizeY, StringLine;		// �����T�C�Y�擾�ɕK�v�ȕϐ��iGetDrawStringSizeToHandle�֌W�ō������z��̂Q�{�ɂȂ�̂́A���s���l�����Ă���H�i�������ɏグ��ꍇ�A�Q���̂P�ł��傤�ǂ悭�Ȃ�j�j
int DrawPointX, DrawPointY;	// ������`��̈ʒu
int SP, CP;									// �Q�Ƃ��镶����ԍ��ƕ����񒆂̕����|�C���^
int EndFlag = 0;							// �������P�������`�悷�鏈���̏I���t���O

int screen_size_x = 1920;	// �Q�[���̉��𑜓x
int screen_size_y = 1080;	// �Q�[���̏c�𑜓x

float bairitu = 1.00f;	// ���݉𑜓x�ɉ������e�v�f�̔{��
// �R�~���Z���N�g���[�h�֌W
float commu_select_coordinate_alternative_y[CS_COMMU_LIMIT];	// �R�~���I�������[y���W
/*---------------------------
���ʃ\�[�X�p�ϐ�
---------------------------*/
int progress_frame = 0 ;					// �Q�[���J�n����o�߂����t���[�����i�P�^60�b�j
int progress_frame_time = GetNowCount();	// �O��̌o�߃t���[�����J�E���g��������
int progress_frame_need_time = 16;			// �O��̌o�߃t���[�����J�E���g����̂ɕK�v�Ȏ���
#pragma endregion

#pragma region �֐�
int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC, int nC)
{
	if (GlobalStaticDebug::GetLog() == FALSE) { SetOutApplicationLogValidFlag(FALSE); }	// �f�o�b�O���[�h�łȂ���΃��O���쐬����Ȃ��悤�ɂ���
	char cpp_title[256] = "";
	char cpp_title_a[256] = "";
	sprintf_s(cpp_title, 256, "%s%s",	GlobalStaticDebug::GetLog() == TRUE ? " �f�o�b�O���O�o�̓��[�h" : "", mode_debug == TRUE ? " �f�o�b�O���[�h" : "");
	if (GlobalStaticVariable::GetModeTrial() == FALSE){ sprintf_s(cpp_title_a, 256, "Shiny_Recollection_Trial_ver0.02%s", cpp_title); }
	else{ sprintf_s(cpp_title_a, 256, "Shiny_Recollection_StillTrial_ver0.03a%s", cpp_title); }	// �̌��ŗp�^�C�g��
	SetWindowText(cpp_title_a);																				// �A�v���P�[�V�����̃^�C�g�������X�́wDxLib�x����ύX����
	// config_data�̓��e��ǂݍ��ށi�����s���j
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "sr_system.dat", "rb");
	if (fp == NULL){}	// ������Ԃł�TRUE���K���ȃ_�C�A���O�\���t���O�ɑ������
	else
	{
		fread(&system_data, sizeof(system_data), 1, fp);
		fclose(fp);
		// �ǂݍ��񂾃Z�[�u�f�[�^�̂h�c�����o�[�W�����������͌Â��o�[�W������
		//if (score_data.id <= g_saveid)
		{
			flag_mode_window = system_data.full_screen;						// �t���X�N���[���̃t���O
			flag_full_hd_now = system_data.screen_resolution;				// �𑜓x�̃t���O�iTRUE�Ȃ�1080px�j
			bgm_volume = system_data.vol_bgm;								// �a�f�l����
			se_volume = system_data.vol_se;									// �r�d����
			text_window_clear_percentage = system_data.text_window_clear;	// �e�L�X�g�E�B���h�E�����x
			g_commumessagespeed = system_data.string_speed;					// �����X�s�[�h
			flag_dialog_appear = system_data.dialog_appear;					// �_�C�A���O�{�b�N�X�\���t���O
			// �G�f�B�b�g���[�h�ł̌ʓǂݍ��݃t���O
			for (int i = 0; i < CharacterImage::GetCharacterMember(); i++){CharacterImage::SetLoadEdit(i, system_data.GetECL(i));}
		}
	}
	// �R�~���Z�[�u�f�[�^��ǂݍ���
	for (int i = 0; i < SAVE_DATA_NUMBER; i++)
	{
		char c[256];
		sprintf_s(c, 256, "sr_commusave%02d.dat", i);
		err = fopen_s(&fp, c, "rb");
		if (fp == NULL) {}
		else
		{
			fread(&commu_save_data_memory, sizeof(commu_save_data_memory), 1, fp);
			fclose(fp);
			// �ǂݍ��񂾃Z�[�u�f�[�^�̂h�c�����o�[�W�����������͌Â��o�[�W������
			//if (score_data.id <= g_saveid)
			{
				commu_save_data[i].play_second = commu_save_data_memory.play_second;
				commu_save_data[i].ChangeTimeString(commu_save_data_memory.GetTimeString());
				commu_save_data[i].ChangeSaveData(commu_save_data_memory.GetWeek(), commu_save_data_memory.GetCommuID(), commu_save_data_memory.GetCell(), commu_save_data_memory.GetMapAppearID());
				// �s�W�����v����
				for (int j = 0; j < GlobalStaticVariable::GetCellLimit(); j++){commu_save_data[i].SetLineJumpSave(j, commu_save_data_memory.GetLineJump(j));}				
				// �X�`���̌��łŎg���L�����ʂ̃R�~�������I�����t���O
				for (int j = 0; j < CommuSaveData::GetCharacterNumber(); j++) { commu_save_data[i].SetTrialStillViewed(j, commu_save_data_memory.GetTrialStillViewed(j)); }
			}
		}
	}
	// ���C�����j�^�[�𑜓x���擾����
	monitor_resolution_x = GetSystemMetrics(SM_CXSCREEN);
	monitor_resolution_y = GetSystemMetrics(SM_CYSCREEN);
	// ���j�^�[�𑜓x���t���g�c��\���ł��Ȃ��Ȃ�A�t���g�c�\���\�t���O���~�낵�A�g�c�T�C�Y�̉𑜓x�ɂ���
	if (monitor_resolution_x < 1920 || monitor_resolution_y < 1080)
	{
		flag_full_hd_ok = FALSE;
		flag_full_hd_now = FALSE;
		flag_dialog_appear = FALSE;	// �_�C�A���O�{�b�N�X��\�������Ȃ�
	}
	// �𑜓x�I���_�C�A���O�{�b�N�X
	if ((mode_debug == FALSE || debug_dialog_through == FALSE) && flag_dialog_appear == TRUE)
	{
		#pragma region ver0.0111���쎞�R�����g���R�[�h
		DialogBox(h1, TEXT("DLG1"), 0, (DLGPROC)DlgProc1);
#pragma endregion
		if (dialog_not_push == TRUE)return 0;	// �w�~�x�{�^�����̔񐳋K�̕��@�Ń_�C�A���O�{�b�N�X���I�������ꍇ�A�A�v�����I��������
	}
	else { DebugWindowChange(); }

	if (DxLib_Init() == -1) return -1;	// DX���C�u����������
	SetAlwaysRunFlag(TRUE);				// ���C���E�C���h�E����A�N�e�B�u��Ԃł����������s���邩�ǂ�����ݒ肷��( TRUE:���s����  FALSE:��~����( �f�t�H���g ) )	SetMouseDispFlag(TRUE);				// �}�E�X��\����Ԃɂ���
	ScreenResolutionChange();
	DebugProgram(DEBUG_LOAD);
	if(flag_mode_window == TRUE)
	{
		if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK) { return -1; };
	}
	SetMouseDispFlag(TRUE);										// �}�E�X��\����Ԃɂ���
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);	// �t���X�N���[�����[�h���̉𑜓x���[�h��ݒ肷��
	SetWindowIconID(283);										// �E�B���h�E����̃A�C�R�����I���W�i���̂��̂ɕύX����
	if (mode_debug == FALSE){ SetDXArchiveExtension("dat"); }	// �f�o�b�O���[�h�łȂ���΁Adat�t�@�C�����t�H���_�Ƃ��ēǂݍ���
	SetDXArchiveKeyString("46399292");							// ���b�N���ꂽ�f�[�^�t�@�C���̃p�X���[�h

	// �摜�A�a�f�l�A�r�d�ǂݍ���
	if (LoadGameImage() == FALSE){ return -1; }					
	LoadFont();
	BGMData::LoadFirst();
	SetDrawScreen(DX_SCREEN_BACK);				// �`���𗠉�ʂɂ���
	g_lasttime = GetNowCount();					// ���ݎ����̋L�^
	// �t���X�N���[���؂�ւ����s���Ă��d���Ȃ�Ȃ��悤�ɂ��鏈���i�d�l�ڍׂ͕s���j
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);	// ��ʃ��[�h�ύX��( �ƃE�C���h�E���[�h�ύX�� )�ɃO���t�B�b�N�X�V�X�e���̐ݒ��O���t�B�b�N�n���h�������Z�b�g���邩�ǂ�����ݒ肷��( TRUE:���Z�b�g����( �f�t�H���g )  FALSE:���Z�b�g���Ȃ� )

	SetSysCommandOffFlag(1);					// �^�X�N�X�C�b�`��L���ɂ��邩�ǂ�����ݒ肷��i1�ɂ����Alt�L�[�������������j
	SetKeyInputCursorBrinkFlag(TRUE);			// �L�[���̓n���h���̃L�[���͎��̃J�[�\����_�ł����邩�ǂ������Z�b�g����
	GameMapTipsSubstitution();					// tips����e�X�g
	g_time_first_load_start = GetNowCount();	// FIRST_LOAD���[�h���J�n�����~���b���L�^����

	// ��pcsv�t�@�C��������Ȃ炻�̓��e��ǂݍ���
	char csv_name[256] = "media\\edit_import.csv";
	struct stat st;

	if (stat(csv_name, &st) == 0)	// �t�@�C�������݂��Ă����0��Ԃ�
	{ 
		char gomi[1][256];
		int FileHandle = FileRead_open("media\\edit_import.csv");
		if (FileHandle == NULL) { return FALSE; }	// �G���[���̏���
		for (int i = 0; i < 1; i++) { FileRead_gets(gomi[0], 1024, FileHandle); }	// �ŏ��̓�s��ǂݔ�΂��i���̂��G���[���N�������ߏC���j
		for (int i = 2; i < COMMU_LINE_MAX; i++) {	// ��s�ڂ���1+n�s�ڂ܂œǂ݂Ƃ�
			// �ǂݍ��݁i�^�u�X�y�[�X���󂯂ĕs����N���Ȃ����͕s���j
			FileRead_scanf(FileHandle,
				//																																																			�L�����N�^�[�E���A																				�i����\��j											�L�����N�^�[�E���A																				�i����\��j											�L�����N�^�[�E�E�A																				�i����\��j											�L�����N�^�[�ύX�^�C�v�A							�L�����N�^�[�����ψꉻ�̃I���I�t�A																		�w�i�ύX�^�C�v�A�i�h�c�A�j																	�a�f�l�؂�ւ��^�C�v
				"%[^,],							%d[^,],									%[^,],						%[^,],						%[^,],						%[^,],		%d[^,],								%[^,],		%[^,],	%[^,],	%[^,],		%[^,],	%[^,],		%d[^,],							%[^,],			%d[^,],										%[^,],		%[^,],	%[^,],		%[^,],		%[^,],	%[^,],	%d[^,],					%[^,],					%d[^,],										%[^,],		%[^,],		%[^,],	%[^,],	%[^,],		%[^,],	%d[^,],					%[^,],					%d[^,],										%[^,],		%d[^,],									%[^,],		%d[^,],											%[^,],		%d[^,],							%[^,],		%d[^,],									%[^,],		%d[^,],			%[^,],					%d[^,],					%[^,],				%d[^,],						%[^,],										%d[^,],										%[^,],										%d[^,],										%[^,],										%d",
				&commu_state_edit[i].command,	&commu_state_edit[i].move_commu_number, &commu_state_edit[i].name,	&commu_state_edit[i].name2, &commu_state_edit[i].line,	&gomi[0],	&commu_state_edit[i].line_mouse,	&gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0],	&commu_state_edit[i].character[0], &gomi[0],	&commu_state_edit[i].character_face_etc[0],	&gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0],	&commu_state_edit[i].character[1], &gomi[0],	&commu_state_edit[i].character_face_etc[1],	&gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0], &gomi[0],	&commu_state_edit[i].character[2], &gomi[0],	&commu_state_edit[i].character_face_etc[2], &gomi[0], &commu_state_edit[i].character_change,	&gomi[0],	&commu_state_edit[i].character_even_distance,	&gomi[0], &commu_state_edit[i].background,	&gomi[0],	&commu_state_edit[i].background_change,	&gomi[0],	&commu_state_edit[i].bgm,	&gomi[0],	&commu_state_edit[i].bgm_change, &gomi[0],	&commu_state_edit[i].se,	&commu_state_edit[i].altenative_message[0], &commu_state_edit[i].altenative_jump[0],	&commu_state_edit[i].altenative_message[1], &commu_state_edit[i].altenative_jump[1],	&commu_state_edit[i].altenative_message[2], &commu_state_edit[i].altenative_jump[2]);
		}
		FileRead_close(FileHandle);	// �t�@�C�������
	}
	// �e�L�X�g�t�@�C���ǂݍ��݃e�X�g---
	else
	{
		// �t�@�C�����J���i�e�X�g�j
		int FileHandle = FileRead_open("media\\�߂���o��R�~��.txt");
		const int txt_line = 2048;	// �i�[�ł���txt�t�@�C���̍s���i�P�s�����̔z���ϐ��Ƃ��Đ錾�ł��Ȃ����߁A�萔�ɂ��邵���Ȃ��j
		char c[txt_line][256];	// �ꎞ�I�Ƀ������̓��e���L������ϐ�
		for (int i = 0; i < txt_line; i++) { sprintf_s(c[i], 256, ""); }	// ����������
		for (int i = 0; i < txt_line; i++) { FileRead_gets(c[i], 256, FileHandle); }	// �ꎞ�I�ȕϐ��Ƀ������̓��e���L�^����
		int x = 2;
		BOOL line_output_mode = FALSE;	// �䎌�ҏW���[�h�t���O
		int line_output_count = 0;		// �䎌�ҏW���[�h���̃J�E���g�p�ϐ�
		for (int i = 0; i < txt_line; i++)
		{
			char c2[3] = { c[i + 1][0] , c[i + 1][1] };	// ���̍s��1�A2�o�C�g�ڂ��擾���A�ꕶ���ɂ���
			char c6[3] = { c[i][0] , c[i][1] };			// ���݂̍s��1�A2�o�C�g�ڂ��擾���A�ꕶ���ɂ���
			if (strcmp(c2, "�u") != 0 && strcmp(c2, "�i") != 0 && line_output_mode == FALSE)
			{
				// �a�f�l�A�r�d��ǂݍ��ޏ���
				if (strcmp(c6, "��") == 0)
				{
					// �擪5�o�C�g���w��BGM�x�Ȃ�w��BGM:�x���폜������������r���Ĉ�v�����������ID��������
					//char c3[6] = { c[i + 1][0], c[i + 1][1], c[i + 1][2] , c[i + 1][3] , c[i + 1][4] };
					char c3[6] = { c[i][0], c[i][1], c[i][2] , c[i][3] , c[i][4] };
					if (strcmp(c3, "��BGM") == 0)
					{
						// ��v���Ă镶���񂪂���΁ABGM���w�肷��
						for (int j = 0; j < BGM_NUMBER; j++)
						{
							char c5[256];
							sprintf_s(c5, 256, "��BGM:%s", music_string[j].name);
							if (strcmp(c[i], c5) == 0) { commu_state_edit[x].BGMChange(j + 1); }
						}
					}
					// �擪4�o�C�g���w��SE�x�Ȃ�w��SE:�x���폜������������r���Ĉ�v�����������ID��������
					char c4[5] = { c[i][0], c[i][1], c[i][2] , c[i][3] };
					if (strcmp(c4, "��SE") == 0)
					{
						// ��v���Ă镶���񂪂���΁ASE���w�肷��
						for (int j = 0; j < SEData::GetNumber(); j++)
						{
							char c5[256];
							sprintf_s(c5, 256, "��SE:%s", se[j].GetName());
							if (strcmp(c[i], c5) == 0)
							{
								commu_state_edit[x].SEChange(j + 1);
								x++;
							}
						}
					}
				}
				else if (strcmp(c[i], "") != 0)
				{
					// line_output_count��1�Ȃ�@�}�[�N������
					if (line_output_count == 0)
					{
						sprintf_s(commu_state_edit[x].line, 256, "%s", c[i]); // ����������Ȃ炻����\���̂ɑ������
						line_output_count++;
					}
					else
					{
						commu_state_edit[x].LineConnection(c[i]);
						line_output_count = 0;
						x++;
					}
				}
				else
				{
					if (line_output_count >= 1)
					{
						line_output_count = 0;
						x++;
					}
				}
			}
			else
			{
				line_output_mode = TRUE;	// �䎌�ҏW���[�h�ɂ���
				// ���݂̕������䎌��ɂ���
				if (line_output_count == 0)
				{
					commu_state_edit[x].LineCharacterChange(0, c[i]);
					line_output_count++;
				}
				// �����񂪂���Α䎌����͂���
				else
				{
					if (strcmp(c[i], "") != 0)
					{
						// �擪�P�����ڂ��w�u�x�Ȃ�s��ς���
						if (strcmp(c6, "�u") == 0 && line_output_count == 2)
						{
							line_output_count = 1;
							x++;
							commu_state_edit[x].LineCharacterChange(0, commu_state_edit[x - 1].GetLineCharacterName());
						}

						if (line_output_count == 1)
						{
							// �䎌�傪������Ȃ���ΑO�s�̑䎌���������
							if (strcmp(commu_state_edit[x].GetLineCharacterName(), "") == 0) { commu_state_edit[x].LineCharacterChange(0, commu_state_edit[x - 1].GetLineCharacterName()); }

							commu_state_edit[x].LineChange(c[i]);
						}
						else
						{
							commu_state_edit[x].LineConnection(c[i]);
							line_output_count = 0;
							x++;
						}
						line_output_count++;
					}
					// �䎌�ҏW�t���O��Reset����
					else
					{
						line_output_count = 0;
						line_output_mode = FALSE;
						x++;
					}
				}
			}
		}

		// �Ō�Ɂwend�x�R�}���h������
		commu_state_edit[x].CommandChange((char*)"end");

		FileRead_close(FileHandle);
	}
	//----------------------------------

	// ���[�r�[�Đ��e�X�g
	//int MovieGraphHandle;
	//MovieGraphHandle = LoadGraph("media\\test.mp4");
	//PlayMovieToGraph(MovieGraphHandle);

	// �i�E�B���h�E�E��́w�~�x��Alt+F4�́A����ɂ����ProcessMessage��-1��Ԃ��������s���Ă���̂ŃE�B���h�E�������I�ɕ�����Ɠ����ɃR�[�h�ʂ�V�X�e���t�@�C���ۑ����s����j
	while ((ProcessMessage() == 0/* && CheckHitKey(KEY_INPUT_E) == 0*/) && quit_game == FALSE)
	{
		if (GetNowCount() - progress_frame_time >= progress_frame_need_time)	// 60�w���c�𒴂���o�b�ł�60�t���[�����b�œ��삷��悤�ɂ��Ă���
		{
			progress_frame_time = GetNowCount();
			progress_frame++;
			// 16�i�~���b�j * 20�i�t���[���j + 17 * 40 = 1000�i�~���b�j
			if (progress_frame % 3 == 0){ progress_frame_need_time = 16; }
			else{ progress_frame_need_time = 17; }
			// 1���[�v�ɂ����������Ԃ��v��
			int curtime = GetNowCount();
			g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
			g_lasttime = curtime;

			ClearDrawScreen();
			GetMousePoint(&MouseX, &MouseY);	// �}�E�X�̈ʒu���擾
			GameMusic();	// �a�f�l�̃t���[������
			switch (g_gamestate)
			{
			//case GAME_OPENING:
			//	DrawGameOpening();
			//	break;
			case GAME_FIRST_LOAD:
				g_time_load_start = GetNowCount();	// �ǂݍ��݊J�n���Ԃ��L�^����
				DrawLoading();						// �ǂݍ��݃A�C�R���\��
				if (LoadSE() == FALSE){ return -1; }
				// �K��~���b�o�߂��Ă��Ȃ���΋����Ƀ��[�h��Ԃ𑱂���i�e�X�g�j
				//if (GetNowCount() <= load_test + 5000){ g_gamestate = GAME_FIRST_LOAD; }	
				break;
			case GAME_TITLE:
				GameTitle();
				break;
			case GAME_MENU:
				DrawGameMenu();
				break;
			case GAME_MAIN_COMMUNICATION:
				GameMainCommunication();
				break;
			case GAME_MAP:
				GameMap();
				break;
			case GAME_SAVELOAD:
				GameSaveLoad();
				break;
			case GAME_TUTORIAL_END:	GameTutorialEnd();	break;
			case GAME_SOUNDROOM:
				SoundRoom();
				break;
			case GAME_COMMU_SELECT:	GameCommuSelect();	break;
			case GAME_COMMU_EDIT:	GameCommuEdit();	break;
			case GAME_CLEAR:
				DrawGameClear();
				break;
			case GAME_CONFIG:
				GameConfig();
				break;
			case GAME_TUTORIAL:
				DrawGameTutorial();
				break;
			case GAME_CONTINUE:
				DrawGameContinue();
				break;
			case GAME_ENDING:
				DrawGameEnding();
				break;
			default:
				break;
			}
			DebugProgram(DEBUG_MAIN);

			// �e�X�g
			//DrawGraph(0, 0, MovieGraphHandle, FALSE);
			//WaitTimer(10);

			ScreenFlip();
		}
	}
	// �Z�[�u����
	system_data.full_screen = flag_mode_window;						// �t���X�N���[���̃t���O
	system_data.screen_resolution = flag_full_hd_now;				// �𑜓x�̃t���O�iTRUE�Ȃ�1080px�j
	system_data.vol_bgm = bgm_volume;								// �a�f�l����
	system_data.vol_se = se_volume;									// �r�d����
	system_data.text_window_clear = text_window_clear_percentage;	// �e�L�X�g�E�B���h�E�����x
	system_data.string_speed = g_commumessagespeed;					// �����X�s�[�h
	system_data.dialog_appear = flag_dialog_appear;					// �_�C�A���O�{�b�N�X�\���t���O
	// �G�f�B�b�g���[�h�ł̌ʓǂݍ��݃t���O
	for (int i = 0; i < CharacterImage::GetCharacterMember(); i++){ system_data.SetECL(i, CharacterImage::GetLoadEdit(i)); }	

	err = fopen_s(&fp, "sr_system.dat", "wb");
	fwrite(&system_data, sizeof(system_data), 1, fp);

	fclose(fp);

	// �R�~���G�f�B�b�gcsv�t�@�C���쐬
	if (mode_debug == TRUE)
	{
		for (int j = 0; j < 2; j++)
		{
			std::ofstream myfile;
			char csv_export_name[256] = "";
			sprintf_s(csv_export_name, 256, "");
			if (j == 0) { sprintf_s(csv_export_name, 256, "media\\commu\\edit.csv"); }
			// �G�N�X�|�[�g�p�i���ݔN���������𓾂�j
			else
			{
				DATEDATA Date;		// DX���C�u�����Ǝ��̍\����
				GetDateTime(&Date);	// ���ݎ����𓾂�
				sprintf_s(csv_export_name, 256, "media\\export\\edit_%04d%02d%02d_%02d%02d%02d.csv", Date.Year, Date.Mon, Date.Day, Date.Hour, Date.Min, Date.Sec);
			}

			myfile.open(csv_export_name);
			myfile << ",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,�I�_\n";
			//myfile << "a,b,c,\n";
			//myfile << "c,s,v,\n";
			for (int i = 2; i < COMMU_LINE_MAX; i++)
			{
				char c_csv[512];
				sprintf_s(c_csv, 512, "%s,%d,%s,%s,%s,,%d,,,,,,,%d,,%d,,,,,,,%d,,%d,,,,,,,%d,,%d,,%d,,%d,,%d,,%d,,%d,,%d,,%d,%s,%d,%s,%d,%s,%d\n",
					commu_state_edit[i].GetCommand(),
					commu_state_edit[i].GetCommandNumber(),
					commu_state_edit[i].GetLineCharacterName(),
					commu_state_edit[i].GetLineCharacterName2(),
					commu_state_edit[i].GetLine(),
					commu_state_edit[i].GetLineMouse(),
					commu_state_edit[i].GetCharacter(0),
					commu_state_edit[i].GetCFE(0),
					commu_state_edit[i].GetCharacter(1),
					commu_state_edit[i].GetCFE(1),
					commu_state_edit[i].GetCharacter(2),
					commu_state_edit[i].GetCFE(2),
					commu_state_edit[i].GetCC(),
					commu_state_edit[i].GetCDU(),
					commu_state_edit[i].GetBackground(),
					commu_state_edit[i].GetBackgroundChangeType(),
					commu_state_edit[i].GetBGM(),
					commu_state_edit[i].GetBGMCT(),
					commu_state_edit[i].GetSE(),
					commu_state_edit[i].GetAlternativeString(0),
					commu_state_edit[i].GetAlternativeJump(0),
					commu_state_edit[i].GetAlternativeString(1),
					commu_state_edit[i].GetAlternativeJump(1),
					commu_state_edit[i].GetAlternativeString(2),
					commu_state_edit[i].GetAlternativeJump(2)
				);
				myfile << c_csv;
			}
			myfile.close();
		}
	}

	// �i�f�o�b�O�p�j�g���ĂȂ��w�i�̃f�[�^�����O�ɏo��
	DebugLog(LogOutputType::NOT_USE_BACKGROUND);
	// DX���C�u�����̏I������
	DxLib_End();

	return 0;
}
// ��ʉ𑜓x���`����
void ScreenResolutionChange()
{
	// �𑜓x��`�ɕK�v�ȕϐ���������
	if (flag_full_hd_now == TRUE)
	{
		screen_size_x = 1920;
		screen_size_y = 1080;
	}
	else
	{
		screen_size_x = 1280;
		screen_size_y = 720;
	}
	bairitu = (float)screen_size_y / WINDOW_SIZE_Y;	// ������摜�̔{�����Ē�`����
	font[0].ChangeMagnification(bairitu);
	SetGraphMode(screen_size_x, screen_size_y, 32);	// �E�B���h�E�T�C�Y��ύX����i��������ʂ�_�ł����Ă�j
	SetDrawScreen(DX_SCREEN_BACK);				// �`���𗠉�ʂɂ���
}
// �^�C�g���f����ʕ`��
void DrawGameOpening()
{
}
// ���j���[��ʕ`��
void DrawGameMenu()
{
}
// �Q�[���N���A��ʕ`��
void DrawGameClear()
{
}
// �������[�h
void DrawGameTutorial()
{
}
// �R���e�j���[���
void DrawGameContinue()
{
}
// �G���f�B���O
void DrawGameEnding()
{
}
// �L�[�g���K�[�����i��L�[�j
BOOL IsUPKeyTrigger(int key, int y)
{
	if (key & PAD_INPUT_UP)
	{
		if (g_upkey_prev[y] == FALSE)
		{
			g_upkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else{ g_upkey_prev[y] = FALSE; }

	return FALSE;
}
// �L�[�g���K�[�����i���L�[�j
BOOL IsDOWNKeyTrigger(int key, int y)
{
	if (key & PAD_INPUT_DOWN)
	{
		if (g_downkey_prev[y] == FALSE)
		{
			g_downkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else{ g_downkey_prev[y] = FALSE; }

	return FALSE;
}
// �L�[�g���K�[�����i���L�[�j
BOOL IsLEFTKeyTrigger(int key, int y)
{
	if (key & PAD_INPUT_LEFT)
	{
		if (g_leftkey_prev[y] == FALSE)
		{
			g_leftkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else{ g_leftkey_prev[y] = FALSE; }

	return FALSE;
}
// �L�[�g���K�[�����i�E�L�[�j
BOOL IsRIGHTKeyTrigger(int key, int y)
{
	if (key & PAD_INPUT_RIGHT)
	{
		if (g_rightkey_prev[y] == FALSE)
		{
			g_rightkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else{ g_rightkey_prev[y] = FALSE; }

	return FALSE;
}
// �L�[�g���K�[�����i�G���^�[�L�[�j
BOOL IsENTERKeyTrigger(int key, int y)
{
	// �i�`�F�b�N�q�b�g�L�[�H�j
	if (CheckHitKey(KEY_INPUT_NUMPADENTER) == TRUE)
	{
		if (g_enterkey_prev[y] == FALSE)
		{
			g_enterkey_prev[y] = TRUE;
			return TRUE;
		}
	}
	else { g_enterkey_prev[y] = FALSE; }

	return FALSE;
}
// �N���b�N���ꂽ�^�C�~���O��󋵂ɉ������t���O��Ԃ�
BOOL ClickFlagCheck(int Cx, int Cy, int Jx, int Jy, int breadth, int length, BOOL z, BOOL a)	// �N���b�Nx���W,�N���b�Ny���W,���荶�[x���W,�����[y���W,���W����,���W�c��,���{�^���������ꂽ�������ꂽ�����ʂ���t���O,�����Ƃ��Ďg�p����ϐ��iz��TRUE�Ȃ�wFALSE�x�ł����j
{
	if (z == TRUE)
	{	
		// �N���b�N�̍��W������͈͓̔��Ȃ�TRUE��Ԃ�
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1){  return TRUE; }
	}
	else
	{
		// �N���b�N�̍��W������͈͓̔��ł���A���������̃t���O�������Ă���Ȃ�TRUE��Ԃ�
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1 && a == TRUE){ return TRUE; }
	}
	return FALSE;
}
// �N���b�N���ꂽ�^�C�~���O��󋵂ɉ������t���O��Ԃ��ifloat�ϐ��wbairitu�x��������j
BOOL ClickFlagCheck2(int Cx, int Cy, int Jx, int Jy, int breadth, int length, BOOL z, BOOL a)	// �N���b�Nx���W,�N���b�Ny���W,���荶�[x���W,�����[y���W,���W����,���W�c��,���{�^���������ꂽ�������ꂽ�����ʂ���t���O,�����Ƃ��Ďg�p����ϐ��iz��TRUE�Ȃ�wFALSE�x�ł����j
{
	if (z == TRUE)
	{
		// �N���b�N�̍��W������͈͓̔��Ȃ�TRUE��Ԃ�
		if (Cx >= Jx * bairitu && Cx <= (Jx - 1) * bairitu + breadth && Cy >= Jy * bairitu && Cy <= (Jy + length - 1) * bairitu){ return TRUE; }
	}
	else
	{
		// �N���b�N�̍��W������͈͓̔��ł���A���������̃t���O�������Ă���Ȃ�TRUE��Ԃ�
		if (Cx >= Jx * bairitu && Cx <= (Jx - 1) * bairitu + breadth && Cy >= Jy * bairitu && Cy <= (Jy + length - 1) * bairitu && a == TRUE){ return TRUE; }
	}
	return FALSE;
}
// �N���b�N���ꂽ�^�C�~���O��󋵂ɉ������t���O��Ԃ��i�񋓒萔�ɉ����ď����̃t���O���ǉ������j
BOOL ClickFlagCheckF2(int Cx, int Cy, float Jx, float Jy, float breadth, float length, BOOL z, BOOL a, ClickFlagCheckType type)	// �N���b�Nx���W,�N���b�Ny���W,���荶�[x���W,�����[y���W,���W����,���W�c��,���{�^���������ꂽ�������ꂽ�����ʂ���t���O,�����Ƃ��Ďg�p����ϐ��iz��TRUE�Ȃ�wFALSE�x�ł����j,�Ăяo���^�C�~���O�i����̗L���𔻕ʂ���񋓒萔�j
{
	if (z == TRUE)
	{
		// �N���b�N�̍��W������͈͓̔��ł���A�wtype�x���̏����𖞂����Ă���i�����蔻�肪���݂��Ă���j�Ȃ�TRUE��Ԃ�
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1)
		{ 
			switch(type)
			{
			case CFC_COMMU_MENU:	if (commu_mode_menu == TRUE && commu_mode_text_off == FALSE) { return TRUE; }	break;
			case CFC_COMMU_TEXT:	if (commu_mode_text_off == FALSE) { return TRUE; }								break;
			default:				return TRUE;																	break;
			}
		}
	}
	else
	{
		// �N���b�N�̍��W������͈͓̔��ł���A���������̃t���O�������Ă���Ȃ�TRUE��Ԃ�
		if (Cx >= Jx && Cx <= Jx + breadth - 1 && Cy >= Jy && Cy <= Jy + length - 1 && a == TRUE) { return TRUE; }
	}
	return FALSE;
}
