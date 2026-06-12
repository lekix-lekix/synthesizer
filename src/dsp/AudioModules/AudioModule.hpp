/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioModule.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 17:08:05 by lekix             #+#    #+#             */
/*   Updated: 2026/06/09 11:27:46 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Modulator.hpp"

class AudioModule {
    protected:
        std::string                                 name_;
        float                                       audioInput_;
        float                                       audioOutput_;

        std::vector<std::weak_ptr<AudioModule>>     inputs_;
        std::vector<std::weak_ptr<AudioModule>>     outputs_;
        std::vector<std::weak_ptr<Modulator>>       modulators_;
    
    public:
        AudioModule() = delete;
        virtual ~AudioModule() = default;
        AudioModule(const AudioModule &other) = default;
        AudioModule(AudioModule &&other) = default;
        AudioModule &operator=(const AudioModule &other) = default;
        AudioModule &operator=(AudioModule &&other) = default;
        
        const uint64_t &totalSamplesElapsed_;
        AudioModule(const uint64_t &totalSamplesElapsed) : totalSamplesElapsed_(totalSamplesElapsed) {};
        
        void addModulator(std::shared_ptr<Modulator> modulator);
        void addInput(std::shared_ptr<AudioModule> other);
        void addOutput(std::shared_ptr<AudioModule> other);
        void audioConnect(std::shared_ptr<AudioModule> from, std::shared_ptr<AudioModule> to);

        virtual float &getInput() { return this->audioInput_; };
        virtual float &getOutput() { return this->audioOutput_; };
        std::string const &getName() { return this->name_; };

        virtual void render() = 0;
};
