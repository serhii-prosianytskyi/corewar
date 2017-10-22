#include "../corewar_vm.h"

void and_com(t_mstruc *ms, t_process *pr, t_opcode *arg)
{
	
	if (arg->type_param[0] == T_REG && arg->type_param[1] == T_REG)
		pr->reg[arg->param[2] - 1] = pr->reg[arg->param[0] - 1] & pr->reg[arg->param[1] - 1];
	else if (arg->type_param[0] != T_REG && arg->type_param[1] == T_REG)
		pr->reg[arg->param[2] - 1] = arg->param[0] & pr->reg[arg->param[1] - 1];
	else if (arg->type_param[0] == T_REG && arg->type_param[1] != T_REG
			&& (arg->param[0] >= 1 && arg->param[0] <= REG_NUMBER))
		pr->reg[arg->param[2] - 1] = pr->reg[arg->param[0] - 1] & arg->param[1];
	else if (arg->type_param[0] != T_REG && arg->type_param[1] != T_REG)
		pr->reg[arg->param[2] - 1] = arg->param[0] & arg->param[1];
	else
	{
		ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
		pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
		return ;
	}
	if (pr->reg[arg->param[2] - 1] == 0)
		pr->carry = 1;
	else
		pr->carry = 0;
	ft_print_corr(ms, pr->pc, (pr->pc + pr->opcode->row_size) % MEM_SIZE);
	pr->pc = (pr->pc + pr->opcode->row_size) % MEM_SIZE;
}