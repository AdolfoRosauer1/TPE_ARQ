#include <audio.h>
#include <Utils.h>
#include <system_calls.h>

#define BLUE 0x0000FF
#define ORANGE 0xFFA500
#define GREY 0x808080

#define WIDTH 1024
#define HEIGHT 768
#define AREAX ((1024*6)/8)/6
#define AREAY ((768*6)/8)/6

#define OFFSETX (WIDTH / 8)
#define OFFSETY (HEIGHT / 8)

#define ENTER 0x1C
#define ESCAPE 0x01

#define W_KEY 0x11
#define A_KEY 0x1E
#define S_KEY 0x1F
#define D_KEY 0x20

#define UP_KEY 0x48
#define DOWN_KEY 0x50
#define LEFT_KEY 0x4B
#define RIGHT_KEY 0x4D

#define I_KEY 0x17
#define J_KEY 0x24
#define K_KEY 0x25
#define L_KEY 0x26

static int area[AREAY][AREAX];

void start_tron();
int update_tron();
void drawRectangle();
void initialize_players();
void draw_bike(int x, int y, int color);
void update_direction( int direc );
int wall_hit();
void draw_wall(int x, int y, int color);
