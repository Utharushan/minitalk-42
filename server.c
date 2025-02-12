/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuthayak <tuthayak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:52:55 by tuthayak          #+#    #+#             */
/*   Updated: 2025/02/12 23:52:55 by tuthayak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	reset_message(char *message, int *char_pos)
{
	ft_printf("%s\n", message);
	*char_pos = 0;
	ft_bzero(message, 1024);
}

void	handle_received_bit(int sig, int *bit_count, unsigned char *current_byte)
{
	if (sig == SIGUSR1)
		*current_byte &= ~(1 << (7 - *bit_count));
	else if (sig == SIGUSR2)
		*current_byte |= (1 << (7 - *bit_count));
	(*bit_count)++;
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int bit_count = 0;
	static unsigned char current_byte = 0;
	static char message[1024] = {0};
	static int char_pos = 0;

	(void)context;
	(void)info;
	handle_received_bit(sig, &bit_count, &current_byte);
	if (bit_count == 8)
	{
		message[char_pos] = current_byte;
		if (current_byte == '\0')
			reset_message(message, &char_pos);
		else
			char_pos++;
		bit_count = 0;
		current_byte = 0;
	}
}


int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
