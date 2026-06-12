/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 23:53:59 by lekix             #+#    #+#             */
/*   Updated: 2026/06/02 14:36:38 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CircularBuffer.hpp"
#include <iostream>
#include <thread>
#include <random>

void read_task(CircularBuffer<int, 5> &buffer) {
    int i = -1;
    
    while (1) {
        buffer.read(i);
        std::cout << "read = " << i << "\n";
    }
}

int main()
{
    CircularBuffer<int, 5> circ;

    std::random_device rd;
    std::mt19937 gen(rd());
    
    // bool init = false;
    std::thread read_thread(read_task, std::ref(circ));

    while (1) {
        circ.write(gen());
        // std::cout << gen() << std::endl;
    }

    // read_thread.join();
    // 
    // while (1) {
        // std::cout << "coucou\n";
    // }
    // while (1) {
        // circ.write(gen());
        // if (!init) {
            // read_thread.join();
            // init = true;
        // }
    // }
}