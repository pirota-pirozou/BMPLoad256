// -*-  tab-width : 4 ; mode : C ; encode : ShiftJIS -*-
// Written by Pirota Pirozou, 2023/04
// BMPLoad256.h
//
// このコードは、２５６色ＢＭＰローダーのヘッダファイル である。
// GCC真里子版 環境で動作するように作られている。
//
// BMPLoad256.c / BMPLoad256.h は、自由に改変して自分のプログラムに組み込むことが可能。
// 著作権表記も必要ない。
// ただし、このコードを使用したことによるいかなる損害についても、作者は一切の責任を負わない。

#pragma once
#ifndef ____BMPLOAD256_H____
#define ____BMPLOAD256_H____

#include <stdio.h>
#include <stdlib.h>

typedef unsigned short WORD_t;
typedef unsigned int DWORD_t;
typedef unsigned char BYTE_t;

#define BI_RGB  0L
#define BI_BITFIELDS 3L

//typedef const char * LPSTR;
//typedef unsigned char u_char;


/// @brief ビットマップファイルヘッダー
typedef struct
{
    WORD_t bfType;
    DWORD_t bfSize;
    WORD_t bfReserved1;
    WORD_t bfReserved2;
    DWORD_t bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER;

/// @brief ビットマップ情報ヘッダー
typedef struct
{
    DWORD_t biSize;
    DWORD_t biWidth;
    DWORD_t biHeight;
    WORD_t biPlanes;
    WORD_t biBitCount;
    DWORD_t biCompression;
    DWORD_t biSizeImage;
    DWORD_t biXPelsPerMeter;
    DWORD_t biYPelsPerMeter;
    DWORD_t biClrUsed;
    DWORD_t biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER;

/// @brief カラーパレット
typedef struct
{
    BYTE_t rgbBlue;
    BYTE_t rgbGreen;
    BYTE_t rgbRed;
    BYTE_t rgbReserved;
} RGBQUAD, *LPRGBQUAD;

/// @brief ビットマップ情報
typedef struct _tagBITMAPINFO
{
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD          bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;

#ifdef __cplusplus
extern "C" {
#endif

// プロトタイプ宣言
int LoadBMP256(const char *fname);

#ifdef __cplusplus
}
#endif

#endif // __BMPLOAD256_H__
