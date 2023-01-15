/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:32:57 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:48:07 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_vec	init_vec(double x, double y, double z);
t_vec	add_vec(t_vec v1, t_vec v2);
t_vec	diff_vec(t_vec v1, t_vec v2);
t_vec	norm_vec(t_vec v);
double	inner_product(t_vec v1, t_vec v2);
double	abs_vec(t_vec v);
t_vec	constant_mul_vec(t_vec v, double c);

t_vec	init_vec(double x, double y, double z)
{
	return ((t_vec){
		.x = x,
		.y = y,
		.z = z
	});
}

void	set_vec(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vec	add_vec(t_vec v1, t_vec v2)
{
	return ((t_vec){
		.x = v1.x + v2.x,
		.y = v1.y + v2.y,
		.z = v1.z + v2.z
	});
}

t_vec	diff_vec(t_vec v1, t_vec v2)
{
	return ((t_vec){
		.x = v1.x - v2.x,
		.y = v1.y - v2.y,
		.z = v1.z - v2.z
	});
}

t_vec	norm_vec(t_vec v)
{
	double	norm;

	norm = sqrt(abs_vec(v));
	return ((t_vec){
		.x = v.x / norm,
		.y = v.y / norm,
		.z = v.z / norm
	});
}

double	inner_product(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	abs_vec(t_vec v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec	constant_mul_vec(t_vec v, double c)
{
	return ((t_vec){
		.x = c * v.x,
		.y = c * v.y,
		.z = c * v.z
	});
}