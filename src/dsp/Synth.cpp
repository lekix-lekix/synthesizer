/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 16:36:33 by lekix             #+#    #+#             */
/*   Updated: 2026/06/12 13:25:42 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Synth.hpp"
#include "constants.hpp"

std::shared_ptr<Modulator> Synth::makeModulator(e_modulators type) {
    std::shared_ptr<Modulator> newModule;
    switch (type)
    {
        case ENV:
            newModule = std::make_shared<Envelope>(this->totalSamplesElapsed);
            break;
        
        default:
            break;
    }
    if (onModulatorCreated)
        onModulatorCreated(newModule.get(), type);
    return newModule;
}

std::shared_ptr<AudioModule> Synth::makeAudioModule(e_audioModules type) {
    std::shared_ptr<AudioModule> newModule;
    switch (type)
    {
        case OSC:
            newModule = std::make_shared<Osc>(this->totalSamplesElapsed);
            break;
        
        case VCA:
            newModule = std::make_shared<Vca>(this->totalSamplesElapsed);
            break;
        
        case MIXER_4:
            newModule = std::make_shared<Mixer_4>(this->totalSamplesElapsed);
        default:
            break;
    }
    if (onAudioModuleCreated)
        onAudioModuleCreated(newModule.get(), type);
    return newModule;
}

std::shared_ptr<AudioModule> Synth::addAudioModule(e_audioModules type) {
    std::shared_ptr<AudioModule> newModule = this->makeAudioModule(type);
    if (newModule == nullptr) return nullptr;
    this->audioModules_.push_back(newModule);
    return newModule;
}

std::shared_ptr<Modulator> Synth::addModulator(e_modulators type, std::shared_ptr<AudioModule> dest) {
    std::shared_ptr<Modulator> newModulator = this->makeModulator(type);
    if (newModulator == nullptr) return nullptr;
    dest->addModulator(newModulator);
    this->modulators_.push_back(newModulator);
    return newModulator;
}

void Synth::render() {
    for (auto &module : this->audioModules_) {
        module->render();
    }
}