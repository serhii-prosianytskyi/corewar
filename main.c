#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#define MEM_SIZE				(4*1024)
#include "draw.h"
#define LIVE_X          196
#define LIVE_Y          55

void create_images(t_draw *v)
{
  v->cross = (char **)malloc(sizeof(char *) * 7);
  v->heart = (char **)malloc(sizeof(char *) * 7);
  v->heart[0] = strdup("  .00.  .00.  ");
  v->heart[1] = strdup(" .0000000000. ");
  v->heart[2] = strdup("  .00000000.  ");
  v->heart[3] = strdup("   .000000.   ");
  v->heart[4] = strdup("     .00.     ");
  v->heart[5] = strdup("      ''      ");
  v->heart[6] = NULL;
  v->cross[0] = strdup("  000.   .000 ");
  v->cross[1] = strdup("  .000. .000. ");
  v->cross[2] = strdup("    .00000.   ");
  v->cross[3] = strdup("    .00000.   ");
  v->cross[4] = strdup("  .000. .000. ");
  v->cross[5] = strdup("  000.   .000 ");
  v->cross[6] = NULL;
}

void  players_status(WINDOW **win, WINDOW **win1, t_draw *v)
{
  int x;
  int y;
  int i;
  int j;
  int h;
  int w;

  i = 0;
  init_pair(5, COLOR_RED, COLOR_BLACK);
  wattron(*win, COLOR_PAIR(5)); 
  x = 0;
  y = 0;
  getyx(*win, h, w);
  while(i < 6)
  {
      j = 0;
      x = 0;
      while (j < 4) //кол-во игроков
      {
          wmove(*win, h + y + 2, w + x + 2);
          wprintw(*win,"%s", v->heart[i]);
          x += 14; 
          j++;
      }  
      y++; 
      i++;
  }
}





void create_main_window(t_draw *draw)
{
    char **temp;

    draw->win[0] = newwin(68, 193, 0, 0);  //главное окно с памятью
    draw->win[1] = newwin(68, 70, 0, 193); //окно с статой
    draw->win[2] = newwin(12,64, LIVE_Y, LIVE_X);
    start_color();
	  init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, 42, COLOR_BLACK);
   	wattron(draw->win[0], COLOR_PAIR(1)); 
   	wborder(draw->win[0], ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
    wattron(draw->win[1], COLOR_PAIR(1)); 
    wborder(draw->win[1], ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
    box(draw->win[2], 0, 0);
     int x = 2;
    int y = 2;
    wattron(draw->win[0], COLOR_PAIR(2)); 
    for(int j = 0; j < 64; j++)
	{  
   		x = 2;
   		for (int i = 0; i < 64; i++)
   		{
   			if (x < 191)
   				mvwprintw(draw->win[0],y, x,"%x", 255);
   			x += 3;
   		}
   		y++;

   	}

  players_status(&draw->win[2],&draw->win[1], draw);
  wrefresh(draw->win[0]);
	wrefresh(draw->win[1]);
  wrefresh(draw->win[2]);

}






int main()
{
  t_draw *draw;

  draw = (t_draw *)malloc(sizeof(draw));
	create_images(draw);
  initscr();
	create_main_window(draw);
	while(1)
	{

	}
	endwin();
}