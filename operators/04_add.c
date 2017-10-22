#include "../corewar_vm.h"


void add_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	pr->reg[arg->param[2] - 1] = pr->reg[arg->param[0] - 1] + pr->reg[arg->param[1] - 1];
	if (pr->reg[arg->param[2] - 1] == 0)
		pr->carry = 1;
	else
		pr->carry = 0;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}