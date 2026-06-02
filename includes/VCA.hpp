/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VCA.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:48:42 by lekix             #+#    #+#             */
/*   Updated: 2026/06/02 17:12:40 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class VCA
{
    private:
        float   ampValue = {0.2};
        
    public:
        VCA() = default;
        ~VCA() = default;
        VCA(const VCA &other) = default;
        VCA(VCA &&other) = default;
        VCA &operator=(const VCA &other) = default;
        VCA &operator=(VCA &&other) = default;

        void    setAmpValue(float newVal) { this->ampValue = newVal; };
        float   render(float signal) { return signal * this->ampValue; };
};
