/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:17:22 by mkaliszc          #+#    #+#             */
/*   Updated: 2025/03/24 15:58:17 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	checker->map_found = false;
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
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\0' && i != ft_strlen(line))
		*pain = true;
}

void	set_bool_texture(char *line, t_bool_format *checker)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		set_bool_pain(&(checker->n_texture), line + 2);
	else if (ft_strncmp(line, "SO", 2) == 0)
		set_bool_pain(&(checker->s_texture), line + 2);
	else if (ft_strncmp(line, "WE", 2) == 0)
		set_bool_pain(&(checker->w_texture), line + 2);
	else if (ft_strncmp(line, "EA", 2) == 0)
		set_bool_pain(&(checker->e_texture), line + 2);
	else if (line[0] == 'F')
		set_bool_pain(&(checker->f_colors), line + 1);
	else if (line[0] == 'C')
		set_bool_pain(&(checker->c_colors), line + 1);
	else if (ft_strncmp(line, "DO", 2) == 0)
		set_bool_pain(&(checker->d_texture), line + 2);
	else if (checker->wrong_param_found != true
		&& checker->all_texture_found == false)
		checker->wrong_param_found = true;
}

void	set_texture(t_tex_ctx *textures, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		textures->north_path = ft_strdup(skip_space(line + 2));
	else if (ft_strncmp(line, "SO", 2) == 0)
		textures->south_path = ft_strdup(skip_space(line + 2));
	else if (ft_strncmp(line, "WE", 2) == 0)
		textures->west_path = ft_strdup(skip_space(line + 2));
	else if (ft_strncmp(line, "EA", 2) == 0)
		textures->east_path = ft_strdup(skip_space(line + 2));
	else if (ft_strncmp(line, "F", 1) == 0)
		textures->floor = ft_strdup(skip_space(line + 1));
	else if (ft_strncmp(line, "C", 1) == 0)
		textures->ceiling = ft_strdup(skip_space(line + 1));
	else if (ft_strncmp(line, "DO", 2) == 0)
		textures->door_path = ft_strdup(skip_space(line + 2));
}
