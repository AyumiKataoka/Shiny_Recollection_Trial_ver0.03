#ifndef __SOUNDROOM_H__
#define __SOUNDROOM_H__

#include <DxLib.h>
#include "main.h"

#define SR_BGM_ALTERNATIVE_NUMBER 34 + 1	// �T�E���h���[�����ł̂a�f�l�I�������i�wBGM_NUMBER + 1�x�j

// �r�d�^�C�g���f�[�^
#pragma region ver0.00607���쎞�R�����g���R�[�h
//class SEStringData
//{
//public:
//	char* name;
//	void NameChange(int x)
//	{
//		switch (x)
//		{
//		#pragma region ver0.0026���쎞�R�����g���R�[�h
//		//case 0:		name = "�i���[�v�j�r�d��~";					break;
//		//case 1:		name = "�E�B���h�`���C��";						break;
//		//case 2:		name = "����i��l�j";							break;
//		//case 3:		name = "����i�吨�j";							break;
//		//case 4:		name = "�`���C��";								break;
//		//case 5:		name = "�h���u��";								break;
//		//case 6:		name = "����";									break;
//		//case 7:		name = "�J�[�e�����J����";						break;
//		//case 8:		name = "�X�̃h�A���J����";						break;
//		//case 9:		name = "�����˂��J����";						break;
//		//case 10:	name = "�m�b�N";								break;
//		//case 11:	name = "���̂�������";							break;
//		//case 12:	name = "��";									break;
//		//case 13:	name = "�I���������肷��";						break;
//		//case 14:	name = "��̐��̗���̉�";						break;
//		//case 15:	name = "��̗���̉� Long Ver";					break;
//		//case 16:	name = "�z���C���";							break;
//		//case 17:	name = "�o�X�P�b�g�{�[���S�[��";				break;
//		//case 18:	name = "�l�Ɛl�Ƃ��Ԃ���";					break;
//		//case 19:	name = "�L�̖���";							break;
//		//case 20:	name = "�}�b�v���ړ�����r�d";					break;
//		//case 21:	name = "�n�C�^�b�`";							break;
//		//case 22:	name = "���@����";							break;
//		//case 23:	name = "���������̐��k�����̐�";				break;
//		//case 24:	name = "���������̐�Long  Ver";					break;
//		//case 25:	name = "�V���[�Y�̉�";							break;
//		//case 26:	name = "�L�[�{�[�h";							break;
//		//case 27:	name = "�����U��΂鉹";						break;
//		//case 28:	name = "�g�с@�ʒm";							break;
//		//case 29:	name = "�֎q�𗧂�";							break;
//		//case 30:	name = "�K�^�K�^�Ƃ�������";					break;
//		//case 31:	name = "�g�с@���M��";							break;
//		//default:	name = "";										break;
//#pragma endregion
//		case 0:		name = (char*)"�i���[�v�j�r�d��~";		break;
//		case 1:		name = (char*)"�E�B���h�`���C��";		break;
//		case 2:		name = (char*)"����i��l�j";			break;
//		case 3:		name = (char*)"����i�吨�j";			break;
//		case 4:		name = (char*)"�`���C��";				break;
//		case 5:		name = (char*)"�h���u��";				break;
//		case 6:		name = (char*)"����";					break;
//		case 7:		name = (char*)"�����i���[�v�j";			break;
//		case 8:		name = (char*)"�J�[�e�����J����";		break;
//		case 9:		name = (char*)"�X�̃h�A���J����";		break;
//		case 10:	name = (char*)"�����˂��J����";			break;
//		case 11:	name = (char*)"�m�b�N";					break;
//		case 12:	name = (char*)"���̂�������";			break;
//		case 13:	name = (char*)"��";						break;
//		case 14:	name = (char*)"�I���������肷��";		break;
//		case 15:	name = (char*)"��̐��̗���̉�";		break;
//		case 16:	name = (char*)"��̗���̉� Long Ver";	break;
//		case 17:	name = (char*)"�z���C���";				break;
//		case 18:	name = (char*)"�o�X�P�b�g�{�[���S�[��";	break;
//		case 19:	name = (char*)"�l�Ɛl�Ƃ��Ԃ���";		break;
//		case 20:	name = (char*)"�L�̖���";				break;
//		case 21:	name = (char*)"�}�b�v���ړ�����r�d";	break;
//		case 22:	name = (char*)"�n�C�^�b�`";				break;
//		case 23:	name = (char*)"���@����";				break;
//		case 24:	name = (char*)"���������̐��k�����̐�";	break;
//		case 25:	name = (char*)"���������̐�Long  Ver";	break;
//		case 26:	name = (char*)"�V���[�Y�̉�";			break;
//		case 27:	name = (char*)"�L�[�{�[�h";				break;
//		case 28:	name = (char*)"�����U��΂鉹";			break;
//		case 29:	name = (char*)"�g�с@�ʒm";				break;
//		case 30:	name = (char*)"�֎q�𗧂�";			break;
//		case 31:	name = (char*)"�K�^�K�^�Ƃ�������";		break;
//		case 32:	name = (char*)"�g�с@���M��";			break;
//		case 33:	name = (char*)"�A�C�R������������";		break;
//		case 34:	name = (char*)"�g���������鉹";			break;
//		case 35:	name = (char*)"�t���b�V���o�b�N";		break;
//		case 36:	name = (char*)"�v���o����";				break;
//		case 37:	name = (char*)"�J���˂̉�";				break;
//		case 38:	name = (char*)"�K�T�K�T";				break;
//		case 39:	name = (char*)"�삯�鑫��";				break;
//		case 40:	name = (char*)"�����J���鉹";			break;
//		case 41:	name = (char*)"����������";				break;
//		case 42:	name = (char*)"����������(LOOP)";		break;
//		case 43:	name = (char*)"�Â��Ɍ˂��J��";			break;
//		case 44:	name = (char*)"�֎q�ɍ���";				break;
//		case 45:	name = (char*)"�Z�~�̐�";				break;
//		case 46:	name = (char*)"�Z�~�̐�(LOOP)";			break;
//		case 47:	name = (char*)"�������J��";				break;
//		case 48:	name = (char*)"�������~�߂鉹";			break;
//		case 49:	name = (char*)"��ʓ]��IN";				break;
//		case 50:	name = (char*)"��ʓ]��OUT";			break;
//		case 51:	name = (char*)"�X�^�[�g��ʑI��";		break;
//		case 52:	name = (char*)"Start";					break;
//		case 53:	name = (char*)"�����̉�";				break;
//		case 54:	name = (char*)"�����̉�(LOOP)";			break;
//		default:	name = (char*)"";						break;
//		}
//	}
//};
//extern SEStringData se_string[];
#pragma endregion

