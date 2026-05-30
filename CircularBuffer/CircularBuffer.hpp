/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CircularBuffer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:22:38 by lekix             #+#    #+#             */
/*   Updated: 2026/05/31 00:38:13 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cuchar>
#include <array>

template <typename T, std::size_t N>
class CircularBuffer {
    private:
        std::array<T, N> buffer_;
        std::size_t head_ = {0};
        std::size_t tail_ = {0};

    public:
        CircularBuffer() = default;
        ~CircularBuffer() = default;
        CircularBuffer(const CircularBuffer &other) = default;
        CircularBuffer(CircularBuffer &&other) = default;
        CircularBuffer &operator=(const CircularBuffer &other) = default;
        CircularBuffer &operator=(CircularBuffer &&other) = default;

        bool    write(const T &value);
        bool    read(T & value);

};

template <typename T, std::size_t N>
bool CircularBuffer<T, N>::write(const T &value) {
    auto new_head = this->head_ + 1;
    if (new_head == buffer_.size())
    new_head = 0;
    if (new_head == this->tail_)
    return false;
    this->buffer_[new_head] = value;
    this->head_ = new_head;
    return true;
}

template <typename T, std::size_t N>
bool CircularBuffer<T, N>::read(T &value) {
    if (this->tail_ == this->head_)
        return false;
    value = this->buffer_[this->tail_];
    this->tail_ += 1;
    if (this->tail_ == this->buffer_.size())
        this->tail_ = 0;
    return true;
}