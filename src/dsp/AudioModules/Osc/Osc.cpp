/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:42:44 by lekix             #+#    #+#             */
/*   Updated: 2026/06/09 11:31:41 by lekix            ###   ########.fr       */
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

void Osc::render() {
    // std::cout << "OSC CALLED\n";
    this->phase += TWO_PI * this->freq / SAMPLE_RATE;
    if (this->phase >= TWO_PI) this->phase -= TWO_PI;
    
    float signal = 0;
    switch (this->waveType_) {
        case SINE:
            signal = sinf(this->phase);
            break;

        case SQUARE:
            signal = this->square();
            break;
        
        // case SAW:
        //     signal = this->saw();
        //     break;
            
        default:
            return ;
    }
    this->audioOutput_ = signal;
}

float Osc::square() {
    return phase < PI ? 1.0f : -1.0f;
}

float Osc::saw() { 
    return phase * 2.0f - 1.0f; // to fix
}
