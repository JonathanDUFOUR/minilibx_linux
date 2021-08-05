/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_parse_xpm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 17:35:45 by jodufour          #+#    #+#             */
/*   Updated: 2021/08/05 19:06:19 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_zeta.h"

void	*mlx_return(t_xvar *xvar, t_zeta *zeta);
int		mlx_int_get_text_rgb(char *name, char *end);
int		mlx_int_get_col_name(char *str, int size);
void	mlx_int_xpm_set_pixel(t_zeta zeta);

void	*mlx_int_parse_xpm(t_xvar *xvar, void *info, int info_size,
	char *(*f)())
{
	t_zeta	zeta;

	memset(&zeta, 0, sizeof(t_zeta));
	zeta.line = f(info, &zeta.pos, info_size);
	if (!zeta.line)
		return (mlx_return(xvar, &zeta));
	zeta.tab = mlx_int_str_to_wordtab(zeta.line);
	if (!zeta.tab)
		return (mlx_return(xvar, &zeta));
	zeta.width = atoi(zeta.tab[0]);
	zeta.height = atoi(zeta.tab[1]);
	zeta.nc = atoi(zeta.tab[2]);
	zeta.cpp = atoi(zeta.tab[3]);
	if (!zeta.width || !zeta.height || !zeta.nc || !zeta.cpp)
		return (mlx_return(xvar, &zeta));
	free(zeta.tab);
	zeta.tab = NULL;
	zeta.method = 0;
	if (zeta.cpp <= 2)
	{
		zeta.method = 1;
		zeta.colors_direct = malloc(((zeta.cpp == 2) * 65536 + (zeta.cpp != 2)
					* 256) * sizeof(int));
		if (!zeta.colors_direct)
			return (mlx_return(xvar, &zeta));
	}
	else
	{
		zeta.colors = malloc(zeta.nc * sizeof(*zeta.colors));
		if (!zeta.colors)
			return (mlx_return(xvar, &zeta));
	}
	zeta.clip_data = 0;
	(void)zeta.clip_data;
	zeta.i = zeta.nc;
	while (zeta.i--)
	{
		zeta.line = f(info, &zeta.pos, info_size);
		if (!zeta.line)
			return (mlx_return(xvar, &zeta));
		zeta.tab = mlx_int_str_to_wordtab(zeta.line + zeta.cpp);
		if (!zeta.tab)
			return (mlx_return(xvar, &zeta));
		zeta.j = 0;
		while (zeta.tab[zeta.j] && strcmp(zeta.tab[zeta.j], "c"))
			++zeta.j;
		if (!zeta.tab[zeta.j])
			return (mlx_return(xvar, &zeta));
		zeta.rgb_col = mlx_int_get_text_rgb(zeta.tab[zeta.j], zeta.tab[zeta.j + 1]);
		if (zeta.method)
			zeta.colors_direct[mlx_int_get_col_name(zeta.line, zeta.cpp)] = zeta.rgb_col;
		else
		{
			zeta.colors[zeta.i].name = mlx_int_get_col_name(zeta.line, zeta.cpp);
			zeta.colors[zeta.i].col = zeta.rgb_col;
		}
		free(zeta.tab);
		zeta.tab = NULL;
	}
	zeta.img = mlx_new_image(xvar, zeta.width, zeta.height);
	if (!zeta.img)
		return (mlx_return(xvar, &zeta));
	zeta.opp = zeta.img->bpp / 8;
	zeta.i = zeta.height;
	zeta.data = zeta.img->data;
	while (zeta.i--)
	{
		zeta.line = f(info, &zeta.pos, info_size);
		if (!zeta.line)
			return (mlx_return(xvar, &zeta));
		zeta.x = 0;
		while (zeta.x < zeta.width)
		{
			zeta.col = 0;
			zeta.col_name = mlx_int_get_col_name(zeta.line + zeta.cpp * zeta.x, zeta.cpp);
			if (zeta.method)
				zeta.col = zeta.colors_direct[zeta.col_name];
			else
			{
				zeta.j = zeta.nc;
				while (zeta.j--)
				{
					if (zeta.colors[zeta.j].name == zeta.col_name)
					{
						zeta.col = zeta.colors[zeta.j].col;
						zeta.j = 0;
					}
				}
			}
			if (zeta.col == -1)
				zeta.col = 0xFF000000;
			mlx_int_xpm_set_pixel(zeta);
			++zeta.x;
		}
		zeta.data += zeta.img->size_line;
	}
	if (zeta.colors)
		free(zeta.colors);
	if (zeta.colors_direct)
		free(zeta.colors_direct);
	return (zeta.img);
}
