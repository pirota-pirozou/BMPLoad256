
PROG = TEST.X						# �ŏI�I�ɍ쐬�������s�t�@�C����

#CC = cc
CC = gcc

#CFLAGS = /Fc /Ns					# for XC2 & SCD
CFLAGS = -c -fcombine-regs -fforce-addr -I$(INCLUDE) 		# for GCC

AS = as							# �A�Z���u��
AFLAGS = -w						# �A�Z���u���E�X�C�b�`
LK = lk							# �����J
LFLAGS = -l -o$(PROG) #-x		# �����J�E�X�C�b�`
LB = lib						# ���C�u�����A��
OBJS = main.o BMPLoad256.o 		# Main�Ɋ֌W���Ă���I�u�W�F�N�g�E�t�@�C����
LIBS = clib.l iocslib.l doslib.l \
       baslib.l floatfnc.l gnulib.l	# �֌W���Ă��郉�C�u����
INC1 = 							# �I�u�W�F�N�g�Ɋ֌W���Ă���w�b�_�t�@�C��
RM = rm							# �t�@�C���폜�R�}���h

#########
# �K��
#########
all: $(PROG)								# �f�t�H���g�̃^�[�Q�b�g

$(PROG): $(OBJS)							# ���s�t�@�C���쐬
	$(LK) $(LFLAGS) $(OBJS) $(LIBS)

main.o: main.c BMPLoad256.h
	$(CC) $(CFLAGS) $<

BMPLoad256.o: BMPLoad256.c BMPLoad256.h		# �b����̃��W���[���쐬
	$(CC) $(CFLAGS) $<

# clean�^�[�Q�b�g
.PHONY: clean

clean: $(PROG)
	$(RM) $(OBJS) $(PROG)
