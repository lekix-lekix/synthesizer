/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mixer_4.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:28:19 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 17:12:56 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mixer_4.hpp"

float Mixer_4::render() {
    float signal = 0;

    for (auto &out : this->inputs_) {
        signal += out.lock()->render();
    }
    return signal;
}
