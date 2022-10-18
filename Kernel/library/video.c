#include <video.h>
#include <stdint.h>
#include <fonts.h>
#include <lib.h>



//codigo basado de https://wiki.osdev.org/User:Omarrx024/VESA_Tutorial
struct vbe_mode_info_structure{
    uint16_t attributes;    // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
    uint8_t window_a;       // deprecated
    uint8_t window_b;       // deprecated
    uint16_t granularity;   // deprecated; used while calculating bank numbers
    uint16_t window_size;
    uint16_t segment_a;
    uint16_t segment_b;
    uint32_t win_func_ptr;  // deprecated; used to switch banks from protected mode without returning to real mode
    uint16_t pitch;         // number of bytes per horizontal line
    uint16_t width;         // width in pixels
    uint16_t height;        // height in pixels
    uint8_t w_char;         // unused...
    uint8_t y_char;         // ...
    uint8_t planes;
    uint8_t bpp;   // bits per pixel in this mode
    uint8_t banks; // deprecated; total number of banks in this mode
    uint8_t memory_model;
    uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
    uint8_t image_pages;
    uint8_t reserved0;

    uint8_t red_mask;
    uint8_t red_position;
    uint8_t green_mask;
    uint8_t green_position;
    uint8_t blue_mask;
    uint8_t blue_position;
    uint8_t reserved_mask;
    uint8_t reserved_position;
    uint8_t direcint_attributes;

    uint32_t framebuffer; // write here to draw to the screen
    uint32_t off_screen_mem_off;
    uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
    uint8_t reserved1[206];
} __attribute__((packed));

static struct vbe_mode_info_structure * screenData = (void*) 0x5C00;

static int currentX = 0;
static int currentY = 0;
unsigned int rows=0;

void drawPixel(int y, int x, int color) {
  char *positionInFrameBuffer = (char *) (uint64_t) screenData->framebuffer + 3 * (y * screenData->width + x);

  int blue = color & 0xFF;
  int green = (color >> 8) & 0xFF;
  int red = (color >> 16) & 0xFF;

  *positionInFrameBuffer = blue;
  positionInFrameBuffer++;
  *positionInFrameBuffer = green;
  positionInFrameBuffer++;
  *positionInFrameBuffer = red;
}

void drawChar(char c,int x, int y, int font_color, int background_color){
  char * charMap = getCharMap(c);

	if(x+(2*CHAR_WIDTH) >= screenData->width){ // si llega al final de la linea
      currentY+=CHAR_HEIGHT/2;
      rows++;
      newLine();
      currentX+=CHAR_WIDTH*2;
  }
  if(c=='\n'){ // si es un enter
			currentY+=CHAR_HEIGHT/2;
      rows=0;
      newLine();
			currentX-=CHAR_WIDTH;
      return ;
  }
  if(c=='\b' && x>=3*CHAR_WIDTH){ // si es un back space
      deleteChar();
      return ;
  }

	for (int i = 0; i < CHAR_HEIGHT; i++) {
       for (int j = 0; j < CHAR_WIDTH; j++) {
           unsigned int point = ((charMap[i] >> j) & 0x01);
           if (point == 0) {
               drawPixel(y+i, x + CHAR_WIDTH - j, background_color);
           } else {
               drawPixel(y+i, x + CHAR_WIDTH - j, font_color);
           }
       }
   }

}

void drawString(char * s, int font_color, int background_color){
  for (int i = 0; s[i]!=0; i++) {
    drawChar(s[i],currentX,currentY,font_color,background_color);
		if(s[i]!='\b')
    	currentX+=CHAR_WIDTH;
  }
}

void newLine(){
    if(HEIGHT-currentY <=CHAR_HEIGHT){
            currentY -=CHAR_HEIGHT/2;
            scrollDown();
        }else{
            currentY+=CHAR_HEIGHT/2;
        }
    currentX=0;
}

void clearScreen(){
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            drawPixel(i ,j,DEFAULT_BG_COLOR);
        }
    }
    currentX = 0;
    currentY = 0;
}

void deleteChar(){
    if(currentX<=3*CHAR_WIDTH && rows==0){
      return;
    }
    if(currentX==0){
        if(currentY==0 ){
            return;
        }
    currentY-=CHAR_HEIGHT;
    rows--;
       currentX=WIDTH-(2*CHAR_WIDTH);
    }
    currentX-=CHAR_WIDTH;
    drawChar(' ',currentX,currentY,DEFAULT_BG_COLOR,DEFAULT_BG_COLOR);
}

void scrollDown(){
    // codigo basado de basado en: https://forum.osdev.org/viewtopic.php?f=1&t=22702
    unsigned long x=0;
    unsigned long long *vidmem = (unsigned long long*)screenData->framebuffer;

    while(x<=HEIGHT*WIDTH/2) //1024*768/2== HEIGHT * WIDTH /2
    {
    vidmem[x]=vidmem[x+(CHAR_HEIGHT*screenData->width/8)*3];    /* Valid only for 1024x768x32bpp */
    x=x+1;
    }
}