/*
Copyright (c) 2018-2019, Michael Romans of Romans Audio
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the MRUtils project.
*/

#ifndef WWBININ_RAMINIVECTOR_H
#define WWBININ_RAMINIVECTOR_H
#define MIN_CAPACITY 10
#define GROWTH_FACTOR 2

#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <cstdlib>

template <typename T>
class RAMiniVector {
public:
    RAMiniVector() {
        m_capacity = MIN_CAPACITY;
        m_size = 0;
        m_data = (T*)malloc(m_capacity * sizeof(*m_data));
        if (!m_data)
            throw std::bad_alloc();
    };
    ~RAMiniVector() { free(m_data); };

    T &operator[] (size_t index) {
        if (index >= m_size) {
            throw std::bad_exception();
        }
        return m_data[index];
    }
    void push_back(T value) {
        if (m_size >= m_capacity) {
            resize();
        }
        *(m_data + m_size++) = value;
    };
    void emplace_back(T value) {
        if (m_size >= m_capacity) {
            resize();
        }
        *(m_data + m_size++) = value;
    };
    T pop_back() {
        return *(m_data + --m_size);
    };
    T at(unsigned long index) {
        if (index >= m_size) {
            throw std::bad_exception();
        }
        return m_data[index];
    };
    size_t size() { return m_size; };
    size_t capacity() { return m_capacity; };
    bool empty() { return m_size == 0; };
    size_t begin() { return 0; }
    size_t end() { return size() - 1; }

private:
    size_t m_size;
    size_t m_capacity;
    T* m_data;
    void resize() {
        size_t capacity = m_capacity*GROWTH_FACTOR;
        T *tmp = (T*)realloc(m_data, capacity * sizeof(*m_data));
        if (!tmp)
            throw std::bad_alloc();
        m_data = tmp;
        m_capacity = capacity;
    };
};

#endif //WWBININ_RAMINIVECTOR_H
