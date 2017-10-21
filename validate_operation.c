/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_operation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 15:28:02 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/21 15:28:03 by sprosian         ###   ########.fr       */
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

void	ft_fill_opcode_mem(t_mstruc *inst)
{
	int i;
	int j;
	int ind;
	t_players *lst;

	i = -1;
	lst = inst->players;
	while (++i < inst->num_of_players)
	{
		ind = MEM_SIZE / inst->num_of_players *
			  (inst->mas_player[i].pl_num - 1);
		j = -1;
		while (++j < lst->header->prog_size)
		{
			inst->memory[ind] = lst->opcode[j];
			ind++;
		}
		lst = lst->next;
	}
}

/*void	ft_validate_opcode(t_process *process, t_mstruc *inst, int *live_flag)
{
	int flag;

	if (live_flag && (inst->live_current_per >= NBR_LIVE ||
					  *live_flag == MAX_CHECKS))
	{
		*live_flag = 0;
		if (inst->cycle_to_die > CYCLE_DELTA)
			inst->cycle_to_die -= CYCLE_DELTA;
		if (process->live_flag == 0)
			delete_process(process, inst);
	}
	else
	{
		if (process->op_cycle == -1)
		{
			process->opcode = ft_init_opcode();
			if ((flag = ft_opcode(process->pc, inst, process)) == 0)
				process->validation_flag = 1;
			process->op_cycle = op_tab[process->opcode->operation - 1].cycles -1;
			if (flag == 2)
				process->op_cycle = 1;
		}
		else if (process->op_cycle > 1)
			process->op_cycle--;
		else
		{
			if (process->validation_flag)
				ft_comands(inst, process, process->opcode);
			else
				process->pc += process->opcode->row_size;
			process->validation_flag = 0;
			process->op_cycle = -1;
			free(process->opcode);
			process->opcode = NULL;
		}
	}
}*/

void	ft_winner(t_mstruc *inst)
{
	t_players *lst;
	t_players *winner;

	lst = inst->players;
	winner = lst;
	while (lst)
	{
		if (winner->last_live <= lst->last_live)
			winner = lst;
		lst = lst->next;
	}
	ft_write_winner(winner);
	ft_del_struct(inst);
	exit(0);
}

void	ft_cycle_to_die(t_process *lst, t_mstruc *inst, int *live_flag)
{
	*live_flag += 1;
	if (inst->live_current_per >= NBR_LIVE || *live_flag == MAX_CHECKS)
	{
		*live_flag = 0;
		if (inst->cycle_to_die > CYCLE_DELTA)
			inst->cycle_to_die -= CYCLE_DELTA;
		else
			ft_winner(inst);
	}
	while (lst)
	{
		if (lst->live_flag == 0)
			delete_process(lst, inst);
		else
			lst->live_flag = 0;
		lst = lst->next;
	}

}

void	ft_validate_opcode(t_process *process, t_mstruc *inst, int flag)
{
	if (process->op_cycle == -1)
	{
		process->opcode = ft_init_opcode();
		if ((flag = ft_opcode(process->pc, inst, process)) == 0)
			process->validation_flag = 1;
		process->op_cycle = op_tab[process->opcode->operation - 1].cycles -1;
		if (flag == 2)
		{
			process->pc = (process->pc + 1) % MEM_SIZE;
			process->validation_flag = 0;
			process->op_cycle = -1;
			if (process->opcode)
				free(process->opcode);
			process->opcode = NULL;
		}
	}
	else if (process->op_cycle > 1)
		process->op_cycle--;
	else
	{
		if (process->validation_flag)
			ft_comands(inst, process, process->opcode);
		else
			process->pc += process->opcode->row_size;
		process->validation_flag = 0;
		process->op_cycle = -1;
		if (process->opcode)
			free(process->opcode);
		process->opcode = NULL;
	}

}

void	ft_core_war(t_mstruc *inst, int live_flag)
{
	t_process *lst;

	//ft_check_flags(inst);
	ft_write_contestants(inst, -1, NULL);
	while (inst->total_cycle != inst->dump_flag)
	{
		if (inst->total_cycle == 49)
 			write(1, "1", 1);
		lst = inst->process;
		if (lst == NULL)
			ft_winner(inst);
		while (lst)
		{
			ft_validate_opcode(lst, inst, 0);
			lst = lst->next;
		}
		inst->total_cycle++;
		if ((inst->total_cycle % inst->cycle_to_die) == 0)
			ft_cycle_to_die(inst->process, inst, &live_flag);
	}
}
