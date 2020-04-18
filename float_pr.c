#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

float range_of_two_max(float x)
{
    float t1;

    t1 = 1.0;
    if (x > 0 && x < 1)
    {
        while (x <= t1)
            t1 = t1 / 2;
        t1 *= 2;
    }
    else
    {
        while (x > t1)
        t1 *= 2;
    }
    return(t1);
}


int *ft_from_10_to_2(int m)
{
    int *mantissa;
    int t;

    t = 0;
    if (!(mantissa = (int*)malloc(sizeof(int) * 23)))
        return(0);
    while (t != 23)
    {
        mantissa[t] = 0;
        t++;
    }
    t = 22;
    while (m != 0)
    {
        mantissa[t] = m % 2;
        m = m / 2;
        t--;
    }
    return(mantissa);
}

float float_ans(int a, int *mantissa, float e, int minus)
{
    long double x;
    double ans;
    int i;
    long double two;
    long double delme;
    double del_e;

    two = (double)1/2; 
    i = 0;
    x = 0;
    while (i != 23)
    {
        x = x + (mantissa[i] * two); 
        two = two / 2;
        i++;
    }
    ans = x + 1;
    ans *= e; //проблема здесь в подсчете экспоненты
    if (minus == 1)
        ans *= -1;
    free(mantissa);
    return (ans);
}
int              len(long long nb)
{
        int len;

        len = 0;
        if (nb < 0)
        {
                nb = nb * (-1);
                len++;
        }
        if (nb >= 0 && nb <= 9)
        {
                len++;
                return (len);
        }
        while (nb != 0)
        {
                nb = nb / 10;
                len++;
        }
        return (len);
}

unsigned long long int ft_power_of_ten(int precision)
{
    unsigned long long int x;

    x = 1;
    while (precision != 0)
    {
        x *= 10;
        precision--;
    }
    return (x);
}

void  ft_create_str(char *flt, int precision, int lng, long double m)
{
    int x;
    unsigned long long int x1;
    unsigned long long int prcsn;
    float del = 56.22;

    prcsn = ft_power_of_ten(precision);
    m = m * prcsn;
    //x1 = (unsigned long long int)(m + 0.5);
    printf("%lld\n", x1);
    printf("%.22f\n", del);
}
void create_str(char *str, long double m)
{
    int precision;
    char *s;
    int lng;
    char *flt;
    
    lng = (int)m;
    if ((s = ft_strchr(str, '.')) != NULL)
        precision = ft_atoi(&str[s - str + 1]); 
    else
        precision = 6;
    lng = len(lng);
    flt = ft_strnew(precision+lng+2);
    ft_create_str(flt, precision, lng, m); //записываем сначала целую часть потом убираем ее, умножаем на precision*10 и переводим в int, те и сразу округляется
}

void get_presicion(float x)
{
    float range_max;
    float range_min;
    long double m;
    int *mantissa;
    int minus;

    minus = 0;
    if (x < 0)
    {
        minus = 1;
        x = x * -1;
    }
    range_max = range_of_two_max(x);
    range_min = range_max / 2; 
    m = (double)(x - range_min) / (range_max - range_min);
    mantissa = ft_from_10_to_2((int)(8388608 * m));
    m = float_ans(x, mantissa, range_min, minus);
    create_str("%.17f", m);
}



int main(void)
{
    float x = 56.22;
    float t = 56.22;

    //printf("%.20f\n", t);
    get_presicion(x);  //реализовать вывод не используя принтф с точностью и округлением 
                        //один из вариантов перевод в строчку 
}

//когда есть точность то записываем строчку с размером нашей тончности 
//если нет точности то пишем 5 знаков так как выводим пять