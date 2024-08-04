/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:22:24 by mcutura           #+#    #+#             */
/*   Updated: 2024/08/04 22:37:57 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	free_map(t_board *node, int height)
{
	for (int j = 0; j < height; j++)
	{
		free(node->map[j]);
	}
	free(node->map);
}

void	free_maps(t_board *tree, int tree_size)
{
	int height = tree[0].height;

	for (int i = 1; i < tree_size; i++)
	{
		free_map(&tree[i], height);
	}
}

double sqroot(double x)
{
	double z = 1.0;

	for (int i = 1; i <= 10; i++)
	{
		z -= (z * z - x) / (2 * z);
	}
	return (z);
}

int	msb(unsigned int v)
{
	unsigned int r = 0;

	while (v >>= 1) {
		r++;
	}
	return (r);
}

float ln(int y)
{
	int log2;
	float divisor, x, result;

	log2 = msb((unsigned int)y); // See: https://stackoverflow.com/a/4970859/6630230
	divisor = (float)(1 << log2);
	x = y / divisor;    // normalized value between [1.0, 2.0]

	result = -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x;
	result += ((float)log2) * 0.69314718; // ln(2) = 0.69314718

	return result;
}

