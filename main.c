#include <libc.h>
   
   void    *ft_calloc(size_t count, size_t size)
{
    size_t    i;
    size_t    l;
    char    *y;

    if ((int)count < 0 && (int)size < 0)
        return (NULL);
    i = 0;
    y = malloc(count * size);
    if (!y)
        return (NULL);
    l = count * size;
    while (i < l)
    {
        y[i] = 0;
        i++;
    }
    return ((void *)y);
}
   
    int main ()
{
    {
        if (!ft_calloc(-2147483648,-2147483648))
            printf ("alo\n");
    }
}