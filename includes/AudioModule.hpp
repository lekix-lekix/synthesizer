/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioModule.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:08:05 by lekix             #+#    #+#             */
/*   Updated: 2026/06/03 15:06:54 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class AudioModule {
    private:
        /* data */
    public:
        AudioModule() = default;
        virtual ~AudioModule() = default;
        AudioModule(const AudioModule &other) = default;
        AudioModule(AudioModule &&other) = default;
        AudioModule &operator=(const AudioModule &other) = default;
        AudioModule &operator=(AudioModule &&other) = default;

        virtual float render(float signal = 0.f) = 0;
};
