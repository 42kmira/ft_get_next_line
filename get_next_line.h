/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmira <kmira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 23:29:29 by kmira             #+#    #+#             */
/*   Updated: 2019/03/30 19:13:44 by kmira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <stdio.h>

# define BUFF_SIZE 8
# define MAX_FD 5200

typedef struct		s_buf
{
	int				fd;
	int				at;
	char			buffer[BUFF_SIZE + 1];
	struct s_buf	*next_buf;
	struct s_buf	*next_fd;
}					t_bufs;

int					get_next_line(int fd, char **line);
t_bufs				*new_buffer(int fd, t_bufs **set);
void				copy_to_(char **line, t_bufs *bufs, int size);
int					calc_malloc_size_from(t_bufs *bufs);

#endif
