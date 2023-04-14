// -*-  tab-width : 4 ; mode : C ; encode : ShiftJIS -*-
// Written by Pirota Pirozou, 2023/04
// main.c
//
// ���̃R�[�h�́A�Q�T�U�F�a�l�o���[�_�[�̃\�[�X�R�[�h �ł���B
// GCC�^���q�� ���œ��삷��悤�ɍ���Ă���B
//
// BMPLoad256.c / BMPLoad256.h �́A���R�ɉ��ς��Ď����̃v���O�����ɑg�ݍ��ނ��Ƃ��\�B
// ���쌠�\�L���K�v�Ȃ��B
// �������A���̃R�[�h���g�p�������Ƃɂ�邢���Ȃ鑹�Q�ɂ��Ă��A��҂͈�؂̐ӔC�𕉂�Ȃ��B

#include <iocslib.h>
//#include <doslib.h>
#include "BMPLoad256.h"

/* main */
int main(int argc, char *argv[])
{
    // �X�[�p�[�o�C�U�[���[�h��
    int usp = B_SUPER(0);

    allmem();       // malloc()/free()���g����悤�ɂ���

    CRTMOD(8);      // 512x512px/31KHz/256�F���[�h/�Q��
    G_CLR_ON();     // �O���t�B�b�N��ʃN���A�E�\��ON

    // BMP�摜�̓ǂݍ���
    LoadBMP256("space.bmp");

    // ���[�U�[���[�h��
    B_SUPER(usp);

    return 0;
}
