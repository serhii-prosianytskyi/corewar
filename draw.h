#ifndef DRAW_H
#include "corewar_vm.h"
#include <ncurses.h>
#define DRAW_H


typedef struct	s_draw
{
	char **heart;
	char **cross;
	WINDOW *win[3];
}				t_draw;

t_draw	*init_wind(void);
void	ft_destr_wins(t_draw *draw);

#endif