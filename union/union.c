/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstoneho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:43:38 by mstoneho          #+#    #+#             */
/*   Updated: 2020/12/28 22:43:41 by mstoneho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**   Assignment name  : union
**   Expected files   : union.c
**   Allowed functions: write
**   ---------------------------------------------------------------------------
**
**   Write a program that takes two strings and displays, without doubles, the
**   characters that appear in either one of the strings.
**
**   The display will be in the order characters appear in the command line,
**   and will be followed by a \n.
**
**   If the number of arguments is not 2, the program displays \n.
**
**   Example:
**
**   $>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
**   zpadintoqefwjy$
**   $>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
**   df6vewg4thras$
**   $>./union "rien" "cette phrase ne cache rien" | cat -e
**   rienct phas$
**   $>./union | cat -e
**   $
**   $>
**   $>./union "rien" | cat -e
**   $
*/

#include <unistd.h>

void	print(char *str, char *ascii)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ascii[(int)str[i]])
		{
			write(1, &str[i], 1);
			ascii[(int)str[i]] = str[i];
		}
		i++;
	}
}

int		main(int argc, char *argv[])
{
	char ascii[127];

	if (argc == 3)
	{
		print(argv[1], ascii);
		print(argv[2], ascii);
	}
	write(1, "\n", 1);
	return (0);
}
