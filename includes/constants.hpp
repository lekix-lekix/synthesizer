/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:03:19 by lekix             #+#    #+#             */
/*   Updated: 2026/06/01 11:19:45 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <inttypes.h>

constexpr float operator""_hz(long double v)  { return (float)v; }
constexpr float operator""_khz(long double v) { return (float)(v * 1000.0); }
constexpr float operator""_ms(long double v)  { return (float)v; }
constexpr float operator""_s(long double v)   { return (float)(v * 1000.0); }

constexpr uint16_t BUFFER_FRAMES    = 128;
constexpr uint16_t SAMPLE_RATE      = 44100;
constexpr float    DEADLINE_US      = static_cast<float>(BUFFER_FRAMES) / static_cast<float>(SAMPLE_RATE) / 2.0f * 1000000;