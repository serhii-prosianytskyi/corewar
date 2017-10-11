/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprosian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 18:34:06 by sprosian          #+#    #+#             */
/*   Updated: 2017/10/07 18:34:08 by sprosian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_COREWAR_VM_H
# define COREWAR_VM_COREWAR_VM_H
# include "libft/libft.h"
# include "op.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_opcode
{
	unsigned int row_size;
	int operation;
	int cod_byte;
	int num_param;
	unsigned int param[3];
	int param_size[3];
	struct s_opcode *next;
}				t_opcode;

typedef struct		s_op
{
	char			*comand_name;
	int				num_arguments;
	char			arguments_types[3];
	int				opcode;
	int				cycles;
	char			*description;
	char			arguments_byte;
	char			index_size;
}					t_op;

typedef struct                 s_helper
{
	int                     comands[16];
	int                     label_size[16];
	int 					coding_byte[16];
	int 					var_arg[16][3];
	int 					arg_size[16][3];
}                            t_helper;

t_helper help;
t_op    op_tab[17];

t_opcode *ft_init_opcode(void);
header_t	*ft_init_header(void);

int ft_validation(char *f_name, header_t *header, t_opcode *op_lst);

unsigned int ft_uint(int ind, char *str);
unsigned short ft_ushort(int ind, char *str);

void	ft_error_vm(void);
char	*ft_realloc(char *ptr, int size, char *buf);

int	ft_validation_cor(int fd, header_t *header, t_opcode *op_lst);
int ft_prog_name(int fd, char *prog_name);
int ft_prog_comment(int fd, char *comment);
int ft_opcode(t_opcode *op_lst, int *ind, char *str);

#endif //COREWAR_VM_COREWAR_VM_H
