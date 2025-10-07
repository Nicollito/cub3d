#include "libft.h"
#include <string.h>
#include <errno.h>

void    print_error(char *msg)
{
    ft_putendl_fd("Error", 2);
    ft_putendl_fd(msg, 2);
}

void    ft_perror(void)
{
    ft_putendl_fd("Error", 2);
    strerror(errno);
}
