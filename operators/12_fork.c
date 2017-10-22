#include "../corewar_vm.h"

void fork_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	int new_pc;

	new_pc = pr->pc + (arg->param[0] % IDX_MOD);
    if (new_pc < 0)
        new_pc = new_pc + (MEM_SIZE -1);
	new_process(pr, ms, new_pc);
	ms->total_process++;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}
