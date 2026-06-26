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

#include "Vco.hpp"

constexpr float PI      = 3.14159;
constexpr float TWO_PI  = 2.0f * PI;

void Vco::render() {
    // std::cout << "Vco CALLED\n";
    phase_ += TWO_PI * this->freq / SAMPLE_RATE;
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
    this->audioOutput = signal;
    incTotalSamplesElapsed();
}

float Vco::sine() {
    return sinf(phase_);
}

float Vco::square() {
    return phase_ < PI ? 1.0f : -1.0f;
}

float Vco::saw() {
    // return phase_ * 2.0f - 1.0f; // to
    return sine();
}

float Vco::triangle() {
    return sine();
}

Vco& Vco::toggleWave()
{
    waveType_ = static_cast<e_wave>((static_cast<int>(waveType_) + 1) % 4);
    return *this;
}