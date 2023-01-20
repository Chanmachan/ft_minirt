/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:11:35 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 17:33:13 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include "draw.h"
#include "color.h"
#include <math.h>
#include <stdio.h>

bool	raytrace(const t_scene *scene, const t_ray *eye_ray, t_rgb *rgb)
{
	t_shape		*shape;
	t_intersect	intp;
	t_light		*light;
	t_raytrace	vars;

	if (get_nearest_shape(scene, eye_ray, INFINITY, false, &shape, &intp))
	{
		rgb->r = scene->ambient_illuminance.r * shape->material.ambient_ref.r;
		rgb->g = scene->ambient_illuminance.g * shape->material.ambient_ref.g;
		rgb->b = scene->ambient_illuminance.b * shape->material.ambient_ref.b;
		light = scene->light;
		while (light != NULL)
		{
			if (light->type == LT_POINT)
			{
				vars.l = norm_vec(diff_vec(light->vector, \
											intp.position));
				vars.dl = abs_vec(diff_vec(light->vector, \
											intp.position)) - C_EPSILON;
			}
			else if (light->type == LT_DIRECTIONAL)
			{
				vars.l = norm_vec(constant_mul_vec(\
									light->vector, -1));
				vars.dl = INFINITY;
			}
			vars.shadow_ray.start = add_vec(intp.position, constant_mul_vec(vars.l, C_EPSILON));
			vars.shadow_ray.direction = vars.l;
			if (get_nearest_shape(scene, &vars.shadow_ray, vars.dl, true, NULL, NULL))
			{
				light = light->next;
				continue ;
			}
			vars.nl_dot = inner_product(intp.normal, vars.l);
			vars.nl_dot = clamp(vars.nl_dot, 0, 1);
			add_on_rgb(rgb, shape->material.diffuse_ref, *light, vars.nl_dot);
			if (vars.nl_dot > 0)
			{
				vars.r = norm_vec(diff_vec(constant_mul_vec(\
									intp.normal, 2 * vars.nl_dot), vars.l));
				vars.v = norm_vec(constant_mul_vec(\
										eye_ray->direction, -1));
				vars.vr_dot = inner_product(vars.v, vars.r);
				vars.vr_dot = clamp(vars.vr_dot, 0, 1);
				vars.vr_dot_pow = pow(vars.vr_dot, shape->material.shininess);
				add_on_rgb(rgb, shape->material.specular_ref, *light, vars.vr_dot_pow);
			}
			light = light->next;
		}
		rgb->r = 255 * clamp(rgb->r, 0, 1);
		rgb->g = 255 * clamp(rgb->g, 0, 1);
		rgb->b = 255 * clamp(rgb->b, 0, 1);
		return (true);
	}
	return (false);
}
