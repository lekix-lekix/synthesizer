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
    public:
        Vca() : AudioModule("Vca") {};
        Vca(const float &gain) : AudioModule("Vca") { this->gain = std::move(gain); };

        float   gain = { 1 };
        float   audioInput = { 0 };
        float   audioOutput = { 0 };
        float   CV_in = { 0 };

        void    render() override;
};
