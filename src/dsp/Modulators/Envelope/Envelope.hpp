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
#include <iostream>

#include "Modulator.hpp"

enum e_envState {
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE, 
    IDLE
};

struct ADSR
{
    float atk_ms = { 10 };
    float dec_ms = { 10 };
    float sus_gain = { 0.5 };
    float rel_ms = { 100 };

    ADSR() {};
};

class Envelope : public Modulator
{
    private:
        ADSR        adsr_;
        bool        gate_ = { false };
        int         startFrame_ = { 0 };
        bool        initRelease_ = false;
        float       initReleaseValue_ = { 0 };
        e_envState  state_ = { IDLE };
        
    public:
        Envelope() = delete;
        ~Envelope() = default;
        Envelope(const Envelope &other) = default;
        Envelope(Envelope &&other) = default;
        Envelope &operator=(const Envelope &other) = default;
        Envelope &operator=(Envelope &&other) = default;

        Envelope(const uint64_t &totalSamplesElapsed) : Modulator(totalSamplesElapsed) {};

        ADSR            &getADSR() { return adsr_; };
        Envelope        &setAttack(float time_ms) { adsr_.atk_ms = time_ms; return *this; };
        Envelope        &setGate(bool gateState);

        float   attack();
        float   decay();
        float   sustain();
        float   release();
        void    render();
};