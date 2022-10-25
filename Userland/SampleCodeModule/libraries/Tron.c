#include <Tron.h>

static unsigned int running = 0;

static int player1[] = {35,35,0,1,BLUE};
static int player2[] = {55,55,0,1,ORANGE};


void drawRectangle()
{
    for (int i = HEIGHT/8; i < HEIGHT*7/8; i++)
    {
        for (int k = WIDTH/8; k < WIDTH*7/8; k++)
        {
            drawPixel(i, k, GREY);
        }
    }
}

void start_tron()
{
    changeFontSize(SMALL);
    clearScreen();
    drawRectangle();
    int c = 0;
    while (c != ENTER)
    {
        printPos("WELCOME. PRESS ENTER TO START", WIDTH * 3 / 8, 1 + HEIGHT * 7 / 8);
        system_call(POLL_READ, KBD_IN, &c, 1, 500, 0);
        printPos("                             ", WIDTH * 3 / 8, 1 + HEIGHT * 7 / 8);
        system_call(POLL_READ, KBD_IN, &c, 1, 250, 0); // KBD_IN es 1
    }
    printPos("                             ", WIDTH * 3 / 8, 1 + HEIGHT * 7 / 8);
    running = 1;
    while (running)
    {
        /* code */
    }
    clearScreen();
}

void update_tron()
{
    // do nothing
}