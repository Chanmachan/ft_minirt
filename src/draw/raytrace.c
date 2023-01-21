/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:11:35 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/18 10:48:47 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include "draw.h"
#include "color.h"
#include <math.h>

static void	set_info(t_info *info, double max_dist, \
					bool exit_once_found, bool out_needed);

bool	raytrace(const t_scene *scene, const t_ray *eye_ray, t_rgb *rgb)
{
	t_shape_intp	shape_intp;
	size_t			i;
	t_raytrace		vars;
	t_info			info;

	set_info(&info, INFINITY, false, true);
	if (get_nearest_shape(scene, eye_ray, info, &shape_intp))
	{
		multiple_rgb(rgb, scene->ambient_illuminance, shape_intp.shape->material.ambient_ref);
		i = 0;
		while (i < scene->num_lights)
		{
			if (scene->lights[i].type == LT_POINT)
			{
				vars.l = norm_vec(diff_vec(scene->lights[i].vector, \
											shape_intp.intp.position));
				vars.dl = abs_vec(diff_vec(scene->lights[i].vector, \
											shape_intp.intp.position)) - C_EPSILON;
			}
			else if (scene->lights[i].type == LT_DIRECTIONAL)
			{
				vars.l = norm_vec(constant_mul_vec(\
									scene->lights[i].vector, -1));
				vars.dl = INFINITY;
			}
			vars.shadow_ray.start = add_vec(shape_intp.intp.position, constant_mul_vec(vars.l, C_EPSILON));
			vars.shadow_ray.direction = vars.l;
			set_info(&info, vars.dl, true, false);
			if (get_nearest_shape(scene, &vars.shadow_ray, info, &shape_intp))
			{
				i++;
				continue ;
			}
			vars.nl_dot = inner_product(shape_intp.intp.normal, vars.l);
			vars.nl_dot = ft_clamp(vars.nl_dot, 0, 1);
			add_on_rgb(rgb, shape_intp.shape->material.diffuse_ref, scene->lights[i], vars.nl_dot);
			if (vars.nl_dot > 0)
			{
				vars.r = norm_vec(diff_vec(constant_mul_vec(\
									shape_intp.intp.normal, 2 * vars.nl_dot), vars.l));
				vars.v = norm_vec(constant_mul_vec(\
										eye_ray->direction, -1));
				vars.vr_dot = inner_product(vars.v, vars.r);
				vars.vr_dot = ft_clamp(vars.vr_dot, 0, 1);
				vars.vr_dot_pow = pow(vars.vr_dot, shape_intp.shape->material.shininess);
				add_on_rgb(rgb, shape_intp.shape->material.specular_ref, scene->lights[i], vars.vr_dot_pow);
			}
			i++;
		}
		clamp_mul_rgb(rgb, 255);
		return (true);
	}
	return (false);
}

static void	set_info(t_info *info, double max_dist, bool exit_once_found, bool output_needed)
{
	info->max_dist = max_dist;
	info->exit_once_found = exit_once_found;
	info->output_needed = output_needed;
}
