/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:53 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/13 13:37:16 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_config(t_cube *cube, char *line)
{
	if (is_empty_line(line))
		return ;
	else if (is_texture_line(line))
		parse_texture(cube, line);
	else if (is_color_line(line))
		parse_color_line(cube, line);
	else
	{
		free(line);
		ft_error(cube, "Invalid line in .cub file");
	}
}
