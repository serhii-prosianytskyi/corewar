#ifndef DRAW_H
#include <ncurses.h>
#define DRAW_H



typedef struct	s_draw
{
	char **heart;
	char **cross;
	WINDOW *win[3];
}				t_draw;

void	init_wind(t_draw *draw);
void	ft_destr_wins(t_draw *draw);
void	output_core(t_draw *draw, unsigned char *memory, int i);
#endif