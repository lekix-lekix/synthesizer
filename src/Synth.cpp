/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:36:33 by lekix             #+#    #+#             */
/*   Updated: 2026/06/02 17:11:19 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.hpp"
#include "../includes/synthesizer.hpp"

void Synth::addOsc(std::unique_ptr<Osc> newOsc) { this->oscillators_.push_back(std::move(newOsc)); }

void Synth::render()
{
    float signal = 0;
    for (auto &osc : this->oscillators_)
        signal += osc->renderFrame();
    this->buffer_.write(signal);
}

// std::unordered_map<char, bool> Synth::initInputs_() {
// std::unordered_map<char, bool> inputs;
//
// for (char c : std::string("asdfghjkl"))
// inputs[c];
// return std::move(inputs);
// }

// void Synth::setInput(int input) {

// }