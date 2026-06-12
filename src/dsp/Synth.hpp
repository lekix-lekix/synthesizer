/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 23:02:05 by lekix             #+#    #+#             */
/*   Updated: 2026/06/09 13:38:10 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <array>
#include <optional>
#include <inttypes.h>
#include <memory>
#include <functional>

#include "AudioModule.hpp"
#include "Modulator.hpp"
#include "Osc.hpp"
#include "Vca.hpp"
#include "Envelope.hpp"
#include "Mixer_4.hpp"
#include "constants.hpp"

// template <typename T>
class Synth
{
    private:
        std::vector<std::shared_ptr<AudioModule>>   audioModules_;
        std::vector<std::shared_ptr<Modulator>>     modulators_;
        
        std::shared_ptr<Modulator>                  makeModulator(e_modulators type);
        std::shared_ptr<AudioModule>                makeAudioModule(e_audioModules type);
        uint64_t                                    totalSamplesElapsed = {0};
        
    public:
        Synth() = default;
        ~Synth() = default;
        Synth(const Synth &other) = default;
        Synth(Synth &&other) = default;
        Synth &operator=(const Synth &other) = default;
        Synth &operator=(Synth &&other) = default;
        
        std::shared_ptr<AudioModule>                addAudioModule(e_audioModules type);
        std::shared_ptr<Modulator>                  addModulator(e_modulators type, std::shared_ptr<AudioModule> dest);
        void                                        incTotalSamples() { totalSamplesElapsed++; };   
        void                                        render();

        template<typename T>
        T*                                          getModule(int idx); // -> a changer
        std::vector<std::shared_ptr<AudioModule>>   &getAudioModules() { return this->audioModules_; };
        std::vector<std::shared_ptr<Modulator>>     &getModulators() { return this->modulators_; };
        const uint64_t                              &getTotalSamples() { return this->totalSamplesElapsed; };
        void                                        setInput(int input);

        std::weak_ptr<Mixer_4> getMaster() {
            if (audioModules_.empty())
                return {};
            return std::dynamic_pointer_cast<Mixer_4>(audioModules_.back());
        }

        std::function<void(Modulator*, e_modulators)> onModulatorCreated;
        std::function<void(AudioModule*, e_audioModules)> onAudioModuleCreated;

        // std::array<float, BUFFER_FRAMES> &getBuffer() { return this->buffer_; };
};

template <typename T>
T* Synth::getModule(int idx) {
    if (idx < 0 || idx >= static_cast<int>(this->audioModules_.size()))
        return nullptr;

    return dynamic_cast<T*>(this->audioModules_[idx].get());
}
