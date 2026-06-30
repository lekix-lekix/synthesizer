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

#include <dsp/dsp.hpp>

#include "Patch.hpp"

class Synth
{
    private:
        std::vector<std::shared_ptr<AudioModule>>   audioModules_;
        std::vector<std::unique_ptr<Patch>>         connections_;

        std::shared_ptr<AudioModule>                makeAudioModule(e_audioModules type);
        std::unique_ptr<Patch>                      makePatch(float &from, float &to);
        
    public:
        Synth() = default;
        ~Synth() = default;
        Synth(const Synth &other) = default;
        Synth(Synth &&other) = default;
        Synth &operator=(const Synth &other) = default;
        Synth &operator=(Synth &&other) = default;
        
        std::shared_ptr<AudioModule>                addAudioModule(e_audioModules type);
        std::unique_ptr<Patch>                      connect(float &from, float &to);
        void                                        render();

        template<typename T>
        T*                                          getModule(int idx); // -> a changer
        std::vector<std::shared_ptr<AudioModule>>   &getAudioModules() { return this->audioModules_; };
        void                                        setInput(int input);

        std::weak_ptr<Mixer_4> getMaster() {
            if (audioModules_.empty())
                return {};
            for (auto &module : audioModules_) {
                std::weak_ptr<Mixer_4> mixer = std::dynamic_pointer_cast<Mixer_4>(module);
                if (mixer.lock())
                    return (mixer);
            }
            return {};
        }

        std::function<void(AudioModule*, e_audioModules)> onAudioModuleCreated;
};

template <typename T>
T* Synth::getModule(int idx) {
    if (idx < 0 || idx >= static_cast<int>(this->audioModules_.size()))
        return nullptr;

    return dynamic_cast<T*>(this->audioModules_[idx].get());
}
