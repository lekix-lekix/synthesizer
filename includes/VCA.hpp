/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VCA.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:48:42 by lekix             #+#    #+#             */
/*   Updated: 2026/06/03 15:33:59 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "synthesizer.hpp"

class VCA : public AudioModule {
    private:
        float   ampValue = {0.2};

    public:
        VCA() = default;
        ~VCA() = default;
        VCA(const VCA &other) = default;
        VCA(VCA &&other) = default;
        VCA &operator=(const VCA &other) = default;
        VCA &operator=(VCA &&other) = default;

        VCA(const float &ampValue) { this->ampValue = ampValue; };

        void    setAmpValue(float newVal) { this->ampValue = newVal; };
        float   render(float signal = 0.f) override { return signal * this->ampValue; } ;
};
