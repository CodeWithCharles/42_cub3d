/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaliszc <mkaliszc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:17:22 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/02/25 20:03:25 by mkaliszc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_checker(t_bool_format *checker)
{
	checker->d_texture = false;
	checker->e_texture = false;
	checker->f_colors = false;
	checker->c_colors = false;
	checker->w_texture = false;
	checker->s_texture = false;
	checker->n_texture = false;
	checker->all_texture_found = false;
	checker->wrong_param_found = false;
}

char	*fill_buffer(char *filename)
{
	char	*buffer;
	char	*line;
	char	*tmp;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: can't open the file", 2), NULL);
	buffer = get_next_line(fd);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n") == 0)
		{
			free(line);
			line = ft_strdup("_\n");
		}
		tmp = buffer;
		buffer = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (buffer);
}

void	set_bool_pain(bool *pain, char *line)
{
	if (line[3] != '\0')
		*pain = true;
}

void	set_bool_pain_2(bool *pain, char *line)
{
	if (line[2] != '\0')
		*pain = true;
}

void	set_bool_texture(char *line, t_bool_format *checker)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_bool_pain(&(checker->n_texture), line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_bool_pain(&(checker->s_texture), line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_bool_pain(&(checker->w_texture), line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_bool_pain(&(checker->e_texture), line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		set_bool_pain_2(&(checker->f_colors), line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		set_bool_pain_2(&(checker->c_colors), line);
	else if (ft_strncmp(line, "DO ", 3) == 0)
		set_bool_pain(&(checker->d_texture), line);
	else if (checker->wrong_param_found != true
		&& checker->all_texture_found == false)
	{
		checker->wrong_param_found = true;
		fd_printf(2, "Error: Wrong map param\n");
	}
}
