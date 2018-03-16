#ifndef RAMINIVECTOR_H
#define RAMINIVECTOR_H
#include <Arduino.h>

/*
This is based on found code from some arduino forum.  I will expand upon this.
*/

template<typename Data>
class RAMiniVector
{
    size_t d_size;
    size_t d_capacity;
    Data *d_data;

    public:
        RAMiniVector() : d_size(0), d_capacity(0), d_data(0) {};
        RAMiniVector(RAMiniVector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) {
            d_data = (Data *)malloc(d_capacity*sizeof(Data));
            memcpy(d_data, other.d_data, d_size*sizeof(Data));
        };
        virtual ~RAMiniVector() {free(d_data);};
        RAMiniVector &operator=(RAMiniVector const &other) {
            free(d_data);
            d_size = other.d_size;
            d_capacity = other.d_capacity;
            d_data = (Data *)malloc(d_capacity*sizeof(Data));
            memcpy(d_data, other.d_data, d_size*sizeof(Data));
            return *this;
        };
        void push_back(Data const &x) {
            if (d_capacity == d_size) resize();
            d_data[d_size++] = x;
        };
        size_t size() const {return d_size;};
        Data const &operator[](size_t idx) const {return d_data[idx];};
        Data &operator[](size_t idx) {return d_data[idx];};

    protected:

    private:
        void resize() {
            d_capacity = d_capacity ? d_capacity*2 : 1;
            Data *newdata = (Data *)malloc(d_capacity*sizeof(Data));
            memcpy(newdata, d_data, d_size * sizeof(Data));
            free(d_data);
            d_data = newdata;
        };
};

#endif // RAMINIVECTOR_H
