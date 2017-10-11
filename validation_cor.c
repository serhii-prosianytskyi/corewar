/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_cor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 17:23:52 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/09 17:23:53 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int ft_prog_name(int fd, char *prog_name)
{
	ssize_t i;
	char *str;

	str = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH + 1 + 3));
	i = read(fd, str, (PROG_NAME_LENGTH + 1 + 3));
	if (i != (PROG_NAME_LENGTH + 1 + 3))
		return (1);
	return (0);
}

int ft_prog_comment(int fd, char *comment)
{
	ssize_t i;
	char *str;

	str = (char *)malloc(sizeof(char) * (COMMENT_LENGTH + 1 + 3));
	i = read(fd, str, (COMMENT_LENGTH + 1 + 3));
	if (i != (COMMENT_LENGTH + 1 + 3))
		return (1);
	return (0);
}

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

int ft_opcode(t_opcode *op_lst, int *ind, char *str)
{
	unsigned int num;

	op_lst->operation = str[*ind];
	*ind += 1;
	if (help.coding_byte[op_lst->operation - 1])
	{
		op_lst->cod_byte = str[*ind];
		*ind += 1;
	}
	op_lst->num_param = op_tab[op_lst->operation - 1].num_arguments;
	ft_fill_param_size(op_lst);
	ft_fill_param(op_lst, str, ind);
	return (0);
}

char *ft_read_opcode(int fd, int size)
{
	char *str;

	str = (char *)malloc(sizeof(char) * (size + 2));
	ft_bzero(str, (size + 2));
	if (read(fd, str, (size + 2)) != size)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

int	ft_validation_cor(int fd, header_t *header, t_opcode *op_lst)
{
	char *str;
	int i;
	char line[4];

	if (read(fd, line, 4) != 4)
		return (1);
	if ((header->magic = ft_uint(0, line)) != COREWAR_EXEC_MAGIC)
		return (1);
	if (ft_prog_name(fd, header->prog_name))
		return (1);
	if (read(fd, line, 4) != 4)
		return (1);
	if ((header->prog_size = ft_uint(0, line)) == 0 ||
		header->prog_size > CHAMP_MAX_SIZE)
		return (1);
	if (ft_prog_comment(fd, header->comment))
		return (1);
	if ((str = ft_read_opcode(fd, header->prog_size)) == NULL)
		return (1);
	i = 0;
	if (ft_opcode(op_lst, &i, str))
		return (1);
	//free(str);
	return (0);
}
