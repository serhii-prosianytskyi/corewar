/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:27:12 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/12 13:27:13 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"


header_t	*ft_init_header(void)
{
	header_t *header;

	header = (header_t *)malloc(sizeof(header_t));
	header->magic = 0;
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	header->prog_size = 0;
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	return (header);
}

void	ft_init_opcode(t_opcode *op_lst)
{
	op_lst->row_size = 0;
	op_lst->operation = -1;
	op_lst->cod_byte = 0;
	op_lst->num_param = 0;
	op_lst->param[0] = 0;
	op_lst->param[1] = 0;
	op_lst->param[2] = 0;
	op_lst->param_size[0] = 0;
	op_lst->param_size[1] = 0;
	op_lst->param_size[2] = 0;
	op_lst->type_param[0] = 0;
	op_lst->type_param[1] = 0;
	op_lst->type_param[2] = 0;
}

t_process *ft_init_process(void)
{
	t_process	*process;
	int 		i;

	process = (t_process *)malloc(sizeof(t_process));
	process->validation_flag = 0;
	process->operation = 0;
	i = -1;
	while (++i < REG_NUMBER)
		process->reg[i] = 0;
	process->pc = 0;
	process->carry = 0;
	process->live_flag = 0;
	process->prev = NULL;
	process->next = NULL;
	return (process);
}

t_players *ft_init_players(void)
{
	t_players *player;

	player = (t_players *)malloc(sizeof(t_players));
	player->header = ft_init_header();
	player->opcode = NULL;
	player->pl_num = 0;
	player->live_flag = 0;
	player->last_live = 0;
	player->next = NULL;
	return (player);
}

t_mstruc *ft_init_mstruct(void)
{
	t_mstruc *inst;

	inst = (t_mstruc *)malloc(sizeof(t_mstruc));
	inst->bonus_flag = 0;
	inst->dump_flag = -1;
	ft_bzero(inst->memory, MEM_SIZE);
	inst->num_of_players = 0;
	inst->player_num[0] = 0;
	inst->player_num[1] = 0;
	inst->player_num[2] = 0;
	inst->player_num[3] = 0;
	inst->players = NULL;
	inst->process = NULL;
	inst->winner = 0;
	inst->total_process = 0;
	inst->cycle_to_die = CYCLE_TO_DIE;
	inst->total_cycle = 0;
	inst->live_current_per = 0;
	inst->live_last_per = 0;
	return (inst);
}
