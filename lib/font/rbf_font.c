#include "stdlib.h"
#include "gui.h"
#include "font.h"
#include "../../core/gui_draw.h"
#include "../../include/conf.h"

//-------------------------------------------------------------------
#define RBF_MAX_NAME       64

//-------------------------------------------------------------------
static unsigned int RBF_HDR_MAGIC1 = 0x0DF00EE0;
static unsigned int RBF_HDR_MAGIC2 = 0x00000003;

// Header as seperate structure so it can be directly loaded from the font file easily
// structure layout maps to file layout - do not change !
typedef struct {
    int magic1, magic2;         // header magic numbers to identify correct font file
    char name[RBF_MAX_NAME];    // name of font (max 64 characters)
    int charSize;               // # of bytes used to store each character
    int points;                 // font size in points
    int height;                 // font height in pixels
    int maxWidth;               // width of widest character
    int charFirst;              // first character #
    int charLast;               // last character #
    int _unknown4;              // ?
    int _wmapAddr;              // offset in font file of wTable array
    int _cmapAddr;              // offset in font file of cTable array
    int descent;                // font descent (not used)
    int intline;                // interline spacing (not used)
} font_hdr;

typedef struct _font {
    font_hdr hdr;

    // calculated values (after font is loaded)
    int charCount;              // count of chars containing in font
    int width;                  // font element width in pixels

    // Width table
    // List of character widths. Elements of list is width of char 
    char wTable[256];

    // Character data
    // List of chars. Element of list is a bytecode string, contains pixels representation of char
    char *cTable;

    // Flag to indicate we are actually using the built in 8x16 font rather than a loaded font
    int usingFont8x16;

    // Current size of the cTable data
    int cTableSize;
    struct _font *uncached_font;      // address of font in uncached memory (for passing to ufree & read)
    char *uncached_cTable;            // address of cTable in uncached memory (for passing to ufree & read)
} font;

static font *rbf_symbol_font = 0, *rbf_font = 0;
static int rbf_codepage = FONT_CP_WIN; 

//-------------------------------------------------------------------

font *new_font() {
    // allocate font from uncached memory
    font *f = umalloc(sizeof(font));
    if (f) {
        memset(f,0,sizeof(font));      // wipe memory (use uncached address to avoid conflict with read & caching)
        f->uncached_font = f;          // save uncached memory address
        // return address in cached memory for faster font rendering
        return (font*)((int)f & ~CAM_UNCACHED_BIT);
    }

    // memory not allocated ! should probably do something else in this case ?
    return 0;
}

void init_fonts()
{
    // Allocate base font memory if needed
    if (rbf_font == 0) rbf_font = new_font();
    if (rbf_symbol_font == 0) rbf_symbol_font = new_font();
}

void alloc_cTable(font *f) {

    // Calculate additional values for font
    f->width = 8 * f->hdr.charSize / f->hdr.height;
    f->charCount = f->hdr.charLast - f->hdr.charFirst + 1;

    // set width table to default value
    memset(f->wTable, f->width, 256);
    
    // allocate cTable memory

    // If existing data has been allocated then we are re-using the font data
    // See if it the existing cTable data is large enough to hold the new font data
    // If not free it so new memory will be allocated
    if ((f->cTable != 0) && (f->cTableSize < (f->charCount*f->hdr.charSize))) {
        ufree(f->uncached_cTable);    // free the memory using the uncached address
        f->cTable = 0;                // clear pointer so new memory is allocated
        f->uncached_cTable = 0;
    }

    // Allocated memory if needed
    if (f->cTable == 0 && !f->usingFont8x16) {
        // Allocate memory from uncached pool
        f->uncached_cTable = umalloc(f->charCount*f->hdr.charSize);
        // Store cached memory address
        f->cTable = (char*)((int)f->uncached_cTable & ~CAM_UNCACHED_BIT);

        // save size
        f->cTableSize = f->charCount*f->hdr.charSize;
    }
}

