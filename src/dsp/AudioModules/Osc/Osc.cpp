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
    phase_ += TWO_PI * freq_ / SAMPLE_RATE;
    if (phase_ >= TWO_PI) phase_ -= TWO_PI;
    
    float signal = 0;
    switch (this->waveType_) {
        case SINE:
            signal = sine();
            break;

        case SQUARE:
            signal = square();
            break;
        
        case SAW:
            signal = saw();
            break;

        case TRIANGLE:
            signal = triangle();
            break;

        default:
            return ;
    }
    this->audioOutput_ = signal;
}

float Osc::sine() {
    return sinf(phase_);
}

float Osc::square() {
    return phase_ < PI ? 1.0f : -1.0f;
}

float Osc::saw() { 
    // return phase_ * 2.0f - 1.0f; // to
    return sine();
}

float Osc::triangle() {
    return sine();
}

Osc& Osc::toggleWave()
{
    waveType_ = static_cast<e_wave>((static_cast<int>(waveType_) + 1) % 4);
    return *this;
}