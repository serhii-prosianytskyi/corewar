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

void	ft_fill_param(t_opcode *op_lst, char *str, int *ind)
{
	int i;

	i = -1;
	while (++i < op_lst->num_param)
	{
		if (op_lst->param_size[i] == 1)
		{
			op_lst->param[i] = (unsigned char)str[*ind];
			*ind += 1;
		}
		else if (op_lst->param_size[i] == 2)
		{
			op_lst->param[i] = ft_ushort(*ind, str);
			*ind += 2;
		}
		else
		{
			op_lst->param[i] = ft_uint(*ind, str);
			*ind += 4;
		}
	}
}

int ft_opcode(int *pc, unsigned char *memory, t_opcode *code)
{
	code->operation = memory[*pc];
	*pc += 1;
	if (help.coding_byte[code->operation - 1])
	{
		code->cod_byte = memory[*pc];
		*pc += 1;
	}
	code->num_param = op_tab[code->operation - 1].num_arguments;
	ft_fill_param_size(code);
	ft_fill_param(code, memory, pc);
	return (0);
}