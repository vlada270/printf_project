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
int ft_help(char *str, int x)
{
    int start;
    int finish;

    start = ft_strchr(str, x) - str + 1;
    finish = ft_strrchr(str, x) - str + 1;
    return(finish - start);
}

char *ft_help_2(int len, char c)
{
    char *str;
    int i;

    i = 0;
    str = ft_memalloc(len); //освободить память
    while (i < len)
    {
        str[i] = c;
        i++;
    }
    return (str);
}

char * ft_search_length(char *str, int len)
{
    if (len > 1)
    {
        if (str[len - 1] == 'h')
        {
            if (ft_help(str, 'h') != 0)
                return(ft_help_2(2, 'h')); //освободить память
            else
               return(ft_help_2(1, 'h')); 
        }
        else if (str[len - 1] == 'l')
        {
            if (ft_help(str, 'l') != 0) 
               return(ft_help_2(2, 'l')); 
            else
               return(ft_help_2(1, 'l')); 
        }
    }
    return (NULL);
}

int ft_search_length_dop(char *str, int len)
{
    if (len > 1)
    {
        if (str[len - 1] == 'h')
        {
            if (ft_help(str, 'h') != 0)
                return(1); //hh
            else
               return(2); //h
        }
        else if (str[len - 1] == 'l')
        {
            if (ft_help(str, 'l') != 0) 
               return(3); // ll
            else
               return(4); // l
        }
    }
    return (0);
}

char *ft_formatting(int length, char str, va_list ap, int len)
{
    signed char hh;
    short int h;
    long int l;                     //нужно узнат есть ли в дальнейшем разница при преобразованиях 
    long long int ll;
    int x;

    if (lenghth == 0)
    {

    }


}


void ft_int(const char * format, char *str, va_list ap) // можно сделать функцию поиска str в общем предложении и заменить ее на то, что получится от преобразования и вернуть строчку 
{
    int x;
    int length;
    int len;
    char *s;

    //реализовать функцию, которая поможет узнать lenght
    len = (int)ft_strlen(str) - 1;
    length = ft_search_length_dop(str, len);
    //найдя длину мы посылаем в следующую функцию где преобразовываем под эту длину и делаем преобразования, сюда возвращаем то, что получилось, записанное в строчку
    printf("%d\n", length);
    printf("%s", str);
    //можно отформатировать строчку, чтобы убрать лишнее
    //formatting_str(&str, length, len);   сделать это в следующей функции то, о чем написанно выше и плюс проверка на валидность того, что написанно 
    s = ft_formatting(length, str, ap, len); // cделать две функции в одну отправляем signed в другую unsigned, если на конце стоит U
     //далее нам нужно распарсить str, чтобы узнать флаги и применить их 
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
    ft_printf("hello how are you %-.5lhd" , 365);
    return (0);
}
