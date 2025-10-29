/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:55:16 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:55:17 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*---------------------error/---------------------*/

// error.c

void	print_error(char *msg);
void	ft_perror(void);
void	ft_error(t_cube *cube, char *msg);

#endif