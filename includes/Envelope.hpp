/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Envelope.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:28:19 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 11:48:23 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <inttypes.h>

#include "Modulator.hpp"

class Envelope : public Modulator
{
    private:
        float   currentParamValue_;
        int     startFrame_;
        
    public:
        Envelope() = delete;
        ~Envelope() = default;
        Envelope(const Envelope &other) = default;
        Envelope(Envelope &&other) = default;
        Envelope &operator=(const Envelope &other) = default;
        Envelope &operator=(Envelope &&other) = default;

        Envelope(const uint64_t &totalSamplesElapsed) : Modulator(totalSamplesElapsed) {};

        float render();
        float linear(float time_ms);
};