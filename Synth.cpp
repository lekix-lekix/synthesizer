/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:36:33 by lekix             #+#    #+#             */
/*   Updated: 2026/05/26 16:08:33 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./constants.hpp"
#include "./synthesizer.hpp"

void Synth::addOsc(std::unique_ptr<Osc> newOsc) { this->oscillators_.push_back(std::move(newOsc)); }

void Synth::render() {
    for (auto &frame : this->buffer_) { // buffer size == BUFFER_FRAMES -> bounded
        // std::cout << "====\n";
        float tmp = 0;
        for (auto &osc : this->oscillators_) {
            tmp += osc->renderFrame();
            // std::cout << frame << std::endl;
        }
        frame = tmp;
    }
}
