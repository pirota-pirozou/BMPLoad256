// -*-  tab-width : 4 ; mode : C ; encode : ShiftJIS -*-
// Written by Pirota Pirozou, 2023/04
// main.c
//
// このコードは、２５６色ＢＭＰローダーのソースコード である。
// GCC真里子版 環境で動作するように作られている。
//
// BMPLoad256.c / BMPLoad256.h は、自由に改変して自分のプログラムに組み込むことが可能。
// 著作権表記も必要ない。
// ただし、このコードを使用したことによるいかなる損害についても、作者は一切の責任を負わない。

#include <iocslib.h>
//#include <doslib.h>
#include "BMPLoad256.h"

/* main */
int main(int argc, char *argv[])
{
    // スーパーバイザーモードへ
    int usp = B_SUPER(0);

    allmem();       // malloc()/free()を使えるようにする

    CRTMOD(8);      // 512x512px/31KHz/256色モード/２枚
    G_CLR_ON();     // グラフィック画面クリア・表示ON

    // BMP画像の読み込み
    LoadBMP256("space.bmp");

    // ユーザーモードへ
    B_SUPER(usp);

    return 0;
}
