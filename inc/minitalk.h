/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuthayak <tuthayak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:48:45 by tuthayak          #+#    #+#             */
/*   Updated: 2025/02/12 23:48:45 by tuthayak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libftprintf/inc/ft_printf.h"
# include "../libftprintf/inc/libft.h"

# define MAX_BITS 8

void	signal_handler(int sig, siginfo_t *info, void *context);
void	reset_message(char *message, int *char_pos);
void	handle_received_bit(int sig, int *bit_count, unsigned char *current_byte);
void	send_byte(int pid, unsigned char byte);
void	send_message(int pid, const char *message);

#endif
