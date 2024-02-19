#include "gamecommuedit.h"

EditType g_edittype;											// ���݉��̋@�\��ҏW���Ă��邩
EditCharacterType g_editcharactertype = EDIT_CHARACTER_BODY;	// �L�����N�^�[�̂ǂ̕�����ҏW���Ă��邩
CommandInputStringType g_commandinputstring = CIS_NULL;		// �����ݓ��͂��Ă���R�}���h�n������

//BackgroundName background_name[BACKGROUND_NUMBER] = { 
//	{(char*)"�߂���̕���"},{(char*)"�ƒ�Ȏ�"},		{(char*)"�y��"},		{(char*)"�Z��O"},	{(char*)"�e���X"},
//	{(char*)"�L��"},		{(char*)"���O�E�f���O"},	{(char*)"�O�̊w�Z"} ,	{(char*)"����"} ,	{(char*)"�E����"} };


/* GlobalStaticEdit�N���X ---------*/
// �w�i�I�����p
int GlobalStaticEdit::background_alternative_row = 0;
int GlobalStaticEdit::background_alternative_line = 0;				// �s�J�[�\��
int GlobalStaticEdit::background_alternative_line_limit = 1;		// �s�̍ő吔
int GlobalStaticEdit::background_alternative_line_draw = 0;			// �P�i�ڂɕ`�悷��s
const int GlobalStaticEdit::BACKGROUND_ALTERNATIVE_LINE_NUMBER = 2;	// �P�s�ɕ��Ԕw�i��
void GlobalStaticEdit::SetBackgroundAlternativeRow(int x)
{
	background_alternative_row += x;
	// �㉺���𒴂����J�[�\�����C������
	if (background_alternative_row < 0) { background_alternative_row = 0; }
	else if (background_alternative_row >= BACKGROUND_ALTERNATIVE_LINE_NUMBER) { background_alternative_row = BACKGROUND_ALTERNATIVE_LINE_NUMBER - 1; }
}
void GlobalStaticEdit::SetBackgroundAlternativeLine(int x)
{
	background_alternative_line += x;
	// �㉺���𒴂����J�[�\�����C������
	if (background_alternative_line < 0) { background_alternative_line = 0; }
	else if (background_alternative_line >= background_alternative_line_limit) { background_alternative_line = background_alternative_line_limit - 1; }
	// �`��s��ς��鏈��
	if (background_alternative_line < background_alternative_line_draw) { background_alternative_line_draw = background_alternative_line; }
	else if (background_alternative_line >= background_alternative_line_draw + BACKGROUND_ALTERNATIVE_LINE_NUMBER) { background_alternative_line_draw = background_alternative_line - BACKGROUND_ALTERNATIVE_LINE_NUMBER + 1; }
}
/*---------------------------------*/
char c_global_function[256] = "";	// char�֐��̕Ԃ�l�Ƃ��Ďg���ϐ��i���[�J���z��ϐ���return�ň����Ȃ��̂ŃO���[�o���ϐ��ɂ���K�v������j

BOOL commu_edit_input_string;	// �i�䎌��ҏW���Ɂj�����̓��͂��s���Ă����Ԃ�
BOOL g_inputbkey_prev;			// ���O�̃L�[�{�[�h�a�L�[�̏��
BOOL g_1key_prev;				// ���O�̃L�[�{�[�h1�L�[�̏��
BOOL g_2key_prev;				// ���O�̃L�[�{�[�h2�L�[�̏��
BOOL g_3key_prev;				// ���O�̃L�[�{�[�h3�L�[�̏��
BOOL g_4key_prev;				// ���O�̃L�[�{�[�h4�L�[�̏��
BOOL g_5key_prev;				// ���O�̃L�[�{�[�h5�L�[�̏��
BOOL g_6key_prev;				// ���O�̃L�[�{�[�h6�L�[�̏��
BOOL g_7key_prev;				// ���O�̃L�[�{�[�h7�L�[�̏��
BOOL g_8key_prev;				// ���O�̃L�[�{�[�h8�L�[�̏��
BOOL g_9key_prev;				// ���O�̃L�[�{�[�h9�L�[�̏��
BOOL g_0key_prev;				// ���O�̃L�[�{�[�h0�L�[�̏��
BOOL edit_insert_prev;			// ���O�̑}�����씻��̏��
BOOL edit_copy_paste_prev;		// ���O�̃R�s�y���씻��̏��
BOOL edit_delete_prev;			// ���O�̍s�폜�̏��

int edit_row = 0;												// ���ݕҏW���悤�Ƃ��Ă������
int edit_row_background = 1;									// ���ݕҏW���悤�Ƃ��Ă���w�i�̃y�[�W
int edit_row_bgm = 0;											// ���ݕҏW���悤�Ƃ��Ă���a�f�l�̃y�[�W
int edit_row_se = 0;											// ���ݕҏW���悤�Ƃ��Ă���r�d�̃y�[�W
int edit_line = 2;												// ���ݕҏW���Ă���s��
int edit_play_bgm = 0;											// �G�f�B�b�g���[�h�Ō��ݗ���Ă���a�f�l�h�c
int edit_character_id[256][EDIT_CHARACTER_ALTERNATIVE_X_LIMIT];	// �����G�I�����ɕK�v�ȃL�����h�c
int edit_character_alternative_row = 0;							// �L�����I�����p�̗�J�[�\��
int edit_character_alternative_line = 0;						// �L�����I�����p�̍s�J�[�\��
int edit_character_alternative_line_limit = 1;					// �L�����I�����p�̍s�̍ő吔

