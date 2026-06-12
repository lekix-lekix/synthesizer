/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:03:19 by lekix             #+#    #+#             */
/*   Updated: 2026/06/05 17:15:33 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <inttypes.h>

inline extern constexpr float operator""_hz(long double v)  { return (float)v; }
inline extern constexpr float operator""_khz(long double v) { return (float)(v * 1000.0); }
inline extern constexpr float operator""_ms(long double v)  { return (float)v; }
inline extern constexpr float operator""_s(long double v)   { return (float)(v * 1000.0); }

inline extern constexpr uint16_t BUFFER_FRAMES    = 128;
inline extern constexpr uint16_t SAMPLE_RATE      = 44100;
inline extern constexpr uint16_t SAMPLE_RATE_1MS  = 44.1;
inline extern constexpr float    DEADLING_US          = static_cast<float>(BUFFER_FRAMES) / static_cast<float>(SAMPLE_RATE) * 1000000;
inline extern constexpr float    DEADLING_MS          = static_cast<float>(BUFFER_FRAMES) / static_cast<float>(SAMPLE_RATE) * 1000;

enum e_audioModules {
    OSC,
    VCA,
    MIXER_4
};

enum e_modulators {
    ENV
};