/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuthayak <tuthayak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:48:16 by tuthayak          #+#    #+#             */
/*   Updated: 2025/02/13 14:48:16 by tuthayak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Handle errors by freeing memory and exiting.
void	handle_error(char *msg, char **str)
{
	if (msg != NULL)
		free(msg);
	free(*str);
	write(2, "client : error\n", 15);
	exit(EXIT_FAILURE);
}

// Send 8 SIGUSR1 signals to indicate end of message.
int	send_null(int pid, char *str)
{
	static int	i = 0;

	if (i++ != 8)
	{
		if (kill(pid, SIGUSR1) == -1)
			handle_error(str, NULL);
		return (0);
	}
	free(str);
	return (1);
}

// Send the message bit by bit to the server.
int	send_bit(int pid, char *str)
{
	static char	*message = NULL;
	static int	s_pid = 0;
	static int	i = 0;

	if (str)
		message = ft_strdup(str);
	if (!message)
		handle_error(0, 0);
	if (pid)
		s_pid = pid;
	if (message[i] == '\0')
		return (send_null(s_pid, message));
	if (message[i] == '1')
	{
		if (kill(s_pid, SIGUSR2) == -1)
			handle_error(message, &str);
	}
	else if (message[i] == '0')
	{
		if (kill(s_pid, SIGUSR1) == -1)
			handle_error(message, &str);
	}
	i++;
	return (0);
}

// Handle signals from the server.
void	handle_signal(int sig)
{
	int	end;

	end = 0;
	if (sig == SIGUSR1)
		end = send_bit(0, NULL);
	else if (sig == SIGUSR2)
	{
		write(2, "client : server ended unexpectedly\n", 35);
		exit(EXIT_FAILURE);
	}
	if (end == 1)
	{
		write (1, "client : message sent\n", 22);
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	char	*bin;

	if (ac != 3 || ft_atoi(av[1]) <= 0)
	{
		ft_putstr_fd("client : invalid arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (av[2] == NULL || av[2][0] == '\0')
	{
		ft_putstr_fd("client : empty message\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	bin = str_to_bin(av[2]);
	if (bin == NULL)
		handle_error(0, 0);
	send_bit(ft_atoi(av[1]), bin);
	free(bin);
	while (1)
		pause();
}
