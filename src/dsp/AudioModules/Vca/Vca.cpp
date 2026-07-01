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

void Vca::render() {
    this->audioOutput = this->audioInput * (gain_ * (this->gainCVIn / 10.0f));
    incTotalSamplesElapsed();
}