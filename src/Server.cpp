/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbajrami <tbajrami@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:12:23 by tbajrami          #+#    #+#             */
/*   Updated: 2021/05/14 16:53:20 by tbajrami         ###   ########lyon.fr   */
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

void Server::getIP()
{
    const char* google_dns_server = "8.8.8.8";
    int dns_port = 53;
	struct sockaddr_in serv;
    int sock = socket ( AF_INET, SOCK_DGRAM, 0);

	memset( &serv, 0, sizeof(serv) );
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr( google_dns_server );
    serv.sin_port = htons( dns_port );
    int err = connect( sock , (const struct sockaddr*) &serv , sizeof(serv) );
    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    err = getsockname(sock, (struct sockaddr*) &name, &namelen);
	char buffer[100];
    const char* p = inet_ntoa(name.sin_addr);
	if(p != NULL)
	{
		printf("Local ip is : %s \n" , p);
	}
    strcpy(_ip, p);
    ft_bzero(_prefix, 17);
    _prefix[0] = ':';
    strcat(_prefix, _ip);
    printf("_prefix : %s\n", _prefix);
}

void Server::setFds(Fds *fds) {_fds = fds;}

void Server::new_serv(Params *pm)
{
    int yes = 1;
    getIP();
    
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

void Server::send_reply(int fd, int cmd, char *prefix)
{
    char *msg = msg_error(cmd);

    std::string ccmd = ft_format_cmd(ft_utoa(cmd));
    std::string to_send;

    to_send += (std::string(prefix) + " " + ccmd + " " + std::string(msg) + "\r\n");
    send(fd, to_send.c_str(), ft_strlen(to_send.c_str()), 0);
}

void Server::do_command(Message *msg, Client &client)
{
    if (!strcmp(msg->command, "PASS"))
        passcmd(msg, client);
    if (!strcmp(msg->command, "NICK"))
        nickcmd(msg, client);
}

void Server::passcmd(Message *msg, Client &client)
{
    if (client.is_register == true)
        send_reply(client.clfd, 462, _prefix);
    else if (!msg->params[0][0])
        send_reply(client.clfd, ERR_NEEDMOREPARAMS, _prefix);
    else
    {
        ft_strlcpy(client.password, msg->params[0], 32);
        //send_reply(client.clfd, 001, _prefix);
        send(client.clfd, "", 1, 0);
    }
        // else if (!strcmp(msg->params[0], _password))
        // {
        //     client.is_register = true;
        //     std::cout << "\nWelcome\n";
        //     send(client.clfd, "welcome", 8, 0);
        // }
        // else
        // {
        //     std::cout << "\nBad password : deconnexion\n";
        //     send(client.clfd, "\nBad password\n", 13, 0);
        //     close(client.clfd);
        //     FD_CLR(client.clfd, &_fds->master);
        //}
}

void Server::nickcmd(Message *msg, Client &client)
{
    ft_strlcpy(client.nickname, msg->params[0], 9);
}