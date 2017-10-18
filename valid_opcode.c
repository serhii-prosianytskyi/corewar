/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_opcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 19:18:41 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/12 19:18:43 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int ft_first_param(t_opcode *op_lst, int num)
{
	if ((num & 64) == 64)
		return (1);
	else if ((num & 128) == 128)
		return (help.label_size[op_lst->operation - 1]);
	else
		return (2);
}

int ft_second_param(t_opcode *op_lst, int num)
{
	if ((num & 16) == 16)
		return (1);
	else if ((num & 32) == 32)
		return (help.label_size[op_lst->operation - 1]);
	else
		return (2);
}

int ft_third_param(t_opcode *op_lst, int num)
{
	if ((num & 4) == 4)
		return (1);
	else if ((num & 8) == 8)
		return (help.label_size[op_lst->operation - 1]);
	else
		return (2);
}

int	ft_var_param(t_opcode *op_lst, int nam_arg)
{
	int rez;

	if (nam_arg == 0)
		rez = ft_first_param(op_lst, op_lst->cod_byte);
	if (nam_arg == 1)
		rez = ft_second_param(op_lst, op_lst->cod_byte);
	if (nam_arg == 2)
		rez = ft_third_param(op_lst, op_lst->cod_byte);
	return (rez);
}

void ft_fill_param_size(t_opcode *op_lst)
{
	int i;

	i = -1;
	while (++i < op_lst->num_param)
	{
		if (help.arg_size[op_lst->operation - 1][i])
			op_lst->param_size[i] = help.arg_size[op_lst->operation - 1][i];
		else
			op_lst->param_size[i] = ft_var_param(op_lst, i);
	}
}

int	ft_fill_param(t_opcode *op_lst, t_mstruc *inst, int *ind)
{
	int i;

	i = -1;
	while (++i < op_lst->num_param)
	{
		if (op_lst->param_size[i] == 1)
		{
			op_lst->param[i] = inst->memory[*ind];
			*ind += 1;
			if (op_lst->param[i] < 1 || op_lst->param[i] > 16)
				return (1);
		}
		else if (op_lst->param_size[i] == 2)
		{
			op_lst->param[i] = ft_ushort(*ind, inst->memory);
			*ind += 2;
		}
		else
		{
			op_lst->param[i] = ft_uint(*ind, inst->memory);
			*ind += 4;
		}
	}
	return (0);
}

int ft_type_param(t_opcode *op_lst, int nam_arg, unsigned char *test_byte)
{
	if (nam_arg == 0)
	{
		if ((op_lst->cod_byte & 192) == 192)
		{
			*test_byte += 192;
			return (T_IND);
		}
		if ((op_lst->cod_byte & 64) == 64)
		{
			*test_byte += 64;
			return (T_REG);
		}
		else if ((op_lst->cod_byte & 128) == 128)
		{
			*test_byte += 128;
			return (T_DIR);
		}
	}
	else if (nam_arg == 1)
	{
		if ((op_lst->cod_byte & 48) == 48)
		{
			*test_byte += 48;
			return (T_IND);
		}
		else if ((op_lst->cod_byte & 16) == 16)
		{
			*test_byte += 16;
			return (T_REG);
		}
		else if ((op_lst->cod_byte & 32) == 32)
		{
			*test_byte += 32;
			return (T_DIR);
		}
	}
	else if (nam_arg == 2)
	{

		if ((op_lst->cod_byte & 12) == 12)
		{
			*test_byte += 12;
			return (T_IND);
		}
		else if ((op_lst->cod_byte & 4) == 4)
		{
			*test_byte += 4;
			return (T_REG);
		}
		else if ((op_lst->cod_byte & 8) == 8)
		{
			*test_byte += 8;
			return (T_DIR);
		}
	}
	return (0);
}

int ft_validate_coding_byte(t_process *process)
{
	int flag;
	int i;
	int rez;
	unsigned char test_byte;
	t_opcode *code;

	code = process->opcode;
	flag = 0;
	i = -1;
	test_byte = 0;
	while (++i < 3)
	{
		rez = ft_type_param(code, i, &test_byte);
		if ((rez & op_tab[code->operation - 1].arguments_types[i]) != rez)
			flag++;
		else
			code->type_param[i] = rez;
		code->row_size += ft_var_param(code, i);
	}
	test_byte -= code->cod_byte;
	if (flag || test_byte)
		return (1);
	return (0);
}

int ft_opcode(int *pc, t_mstruc *inst, t_process *process)
{
	process->opcode->operation = inst->memory[*pc];
	if (process->opcode->operation < 1 || process->opcode->operation > 16)
	{
		process->opcode->row_size += 1;
		return (2);
	}
	*pc += 1;
	if (help.coding_byte[process->opcode->operation - 1])
	{
		process->opcode->cod_byte = inst->memory[*pc];
		*pc += 1;
		if (ft_validate_coding_byte(process))
			return (1);
	}
	process->opcode->num_param = op_tab[process->opcode->operation - 1].num_arguments;
	ft_fill_param_size(process->opcode);
	if (ft_fill_param(process->opcode, inst, pc))
		return (1);
	return (0);
}