/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vca.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:24:57 by lekix             #+#    #+#             */
/*   Updated: 2026/06/12 13:25:11 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vca.hpp"
#include <iostream>

void Vca::render() {
    this->audioInput_ = 0;
    this->CV_in_ = 0;
    for (auto &input : this->inputs_)
        this->audioInput_ += input.lock()->getOutput();
    for (auto &modulator : this->modulators_) {
        modulator.lock()->render();
        this->CV_in_ += modulator.lock()->getCVOut();
    }
    this->audioOutput_ = this->audioInput_ * (this->gain_ * (CV_in_ / 10.0f));
}