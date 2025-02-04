/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:22:00 by jiparcer          #+#    #+#             */
/*   Updated: 2025/02/04 17:28:27 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "talk.h"

volatile sig_atomic_t	g_server = 0;

//check si le serveur a bien reçu le message
void	ack_handler(int signal)
{
	(void)signal;
	g_server = 1;
}

//check si le message est fini
void	end_handler(int signo)
{
	(void)signo;
	write(1, "ok\n", 2);
	exit(EXIT_SUCCESS);
}

//envoie bit par bit chaque caractère du message
void	send_char(char c, pid_t server)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			ft_kill(server, SIGUSR1);
		else
			ft_kill(server, SIGUSR2);
		++bit;
		while (g_server == 0)
			usleep(42);
		g_server = 0;
	}
}

int	main(int ac, char **av)
{
	pid_t	server;
	char	*message;

	if (ac != 3)
	{
		ft_printf("Usage: %s <serveur_pid> <message>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	server = ft_atoi(av[1]);
	message = av[2];
	ft_signal(SIGUSR1, ack_handler, false);
	ft_signal(SIGUSR2, end_handler, false);
	while (*message)
		send_char(*message++, server);
	send_char('\0', server);
}
