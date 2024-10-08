/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:28:12 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/25 13:38:39 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*space;

	space = (unsigned char *) ft_malloc (count * size);
	if (!space)
		return (NULL);
	ft_bzero(space, count * size);
	return ((void *)space);
}
