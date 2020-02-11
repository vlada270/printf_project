/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thalfemp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:49:42 by thalfemp          #+#    #+#             */
/*   Updated: 2020/02/11 10:49:43 by thalfemp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct t_list
{
    char *data;
    char c;
    struct t_list *next;
}               s_list;

typedef struct x_list
{
    char *data;
    struct x_list *next; 
}               y_list;


int find_symbol(char *str, int start) //реализовать %%
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 'd' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' || 
        str[i] == 'x' || str[i] == 'X' || str[i] == 'f' || str[i] == 'c' 
        || str[i] == 's' || str[i] == 'p')
            return (i + start);
        i++;
    }
    return (-1);
}
void ft_int(const char * format, char *str, va_list ap) // скорее всего, нужно сделать ap через указатели, чтобы она изменялась
{
    int x;

    x = va_arg(ap, int); //далее нам нужно распарсить str, чтобы узнать флаги и применить их 
    printf("%d", x);

}
void ft_main(const char * format, int start, int finish, va_list ap) //изменить то, что возвращает функция
{
    char *str;
    char c;

    str = ft_strsub(format, (unsigned int)start, finish - start + 1); //можно перенести в другую функиц
    c = format[finish];
    if (c == 'd' || c == 'i')
        ft_int(format, str, ap);
    /*else if (c == 'f')
        ft_double(format, str, ap);
    else if (c == 'o' || c == 'u' || c == 'x' || c == 'X')
        ft_unsigned_int(format, str, ap);
    else if (c == 'c')
        ft_char(format, str, ap);
    else if (c == 's')
        ft_str(format, str, ap)
    else if (c == 'p')
        ft_pointer_to_void(format, str, ap);*/
    ft_strdel(&str);
}


char *get_type(const char * format, va_list ap)
{
    int i;
    int start;
    int finish;
    char *str;

    i = 0;
    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            start = i;
            if ((finish = find_symbol((char*)&format[start], start)) == -1)
                return (NULL);
            ft_main(format, start, finish, ap); //передаем в функцию которая узнает тип и исходя из типа достанет аргумент и будет преобразовывать 
            i = finish;
        }
        //можем записывать start or finish в структуру для каждого %, чтобы потом печатать пока не start, 
        //если start, то печатаем начиная со старта, то что мы получили после преобразования, после финиша 
        //опять печатаем символы до момента старта
        i++;
    }
    return ((char *)format);
}

int ft_printf(const char * restrict format, ...) //убрать ft_
{
    va_list ap;
    char *str;

    va_start(ap, format);
    str = get_type(format, ap);
//    printf("%s", str);
    va_end(ap);
    return (0);
}

int main()
{
    ft_printf("hello how are you %d" , 365);
    return (0);
}
