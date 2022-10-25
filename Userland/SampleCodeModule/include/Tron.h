#include <Utils.h>
#include <system_calls.h>

#define BLUE 0x0000FF
#define ORANGE 0xFFA500
#define GREY 0x808080

#define WIDTH 1024
#define HEIGHT 768

#define ENTER 0x1C

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Player {
    Point point;
    int color;
    Point direction;
} Player;

void start_tron();
void update_tron();
void drawRectangle();