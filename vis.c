#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "corewar_vm.h"
#include "draw.h"

void	init_colors()
{
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(50, COLOR_BLACK, COLOR_YELLOW);
	init_pair(10, COLOR_BLACK, COLOR_GREEN);
	init_pair(20, COLOR_BLACK, COLOR_BLUE);
	init_pair(30, COLOR_BLACK, COLOR_RED);
	init_pair(40, COLOR_BLACK, COLOR_MAGENTA);
}

void		ft_print_in_gen(int pos, t_mstruc *inst, t_process *proc)
{
		int x;
		int y;
		int i;
		int color;
		t_players *tmp;

		i = 0;
		color = 1;
		tmp = inst->players;
		while (tmp != NULL && proc->reg[0] * (-1) != tmp->pl_num)
		{
			color++;
			tmp = tmp->next;
		}
		wattron(inst->gen_win, COLOR_PAIR(color));
		while(i < 4)
		{
			x = (get_pc((pos + i)) % 64) * 3 + 2;
			y = (get_pc(pos + i)) / 64 + 2;
			inst->col_map[get_pc(pos + i)] = color;
			mvwprintw(inst->gen_win, y, x,"%.2x", inst->memory[get_pc(pos + i++)]);
		}
		wattron(inst->gen_win, COLOR_PAIR(5));
}

void 	ft_print_corr(t_mstruc *inst, int pre, int now)
{
		int x;
		int y;
		wattron(inst->gen_win, COLOR_PAIR(inst->col_map[pre]));
		x = ((get_pc(pre)) % 64) * 3 + 2;
		y = (get_pc(pre)) / 64 + 2;
		mvwprintw(inst->gen_win, y, x,"%.2x", inst->memory[get_pc(pre)]);
		wattroff(inst->gen_win, COLOR_PAIR(inst->col_map[pre]));
		wattron(inst->gen_win, COLOR_PAIR(inst->col_map[pre] * 10));
		x = (get_pc(now)) % 64 * 3 + 2;
		y = (get_pc(now)) / 64 + 2;
		mvwprintw(inst->gen_win, y, x,"%.2x", inst->memory[get_pc(now)]);
		wattron(inst->gen_win, COLOR_PAIR(5));

}

int		ft_get_st_pair(t_mstruc *inst, t_draw *draw, int pos)
{
	t_process *proc;
	t_players *plr;
	int num;
	int c;

	proc = inst->process;
	while (proc->next != NULL)
		proc = proc->next;
	plr = inst->players;
	num = 5;
	c = 1;
	while (proc != NULL)
	{
		if (proc->pc == pos)
		{
			num = c * 10;
			break ;
		}
		if (proc->pc < pos && (proc->pc + plr->header->prog_size) > pos)
		{
			num = c;
			break ;
		}
		if ((proc->pc + plr->header->prog_size) > pos)
			num = 5;
		plr = plr->next;
		proc = proc->prev;
		c++;
	}
	wattron(inst->gen_win, COLOR_PAIR(num));
	if (num >= 10)
		return (num / 10);
	return (num);
}

void		ft_fill_gen_win(t_mstruc *inst, t_draw *draw)
{
	int x;
	int y;
	int k;
	int col;

	k = 0;
	y = 1;
//	wattron(draw->win[1], COLOR_PAIR(5)); 
	while (++y < 66)
	{ 
		x = 2;  
		while (x < 194)
		{
			col = ft_get_st_pair(inst, draw, k);
			inst->col_map[k] = col;
			mvwprintw(inst->gen_win, y, x,"%.2x", inst->memory[k++]);
			x += 3;
		}
	}
	wrefresh(inst->gen_win);
}

void		output_core(t_mstruc *inst, t_draw *draw)
{
	mvwprintw(draw->win[1], 8, 12, "%d", inst->total_cycle);    //отображает циклы в стате
	mvwprintw(draw->win[1], 10, 16, "%d", inst->total_process); //отображает процессы
 }


void show_players(t_mstruc *inst, t_draw *draw)
{
	int	h;
	int	w;
	int	i;
	t_players *tmp;

	h = 12;
	w = 5;
	i = 0;
	tmp = inst->players;
	wmove(draw->win[1], h, w);
	while (i < inst->num_of_players)
	{
		wprintw(draw->win[1],"Player -%d :",tmp->pl_num);
		wattron(draw->win[1], COLOR_PAIR(tmp->pl_num)); 
		wprintw(draw->win[1]," %s", tmp->header->prog_name);
		wattroff(draw->win[1], COLOR_PAIR(tmp->pl_num)); 
		wmove(draw->win[1], ++h, w);
		wprintw(draw->win[1],"	Last live :			%d",tmp->last_live);
		wmove(draw->win[1], ++h, w);
		wprintw(draw->win[1],"	Lives in current period : 	%d",tmp->live_flag);
		h += 2;
		wmove(draw->win[1], h, w);
		tmp	= tmp->next;
		i++;
	}
}

void create_labels(t_draw *draw) 
{
	int  h;
	int  w;

	getyx(draw->win[1], h, w);
	h += 5;
	w += 5;
	wattron(draw->win[1], COLOR_PAIR(5)); 
	wmove(draw->win[1], h, w);
	wprintw(draw->win[1],"Cycles/second limit:");
	wmove(draw->win[1], h + 3, w);
	wprintw(draw->win[1],"CYCLE: 0");
	wmove(draw->win[1], h + 5, w);
	wprintw(draw->win[1],"Processes: 0");
}

void	ft_destr_wins(t_draw *draw)
{
	delwin(draw->win[0]);
	delwin(draw->win[1]);
	endwin();
}

t_draw	*init_wind(void)
{
	t_draw *draw;

	initscr();
	cbreak();
	draw = (t_draw *)malloc(sizeof(t_draw));
	start_color();
	init_colors();
	draw->win[0] = newwin(68, 195, 0, 0);   //главное окно с памятью
	draw->win[1] = newwin(68, 70, 0, 196); //окно с статой
	// draw->win[2] = newwin(12,64, 196, 55); // liza 
	wattron(draw->win[0], COLOR_PAIR(6)); 
	wborder(draw->win[0], ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
	wattron(draw->win[1], COLOR_PAIR(6)); 
	wborder(draw->win[1], ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
	wrefresh(draw->win[0]);
	wrefresh(draw->win[1]);
	//box(draw->win[2], 0, 0);
	create_labels(draw);
	return (draw);
}
