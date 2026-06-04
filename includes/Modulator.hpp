/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Modulator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:13:49 by lekix             #+#    #+#             */
/*   Updated: 2026/06/04 16:48:54 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "synthesizer.hpp"

class Modulator
{
    private:
    public:
        Modulator() = default;
        virtual ~Modulator() = default;
        Modulator(const Modulator &other) = default;
        Modulator(Modulator &&other) = default;
        Modulator &operator=(const Modulator &other) = default;
        Modulator &operator=(Modulator &&other) = default;

        Modulator(const uint64_t &totalSamplesElapsed) : totalSamplesElapsed(totalSamplesElapsed) {};
        const uint64_t &totalSamplesElapsed;
        
        virtual float render(float signal = 0);
};