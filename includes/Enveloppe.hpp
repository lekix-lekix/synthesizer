/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enveloppe.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:28:19 by lekix             #+#    #+#             */
/*   Updated: 2026/06/04 16:49:51 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "synthesizer.hpp"

#pragma once

class Enveloppe : public Modulator
{
    private:
        /* data */
    public:
        Enveloppe() = delete;
        ~Enveloppe() = default;
        Enveloppe(const Enveloppe &other) = default;
        Enveloppe(Enveloppe &&other) = default;
        Enveloppe &operator=(const Enveloppe &other) = default;
        Enveloppe &operator=(Enveloppe &&other) = default;

        Enveloppe(const uint64_t &totalSamplesElapsed) : Modulator(totalSamplesElapsed) {};

        float render(float signal = 0);
        float linear(float signal);
};