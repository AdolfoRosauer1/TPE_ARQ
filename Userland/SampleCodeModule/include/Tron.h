#include <Utils.h>
#include <system_calls.h>

#define BLUE 0x0000FF
#define ORANGE 0xFFA500
#define GREY 0x808080

#define WIDTH 1024
#define HEIGHT 768
#define AREA 48

#define ENTER 0x1C

static int area[AREA][2*AREA] = {0};

void start_tron();
void update_tron();
void drawRectangle();