// GAME_COMMU_EDIT��Ԃ̃��C������
void GameCommuEdit()
{
	GameCommuEditControl();
	DrawGameCommuEdit();
}
// �R�~���G�f�B�b�g��ʑ��쏈��
void GameCommuEditControl()
{
	int key = GetJoypadInputState(DX_INPUT_KEY);
	// �������͎�
	if(g_edittype == EDIT_LINES || commu_edit_input_string == TRUE)
	{ 
		// �䎌�̓��͂�����������
		if (CheckKeyInput(InputHandle) != 0)
		{
			// �G�X�P�[�v�L�[�ɂ��I���łȂ���Γ��͂��ꂽ��������擾
			if (CheckHitKey(KEY_INPUT_ESCAPE) == FALSE) 
			{
				switch (g_edittype)
				{
				case EDIT_LINES_CHARACTER:	commu_state_edit[edit_line].LineCharacterChange(0, InputHandle);	break;
				case EDIT_LINES_CHARACTER2:	commu_state_edit[edit_line].LineCharacterChange(1, InputHandle);	break;
				case EDIT_LINES:			commu_state_edit[edit_line].LineChange(InputHandle);				break;
				default:																						break;
				}
				// �R�}���h�n
				if (g_commandinputstring == CIS_FRAME_AUTO || g_commandinputstring == CIS_MOVE_SELL || g_commandinputstring == CIS_MOVE_COMMU) { commu_state_edit[edit_line].CommandNumberChange(GetKeyInputNumber(InputHandle)); }
				if (g_commandinputstring >= CIS_ALTERNATIVE2_1 && g_commandinputstring <= CIS_ALTERNATIVE3_3){commu_state_edit[edit_line].AlternativeChange(g_commandinputstring <= CIS_ALTERNATIVE2_2 ? g_commandinputstring - CIS_ALTERNATIVE2_1 : g_commandinputstring - CIS_ALTERNATIVE3_1, InputHandle); }
				// �i�K���Ȑ��l������j
				//if (g_commandinputstring >= CIS_ALTERNATIVE2_1 && g_commandinputstring <= CIS_ALTERNATIVE3_3) { commu_state_edit[edit_line].AlternativeJumpChange
				//( , GetKeyInputNumber(InputHandle)); }
				switch (g_commandinputstring)
				{
				case CIS_FRAME_AUTO:			
					commu_state_edit[edit_line].CommandChange((char*)"frame_auto");		
					g_commandinputstring = CIS_NULL;
					break;
				case CIS_MOVE_SELL:
					commu_state_edit[edit_line].CommandChange((char*)"move_sell");
					g_commandinputstring = CIS_NULL;
					break;
				case CIS_MOVE_COMMU:			
					commu_state_edit[edit_line].CommandChange((char*)"move_commu");		
					g_commandinputstring = CIS_NULL;
					break;
				case CIS_ALTERNATIVE2_1:		commu_state_edit[edit_line].AlternativeChange(0 ,InputHandle);		break;
				case CIS_ALTERNATIVE2_2:		commu_state_edit[edit_line].AlternativeChange(1, InputHandle);		break;
				case CIS_ALTERNATIVE3_1:		commu_state_edit[edit_line].AlternativeChange(0, InputHandle);		break;
				case CIS_ALTERNATIVE3_2:		commu_state_edit[edit_line].AlternativeChange(1, InputHandle);		break;
				case CIS_ALTERNATIVE3_3:		commu_state_edit[edit_line].AlternativeChange(2, InputHandle);		break;
				case CIS_ALTERNATIVE_JUMP2_1:	commu_state_edit[edit_line].AlternativeJumpChange(0, GetKeyInputNumber(InputHandle));	break;
				case CIS_ALTERNATIVE_JUMP2_2:
					commu_state_edit[edit_line].CommandChange((char*)"altenative_2");	
					g_commandinputstring = CIS_NULL;
					commu_state_edit[edit_line].AlternativeJumpChange(1, GetKeyInputNumber(InputHandle));
					break;
				case CIS_ALTERNATIVE_JUMP3_1:	commu_state_edit[edit_line].AlternativeJumpChange(0, GetKeyInputNumber(InputHandle));	break;
				case CIS_ALTERNATIVE_JUMP3_2:	commu_state_edit[edit_line].AlternativeJumpChange(1, GetKeyInputNumber(InputHandle));	break;
				case CIS_ALTERNATIVE_JUMP3_3:
					commu_state_edit[edit_line].CommandChange((char*)"altenative_3");	
					g_commandinputstring = CIS_NULL;
					commu_state_edit[edit_line].AlternativeJumpChange(2, GetKeyInputNumber(InputHandle));
					break;
				default:																							
					break;
				}
			}
			else
			{
				g_commandinputstring = CIS_NULL;
			}
			DeleteKeyInput(InputHandle);
			g_edittype = EDIT_DEFAULT;
			commu_edit_input_string = FALSE;			// EDIT_LINES��Ԃ̎��ɂ��łɂ��̏��������Ă����炭���Ȃ�
			// �����ɉ����čĂѕ�������͂����Ԃɂ���
			if (CheckHitKey(KEY_INPUT_ESCAPE) == FALSE)
			{
				switch (g_commandinputstring)
				{
				case CIS_ALTERNATIVE2_1:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP2_1);	break;
				case CIS_ALTERNATIVE2_2:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP2_2);	break;
				case CIS_ALTERNATIVE3_1:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP3_1);	break;
				case CIS_ALTERNATIVE3_2:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP3_2);	break;
				case CIS_ALTERNATIVE3_3:		GameCommuEditAlternativeInput(CIS_ALTERNATIVE_JUMP3_3);	break;
				case CIS_ALTERNATIVE_JUMP2_1:	GameCommuEditAlternativeInput(CIS_ALTERNATIVE2_2);		break;
				case CIS_ALTERNATIVE_JUMP3_1:	GameCommuEditAlternativeInput(CIS_ALTERNATIVE3_2);		break;
				case CIS_ALTERNATIVE_JUMP3_2:	GameCommuEditAlternativeInput(CIS_ALTERNATIVE3_3);		break;
				default:																				break;
				}
			}
			if (IsENTERKeyTrigger(key, 0) == TRUE) {}	// �������͊m�聨�f�t�H���g��Ԃő����ɍ��ڊm��̌�쓮��h�����߂̃`�F�b�N�����̏���
		}
	}
	else
	{
		// ���E�L�[�ɉ����ĕҏW���e����ω�������
		if (IsLEFTKeyTrigger(key, 0) == TRUE)
		{
			switch (g_edittype)
			{
			case EDIT_DEFAULT:
				if (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) { edit_row = 0; }
				else if (edit_row > 0) { edit_row--; }						
				break;
			case EDIT_CHARACTER_LEFT:	
			case EDIT_CHARACTER_CENTER:
			case EDIT_CHARACTER_RIGHT:
				if (edit_character_alternative_row > 0) { edit_character_alternative_row--; }
				break;
			case EDIT_BACKGROUND:
				if (edit_row_background > 0) { edit_row_background--; }
				GlobalStaticEdit::SetBackgroundAlternativeRow(-1);
				break;
			case EDIT_BGM:			if (edit_row_bgm > 0) { edit_row_bgm--; }				break;
			case EDIT_SE:			if (edit_row_se > 0) { edit_row_se--; }					break;
			default:																		break;
			}
		}
		if (IsRIGHTKeyTrigger(key, 0) == TRUE)
		{
			switch (g_edittype)
			{
			case EDIT_DEFAULT:
				if (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) { edit_row = EDIT_SELECT_PAGE_MAX; }
				else if (edit_row < EDIT_SELECT_PAGE_MAX) { edit_row++; }
				break;
			case EDIT_CHARACTER_LEFT:
			case EDIT_CHARACTER_CENTER:
			case EDIT_CHARACTER_RIGHT:
				if (edit_character_alternative_row < EDIT_CHARACTER_ALTERNATIVE_X_LIMIT - 1) { edit_character_alternative_row++; }
				break;
			#pragma region ver0.00704���쎞�R�����g���R�[�h
			//case EDIT_BACKGROUND:	if (edit_row_background < (BACKGROUND_NUMBER - 1) / 10 + 1) { edit_row_background++; }	break;
#pragma endregion
			case EDIT_BACKGROUND:
				if (edit_row_background < (bgimage[0].GetNumber() - 1) / 10 + 1) { edit_row_background++; }
				GlobalStaticEdit::SetBackgroundAlternativeRow(1);
				break;
			case EDIT_BGM:			if (edit_row_bgm < (BGMData::GetNumber() - 1) / 10 + 1) { edit_row_bgm++; }												break;
			#pragma region ver0.00707���쎞�R�����g���R�[�h
			//case EDIT_SE:			if (edit_row_se < SE_NUMBER / 10 + 1) { edit_row_se++; }								break;
#pragma endregion
			case EDIT_SE:			if (edit_row_se < SEData::GetNumber() / 10 + 1) { edit_row_se++; }								break;
			default:																										break;
			}
		}
		// �������ςȂ��̃L�[�ɉ����ē����s�̌�����ς���
		int move_line_times = 1;
		if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE) { move_line_times = 100; }
		else if (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) { move_line_times = 10; }
		// �㉺�L�[�ɉ����ĕҏW�s��ω�������
		//if (IsUPKeyTrigger(key, 0) == TRUE && edit_line > 2)
		if (IsUPKeyTrigger(key, 0) == TRUE)
		{
			//if (g_edittype == EDIT_DEFAULT) { edit_line--; }
			if (g_edittype == EDIT_DEFAULT) 
			{ 
				edit_line -= move_line_times;
				if (edit_line < 2) { edit_line = 2; }
			}
			// �L�����N�^�[�I����
			else if (g_edittype >= EDIT_CHARACTER_LEFT && g_edittype <= EDIT_CHARACTER_RIGHT && edit_character_alternative_line > 0) { edit_character_alternative_line--; }
			// �w�i�I����
			else if (g_edittype == EDIT_BACKGROUND) { GlobalStaticEdit::SetBackgroundAlternativeLine(-1); }
		}
		//if (IsDOWNKeyTrigger(key, 0) == TRUE && edit_line < COMMU_LINE_MAX_EDIT - 1)
		if (IsDOWNKeyTrigger(key, 0) == TRUE)
		{
			//if (g_edittype == EDIT_DEFAULT) { edit_line++; }
			if (g_edittype == EDIT_DEFAULT)
			{
				edit_line += move_line_times;
				if (edit_line > COMMU_LINE_MAX_EDIT - 1) { edit_line = COMMU_LINE_MAX_EDIT - 1; }
			}
			// �L�����N�^�[�I����
			else if (g_edittype >= EDIT_CHARACTER_LEFT && g_edittype <= EDIT_CHARACTER_RIGHT && edit_character_alternative_line < edit_character_alternative_line_limit - 1) { edit_character_alternative_line++; }
			// �w�i�I�����i�Ȃ����ł��Ȃ��j
			else if (g_edittype == EDIT_BACKGROUND) { GlobalStaticEdit::SetBackgroundAlternativeLine(1); }
		}

		if (IsINPUTBKeyTrigger() == TRUE)
		{
			int edit_commu_number = static_cast<int>(CommuType::EDIT);
			switch (g_edittype)
			{
			// �R�~���Z���N�g�p�G�f�B�b�g�R�~���ɃG�f�B�b�g���e���R�s�y���ă^�C�g���֖߂�
			case EDIT_DEFAULT:
				for (int i = 2; i < COMMU_LINE_MAX; i++)
				{
					//HM[edit_commu_number][i - 2](commu_state_edit[i]());	// 
					HM[edit_commu_number][i - 2].CommandChange(commu_state_edit[i].GetCommand());						// �R�}���h
					HM[edit_commu_number][i - 2].CommandNumberChange(commu_state_edit[i].GetCommandNumber());			// �e����R�}���h�p���l
					HM[edit_commu_number][i - 2].LineCharacterChange(0, commu_state_edit[i].GetLineCharacterName());	// �䎌��
					HM[edit_commu_number][i - 2].LineCharacterChange(1, commu_state_edit[i].GetLineCharacterName2());	// �䎌��Q
					HM[edit_commu_number][i - 2].LineChange(commu_state_edit[i].GetLine());								// �䎌
					HM[edit_commu_number][i - 2].LineMouseChange(commu_state_edit[i].GetLineMouse());					// �䎌���p�N�^�C�v
					for(int j = 0; j < 3; j++)
					{
						HM[edit_commu_number][i - 2].CharacterIDChange(j, commu_state_edit[i].GetCharacter(j));				// �L�����N�^�[�h�c
						HM[edit_commu_number][i - 2].CFECHANGE(j, commu_state_edit[i].GetCFE(j));							// �L�����N�^�[����\��
						HM[edit_commu_number][i - 2].AlternativeChange(j, commu_state_edit[i].GetAlternativeString(j));		// �I����������
						HM[edit_commu_number][i - 2].AlternativeJumpChange(j, commu_state_edit[i].GetAlternativeJump(j));	// �I�����W�����v��s
					}
					HM[edit_commu_number][i - 2].CCCHANGE(commu_state_edit[i].GetCC());										// �L�����N�^�[�ύX�^�C�v
					HM[edit_commu_number][i - 2].CDUCHANGE(commu_state_edit[i].GetCDU());									// �L�����ԋ����ψꉻ
					HM[edit_commu_number][i - 2].BackgroundChange(commu_state_edit[i].GetBackground());						// �w�i
					HM[edit_commu_number][i - 2].BackgroundChangeTypeChange(commu_state_edit[i].GetBackgroundChangeType());	// �w�i�ύX�^�C�v
					HM[edit_commu_number][i - 2].BGMChange(commu_state_edit[i].GetBGM());	// �a�f�l
					HM[edit_commu_number][i - 2].BCTChange(commu_state_edit[i].GetBGMCT());	// �a�f�l�ύX�^�C�v
					HM[edit_commu_number][i - 2].SEChange(commu_state_edit[i].GetSE());		// �r�d

				}
				GameTitleNext();
				break;	

				//case EDIT_COMMAND_NUMBER:						break;
			default:					g_edittype = EDIT_DEFAULT;	break;
			}
		}
		// D�L�[���������^�C�~���O�ɉ����ėl�X�Ȃ��̂����肷��		
		if (CheckHitKey(KEY_INPUT_D) == TRUE) 
		{ 
			if (g_edittype == EDIT_DEFAULT)
			{
				if (edit_row == EDIT_SELECT_LINES) { commu_state_edit[edit_line].LineChange((char*)""); }					// �䎌��S�폜����
				// �L�����ϐ�������������
				else if (edit_row == EDIT_SELECT_CHARACTER_LEFT) { commu_state_edit[edit_line].CharacterIDChange(0, 0); }
				else if (edit_row == EDIT_SELECT_CHARACTER_CENTER) { commu_state_edit[edit_line].CharacterIDChange(1, 0); }
				else if (edit_row == EDIT_SELECT_CHARACTER_RIGHT) { commu_state_edit[edit_line].CharacterIDChange(2, 0); }
			}
		}
		// �G���^�[���������^�C�~���O�ɉ����ėl�X�Ȃ��̂����肷��
		if (IsENTERKeyTrigger(key, 0) == TRUE)
		{
			char* c_line = commu_state_edit[edit_line].line;	// �L�[���͂�����ہA�O��̑䎌���e��\�������邽�߂̕ϐ�
			switch (g_edittype)
			{
			case EDIT_DEFAULT:
				// edit_row���ʒu���Ă����ꏊ�ɉ����ĕҏW������̂��ς��
				switch (edit_row)
				{
				case EDIT_SELECT_COMMAND:			g_edittype = EDIT_COMMAND;			break;
				case EDIT_SELECT_LINES_CHARACTER:	g_edittype = EDIT_LINES_CHARACTER;	break;
				case EDIT_SELECT_LINES_CHARACTER2:	g_edittype = EDIT_LINES_CHARACTER2;	break;
				case EDIT_SELECT_LINES:
					GameCommuEditInputString(105, FALSE,c_line);	// �u�v���]���ɏo�Ă��܂��̂�101�̂Ƃ����̐����ɂ��Ă���
					g_edittype = EDIT_LINES;
					break;
				case EDIT_SELECT_LINES_MOUSE:		g_edittype = EDIT_LINES_MOUSE;		break;
				case EDIT_SELECT_CHARACTER_LEFT:	
					g_edittype = EDIT_CHARACTER_LEFT;	
					g_editcharactertype = EDIT_CHARACTER_BODY;
					break;
				case EDIT_SELECT_CHARACTER_CENTER:
					g_edittype = EDIT_CHARACTER_CENTER;
					g_editcharactertype = EDIT_CHARACTER_BODY;
					break;
				case EDIT_SELECT_CHARACTER_RIGHT:
					g_edittype = EDIT_CHARACTER_RIGHT;
					g_editcharactertype = EDIT_CHARACTER_BODY;
					break;
				case EDIT_SELECT_BACKGROUND:
					g_edittype = EDIT_BACKGROUND;
					edit_row_background = 1;
					break;
				case EDIT_SELECT_BGM:
					g_edittype = EDIT_BGM;
					edit_row_bgm = 1;
					break;
				case EDIT_SELECT_SE:
					g_edittype = EDIT_SE;
					edit_row_se = 1;
					break;
				default:																break;
				}
				break;
			case EDIT_CHARACTER_LEFT:
			case EDIT_CHARACTER_CENTER:
			case EDIT_CHARACTER_RIGHT:
				commu_state_edit[edit_line].CharacterIDChange(g_edittype - EDIT_CHARACTER_LEFT, edit_character_id[edit_character_alternative_line][edit_character_alternative_row]);
				g_edittype = EDIT_DEFAULT;
				break;
			default:																	break;
			}

		}
		if (g_edittype == EDIT_DEFAULT)
		{
			// �󔒍s�}��
			if (IsInsertTrigger() == TRUE)
			{
				for (int i = COMMU_LINE_MAX_EDIT - 1; i >= edit_line; i--)
				{
					GameCommuEditLineErase(i);								// �s�̓��e����������
					if (i > edit_line) { GameCommuEditLineCopy(i, i - 1, 1); }	// �ҏW���̍s�łȂ����i�s�ڂ�i-1�s�ڂ̓��e���R�s�[����
				}
			}
			// �s�R�s�[�}��
			if (IsCopyPasteTrigger() == TRUE)
			{
				for (int i = COMMU_LINE_MAX_EDIT - 1; i >= edit_line; i--)
				{
					GameCommuEditLineErase(i);								// �s�̓��e����������
					if (i > edit_line) { GameCommuEditLineCopy(i, i - 1, 1); }	// �ҏW���̍s�łȂ����i�s�ڂ�i-1�s�ڂ̓��e���R�s�[����
				}
				GameCommuEditLineCopy(edit_line, edit_line + 1, 0);	// �I���s�Ɂw�I���s+1�x�s�ڂ̓��e���R�s�[����
			}
			// �s�폜
			if (IsDeleteTrigger() == TRUE)
			{
				for (int i = edit_line; i < COMMU_LINE_MAX_EDIT - 1; i++) { GameCommuEditLineCopy(i, i + 1, -1); }
				GameCommuEditLineErase(COMMU_LINE_MAX_EDIT - 1);	// �Ō�̍s�͍폜����
			}
		}
		// �R�}���h�I�����̏���
		if (g_edittype == EDIT_COMMAND && g_commandinputstring == CIS_NULL)
		{
			if (CheckHitKey(KEY_INPUT_2) == TRUE || CheckHitKey(KEY_INPUT_5) == TRUE || CheckHitKey(KEY_INPUT_7) == TRUE) { GameCommuEditInputString(3, TRUE, (char*)""); }
			else if (CheckHitKey(KEY_INPUT_3) == TRUE || CheckHitKey(KEY_INPUT_4) == TRUE) { GameCommuEditInputString(33, FALSE, (char*)""); }

			if (Is1KeyTrigger() == TRUE) 
			{ 
				commu_state_edit[edit_line].CommandChange((char*)"auto_se");
				g_edittype = EDIT_DEFAULT;
			}
			else if (Is2KeyTrigger() == TRUE) { g_commandinputstring = CIS_FRAME_AUTO; }
			else if (Is3KeyTrigger() == TRUE) { g_commandinputstring = CIS_ALTERNATIVE2_1; }
			else if (Is4KeyTrigger() == TRUE) { g_commandinputstring = CIS_ALTERNATIVE3_1; }
			else if (Is5KeyTrigger() == TRUE) { g_commandinputstring = CIS_MOVE_SELL; }
			else if (Is6KeyTrigger() == TRUE) 
			{ 
				sprintf_s(commu_state_edit[edit_line].command, 256, "end");
				g_edittype = EDIT_DEFAULT;
			}
			else if (Is7KeyTrigger() == TRUE) { g_commandinputstring = CIS_MOVE_COMMU; }
			else if (Is8KeyTrigger() == TRUE) { g_edittype = EDIT_TEXT_WINDOW; }
			else if (CheckHitKey(KEY_INPUT_D) == TRUE)
			{
				sprintf_s(commu_state_edit[edit_line].command, 256, "");
				commu_state_edit[edit_line].CommandNumberChange(0);	// ���łɃR�}���h�p���l��������
				g_edittype = EDIT_DEFAULT;
			}
		}
		// �e�L�X�g�E�B���h�E�F�I�����̏���
		if (g_edittype == EDIT_TEXT_WINDOW)
		{
			if (Is1KeyTrigger() == TRUE) { GameCommuEditTextWindow(1); }
			else if (Is2KeyTrigger() == TRUE) { GameCommuEditTextWindow(2); }
			else if (Is3KeyTrigger() == TRUE) { GameCommuEditTextWindow(3); }
			else if (Is4KeyTrigger() == TRUE) { GameCommuEditTextWindow(4); }
		}
		// �䎌��I�����̏���
		if (g_edittype >= EDIT_LINES_CHARACTER && g_edittype <= EDIT_LINES_CHARACTER2)
		{
			if (Is1KeyTrigger() == TRUE)		{ GameCommuEditLinesCharacter((char*)"��l��"); }
			else if (Is2KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"�߂���"); }
			else if (Is3KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"����"); }
			else if (Is4KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"����"); }
			else if (Is5KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"�z��"); }
			else if (Is6KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"���"); }
			else if (Is7KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"�͂Â�"); }
			else if (Is8KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"�Z��"); }
			else if (Is9KeyTrigger() == TRUE)	{ GameCommuEditLinesCharacter((char*)"�ꓯ"); }
			// �䎌�厩�R���̓��[�h�Ɉڍs
			else if (Is0KeyTrigger() == TRUE) {	GameCommuEditInputString(16, FALSE,(char*)"");}
			else if (CheckHitKey(KEY_INPUT_D) == TRUE) { GameCommuEditLinesCharacter((char*)""); }
		}
		// ���p�N�^�C�v�I�����̏���
		if (g_edittype == EDIT_LINES_MOUSE)
		{
			if (Is1KeyTrigger() == TRUE) { GameCommuEditLinesMouse(-1); }
			else if (Is2KeyTrigger() == TRUE) { GameCommuEditLinesMouse(1); }
			else if (Is3KeyTrigger() == TRUE) { GameCommuEditLinesMouse(2); }
			else if (Is4KeyTrigger() == TRUE) { GameCommuEditLinesMouse(3); }
			else if (CheckHitKey(KEY_INPUT_D) == TRUE) { GameCommuEditLinesMouse(0); }
		}
		// �L�����N�^�[�I�����̏���
		if (g_edittype >= EDIT_CHARACTER_LEFT && g_edittype <= EDIT_CHARACTER_RIGHT)
		{
			//int x = g_edittype - EDIT_CHARACTER_LEFT;
			//// HM[j][i].character[x]��1000�̈ʂ������āA���͂��ꂽ���~1000��ǉ�����
			//if (g_editcharactertype == EDIT_CHARACTER_BODY)
			//{
			//	if (Is0KeyTrigger() == TRUE)
			//	{ 
			//		commu_state_edit[edit_line].CharacterIDChange(x, -1000);
			//		g_edittype = EDIT_DEFAULT;
			//	}
			//	else if (Is1KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 1); }
			//	else if (Is2KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 2); }
			//	else if (Is3KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 3); }
			//	else if (Is4KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 4); }
			//	else if (Is5KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 5); }
			//	else if (Is6KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 6); }
			//	else if (Is7KeyTrigger() == TRUE) { GameCommuEditCharacter(x, 4, 7); }
			//	else if (CheckHitKey(KEY_INPUT_D) == TRUE) 
			//	{ 
			//		commu_state_edit[edit_line].CharacterIDChange(x, 0);
			//		g_edittype = EDIT_DEFAULT;
			//	}
			//}
			//// �|�[�Y�A�ߑ��A�\��p
			//else
			//{
			//	if (Is0KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 0); }
			//	else if (Is1KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 1); }
			//	else if (Is2KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 2); }
			//	else if (Is3KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 3); }
			//	else if (Is4KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 4); }
			//	else if (Is5KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 5); }
			//	else if (Is6KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 6); }
			//	else if (Is7KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 7); }
			//	else if (Is8KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 8); }
			//	else if (Is9KeyTrigger() == TRUE) { GameCommuEditCharacter(x, g_editcharactertype + 1, 9); }
			//}

			// �폜�p�����G�h�c��������
			if (Is0KeyTrigger() == TRUE)
			{
				commu_state_edit[edit_line].CharacterIDChange(g_edittype - EDIT_CHARACTER_LEFT, -1000);
				g_edittype = EDIT_DEFAULT;
			}
			// �����ꂽ�����L�[�ɉ����ăJ�[�\�����u���ړ�����
			if (Is1KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(1); }
			else if (Is2KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(2); }
			else if (Is3KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(3); }
			else if (Is4KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(4); }
			else if (Is5KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(5); }
			else if (Is6KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(6); }
			else if (Is7KeyTrigger() == TRUE) { GameCommuEditCharacterCursorMove(7); }
		}
		// �w�L�����ύX�^�C�v�x�I�����̏���
		if(edit_row == EDIT_CHARACTER_CHANGE_TYPE)
		{
			#pragma region ver0.007���쎞�R�����g���R�[�h
			//if (CheckHitKey(KEY_INPUT_0) == TRUE)
			//{ 
			//	if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)
			//	{
			//		for (int i = edit_line; i <= COMMU_LINE_MAX; i++) { commu_state_edit[i].CCCHANGE(0); }
			//	}
			//	else { commu_state_edit[edit_line].CCCHANGE(0); }
			//}
			//else if (CheckHitKey(KEY_INPUT_1) == TRUE)
			//{
			//	if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)
			//	{
			//		for(int i = edit_line; i <= COMMU_LINE_MAX; i++){ commu_state_edit[i].CCCHANGE(1); }
			//	}
			//	else{ commu_state_edit[edit_line].CCCHANGE(1); }
			//}
#pragma endregion
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { GameCommuEditCharacterChange(0); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { GameCommuEditCharacterChange(1); }
			else if (CheckHitKey(KEY_INPUT_2) == TRUE) { GameCommuEditCharacterChange(2); }
		}
		// �w����\��x�I�����̏���
		if(edit_row == EDIT_SELECT_FE_LEFT || edit_row == EDIT_SELECT_FE_CENTER || edit_row == EDIT_SELECT_FE_RIGHT)
		{
			int x = 0;
			switch (edit_row)
			{
			case EDIT_SELECT_FE_CENTER:	x = 1;	break;
			case EDIT_SELECT_FE_RIGHT:	x = 2;	break;
			default:							break;
			}
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { commu_state_edit[edit_line].CFECHANGE(x, -1); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { commu_state_edit[edit_line].CFECHANGE(x, 1); }
			else if (CheckHitKey(KEY_INPUT_2) == TRUE) { commu_state_edit[edit_line].CFECHANGE(x, 2); }
			else if (CheckHitKey(KEY_INPUT_D) == TRUE) { commu_state_edit[edit_line].CFECHANGE(x, 0); }
		}
		// �w�L�����ԋ����ψꉻ�x�I�����̏���
		if (edit_row == EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM)
		{
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { commu_state_edit[edit_line].CDUCHANGE(-1); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { commu_state_edit[edit_line].CDUCHANGE(1); }
			else if (CheckHitKey(KEY_INPUT_D) == TRUE) { commu_state_edit[edit_line].CDUCHANGE(0); }
		}
		// �w�i�I�����̏���
		if (g_edittype == EDIT_BACKGROUND)
		{
			int x = (edit_row_background - 1) * 10;
			if (CheckHitKey(KEY_INPUT_D) == TRUE) { GameCommuEditBackground(0); }
			else if (edit_row_background == 0)
			{
				if (Is0KeyTrigger() == TRUE) { GameCommuEditBackground(-1); }
			}
			else if (Is0KeyTrigger() == TRUE) { GameCommuEditBackground(x + 1); }
			else if (Is1KeyTrigger() == TRUE) { GameCommuEditBackground(x + 2); }
			else if (Is2KeyTrigger() == TRUE) { GameCommuEditBackground(x + 3); }
			else if (Is3KeyTrigger() == TRUE) { GameCommuEditBackground(x + 4); }
			else if (Is4KeyTrigger() == TRUE) { GameCommuEditBackground(x + 5); }
			else if (Is5KeyTrigger() == TRUE) { GameCommuEditBackground(x + 6); }
			else if (Is6KeyTrigger() == TRUE) { GameCommuEditBackground(x + 7); }
			else if (Is7KeyTrigger() == TRUE) { GameCommuEditBackground(x + 8); }
			else if (Is8KeyTrigger() == TRUE) { GameCommuEditBackground(x + 9); }
			else if (Is9KeyTrigger() == TRUE) { GameCommuEditBackground(x + 10); }
		}
		// �w�L�����ύX�^�C�v�x�I�����̏���
		if (edit_row == EDIT_SELECT_BACKGROUND_CHANGE_TYPE)
		{
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { commu_state_edit[edit_line].BackgroundChangeTypeChange(BACKGROUND_CHANGE_VISIBILITY); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { commu_state_edit[edit_line].BackgroundChangeTypeChange(BACKGROUND_CHANGE_BLACKOUT); }
			else if (CheckHitKey(KEY_INPUT_2) == TRUE) { commu_state_edit[edit_line].BackgroundChangeTypeChange(BACKGROUND_CHANGE_WHITEOUT); }
		}
		// �a�f�l�I�����̏���
		if (g_edittype == EDIT_BGM)
		{
			if(CheckHitKey(KEY_INPUT_D) == TRUE){ GameCommuEditBGM(0); }
			else if(edit_row_bgm == 0)
			{ 
				if (Is0KeyTrigger() == TRUE) { GameCommuEditBGM(-1); }
			}
			else
			{
				if (Is0KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 1); }
				else if (Is1KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 2); }
				else if (Is2KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 3); }
				else if (Is3KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 4); }
				else if (Is4KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 5); }
				else if (Is5KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 6); }
				else if (Is6KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 7); }
				else if (Is7KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 8); }
				else if (Is8KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 9); }
				else if (Is9KeyTrigger() == TRUE) { GameCommuEditBGM((edit_row_bgm - 1) * 10 + 10); }
			}
		}
		// �w�a�f�l�ύX�^�C�v�x�I�����̏���
		if (edit_row == EDIT_SELECT_BGM_CHANGE_TYPE)
		{
			if (CheckHitKey(KEY_INPUT_0) == TRUE) { commu_state_edit[edit_line].BCTChange(BGM_CHANGE_FO_P); }
			else if (CheckHitKey(KEY_INPUT_1) == TRUE) { commu_state_edit[edit_line].BCTChange(BGM_CHANGE_FO_FI); }
			else if (CheckHitKey(KEY_INPUT_2) == TRUE) { commu_state_edit[edit_line].BCTChange(BGM_CHANGE_S_P); }
			else if (CheckHitKey(KEY_INPUT_3) == TRUE) { commu_state_edit[edit_line].BCTChange(BGM_CHANGE_S_FI); }
		}
		// �r�d�I�����̏���
		if (g_edittype == EDIT_SE)
		{
			if (CheckHitKey(KEY_INPUT_D) == TRUE) { GameCommuEditSE(0); }
			else if (edit_row_se == 0)
			{
				if (Is0KeyTrigger() == TRUE) { GameCommuEditSE(-1); }
			}
			else
			{
				if (Is0KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 1); }
				else if (Is1KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 2); }
				else if (Is2KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 3); }
				else if (Is3KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 4); }
				else if (Is4KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 5); }
				else if (Is5KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 6); }
				else if (Is6KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 7); }
				else if (Is7KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 8); }
				else if (Is8KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 9); }
				else if (Is9KeyTrigger() == TRUE) { GameCommuEditSE((edit_row_se - 1) * 10 + 10); }
			}
		}
	}
}
// �e�L�X�g�E�B���h�E�F�ύX�̍ۂ̋��ʏ���
void GameCommuEditTextWindow(int x)	// �E�B���h�E�̐F
{
	g_edittype = EDIT_DEFAULT;
	commu_state_edit[edit_line].CommandChange((char*)"text_window_color");
	commu_state_edit[edit_line].CommandNumberChange(x);
}
// �I������������͂̍ۂ̋��ʏ���
void GameCommuEditAlternativeInput(CommandInputStringType x)	// ���ɓ��͂���I�����n������
{
	g_commandinputstring = x;
	if (x >= CIS_ALTERNATIVE_JUMP2_1 && x <= CIS_ALTERNATIVE_JUMP3_3) { GameCommuEditInputString(3, TRUE, (char*)""); }
	else { GameCommuEditInputString(33, FALSE, (char*)""); }
	g_edittype = EDIT_COMMAND;
	commu_edit_input_string = TRUE;
}
// �������͏�Ԉڍs�̋��ʏ���
void GameCommuEditInputString(int x, BOOL y, char* c)	// ���͂ł��锼�p���������,���p��������̃t���O,���͊J�n��������
{
	InputHandle = MakeKeyInput(x, TRUE, FALSE, y);		// �L�[���̓n���h�������
	SetKeyInputString(c, InputHandle);					// �L�[���̓n���h���Ɏw��̕�������Z�b�g����
	SetActiveKeyInput(InputHandle);						// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
	commu_edit_input_string = TRUE;						// �������̓��[�h�I��
}
// �s���e�S�폜�̋��ʏ���
void GameCommuEditLineErase(int x)	// �폜�s
{
	char c_null[256] = "";
	commu_state_edit[x].CommandChange(c_null);			// �R�}���h
	commu_state_edit[x].CommandNumberChange(0);			// �e����R�}���h�p���l
	commu_state_edit[x].LineCharacterChange(0, c_null);	// �䎌��
	commu_state_edit[x].LineCharacterChange(1, c_null);	// �䎌��Q
	commu_state_edit[x].LineChange(c_null);				// �䎌
	commu_state_edit[x].LineMouseChange(0);				// �䎌���p�N�^�C�v
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j <= 4; j++) { commu_state_edit[x].CharacterIDChange(i, j, 0); }	// �L�����N�^�[
		commu_state_edit[x].CFECHANGE(i, 0);												// �L�����N�^�[����\��
	}
	commu_state_edit[x].CCCHANGE(0);												// �L�����N�^�[�ύX�^�C�v
	commu_state_edit[x].CDUCHANGE(0);												// �L�����ԋ����ψꉻ
	commu_state_edit[x].BackgroundChange(0);										// �w�i
	commu_state_edit[x].BackgroundChangeTypeChange(BACKGROUND_CHANGE_VISIBILITY);	// �w�i�ύX�^�C�v
	commu_state_edit[x].BGMChange(0);												// �a�f�l
	commu_state_edit[x].BCTChange(BGM_CHANGE_FO_P);									// �a�f�l�ύX�^�C�v
	commu_state_edit[x].SEChange(0);												// �r�d
	for (int i = 0; i < 3; i++)
	{
		commu_state_edit[x].AlternativeChange(i, 0);		// �I����������i��Q�������K���ł͂Ȃ��\��������j
		commu_state_edit[x].AlternativeJumpChange(i, 0);	// �I�����W�����v��s
	}
}
// �s���e�R�s�[�̋��ʏ���
#pragma region ver0.00704���쎞�R�����g���R�[�h
//void GameCommuEditLineCopy(int x, int y)	// �R�s�[��s,�R�s�[���s
#pragma endregion
void GameCommuEditLineCopy(int x, int y, int z)	// �R�s�[��s,�R�s�[���s,����̏������ɉ��Z����鐔�l
{
	commu_state_edit[x].CommandChange(commu_state_edit[y].GetCommand());						// �R�}���h
	// �e����R�}���h�p���l�i�wmove_cell�x���w�肳��Ă���ۂ͓���̐��l�����Z�����j
	commu_state_edit[x].CommandNumberChange(commu_state_edit[y].GetCommandNumber() + (strcmp(commu_state_edit[y].GetCommand(), "move_sell") == 0 ? z : 0));

	commu_state_edit[x].LineCharacterChange(0, commu_state_edit[y].GetLineCharacterName());		// �䎌��
	commu_state_edit[x].LineCharacterChange(1, commu_state_edit[y].GetLineCharacterName2());	// �䎌��Q
	commu_state_edit[x].LineChange(commu_state_edit[y].GetLine());								// �䎌
	commu_state_edit[x].LineMouseChange(commu_state_edit[y].GetLineMouse());					// �䎌���p�N�^�C�v
	for (int i = 0; i < 3; i++)
	{
		commu_state_edit[x].CharacterIDChange(i, commu_state_edit[y].GetCharacter(i));	// �L�����N�^�[
		commu_state_edit[x].CFECHANGE(i, commu_state_edit[y].GetCFE(i));				// �L�����N�^�[����\��
	}
	commu_state_edit[x].CCCHANGE(commu_state_edit[y].GetCC());										// �L�����N�^�[�ύX�^�C�v
	commu_state_edit[x].CDUCHANGE(commu_state_edit[y].GetCDU());									// �L�����ԋ����ψꉻ
	commu_state_edit[x].BackgroundChange(commu_state_edit[y].GetBackground());						// �w�i
	commu_state_edit[x].BackgroundChangeTypeChange(commu_state_edit[y].GetBackgroundChangeType());	// �w�i�ύX�^�C�v
	commu_state_edit[x].BGMChange(commu_state_edit[y].GetBGM());									// �a�f�l
	commu_state_edit[x].BCTChange(commu_state_edit[y].GetBGMCT());									// �a�f�l�ύX�^�C�v
	commu_state_edit[x].SEChange(commu_state_edit[y].GetSE());										// �r�d
	for (int i = 0; i < 3; i++)
	{
		commu_state_edit[x].AlternativeChange(i, commu_state_edit[y].GetAlternativeString(i));		// �I����������i��Q�������K���ł͂Ȃ��\��������j
		// �I�����W�����v��s�i�R�}���h�Ŏ��ۂɑI�������g����ꍇ�A����̐��l�����Z�����j
		int a = 0;
		if (strcmp(commu_state_edit[y].GetCommand(), "altenative_2") || (strcmp(commu_state_edit[y].GetCommand(), "altenative_3") && i == 2)) { a = z; }
		{commu_state_edit[x].AlternativeJumpChange(i, commu_state_edit[y].GetAlternativeJump(i) + a);}
	}
}
// ���p�N�^�C�v�ϐ�����̋��ʏ���
void GameCommuEditLinesMouse(int x)	// ���p�N�^�C�v�p�ϐ�
{
	commu_state_edit[edit_line].LineMouseChange(x);
	g_edittype = EDIT_DEFAULT;
}
// �䎌��ϐ���������̍ۂ̋��ʏ���
void GameCommuEditLinesCharacter(char* c)	// ������
{
	commu_state_edit[edit_line].LineCharacterChange(g_edittype - EDIT_SELECT_LINES_CHARACTER, c);
	g_edittype = EDIT_DEFAULT;
}
// �L�����N�^�[�p�ϐ���������̍ۂ̋��ʏ���
void GameCommuEditCharacter(int x, int y, int z) // �ύX����L�����N�^�[,�ύX����ID���l�̌��̈�,�ύX��̐���
{
	commu_state_edit[edit_line].CharacterIDChange(x, y, z);
	switch (g_editcharactertype)
	{
	case EDIT_CHARACTER_EXPRESSION:	
		g_edittype = EDIT_DEFAULT;
		g_editcharactertype = EDIT_CHARACTER_BODY;
		break;
	case EDIT_CHARACTER_COSTUME:	g_editcharactertype = EDIT_CHARACTER_EXPRESSION;	break;
	case EDIT_CHARACTER_PAUSE:		g_editcharactertype = EDIT_CHARACTER_COSTUME;		break;
	case EDIT_CHARACTER_BODY:		g_editcharactertype = EDIT_CHARACTER_PAUSE;			break;
	default:																			break;
	}
}
// �L���������G�I�����u���ړ�����L�������������ړ�����ۂ̋��ʏ���
void GameCommuEditCharacterCursorMove(int x)	// ��������L�����̐�̈�
{
	// ��������
	for (int i = 0; i < edit_character_alternative_line_limit; i++)
	{
		for (int j = 0; j < EDIT_CHARACTER_ALTERNATIVE_X_LIMIT; j++)
		{
			// ��̈ʂ���v���Ă�����J�[�\�����ړ������֐��𔲂��o��
			if (edit_character_id[i][j] / 1000 == x)
			{
				edit_character_alternative_row = j;
				edit_character_alternative_line = i;
				return;
			}
		}
	}
}
// �L�����ύX�^�C�v��ύX����ۂ̋��ʏ���
void GameCommuEditCharacterChange(int x)	// �L�����ύX�^�C�v�h�c
{
	if (CheckHitKey(KEY_INPUT_LSHIFT) == TRUE || CheckHitKey(KEY_INPUT_RSHIFT) == TRUE)
	{
		for (int i = edit_line; i <= COMMU_LINE_MAX; i++) { commu_state_edit[i].CCCHANGE(x); }
	}
	else { commu_state_edit[edit_line].CCCHANGE(x); }
}
// �w�i�ϐ�����̋��ʏ���
void GameCommuEditBackground(int x)	// �w�i
{
	#pragma region ver0.00704���쎞�R�����g���R�[�h
	//if (x <= BACKGROUND_NUMBER)
#pragma endregion
	if (x <= bgimage[0].GetNumber())
	{
		commu_state_edit[edit_line].BackgroundChange(x);
		g_edittype = EDIT_DEFAULT;
	}
}
// �a�f�l�ϐ�����̋��ʏ���
void GameCommuEditBGM(int x)	// �a�f�l
{
	commu_state_edit[edit_line].BGMChange(x);
	g_edittype = EDIT_DEFAULT;
}
// �r�d�ϐ�����̋��ʏ���
void GameCommuEditSE(int x)	// �r�d
{
	// ���݂���r�d�̂h�c�Ȃ�r�d��ҏW����EDIT_DEFAULT��Ԃɂ���
	#pragma region ver0.00707���쎞�R�����g���R�[�h
	//if (x <= SE_NUMBER)
#pragma endregion
	if (x <= SEData::GetNumber())
	{
		commu_state_edit[edit_line].SEChange(x);
		g_edittype = EDIT_DEFAULT;
		//if(x > 0){ PlaySoundMem(g_sndhandles.SE[x - 1], DX_PLAYTYPE_BACK); }	// �ҏW�����r�d��炷
		if (x > 0) { se[x - 1].PlayBack(); }	// �ҏW�����r�d��炷
	}
}
// �R�~���G�f�B�b�g��ʂ̕`�揈���i�v���C���[�����ɃA�b�v���[�h����ۂ͂����̓��e���ꎞ�������ăr���h����j
void DrawGameCommuEdit()
{
	// �L���������G�I�����p�`��
	if(g_edittype >= EDIT_CHARACTER_LEFT && g_edittype <= EDIT_CHARACTER_RIGHT)
	{
		float b_x = screen_size_x * edit_character_alternative_row / 7.0f - screen_size_x / 10;
		float b_y = screen_size_y / 3.0f;
		// 16�F�X�T�C�Y�̃L���������G�Ɠ����T�C�Y���Ɨ��ׂɂԂ���̂ŉ������������Ă���
		DrawBoxAA(b_x + screen_size_x * 0.25f, b_y, b_x + (WINDOW_SIZE_X * bairitu) / 3 - screen_size_x * 0.25f, b_y + screen_size_y / 3, GetColor(100, 150, 255), TRUE);

		for (int i = -1; i < 2; i++)
		{
			for(int j = 0; j < EDIT_CHARACTER_ALTERNATIVE_X_LIMIT; j++)
			{
				if (edit_character_id[edit_character_alternative_line + i][j] >= 1000)
				{
					float x = screen_size_x * j / 7.0f - screen_size_x / 10;	// �L�����̔z�u�ꏊ�ɂ���ĕς��x���W
					float cy = screen_size_y / 3.0f + i * screen_size_y / 2.5f;	// �L�����̔z�u�ꏊ�ɂ���ĕς��y���W
					DrawExtendGraphF(x, cy, x + (WINDOW_SIZE_X * bairitu) / 3, cy + screen_size_y / 3, g_imghandles.character_body[edit_character_id[edit_character_alternative_line + i][j] / 1000 - 1][edit_character_id[edit_character_alternative_line + i][j] / 100 % 10][edit_character_id[edit_character_alternative_line + i][j] / 10 % 10], TRUE);
					int y = 2;	// �ڃp�[�c�Ɏg���ϐ��i�܂΂��������I����܂ł̃t���[������1�ȏ㊎�A18�i6�~3�j�ȉ��Ȃ�A�c��t���[������5�𑫂������l��6�Ŋ�������A2�Ŋ������ۂ̗]���Ԃ��A����Ă����2��Ԃ��i�t���[����19�ȏ�Ȃ�J�����ςȂ��j�j
					//if (g_commu_character_face[i] == CCF_CLOSE_EYE_SMILE && y == 0) { y = 3; }																																					// ����\��w�Ί���ځx�Ȃ�ʏ�̕��ڂ̎��ɍ����ւ���
					DrawExtendGraphF(x, cy, x + (WINDOW_SIZE_X * bairitu) / 3, cy + screen_size_y / 3, g_imghandles.character_face[edit_character_id[edit_character_alternative_line + i][j] / 1000 - 1][edit_character_id[edit_character_alternative_line + i][j] / 100 % 10][edit_character_id[edit_character_alternative_line + i][j] / 10 % 10][edit_character_id[edit_character_alternative_line + i][j] % 10][y], TRUE);
					DrawExtendGraphF(x, cy, x + (WINDOW_SIZE_X * bairitu) / 3, cy + screen_size_y / 3, g_imghandles.character_eyebrow[edit_character_id[edit_character_alternative_line + i][j] / 1000 - 1][edit_character_id[edit_character_alternative_line + i][j] / 100 % 10][edit_character_id[edit_character_alternative_line + i][j] / 10 % 10][edit_character_id[edit_character_alternative_line + i][j] % 10][2], TRUE);	// ����
					DrawExtendGraphF(x, cy, x + (WINDOW_SIZE_X * bairitu) / 3, cy + screen_size_y / 3, g_imghandles.character_face[edit_character_id[edit_character_alternative_line + i][j] / 1000 - 1][edit_character_id[edit_character_alternative_line + i][j] / 100 % 10][edit_character_id[edit_character_alternative_line + i][j] / 10 % 10][edit_character_id[edit_character_alternative_line + i][j] % 10][8], TRUE);
					DrawFormatStringFToHandle(x + (WINDOW_SIZE_X * bairitu) / 6.1f - bairitu * 30, cy + screen_size_y / 3, GetColor(255, 255, 255), g_font3, "%d", edit_character_id[edit_character_alternative_line + i][j]);
				}
			}
		}
		// �w���v���b�Z�[�W
		char h_c[256] = "";
		sprintf_s(h_c, 256, "�\���L�[�F�ړ�\nEnter�F����\n0�F�폜�i-1000�j\n���u���ړ�\n��1�F�߂���\n��2�F����\n��3�F����\n��4�F�z��\n��5�F���\n��6�F�͂Â�\n��7�F�Z��\n\nB�F�L�����Z��");
		DrawFormatStringFToHandle(bairitu * 1662, screen_size_y / 4.0f - bairitu * 198, GetColor(255, 255, 255), g_font3, h_c);
	}
	// �w�i�I�����p�`��i���݂��Ȃ��w�i��`�悳���Ȃ��j
	else if (g_edittype == EDIT_BACKGROUND)
	{
		const float CURSOR_X = GlobalStaticEdit::GetBackgroundAlternativeRow() * static_cast<float>(screen_size_x) / GlobalStaticEdit::GetBackgroundAlternativeLineNumber();
		//const float CURSOR_Y = GlobalStaticEdit::GetBackgroundAlternativeRow() * screen_size_x / GlobalStaticEdit::GetBackgroundAlternativeLineNumber();
		DrawBoxAA(CURSOR_X, 0, CURSOR_X + screen_size_x / GlobalStaticEdit::GetBackgroundAlternativeLineNumber(), static_cast<float>(screen_size_y) / GlobalStaticEdit::GetBackgroundAlternativeLineNumber(), GetColor(100, 150, 255), TRUE);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				const int B = (i + GlobalStaticEdit::GetBackgroundAlternativeLine()) * 2 + j;
				if (B < bgimage[0].GetNumber())
				{
					const float X = j * screen_size_x / 2.0f;
					const float Y = i * screen_size_y / 2.0f;
					const float Z = bairitu * 30;	// �k���s�N�Z������
					const float A = Z * 2 * 9 / 16;	// �k���s�N�Z�����c�i�������̂݁j
					DrawExtendGraphF(X + Z, Y, X + screen_size_x / 2 - Z, Y + screen_size_y / 2 - A, bgimage[B].GetHandle(), TRUE);
					DrawFormatStringFToHandle(X + Z, Y + screen_size_y / 2 - A, GetColor(255, 255, 255), g_font3, "%d�F%s", B + 1, bgimage[B].GetName());
				}
			}
		}
	}

	else
	{
		char c[512];	// ������
		// �I��ҏW���e�̕�������`������
		char e_string[256];
		switch (edit_row)
		{
		case EDIT_SELECT_COMMAND:
			sprintf_s(e_string, 256, "�R�}���h");
			// �I�����Q���I�΂�Ă�Ȃ�I�����Q�̓��e��
			if (strcmp(commu_state_edit[edit_line].command, "altenative_2") == 0 || strcmp(commu_state_edit[edit_line].command, "altenative_3") == 0) { sprintf_s(e_string, 256, "%s\n�I�����P�F\n%s\n�ړ���̍s�F%d\n�I�����Q�F\n%s\n�ړ���̍s�F%d\n", e_string, commu_state_edit[edit_line].altenative_message[0], commu_state_edit[edit_line].altenative_jump[0], commu_state_edit[edit_line].altenative_message[1], commu_state_edit[edit_line].altenative_jump[1]); }
			if (strcmp(commu_state_edit[edit_line].command, "altenative_3") == 0) { sprintf_s(e_string, 256, "%s�I�����R�F\n%s\n�ړ���̍s�F%d\n", e_string, commu_state_edit[edit_line].altenative_message[2], commu_state_edit[edit_line].altenative_jump[2]); }
			break;
		case EDIT_SELECT_LINES_CHARACTER:				sprintf_s(e_string, 256, "�䎌��");						break;
		case EDIT_SELECT_LINES_CHARACTER2:				sprintf_s(e_string, 256, "�䎌��E�Q");					break;
		case EDIT_SELECT_LINES:							sprintf_s(e_string, 256, "�䎌");						break;
		case EDIT_SELECT_LINES_MOUSE:					sprintf_s(e_string, 256, "�䎌���p�N�^�C�v");			break;
		case EDIT_SELECT_CHARACTER_LEFT:				sprintf_s(e_string, 256, "���L�����N�^�[");				break;
		case EDIT_SELECT_FE_LEFT:						sprintf_s(e_string, 256, "���L�����N�^�[����\��");		break;
		case EDIT_SELECT_CHARACTER_CENTER:				sprintf_s(e_string, 256, "�����L�����N�^�[");			break;
		case EDIT_SELECT_FE_CENTER:						sprintf_s(e_string, 256, "�����L�����N�^�[����\��");	break;
		case EDIT_SELECT_CHARACTER_RIGHT:				sprintf_s(e_string, 256, "�E�L�����N�^�[");				break;
		case EDIT_SELECT_FE_RIGHT:						sprintf_s(e_string, 256, "�E�L�����N�^�[����\��");		break;
		case EDIT_CHARACTER_CHANGE_TYPE:				sprintf_s(e_string, 256, "�L�����N�^�[�ύX�^�C�v");		break;
		case EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM:	sprintf_s(e_string, 256, "�L�����ԋ����ψꉻ");			break;
		case EDIT_SELECT_BACKGROUND:					sprintf_s(e_string, 256, "�w�i");						break;
		case EDIT_SELECT_BACKGROUND_CHANGE_TYPE:		sprintf_s(e_string, 256, "�w�i�ύX�^�C�v");				break;
		case EDIT_SELECT_BGM:							sprintf_s(e_string, 256, "�a�f�l");						break;
		case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(e_string, 256, "�a�f�l�ύX�^�C�v");			break;
		case EDIT_SELECT_SE:							sprintf_s(e_string, 256, "�r�d");						break;
		default:										sprintf_s(e_string, 256, "�i���ݒ�̍��ځj");			break;
		}
		// ��Ԃɉ����Đ�������ύX����
		char c_x[10][256] = { "", "", "" , "" , "" , "" , "" , "" , "" , "" };	// �G���[���N�������Ȃ̂ŏ����l���
		switch (g_edittype)
		{
		case EDIT_DEFAULT:
			char c_line_control[256];
			sprintf_s(c_line_control, 256, "B�F�^�C�g���֖߂�\nI�F�󔒍s�}��\nC+E or Ctrl+E�F�ҏW�s�R�s�[�}��\nD+L or Ctrl+L�F�s�폜");
			// �ҏW�s�ړ��ɂ��Ă̐�����
			char c_line_move[256];
			sprintf_s(c_line_move, 256, "�ҏW�s�F%d\nCtrl�{���E�L�[�F���E�[�ֈړ�\n\n(�����L�[�F�ړ�\nShift�L�[�����Ȃ���F�ړ���100�{�Actrl�L�[�����Ȃ���F�ړ���10�{)", edit_line);

			switch (edit_row)
			{
			case EDIT_SELECT_LINES:							sprintf_s(c, 512, "�ҏW���e���i�����L�[�j�F%s\n%s\nD�F�䎌���폜\nEnter�F�䎌��ҏW\n%s", e_string, c_line_move, c_line_control);									break;
			case EDIT_SELECT_CHARACTER_LEFT:
			case EDIT_SELECT_CHARACTER_CENTER:
			case EDIT_SELECT_CHARACTER_RIGHT:
				sprintf_s(c, 512, "�ҏW���e���i�����L�[�j�F%s\n%s\nEnter�F�����G�ҏW\nD�F�폜\n%s", e_string, c_line_move, c_line_control);
				break;
			case EDIT_SELECT_FE_LEFT:
			case EDIT_SELECT_FE_CENTER:
			case EDIT_SELECT_FE_RIGHT:
				sprintf_s(c, 512, "�ҏW���e���i�����L�[�j�F%s\n%s\nD�F�폜\n0�F�ʏ�ɖ߂�\n1�F����\n2�F�Ί����\n%s", e_string, c_line_move, c_line_control);
				break;
			case EDIT_CHARACTER_CHANGE_TYPE:				sprintf_s(c, 512, "�ҏW���e���i�����L�[�j�F%s\n%s\n\nShift�������Ȃ���F���̍s����ŏI�s�܂�\n0�F�폜\n1�F�u���\���E����ւ�\n2�F�����x��������ւ�\n\n%s", e_string, c_line_move, c_line_control);								break;
			case EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM:	sprintf_s(c, 512, "�ҏW���e���i�����L�[�j�F%s\n%s\nD�F�폜\n0�F�I�t\n1�F�I��\n%s", e_string, c_line_move, c_line_control);									break;
			case EDIT_SELECT_BACKGROUND_CHANGE_TYPE:		sprintf_s(c, 512, "�ҏW���e���i�����L�[�j�F%s\n%s\n0�F�s�����x����ւ�\n1�F�u���b�N�A�E�g\n2�F�z���C�g�A�E�g\n%s", e_string, c_line_move, c_line_control);	break;
				//case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(c, 256, "�ҏW���e���i�����L�[�j�F%s\n�ҏW�s�i�����L�[�j�F%d\n0�F�e�n���o\n1�F�e�n���e�h\n2�F�r���o\n3�F�r���e�h\n��\n�e�n�ifade out�j�F60�t���[�������ĉ��ʂ��������Ȃ��~���܂�\n�r�istop�j�F10�t���[�������ĉ��ʂ��������Ȃ��~���܂�\n���o(play)�F���Đ����܂�\n�e�h(fade in)�F�Đ����A240�t���[�������Đݒ艹�ʂɂȂ�܂�\n\nB�F�^�C�g���֖߂�", e_string, edit_line);	break;
			case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(c, 512, "�ҏW���e���i�����L�[�j�F%s\n%s\n0�F�e�n���o\n1�F�e�n���e�h\n2�F�r���o\n3�F�r���e�h\n%s", e_string, c_line_move, c_line_control);			break;
			default:										sprintf_s(c, 512, "�ҏW���e���i�����L�[�j�F%s\n%s\nEnter�F�w��R�}���h��ҏW\n%s", e_string, c_line_move, c_line_control);									break;
			}
			break;
		case EDIT_COMMAND:
			switch (g_commandinputstring)
			{
			case CIS_NULL:
				sprintf_s(c, 256, "1�F�r�d�I���Ŏ��s����\n2�F�w��t���[�����㎟�s����\n3�F�Q��I����\n4�F�R��I����\n5�F�w��s�փW�����v\n6�F�R�~���I��\n7�F�w��h�c�R�~���ֈړ�\n8�F�e�L�X�g�E�B���h�E�F�ύX\nB�F�L�����Z��\nD�F�폜");
				break;
			case CIS_FRAME_AUTO:
			case CIS_MOVE_SELL:
			case CIS_MOVE_COMMU:
				sprintf_s(c, 256, "���l�����\nEsc�F�L�����Z��\nEnter�F����");
				break;
			case CIS_ALTERNATIVE2_1:
			case CIS_ALTERNATIVE3_1:
				sprintf_s(c, 256, "�I�����P�����\nEsc�F�L�����Z��\nEnter�F����");
				break;
			case CIS_ALTERNATIVE2_2:
			case CIS_ALTERNATIVE3_2:
				sprintf_s(c, 256, "�I�����Q�����\nEsc�F�L�����Z��\nEnter�F����");
				break;
			case CIS_ALTERNATIVE3_3:
				sprintf_s(c, 256, "�I�����R�����\nEsc�F�L�����Z��\nEnter�F����");
				break;
			case CIS_ALTERNATIVE_JUMP2_1:
			case CIS_ALTERNATIVE_JUMP3_1:
				sprintf_s(c, 256, "�I�����P���莞�W�����v��s�����\nEsc�F�L�����Z��\nEnter�F����");
				break;
			case CIS_ALTERNATIVE_JUMP2_2:
			case CIS_ALTERNATIVE_JUMP3_2:
				sprintf_s(c, 256, "�I�����Q���莞�W�����v��s�����\nEsc�F�L�����Z��\nEnter�F����");
				break;
			case CIS_ALTERNATIVE_JUMP3_3:
				sprintf_s(c, 256, "�I�����R���莞�W�����v��s�����\nEsc�F�L�����Z��\nEnter�F����");
				break;
			default:
				sprintf_s(c, 256, "1�F�r�d�I���Ŏ��s����\n2�F�w��t���[�����㎟�s����\n3�F�Q��I����\n4�F�R��I����\n5�F�w��s�փW�����v\n6�F�R�~���I��\n7�F�w��h�c�R�~���ֈړ�\n8�F�e�L�X�g�E�B���h�E�F�ύX\nB�F�L�����Z��\nD�F�폜");
				break;
			}
			break;
		case EDIT_TEXT_WINDOW:		sprintf_s(c, 256, "1�F�D\n2�F��\n3�F��\n4�F��\nB�F�L�����Z��");																														break;
		case EDIT_LINES_CHARACTER:
		case EDIT_LINES_CHARACTER2:
			if (commu_edit_input_string == FALSE) { sprintf_s(c, 256, "1�F��l��\n2�F�߂���\n3�F����\n4�F����\n5�F�z��\n6�F���\n7�F�͂Â�\n8�F�Z��\n9�F�ꓯ\n0�F���R����\nB�F�L�����Z��\nD�F�폜"); }
			else { sprintf_s(c, 256, "Enter�F���͖�������\nEsc�F�L�����Z���F"); }
			break;
		case EDIT_LINES:		sprintf_s(c, 256, "Enter�F���͑䎌������\nEsc�F�L�����Z���F");												break;
		case EDIT_LINES_MOUSE:	sprintf_s(c, 256, "1�F�J���Ȃ�\n2�F�䎌���I���܂ŊJ��\n3�F�J�����ςȂ�\n4�F�S�����点��\nB�F�L�����Z��\nD�F�ʏ�ɖ߂�");	break;
		case EDIT_CHARACTER_LEFT:
		case EDIT_CHARACTER_CENTER:
		case EDIT_CHARACTER_RIGHT:
			char c_character[256];	// �L�����h�c�I�����̋��ʃ��b�Z�[�W
			sprintf_s(c_character, 256, "B�F�L�����Z��\nD�F�폜");
			switch (g_editcharactertype)
			{
			case EDIT_CHARACTER_EXPRESSION:	sprintf_s(c, 256, "0�`9�F�w��\�������\n%s", c_character);													break;
			case EDIT_CHARACTER_COSTUME:	sprintf_s(c, 256, "0�`9�F�w��ߑ�������\n%s", c_character);													break;
			case EDIT_CHARACTER_PAUSE:		sprintf_s(c, 256, "0�`9�F�w��|�[�Y������\n%s", c_character);												break;
			case EDIT_CHARACTER_BODY:		sprintf_s(c, 256, "0�F�o���L����������\n1�F�߂���\n2�F����\n3�F����\n4�F�z��\n5�F���\n6�F�͂Â�\n7�F�Z��\n%s", c_character);	break;
			default:																																	break;
			}
			break;
		case EDIT_BACKGROUND:
			#pragma region ver0.00704���쎞�R�����g���R�[�h
			//if (edit_row_background == 0) { sprintf_s(c, 256, "�y�[�W1/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�F�w�i���폜\nB�F�L�����Z��\nD�F�폜", (BACKGROUND_NUMBER - 1) / 10 + 2); }
#pragma endregion
			if (edit_row_background == 0) { sprintf_s(c, 256, "�y�[�W1/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�F�w�i���폜\nB�F�L�����Z��\nD�F�폜", (bgimage[0].GetNumber() - 1) / 10 + 2); }
			else
			{
				int x = (edit_row_background - 1) * 10;
				// 40�Ԗڂ̔w�i���͑��݂��Ȃ����A�s����m�F�ł����A�v���C���[���g�����[�h�ł��Ȃ��̂ŕ��u��
				#pragma region ver0.00704���쎞�R�����g���R�[�h
				//sprintf_s(c, 256, "�y�[�W%d/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�F%s\n1�F%s\n2�F%s\n3�F%s\n4�F%s\n5�F%s\n6�F%s\n7�F%s\n8�F%s\n9�F%s\nB�F�L�����Z��\nD�F�폜", edit_row_background + 1, (BACKGROUND_NUMBER - 1) / 10 + 2, bgimage[x + 0].GetName(), bgimage[x + 1].GetName(), bgimage[x + 2].GetName(), bgimage[x + 3].GetName(), bgimage[x + 4].GetName(), bgimage[x + 5].GetName(), bgimage[x + 6].GetName(), bgimage[x + 7].GetName(), bgimage[x + 8].GetName(), bgimage[x + 9].GetName());
#pragma endregion
				//sprintf_s(c, 256, "�y�[�W%d/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�F%s\n1�F%s\n2�F%s\n3�F%s\n4�F%s\n5�F%s\n6�F%s\n7�F%s\n8�F%s\n9�F%s\nB�F�L�����Z��\nD�F�폜", edit_row_background + 1, (bgimage[0].GetNumber() - 1) / 10 + 2, bgimage[x + 0].GetName(), bgimage[x + 1].GetName(), bgimage[x + 2].GetName(), bgimage[x + 3].GetName(), bgimage[x + 4].GetName(), bgimage[x + 5].GetName(), bgimage[x + 6].GetName(), bgimage[x + 7].GetName(), bgimage[x + 8].GetName(), bgimage[x + 9].GetName());
				sprintf_s(c, 512, "�y�[�W%d/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�F%s\n1�F%s\n2�F%s\n3�F%s\n4�F%s\n5�F%s\n6�F%s\n7�F%s\n8�F%s\n9�F%s\nB�F�L�����Z��\nD�F�폜", edit_row_background + 1, (bgimage[0].GetNumber() - 1) / 10 + 2, bgimage[x + 0].GetName(), bgimage[x + 1].GetName(), bgimage[x + 2].GetName(), bgimage[x + 3].GetName(), bgimage[x + 4].GetName(), bgimage[x + 5].GetName(), bgimage[x + 6].GetName(), bgimage[x + 7].GetName(), bgimage[x + 8].GetName(), bgimage[x + 9].GetName());
			}
			break;
		case EDIT_BGM:
			// 10�̕ϐ�����
			for (int i = 0; i < 10; i++)
			{
				int x = (edit_row_bgm - 1) * 10 + i;	// ��r�p
				if (x >= 0 && x < BGM_NUMBER) { sprintf_s(c_x[i], 256, "%s", music_string[(edit_row_bgm - 1) * 10 + i].name); }
			}
			if (edit_row_bgm == 0) { sprintf_s(c, 256, "�y�[�W1/4\n�����L�[�F�y�[�W�؂�ւ�\n0�F�a�f�l��~"); }
			else { sprintf_s(c, 256, "�y�[�W%d/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�F%s\n1�F%s\n2�F%s\n3�F%s\n4�F%s\n5�F%s\n6�F%s\n7�F%s\n8�F%s\n9�F%s\nB�F�L�����Z��\nD�F�폜\n", edit_row_bgm + 1, (BGMData::GetNumber() - 1) / 10 + 2, c_x[0], c_x[1], c_x[2], c_x[3], c_x[4], c_x[5], c_x[6], c_x[7], c_x[8], c_x[9]); }
			break;
		case EDIT_SE:
			// 10�̕ϐ�����
			for (int i = 0; i < 10; i++)
			{
				int x = (edit_row_se - 1) * 10 + i;	// ��r�p
				#pragma region ver0.00707���쎞�R�����g���R�[�h
				//if (x >= 0 && x < SE_NUMBER) { sprintf_s(c_x[i], 256, se[(edit_row_se - 1) * 10 + i].GetName()); }
#pragma endregion
				if (x >= 0 && x < SEData::GetNumber()) { sprintf_s(c_x[i], 256, se[(edit_row_se - 1) * 10 + i].GetName()); }
			}
			// ������ƕ��������������
			#pragma region ver0.00707���쎞�R�����g���R�[�h
			//if (edit_row_se == 0) { sprintf_s(c, 256, "�y�[�W1/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�FSE��~", SE_NUMBER / 10 + 2); }
			//else { sprintf_s(c, 256, "�y�[�W%d/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�F%s\n1�F%s\n2�F%s\n3�F%s\n4�F%s\n5�F%s\n6�F%s\n7�F%s\n8�F%s\n9�F%s\nB�F�L�����Z��\nD�F�폜\n", edit_row_se + 1, SE_NUMBER / 10 + 2, c_x[0], c_x[1], c_x[2], c_x[3], c_x[4], c_x[5], c_x[6], c_x[7], c_x[8], c_x[9]); }
#pragma endregion
			if (edit_row_se == 0) { sprintf_s(c, 256, "�y�[�W1/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�FSE��~", SEData::GetNumber() / 10 + 2); }
			else { sprintf_s(c, 256, "�y�[�W%d/%d\n�����L�[�F�y�[�W�؂�ւ�\n0�F%s\n1�F%s\n2�F%s\n3�F%s\n4�F%s\n5�F%s\n6�F%s\n7�F%s\n8�F%s\n9�F%s\nB�F�L�����Z��\nD�F�폜\n", edit_row_se + 1, SEData::GetNumber() / 10 + 2, c_x[0], c_x[1], c_x[2], c_x[3], c_x[4], c_x[5], c_x[6], c_x[7], c_x[8], c_x[9]); }
			break;
		default:	sprintf_s(c, 256, "�i���ݒ�̍��ځj\n%s", c_character);																				break;
		}
		DrawFormatStringFToHandle(screen_size_x / 2.0f, screen_size_y / 4.0f - bairitu * 198, GetColor(255, 255, 255), g_font3, c);
		// �T���l����̕�---------
		int samune_character[] = { GetEditSamuneNumber(ESS_CHARACTER_LEFT), GetEditSamuneNumber(ESS_CHARACTER_CENTER), GetEditSamuneNumber(ESS_CHARACTER_RIGHT) };
		int samune_distance = GetEditSamuneNumber(ESS_CHARACTER_DISTANCE);
		int samune_background = GetEditSamuneNumber(ESS_BACKGROUND);
		int samune_bgm = GetEditSamuneNumber(ESS_BGM);
		DrawFormatStringFToHandle(0.0f, screen_size_y / 2.0f, GetColor(255, 255, 255), g_font3,
			//"�ҏW�s�F%d\n�䎌�\�\%s�F%s\n/*�L�����N�^�[���F%s\n�L�����N�^�[���F%s\n�L�����N�^�[�E�F%s\n*/�w�i�F%s\n�a�f�l�F%s\n�r�d�F%s",
			"�ҏW�s�F%d\n�䎌�\�\%s%s%s\n�L�����ψ�F%s\n�a�f�l�F%s\n�r�d�F%s",
			edit_line,
			commu_state_edit[edit_line].GetLineCharacterName(),
			commu_state_edit[edit_line].GetLineCharacterName() != "" ? "" : "�F",
			commu_state_edit[edit_line].GetLine(),
			samune_distance == 0 ? "�I�t" : (commu_state_edit[samune_distance].GetCDU() < 1 ? "�I�t" : "�I��"),
			samune_bgm == 0 ? "" : music_string[commu_state_edit[samune_bgm].GetBGM() - 1].GetName(),
			GetSEString(commu_state_edit[edit_line].GetSE())
		);
		// -------------------------
		// �T���l�摜
		//if(commu_state_edit[samune_background].GetBackground() - 1 >= 0)DrawExtendGraphF(0, 0, WINDOW_SIZE_X * bairitu / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.background[commu_state_edit[samune_background].GetBackground() - 1], TRUE);	// �w�i
		if (commu_state_edit[samune_background].GetBackground() - 1 >= 0) { bgimage[commu_state_edit[samune_background].GetBackground() - 1].DrawImageSamune(); }	// �w�i

		// �L�����N�^�[
		for (int i = 0; i < COMMU_CHARACTER_MAX; i++)
		{
			if (samune_character[i] > 0)
			{
				float x = (i * COMMU_CHARACTER_SPACE - COMMU_CHARACTER_SPACE) * bairitu;	// �L�����̔z�u�ꏊ�ɂ���ĕς��x���W
				DrawExtendGraphF(x / 2, 0, (x + WINDOW_SIZE_X * bairitu) / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.character_body[commu_state_edit[samune_character[i]].GetCharacter(i) / 1000 - 1][commu_state_edit[samune_character[i]].GetCharacter(i) / 100 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) / 10 % 10], TRUE);
				int y = 2;	// �ڃp�[�c�Ɏg���ϐ��i�܂΂��������I����܂ł̃t���[������1�ȏ㊎�A18�i6�~3�j�ȉ��Ȃ�A�c��t���[������5�𑫂������l��6�Ŋ�������A2�Ŋ������ۂ̗]���Ԃ��A����Ă����2��Ԃ��i�t���[����19�ȏ�Ȃ�J�����ςȂ��j�j
				//if (g_commu_character_face[i] == CCF_CLOSE_EYE_SMILE && y == 0) { y = 3; }																																					// ����\��w�Ί���ځx�Ȃ�ʏ�̕��ڂ̎��ɍ����ւ���
				DrawExtendGraphF(x / 2, 0, (x + WINDOW_SIZE_X * bairitu) / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.character_face[commu_state_edit[samune_character[i]].GetCharacter(i) / 1000 - 1][commu_state_edit[samune_character[i]].GetCharacter(i) / 100 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) / 10 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) % 10][y], TRUE);
				DrawExtendGraphF(x / 2, 0, (x + WINDOW_SIZE_X * bairitu) / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.character_eyebrow[commu_state_edit[samune_character[i]].GetCharacter(i) / 1000 - 1][commu_state_edit[samune_character[i]].GetCharacter(i) / 100 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) / 10 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) % 10][2], TRUE);	// ����
				DrawExtendGraphF(x / 2, 0, (x + WINDOW_SIZE_X * bairitu) / 2, WINDOW_SIZE_Y * bairitu / 2, g_imghandles.character_face[commu_state_edit[samune_character[i]].GetCharacter(i) / 1000 - 1][commu_state_edit[samune_character[i]].GetCharacter(i) / 100 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) / 10 % 10][commu_state_edit[samune_character[i]].GetCharacter(i) % 10][8], TRUE);
			}
		}

		// �^�񒆂̍s���l�p�ň͂�
		DrawBoxAA(0, bairitu * 855, screen_size_x * 1.0f, bairitu * 930, GetColor(100, 150, 255), TRUE);
		// �ҏW�s�Ƃ��́}�P�s�̓��e
		for (int i = -1; i < 2; i++)
		{
			char c_mouse[256];	// ���p�N�^�C�v�p�ϐ�
			switch (commu_state_edit[edit_line + i].line_mouse)
			{
			case -1:	sprintf_s(c_mouse, 256, "�J���Ȃ�");				break;
			case 0:		sprintf_s(c_mouse, 256, "�ʏ�");					break;
			case 1:		sprintf_s(c_mouse, 256, "�䎌���I���܂ŊJ��");	break;
			case 2:		sprintf_s(c_mouse, 256, "�J�����ςȂ�");			break;
			case 3:		sprintf_s(c_mouse, 256, "�S�����点��");			break;
			default:														break;
			}
			char c_face_etc[3][256];	// ����\�����p�ϐ�
			for (int j = 0; j < 3; j++)
			{
				switch (commu_state_edit[edit_line + i].GetCFE(j))
				{
				case -1:	sprintf_s(c_face_etc[j], 256, "�ʏ�ɖ߂�");	break;
				case 0:		sprintf_s(c_face_etc[j], 256, "");				break;
				case 1:		sprintf_s(c_face_etc[j], 256, "����");		break;
				case 2:		sprintf_s(c_face_etc[j], 256, "�Ί����");	break;
				default:	sprintf_s(c_face_etc[j], 256, "");				break;
				}
			}
			char c_cdu[256];	// �L�����N�^�[�����ψꉻ�p�ϐ�
			switch (commu_state_edit[edit_line + i].GetCDU())
			{
			case -1:	sprintf_s(c_cdu, 256, "�I�t");	break;
			case 1:		sprintf_s(c_cdu, 256, "�I��");	break;
			default:	sprintf_s(c_cdu, 256, "");		break;
			}
			char c_bct[256];	// �w�i�ύX�^�C�v�p�ϐ�
			switch (commu_state_edit[edit_line + i].GetBackgroundChangeType())
			{
			case BACKGROUND_CHANGE_BLACKOUT:	sprintf_s(c_bct, 256, "�u���b�N�A�E�g");	break;
			case BACKGROUND_CHANGE_WHITEOUT:	sprintf_s(c_bct, 256, "�z���C�g�A�E�g");	break;
			default:							sprintf_s(c_bct, 256, "�s�����x����ւ�");	break;
			}
			char c_bgmct[256];	// �w�i�ύX�^�C�v�p�ϐ�
			switch (commu_state_edit[edit_line + i].GetBGMCT())
			{
			case BGM_CHANGE_FO_FI:	sprintf_s(c_bgmct, 256, "�e�n���e�h");	break;
			case BGM_CHANGE_S_P:	sprintf_s(c_bgmct, 256, "�r���o");		break;
			case BGM_CHANGE_S_FI:	sprintf_s(c_bgmct, 256, "�r���e�h");	break;
			default:				sprintf_s(c_bgmct, 256, "�e�n���o");	break;
			}
			int row_x = 570;	// �e��̌Œ�Ԋu
			if (edit_line + i >= 2 && edit_line + i <= COMMU_LINE_MAX)
			{
				DrawFormatStringFToHandle(bairitu * 99, screen_size_y + i * bairitu * 99 - bairitu * 198, GetColor(255, 255, 255), g_font3, "%d�F",
					//		%16s�E%d�E%s%s%s%s%64s�F%d�F%d�F%d", 
					edit_line + i
					//		//commu_state_edit[edit_line + i].command == "" ? "�@�@�@" : commu_state_edit[edit_line + i].command,
					//		commu_state_edit[edit_line + i].command,
					//		commu_state_edit[edit_line + i].move_commu_number,
					//		commu_state_edit[edit_line + i].name,
					//		strcmp(commu_state_edit[edit_line + i].name, "") != 0 && strcmp(commu_state_edit[edit_line + i].name2, "") != 0 ? "�E" : "",
					//		commu_state_edit[edit_line + i].name2,
					//		c_mouse,
					//		commu_state_edit[edit_line + i].line,
					//		commu_state_edit[edit_line + i].character[0],
					//		commu_state_edit[edit_line + i].character[1],
					//		commu_state_edit[edit_line + i].character[2]
				);
				// ���ݎw�蒆��edit_row�ɉ����ĕ\��������̂�ς���
				for (int j = -1; j < 2; j++)
				{
					if (edit_row + j >= EDIT_SELECT_COMMAND && edit_row + j <= EDIT_SELECT_PAGE_MAX)
					{
						char c_edit[256];
						switch (edit_row + j)
						{
						case EDIT_SELECT_COMMAND:						sprintf_s(c_edit, 256, "%s�F%d", commu_state_edit[edit_line + i].command, commu_state_edit[edit_line + i].move_commu_number);	break;
						case EDIT_SELECT_LINES_CHARACTER:				sprintf_s(c_edit, 256, "%s", commu_state_edit[edit_line + i].name);																break;
						case EDIT_SELECT_LINES_CHARACTER2:				sprintf_s(c_edit, 256, "%s", commu_state_edit[edit_line + i].name2);															break;
						case EDIT_SELECT_LINES:							sprintf_s(c_edit, 256, "%s", commu_state_edit[edit_line + i].line);																break;
						case EDIT_SELECT_LINES_MOUSE:					sprintf_s(c_edit, 256, c_mouse);																								break;
						case EDIT_SELECT_CHARACTER_LEFT:				sprintf_s(c_edit, 256, "%d", commu_state_edit[edit_line + i].character[0]);														break;
						case EDIT_SELECT_FE_LEFT:						sprintf_s(c_edit, 256, c_face_etc[0]);																							break;
						case EDIT_SELECT_CHARACTER_CENTER:				sprintf_s(c_edit, 256, "%d", commu_state_edit[edit_line + i].character[1]);														break;
						case EDIT_SELECT_FE_CENTER:						sprintf_s(c_edit, 256, c_face_etc[1]);																							break;
						case EDIT_SELECT_CHARACTER_RIGHT:				sprintf_s(c_edit, 256, "%d", commu_state_edit[edit_line + i].character[2]);														break;
						case EDIT_SELECT_FE_RIGHT:						sprintf_s(c_edit, 256, c_face_etc[2]);																							break;
						case EDIT_CHARACTER_CHANGE_TYPE:
							if (commu_state_edit[edit_line + i].GetCC() == CCC_INSTANT) { sprintf_s(c_edit, 256, "�u���\���E����ւ�"); }
							else if(commu_state_edit[edit_line + i].GetCC() == CCC_TRANSPARENCY_FAST){sprintf_s(c_edit, 256, "�����x��������ւ�");}
							else { sprintf_s(c_edit, 256, ""); }
							break;
						case EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM:	sprintf_s(c_edit, 256, c_cdu);																									break;
						case EDIT_SELECT_BACKGROUND:
							if (commu_state_edit[edit_line + i].GetBackground() == -1) { sprintf_s(c_edit, 256, "�w�i���폜"); }
							else if (commu_state_edit[edit_line + i].GetBackground() > 0) { sprintf_s(c_edit, 256, bgimage[commu_state_edit[edit_line + i].GetBackground() - 1].GetName()); }
							else { sprintf_s(c_edit, 256, ""); }
							break;
						case EDIT_SELECT_BACKGROUND_CHANGE_TYPE:		sprintf_s(c_edit, 256, c_bct);																									break;
						case EDIT_SELECT_BGM:
							if (commu_state_edit[edit_line + i].bgm == -1) { sprintf_s(c_edit, 256, music_string_stop.name); }
							else if (commu_state_edit[edit_line + i].bgm > 0) { sprintf_s(c_edit, 256, music_string[commu_state_edit[edit_line + i].bgm - 1].name); }
							else { sprintf_s(c_edit, 256, ""); }
							break;
						case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(c_edit, 256, c_bgmct);																								break;
							//case EDIT_SELECT_SE:
							//	if (commu_state_edit[edit_line + i].se == -1) { sprintf_s(c_edit, 256, se_string[0].name); }
							//	else if (commu_state_edit[edit_line + i].se > 0) { sprintf_s(c_edit, 256, se_string[commu_state_edit[edit_line + i].se - 0].name); }
							//	else { sprintf_s(c_edit, 256, ""); }
							//	break;
						case EDIT_SELECT_SE:	sprintf_s(c_edit, 256, "%s", GetSEString(commu_state_edit[edit_line + i].se));																				break;
						default:																																										break;
						}
						DrawFormatStringFToHandle(bairitu * (750 + j * row_x), screen_size_y + i * bairitu * 99 - bairitu * 198, GetColor(255, 255, 255), g_font3, "%s", c_edit);
					}
				}
			}
			if (i == -1)
			{
				for (int j = -1; j < 2; j++)
				{
					if (edit_row + j >= EDIT_SELECT_COMMAND && edit_row + j <= EDIT_SELECT_PAGE_MAX)
					{
						char c_edit_title[256];
						switch (edit_row + j)
						{
						case EDIT_SELECT_COMMAND:						sprintf_s(c_edit_title, 256, "�R�}���h�F�R�}���h�֌W���l");	break;
						case EDIT_SELECT_LINES_CHARACTER:				sprintf_s(c_edit_title, 256, "�䎌��");						break;
						case EDIT_SELECT_LINES_CHARACTER2:				sprintf_s(c_edit_title, 256, "�䎌��Q");					break;
						case EDIT_SELECT_LINES:							sprintf_s(c_edit_title, 256, "�䎌");						break;
						case EDIT_SELECT_LINES_MOUSE:					sprintf_s(c_edit_title, 256, "�䎌���p�N�^�C�v");			break;
						case EDIT_SELECT_CHARACTER_LEFT:				sprintf_s(c_edit_title, 256, "�L�����N�^�[��");				break;
						case EDIT_SELECT_FE_LEFT:						sprintf_s(c_edit_title, 256, "�L�����N�^�[������\��");		break;
						case EDIT_SELECT_CHARACTER_CENTER:				sprintf_s(c_edit_title, 256, "�L�����N�^�[����");			break;
						case EDIT_SELECT_FE_CENTER:						sprintf_s(c_edit_title, 256, "�L�����N�^�[��������\��");	break;
						case EDIT_SELECT_CHARACTER_RIGHT:				sprintf_s(c_edit_title, 256, "�L�����N�^�[�E");				break;
						case EDIT_SELECT_FE_RIGHT:						sprintf_s(c_edit_title, 256, "�L�����N�^�[�E����\��");		break;
						case EDIT_CHARACTER_CHANGE_TYPE:				sprintf_s(c_edit_title, 256, "�L�����N�^�[�ύX�^�C�v");		break;
						case EDIT_SELECT_CHARACTER_DISTANCE_UNIFORM:	sprintf_s(c_edit_title, 256, "�L�����ԋ����ψꉻ");			break;
						case EDIT_SELECT_BACKGROUND:					sprintf_s(c_edit_title, 256, "�w�i");						break;
						case EDIT_SELECT_BACKGROUND_CHANGE_TYPE:		sprintf_s(c_edit_title, 256, "�w�i�ύX�^�C�v");				break;
						case EDIT_SELECT_BGM:							sprintf_s(c_edit_title, 256, "�a�f�l");						break;
						case EDIT_SELECT_BGM_CHANGE_TYPE:				sprintf_s(c_edit_title, 256, "�a�f�l�ύX�^�C�v");			break;
						case EDIT_SELECT_SE:							sprintf_s(c_edit_title, 256, "�r�d");						break;
						default:										sprintf_s(c_edit_title, 256, "�i���ݒ�̍��ځj");			break;
							break;
						}
						DrawFormatStringFToHandle(bairitu * (750 + j * row_x), screen_size_y + i * bairitu * 99 - bairitu * 297, GetColor(255, 255, 255), g_font3, "%s", c_edit_title);
					}
				}
			}
		}
		// ���͓r���̕������`��
		DrawKeyInputString(screen_size_x / 2, (int)(bairitu * 345), InputHandle);
	}
}
// se�̈������當������擾����
char* GetSEString(int x)	// se�̕ϐ�
{
	sprintf_s(c_global_function, 256, "");
	if (x == -1) { sprintf_s(c_global_function, 256, "SE��~"); }
	else if (x > 0) { sprintf_s(c_global_function, 256, se[x - 1].GetName()); }
	return c_global_function;
}
#pragma region �L�[�g���K�[����
// �L�[�{�[�hB�L�[
BOOL IsINPUTBKeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_B) == TRUE)
	{
		if (g_inputbkey_prev == FALSE)
		{
			g_inputbkey_prev = TRUE;
			return TRUE;
		}
	}
	else { g_inputbkey_prev = FALSE; }
	return FALSE;
}
// 1�L�[
BOOL Is1KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_1) == TRUE)
	{
		if (g_1key_prev == FALSE)
		{
			g_1key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_1key_prev = FALSE; }
	return FALSE;
}
// 2�L�[
BOOL Is2KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_2) == TRUE)
	{
		if (g_2key_prev == FALSE)
		{
			g_2key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_2key_prev = FALSE; }
	return FALSE;
}
// 3�L�[
BOOL Is3KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_3) == TRUE)
	{
		if (g_3key_prev == FALSE)
		{
			g_3key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_3key_prev = FALSE; }
	return FALSE;
}
// 4�L�[
BOOL Is4KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_4) == TRUE)
	{
		if (g_4key_prev == FALSE)
		{
			g_4key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_4key_prev = FALSE; }
	return FALSE;
}
// 5�L�[
BOOL Is5KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_5) == TRUE)
	{
		if (g_5key_prev == FALSE)
		{
			g_5key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_5key_prev = FALSE; }
	return FALSE;
}
// 6�L�[
BOOL Is6KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_6) == TRUE)
	{
		if (g_6key_prev == FALSE)
		{
			g_6key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_6key_prev = FALSE; }
	return FALSE;
}
// 1�L�[
BOOL Is7KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_7) == TRUE)
	{
		if (g_7key_prev == FALSE)
		{
			g_7key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_7key_prev = FALSE; }
	return FALSE;
}
// 8�L�[
BOOL Is8KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_8) == TRUE)
	{
		if (g_8key_prev == FALSE)
		{
			g_8key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_8key_prev = FALSE; }
	return FALSE;
}
// 9�L�[
BOOL Is9KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_9) == TRUE)
	{
		if (g_9key_prev == FALSE)
		{
			g_9key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_9key_prev = FALSE; }
	return FALSE;
}
// 0�L�[
BOOL Is0KeyTrigger()
{
	if (CheckHitKey(KEY_INPUT_0) == TRUE)
	{
		if (g_0key_prev == FALSE)
		{
			g_0key_prev = TRUE;
			return TRUE;
		}
	}
	else { g_0key_prev = FALSE; }
	return FALSE;
}
// �}������
BOOL IsInsertTrigger()
{
	if (CheckHitKey(KEY_INPUT_I) == TRUE)
	{
		if (edit_insert_prev == FALSE)
		{
			edit_insert_prev = TRUE;
			return TRUE;
		}
	}
	else { edit_insert_prev = FALSE; }
	return FALSE;
}
// �R�s�y����
BOOL IsCopyPasteTrigger()
{
	BOOL input_control = (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) ? TRUE : FALSE;
	if ((CheckHitKey(KEY_INPUT_C) == TRUE || input_control == TRUE) && CheckHitKey(KEY_INPUT_E) == TRUE)
	{
		if (edit_copy_paste_prev == FALSE)
		{
			edit_copy_paste_prev = TRUE;
			return TRUE;
		}
	}
	else { edit_copy_paste_prev = FALSE; }
	return FALSE;
}
// �s�폜����
BOOL IsDeleteTrigger()
{
	BOOL input_control = (CheckHitKey(KEY_INPUT_LCONTROL) == TRUE || CheckHitKey(KEY_INPUT_RCONTROL) == TRUE) ? TRUE : FALSE;
	if ((CheckHitKey(KEY_INPUT_D) == TRUE || input_control == TRUE) && CheckHitKey(KEY_INPUT_L) == TRUE)
	{
		if (edit_delete_prev == FALSE)
		{
			edit_delete_prev = TRUE;
			return TRUE;
		}
	}
	else { edit_delete_prev = FALSE; }
	return FALSE;
}
// �k���Č�������^�C�v�̃T���l���̗v�f�Ɋւ�鐔�l��T���ۂ̋��ʏ���
int GetEditSamuneNumber(EditSamuneSearchType x)	// ���l�̃A�h���X,��������T���l�p���l�̎��
{
	int y = 0;
	// ���l��T��
	if (x == ESS_CHARACTER_DISTANCE)
	{
		for (int i = edit_line; i >= 2; i--)
		{
			y = commu_state_edit[i].GetCDU();
			if (y > 0 || y < 0) { return i; }
		}
	}
	for (int i = edit_line; i >= 2; i--)
	{
		// ��r�p���l�̒�`
		switch (x)
		{
		case ESS_CHARACTER_LEFT:	y = commu_state_edit[i].GetCharacter(0);	break;
		case ESS_CHARACTER_CENTER:	y = commu_state_edit[i].GetCharacter(1);	break;
		case ESS_CHARACTER_RIGHT:	y = commu_state_edit[i].GetCharacter(2);	break;
		case ESS_BACKGROUND:		y = commu_state_edit[i].GetBackground();	break;
		case ESS_BGM:
			y = commu_state_edit[i].GetBGM();
			if (edit_play_bgm != y && y != 0)
			{
				if (y < 0) 
				{
					edit_play_bgm = -1;
					MusicPlay(-1);
				}
				else
				{
					edit_play_bgm = y;
					MusicPlay(y - 1);
				}
			}
			break;
		default:																break;
		}
		if (y > 0){return i;}
		else if (y < 0) { return 0; }
	}
	// �Ȃ�������Ȃ������ꍇ�A���݂̂a�f�l���~������
	if(x == ESS_BGM)
	{
		edit_play_bgm = 0;
		MusicPlay(-1);
	}	
	return 0;
}

#pragma endregion
