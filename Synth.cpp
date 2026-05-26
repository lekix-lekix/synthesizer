/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:36:33 by lekix             #+#    #+#             */
/*   Updated: 2026/05/25 17:11:29 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Synth.hpp"

void Synth::addOsc(std::unique_ptr< Osc > newOsc) { this->oscillators_.push_back(newOsc); }

void Synth::render() {
    for (auto &frame : this->buffer_) { // buffer size == BUFFER_FRAMES -> bounded
        for (auto &osc : this->oscillators_) {
            frame += osc->renderFrame();
        }
    }
}
