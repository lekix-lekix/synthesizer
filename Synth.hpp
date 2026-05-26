/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 23:02:05 by lekix             #+#    #+#             */
/*   Updated: 2026/05/26 15:59:08 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./synthesizer.hpp"
#include <array>
#include <memory>

// constexpr uint8_t MAX_OSC = 3;

class Synth
{
    private:
        std::vector<std::unique_ptr<Osc>> oscillators_;
        std::array<float, BUFFER_FRAMES> buffer_;
    
    public:
        Synth() = default;
        ~Synth() = default;
        Synth(const Synth &other) = default;
        Synth(Synth &&other) = default;
        Synth &operator=(const Synth &other) = default;
        Synth &operator=(Synth &&other) = default;
    
        void                        addOsc(std::unique_ptr<Osc> osc);
        std::unique_ptr<Osc> const  &getOsc(int idx) { return this->oscillators_[idx]; };
        void                        render();

        std::array<float, BUFFER_FRAMES> &getBuffer() { return this->buffer_; };
};