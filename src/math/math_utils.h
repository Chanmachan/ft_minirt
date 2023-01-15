/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:33:29 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/15 18:48:07 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

t_vec	init_vec(double x, double y, double z);
void	set_vec(t_vec *v, double x, double y, double z);
t_vec	add_vec(t_vec v1, t_vec v2);
t_vec	diff_vec(t_vec v1, t_vec v2);
t_vec	norm_vec(t_vec v);
double	inner_product(t_vec v1, t_vec v2);
double	abs_vec(t_vec v);
t_vec	constant_mul_vec(t_vec v, double c);

double	min(double x, double y);
double	max(double x, double y);
double	clamp(double f, double min, double max);
double	rand_range(double a, double b);

#endif