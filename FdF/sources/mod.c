/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:43:17 by rwintgen          #+#    #+#             */
/*   Updated: 2023/12/17 17:58:49 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "MLX42/MLX42.h"

void	ft_mod_key(mlx_key_data_t keydata, void *param)
{
	t_map	*map_c;

	map_c = param;
	if (keydata.key >= MLX_KEY_RIGHT && keydata.key <= MLX_KEY_UP)
		ft_move(map_c, keydata.key);
	if (keydata.key == MLX_KEY_EQUAL || keydata.key == MLX_KEY_MINUS)
		ft_scale(map_c, keydata.key);
	ft_rerender(map_c);
	ft_draw_map(map_c);
}

void	ft_mod_scroll(double xdelta, double ydelta, void *param)
{
	t_map	*map_c;

	map_c = param;
	(void) xdelta;
	if (ydelta > 0)
		map_c->cam.zoom += 1;
	if (ydelta < 0)
		map_c->cam.zoom -= 1;
	ft_rerender(map_c);
	ft_draw_map(map_c);
}