/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Osc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:41:00 by lekix             #+#    #+#             */
/*   Updated: 2026/05/25 16:50:39 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <array>
#include <cmath>
#include "./synthesizer.h"

// using WaveFunc = float(*)(float);  // type : pointeur vers fonction float(float)

// constexpr WaveFunc waveTable[] = { 
//     [](float p) { return sinf(p); },
//     [](float p) { return p > 0.5f ? 1.0f : -1.0f; },
//     [](float p) { return 2.0f * p - 1.0f; }
// };

enum wave {
    SINE,
    SQUARE,
    SAW,
    // TRIANGLE
};

class Osc {
    private:
        wave    waveType = { SINE };
        float   freq = { 440.0f };
        float   amp = { 0.5f };
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

        void    incFreq() { this->freq++; };
};