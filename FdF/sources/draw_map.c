/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:51:10 by rwintgen          #+#    #+#             */
/*   Updated: 2023/12/17 18:19:34 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "MLX42/MLX42.h"
#include <math.h>

#include <stdio.h>

void	ft_iso_line(t_point	*orig, t_point *dest, t_map *map)
{
	printf("\n\tentered ft_iso_line\n\n");

	float	orig_x;
	float	orig_y;
	float	dest_x;
	float	dest_y;

	orig_x = orig->x;
	orig_y = orig->y;
	dest_x = dest->x;
	dest_y = dest->y;

	orig->x = (orig_x - orig_y) * cos(0.6); // TODO replace with cam.angle
	printf("\tnew orig.x: %f\n", orig->x);

	orig->y = (orig_x + orig_y) * sin(0.6) - orig->z * map->cam.scale;
	printf("\tnew orig.y: %f\n", orig->y);

	dest->x = (dest_x - dest_y) * cos(0.6);
	printf("\tnew dest.x: %f\n", dest->x);

	dest->y = (dest_x + dest_y) * sin(0.6) - dest->z * map->cam.scale;
	printf("\tnew dest.y: %f\n", dest->y);
}

void	ft_bresenham(t_map *map, t_point orig, t_point dest)
{
	float	delta_x;
	float	delta_y;
	int		max;

	printf("\n\n==================beginning ft_bresenham==================\n");

	orig.z = map->altitude[(int)orig.y][(int)orig.x];
	dest.z = map->altitude[(int)dest.y][(int)dest.x];

	printf("\norig.x: %f\torig.y: %f\torig.z: %f", orig.x, orig.y, orig.z);
	printf("\ndest.x: %f\tdest.y: %f\tdest.z: %f\n", dest.x, dest.y, dest.z);

	printf("\nentering ft_add_color...\n");

	ft_add_color(&orig, &dest);

	printf("\norig.x: %f\torig.y: %f\torig.z: %f", orig.x, orig.y, orig.z);
	printf("\ndest.x: %f\tdest.y: %f\tdest.z: %f\n", dest.x, dest.y, dest.z);

	printf("\nentering ft_iso_line...\n");

	ft_iso_line(&orig, &dest, map);

	printf("\norig.x: %f\torig.y: %f\torig.z: %f", orig.x, orig.y, orig.z);
	printf("\ndest.x: %f\tdest.y: %f\tdest.z: %f\n", dest.x, dest.y, dest.z);

	printf("\nentering ft_shift...\n");

	ft_shift(&orig, &dest, map);

	printf("\norig.x: %f\torig.y: %f\torig.z: %f", orig.x, orig.y, orig.z);
	printf("\ndest.x: %f\tdest.y: %f\tdest.z: %f\n", dest.x, dest.y, dest.z);

	printf("\nentering ft_zoom...\n");
	printf("adding x%d factor...\n", map->cam.zoom);

	ft_zoom(map, &orig, &dest);

	printf("\norig.x: %f\torig.y: %f\torig.z: %f", orig.x, orig.y, orig.z);
	printf("\ndest.x: %f\tdest.y: %f\tdest.z: %f\n", dest.x, dest.y, dest.z);

	delta_x = (dest.x - orig.x);
	delta_y = (dest.y - orig.y);
	max = ft_max(delta_x, delta_y);
	delta_x = delta_x / max;
	delta_y = delta_y / max;

	printf("\ndrawing line...\n");

	while ((int)(orig.x - dest.x) || (int)(orig.y - dest.y))
	{
		//mlx_put_pixel(map->mlx_img, orig.x, orig.y, orig.col);
		ft_put_pixel(map, orig);
		orig.x += delta_x;
		orig.y += delta_y;
	}

	printf("line drawn!\n");
}

void	ft_draw_map(t_map *map)
{
	t_point	ref;
	t_point	v;
	t_point	h;

	printf("\nstarting drawing...\n");

	ref.y = 0;
	while (ref.y < map->height)
	{
		ref.x = 0;
		v = ref;
		h = ref;
		v.y = ref.y + 1;
		while (ref.x < map->width)
		{
			h.x = ref.x + 1;
			if (ref.x < map->width -1)
				ft_bresenham(map, ref, h);
			if (ref.y < map->height -1)
				ft_bresenham(map, ref, v);
			ref.x++;
			v.x++;
		}
		ref.y++;
	}
}