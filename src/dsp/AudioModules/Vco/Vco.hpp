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

#include <cmath>
#include <unordered_map>

#include "dsp/constants.hpp"
#include "dsp/AudioModules/AudioModule.hpp"

enum e_wave {
    SINE,
    SQUARE,
    SAW,
    TRIANGLE
};

class Vco : public AudioModule {
    private:
        e_wave      waveType_ = { SINE };
        float       phase_ = { 0 };

        float       sine();
        float       square();
        float       saw();
        float       triangle();

    public:
        Vco()                  : AudioModule("Vco") {};
        Vco(const float &freq) : AudioModule("Vco") { this->freq = std::move(freq); }

        float       freq = { 440.0f };

        float       audioOutput = { 0 };
        float       freqCVIn = { 0 };

        Vco         &setFreq(float newFreq) { this->freq = newFreq; return *this; };
        e_wave      &getWavetype() { return waveType_; }

        void        incFreq() { this->freq++; };
        void        decFreq() { this->freq--; };

        Vco         &toggleWave();

        void        render() override;
};