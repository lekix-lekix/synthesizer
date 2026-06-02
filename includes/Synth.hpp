/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 23:02:05 by lekix             #+#    #+#             */
/*   Updated: 2026/06/02 17:12:16 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "synthesizer.hpp"
#include "../CircularBuffer/CircularBuffer.hpp"
#include <array>
#include <memory>
#include <unordered_map>

// constexpr uint8_t MAX_OSC = 3;

class Synth
{
    private:
        std::vector<std::unique_ptr<Osc>> oscillators_;
        CircularBuffer<float, BUFFER_FRAMES> buffer_;
        // std::unordered_map<char, bool> inputs_ = initInputs_();

        // std::unordered_map<char, bool> initInputs_();
    
    public:
        Synth() = default;
        ~Synth() = default;
        Synth(const Synth &other) = default;
        Synth(Synth &&other) = default;
        Synth &operator=(const Synth &other) = default;
        Synth &operator=(Synth &&other) = default;
    
        void                            addOsc(std::unique_ptr<Osc> osc);
        // void                            addVCA(std::unique_ptr<VCA> vca);
        std::unique_ptr<Osc> const      &getOsc(int idx) { return this->oscillators_[idx]; };
        void                            setInput(int input);
        void                            render();

        CircularBuffer<float, BUFFER_FRAMES> &getBuffer() { return this->buffer_; };
};