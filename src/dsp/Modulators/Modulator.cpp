/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Modulator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:48:45 by lekix             #+#    #+#             */
/*   Updated: 2026/06/09 11:50:07 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Modulator.hpp"

bool Modulator::setCVOut(float newValue) {
    if (newValue < -10 || newValue > 10)
        return false;
    this->CV_out_ = newValue;
    return true;
}