/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thalfemp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:49:42 by thalfemp          #+#    #+#             */
/*   Updated: 2020/02/26 11:55:27 by thalfemp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include "printf_project/libft/libft.h"

char	*ft_itoa_base(int value, int base);
char            *ft_itoa_long(long long int n);

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
int ft_len_num(int n)
{
    int i;

    i = 0;
    if (n == 0)
        return (1);
    if (n < 0)
    {
        i++;
        n *= -1;
    }
    while ( n != 0)
    {
        n = n / 10;
        i++;
    }
    return(i);
}

int ft_precision(char *str, char *x)
{
    int precision;
    char *s;
    int len_x;

    if ((s = ft_strchr(str, '.')) != NULL)   
    {
        precision = ft_atoi(&str[s - str + 1]);  //можно проверить на отрицательность 
        len_x = ft_strlen(x);
        if (x[0] == '-')
            len_x--;
        if (len_x >= precision)
            return (0);       
        else
            return (precision - len_x);
    }
    return (0);

}
int ft_flags_help(char c)
{
    if (c == '#')
        return (1);
    else if (c == '0') //сделать #
        return (2);
    else if (c == '-')
        return (3);
    else if (c == ' ')
        return (4);
    else
        return (5);
}

int ft_flags(char *str)
{
    int x;
    int i;

    i = 0;
    x = 0;
    if (str[i] == '0' || str[i] == '-' || str[i] == ' '
        || str[i] == '+' || str[i] == '#')
    {
        x = ft_flags_help(str[i]);
        i++;
        if (str[i] == '0' || str[i] == '-' || str[i] == ' '   //если будет больше флагов, то заменим на while
        || str[i] == '+' || str[i] == '#') 
            x = x * 10 + ft_flags_help(str[i]);
    }
    //printf("flags - %d\n", x);
    return (x);
}

int ft_width(char *str, int flags, char *x, int n_of_z)
{
    int num_of_flags;
    int y;
    int len_x;

    num_of_flags = 0;
    y = 0;
    if (flags > 10)
        num_of_flags = 2;
    else if (flags > 0 && flags < 10)
        num_of_flags = 1;
    if (str[num_of_flags] >= '0' && str[num_of_flags] <= '9')
    {
        y = ft_atoi(&str[num_of_flags]);
        len_x = ft_strlen(x) + n_of_z;
        if (len_x < y)
            return (y - len_x);
    }
    return (0);
}

void ft_printf_d_help_3(char *x, int number_of_zeros, int number_of_spaces)
{
    int i;

    i = 0;
    if (x[0] == '-')
    {
        write(1, "-", 1);
        x = &x[1];
    }
    while (i != number_of_zeros)
    {
        write(1, "0", 1);
        i++;
    }
    ft_putstr(x);
    i = 0; 
    while (i != number_of_spaces)
    {
        write(1, " ", 1);
        i++;
    }   
}

void ft_printf_d_help_main(char *x, int number_of_zeros, int number_of_spaces, int flags)
{
    int i;

    i = 0;
    while (i != number_of_spaces)
    {
        write(1, " ", 1);
        i++;
    }
    i = 0;
    if (x[0] != '-' && flags == 5)
        write(1, "+", 1);
    else if (x[0] == '-')
    {
        write(1, "-", 1);
        x = &x[1];
    }
    while (i != number_of_zeros)
    {
        write(1, "0", 1);
        i++;
    }
    ft_putstr(x);
}

void ft_printf_d_help(char * x, int number_of_zeros, int number_of_spaces, int flags)
{
    if (flags == 3)
       ft_printf_d_help_3(x, number_of_zeros, number_of_spaces);
    else 
       ft_printf_d_help_main(x, number_of_zeros, number_of_spaces, flags);
}

void ft_printf_d_1(char *x, int number_of_zeros, int number_of_spaces, int flags) //ситуация когда флаг один 
{
    if (flags == 2 && number_of_zeros == 0 && number_of_spaces > 0) 
    {
        number_of_zeros = number_of_spaces;
        number_of_spaces = 0;
    }
    else if (flags == 4 && x[0] != '-' && number_of_spaces == 0)
        number_of_spaces = 1;
    else if (flags == 5 && x[0] != '-' && number_of_spaces > 0)
        number_of_spaces -= 1;
    ft_printf_d_help(x, number_of_zeros, number_of_spaces, flags);
}

void ft_printf_d_2_minus(char *x, int number_of_zeros, int number_of_spaces, int flags)
{
    int i;

    i = 0;
    if (flags == 35 || flags == 53)
        write(1, "+", 1);
    else if (flags == 34 || flags == 43)
        write(1, " ", 1); 
    while (i != number_of_zeros)
    {
        write(1, "0", 1);
        i++;
    }
    ft_putstr(x);
    i = 0; 
    while (i != number_of_spaces)
    {
        write(1, " ", 1);
        i++;
    }   
}

void ft_printf_d_help_2(char *x, int number_of_zeros, int number_of_spaces, int flags)
{
    int i;

    i = 0;
    if (flags == 35 || flags == 53 || flags == 34 || flags == 43)
    {
       ft_printf_d_2_minus(x, number_of_zeros, number_of_spaces, flags);
       return ;
    }
    while (i != number_of_spaces)
    {
        write(1, " ", 1);
        i++;
    }
    i = 0;
    if (flags == 25 || flags == 52)
        write(1, "+", 1);
    while (i != number_of_zeros)
    {
        write(1, "0", 1);
        i++;
    }
    ft_putstr(x);
}

void ft_printf_d_2(char *x, int number_of_zeros, int number_of_spaces, int flags)
{
    if ((flags == 25 || flags == 52) && number_of_spaces > 0)
    {
        if (x[0] != '-')
        {
            number_of_spaces -= 1;
            if (number_of_zeros == 0 && number_of_spaces > 0)
            {
               number_of_zeros = number_of_spaces;
               number_of_spaces = 0; 
            }
        }
        else
        { 
            ft_printf_d_1(x, number_of_zeros, number_of_spaces, 2);
            return ;
        }
    }
    else if (flags == 35 || flags == 53)
    {
        if (x[0]!= '-' && number_of_spaces > 0) // в функции печати просто перед всем печатаем плюс
            number_of_spaces -= 1;
        else if (x[0] == '-')
        {
           ft_printf_d_1(x, number_of_zeros, number_of_spaces, 3);
           return ;
        }
    }
    else if (flags == 34 || flags == 43)
    {
        if (x[0] != '-' && number_of_spaces > 0) //в функции печати просто перед всем печатаем пробел также как с плюсом, а ширину отправляем вправо
           number_of_spaces -= 1;
        else if (x[0] == '-')
        {
            ft_printf_d_1(x, number_of_zeros, number_of_spaces, 3);
            return ;
        }
    }
    ft_printf_d_help_2(x, number_of_zeros, number_of_spaces, flags);
}

void ft_d_or_i(char *x, char *str) //для x можно сделать тип long long int чтобы любые числа могли уместиться 
{
    int number_of_zeros;
    int number_of_spaces;
    int flags; //1 - # 2 -0 3 - '-' 4 - ' ' 5 - '+'

    number_of_zeros = ft_precision(str, x);
    flags = ft_flags(&str[1]);
    number_of_spaces = ft_width(&str[1], flags, x, number_of_zeros);
    if (flags >= 0 && flags <= 5)
        ft_printf_d_1(x, number_of_zeros, number_of_spaces, flags); //функция с оодним флагом, нужно создать функцию с двумя флагами
    else
       ft_printf_d_2(x, number_of_zeros, number_of_spaces, flags);     
}


void ft_formatting(int length, char *str, va_list ap) 
{                   
    char *s;

    if (length == 0) //d
       s = ft_itoa(va_arg(ap, int));//функция преобразования
    else if (length == 1) //hh
       s = ft_itoa((signed char)va_arg(ap, int));// функция преобразования
    else if (length == 2) //h
       s = ft_itoa((short int)va_arg(ap, int));
    else if (length == 3) //ll
       s = ft_itoa_long(va_arg(ap, long long int));  //сделать итоа для long long
    else if (length == 4) //l
       s = ft_itoa(va_arg(ap, long int));
    ft_d_or_i(s, str);
    ft_strdel(&s);
}

char *ft_str_to_lower(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 65 && str[i] <= 90)
            str[i] = str[i] + 32;
        i++;
    }
    return (str);
}
void ft_oux(char *x, char *str, char type)
{
    int flags; //1 - # 2 -0 3 - '-' 4 - ' ' 5 - '+'

    flags = ft_flags(&str[1]);
    if ((type == 'o') && (flags == 1 || flags == 13 || flags == 31 
        || flags == 12 || flags == 21))
        x = ft_strjoin("0", x);
    else if ((type == 'x' || type == 'X') && (flags == 1 || flags == 13 || flags == 31 
        || flags == 12 || flags == 21))
        x = ft_strjoin("0x", x);
    ft_d_or_i(x, str);        
}

void ft_create_str(unsigned long long int x, char c, char *str)
{
    char *s;

    if (c == 'o')
        s = ft_itoa_base(x, 8);
    else if (c == 'u')
        s = ft_itoa_base(x, 10);
    else if (c == 'x')
    {
        s = ft_itoa_base(x, 16);
        s = ft_str_to_lower(str);    
    }
    else if (c == 'X')
        s = ft_itoa_base(x, 16);
    ft_oux(s, str, c);
}
void ft_formatting_unsigned(int length, char *str, va_list ap, char c) 
{                   
    if (length == 0) //ouxX
       ft_create_str(va_arg(ap, unsigned int), c, str);//функция преобразования
    else if (length == 1) //hh
       ft_create_str((unsigned char)va_arg(ap, int), c, str);// функция преобразования
    else if (length == 2) //h
       ft_create_str((unsigned short)va_arg(ap, int), c, str);
    else if (length == 3) //ll:w

       ft_create_str(va_arg(ap, unsigned long long int), c, str);  //сделать итоа для long long
    else if (length == 4) //l
       ft_create_str(va_arg(ap, unsigned long int), c, str);
}

void ft_int(const char * format, char *str, va_list ap, char c) // можно сделать функцию поиска str в общем предложении и заменить ее на то, что получится от преобразования и вернуть строчку 
{
    int x;
    int length;
    int len;

    len = (int)ft_strlen(str) - 1;
    length = ft_search_length_dop(str, len);
    if (c == 'd' || c == 'i' )
        ft_formatting(length, str, ap); // cделать две функции в одну отправляем signed в другую unsigned, если на конце стоит U
    else if (c == 'o' || c == 'u' || c == 'x' || c == 'X')
        ft_formatting_unsigned(length, str, ap, c); 
}

void ft_main(const char * format, int start, int finish, va_list ap) //изменить то, что возвращает функция
{
    char *str;
    char c;

    str = ft_strsub(format, (unsigned int)start, finish - start + 1); //можно перенести в другую функиц
    c = format[finish];
    if (c == 'd' || c == 'i' || c == 'o' || c == 'u' || c == 'x' || c == 'X')
        ft_int(format, str, ap, c);
    /*else if (c == 'f')
        ft_double(format, str, ap);
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
    long long  x = 100000000000;
    int y = 0xFF;
    
    ft_printf("%#100.20X" , y);
    printf("\n");
    printf("%#100.20X\n" , y); 
    return (0);
}
