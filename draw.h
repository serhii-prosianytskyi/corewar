#include <ncurses.h>


typedef struct	s_draw
{
	char **heart;
	char **cross;
	WINDOW *win[3];
}				t_draw;