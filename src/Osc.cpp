/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:42:44 by lekix             #+#    #+#             */
/*   Updated: 2026/06/08 16:25:15 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Generate a sinewave 
// Sample it 44100 times / second ?
// send it to sound card ---> OS : audio API, MCU : send to DAC

#include "Osc.hpp"
#include "constants.hpp"
#include <iostream>

constexpr float PI      = 3.14159;
constexpr float TWO_PI  = 2.0f * PI;

float Osc::render() {
    // std::cout << "OSC CALLED\n";
    this->phase += TWO_PI * this->freq / SAMPLE_RATE;
    if (this->phase >= TWO_PI) this->phase -= TWO_PI;
    
    float signal = 0;
    switch (this->waveType) {
        case SINE:
            signal = sinf(this->phase);
            break;

        case SQUARE:
            signal = this->square();
            break;
        
        case SAW:
            signal = this->saw();
            break;
            
        default:
            return -1;
    }
    this->audioOutput_ = signal;
    return 0;
}

float Osc::square() {
    return phase < PI ? 1.0f : -1.0f;
}

float Osc::saw() { 
    return phase * 2.0f - 1.0f; // to fix
}
