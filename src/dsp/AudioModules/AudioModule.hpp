/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioModule.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:08:05 by lekix             #+#    #+#             */
/*   Updated: 2026/06/18 15:00:49 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class AudioModule {
    protected:
        std::string         name_;
        uint64_t            totalSamplesElapsed_ = { 0 };
    
    public:
        AudioModule() = delete;
        explicit AudioModule(std::string name) : name_(std::move(name)) {}
        virtual ~AudioModule() = default;
        AudioModule(const AudioModule &other) = default;
        AudioModule(AudioModule &&other) = default;
        AudioModule &operator=(const AudioModule &other) = delete;
        AudioModule &operator=(AudioModule &&other) = delete;
        
        const std::string   &getName() { return name_; };
        const uint64_t      &getTotalSamplesElapsed() { return totalSamplesElapsed_; };

        AudioModule         &incTotalSamplesElapsed() { totalSamplesElapsed_ += 1; return *this; };

        virtual void render() = 0;
};
