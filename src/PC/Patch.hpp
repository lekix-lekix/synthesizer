#pragma once

class Patch
{
    private:
        float &to_;
        float &from_;

    public:
        Patch() = delete;
        ~Patch() = default;
        Patch(const Patch &other) = delete;
        Patch(Patch &&other) = default;
        Patch &operator=(const Patch &other) = delete;
        Patch &operator=(Patch &&oother) = delete;

        Patch(float &from, float &to) : from_(from), to_(to) {};

        float   &getFrom() { return from_; };
        float   &getTo() { return to_; };

        void    propagate() { to_ = from_; };
};

