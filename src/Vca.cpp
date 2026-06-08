/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vca.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:24:57 by lekix             #+#    #+#             */
/*   Updated: 2026/06/08 17:14:31 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vca.hpp"
#include <iostream>

float Vca::render() {
    // std::cout << "VCA CALLED\n";
    this->audioInput_ = 0;
    for (auto &input : this->inputs_) {
        this->audioInput_ += input.lock()->getOutput();
    }
    this->audioOutput_ = this->audioInput_ * this->gain_;
    return 0;
}