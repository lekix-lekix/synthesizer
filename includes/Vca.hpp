/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vca.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:48:42 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 15:12:53 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AudioModule.hpp"

class Vca : public AudioModule {
    private:
        float   gain_ = {0.2};

    public:
        Vca() = default;
        ~Vca() = default;
        Vca(const Vca &other) = default;
        Vca(Vca &&other) = default;
        Vca &operator=(const Vca &other) = default;
        Vca &operator=(Vca &&other) = default;

        Vca(const uint64_t &totalSamplesElapsed) : AudioModule(totalSamplesElapsed) {};

        void    setGain(float newVal) { this->gain_ = newVal; };
        float   render() override;
};
