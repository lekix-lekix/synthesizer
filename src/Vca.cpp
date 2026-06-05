/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vca.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:24:57 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 17:12:27 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vca.hpp"

float Vca::render() {
    // float mod = 0;

    this->audioOutput_ = this->audioInput_ * this->gain_;
    return this->audioInput_;
}