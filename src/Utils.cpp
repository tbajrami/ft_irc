/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbajrami <tbajrami@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:38:14 by tbajrami          #+#    #+#             */
/*   Updated: 2021/05/17 15:38:12 by tbajrami         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ftirc.hpp"

int	ft_atoi(const char *str)
{
    int	i;
    int	s;
    int nb;

    i = 0;
    s = 1;
    nb = 0;
    while (str[i] == ' ' || str[i] == '\t'
           || str[i] == '\n' || str[i] == '\f'
           || str[i] == '\r' || str[i] == '\v')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            s = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        nb = nb * 10 + (str[i] - '0');
        i++;
    }
    return (s * nb);
}

void	ft_bzero(void *s, size_t n)
{
    unsigned char	*str;
    size_t			i;

    i = 0;
    str = (unsigned char *)s;
    while (i < n)
    {
        *str = 0;
        str++;
        i++;
    }
}

int ft_isalpha(const char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return (1);
    else
        return (0);
}

int ft_isnum(const char c)
{
    if (c >= 48 && c <= 57)
        return (1);
    else
        return (0);
}

size_t  ft_strlen(const char *src) 
{
    size_t i = 0;

    while (src[i])
        i++;
    return i;
}

size_t  ft_strlcpy(char *dst, const char *src, size_t size)
{
    size_t  i;

    if (!dst || !src)
        return (0);
    i = 0;
    if (size == 0)
        return (ft_strlen(src));
    while (i < size - 1 && src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (ft_strlen(src));
}

std::string ft_utoa(unsigned int n)
{
    if (n == 0)
        return (std::string("0"));
    std::string str;
    size_t i = n;
    while (i)
    {
        str.insert(str.begin(), (i % 10) + 48);
        i /= 10;
    }
    return (str);
}

std::string ft_format_cmd(std::string cmd)
{
    while (cmd.size() < 3)
        cmd.insert(cmd.begin(), '0');
    return (cmd);
}

std::string ft_current_time(void)
{
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    return(asctime(timeinfo));

}

std::string ft_uptime(time_t &launch_time)
{
    time_t rawtime;
    struct tm * c_time;
    struct tm *l_time;

    time (&rawtime);
    c_time = localtime (&rawtime);
    l_time = localtime(&launch_time);
    c_time->tm_hour -=  l_time->tm_hour;
    c_time->tm_mday -=  l_time->tm_mday;
    c_time->tm_min -=   l_time->tm_min;
    c_time->tm_sec -=   l_time->tm_sec;

std::cout << "tm_sec : " << l_time->tm_sec << "\n";
    return(std::string(ft_utoa(c_time->tm_mday) + " days " +
           ft_utoa(c_time->tm_hour) + ":" + ft_utoa(c_time->tm_min) + ":" + ft_utoa(c_time->tm_sec)));
}
