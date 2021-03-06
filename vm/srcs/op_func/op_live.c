/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgonon <mgonon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 23:55:03 by gudemare          #+#    #+#             */
/*   Updated: 2018/03/27 04:13:00 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The advancement of the PC is to be made more generic.
*/

int		do_live(t_process *process, t_env *env)
{
	unsigned int	param;
	char			*champion_name;

	param = get_param_raw_value(env, process->pc + 1, T_DIR, OP_LIVE);
	if ((champion_name = get_champ_name(env, param)))
	{
		env->last_live_id = param;
		if (env->visual)
			ft_printf("\n\x1b[KA process reports the champion %s\
(%u) as alive.\x1b[500D\x1b[A", champion_name, param);
	}
	else
		param = NULL_ID;
	env->mask[(process->pc + 1) % MEM_SIZE] = param;
	env->mask[(process->pc + 2) % MEM_SIZE] = param;
	env->mask[(process->pc + 3) % MEM_SIZE] = param;
	env->mask[(process->pc + 4) % MEM_SIZE] = param;
	env->mask[process->pc] = process->champ_id;
	process->is_alive = true;
	env->nb_live++;
	return (0);
}
