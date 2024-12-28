/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 20:42:48 by yojablao          #+#    #+#             */
/*   Updated: 2024/12/25 20:42:49 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tool.h"




int ft_rang(double min,double num,double max)
{
    if (num >= min && num <= max)
        return (1);
    else 
        return (0);
}