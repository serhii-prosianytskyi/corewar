/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 20:26:52 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/14 20:26:53 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int 	ft_lst_len(void *lst, int flag, int len)
{
	t_players *player;
	t_process *process;

	player = NULL;
	process = NULL;
	if (flag == 1)
	{
		player = (t_players *)lst;
		while (player)
		{
			len++;
			player = player->next;
		}
		return (len);
	}
	else
	{
		process = (t_process *)lst;
		while (process)
		{
			len++;
			process = process->next;
		}
		return (len);
	}
}

void	*ft_lst_end(void *lst, int flag)
{
	t_players *player;
	t_process *process;

	player = NULL;
	process = NULL;
	if (flag == 1)
	{
		player = (t_players *)lst;
		while (player->next)
			player = player->next;
		return ((void *)player);
	}
	else
	{
		process = (t_process *)lst;
		while (process->next)
			process = process->next;
		return ((void *)process);
	}
}

t_players *ft_copy_player_s(t_players *lst)
{
	t_players *new;

	new = ft_init_players();
	free(new->header);
	new->header = lst->header;
	new->opcode = lst->opcode;
	new->pl_num = lst->pl_num;
	return (new);
}

void	*ft_sort_players_h(t_players *new, t_players *lst, int flag)
{
	if (flag == 1)
	{
		while (new->next)
		{
			if (new->pl_num < lst->pl_num)
				new = new->next;
			else
				break ;
		}
		new->next = ft_copy_player_s(lst);
		new->next->prev = new;
	}
	else
	{
		while (new->prev)
		{
			if (new->pl_num < lst->pl_num)
				new = new->prev;
			else
				break ;
		}
		new->prev = ft_copy_player_s(lst);
		new->prev->next = new;
	}
}

t_players *ft_sort_players(t_players *lst)
{
	t_players *new;
	t_players *copy_lst;

	copy_lst = lst;
	new = ft_copy_player_s(lst);
	lst = lst->next;
	while (lst)
	{
		if (new->pl_num < lst->pl_num)
			ft_sort_players_h(new, lst, 1);
		else
			ft_sort_players_h(new, lst, 2);
		lst = lst->next;
	}
	while (new->prev)
		new = new->prev;
	while (copy_lst)
	{
		lst = copy_lst;
		copy_lst = copy_lst->next;
		free(lst);
	}
	return (new);
}
