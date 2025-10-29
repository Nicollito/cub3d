/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:19 by nimadela          #+#    #+#             */
/*   Updated: 2025/10/29 14:56:20 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include <stdlib.h>
# include "cube.h"
# include "libft.h"

void	free_tab(char **tab);
void	free_tmp_map(t_list *tmp_map);
void	free_cube(t_cube *cube);

#endif