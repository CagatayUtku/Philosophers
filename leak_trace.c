/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_trace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cutku <cutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:38:38 by Cutku             #+#    #+#             */
/*   Updated: 2023/06/03 23:43:32 by Cutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*my_malloc(t_garbage **garbage, size_t count, size_t size)
{
	void	*ptr;

	if (count != 0 && ((size * count) / count != size))
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
	{
		free_garbage(garbage);
		return (NULL);
	}
	add_garbage(garbage, ptr);
	return (ptr);
}

void	add_garbage(t_garbage **first, void *ptr)
{
	t_garbage	*new;
	t_garbage	*last;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	if (!new)
		return ;
	new->ptr = ptr;
	new->next = NULL;
	if (*first == NULL)
		*first = new;
	else
	{
		last = *first;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	free_garbage(t_garbage **first)
{
	t_garbage	*del;

	while (*first != NULL)
	{
		del = *first;
		*first = (*first)->next;
		free(del->ptr);
		free(del);
		del = NULL;
	}
}
