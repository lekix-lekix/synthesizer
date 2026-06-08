/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mixer_4.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:28:19 by lekix             #+#    #+#             */
/*   Updated: 2026/06/08 16:25:21 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mixer_4.hpp"
#include <iostream>

float Mixer_4::render() {
    this->audioInput_ = 0;
    // std::cout << "MIXER CALLED\n";
    for (auto &input : this->inputs_) {
        // input.lock()->render();
        this->audioInput_ += input.lock()->getOutput();
        // std::cout << input.lock()->getName() << std::endl;
    }
    this->audioOutput_ = this->audioInput_;
    return 0;
}
