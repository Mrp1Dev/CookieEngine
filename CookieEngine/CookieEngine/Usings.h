#pragma once
#include <cstdint>
#include <cmath>
#include <utility>

template<class T, class F>
T scast(F&& f)
{
    return static_cast<T>(std::forward<F>(f));
}

template<class T, class F>
T rcast(F&& f)
{
    return reinterpret_cast<T>(std::forward<F>(f));
}
template<class T, class F>
T dcast(F&& f)
{
    return dynamic_cast<T>(std::forward<F>(f));
}

using u8 = std::uint8_t;

using u16 = std::uint16_t;

using u32 = std::uint32_t;

using u64 = std::uint32_t;

using i8 = std::int8_t;
      
using i16 = std::int16_t;
      
using i32 = std::int32_t;
      
using i64 = std::int32_t;

using f32 = std::float_t;

using f64 = std::double_t;