/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Synth.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 23:02:05 by lekix             #+#    #+#             */
/*   Updated: 2026/05/25 17:10:44 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Osc.hpp"
#include <vector>
#include <array>
#include <memory>

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
    
        void addOsc(std::unique_ptr<Osc> osc);
        void render();
        std::array<float, BUFFER_FRAMES> &getBuffer() { return this->buffer_; };
};