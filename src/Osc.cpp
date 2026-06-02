/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:42:44 by lekix             #+#    #+#             */
/*   Updated: 2026/06/02 17:13:24 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Generate a sinewave 
// Sample it 44100 times / second ?
// send it to sound card ---> OS : audio API, MCU : send to DAC

#include "../includes/synthesizer.hpp"

constexpr float PI      = 3.14159;
constexpr float TWO_PI  = 2.0f * PI;

float Osc::renderFrame() {
    this->phase += TWO_PI * this->freq / SAMPLE_RATE;
    if (this->phase >= TWO_PI) this->phase -= TWO_PI;
    switch (this->waveType) {
        case SINE:
            return this->sine();
            break;

        case SQUARE:
            return this->square();
            break;
        
        case SAW:
            return this->saw();
            break;
            
        default:
            return -1;
    }
}

float Osc::square() {
    return phase < PI ? 1.0f : -1.0f;
}

float Osc::saw() { 
    return phase * 2.0f - 1.0f; // to fix
}

float Osc::sine() {
    return sinf(this->phase);
}