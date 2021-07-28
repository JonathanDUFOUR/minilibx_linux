/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/07/31 19:01:33 by Charlie Roo       #+#    #+#             */
/*   Updated: 2021/07/28 02:22:59 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

void		mlx_pixel_put(t_xvar *xvar,t_win_list *win,
			      int x,int y,int color)
{
   XGCValues	xgcv;
   
   xgcv.foreground = mlx_int_get_good_color(xvar,color);
   XChangeGC(xvar->display,win->gc,GCForeground,&xgcv);
   XDrawPoint(xvar->display,win->window,win->gc,x,y);
   if (xvar->do_flush)
     XFlush(xvar->display);
}
