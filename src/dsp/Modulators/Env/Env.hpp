/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Env.hpp                                      :+:      :+:    :+:   */
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

#include "dsp/constants.hpp"
#include "dsp/AudioModules/AudioModule.hpp"

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

class Env : public AudioModule
{
    private:
        ADSR            adsr_;
        int             startFrame_ = { 0 };
        bool            initRelease_ = false;
        float           initReleaseValue_ = { 0 };
        e_envState      state_ = { IDLE };

        void            checkGate();

        float           attack();
        float           decay();
        float           sustain();
        float           release();

    public:
        Env() : AudioModule("Env") {};

        bool            gateIn = { false };
        float           cvOut = { 0 };

        const ADSR      &getADSR() { return adsr_; };
        const float     &getAttack() { return adsr_.atk_ms; };
        const float     &getDecay() { return adsr_.dec_ms; };
        const float     &getSustain() { return adsr_.sus_gain; };
        const float     &getRelease() { return adsr_.rel_ms; };

        Env             &setAttack(float time_ms) { adsr_.atk_ms = time_ms; return *this; };
        Env             &setDecay(float time_ms) { adsr_.dec_ms = time_ms; return *this; };
        Env             &setSustain(float time_ms) { adsr_.sus_gain = time_ms; return *this; };
        Env             &setRelease(float time_ms) { adsr_.rel_ms = time_ms; return *this; };

        void            render() override;
};