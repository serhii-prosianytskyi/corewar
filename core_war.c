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

}

void	ft_check_flags(t_mstruc *inst)
{

}

void	ft_validate_option(t_process *lst, t_mstruc *inst)
{
	if (lst->validation_flag == 0)
	{

	}
	else
	{

		lst->validation_flag = 0;
	}
}

void	ft_core_war(t_mstruc *inst)
{
	t_process *lst;

	ft_create_process(inst);
	ft_check_flags(inst);
	while (inst->total_cycle < inst->dump_flag)
	{
		lst = inst->process;
		while (lst)
		{
			ft_validate_option(lst, inst);
			lst = lst->next;
		}
		inst->total_process++;
	}
}