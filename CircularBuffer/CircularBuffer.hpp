/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CircularBuffer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:22:38 by lekix             #+#    #+#             */
/*   Updated: 2026/06/03 13:20:30 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cuchar>
#include <array>
#include <atomic>

template <typename T, std::size_t N>
class CircularBuffer {
    private:
        std::array<T, N>    buffer_;
        alignas(64) std::atomic<size_t> head_ = 0;
        alignas(64) std::atomic<size_t> tail_ = 0;

    public:
        CircularBuffer() = default;
        ~CircularBuffer() = default;
        CircularBuffer(const CircularBuffer &other) = default;
        CircularBuffer(CircularBuffer &&other) = default;
        CircularBuffer &operator=(const CircularBuffer &other) = default;
        CircularBuffer &operator=(CircularBuffer &&other) = default;

        bool    write(const T &value);
        bool    read(T & value);
        bool    isFull();

};

template <typename T, std::size_t N>
bool CircularBuffer<T, N>::write(const T &value) {
    auto new_head = this->head_.load() + 1;
    if (new_head == buffer_.size())
        new_head = 0;
    if (new_head == this->tail_.load())
    {
        // std::cout << "full\n";
        return false;
    }
    this->buffer_[new_head] = value;
    this->head_.store(new_head);
    // std::cout << "filled\n";
    return true;
}

template <typename T, std::size_t N>
bool CircularBuffer<T, N>::read(T &value) {
    const auto tail = this->tail_.load();
    if (tail_ == head_.load())
        return false;
    value = this->buffer_[tail];
    auto next_tail = tail + 1;
    if (next_tail == this->buffer_.size())
        next_tail = 0;
    this->tail_.store(next_tail);
    return true;
}

template <typename T, std::size_t N>
bool CircularBuffer<T, N>::isFull() {
    const auto new_head = this->head_.load() + 1;
    if (new_head == this->tail_.load())
        return true;
    return false;
}