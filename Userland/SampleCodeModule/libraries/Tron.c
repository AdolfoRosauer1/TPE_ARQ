#include <Tron.h>

static unsigned int running = 0;

static int player1[] = {(2*AREAX)/6,AREAY/2, 0, 1, BLUE};
static int player2[] = {(4*AREAX)/6, AREAY/2, 0, 1, ORANGE};

void drawRectangle()
{
    for (int i = OFFSETY; i < HEIGHT-OFFSETY; i++)
    {
        for (int k = OFFSETX; k < WIDTH-OFFSETX ; k++)
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
    initialize_players();
    running = 1;
    while (running)
    {
        system_call(POLL_READ, KBD_IN, &c, 1, 250, 0);
        
        //lectura de teclado
        //actualizacion de la direccion del jugador
        //update_tron lee la direccion, y le mete la magia
        //update_tron devuelve la win condition win=update_tron
    }
    clearScreen();
}

void initialize_players()
{
    area[player1[1]][player1[0]] = 1;
    draw_bike(player1[0],player1[1],player1[4]);

}

void draw_bike( int x, int y, int color) // cordenadas respecto al area de juego
{   
    for ( int i = 0 ; i < 6 ; i++ )
    {
        for (int j = 0; j < 6; j++)
        {
            drawPixel(OFFSETY+6*y+i,OFFSETX+6*x+j,color);
        }
        
    }
}

int update_tron()
{
    // do nothing
}