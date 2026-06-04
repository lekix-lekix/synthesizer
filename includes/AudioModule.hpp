/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioModule.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:08:05 by lekix             #+#    #+#             */
/*   Updated: 2026/06/04 16:10:17 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class AudioModule {
    public:
        AudioModule() = delete;
        virtual ~AudioModule() = default;
        AudioModule(const AudioModule &other) = default;
        AudioModule(AudioModule &&other) = default;
        AudioModule &operator=(const AudioModule &other) = default;
        AudioModule &operator=(AudioModule &&other) = default;
        
        AudioModule(const uint64_t &totalSamplesElapsed) : totalSamplesElapsed(totalSamplesElapsed) {};
        
        const uint64_t &totalSamplesElapsed;
        
        virtual float render(float signal = 0.f) = 0;
};
