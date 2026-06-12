/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AudioModule.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:54:54 by lekix             #+#    #+#             */
/*   Updated: 2026/06/12 13:25:18 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AudioModule.hpp"

void AudioModule::addModulator(std::shared_ptr<Modulator> modulator) {
    std::weak_ptr<Modulator> newModulator = modulator;
    this->modulators_.push_back(newModulator);
}

void AudioModule::audioConnect(std::shared_ptr<AudioModule> from, std::shared_ptr<AudioModule> to) {
    std::weak_ptr<AudioModule> fromPtr(from);
    std::weak_ptr<AudioModule> toPtr(to);
    from->outputs_.push_back(toPtr);
    to->inputs_.push_back(fromPtr);
}