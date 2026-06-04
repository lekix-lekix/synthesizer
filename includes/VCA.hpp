/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VCA.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:48:42 by lekix             #+#    #+#             */
/*   Updated: 2026/06/04 15:05:51 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "synthesizer.hpp"

class Vca : public AudioModule {
    private:
        float   ampValue = {0.2};

    public:
        Vca() = default;
        ~Vca() = default;
        Vca(const Vca &other) = default;
        Vca(Vca &&other) = default;
        Vca &operator=(const Vca &other) = default;
        Vca &operator=(Vca &&other) = default;

        Vca(const uint64_t &totalSamplesElapsed) : AudioModule(totalSamplesElapsed) {};

        void    setAmpValue(float newVal) { this->ampValue = newVal; };
        float   render(float signal = 0.f) override { return signal * this->ampValue; } ;
};
