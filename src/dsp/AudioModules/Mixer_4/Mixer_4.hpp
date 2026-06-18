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

#include "AudioModule.hpp"

class Mixer_4 : public AudioModule {
    private:
        std::array<float, 4> gains_ = {1};

    public:
        Mixer_4() = delete;
        ~Mixer_4() = default;
        Mixer_4(const Mixer_4 &other) = default;
        Mixer_4(Mixer_4 &&other) = default;
        Mixer_4 &operator=(Mixer_4 const &other) = delete;
        Mixer_4 &operator=(Mixer_4 &&other) = delete;

        Mixer_4(const uint64_t& totalSamplesElapsed) : AudioModule(totalSamplesElapsed) {}

        std::array<float, 4>    &getGains() { return this->gains_; };
        float                   getGain(int idx);
        Mixer_4                 &setGain(int idx, float newGain);

        void                    render();
};