//-------------------------------------------------------------------
static const char tbl_dos2win[] = {
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0x2D, 0x2D, 0x2D, 0xA6, 0x2B, 0xA6, 0xA6, 0xAC, 0xAC, 0xA6, 0xA6, 0xAC, 0x2D, 0x2D, 0x2D, 0xAC,
    0x4C, 0x2B, 0x54, 0x2B, 0x2D, 0x2B, 0xA6, 0xA6, 0x4C, 0xE3, 0xA6, 0x54, 0xA6, 0x3D, 0x2B, 0xA6,
    0xA6, 0x54, 0x54, 0x4C, 0x4C, 0x2D, 0xE3, 0x2B, 0x2B, 0x2D, 0x2D, 0x2D, 0x2D, 0xA6, 0xA6, 0x2D,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF,
    0xA8, 0xB8, 0xAA, 0xBA, 0xAF, 0xBF, 0xA1, 0xA2, 0xB0, 0x95, 0xB7, 0x76, 0xB9, 0xA4, 0xA6, 0xA0
};

int code_page_char(int ch)
{
    // convert character value based on selected code page
    if ((rbf_codepage == FONT_CP_DOS) && (ch >= 128) && (ch < 256)) {
        // Convert DOS to WIN char
        ch = tbl_dos2win[ch-128];
    }
    return ch;
}

//-------------------------------------------------------------------
// Return address of 'character' data for specified font & char
char* rbf_font_char(font* f, int ch)
{
    if (f && (ch >= f->hdr.charFirst) && (ch <= f->hdr.charLast))
    {
        return &f->cTable[(ch-f->hdr.charFirst)*f->hdr.charSize];
    }

    return 0;
}
//-------------------------------------------------------------------
// Load from from file. If maxchar != 0 limit charLast (for symbols)
// Note: pass the uncached font address to this function
int rbf_font_load(char *file, font* f, int maxchar)
{
    int i;

    // make sure the font has been allocated
    if (f == 0) return 0;

    // turn of default font if it was being used
    f->usingFont8x16 = 0;

    // open file (can't use fopen here due to potential conflict FsIoNotify crash)
    int fd = open(file, O_RDONLY, 0777);
    if (fd >= 0) {
        // read header
        i = read(fd, &f->hdr, sizeof(font_hdr));

        // check size read is correct and magic numbers are valid
        if ((i == sizeof(font_hdr)) && (f->hdr.magic1 == RBF_HDR_MAGIC1) && (f->hdr.magic2 == RBF_HDR_MAGIC2)) {

            if (maxchar != 0) {
                f->hdr.charLast = maxchar;
            }

            alloc_cTable(f);

            // read width table (using uncached memory address)
            lseek(fd, f->hdr._wmapAddr, SEEK_SET);
            read(fd, &f->wTable[f->hdr.charFirst], f->charCount);

            // read cTable data (using uncached memory address)
            lseek(fd, f->hdr._cmapAddr, SEEK_SET);
            read(fd, f->uncached_cTable, f->charCount*f->hdr.charSize);

            close(fd);

            // Reset symbol display if symbol font too tall
            if (conf.menu_symbol_enable && rbf_font && rbf_symbol_font)
                conf.menu_symbol_enable=(rbf_font->hdr.height>=rbf_symbol_font->hdr.height);

            return 1;
        }
    }

    return 0;
}
//-------------------------------------------------------------------
int rbf_load(char *file) {
    // Allocate font if needed
    init_fonts();
    // Load font
    return rbf_font_load(file, rbf_font->uncached_font, 0);
}

//-------------------------------------------------------------------
#define maxSymbols 128
int rbf_load_symbol(char *file) {
    // Allocate font if needed
    init_fonts();
    // Load font
    return rbf_font_load(file, rbf_symbol_font->uncached_font, maxSymbols+32);
}

