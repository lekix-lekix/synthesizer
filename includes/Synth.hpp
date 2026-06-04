/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 23:02:05 by lekix             #+#    #+#             */
/*   Updated: 2026/06/04 16:02:37 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "synthesizer.hpp"
#include <array>
#include <memory>
#include <unordered_map>
#include <optional>

// template <typename T>
class Synth
{
    private:
        std::vector<std::unique_ptr<AudioModule>>   audioModules_;
        // std::array<float, BUFFER_FRAMES>            buffer_;
        
        std::unique_ptr<AudioModule>                makeAudioModule(e_modules type);
        uint64_t                                    totalSamplesElapsed = {0};
        
        public:
        Synth() = default;
        ~Synth() = default;
        Synth(const Synth &other) = default;
        Synth(Synth &&other) = default;
        Synth &operator=(const Synth &other) = default;
        Synth &operator=(Synth &&other) = default;
        
        
        void                                        addAudioModule(e_modules type);
        void                                        incTotalSamples() { totalSamplesElapsed++; };   
        float                                       render();

        template<typename T>
        T*                                          getModule(int idx);
        std::vector<std::unique_ptr<AudioModule>>   &getModules() { return this->audioModules_; };
        const uint64_t                              &getTotalSamples() { return this->totalSamplesElapsed; };
        void                                        setInput(int input);

        // std::array<float, BUFFER_FRAMES> &getBuffer() { return this->buffer_; };
};

template <typename T>
T* Synth::getModule(int idx) {
    if (idx < 0 || idx >= static_cast<int>(this->audioModules_.size()))
        return nullptr;

    return dynamic_cast<T*>(this->audioModules_[idx].get());
}
