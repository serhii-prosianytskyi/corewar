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

void	ft_create_process(t_mstruc *inst)
{
	int i;
	t_process *process_lst;

	process_lst = ft_init_process();
	i = -1;
	while (++i < inst->num_of_players)
	{
		process_lst->reg[0] = inst->mas_player[i].pl_num * -1;
		process_lst->pc = MEM_SIZE / inst->num_of_players *
							(inst->mas_player[i].pl_num - 1);
		if ((i + 1) < inst->num_of_players)
		{
			process_lst->prev = ft_init_process();
			process_lst->prev->next = process_lst;
			process_lst = process_lst->prev;
		}
	}
	inst->process = process_lst;
}

void	ft_check_flags(t_mstruc *inst)
{

}

void	ft_validate_opcode(t_process *process, t_mstruc *inst)
{

	if (process->op_cycle == -1)
	{
		process->opcode = ft_init_opcode();
		if (ft_opcode(&(process->pc), inst->memory, process->opcode))
			process->validation_flag = 1;
		else
			process->op_cycle = op_tab[process->opcode->operation].cycles;
	}
	else if (process->op_cycle > 0)
		process->op_cycle--;
	else
	{
		ft_comands(inst, process, process->opcode);
		process->op_cycle = -1;
		free(process->opcode);
		process->opcode = NULL;
	}
}

void	ft_fill_opcode_mem(t_mstruc *inst)
{
	int i;
	int j;
	int ind;

	i = -1;
	while (++i < inst->num_of_players)
	{
		ind = MEM_SIZE / inst->num_of_players *
				(inst->mas_player[i].pl_num - 1);
		j = -1;
		while (++j < inst->mas_player[i].header->prog_size)
		{
			inst->memory[ind] = inst->mas_player[i].opcode[j];
			ind++;
		}
	}
}

void	ft_core_war(t_mstruc *inst)
{
	t_process *lst;

	ft_create_process(inst);
	//ft_check_flags(inst);
	ft_fill_opcode_mem(inst);
	while (inst->total_cycle < inst->dump_flag)
	{
		lst = inst->process;
		while (lst)
		{
			ft_validate_opcode(lst, inst);
			lst = lst->next;
		}
		if (ft_lst_len(inst->process, 2, 0) == 0)
			return ;
		inst->total_process++;
	}
}