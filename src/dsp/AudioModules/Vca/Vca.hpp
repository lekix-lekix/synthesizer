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

#include "AudioModule.hpp"

class Vca : public AudioModule {
    private:
        float   gain_ = {1};
        float   CV_in_ = {0};

    public:
        Vca() = delete;
        ~Vca() = default;
        Vca(const Vca &other) = default;
        Vca(Vca &&other) = default;
        Vca &operator=(const Vca &other) = delete;
        Vca &operator=(Vca &&other) = delete;

        Vca(const uint64_t &totalSamplesElapsed) : AudioModule(totalSamplesElapsed) { this->name_ = "Vca"; };

        float   getGain() { return gain_; }
        Vca     &setGain(float newVal) { gain_ = newVal; return *this; };
        void    render() override;
};
