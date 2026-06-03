/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 23:02:05 by lekix             #+#    #+#             */
/*   Updated: 2026/06/03 15:34:59 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "synthesizer.hpp"
#include <array>
#include <memory>
#include <unordered_map>

class Synth
{
    private:
        std::vector<std::unique_ptr<AudioModule>>   audioModules_;
        std::array<float, BUFFER_FRAMES>            buffer_;

    public:
        Synth() = default;
        ~Synth() = default;
        Synth(const Synth &other) = default;
        Synth(Synth &&other) = default;
        Synth &operator=(const Synth &other) = default;
        Synth &operator=(Synth &&other) = default;
    
        void                            addAudioModule(std::unique_ptr<AudioModule> module);
        void                            setInput(int input);
        float                           render();

        std::array<float, BUFFER_FRAMES> &getBuffer() { return this->buffer_; };
};