/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mixer_4.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:22:00 by lekix             #+#    #+#             */
/*   Updated: 2026/06/18 15:07:14 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>

#include "dsp/AudioModules/AudioModule.hpp"

class Mixer_4 : public AudioModule {
    private:
        std::array<float, 4>    gains_ = { 1 };

    public:
        Mixer_4() : AudioModule("Mixer_4") {}

        std::array<float, 4>    audioInputs = { 0 };
        float                   audioOutput = { 0 };

        std::array<float, 4>    &getGains() { return this->gains_; };
        float                   getGain(int idx);
        Mixer_4                 &setGain(int idx, float newGain);

        void                    render() override;
};