/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:16:34 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/07/06 18:44:09 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./die.h"

int die(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);

	int d;
	char *s;
	double f;

	while (*fmt) {
		switch (*fmt) {
			case 'd':
				d = va_arg(args, int);
				fprintf(stderr, "%d", d);
				break ;
			case 'c':
				d = va_arg(args, int);
				fprintf(stderr, "%c", d);
				break ;
			case 's':
				s = va_arg(args, char *);
				fprintf(stderr, "%s", s);
				break ;
			case 'f':
				f = va_arg(args, double);
				fprintf(stderr, "%f", f);
		}
		++fmt;
		if (*fmt)
			fprintf(stderr, ": ");
	}
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
	return (0);
}
