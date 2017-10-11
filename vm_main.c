/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 20:17:28 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/04 20:17:29 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void	ft_error_vm(void)
{

}

int ft_validation(char *f_name, header_t *header, t_opcode *op_lst)
{
	int fd;

	if ((fd = open(f_name, O_RDWR, 0)) == -1)
		return (1);
	if (ft_validation_cor(fd, header, op_lst))
		return (1);

}

header_t	*ft_init_header(void)
{
	header_t *header;

	header = (header_t *)malloc(sizeof(header_t));
	header->magic = 0;
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	header->prog_size = 0;
	ft_bzero(header->comment, COMMENT_LENGTH + 1);
	return (header);
}

t_opcode *ft_init_opcode(void)
{
	t_opcode *op_lst;

	op_lst = (t_opcode *)malloc(sizeof(t_opcode));
	op_lst->row_size = 0;
	op_lst->operation = -1;
	op_lst->cod_byte = 0;
	op_lst->num_param = 0;
	op_lst->param[0] = 0;
	op_lst->param[1] = 0;
	op_lst->param[2] = 0;
	op_lst->param_size[0] = 0;
	op_lst->param_size[1] = 0;
	op_lst->param_size[2] = 0;
	op_lst->next = NULL;
	return (op_lst);
}

int main(int argc, char **argv)
{
	header_t *header;
	t_opcode *op_lst;


	header = ft_init_header();
	op_lst = ft_init_opcode();
	if (argc != 2)
		return (1);
	if (ft_validation(argv[1], header, op_lst))
		return (1);
	return (0);
}
