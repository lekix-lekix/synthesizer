/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 23:53:59 by lekix             #+#    #+#             */
/*   Updated: 2026/05/31 00:44:39 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CircularBuffer.hpp"
#include <iostream>

int main()
{
    CircularBuffer<int, 5> circ;

    for (int i = 0; i < 5; i++)
    {
        int curr;
        circ.write(i);
        circ.read(curr);
        std::cout << curr << std::endl;
    }
}