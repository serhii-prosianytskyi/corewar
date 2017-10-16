/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_argc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 21:42:42 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/11 21:42:43 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

char *ft_dump_num(int *ind, char **params, t_mstruc *inst)
{
	int i;

	i = -1;
	if (params[*ind + 1])
	{
		while (params[*ind + 1][++i])
		{
			if (ft_isdigit(params[*ind + 1][i]) == 0)
			{
				if (i == 0 && params[*ind + 1][i] == '-')
					;
				else
					return (USAGE);
			}
		}
		*ind += 1;
		inst->dump_flag = ft_atoi(params[*ind]);
		return (NULL);
	}
	return (USAGE);
}

char	*ft_num_player(int ind, char **params, t_mstruc *inst, int i)
{
	int num;

	if (params[ind] && params[ind + 1])
	{
		while (params[ind][++i])
		{
			if (ft_isdigit(params[ind][i]) == 0)
				return (NUM_WRONG);
		}
		num = ft_atoi(params[ind]);
		if (num < 1 || num > MAX_PLAYERS)
			return (NUM_WRONG);
		else
		{
			i = ft_lst_len(inst->players, 1, 0);
			if (i < MAX_PLAYERS)
			{
				inst->player_num[i] = num;
				return (NULL);
			}
			else
				return (MANY_CHAMP);
		}
	}
	return (NUM_WRONG);
}

int 	ft_file_extension(char *str)
{
	char *ptr;
	int i;

	i = 0;
	if ((ptr = ft_strstr(str, ".cor")) == NULL)
		return (1);
	while (*ptr)
	{
		i++;
		ptr++;
	}
	if (i != 4)
		return (1);
	return (0);
}

char	*ft_create_new_player(int i, char **params, t_mstruc *inst)
{
	t_players	*tmp;
	int 		fd;
	char 		*str;

	inst->num_of_players += 1;
	tmp = inst->players;
	if (tmp)
	{
		tmp = (t_players *)ft_lst_end(tmp, 1);
		tmp->next = ft_init_players();
		tmp = tmp->next;
	}
	else
	{
		inst->players = ft_init_players();
		tmp = inst->players;
	}
	if (ft_file_extension(params[i]))
		return (EXTENSION);
	if ((fd = open(params[i], O_RDONLY)) < 0)
		return (CANT_READ);
	str = ft_validation_cor(fd, tmp);
	close(fd);
	return (str);
}


void	ft_validation_arg(int argc, char **params, t_mstruc *inst, int i)
{
	char *fail;

	fail = NULL;
	argc -= 1;
	while (++i < argc)
	{
		if (ft_strcmp(params[i], BONUS) == 0)
			inst->bonus_flag = 1;
		else if (ft_strcmp(params[i], DUMP) == 0)
			fail = ft_dump_num(&i, params, inst);
		else if (ft_strcmp(params[i], NUM) == 0)
			fail = ft_num_player(++i, params, inst, -1);
		else
			fail = ft_create_new_player(i, params, inst);
		if (fail)
			ft_error_vm(fail, inst, params);
	}
	if ((i = ft_lst_len(inst->players, 1, 0)) == 0)
		ft_error_vm(NOT_CHAMP, inst, params);
	if (i > MAX_PLAYERS)
		ft_error_vm(MANY_CHAMP, inst, params);
	if ((fail = ft_move_to_mas(inst)) != NULL)
		ft_error_vm(fail, inst, params);
	ft_dell_mas(params);
}