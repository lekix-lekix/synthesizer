/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:42:44 by lekix             #+#    #+#             */
/*   Updated: 2026/05/25 16:49:27 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Generate a sinewave 
// Sample it 44100 times / second ?
// send it to sound card ---> OS : audio API, MCU : send to DAC

#include "./synthesizer.h"
#include "./Osc.hpp"

float Osc::renderFrame() {
    switch (this->waveType)
    {
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
            break;
    }
}

float Osc::sine() {
    // for (auto &frame : this->buffer) { // buffer size == BUFFER_FRAMES -> bounded
        // this->phase += (twoPI * this->freq / SAMPLE_RATE);
        // if (this->phase >= twoPI) this->phase -= twoPI;
        // frame = this->amp * sin(this->phase);
    // }
    // return 0;
    this->phase += twoPI * this->freq / SAMPLE_RATE;
    if (this->phase >= twoPI) this->phase -= twoPI;
    return this->amp * sin(this->phase);
}