//-------------------------------------------------------------------
void rbf_load_from_8x16(unsigned char font[256][16]) {

    // Allocate font if needed
    init_fonts();

    rbf_font->hdr.charSize  = 16;
    rbf_font->hdr.height    = 16;
    rbf_font->hdr.maxWidth  = 8;
    rbf_font->hdr.charFirst = 0;
    rbf_font->hdr.charLast  = 255;

    // This is only ever called to copy the 'current_font' data into the rbf_font
    // Instead of doing this set the rbf_font flag so we call 'draw_char' directly (which uses current_font)
    // This avoids allocating memory for a copy of something we already have
    rbf_font->usingFont8x16 = 1;

    alloc_cTable(rbf_font);
}

//-------------------------------------------------------------------
void rbf_set_codepage(int codepage) {
    rbf_codepage = codepage;
}

//-------------------------------------------------------------------
int rbf_font_height() {
    return rbf_font->hdr.height;
}
//-------------------------------------------------------------------
int rbf_symbol_height() {
    return rbf_symbol_font->hdr.height;
}

//-------------------------------------------------------------------
int rbf_char_width(int ch) {
    return rbf_font->wTable[code_page_char(ch)];
}

//-------------------------------------------------------------------
int rbf_symbol_width(int ch) {
    return rbf_symbol_font->wTable[ch];
}

//-------------------------------------------------------------------
int rbf_str_width(const char *str) {
    int l=0;

    // Calculate how long the string is in pixels
    while (*str)
        l+=rbf_char_width(*str++);

    return l;
}

int rbf_str_clipped_width(const char *str, int l, int maxlen) {
    // Calculate how long the string is in pixels (possibly clipped to 'maxlen')
    while (*str && l+rbf_char_width(*str)<=maxlen)
        l+=rbf_char_width(*str++);

    return l;
}

//-------------------------------------------------------------------
void font_draw_char(int x, int y, char *cdata, int width, int height, int pixel_width, color cl) {
    int xx, yy;

    // draw pixels for font character
    if (cdata)
        for (yy=0; yy<height; ++yy)
            for (xx=0; xx<pixel_width; ++xx)
                draw_pixel(x+xx ,y+yy, (cdata[yy*width/8+xx/8] & (1<<(xx%8)))? cl&0xff : cl>>8);
}

//-------------------------------------------------------------------
int rbf_draw_char(int x, int y, int ch, color cl) {
    // Convert char for code page
    ch = code_page_char(ch);

    // Get char data pointer
    char* cdata = rbf_font_char(rbf_font, ch);

    // Draw font character (either loaded font, or from default font)
    if (rbf_font->usingFont8x16 || !cdata)
        draw_char(x,y,ch,cl);
    else
        font_draw_char(x, y, cdata, rbf_font->width, rbf_font->hdr.height, rbf_font->wTable[ch], cl);

    return rbf_font->wTable[ch];
}

//-------------------------------------------------------------------
int rbf_draw_symbol(int x, int y, int ch, color cl) {
    int space=0, pixel_width, sym_height, txt_height;

    // Skip if symbol font height taller than text font height (or invalid char value)
    if (rbf_font->hdr.height<rbf_symbol_font->hdr.height || ch==0x0) return 0;

    // get width of symbol in pixels
    pixel_width = rbf_symbol_width(ch);
    // get height of symbol font
    sym_height = rbf_symbol_font->hdr.height;
    // get height of text font
    txt_height = rbf_font->hdr.height;

    // Get char data pointer
    char* cdata = rbf_font_char(rbf_symbol_font, ch);

    if (cdata) {
      // if symbol font shorter than text font center symbol vertically and fill empty space above
      if (txt_height > sym_height) {
        space = (txt_height - sym_height)/2;
        draw_filled_rect(x, y, x+pixel_width, y+space, MAKE_COLOR(cl>>8, cl>>8));
        y+=space;
      }

      // Draw font character
      font_draw_char(x, y, cdata, rbf_symbol_font->width, sym_height, pixel_width, cl);

      // Fill space below symbol if shorter than text font
      if (txt_height > sym_height)
          draw_filled_rect(x, y+sym_height, x+pixel_width, y-space+txt_height-1, MAKE_COLOR(cl>>8, cl>>8));
    }

    return pixel_width;
}

