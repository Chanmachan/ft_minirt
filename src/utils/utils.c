/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:10:14 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 13:06:15 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_scene(t_scene *scene)
{
	t_shape	*tmp_shape;
	t_light	*tmp_light;

	if (scene == NULL)
		return ;
	while (scene->shape != NULL)
	{
		tmp_shape = scene->shape->next;
		free(scene->shape);
		scene->shape = tmp_shape;
	}
	while (scene->light != NULL)
	{
		tmp_light = scene->light->next;
		free(scene->light);
		scene->light = tmp_light;
	}
	free(scene);
}
