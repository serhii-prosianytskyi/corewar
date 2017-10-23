#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "corewar_vm.h"
#include "draw.h"

void	init_colors()
{
	init_color(COLOR_YELLOW, 300, 300, 300);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);
	init_pair(50, COLOR_BLACK, COLOR_YELLOW);
	init_pair(10, COLOR_WHITE, COLOR_GREEN);
	init_pair(20, COLOR_WHITE, COLOR_BLUE);
	init_pair(30, COLOR_WHITE, COLOR_RED);
	init_pair(40, COLOR_WHITE, COLOR_MAGENTA);
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

void	show_stat(t_mstruc *inst, t_draw *draw)
{
	int			new_live;
	int			i;
	t_players	*tmp;

	tmp = inst->players;
	wmove(draw->win[1], 32, 6);
	i = -1;
	while (++i < inst->num_of_players)
	{
		if (inst->live_current_per / 36 > 0)
		{
			new_live = tmp->live_flag /(inst->live_current_per / 36);
			wattron(draw->win[1], COLOR_PAIR(tmp->pl_num * 10));
			while (new_live--)
				wprintw(draw->win[1], "|");
			wattroff(draw->win[1], COLOR_PAIR(5));
			tmp = tmp->next;
		}
	}
	//sleep(200);
}

void		output_core(t_mstruc *inst, t_draw *draw)
{
	t_players *tmp;
	int h;

	h = 13;
	tmp = inst->players;
	mvwprintw(draw->win[1], 8, 12, "%d", inst->total_cycle);    //отображает циклы в стате
	mvwprintw(draw->win[1], 10, 16, "%d", inst->total_process); //отображает процессы
	while (tmp)
	{
		mvwprintw(draw->win[1], h++, 38, "%d", tmp->last_live);
		mvwprintw(draw->win[1], h, 38, "%d", tmp->live_flag);
		h += 3;
		tmp = tmp->next;
	}
//	if (inst->live_current_per > 0)	
 		show_stat(inst, draw);
}

unsigned int ft_key_processing(t_draw *draw, unsigned int sleep)
{
	int ch;
	int rep_ch;

	wattron(draw->win[0], COLOR_PAIR(5)); 
	ch = wgetch(draw->win[0]);
	rep_ch = 0;
	while (ch == ' ' && rep_ch != ' ')
	{
		mvwprintw(draw->win[1], 3, 5, "PAUSE");
		rep_ch = wgetch(draw->win[0]);
		if (rep_ch == ' ')
			mvwprintw(draw->win[1], 3, 5, "START");	
		if (rep_ch == KEY_DOWN)
			sleep += 1000;
		if (rep_ch == KEY_UP && sleep != 0)
			sleep -= 1000;
		if (rep_ch == 'q' || rep_ch == 'Q')
			{
				ft_destr_wins(draw);
				exit(0);
			}
	}
	if (ch == KEY_DOWN)
		sleep += 1000;
	if (ch == KEY_UP && sleep != 0)
		sleep -= 1000;
	if (sleep > 1000000)
		sleep = 1000000;
	if (ch == 'q' || ch == 'Q')
		{
			ft_destr_wins(draw);
			exit(0);
		}
	return (sleep);
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
		wprintw(draw->win[1],"	Last live :			");
		wmove(draw->win[1], ++h, w);
		wprintw(draw->win[1],"	Lives in current period :");
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
	mvwprintw(draw->win[1], 3, 5, "START");
	mvwprintw(draw->win[1], h, w, "Cycles/second limit:");
	mvwprintw(draw->win[1], h + 3, w, "CYCLE: 0");
	mvwprintw(draw->win[1], h + 5, w, "Processes: 0");
	h = 30;
	mvwprintw(draw->win[1], h, w,"Live for current period :");
	mvwprintw(draw->win[1], h + 2, w, "|                                    |");
	mvwprintw(draw->win[1], h + 4, w, "Live for last period :");
	mvwprintw(draw->win[1], h + 6, w, "|                                    |");
	mvwprintw(draw->win[1], h + 8, w,  "CYCLE_TO_DIE :    %d", CYCLE_TO_DIE);
	mvwprintw(draw->win[1], h + 10, w, "CYCLE_DELTA :     %d", CYCLE_DELTA);
	mvwprintw(draw->win[1], h + 12, w, "NBR_LIVE :        %d", NBR_LIVE);
	mvwprintw(draw->win[1], h + 14, w, "MAX_CHECKS :      %d", MAX_CHECKS);
		
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
	draw = (t_draw *)malloc(sizeof(t_draw));
	start_color();
	init_colors();
	noecho();
	curs_set(0);
	draw->win[0] = newwin(68, 195, 0, 0);
	draw->win[1] = newwin(68, 70, 0, 196);
	nodelay(draw->win[0], TRUE);
	keypad(draw->win[0], TRUE);
	wattron(draw->win[0], COLOR_PAIR(6)); 
	wborder(draw->win[0], ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
	wattron(draw->win[1], COLOR_PAIR(6)); 
	wborder(draw->win[1], ' ', ' ',' ' ,' ', ' ',' ',' ',' ');
	wrefresh(draw->win[0]);
	wrefresh(draw->win[1]);
	create_labels(draw);
	return (draw);
}
