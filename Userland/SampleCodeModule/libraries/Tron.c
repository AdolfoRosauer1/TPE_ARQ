#include <Tron.h>

static unsigned int running = 0;

static int player1[] = {0, 0, 0, 1, BLUE};
static int player2[] = {0, 0, 0, 1, ORANGE};

void drawRectangle()
{
    for (int i = OFFSETY; i < HEIGHT - OFFSETY; i++)
    {
        for (int k = OFFSETX; k < WIDTH - OFFSETX; k++)
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
        system_call(POLL_READ, KBD_IN, &c, 1, 150, 0);

        update_direction(c);

        running = !update_tron();

        // lectura de teclado
        // actualizacion de la direccion del jugador
        // update_tron lee la direccion, y le mete la magia
        // update_tron devuelve la win condition win=update_tron
    }
    while (c != ENTER)
    {
        printPos("GAME OVER", WIDTH * 3 / 8, 1 + HEIGHT * 7 / 8);
        system_call(POLL_READ, KBD_IN, &c, 1, 500, 0);
        printPos("                             ", WIDTH * 3 / 8, 1 + HEIGHT * 7 / 8);
        system_call(POLL_READ, KBD_IN, &c, 1, 250, 0); // KBD_IN es 1
    }
    clearScreen();
}

void initialize_players()
{
    for ( int i = 0; i < AREAY ; i++ )
    {
        for ( int j = 0 ; j < AREAX ; j++ )
        {
            area[i][j] = 0;
        }
    }
    player1[0] = (2 * AREAX) / 6;
    player1[1] = AREAY / 2;

    player2[0] = (4 * AREAX) / 6;
    player2[1] = AREAY / 2;

    area[player1[1]][player1[0]] = 1;
    draw_bike(player1[0], player1[1], player1[4]);
}

void draw_bike(int x, int y, int color) // cordenadas respecto al area de juego
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            drawPixel(OFFSETY + 6 * y + i, OFFSETX + 6 * x + j, color);
        }
    }
}

int update_tron()
{
    player1[0] += player1[2];
    player1[1] -= player1[3];

    player2[0] += player2[2];
    player2[1] -= player2[3];

    if (player1[0] < 0 || player1[1] < 0 || player1[0] > AREAX || player1[1] > AREAY)
        return 1;

    if (player2[0] < 0 || player2[1] < 0 || player2[0] > AREAX || player2[1] > AREAY)
        return 1;

    if (wall_hit())
        return 1;

    draw_wall(player1[0], player1[1], player1[4]);
    draw_wall(player2[0], player2[1], player2[4]);

    return 0;
}

int wall_hit()
{
    if (area[player1[1]][player1[0]] == 1 || area[player2[1]][player2[0]] == 1)
        return 1;
    return 0;
}

void draw_wall(int x, int y, int color)
{
    area[y][x] = 1;
    draw_bike(x, y, color);
}

void update_direction(int direc)
{
    switch (direc)
    {
    case W_KEY:
        if (player1[3] != -1)
        {
            if (player1[2] != 0)
                player1[2] = 0;
            player1[3] = 1;
        }
        break;

    case A_KEY:
        if (player1[2] != 1)
        {
            if (player1[3] != 0)
                player1[3] = 0;
            player1[2] = -1;
        }
        break;

    case S_KEY:
        if (player1[3] != 1)
        {
            if (player1[2] != 0)
                player1[2] = 0;
            player1[3] = -1;
        }
        break;

    case D_KEY:
        if (player1[2] != -1)
        {
            if (player1[3] != 0)
                player1[3] = 0;
            player1[2] = 1;
        }
        break;

    case UP_KEY:
        if (player2[3] != -1)
        {
            if (player2[2] != 0)
                player2[2] = 0;
            player2[3] = 1;
        }
        break;

    case LEFT_KEY:
        if (player2[2] != 1)
        {
            if (player2[3] != 0)
                player2[3] = 0;
            player2[2] = -1;
        }
        break;

    case DOWN_KEY:
        if (player2[3] != 1)
        {
            if (player2[2] != 0)
                player2[2] = 0;
            player2[3] = -1;
        }
        break;

    case RIGHT_KEY:
        if (player2[2] != -1)
        {
            if (player2[3] != 0)
                player2[3] = 0;
            player2[2] = 1;
        }
        break;

    default:
        break;
    }
}