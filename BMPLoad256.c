// -*-  tab-width : 4 ; mode : C ; encode : ShiftJIS -*-
// Written by Pirota Pirozou, 2023/04
// BMPLoad256.c
//
// このコードは、２５６色ＢＭＰローダーのソースコード である。
// GCC真里子版 環境で動作するように作られている。
//
// BMPLoad256.c / BMPLoad256.h は、自由に改変して自分のプログラムに組み込むことが可能。
// 著作権表記も必要ない。
// ただし、このコードを使用したことによるいかなる損害についても、作者は一切の責任を負わない。

//#include <iocslib.h>
//#include <doslib.h>
#include "BMPLoad256.h"

// xdev68k環境でmalloc()/free()を使うとうまく動作しないので、
// 代わりに、DOSコールのMALLOC()/MFREE()を使う関数を使用します。
// allmem()を使えばmalloc()/free() が使えるのでコメントアウト
//#define dos_malloc(siz)    	MALLOC((siz))
//#define dos_free(ptr)   	MFREE((int)(ptr))

static BITMAPFILEHEADER fileHeader;
static BITMAPINFOHEADER infoHeader;
static RGBQUAD palette[256];

// word値のエンディアンをスワップします
static inline WORD_t swap_endian_word(WORD_t value)
 {
    return (value << 8) | (value >> 8);
}

// dword値のエンディアンをスワップします
static inline DWORD_t swap_endian_dword(DWORD_t value)
 {
    return (value << 24) |
           ((value << 8) & 0x00FF0000) |
           ((value >> 8) & 0x0000FF00) |
           (value >> 24);
}

/// @brief BMP256色画像の読み込み
/// @param fname ファイル名
/// @return 結果
/// @retval 0 失敗
/// @retval 1 成功
int LoadBMP256(const char *fname)
{
    int imageSize;
    BYTE_t *imageData;
	WORD_t *pal;
	WORD_t *vram;
	int i;
	int x, y;
	int width, height;


	FILE *fp = fopen(fname, "rb");
    if (fp == NULL)
	{
        fprintf(stderr, "ファイルを開けませんでした\n");
        return 0;
    }

    fread(&fileHeader, sizeof(fileHeader), 1, fp);
    fread(&infoHeader, sizeof(infoHeader), 1, fp);
    fread(&palette, sizeof(RGBQUAD), 256, fp);

	// エンディアンのスワップをします
	// ヘッダーの情報は、リトルエンディアンで記述されています
	fileHeader.bfType = swap_endian_word(fileHeader.bfType);
	fileHeader.bfSize = swap_endian_dword(fileHeader.bfSize);
	fileHeader.bfReserved1 = swap_endian_word(fileHeader.bfReserved1);
	fileHeader.bfReserved2 = swap_endian_word(fileHeader.bfReserved2);
	fileHeader.bfOffBits = swap_endian_dword(fileHeader.bfOffBits);

	infoHeader.biSize = swap_endian_dword(infoHeader.biSize);
	infoHeader.biWidth = swap_endian_dword(infoHeader.biWidth);
	infoHeader.biHeight = swap_endian_dword(infoHeader.biHeight);
	infoHeader.biPlanes = swap_endian_word(infoHeader.biPlanes);
	infoHeader.biBitCount = swap_endian_word(infoHeader.biBitCount);
	infoHeader.biCompression = swap_endian_dword(infoHeader.biCompression);
	infoHeader.biSizeImage = swap_endian_dword(infoHeader.biSizeImage);
	infoHeader.biXPelsPerMeter = swap_endian_dword(infoHeader.biXPelsPerMeter);
	infoHeader.biYPelsPerMeter = swap_endian_dword(infoHeader.biYPelsPerMeter);
	infoHeader.biClrUsed = swap_endian_dword(infoHeader.biClrUsed);
	infoHeader.biClrImportant = swap_endian_dword(infoHeader.biClrImportant);

	// デバッグ用：ヘッダーの情報を表示します
	printf("bfType = %X\n", fileHeader.bfType);
	printf("biBitCount = %d\n", infoHeader.biBitCount);
	printf("biWidth = %d\n", infoHeader.biWidth);
	printf("biHeight = %d\n", infoHeader.biHeight);

    if (fileHeader.bfType != 0x4D42 // 'BM'
		 		|| infoHeader.biBitCount != 8)
	{
        fprintf(stderr, "サポートされていないフォーマットです\n");
        fclose(fp);
        return 0;
    }

    imageSize = infoHeader.biWidth * infoHeader.biHeight;
    imageData = (BYTE_t *)malloc(imageSize);
	if (imageData == NULL)
	{
        fprintf(stderr, "メモリが確保できません。\n");
		free(imageData);
        fclose(fp);
        return 1;
	}
    fread(imageData, 1, imageSize, fp);
    fclose(fp);

	// pallete を使用して、必要な操作を行います
	pal = (WORD_t *)0xE82000;
	for (i = 0; i < 256; i++)
	{
		BYTE_t r = palette[i].rgbRed >> 3;
		BYTE_t g = palette[i].rgbGreen >> 3;
		BYTE_t b = palette[i].rgbBlue >> 3;
		WORD_t col = (b << 1) | (r << 6) | (g << 11);
		pal[i] = col;
	}

	// 画像データをVRAMに転送します
	vram = (WORD_t *)0xC00000;
	width = infoHeader.biWidth;
	height = infoHeader.biHeight;

	for (y = 0; y < height; ++y)
	{
		WORD_t* vramLine = &vram[y * 512];
		const BYTE_t *imageLine = &imageData[(height - y - 1) * width];

		for (x = 0; x < width; ++x)
		{
			vramLine[x] = imageLine[x];
		}
	}

	// メモリを解放します
    free(imageData);
    return 1;
}
