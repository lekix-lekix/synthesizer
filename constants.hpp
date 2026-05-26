/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:03:19 by lekix             #+#    #+#             */
/*   Updated: 2026/05/26 17:08:39 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <inttypes.h>

constexpr float operator""_hz(long double v)  { return (float)v; }
constexpr float operator""_khz(long double v) { return (float)(v * 1000.0); }
constexpr float operator""_ms(long double v)  { return (float)v; }
constexpr float operator""_s(long double v)   { return (float)(v * 1000.0); }

constexpr uint16_t BUFFER_FRAMES    = 256;
constexpr uint16_t SAMPLE_RATE      = 44100;