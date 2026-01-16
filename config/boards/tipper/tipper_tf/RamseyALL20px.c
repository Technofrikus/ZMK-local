/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --no-compress --stride 1 --align 1 --font RamseyTest-BlackCondensedItalic-BF64069d9ad0c68.ttf --symbols 1234567890ABCDEFGHIKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz --format lvgl -o Ramsey.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef RAMSEY
#define RAMSEY 1
#endif

#if RAMSEY

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x1f, 0xe3, 0xff, 0x3f, 0xf7, 0xdf, 0x7d, 0xe7,
    0xde, 0x79, 0xe7, 0x9e, 0x7b, 0xe7, 0xbe, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8,

    /* U+0031 "1" */
    0x3c, 0xf3, 0xcf, 0x7d, 0xf7, 0xde, 0x79, 0xe7,
    0xbe, 0xfb, 0xc0,

    /* U+0032 "2" */
    0x1f, 0xe3, 0xff, 0x3f, 0xf7, 0xde, 0x1, 0xe0,
    0x1e, 0x3f, 0xe7, 0xfe, 0x7f, 0xc7, 0x80, 0xf8,
    0xf, 0xfc, 0xff, 0xcf, 0xfc,

    /* U+0033 "3" */
    0x3f, 0xf3, 0xff, 0x3f, 0xf0, 0x3c, 0x7, 0x80,
    0xf0, 0x1f, 0xc1, 0xfe, 0x3, 0xef, 0xbe, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8,

    /* U+0034 "4" */
    0x3d, 0xe7, 0xbc, 0xff, 0xbd, 0xf7, 0xbe, 0xf7,
    0x9e, 0xf7, 0xde, 0xff, 0xff, 0xff, 0xff, 0x83,
    0xe0, 0x78, 0xf, 0x0,

    /* U+0035 "5" */
    0x3f, 0xf3, 0xff, 0x3f, 0xe7, 0xc0, 0x7c, 0x7,
    0xbc, 0x7f, 0xe7, 0xfe, 0x3, 0xe0, 0x3e, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8,

    /* U+0036 "6" */
    0x1f, 0xe3, 0xfe, 0x7f, 0xe7, 0xde, 0x7c, 0x7,
    0x98, 0x7f, 0xc7, 0xfe, 0x7b, 0xef, 0xbc, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8,

    /* U+0037 "7" */
    0x3f, 0xe7, 0xf8, 0xff, 0x1, 0xe0, 0x7c, 0xf,
    0x3, 0xe0, 0x78, 0x1f, 0x3, 0xc0, 0xf8, 0x1e,
    0x7, 0xc0, 0xf0, 0x0,

    /* U+0038 "8" */
    0x1f, 0xe3, 0xfe, 0x3f, 0xe7, 0xde, 0x7d, 0xe7,
    0xfe, 0x1f, 0x7, 0xfc, 0x7b, 0xcf, 0xbc, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8,

    /* U+0039 "9" */
    0x1f, 0xe3, 0xff, 0x3f, 0xf3, 0xdf, 0x7d, 0xe7,
    0xde, 0x7f, 0xe7, 0xfe, 0xb, 0xe0, 0x3e, 0x7b,
    0xe7, 0xfc, 0x7f, 0xc7, 0xf8,

    /* U+0041 "A" */
    0x1f, 0xe3, 0xfc, 0x7f, 0x8f, 0xf3, 0xfe, 0x7b,
    0xcf, 0x79, 0xef, 0x7d, 0xef, 0xfd, 0xff, 0xbf,
    0xff, 0xbf, 0xf7, 0xc0,

    /* U+0042 "B" */
    0x3f, 0xe3, 0xfe, 0x3f, 0xf3, 0xde, 0x7d, 0xe7,
    0xfe, 0x7f, 0x87, 0xfc, 0x7b, 0xe7, 0xbe, 0x7b,
    0xef, 0xfc, 0xff, 0xcf, 0xf8,

    /* U+0043 "C" */
    0x1f, 0xe3, 0xfe, 0x3f, 0xe7, 0xde, 0x7d, 0xe7,
    0xc0, 0x78, 0x7, 0x80, 0x78, 0x7, 0xbc, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8,

    /* U+0044 "D" */
    0x3f, 0xc3, 0xfe, 0x3f, 0xe3, 0xde, 0x7d, 0xe7,
    0xde, 0x79, 0xe7, 0xbe, 0x7b, 0xe7, 0xbe, 0x7b,
    0xcf, 0xfc, 0xff, 0xcf, 0xf8,

    /* U+0045 "E" */
    0x3f, 0x8f, 0xe3, 0xf8, 0xf0, 0x7c, 0x1f, 0xe7,
    0xb1, 0xec, 0x78, 0x1e, 0x7, 0x83, 0xfc, 0xff,
    0x3f, 0xc0,

    /* U+0046 "F" */
    0x3f, 0x9f, 0xcf, 0xe7, 0x87, 0xc3, 0xe1, 0xec,
    0xf6, 0x7b, 0x3c, 0x1e, 0x1f, 0xf, 0x87, 0x80,

    /* U+0047 "G" */
    0x1f, 0xe3, 0xfe, 0x3f, 0xe7, 0xde, 0x7d, 0xe7,
    0xc0, 0x7b, 0xe7, 0xbe, 0x7b, 0xe7, 0xbc, 0xfb,
    0xcf, 0xfc, 0xfb, 0xc7, 0xfc,

    /* U+0048 "H" */
    0x3c, 0xf3, 0xdf, 0x3d, 0xf3, 0xdf, 0x7d, 0xe7,
    0xfe, 0x7f, 0xe7, 0xfe, 0x7b, 0xe7, 0xbe, 0x7b,
    0xcf, 0xbc, 0xfb, 0xcf, 0x3c,

    /* U+0049 "I" */
    0x3c, 0xf3, 0xcf, 0x7d, 0xf7, 0xde, 0x79, 0xe7,
    0xbe, 0xfb, 0xe0,

    /* U+004B "K" */
    0x3e, 0xf1, 0xf7, 0x8f, 0x7c, 0x7b, 0xc3, 0xde,
    0x1f, 0xe0, 0xff, 0xf, 0xf8, 0x7f, 0xc3, 0xde,
    0x1e, 0xf0, 0xf7, 0x87, 0xbc, 0x3d, 0xf0,

    /* U+004C "L" */
    0x3c, 0x3c, 0x3c, 0x3c, 0x7c, 0x7c, 0x7c, 0x78,
    0x78, 0x78, 0x78, 0xff, 0xff, 0xff,

    /* U+004D "M" */
    0x3f, 0x7f, 0x3f, 0x7f, 0x7f, 0x7e, 0x7f, 0x7e,
    0x7f, 0x7e, 0x7f, 0x7e, 0x7f, 0xfe, 0x77, 0xde,
    0x77, 0xde, 0xf7, 0xdc, 0xf7, 0xdc, 0xf7, 0xbc,
    0xf7, 0xbc, 0xf7, 0xbc,

    /* U+004E "N" */
    0x3f, 0x79, 0xfb, 0xcf, 0xde, 0xfe, 0xf7, 0xf7,
    0x3f, 0xb9, 0xfd, 0xce, 0xfe, 0x77, 0xf3, 0xbf,
    0xbd, 0xfd, 0xef, 0xcf, 0x7e, 0x7b, 0xf0,

    /* U+004F "O" */
    0x1f, 0xe3, 0xff, 0x3f, 0xf7, 0xdf, 0x7d, 0xe7,
    0xde, 0x79, 0xe7, 0x9e, 0x7b, 0xe7, 0xbe, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8,

    /* U+0050 "P" */
    0x3f, 0xe3, 0xff, 0x3f, 0xf3, 0xdf, 0x7d, 0xe7,
    0xde, 0x79, 0xe7, 0xbe, 0x7b, 0xe7, 0xbc, 0x78,
    0xf, 0x80, 0xf8, 0xf, 0x0,

    /* U+0051 "Q" */
    0x1f, 0xe3, 0xff, 0x3f, 0xf7, 0xdf, 0x7d, 0xe7,
    0xde, 0x79, 0xe7, 0x9e, 0x7b, 0xe7, 0xbe, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8, 0x7, 0x0, 0x78,
    0x7, 0x80, 0x78,

    /* U+0052 "R" */
    0x3f, 0xe3, 0xfe, 0x3f, 0xf3, 0xde, 0x7d, 0xe7,
    0xde, 0x7f, 0xe7, 0xfc, 0x7b, 0x7, 0xbc, 0x7b,
    0xcf, 0xbc, 0xfb, 0xcf, 0xbc,

    /* U+0053 "S" */
    0x1f, 0xe7, 0xfc, 0xff, 0xbe, 0xf7, 0xc0, 0xff,
    0x9f, 0xf9, 0xff, 0x3, 0xff, 0x7b, 0xef, 0x7f,
    0xef, 0xfc, 0xff, 0x0,

    /* U+0054 "T" */
    0xff, 0xff, 0xff, 0xfc, 0x78, 0x3e, 0xf, 0x83,
    0xe0, 0xf0, 0x3c, 0xf, 0x3, 0xc1, 0xf0, 0x7c,
    0x1f, 0x0,

    /* U+0055 "U" */
    0x3d, 0xf3, 0xdf, 0x3d, 0xe7, 0xde, 0x7d, 0xe7,
    0xde, 0x79, 0xe7, 0xbe, 0x7b, 0xe7, 0xbc, 0xfb,
    0xcf, 0xfc, 0xff, 0xc7, 0xf8,

    /* U+0056 "V" */
    0xfb, 0xfe, 0xff, 0x7f, 0xde, 0xf7, 0xbd, 0xef,
    0x7b, 0xfc, 0xff, 0x3f, 0xcf, 0xf3, 0xfc, 0xfe,
    0x3f, 0x80,

    /* U+0057 "W" */
    0xf3, 0xcf, 0xf7, 0xde, 0xf7, 0xde, 0xf7, 0xde,
    0xf7, 0xde, 0xf7, 0xdc, 0xff, 0xdc, 0xfd, 0xfc,
    0xfd, 0xfc, 0xed, 0xf8, 0xfd, 0xf8, 0xfd, 0xf8,
    0xfd, 0xf8, 0xf9, 0xf0,

    /* U+0058 "X" */
    0x3e, 0xf3, 0xff, 0x1f, 0xe1, 0xfe, 0x1f, 0xc1,
    0xfc, 0x1f, 0xc1, 0xf8, 0x3f, 0xc3, 0xfc, 0x3f,
    0xc7, 0xbc, 0x7b, 0xcf, 0xbc,

    /* U+0059 "Y" */
    0xf7, 0xfb, 0xfd, 0xcf, 0xe7, 0xf3, 0xf1, 0xf8,
    0xf8, 0x7c, 0x3e, 0x1e, 0xf, 0x7, 0x83, 0xc0,

    /* U+005A "Z" */
    0x3f, 0xdf, 0xf7, 0xfc, 0x1e, 0xf, 0x87, 0xc1,
    0xe0, 0xf8, 0x7c, 0x1f, 0xf, 0x83, 0xfc, 0xff,
    0x3f, 0xc0,

    /* U+0061 "a" */
    0x3f, 0xcf, 0xf9, 0xff, 0xbd, 0xe7, 0xbc, 0xf7,
    0xbe, 0xf7, 0xde, 0xff, 0xdf, 0xf9, 0xfe, 0x0,

    /* U+0062 "b" */
    0x3c, 0x7, 0x80, 0xf0, 0x1e, 0x7, 0xfc, 0xf7,
    0xdf, 0xfb, 0xde, 0x7b, 0xcf, 0x79, 0xef, 0x7d,
    0xef, 0xfd, 0xff, 0x1f, 0xe0,

    /* U+0063 "c" */
    0x3f, 0xcf, 0xf9, 0xff, 0xbd, 0xe7, 0xbc, 0xf0,
    0x3e, 0xf7, 0xde, 0xff, 0xdf, 0xf1, 0xfc, 0x0,

    /* U+0064 "d" */
    0x1, 0xe0, 0x3c, 0x7, 0x80, 0xf3, 0xfe, 0xff,
    0xdf, 0xfb, 0xde, 0x7b, 0xcf, 0x7b, 0xef, 0x7d,
    0xef, 0xfd, 0xff, 0x9f, 0xe0,

    /* U+0065 "e" */
    0x3f, 0xcf, 0xf9, 0xff, 0xbd, 0xe7, 0xbc, 0xff,
    0xbf, 0xf7, 0xc0, 0xff, 0x9f, 0xf1, 0xfe, 0x0,

    /* U+0066 "f" */
    0x1f, 0x3f, 0x3e, 0x7c, 0xfe, 0xfe, 0xfe, 0x78,
    0x78, 0x78, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0,

    /* U+0067 "g" */
    0x3f, 0xcf, 0xf9, 0xff, 0xbd, 0xe7, 0xbc, 0xf7,
    0xbe, 0xf7, 0xde, 0xff, 0xdf, 0xf9, 0xfe, 0x3,
    0xcf, 0xf9, 0xff, 0x3f, 0xc0,

    /* U+0068 "h" */
    0x3c, 0x7, 0x80, 0xf0, 0x1e, 0x7, 0xfc, 0xf7,
    0xdf, 0xfb, 0xdf, 0x7b, 0xcf, 0x79, 0xef, 0x7d,
    0xef, 0xbd, 0xef, 0xbd, 0xf0,

    /* U+0069 "i" */
    0x3c, 0xf3, 0xc0, 0x7d, 0xe7, 0x9e, 0x79, 0xe7,
    0xbe, 0xfb, 0xcf, 0x0,

    /* U+006A "j" */
    0xf, 0xf, 0xf, 0x0, 0x1f, 0x1f, 0x1e, 0x1e,
    0x1e, 0x1e, 0x1e, 0x3e, 0x3e, 0x3c, 0x3c, 0x3c,
    0xfc, 0xfc, 0xf8,

    /* U+006B "k" */
    0x3c, 0x7, 0x80, 0xf0, 0x1e, 0x7, 0xde, 0xf3,
    0xde, 0xf3, 0xde, 0x7f, 0xcf, 0xf1, 0xfe, 0x7f,
    0xcf, 0xfd, 0xe7, 0xbc, 0xf0,

    /* U+006C "l" */
    0x3c, 0xf3, 0xcf, 0x7d, 0xe7, 0x9e, 0x79, 0xe7,
    0xbe, 0xfb, 0xcf, 0x0,

    /* U+006D "m" */
    0x7f, 0xde, 0x7b, 0xdf, 0x7f, 0xdf, 0x7b, 0xde,
    0x7b, 0xde, 0x7b, 0xde, 0x7b, 0xde, 0xfb, 0xde,
    0xf7, 0xde, 0xf7, 0xbe, 0xf7, 0xbe,

    /* U+006E "n" */
    0x7f, 0xcf, 0x7d, 0xff, 0xbd, 0xe7, 0xbc, 0xf7,
    0x9e, 0xf7, 0xde, 0xfb, 0xde, 0xfb, 0xdf, 0x0,

    /* U+006F "o" */
    0x3f, 0xcf, 0xf9, 0xff, 0xbd, 0xe7, 0xbc, 0xf7,
    0xbe, 0xf7, 0xde, 0xff, 0xdf, 0xf1, 0xfc, 0x0,

    /* U+0070 "p" */
    0x3f, 0xe3, 0xff, 0x3f, 0xf3, 0xde, 0x3d, 0xe3,
    0xde, 0x3d, 0xe7, 0xde, 0x7b, 0xe7, 0xbc, 0x7b,
    0xc7, 0x80, 0x78, 0x7, 0x80, 0xf8, 0x0,

    /* U+0071 "q" */
    0x3f, 0xcf, 0xf9, 0xff, 0xbd, 0xe7, 0xbc, 0xf7,
    0xbe, 0xf7, 0xde, 0xff, 0xdf, 0xf9, 0xfe, 0x3,
    0xc0, 0x78, 0xf, 0x1, 0xe0,

    /* U+0072 "r" */
    0x7f, 0xbd, 0xdf, 0xef, 0x7, 0x83, 0xc1, 0xe1,
    0xf0, 0xf8, 0x78, 0x3c, 0x0,

    /* U+0073 "s" */
    0x3f, 0xc7, 0xf9, 0xff, 0x3c, 0x7, 0xf8, 0xff,
    0x8f, 0xf0, 0x1e, 0xff, 0xdf, 0xf1, 0xfc, 0x0,

    /* U+0074 "t" */
    0x1c, 0x79, 0xf7, 0xff, 0xff, 0xde, 0x3c, 0x79,
    0xf3, 0xe7, 0xef, 0xcf, 0x80,

    /* U+0075 "u" */
    0x7d, 0xef, 0x7d, 0xef, 0xbd, 0xe7, 0xbc, 0xf7,
    0xbe, 0xf7, 0xde, 0xfb, 0xdf, 0xf9, 0xfe, 0x0,

    /* U+0076 "v" */
    0xf7, 0xfb, 0xfd, 0xfe, 0xff, 0x77, 0xfb, 0xfd,
    0xfe, 0xfe, 0x7f, 0x3f, 0x80,

    /* U+0077 "w" */
    0xf7, 0xdf, 0xef, 0xbf, 0xdf, 0x77, 0xbe, 0xef,
    0xff, 0xdf, 0xff, 0xbf, 0x7e, 0x7e, 0xfc, 0xfd,
    0xf9, 0xfb, 0xf3, 0xf7, 0xc0,

    /* U+0078 "x" */
    0x7d, 0xef, 0xf9, 0xff, 0x1f, 0xc3, 0xf8, 0x7f,
    0x1f, 0xe3, 0xfc, 0x77, 0x9e, 0xf3, 0xde, 0x0,

    /* U+0079 "y" */
    0x7b, 0xde, 0xf7, 0xbd, 0xee, 0x7b, 0x9f, 0xe7,
    0xf9, 0xfc, 0x7f, 0x1f, 0xc7, 0xf0, 0x38, 0x7e,
    0x3f, 0x8f, 0xc0,

    /* U+007A "z" */
    0x7f, 0xbf, 0xdf, 0xe3, 0xf1, 0xf1, 0xf1, 0xf1,
    0xf0, 0xff, 0x7f, 0xbf, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 184, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 96, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 186, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 182, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 197, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 183, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 185, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 159, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 180, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 185, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 173, .box_w = 11, .box_h = 14, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 181, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 179, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 182, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 142, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 135, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 181, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 185, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 96, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 180, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 146, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 248, .box_w = 16, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 203, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 184, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 182, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 184, .box_w = 12, .box_h = 18, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 525, .adv_w = 179, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 178, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 163, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 182, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 168, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 258, .box_w = 16, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 172, .box_w = 12, .box_h = 14, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 151, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 147, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 706, .adv_w = 173, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 173, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 172, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 174, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 172, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 126, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 172, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 832, .adv_w = 174, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 90, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 865, .adv_w = 91, .box_w = 8, .box_h = 19, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 884, .adv_w = 174, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 905, .adv_w = 90, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 254, .box_w = 16, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 939, .adv_w = 174, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 955, .adv_w = 172, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 971, .adv_w = 173, .box_w = 12, .box_h = 15, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 994, .adv_w = 173, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1015, .adv_w = 139, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1028, .adv_w = 173, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1057, .adv_w = 174, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1073, .adv_w = 156, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1086, .adv_w = 241, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1107, .adv_w = 164, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1123, .adv_w = 157, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1142, .adv_w = 143, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 9, .glyph_id_start = 11,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 75, .range_length = 16, .glyph_id_start = 20,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 97, .range_length = 26, .glyph_id_start = 36,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    1, 31,
    1, 32,
    1, 33,
    1, 34,
    3, 4,
    3, 5,
    5, 8,
    5, 29,
    5, 31,
    5, 32,
    8, 5,
    8, 11,
    10, 31,
    10, 32,
    10, 33,
    10, 34,
    11, 29,
    11, 30,
    11, 31,
    11, 32,
    11, 33,
    11, 34,
    11, 41,
    11, 55,
    11, 57,
    11, 58,
    11, 60,
    12, 31,
    12, 32,
    12, 33,
    12, 34,
    13, 31,
    13, 32,
    13, 33,
    13, 34,
    14, 31,
    14, 32,
    14, 33,
    14, 34,
    16, 11,
    17, 34,
    20, 13,
    20, 17,
    20, 24,
    20, 26,
    20, 28,
    20, 36,
    20, 38,
    20, 39,
    20, 40,
    20, 42,
    20, 50,
    20, 52,
    20, 54,
    20, 56,
    20, 57,
    20, 58,
    20, 60,
    21, 8,
    21, 29,
    21, 31,
    21, 32,
    21, 34,
    21, 41,
    21, 55,
    21, 57,
    21, 58,
    21, 60,
    24, 31,
    24, 32,
    24, 33,
    24, 34,
    25, 11,
    25, 33,
    26, 11,
    26, 31,
    26, 32,
    26, 33,
    26, 34,
    27, 34,
    28, 31,
    28, 32,
    28, 33,
    28, 34,
    28, 41,
    28, 55,
    29, 5,
    29, 11,
    29, 36,
    29, 38,
    29, 39,
    29, 40,
    29, 42,
    29, 48,
    29, 49,
    29, 50,
    29, 51,
    29, 52,
    29, 53,
    29, 54,
    29, 56,
    29, 57,
    29, 58,
    29, 59,
    29, 60,
    29, 61,
    30, 11,
    31, 1,
    31, 5,
    31, 10,
    31, 11,
    31, 13,
    31, 17,
    31, 24,
    31, 26,
    31, 28,
    31, 35,
    31, 36,
    31, 38,
    31, 39,
    31, 40,
    31, 42,
    31, 48,
    31, 49,
    31, 50,
    31, 51,
    31, 52,
    31, 53,
    31, 54,
    31, 56,
    31, 61,
    32, 1,
    32, 5,
    32, 10,
    32, 11,
    32, 13,
    32, 17,
    32, 24,
    32, 26,
    32, 28,
    32, 36,
    32, 38,
    32, 39,
    32, 40,
    32, 42,
    32, 48,
    32, 49,
    32, 50,
    32, 51,
    32, 52,
    32, 53,
    32, 54,
    32, 56,
    32, 61,
    33, 1,
    33, 5,
    33, 10,
    33, 11,
    33, 13,
    33, 17,
    33, 24,
    33, 26,
    33, 28,
    33, 36,
    33, 38,
    33, 39,
    33, 40,
    33, 42,
    33, 50,
    33, 52,
    33, 54,
    33, 56,
    33, 57,
    33, 58,
    33, 60,
    34, 1,
    34, 10,
    34, 11,
    34, 13,
    34, 17,
    34, 24,
    34, 26,
    34, 28,
    34, 36,
    34, 38,
    34, 39,
    34, 40,
    34, 41,
    34, 42,
    34, 48,
    34, 49,
    34, 50,
    34, 51,
    34, 52,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 57,
    34, 58,
    34, 59,
    34, 60,
    34, 61,
    35, 36,
    35, 38,
    35, 39,
    35, 40,
    35, 42,
    35, 50,
    35, 52,
    35, 54,
    35, 56,
    36, 29,
    37, 29,
    37, 31,
    37, 32,
    37, 33,
    37, 34,
    37, 59,
    37, 60,
    38, 29,
    38, 31,
    38, 32,
    38, 33,
    38, 34,
    38, 59,
    40, 29,
    40, 32,
    40, 33,
    40, 34,
    40, 59,
    40, 61,
    42, 29,
    42, 31,
    42, 32,
    42, 34,
    43, 29,
    43, 31,
    43, 32,
    43, 34,
    46, 29,
    46, 32,
    46, 34,
    46, 36,
    46, 38,
    46, 39,
    46, 40,
    46, 42,
    46, 50,
    46, 52,
    46, 54,
    46, 56,
    48, 29,
    48, 32,
    48, 34,
    49, 29,
    49, 32,
    49, 34,
    50, 29,
    50, 31,
    50, 32,
    50, 33,
    50, 34,
    50, 59,
    51, 29,
    51, 31,
    51, 32,
    51, 33,
    51, 34,
    51, 59,
    52, 29,
    52, 31,
    52, 32,
    52, 34,
    53, 11,
    53, 33,
    53, 34,
    54, 29,
    54, 31,
    54, 32,
    54, 33,
    54, 34,
    54, 59,
    55, 29,
    56, 29,
    56, 34,
    57, 11,
    57, 29,
    57, 34,
    58, 11,
    58, 29,
    58, 34,
    59, 29,
    59, 34,
    59, 38,
    59, 40,
    59, 42,
    59, 50,
    59, 52,
    59, 54,
    59, 56,
    60, 29,
    60, 34,
    61, 29,
    61, 34
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -3, -3, -6, -8, -6, -2, -6, -1,
    -1, -1, -3, -6, -3, -3, -6, -8,
    -16, -3, -5, -5, -4, -19, -6, -6,
    -1, -1, -1, -3, -3, -5, -6, -3,
    -3, -5, -8, -3, -3, -5, -6, -6,
    -8, -3, -3, -3, -3, -3, -5, -5,
    -5, -5, -5, -5, -5, -5, -5, -6,
    -1, -6, -6, -27, -16, -16, -38, -16,
    -16, -2, -2, -10, -3, -3, -8, -8,
    -6, -5, -4, -3, -3, -5, -8, -6,
    -3, -3, -5, -6, -3, -3, -1, -16,
    -15, -6, -6, -15, -6, -2, -2, -15,
    -2, -15, -3, -15, -3, 0, -3, 0,
    0, -3, -3, -3, -1, -3, -5, -3,
    -3, -3, -3, -3, -2, -7, -7, -7,
    -7, -7, -5, -5, -7, -5, -3, -5,
    -7, -7, -6, -3, -1, -3, -5, -3,
    -3, -3, -3, -3, -7, -3, -3, -3,
    -3, -5, -5, -7, -5, -3, -5, -7,
    -1, -2, -6, -10, -6, -4, -5, -5,
    -8, -5, -5, -6, -3, -3, -6, -3,
    -6, -3, -3, -3, -6, -10, -6, -8,
    -8, -19, -8, -8, -8, -6, -6, -21,
    -14, -21, -21, -6, -14, -10, -10, -21,
    -13, -14, -13, -14, -6, -14, -6, -6,
    -6, -3, -10, -3, -3, -3, -3, -3,
    -3, -3, -3, -3, -6, -6, -3, -3,
    -3, -14, -5, -3, -6, -3, -3, -3,
    -14, -5, -6, -3, -3, -14, -3, 0,
    -6, -3, -3, -14, -6, -3, -3, -14,
    0, -3, -6, -7, -3, -2, -3, -3,
    -7, -3, -3, -2, -6, -3, -14, -6,
    -3, -14, -6, -9, -3, -3, -14, -5,
    -6, -3, -3, -3, -14, -5, -6, -3,
    -3, -14, -6, -3, -6, -6, -9, -3,
    -3, -14, -5, -2, -6, -10, -1, 0,
    -6, -1, 0, -6, 0, -6, -5, -5,
    -2, -5, -5, -5, -1, 0, -3, 0,
    -10
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 305,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 4,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t Ramsey = {
#else
lv_font_t Ramsey = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if RAMSEY*/
