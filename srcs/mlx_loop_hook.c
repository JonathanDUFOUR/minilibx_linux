/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/08/03 11:49:06 by Charlie Roo       #+#    #+#             */
/*   Updated: 2021/07/28 02:12:05 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

void	mlx_loop_hook(t_xvar *xvar,int (*funct)(),void *param)
{
  xvar->loop_hook = funct;
  xvar->loop_param = param;
}
