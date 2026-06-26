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

std::shared_ptr<AudioModule> Synth::makeAudioModule(e_audioModules type) {
    std::shared_ptr<AudioModule> newModule;
    switch (type)
    {
        case VCO:
            newModule = std::make_shared<Vco>();
            break;
        
        case VCA:
            newModule = std::make_shared<Vca>();
            break;

        case MIXER_4:
            newModule = std::make_shared<Mixer_4>();
            break;

        case ENV:
            newModule = std::make_shared<Env>();
            break;

        default:
            break;
    }
    if (!newModule)
        std::cerr << "Error creating module" << std::endl;
    if (onAudioModuleCreated)
        onAudioModuleCreated(newModule.get(), type);
    return newModule;
}

std::shared_ptr<AudioModule> Synth::addAudioModule(e_audioModules type) {
    std::shared_ptr<AudioModule> newModule = this->makeAudioModule(type);
    if (newModule == nullptr) return nullptr;
    audioModules_.push_back(newModule);
    return newModule;
}

std::unique_ptr<Patch> Synth::connect(float &from, float &to) {
    std::unique_ptr<Patch> newPatch = std::make_unique<Patch>(from, to);
    if (newPatch == nullptr) return nullptr;
    connections_.push_back(std::move(newPatch));
    return newPatch;
}

void Synth::render() {
    for (auto &module : audioModules_) {
        module->render();
    }
    for (auto &connection : connections_) {
        connection->propagate();
    }
}