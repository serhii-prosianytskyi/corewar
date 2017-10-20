#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "corewar_vm.h"
#include "draw.h"

void output_core(t_draw *draw, unsigned char *memory, int i)
{
	int x;
	int y;
	int k;

	k = 0;
	y = 2;
	wattron(draw->win[0], COLOR_PAIR(5)); 
	for (int j = 0; j < 64; j++)
	{ 
		x = 2;  
		for (int i = 0; i < 64; i++)
		{
			mvwprintw(draw->win[0],y, x,"%.2x", memory[k]);
			k++;
			x += 3;
		}
		y++;
	}
	mvwprintw(draw->win[1],8, 12,"%.d", i);
 // usleep(100);
 }

void create_labels(t_draw *draw) 
{
	int  h;
	int  w;

	getyx(draw->win[1], h, w);
	h += 5;
	w += 5;
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	wattron(draw->win[1], COLOR_PAIR(5)); 
	wmove(draw->win[1], h, w);
	wprintw(draw->win[1],"Cycles/second limit:");
	wmove(draw->win[1], h + 3, w);
	wprintw(draw->win[1],"CYCLE: 0");
	wmove(draw->win[1], h + 5, w);
	wprintw(draw->win[1],"Processes:");
}

void	ft_destr_wins(t_draw *draw)
{
	delwin(draw->win[0]);
	delwin(draw->win[1]);
	endwin();
}

void	init_colors()
{ 
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
}

void	init_wind(t_draw *draw)
{
	initscr();
	start_color();
	init_colors();
	draw->win[0] = newwin(68, 195, 0, 0);   //главное окно с памятью
	draw->win[1] = newwin(68, 70, 0, 195); //окно с статой
	// draw->win[2] = newwin(12,64, 196, 55); // liza 
	wattron(draw->win[0], COLOR_PAIR(6)); 
	wborder(draw->win[0], ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
	wattron(draw->win[1], COLOR_PAIR(6)); 
	wborder(draw->win[1], ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
	//box(draw->win[2], 0, 0);
	create_labels(draw);
}
