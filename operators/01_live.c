#include "../corewar_vm.h"

void live_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	int player;
	t_players *lst;

	lst = ms->players;
	player = arg->param[0] * -1;
	if (player > 0 && player <= INT_MAX)
	{
		while (lst)
		{
			if (lst->pl_num == player)
			{
				lst->live_flag++;
				lst->last_live = ms->total_cycle;
			}
			lst = lst->next;
		}
	}
	(ms->live_current_per)++;
	(pr->live_flag)++;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}