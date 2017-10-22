#include "../corewar_vm.h"

void aff_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	char c;

	c = pr->reg[arg->param[0] - 1] % 256;
	write(1, "Aff: ", 5);
	write(1, &c, 1);
	write(1, "\n", 1);
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}