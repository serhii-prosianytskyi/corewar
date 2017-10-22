#include "../corewar_vm.h"

void sti_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	int	first;
	int	second;
	int 			sum;

	if(arg->type_param[1] == T_REG) 
		first = pr->reg[arg->param[1] - 1];
	else
		first = arg->param[1];
	if (arg->type_param[2] == T_REG) 
		second = pr->reg[arg->param[2] - 1];
	else
		second = arg->param[2];
	sum = (first + second) % IDX_MOD;
	sum = get_pc(pr->pc + sum);
	value_to_memory(ms, sum, pr->reg[arg->param[0] - 1]);
	ft_print_in_gen(sum, ms, pr);
	ft_print_corr(ms, pr->pc, pr->pc + pr->opcode->row_size);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;

}