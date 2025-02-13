/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuthayak <tuthayak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:48:22 by tuthayak          #+#    #+#             */
/*   Updated: 2025/02/13 14:48:22 by tuthayak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// Handle errors by freeing memory and sending SIGUSR2 to client.
void	handle_error(int pid, char *str)
{
    if (str != NULL)
        free(str);
    write(2, "server: unexpected error.\n", 26);
    kill(pid, SIGUSR2);
    exit(EXIT_FAILURE);
}

// Print the message and free memory.
char	*print_msg(char *message)
{
    ft_printf("%s\n", message);
    return (free(message), NULL);
}

// Append a character to the string.
char	*str_append_c(char *str, char c)
{
    char	*add;
    int		i;

    if (c == '\0')
        return (NULL);
    if (str == NULL)
    {
        add = malloc(sizeof(char) * 2);
        if (!add)
            return (NULL);
        return (add[0] = c, add[1] = '\0', add);
    }
    add = malloc(sizeof(char) * (ft_strlen(str) + 2));
    if (add == NULL)
        return (free(str), NULL);
    i = 0;
    while (str[i])
    {
        add[i] = str[i];
        i++;
    }
    return (free(str), add[i++] = c, add[i] = '\0', add);
}

// Handle signals from the client and build the message.
void	handle_signal(int signal, siginfo_t *info, void *context)
{
    static int	pid = 0;
    static int	bits = 0;
    static char	c = 0xFF;
    static char	*message = 0;

    if (info->si_pid)
        pid = info->si_pid;
    if (signal == SIGUSR1)
        c ^= 0x80 >> bits;
    else if (signal == SIGUSR2)
        c |= 0x80 >> bits;
    bits++;
    if (bits == 8)
    {
        if (c != '\0')
            message = str_append_c(message, c);
        else
            message = print_msg(message);
        bits = 0;
        c = 0xFF;
    }
    if (kill(pid, SIGUSR1) == -1)
        handle_error (pid, message);
    (void)context;
}

int	main(void)
{
    struct sigaction	sa_signal;
    sigset_t			block_mask;
    int					pid;

    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGINT);
    sigaddset(&block_mask, SIGQUIT);
    sa_signal.sa_handler = 0;
    sa_signal.sa_flags = SA_SIGINFO;
    sa_signal.sa_mask = block_mask;
    sa_signal.sa_sigaction = handle_signal;
    sigaction(SIGUSR1, &sa_signal, NULL);
    sigaction(SIGUSR2, &sa_signal, NULL);
    pid = getpid();
    ft_printf("Server PID : %d\n", pid);
    while (1)
        pause();
}
