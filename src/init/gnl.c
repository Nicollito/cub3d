#include "libft.h"

static int	loop_gnl(char *buffer, char *res, int fd)
{
	int			b_read;
	char		*tmp;

	while (!ft_strchr(res, '\n'))
	{
		b_read = read(fd, buffer, 10);
		if (b_read == -1)
			return (1);
		if (!b_read)
			break ;
		tmp = res;
		res = ft_strjoin(tmp, buffer);
		if (tmp)
			free(tmp);
		if (!res)
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[11];
	char		*res;
	char		*end_line;

	res = ft_strdup(buffer);
	if (!res && ft_strlen(buffer))
		return (NULL);
	ft_bzero(buffer, 11);
	if (loop_gnl(buffer, res, fd))
		return (NULL);
	end_line = ft_strchr(res, '\n');
	if (end_line)
		end_line++;
	ft_strcpy(end_line, buffer);
	if (end_line)
		*end_line = '\0';
	return (res);
}
