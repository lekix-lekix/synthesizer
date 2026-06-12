/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CircularBufferMutex.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 14:22:38 by lekix             #+#    #+#             */
/*   Updated: 2026/06/02 15:16:44 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cuchar>
#include <array>
#include <mutex>

template <typename T, std::size_t N>
class CircularBufferMutex {
    private:
        std::array<T, N> buffer_;
        std::size_t      head_ = 0;
        std::size_t      tail_ = 0;
        std::mutex       mutex_;

    public:
        CircularBufferMutex() = default;
        ~CircularBufferMutex() = default;
        CircularBufferMutex(const CircularBufferMutex &other) = default;
        CircularBufferMutex(CircularBufferMutex &&other) = default;
        CircularBufferMutex &operator=(const CircularBufferMutex &other) = default;
        CircularBufferMutex &operator=(CircularBufferMutex &&other) = default;

        bool    write(const T &value);
        bool    read(T & value);

};

template <typename T, std::size_t N>
bool CircularBufferMutex<T, N>::write(const T &value) {
    std::lock_guard<std::mutex> lock(this->mutex_);
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
bool CircularBufferMutex<T, N>::read(T &value) {
    std::lock_guard<std::mutex> lock(this->mutex_);
    if (this->tail_ == this->head_)
        return false;
    value = this->buffer_[this->tail_];
    this->tail_ += 1;
    if (this->tail_ == this->buffer_.size())
        this->tail_ = 0;
    return true;
}