/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:31:19 by gribeiro          #+#    #+#             */
/*   Updated: 2025/05/06 21:36:22 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_phil	phil;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid Argument(s).\n", 21), 1);
	if (!init_phil(&phil, argv))
		return (1);
	return (0);
}
