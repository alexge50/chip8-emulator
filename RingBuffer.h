//
// Created by alex on 8/31/19.
//

#ifndef CHIP8_EMULATOR_RINGBUFFER_H
#define CHIP8_EMULATOR_RINGBUFFER_H

#include <optional>

template<typename T, std::size_t N>
class RingBuffer
{
    static constexpr std::size_t MOD = N + 1;
public:
    RingBuffer(): back(0), front(0) {}
    RingBuffer(const RingBuffer&) = delete;
    RingBuffer(RingBuffer&&) = delete;

    void push(const T& t)
    {
        auto p = back.load();

        new (data + p) T(t);

        p = (p + 1) % MOD;
        back.store(p);
    }

    void push(T&& t)
    {
        auto p = back.load();

        new (data + p) T(std::move(t));

        p = (p + 1) % MOD;
        back.store(p);
    }

    std::optional<T> pop()
    {
        if(empty())
            return std::nullopt;

        return raw_pop();
    }

    T raw_pop()
    {
        auto p = front.load();
        T *e = reinterpret_cast<T*>(data + p);
        T t = *e;
        e->~T();

        p = (p + 1) % MOD;
        front.store(p);
        return t;
    }

    std::size_t size() const
    {
        auto b = back.load(), f = front.load();

        if(f <= b)
            return b - f;
        else return MOD - f + b;
    }

    bool empty() const
    {
        return front.load() == back.load();
    }

    bool full() const
    {
        return (back.load() + 1) % MOD == front.load();
    }

private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data[N + 1];

    std::atomic<std::size_t> front, back;
};

#endif //CHIP8_EMULATOR_RINGBUFFER_H
