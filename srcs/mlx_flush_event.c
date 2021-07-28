/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_flush_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/08/02 01:50:14 by Charlie Roo       #+#    #+#             */
/*   Updated: 2021/07/28 01:51:33 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

void	mlx_flush_event(t_xvar *xvar)
{
  XEvent	ev;

  while (XPending(xvar->display))
  {
     XNextEvent(xvar->display,&ev);
  }
}