//-------------------------------------------------------------------
// Draw a string colored 'c1' with the character at string-position 'c' colored 'c2'.
int rbf_draw_string_c(int x, int y, const char *str, color c1, int c, color c2) {
     int l=0, i=0;

     while (*str) {
          l+=rbf_draw_char(x+l, y, *str++, (i==c)?c2:c1);
          ++i;
     }
     return l;
}

//-------------------------------------------------------------------
int rbf_draw_string(int x, int y, const char *str, color cl) {
    return rbf_draw_string_c(x, y, str, cl, -1, 0);
}

//-------------------------------------------------------------------
int rbf_draw_clipped_string(int x, int y, const char *str, color cl, int l, int maxlen) {
    // Draw chars from string up to max pixel length
    while (*str && l+rbf_char_width(*str)<=maxlen)
        l+=rbf_draw_char(x+l, y, *str++, cl);
    return l;
}

//-------------------------------------------------------------------
int rbf_draw_string_len(int x, int y, int len, const char *str, color cl) {
    // Draw string characters
    int l = rbf_draw_clipped_string(x, y, str, cl, 0, len);

    // Fill any remaining space on right with background color
    if (l < len)
        draw_filled_rect(x+l, y, x+len-1, y+rbf_font->hdr.height-1, MAKE_COLOR(cl>>8, cl>>8));

    return len;
}

//-------------------------------------------------------------------
int rbf_draw_string_right_len(int x, int y, int len, const char *str, color cl) {
    // Calulate amount of padding needed on the left
    int l = len - rbf_str_clipped_width(str, 0, len);

    // Fill padding with background color
    if (l > 0)
        draw_filled_rect(x, y, x+l-1, y+rbf_font->hdr.height-1, MAKE_COLOR(cl>>8, cl>>8));

    // Draw chars
    l = rbf_draw_clipped_string(x, y, str, cl, l, len);

    return l;
}

//-------------------------------------------------------------------
int rbf_draw_string_center_len(int x, int y, int len, char symbol, const char *str, color cl) { 
    int l=0, strLen=0, i;
    const char *s=str; 

    // If symbol to be added to string determing the width of the symbol + space
    if (symbol!=0x0 && conf.menu_symbol_enable && rbf_font_height()>=rbf_symbol_height()) {
        l += rbf_symbol_width(symbol);
        l += rbf_char_width(' ');
    }

    // Add the length of the string (possibly clipped to fit)
    l = rbf_str_clipped_width(str, l, len);

    // Calculate padding required on left and right side
    l = (len-l)/2; 

    int right = x+len-1, bottom = y+rbf_font_height()-1;

    // Fill left & right sides of string area with a rectangle that has rounded top corners
    for (i=0; i<=l && i<3; i++) {
        if (i < 2) {
            // First and second columns make rounded top corners
            draw_line(x+i,     y+2-i, x+i,     bottom, MAKE_COLOR(cl>>8, cl>>8));        // left side
            draw_line(right-i, y+2-i, right-i, bottom, MAKE_COLOR(cl>>8, cl>>8));        // right side
        }
        else {
            // Rest of empty space is just filled with rectangles
            draw_filled_rect(x+i,     y, x+l-1,    bottom, MAKE_COLOR(cl>>8, cl>>8));    // left side
            draw_filled_rect(right-l, y, right-i,  bottom, MAKE_COLOR(cl>>8, cl>>8));    // right side
        }
    }

    // Draw symbol and space if required
    if (symbol!=0x0 && conf.menu_symbol_enable && rbf_font_height()>=rbf_symbol_height()) {
      l += rbf_draw_symbol(x+l, y, symbol, cl);
      l += rbf_draw_char(x+l, y, ' ', cl);
    }

    // Draw chars
    l = rbf_draw_clipped_string(x, y, str, cl, l, len);

    return l;
} 

//-------------------------------------------------------------------
