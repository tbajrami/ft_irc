/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addclient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbajrami <tbajrami@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:52:51 by tbajrami          #+#    #+#             */
/*   Updated: 2021/05/14 14:14:53 by tbajrami         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ftirc.hpp"

int addclient(std::map<int, Client> *clients, int listener)
{
    Client nc;

    nc.is_server = false;
    nc.is_register = false;
    int addrlen = sizeof(nc.clientaddr);
    if((nc.clfd = accept(listener, (struct sockaddr *)&nc.clientaddr, &nc.addrlen)) == -1)
    {
		std::cout << "Server-accept() error\n";
        return (-1);
    }
    else
        std::cout << "Server-accept() is OK...\n";
    std::cout << "New connection from " << inet_ntoa(nc.clientaddr.sin_addr);
    ft_strlcpy(nc.host, inet_ntoa(nc.clientaddr.sin_addr), 16);
    std::cout << " on socket " << nc.clfd << std::endl;
    std::pair<int, Client> n(nc.clfd, nc);
    clients->insert(n);
    return (nc.clfd);
}
