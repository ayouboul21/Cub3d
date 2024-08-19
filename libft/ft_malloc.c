/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:37:35 by aoulahra          #+#    #+#             */
/*   Updated: 2024/08/18 15:58:48 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	(void)size;
	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Allocation failed\n", 19);
		exit(1);
	}
	return (ptr);
}
