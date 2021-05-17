/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbajrami <tbajrami@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:12:30 by tbajrami          #+#    #+#             */
/*   Updated: 2021/05/14 16:13:03 by tbajrami         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "replies.hpp"

const char *msg_error(int code)
{
    if (code == ERR_ALREADYREGISTERED)
        return (":You may not reregister");
    if (code == ERR_NEEDMOREPARAMS)
        return (":Not enough parameters");
    if (code == RPL_WELCOME)
        return (":Welcome to the Internet Relay Network");
    return "";
}