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

	draw = (t_draw *)malloc(sizeof(draw));
	init_wind(draw);
	inst->gen_win = draw->win[0];
	ft_fill_gen_win(inst, draw);
	show_players(inst, draw);
	while (inst->total_cycle != inst->dump_flag)
	{
		output_core(inst, draw);
		wrefresh(draw->win[0]);
		wrefresh(draw->win[1]);
		lst = inst->process;
		if (lst == NULL)
		{

			ft_destr_wins(draw);
			return ;
		}
		while (lst)
		{
			ft_validate_opcode(lst, inst, &live_flag);
			lst = lst->next;
		}
		inst->total_cycle++;
		if ((inst->total_cycle % inst->cycle_to_die) == 0)
			live_flag++;
		usleep(10000);
	}
}

void	ft_choose_one(t_mstruc *inst)
{
	int 		live_flag;

	ft_create_process(inst);
	ft_fill_opcode_mem(inst);
	live_flag = 0;
	if (inst->bonus_flag)
		ft_core_war_viz(inst, live_flag);
	else
		ft_core_war(inst, live_flag);
}