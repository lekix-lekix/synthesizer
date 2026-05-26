/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:41:00 by lekix             #+#    #+#             */
/*   Updated: 2026/05/26 16:58:31 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <array>
#include <cmath>
#include "./synthesizer.hpp"

enum wave {
    SINE,
    SQUARE,
    SAW,
    // TRIANGLE
};

class Osc {         // to do : Osc (interface) -> SineOsc, SquareOsc, ..
    private:
        wave    waveType = { SINE };
        float   freq = { 440.0f };
        float   amp = { 0.2f };   // will go into VCA
        float   phase = { 0 };
        
    public:
        Osc() = default;
        ~Osc() = default;
        Osc(Osc const &other) = default;
        Osc(Osc &&other) = default;
        Osc &operator=(Osc const &other) = default;
        Osc &operator=(Osc &&other) = default;

        float   renderFrame();
        float   sine();
        float   square();
        float   saw();

        void    setFreq(float newFreq) { this->freq = newFreq; };
        void    setAmp(float newAmp) { this->amp = newAmp; };
        void    setWave(wave newWaveType) { this->waveType = newWaveType; }; 
        void    incFreq() { this->freq++; };
        void    decFreq() { this->freq--; };
};