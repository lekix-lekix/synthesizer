/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mixer_4.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:22:00 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 17:37:08 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <array>

#include "AudioModule.hpp"


class Mixer_4 : public AudioModule
{        
    public:
        Mixer_4() = default;
        ~Mixer_4() = default;
        Mixer_4(const Mixer_4 &other) = default;
        Mixer_4(Mixer_4 &&other) = default;
        Mixer_4 &operator=(Mixer_4 const &other) = default;
        Mixer_4 &operator=(Mixer_4 &&other) = default;

    Mixer_4(const uint64_t& totalSamplesElapsed) : AudioModule(totalSamplesElapsed) {}

        float render();
};