/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthesizer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 23:03:38 by lekix             #+#    #+#             */
/*   Updated: 2026/05/25 16:44:01 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTHESIZER_H
# define SYNTHESIZER_H

#include <inttypes.h>

constexpr float operator""_hz(long double v)  { return (float)v; }
constexpr float operator""_khz(long double v) { return (float)(v * 1000.0); }
constexpr float operator""_ms(long double v)  { return (float)v; }
constexpr float operator""_s(long double v)   { return (float)(v * 1000.0); }

constexpr uint16_t BUFFER_FRAMES    = 256;
constexpr uint16_t SAMPLE_RATE      = 44100;
constexpr float PI                  = 3.14159;
constexpr float twoPI               = 2.0f * PI;

#endif