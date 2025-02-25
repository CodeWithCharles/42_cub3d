/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:04:13 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/22 18:30:32 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSING_H
# define PARSING_H

typedef struct s_bool_format
{
	bool	all_texture_found;
	bool	wrong_param_found;
	bool	n_texture;
	bool	s_texture;
	bool	w_texture;
	bool	e_texture;
	bool	f_colors;
	bool	c_colors;
	bool	d_texture;
}	t_bool_format;

#endif