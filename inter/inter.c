/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstoneho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:43:46 by mstoneho          #+#    #+#             */
/*   Updated: 2020/12/28 22:43:48 by mstoneho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   Assignment name  : inter
**   Expected files   : inter.c
**   Allowed functions: write
**   ---------------------------------------------------------------------------
**
**   Write a program that takes two strings and displays, without doubles, the
**   characters that appear in both strings, in the order they appear in the
**   first one.
**
**   The display will be followed by a \n.
**
**   If the number of arguments is not 2, the program displays \n.
**
**   Examples:
**
**   $>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
**   padinto$
**   $>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
**   df6ewg4$
**   $>./inter "rien" "cette phrase ne cache rien" | cat -e
**   rien$
**   $>./inter | cat -e
**   $
*/

#include <unistd.h>

int	main(int argc, char *argv[])
{
	int		i;
	int		j;
	char	ascii[127];

	i = 0;
	while (argc == 3 && argv[1][i] != '\0')
	{
		j = 0;
		while (argv[2][j] != '\0')
		{
			if (argv[1][i] == argv[2][j] &&
										ascii[(int)argv[1][i]] != argv[1][i])
			{
				write(1, &argv[1][i], 1);
				ascii[(int)argv[1][i]] = argv[1][i];
			}
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
