#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include <DxLib.h>
#include "main.h"

#define COMMU_CHARACTER_NUMBER 5	// �ʃR�~�������݂���L�����̑���
#define GAME_ALL_WEAK 2				// �S���R�T�ڂ��琔���āA�K�v�ȏT�̐��i���݂͑̌��łȂ̂łQ�j
// �ړ���}�b�v�̏��
enum MapDestinationType
{
	MAP_DESTINATION_LEFT, MAP_DESTINATION_CENTER, MAP_DESTINATION_RIGHT
};
extern MapDestinationType g_map_destination;
// tips����p������
struct TipsStringData
{
	char* string;
	float x;		// ������\��X���W
};
extern TipsStringData tips_string[2];
// tips�֌W�̍\����
struct TipsData
{
	int id;										// ID����
	char tips[256];								// ���e
	BOOL appear;								// �o���ς݃t���O
	static constexpr int LOAD_LIMIT = 128;
	static void NumberCount() { number++; };	// number���J�E���g����
	// ����constexpr������̂��s��
	static constexpr int GetNumber() { return number; }
private:
	static int	number;	// ��
};
extern TipsData tips_data[TipsData::LOAD_LIMIT];
// �}�b�v�֌W�Ŏ�Ɏg����^���O���[�o���ϐ��A�萔
class GlobalStaticMap
{
	static BOOL trial_commu_viewed[COMMU_CHARACTER_NUMBER];	// �X�`���̌��łŃR�~���������t���O
public:
	static constexpr int WEEK_INITIAL_VALUE = 12;	//	�����̌��T
	static void TrialCommuViewedReset();
	static void SetTrialCommuViewed(int x, BOOL y) { trial_commu_viewed[x] = y; }
	static BOOL GetTrialCommuViewed(int x) { return trial_commu_viewed[x]; }
	static int GetWeekInitialValue() { return WEEK_INITIAL_VALUE; }
};

extern BOOL map_move_commu_check;	// �I�������R�~�����{�����邩�m�F����t���O
extern BOOL map_commu_upper[3][2];	// �}�b�v��ʂɃR�~���A�C�R�����o�����邩
// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfgm=click_flag_game_map�j
/*
extern BOOL cfgm_move_left;						// ���}�b�v�ֈړ�
extern BOOL cfgm_move_right;					// �E�}�b�v�ֈړ�
*/
extern BOOL cfgm_commu_check_ok;				// �I���R�~���ֈڍs����
extern BOOL cfgm_commu_check_no;				// �I���R�~���{����ʂ���������

extern int game_week_number;							// �Q�[�����̌��A�T���Q�Ƃ���ϐ�
extern int commu_look_count[COMMU_CHARACTER_NUMBER];	// �}�b�v��ʂ���A�C�R����I�����A�i�t�����h�R�~���ȊO�́j�e�L�����̃R�~����������
//extern int select_map_number;							// �I�΂�Ă���}�b�v�t�h
extern int map_font_arrow;								// �}�b�v��ʖ��̃t�H���g�T�C�Y

extern float draw_map_plus_x;				// �}�b�v�t�h�ɉ��Z����x���W�l
//extern float map_arrow_left_x;				// �����ɍs������x���W�l
//extern float map_arrow_right_x;				// �E���ɍs������x���W�l
extern float draw_map_space;				// �e�}�b�v�Ԃ̌���
extern float draw_map_commu_choice_x[2];						// �R�~���ړ��I����x���W�n�_
extern float draw_map_commu_choice_y;							// �R�~���ړ��I����y���W�n�_

void GameMapNext();						// �}�b�v��ʈڍs����
void GameMap();							// GAME_MAP��Ԃ̃��C������
void GameMapControl();					// �}�b�v��ʑ��쏈��
void GameMapFlame();					// �}�b�v���[�h���P�t���[�����ɍs���鏈��
void GameMapTipsSubstitution();			// tips������f�[�^��������
void GameMapCoordinateSetting();		// �}�b�v��ʂŎg���l�X�ȍ��W���i�āj��`����
void DrawGameMap();						// �}�b�v���[�h���`�揈��

BOOL GameMapUpperCheck(int x, int y);	// �Ή�����L�����R�~�����o�����邩�`�F�b�N����
BOOL GameMapControlCommuCheck(BOOL x);	// �}�b�v�A�C�R���N���b�N�m�F�p�֐�
#endif
