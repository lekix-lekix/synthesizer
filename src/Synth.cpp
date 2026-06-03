/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:36:33 by lekix             #+#    #+#             */
/*   Updated: 2026/06/03 15:35:17 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.hpp"
#include "../includes/synthesizer.hpp"

void Synth::addAudioModule(std::unique_ptr<AudioModule> module) { this->audioModules_.push_back(std::move(module)); }

float Synth::render()
{
    if (this->audioModules_.size() == 0)
        return -1;

    float signal = 0;
    for (auto &module : this->audioModules_) {
        signal = module->render(signal);
    }
    return signal;
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