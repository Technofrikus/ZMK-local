/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --no-compress --stride 1 --align 1 --font RamseyTest-BlackCondensedItalic-BF64069d9ad0c68.ttf --symbols BAT1234567890% --format lvgl -o Ramsey.c
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

    /* U+0054 "T" */
    0xff, 0xff, 0xff, 0xfc, 0x78, 0x3e, 0xf, 0x83,
    0xe0, 0xf0, 0x3c, 0xf, 0x3, 0xc1, 0xf0, 0x7c,
    0x1f, 0x0
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
    {.bitmap_index = 239, .adv_w = 163, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1, 0x13
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 20, .glyph_id_start = 11,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 4,
    3, 5,
    5, 8,
    5, 13,
    8, 5,
    8, 11,
    11, 13,
    13, 5,
    13, 11
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -6, -2, -6, -1, -3, -6, -16, -1,
    -16
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 9,
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
    .cmap_num = 2,
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
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if RAMSEY*/
