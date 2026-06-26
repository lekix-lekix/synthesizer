/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mixer_4.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:28:19 by lekix             #+#    #+#             */
/*   Updated: 2026/06/18 15:06:57 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mixer_4.hpp"
// #include <iostream>

void Mixer_4::render() {
    float signal = 0;

    for (int i = 0; i < 4; i++) {
        signal += (this->audioInputs[i] * gains_[i]);
    }
    this->audioOutput = signal;
    incTotalSamplesElapsed();
}

float Mixer_4::getGain(int idx) {
    if (idx < 0 || idx > 3)
        return 1.0f;
    return gains_[idx];
}

Mixer_4 &Mixer_4::setGain(int idx, float newGain) {
    if (idx < 0 || idx > 3)
        return *this;
    gains_[idx] = newGain;
    return *this;
}
