#include "corewar_vm.h"

size_t		get_pc(size_t pc)
{
	return (pc % MEM_SIZE);
}

t_process	*empty_process()
{
	t_process *pr;
	int i;

	i = 0;
	pr = (t_process*)malloc(sizeof(t_process));
	pr->validation_flag = 0;
	pr->operation = 0;
	pr->pc = 0;
	pr->carry = 0;
	pr->live_flag = 0;
	pr->prev = NULL;
	pr->next = NULL;
	while (i < REG_NUMBER)
	{
		pr->reg[i] = 0;
		++i;
	}
	return (pr);
}

t_process	*copy_process(t_process *rhs)
{
	t_process *pr;
	int i;

	i = 0;
	pr = empty_process();
	pr->validation_flag = rhs->validation_flag;
	pr->operation = rhs->operation;
	pr->pc = rhs->pc;
	pr->carry = rhs->carry;
	pr->live_flag = rhs->live_flag;
	pr->prev = NULL;
	pr->next = NULL;
	while (i < REG_NUMBER)
	{
		pr->reg[i] = rhs->reg[i];
		++i;
	}
	return (pr);
}

void new_process(t_process *rpr, t_mstruc *ms, int pc)
{
	t_process *pr;

	pr = copy_process(rpr);
	pr->pc = pc;
	pr-> next = ms->process;
	ms->process->prev = pr;
	ms->process = pr;
}


void delete_process(t_process *pr, t_mstruc *ms)
{
	if (pr == ms->process)
		ms->process = ms->process->next;
	if (pr->next != NULL)
		pr->next->prev = pr->prev;
	if (pr->prev != NULL)
		pr->prev->next = pr->next;
	free(pr);
}

void	value_to_memory(t_mstruc *ms, size_t pos, int val)
{
	ms->memory[pos] = (unsigned char)(val >> 24);
	ms->memory[get_pc(pos + 1)] = (unsigned char)(val >> 16);
	ms->memory[get_pc(pos + 2)] = (unsigned char)(val >> 8);
	ms->memory[get_pc(pos + 3)] = (unsigned char)(val);
}