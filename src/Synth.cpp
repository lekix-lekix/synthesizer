/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:36:33 by lekix             #+#    #+#             */
/*   Updated: 2026/06/04 15:40:31 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.hpp"
#include "../includes/synthesizer.hpp"

std::unique_ptr<AudioModule> Synth::makeAudioModule(e_modules type) {
    switch (type)
    {
        case OSC:
            return std::move(std::make_unique<Osc>(this->totalSamplesElapsed));
            break;
        
        case VCA:
            return std::move(std::make_unique<Vca>(this->totalSamplesElapsed));
            break;
        
        default:
            break;
    }
    return nullptr;
}

void Synth::addAudioModule(e_modules type) {
    std::unique_ptr<AudioModule> module = this->makeAudioModule(type);
    if (module == nullptr)
        return ;
    this->audioModules_.push_back(this->makeAudioModule(type));
}

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