/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:41:00 by lekix             #+#    #+#             */
/*   Updated: 2026/06/03 15:33:11 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <array>
#include <cmath>
#include "synthesizer.hpp"

enum wave {
    SINE,
    SQUARE,
    SAW,
    // TRIANGLE
};

class Osc : public AudioModule {         // to do : Osc (interface) -> SineOsc, SquareOsc, ..
    private:
        wave    waveType = { SINE };
        float   freq = { 440.0f };
        float   phase = { 0 };
        
    public:
        Osc() = default;
        ~Osc() = default;
        Osc(const Osc &other) = default;
        Osc(Osc &&other) = default;
        Osc &operator=(const Osc &other) = default;
        Osc &operator=(Osc &&other) = default;

        Osc(const float &freq) { this->freq = freq; };

        float   render(float signal = 0.f) override;
        float   sine();
        float   square();
        float   saw();

        void    setFreq(float newFreq) { this->freq = newFreq; };
        void    setWave(wave newWaveType) { this->waveType = newWaveType; }; 
        void    incFreq() { this->freq++; };
        void    decFreq() { this->freq--; };
};