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

int ft_precision(char *str, int x)
{
    int precision;
    char *s;
    int len_x;

    if ((s = ft_strchr(str, '.')) != NULL)   
    {
        precision = ft_atoi(&str[s - str + 1]);  //можно проверить на отрицательность 
       // printf("preciion = %d\n", precision);
        len_x = ft_len_num(x); // чтобы понять что нам нужно добавлять нули мы можем записать в число количество нулей которое нам нужно добавить и вернуть его же если нужно 
        if (x < 0)
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
    if (c == '0')
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
        || str[i] == '+')
    {
        x = ft_flags_help(str[i]);
        i++;
        if (str[i] == '0' || str[i] == '-' || str[i] == ' '   //если будет больше флагов, то заменим на while
        || str[i] == '+')
            x = x * 10 + ft_flags_help(str[i]);
    }
    //printf("flags - %d\n", x);
    return (x);
}

int ft_width(char *str, int flags, int x, int n_of_z)
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
    //printf("%c", str[num_of_flags]);
    if (str[num_of_flags] >= '0' && str[num_of_flags] <= '9')
    {
        y = ft_atoi(&str[num_of_flags]);
        len_x = ft_len_num(x) + n_of_z;
        if (len_x < y)
            return (y - len_x);
    }
    return (0);
}

void ft_printf_d_help_3(int x, int number_of_zeros, int number_of_spaces)
{
    int i;

    i = 0;
    if (x < 0)
    {
        write(1, "-", 1);
        x *= -1;
    }
    while (i != number_of_zeros)
    {
        write(1, "0", 1);
        i++;
    }
    ft_putnbr(x);
    i = 0; 
    while (i != number_of_spaces)
    {
        write(1, " ", 1);
        i++;
    }   
}

void ft_printf_d_help_main(int x, int number_of_zeros, int number_of_spaces, int flags)
{
    int i;

    i = 0;
    while (i != number_of_spaces)
    {
        write(1, " ", 1);
        i++;
    }
    i = 0;
    if (x > 0 && flags == 5)
        write(1, "+", 1);
    else if (x < 0)
    {
        write(1, "-", 1);
        x *= -1;
    }
    while (i != number_of_zeros)
    {
        write(1, "0", 1);
        i++;
    }
    ft_putnbr(x);
}

void ft_printf_d_help(int x, int number_of_zeros, int number_of_spaces, int flags)
{
    if (flags == 3)
       ft_printf_d_help_3(x, number_of_zeros, number_of_spaces);
    else 
       ft_printf_d_help_main(x, number_of_zeros, number_of_spaces, flags);
}

void ft_printf_d_1(int x, int number_of_zeros, int number_of_spaces, int flags) //ситуация когда флаг один 
{
    if (flags == 2 && number_of_zeros == 0 && number_of_spaces > 0) 
    {
        number_of_zeros = number_of_spaces;
        number_of_spaces = 0;
    }
    else if (flags == 4 && x >= 0 && number_of_spaces == 0)
        number_of_spaces = 1;
    else if (flags == 5 && x >= 0 && number_of_spaces > 0)
        number_of_spaces -= 1;
    ft_printf_d_help(x, number_of_zeros, number_of_spaces, flags);
}

void ft_printf_d_2_minus(int x, int number_of_zeros, int number_of_spaces, int flags)
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
    ft_putnbr(x);
    i = 0; 
    while (i != number_of_spaces)
    {
        write(1, " ", 1);
        i++;
    }   
}

void ft_printf_d_help_2(unsigned int x, int number_of_zeros, int number_of_spaces, int flags)
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
    ft_putnbr(x);
}

void ft_printf_d_2(int x, int number_of_zeros, int number_of_spaces, int flags)
{
    if ((flags == 25 || flags == 52) && number_of_spaces > 0)
    {
        if (x >= 0)
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
        if (x >= 0 && number_of_spaces > 0) // в функции печати просто перед всем печатаем плюс
            number_of_spaces -= 1;
        else if (x < 0)
        {
           ft_printf_d_1(x, number_of_zeros, number_of_spaces, 3);
           return ;
        }
    }
    else if ( flags == 34 || flags == 43)
    {
        if (x >= 0 && number_of_spaces > 0) //в функции печати просто перед всем печатаем пробел также как с плюсом, а ширину отправляем вправо
           number_of_spaces -= 1;
        else if (x < 0)
        {
            ft_printf_d_1(x, number_of_zeros, number_of_spaces, 3);
            return ;
        }
    }
    ft_printf_d_help_2(x, number_of_zeros, number_of_spaces, flags);
}

void ft_d(int x, int len, char *str) //для x можно сделать тип long long int чтобы любые числа могли уместиться 
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
    //printf(" number_of_zeros - %d\n", number_of_zeros);              //для реализации точности можно сделать поиск в str точки, если точка есть то берем число после точки
    //printf(" number_of_spaces - %d\n", number_of_spaces); 
//    printf("size - %ld\n", sizeof(x));   // реализуем точность с помощью поиска в нашей строке . и запищем местоположение точки в нашей стрчке после будем работать с тем что до этого местоположения те там должны стять ширина или флаг
}

void ft_char(signed char x, int len, char *str)
{
    printf("hhd - %hhd\n", x);
    printf("size - %ld\n", sizeof(x));
}

void ft_short_int(short int x, int len, char *str)
{
    printf("hd - %hd\n", x);
    printf("size - %ld\n", sizeof(x));
}

void ft_long_long(long long int x, int len, char *str)
{
    printf("lld - %lld\n", x);
    printf("size - %ld\n", sizeof(x));
}

void ft_long(long int x, int len, char *str)
{
    printf("ld - %ld\n", x);
    printf("size - %ld\n", sizeof(x));
}

void ft_formatting(int length, char *str, va_list ap, int len) // использую тип char* потому что хочу перевести в дальнейшем в строчку, чтобы не было проблем с размером возвращаемых данных, но можно использовать void*
{                   
    if (length == 0) //d
        ft_d(va_arg(ap, int), len, str);//функция преобразования
    else if (length == 1) //hh
        ft_char((signed char)va_arg(ap, int), len, str); // функция преобразования
    else if (length == 2) //h
        ft_short_int((short int)va_arg(ap, int), len, str);
    else if (length == 3) //ll
        ft_long_long(va_arg(ap, long long int), len, str);
    else if (length == 4) //l
        ft_long(va_arg(ap, long int), len, str);

}


void ft_int(const char * format, char *str, va_list ap) // можно сделать функцию поиска str в общем предложении и заменить ее на то, что получится от преобразования и вернуть строчку 
{
    int x;
    int length;
    int len;
//    char *s;

    //реализовать функцию, которая поможет узнать lenght
    len = (int)ft_strlen(str) - 1;
    length = ft_search_length_dop(str, len);
    //найдя длину мы посылаем в следующую функцию где преобразовываем под эту длину и делаем преобразования, сюда возвращаем то, что получилось, записанное в строчку
    //printf("%d\n", length);
    //printf("%s", str);
    //можно отформатировать строчку, чтобы убрать лишнее
    //formatting_str(&str, length, len);   сделать это в следующей функции то, о чем написанно выше и плюс проверка на валидность того, что написанно 
    ft_formatting(length, str, ap, len); // cделать две функции в одну отправляем signed в другую unsigned, если на конце стоит U
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
    ft_printf("%0+100.20d" , 5);
    printf("\n");
    printf("%0+100.20d\n" , 5); 
    return (0);
}
