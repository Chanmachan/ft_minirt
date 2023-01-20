/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:07:56 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 11:15:58 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "hook.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_env		env;

	if (argc != 2)
	{
		perror("not valid argc");
		return (RETURN_FAILURE);
	}
	init_scene(&env, argv[1]);
	init_mlx(&env);
	setup_hook(&env);
}