// �����͈͂Ń}�E�X�������A�����ꂽ�灛������t���O�icfsr=click_flag_sound_room�j
extern BOOL cfsr_play_music[];	// �a�f�l���Đ�����i�o�O���N���Ȃ����v�m�F�j
extern BOOL cfsr_play_se[];		// �a�f�l���Đ�����i�o�O���N���Ȃ����v�m�F�j
extern BOOL cfsr_move_title;	// �^�C�g����ʂֈړ�
extern BOOL cfsr_bgm_down;		// �a�f�l���ʂ�������
extern BOOL cfsr_bgm_up;		// �a�f�l���ʂ��グ��
extern BOOL cfsr_se_down;		// �r�d���ʂ�������
extern BOOL cfsr_se_up;			// �r�d���ʂ��グ��

#pragma region ver0.00391���쎞�R�����g���R�[�h
//extern float sound_room_coordinate_alternative_x;		// BGM�I������{x���W
#pragma endregion
extern float sound_room_coordinate_alternative_x[];		// BGM�I������{x���W
extern float sound_room_coordinate_alternative_y[];		// BGM�I������{y���W�i�o�O���N���Ȃ����v�m�F�j
extern float sound_room_coordinate_alternative_se_x[];	// �r�d�I������{x���W
extern float sound_room_coordinate_alternative_se_y[];	// �r�d�I������{y���W�i�o�O���N���Ȃ����v�m�F�j
extern float sound_room_size_alternative_x;				// BGM�I������{x��
extern float sound_room_size_alternative_y;				// BGM�I������{y��
extern float sound_room_coordinate_string_title_x;		// �wTITLE�xx���W
extern float sound_room_coordinate_string_title_y;		// �wTITLE�xy���W
extern float sound_room_coordinate_bgm_message_y;		// BGM���ʊ֌WY���W
extern float sound_room_coordinate_bgm_volume_up_x;		// BGM�w���x����X���W
extern float sound_room_coordinate_bgm_volume_up_y;		// BGM�w���x����Y���W
extern float sound_room_coordinate_se_message_y;		// SE���ʊ֌WY���W
extern float sound_room_coordinate_se_volume_up_x;		// SE�w���x����X���W
extern float sound_room_coordinate_se_volume_up_y;		// SE�w���x����Y���W

void SoundRoom();					// SoundRoom��Ԃ̃��C������
void SoundRoomControl();			// �T�E���h���[����ʑ��쏈��
void SoundRoomCoordinateSetting();	// �T�E���h���[����ʂŎg���l�X�ȍ��W���i�āj��`����
void DrawSoundRoom();				// �T�E���h���[���̕`�揈��

#endif
