//�Q�[���p�̃Z�[�u�A���[�h���܂Ƃ߂��w�b�_�t�@�C��
#if !defined __GAME_SAVELOADMACRO
#define __GAME_SAVELOADMACRO
//����������������������������������������������������������������������������������������������������������������������
#include <windows.h>	//Windows�p�w�b�_�t�@�C��

void GameSave(char *);	//�Q�[���̃f�[�^�Z�[�u�̊֐��̃v���g�^�C�v�錾
void GameLoad(char *);	//�Q�[���̃f�[�^���[�h�̊֐��̃v���g�^�C�v�錾
void EneOnPosSave(char *);	//�K�o���ʒu�Z�[�u�̊֐��̃v���g�^�C�v�錾
void EneOnPosLoad(char *);	//�K�o���ʒu���[�h�̊֐��̃v���g�^�C�v�錾
//����������������������������������������������������������������������������������������������������������������������������
#endif