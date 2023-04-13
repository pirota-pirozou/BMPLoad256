
PROG = TEST.X						# 最終的に作成される実行ファイル名

#CC = cc
CC = gcc

#CFLAGS = /Fc /Ns					# for XC2 & SCD
CFLAGS = -c -fcombine-regs -fforce-addr -I$(INCLUDE) 		# for GCC

AS = as							# アセンブラ
AFLAGS = -w						# アセンブラ・スイッチ
LK = lk							# リンカ
LFLAGS = -l -o$(PROG) #-x		# リンカ・スイッチ
LB = lib						# ライブラリアン
OBJS = main.o BMPLoad256.o 		# Mainに関係しているオブジェクト・ファイル名
LIBS = clib.l iocslib.l doslib.l \
       baslib.l floatfnc.l gnulib.l	# 関係しているライブラリ
INC1 = 							# オブジェクトに関係しているヘッダファイル
RM = rm							# ファイル削除コマンド

#########
# 規則
#########
all: $(PROG)								# デフォルトのターゲット

$(PROG): $(OBJS)							# 実行ファイル作成
	$(LK) $(LFLAGS) $(OBJS) $(LIBS)

main.o: main.c BMPLoad256.h
	$(CC) $(CFLAGS) $<

BMPLoad256.o: BMPLoad256.c BMPLoad256.h		# Ｃ言語のモジュール作成
	$(CC) $(CFLAGS) $<

# cleanターゲット
.PHONY: clean

clean: $(PROG)
	$(RM) $(OBJS) $(PROG)
