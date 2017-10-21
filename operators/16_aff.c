#include "../corewar_vm.h"

void aff_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	printf("Aff: %c\n", (char)pr->reg[arg->param[0]]);
	pr->pc = pr->pc + pr->opcode->row_size;
}