#include "../inc/ftirc.hpp"
#include "../inc/Params.hpp"
#include "../inc/Server.hpp"

int main_loop(Server &serv, Fds *fds)
{
	int newfd;

	for (int i = 0 ; i <= fds->fdmax ; i++)
	{
		if(FD_ISSET(i, &fds->read))
		{
			if (i == serv.listener)
			{
				if ((newfd = serv.addclient(serv.listener)) != -1)
				{
					if(newfd > fds->fdmax)
						fds->fdmax = newfd;
					return newfd;
				}
			}
			else
				rec_data(serv, i, fds);
		}
	}
	return 0;
}

std::vector<std::string> getParams(size_t  ac, char **av)
{
	std::vector<std::string> vec;

	for (size_t i = 1; i < ac; i++)
		vec.push_back(std::string(av[i]));
	return (vec);
}

int main(int ac, char *av[])
{
	if (ac < 3)
	{
		std::cerr << "Insufficient parameters. \nUsage : ./ircserv [PORT] [PASS]" << std::endl;
		return (1);
	}
	Params *pm = new Params(ac, getParams(ac, av));
	Server serv(pm);
	int newfd;
	Fds *fds = serv.getFds();

	FD_ZERO(&fds->master);
	FD_ZERO(&fds->read);
	FD_SET(serv.listener, &fds->master);
	fds->fdmax = serv.listener;
	for(;;)
	{
		fds = serv.getFds();
		fds->read = fds->master;
		if(select(fds->fdmax + 1, &fds->read, NULL, NULL, NULL) == -1)
		{
			std::cerr << "Server-select() error";
			exit(1);
		}
		if ((newfd = main_loop(serv, fds)) > 0)
			FD_SET(newfd, &fds->master);
	}
	return 0;
}
