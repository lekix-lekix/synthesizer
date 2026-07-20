#pragma once
#include <iostream>

class Patch
{
    private:
        float *from_;
        float *to_;

    public:
        Patch() = delete;
        ~Patch() = default;
        Patch(const Patch &other) = default;
        Patch(Patch &&other) = default;
        Patch &operator=(const Patch &other) = default;
        Patch &operator=(Patch &&oother) = delete;

        Patch(float *from, float *to) : from_(from), to_(to) {};

        float   *getFrom() { if (!from_) std::cout << "from null" << std::endl; return from_; };
        float   *getTo() { return to_; };

        void    propagate() { *to_ = *from_; };
};

