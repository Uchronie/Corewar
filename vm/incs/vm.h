/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:10:32 by gudemare          #+#    #+#             */
/*   Updated: 2018/04/04 22:56:27 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include <stdbool.h>

# define DUMP_LINE_LEN	32
# define NULL_ID 0

/*
**	ANSI escape sequences for colors.
*/
# define COLOR_P1 "\x1b[0;31m"
# define COLOR_P1_PC "\x1b[0;1;7;31m"
# define COLOR_P2 "\x1b[0;32m"
# define COLOR_P2_PC "\x1b[0;1;7;32m"
# define COLOR_P3 "\x1b[0;33m"
# define COLOR_P3_PC "\x1b[0;1;7;33m"
# define COLOR_P4 "\x1b[0;34m"
# define COLOR_P4_PC "\x1b[0;1;7;34m"

enum					e_opcode
{
	OP_LIVE = 0x01,
	OP_LD = 0x02,
	OP_ST = 0x03,
	OP_ADD = 0x04,
	OP_SUB = 0x05,
	OP_AND = 0x06,
	OP_OR = 0x07,
	OP_XOR = 0x08,
	OP_ZJMP = 0x09,
	OP_LDI = 0x0A,
	OP_STI = 0x0B,
	OP_FORK = 0x0C,
	OP_LLD = 0x0D,
	OP_LLDI = 0x0E,
	OP_LFORK = 0x0F,
	OP_AFF = 0x10,
};

typedef	struct			s_process
{
	unsigned int		pc;
	unsigned int		reg[REG_NUMBER];
	unsigned int		champ_id;
	unsigned int		cycle_to_wait;
	char				*aff_buffer;
	bool				is_alive;
	bool				carry;
	unsigned short		cur_opcode;
}						t_process;

typedef	struct			s_champion
{
	t_header			header;
	unsigned int		id;
	unsigned char		program[CHAMP_MAX_SIZE];
}						t_champion;

typedef struct			s_env
{
	unsigned char		arena[MEM_SIZE];
	unsigned int		mask[MEM_SIZE];
	t_champion			champions[MAX_PLAYERS];
	t_list				*process;
	t_list				*dead_processes;
	unsigned short		nb_of_champions;
	bool				is_dump_cycle_specified;
	bool				debug;
	bool				interactive;
	bool				visual;
	bool				comparison;
	bool				aff;
	bool				skip_cycle;
	size_t				dump_cycle;
	size_t				cycle_to_die;
	size_t				nb_live;
	unsigned int		last_live_id;
	int					(*exec_inst_tab[17]) (t_process *process,
						struct s_env *env);
}						t_env;

typedef struct			s_op
{
	char				*name;
	unsigned short		nb_of_params;
	unsigned short		param_type[3];
	unsigned short		opcode;
	unsigned short		cycle_nb;
	char				*description;
	bool				ocp;
	bool				addr_or_nb;
	bool				modif_carry;
}						t_op;

extern t_op				g_op_tab[17];

/*
** Init & Parsing
*/
void					init_env(t_env *env);
void					parse_argv(t_env *env, char **argv);
void					parse_champion(t_env *env, char *custom_id,
						char *program_path);
void					parse_file(t_env *env, char *program_path);

/*
** Utils
*/
bool					is_string_numeric(char *s);
void					free_env(t_env env);
void					ft_free_exit(t_env env, char *error,
						bool disp_errno, bool disp_usage);
unsigned int			swap_uint32(unsigned int x);
unsigned int			ft_unsigned_atoi(const char *str);
unsigned int			ft_lstlen(t_list *lst);
char					*get_champ_name(t_env *env, unsigned int id);
void					print_usage(void);
/*
** Arena runtime
*/
void					run(t_env *env);
/*
** Arena Init
*/
void					load_champions(t_env *env);
/*
** Arena utils
*/
void					disp_arena(t_env *env, size_t line_len);
void					debug_actions(t_process *process, char *action);
unsigned int			get_uintfrom_char(t_env *env,
						unsigned int start, unsigned short size);
unsigned short			get_param_type(t_env *env, unsigned int pc,
						unsigned short opcode, unsigned int param_nb);
unsigned int			get_param_raw_value(t_env *env, unsigned int start,
						unsigned short param_type, unsigned short opcode);
void					write_uint_to_char(t_env *env, unsigned int start,
						unsigned short size, unsigned int value);
unsigned int			skip_pc(t_env *env, t_process *process);
unsigned int			is_reg(unsigned int value);
void					disp_process_state(t_env *env, t_process *proc);
void					ft_pause(t_env *env);
void					dump_memory(t_env *env, size_t line_len);
void					disp_cycle_data(t_env *env, size_t cycle,
						size_t global_cycle, size_t nb_checks);
void					set_process_instruction(t_env *env, t_process *process);

/*
** List of actions tht can be performed by the process
*/
int						do_live(t_process *process, t_env *env);
int						do_ld(t_process *process, t_env *env);
int						do_st(t_process *process, t_env *env);
int						do_add(t_process *process, t_env *env);
int						do_sub(t_process *process, t_env *env);
int						do_and(t_process *process, t_env *env);
int						do_or(t_process *process, t_env *env);
int						do_xor(t_process *process, t_env *env);
int						do_zjmp(t_process *process, t_env *env);
int						do_ldi(t_process *process, t_env *env);
int						do_sti(t_process *process, t_env *env);
int						do_fork(t_process *process, t_env *env);
int						do_lld(t_process *process, t_env *env);
int						do_lldi(t_process *process, t_env *env);
int						do_lfork(t_process *process, t_env *env);
int						do_aff(t_process *process, t_env *env);

/*
** Utils for process
*/
t_list					*lstdelnode(t_list *cur, t_list *node);
size_t					kill_dead_processes(t_env *env);
void					add_new_process(t_env *env, unsigned int champion_id);
void					release_aff_buffer(t_process *process);
void					pop_one_dead_process(t_env *env);

#endif
