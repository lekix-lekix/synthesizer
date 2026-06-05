/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:41:00 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 15:10:35 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <array>
#include <cmath>

#include "AudioModule.hpp"

enum e_wave {
    SINE,
    SQUARE,
    SAW,
    // TRIANGLE
};

class Osc : public AudioModule {
    private:
        e_wave  waveType = { SINE };
        float   freq = { 440.0f };
        float   phase = { 0 };
        
    public:
        Osc() = default;
        ~Osc() = default;
        Osc(const Osc &other) = default;
        Osc(Osc &&other) = default;
        Osc &operator=(const Osc &other) = default;
        Osc &operator=(Osc &&other) = default;

        Osc(const uint64_t &totalSamplesElapsed) : AudioModule(totalSamplesElapsed) {};
        Osc(const float &freq, const uint64_t totalSamplesElapsed) : AudioModule(totalSamplesElapsed) { this->freq = freq; };

        float   sine();
        float   square();
        float   saw();
        float   render() override;

        void    setFreq(float newFreq) { this->freq = newFreq; };
        void    setWave(e_wave newWaveType) { this->waveType = newWaveType; }; 
        void    incFreq() { this->freq++; };
        void    decFreq() { this->freq--; };
};