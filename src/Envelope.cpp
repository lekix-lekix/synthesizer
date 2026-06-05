/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Envelope.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:49:59 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 15:15:24 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Envelope.hpp"
#include "constants.hpp"

float Envelope::render() {
    return 0;
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

float Envelope::linear(float time_ms) {
    if (this->startFrame_ == 0)
        this->startFrame_ = this->totalSamplesElapsed_;
    
    int totalSteps = time_ms * SAMPLE_RATE_1MS; // --> N
    int actualStep = this->totalSamplesElapsed_ - this->startFrame_;
    if (actualStep >= totalSteps)
        return 0; // -> stop enveloppe instead
    return static_cast<float>(actualStep) / static_cast<float>(totalSteps);
}
