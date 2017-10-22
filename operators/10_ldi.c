#include "../corewar_vm.h"

void ldi_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	unsigned int		first;
	unsigned int		second;
	int 				sum;

	if(arg->type_param[0] == T_REG) 
		first = pr->reg[arg->param[0] - 1];
	else
		first = arg->param[0];
	if(arg->type_param[1] == T_REG) 
		second =  pr->reg[arg->param[1] - 1];
	else
		second =  arg->param[1];
	sum = (first + second) % IDX_MOD;
	sum = get_pc(pr->pc + sum);
	pr->reg[arg->param[2] - 1] = sum;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}