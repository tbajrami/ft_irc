/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbajrami <tbajrami@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:12:23 by tbajrami          #+#    #+#             */
/*   Updated: 2021/05/13 14:18:26 by tbajrami         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(Params *pm)
{
    _network = new std::vector<sockaddr_in>;
    if (pm->isnew())
        new_serv(pm);
    else
        connect_serv(pm);
}

void Server::setFds(Fds *fds) {_fds = fds;}

void Server::new_serv(Params *pm)
{
    int yes = 1;
    if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "Server-socket() error\n";
        exit(1);
    }
    if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        std::cout << "Server-setsockopt() error\n";
        exit(1);
    }
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(pm->getPort());
    strcpy(_password, pm->getPwd());
    ft_bzero(&(_addr.sin_zero), 8);
    _ip = inet_ntoa(_addr.sin_addr);
    printf("ip : %s\n", _ip);
    if(bind(listener, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
    {
        perror("Server-bind() error");
        exit(1);
    }
    if(listen(listener, 10) == -1)
    {
        perror("Server-listen() error");
        exit(1);
    }
}

void Server::connect_serv(Params *pm)
{
    int yes = 1;
    if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "Server-socket() error\n";
        exit(1);
    }
    if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        std::cout << "Server-setsockopt() error\n";
        exit(1);
    }
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(pm->getPort());
    strcpy(_password, pm->getPwd());
    ft_bzero(&(_addr.sin_zero), 8);
    _ip = inet_ntoa(_addr.sin_addr);
    printf("ip : %s\n", _ip);
    if(bind(listener, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
    {
        perror("Server-bind() error");
        exit(1);
    }
    if(listen(listener, 10) == -1)
    {
        perror("Server-listen() error");
        exit(1);
    }
    do_connect(pm);
}

void Server::do_connect(Params *pm)
{
    int net_socket = socket(AF_INET, SOCK_STREAM, 0);
    char message[1024];

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(pm->getPortNetwork());
    server_address.sin_addr.s_addr = INADDR_ANY;
    this->_network->push_back(server_address);
    
    int connection_status = connect(net_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status == -1)
        printf("Error making connection to the remote socket\n\n");
    send(net_socket, "SERVER", 6, 0);
}



/******************/
/* TREAT COMMANDS */
/******************/



void Server::do_command(Message *msg, Client &client)
{
    if (!strcmp(msg->command, "PASS"))
        passcmd(msg, client);
}

void Server::passcmd(Message *msg, Client &client)
{
    if (client.is_register == true)
    {
        std::cout << std::endl << msg_error(ERR_ALREADYREGISTERED) << std::endl;
        send(client.clfd, msg_error(ERR_ALREADYREGISTERED), sizeof(msg_error(ERR_ALREADYREGISTERED)), 0);
    }
    else
    {
        if (!strcmp(msg->params[0], _password))
        {
            client.is_register = true;
            std::cout << "\nWelcome\n";
            send(client.clfd, "welcome\n", 8, 0);
        }
        else
        {
            std::cout << "\nBad password : deconnexion\n";
            send(client.clfd, "\nBad password\n", 13, 0);
            close(client.clfd);
            FD_CLR(client.clfd, &_fds->master);
        }
    }
}

void Server::nickcmd(Message *msg, Client &client)
{
    
}