#if !defined __DEFINE	//�����A�}�N�����܂���`����ĂȂ����
#define __DEFINE		//�}�N�����`
//��������������������������������������������������������������������������������������������������������������
#define WIN_CLASSNAME "Window Sample"	//�N���X��  ��÷��P144(9,20�s�ڂŎw��j
#define WIN_W 640						//�E�B���h�E�̕�
#define WIN_H 480						//�E�B���h�E�̍���
#define CWIN_W 400						//�q�E�B���h�E�̕�
#define CWIN_H 360						//�q�E�B���h�E�̍���
#define MWIN_W 320						//�~�j�}�b�v�q�E�B���h�E�̕��A����
#define MWIN_H 320						
#define WIN_TITLE "�e�E�B���h�E���A�N�e�B�u�ŃX�y�[�X�������ƃG�l�~�[�o���ʒu�ݒ胂�[�h�iF11�łP�O�ɖ߂�j"		//�E�B���h�E�̃^�C�g��

//�}�b�v
#define BMPTIP_W 20		//ϯ�����߂̉摜���̉��ɕ��񂾃`�b�v�̐�
#define BMPTIP_H 15		//ϯ�����߂̉摜���̏c�ɕ��񂾃`�b�v�̐�	
#define TIP_MAX (20*15)		//�`�b�v�̎�ނ̐�

#define TIP_W 32		//�`�b�v�̕�
#define TIP_H 32		//�`�b�v�̍���
#define MAP_XNUM 640	//�}�b�v�̃��R����
#define MAP_YNUM 40		//�}�b�v�̃^�e����
#define WINMAP_W 20		//�E�B���h�E���ɕ\������`�b�v�̃��R�̐�
#define WINMAP_H 14		//�E�B���h�E���ɕ\������`�b�v�̃^�e�̐�

//�G�l�~�[�o���|�C���g
#define ENEONPOS_MAX 80	//�G�l�~�[���o��������|�C���g�̍ő吔
#define ENETYPE_MAX 18	//�G�l�~�[�̎�ނ̍ő吔

#define MY_DELETEDC(x) if(x != NULL) {DeleteDC(x); x = NULL;}	//HDC�̉����NULL��������}�N��
//������������������������������������������������������������������������������������������������������������������
#endif