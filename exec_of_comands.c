#include "corewar_vm.h"

void execution_of_comands(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	if (pr->operation_num == 1)
		live_com(ms, pr, arg);
	else if (pr->operation_num == 2)
		ld_com(ms, pr, arg);
	else if (pr->operation_num == 3)
		st_com(ms, pr, arg);
	else if (pr->operation_num == 4)
		add_com(ms, pr, arg);
	else if (pr->operation_num == 5)
		sub_com(ms, pr, arg);
	else if (pr->operation_num == 6)
		and_com(ms, pr, arg);
	else if (pr->operation_num == 7)
		or_com(ms, pr, arg);
	else if (pr->operation_num == 8)
		xor_com(ms, pr, arg);
	else if (pr->operation_num == 9)
		zjmp_com(ms, pr, arg);
	else if (pr->operation_num == 10)
		ldi_com(ms, pr, arg);
}

void execution_of_comands1(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	if (pr->operation_num == 11)
		sti_com(ms, pr, arg);
	else if (pr->operation_num == 12)
		fork_com(ms, pr, arg);
	else if (pr->operation_num == 13)
		lld_com(ms, pr, arg);
	else if (pr->operation_num == 14)
		lldi_com(ms, pr, arg);
	else if (pr->operation_num == 15)
		lfork_com(ms, pr, arg);
	else if (pr->operation_num == 16)
		aff_com(ms, pr, arg);
}