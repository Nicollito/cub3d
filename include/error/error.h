/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lserodon <lserodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:55:16 by nimadela          #+#    #+#             */
/*   Updated: 2025/11/13 13:32:32 by lserodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*---------------------error/---------------------*/

# include "cube.h"

void	rgb_error(char **color, char *line, char *tmp);
void	print_error(char *msg);
void	ft_error(t_cube *cube, char *msg) __attribute__((noreturn));

#endif