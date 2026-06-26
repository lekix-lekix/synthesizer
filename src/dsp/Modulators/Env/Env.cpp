/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Envelope.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:49:59 by lekix             #+#    #+#             */
/*   Updated: 2026/06/18 14:18:05 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Env.hpp"

void Env::render() {
    checkGate();
    float signal = 0;
    switch (state_)
    {
        case ATTACK:
            signal = attack();
            break;
        
        case DECAY:
            signal = decay();
            break;

        case SUSTAIN:
            signal = sustain();
            break;

        case RELEASE:
            signal = release();
            break;
              
        case IDLE:
            signal = 0;

        default:
            break;
    }
    this->cvOut = (signal * 10.0f);
    incTotalSamplesElapsed();
}

float Env::attack() {
    if (state_ == IDLE)
        return 0;
    uint64_t totalSamplesElapsed = getTotalSamplesElapsed();
    if (startFrame_ == 0)
        startFrame_ = totalSamplesElapsed;
    float totalSteps = adsr_.atk_ms * SAMPLE_RATE_1MS; // --> N
    float currentStep = totalSamplesElapsed - startFrame_; // -> n
    if (currentStep >= totalSteps) {
        startFrame_ = 0;
        state_ = DECAY;
        return 1.0f;
    }
    float t = currentStep / totalSteps;
    return 1 - (1 - t) * (1 - t); // exp
}

float Env::decay() {
    uint64_t totalSamplesElapsed = getTotalSamplesElapsed();
    if (startFrame_ == 0) {
        startFrame_ = totalSamplesElapsed;
    }
    float totalSteps = adsr_.dec_ms * SAMPLE_RATE_1MS; // --> N
    float currentStep = totalSamplesElapsed - startFrame_; // -> n
    if (currentStep >= totalSteps) {
        startFrame_ = 0;
        state_ = SUSTAIN;
        return adsr_.sus_gain;
    }
    float t = currentStep / totalSteps;
    t = t * t;
    return 1 + t * (adsr_.sus_gain - 1);
}

float Env::sustain() {
    return adsr_.sus_gain;
}

float Env::release() {
    uint64_t totalSamplesElapsed = getTotalSamplesElapsed();
    if (initRelease_ == true) {
        initRelease_ = false;
        initReleaseValue_ = this->cvOut / 10.0f;
        startFrame_ = totalSamplesElapsed;
    }
    float totalSteps = adsr_.rel_ms * SAMPLE_RATE_1MS; // --> N
    float currentStep = totalSamplesElapsed - startFrame_; // -> n
    if (currentStep >= totalSteps) {
        state_ = IDLE;
        startFrame_ = 0;
        return 0;
    }
    float t = currentStep / totalSteps;
    t = t * t;
    return initReleaseValue_ + t * (0 - initReleaseValue_);
}

void    Env::checkGate() {
    if (!this->gateIn && (state_ == ATTACK || state_ == DECAY || state_ == SUSTAIN)) {
        state_ = RELEASE;
        initRelease_ = true;
        return ;
    }
    if (this->gateIn && (state_ == IDLE || state_ == RELEASE))
        state_ = ATTACK;
}

// v[n+1] = v[n] + (b2 ​− b1​​) / N -> linear enveloppe

// v[n]	            Valeur de la rampe à l'échantillon n. C'est la quantité que l'on calcule au fil du temps.
// n	            Indice d'échantillon (0, 1, 2, 3, ...).
// v[0]	            Valeur initiale de la rampe.
// b1               Valeur de départ (begin value).
// b2               Valeur d'arrivée (end value).
// N	            Nombre de pas (ou durée de la transition en échantillons).
// (b2 - b1)	    Amplitude totale du changement à effectuer.
// (b2 - b1) / N    Incrément ajouté à chaque échantillon -> step size / slope.

// N = Fs * t où :
// Fs = fréquence d'échantillonnage (samples/s)
// t = durée souhaitée (s)

// only INC will change depending on linear, exp, log