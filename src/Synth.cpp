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

std::unique_ptr<Patch> Synth::connect(float *from, float *to) {
    std::unique_ptr<Patch> newPatch = std::make_unique<Patch>(from, to);
    if (newPatch == nullptr) return nullptr;
    connections_.load()->push_back(std::move(newPatch));
    std::cout << "connected !" << std::endl;
    return newPatch;
}

void Synth::deleteConnection(unsigned int idx) {
    std::vector<std::unique_ptr<Patch>> *newVec = new std::vector<std::unique_ptr<Patch>>;
    std::vector<std::unique_ptr<Patch>> *oldVec = connections_.load();

    for (auto &patch : *oldVec) {
        newVec->push_back(std::make_unique<Patch>(*patch.get()));
    }
    // newVec->at(idx).release();
    newVec->erase(newVec->begin() + idx);

    std::cout<<"coucou\n";
    bool copySuccess = false;
    while (!copySuccess) copySuccess = connections_.compare_exchange_strong(oldVec, newVec);
    std::cout << "copy success = " << copySuccess << std::endl;

    delete oldVec;
}

void Synth::render() {
    for (auto &module : audioModules_) {
        module->render();
    }
    int idx = 0;
    std::vector<std::unique_ptr<Patch>> *vec = connections_.load();
        for (auto &connection : *vec) {
            connection->propagate();
    }
}