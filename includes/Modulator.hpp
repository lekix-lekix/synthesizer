/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Modulator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:13:49 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 15:15:51 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <inttypes.h>

class Modulator
{
    private:
    
    public:
        Modulator() = default;
        virtual ~Modulator() = default;
        Modulator(const Modulator &other) = default;
        Modulator(Modulator &&other) = default;
        Modulator &operator=(const Modulator &other) = default;
        Modulator &operator=(Modulator &&other) = default;

        const uint64_t &totalSamplesElapsed_;
        
        Modulator(const uint64_t &totalSamplesElapsed) : totalSamplesElapsed_(totalSamplesElapsed) {};
        
        virtual float render() = 0;
};