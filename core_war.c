/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_war.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:49:42 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/16 18:49:44 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void    ft_core_war_viz(t_mstruc *inst, int live_flag)
{
	t_process *lst;
	t_draw *draw;
	unsigned int sleep;

	draw = init_wind();
	sleep = 10000;
	inst->gen_win = draw->win[0];
	ft_fill_gen_win(inst, draw);
	show_players(inst, draw);
	while (inst->total_cycle != inst->dump_flag)
	{
		output_core(inst, draw);
		wrefresh(draw->win[1]);
		lst = inst->process;
		if (lst == NULL)
		{
			ft_destr_wins(draw);
			return ;
			ft_winner(inst);
		}
		while (lst)
		{
			ft_validate_opcode(lst, inst, 0);
			sleep = ft_key_processing(draw, sleep);
			lst = lst->next;
			wrefresh(draw->win[0]);
		}
		inst->total_cycle++;
		if ((inst->total_cycle % inst->cycle_to_die) == 0)
			ft_cycle_to_die(inst->process, inst, &live_flag);
		usleep(sleep);
	}
	wgetch(draw->win[0]);
}

void	ft_choose_one(t_mstruc *inst)
{
	int 		live_flag;

	ft_create_process(inst);
	ft_fill_opcode_mem(inst);
	inst->total_process = inst->num_of_players;
	live_flag = 0;
	if (inst->bonus_flag)
		ft_core_war_viz(inst, live_flag);
	else
		ft_core_war(inst, live_flag);
}