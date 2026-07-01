/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vca.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:48:42 by lekix             #+#    #+#             */
/*   Updated: 2026/06/09 11:31:16 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "dsp/AudioModules/AudioModule.hpp"

class Vca : public AudioModule {
    private:
        float   gain_ = { 1 };

    public:
        Vca() : AudioModule("Vca") {};
        Vca(const float &gain) : AudioModule("Vca") { gain_ = std::move(gain); };

        float   audioInput = { 0 };
        float   audioOutput = { 0 };
        float   gainCVIn = { 0 };

        float   getGain() { return gain_; };
        Vca     &setGain(float newGain) { gain_ = newGain; return *this; };

        void    render() override;
};
