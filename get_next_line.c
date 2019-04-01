/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 23:29:59 by kmira             #+#    #+#             */
/*   Updated: 2019/03/30 18:01:58 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_bufs	*new_buffer(int fd, t_bufs **set)
{
	t_bufs	*result;

	result = malloc(sizeof(*result));
	ft_bzero(result->buffer, BUFF_SIZE + 1);
	result->next_buf = NULL;
	result->fd = fd;
	result->at = 0;
	*set = result;
	return (result);
}

int		calc_malloc_size_from(t_bufs *bufs)
{
	int		size;
	long	last;

	size = 0;
	while (bufs->next_buf && bufs->buffer[0] != '\0')
	{
		size += (BUFF_SIZE - bufs->at);
		bufs = bufs->next_buf;
	}
	last = ft_strchr(&(bufs->buffer)[bufs->at], '\n') \
							- &(bufs->buffer)[bufs->at];
	if (last >= 0)
		size = size + last;
	else
		size = size + ft_strlen(&(bufs->buffer)[bufs->at]);
	return (size);
}

void	copy_to_(char **line, t_bufs *bufs, int size)
{
	t_bufs	*prev;
	char	*line_head;

	*line = malloc(sizeof(**line) * (size + 1));
	line_head = *line;
	while (bufs->next_buf && bufs->buffer[0] != '\0')
	{
		*line = ft_memcpy_at(*line, &(bufs->buffer[bufs->at]), \
										(BUFF_SIZE - bufs->at));
		prev = bufs;
		bufs = bufs->next_buf;
		free(prev);
	}
	while ((bufs->buffer)[bufs->at] != '\0' && (bufs->buffer)[bufs->at] != '\n')
		(*(*line)++) = (bufs->buffer)[(bufs->at)++];
	line_head[size] = '\0';
	if ((bufs->buffer)[bufs->at] == '\n')
		(bufs->at)++;
	if ((bufs->buffer)[bufs->at] == '\0' && bufs->at < BUFF_SIZE && size > 0)
		bufs = NULL;
	*line = line_head;
}

t_bufs	*fetch_correct_buf(int fd, t_bufs **fetch_buf)
{
	t_bufs	*curr_buf;

	if (*fetch_buf == NULL)
		curr_buf = new_buffer(fd, fetch_buf);
	else
		curr_buf = NULL;
	return (curr_buf);
}

int		get_next_line(int fd, char **line)
{
	static t_bufs	*fetch_buf[MAX_FD];
	t_bufs			*curr_buf;
	int				size;

	if (line == NULL || read(fd, (fetch_buf[0])->buffer, 0) == -1 \
													|| BUFF_SIZE < 1)
		return (-1);
	curr_buf = fetch_correct_buf(fd, &fetch_buf[fd]);
	if (ft_strchr(&(fetch_buf[fd]->buffer)[(fetch_buf[fd])->at], '\n') == NULL)
	{
		if (curr_buf == NULL)
			curr_buf = new_buffer(fd, &(fetch_buf[fd])->next_buf);
		while ((size = read(fd, curr_buf->buffer, BUFF_SIZE)) > 0)
			if (ft_strchr(curr_buf->buffer, '\n') != NULL || size < BUFF_SIZE)
				break ;
			else
				curr_buf = new_buffer(fd, &curr_buf->next_buf);
	}
	copy_to_(line, (fetch_buf[fd]), calc_malloc_size_from(fetch_buf[fd]));
	if (curr_buf != NULL)
		fetch_buf[fd] = curr_buf;
	if (fetch_buf[fd]->buffer[0] != '\0' || *line[0] != '\0')
		return (1);
	return (0);
}
