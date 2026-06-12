/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:41:00 by lekix             #+#    #+#             */
/*   Updated: 2026/06/09 11:31:56 by lekix            ###   ########.fr       */
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
    // SAW,
    // TRIANGLE
};

class Osc : public AudioModule {
    private:
        e_wave  waveType_ = { SINE };
        float   freq = { 440.0f };
        float   phase = { 0 };
        
    public:
        Osc() = delete;
        ~Osc() = default;
        Osc(const Osc &other) = default;
        Osc(Osc &&other) = default;
        Osc &operator=(const Osc &other) = delete;
        Osc &operator=(Osc &&other) = delete;

        Osc(const uint64_t &totalSamplesElapsed) : AudioModule(totalSamplesElapsed) { this->name_ = "Osc"; };
        Osc(const uint64_t totalSamplesElapsed, const float &freq) : AudioModule(totalSamplesElapsed) {
            this->name_ = "Osc";
            this->freq = freq;
        }
        
        float   sine();
        float   square();
        float   saw();
        void    render() override;

        float       getFreq() { return this->freq; };
        Osc         &setFreq(float newFreq) { this->freq = newFreq; return *this; };

        Osc         &setWave(e_wave newWaveType) { this->waveType_ = newWaveType; return *this; };
        e_wave      &getWave() { return this->waveType_; };

        void        incFreq() { this->freq++; };
        void        decFreq() { this->freq--; };

        Osc     &toggleWave() {
            if (waveType_ == SINE)
                waveType_ = SQUARE;
            else
                waveType_ = SINE;
            return *this;
        };
};