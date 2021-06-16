#pragma once
#include <Usings.h>
#include <utility>
#include <limits>
#include <algorithm>
#include <numbers>
namespace cookie
{
    namespace Mathf
    {
        template<typename T>
        constexpr auto Epsilon = std::numeric_limits<T>::epsilon();
        constexpr auto Epsilonf = Epsilon<f32>;
        template<typename T>
        constexpr auto Infinity = std::numeric_limits<T>::infinity();
        constexpr auto Infinityf = Infinity<f32>;
        constexpr f64 PI64 = 3.141592653589793238463;
        constexpr f64 Tau64 = PI64 * 2.0;
        constexpr f32 PI = 3.141592653589793238463f;
        constexpr f32 Tau = PI * 2.0f;
        constexpr auto Deg2Radf = PI * 2.0f / 360.0f;
        constexpr auto Rad2Degf = 1.0f / Deg2Radf;
        constexpr auto Deg2Rad = PI * 2.0 / 360.0;
        constexpr auto Rad2Deg = 1.0 / Deg2Rad;

        template<typename T>
        constexpr  T Max(T a, T b) noexcept
        {
            return std::max(a, b);
        }

        template<typename T>
        constexpr  T Min(T a, T b) noexcept
        {
            return std::min(a, b);
        }

        template<typename T>
        constexpr  T Abs(T f) noexcept
        {
            return scast<T>(std::abs(f));
        }

        template<typename T>
        constexpr  T Cos(T f) noexcept
        {
            return scast<T>(std::cos(f));
        }

        template<typename T>
        constexpr  T Acos(T f) noexcept
        {
            return scast<T>(std::acos(f));
        }

        template<typename T>
        constexpr  T Tan(T f) noexcept
        {
            return scast<T>(std::tan(f));
        }

        template<typename T>
        constexpr  T Atan(T f) noexcept
        {
            return scast<T>(std::atan(f));
        }

        template<typename T>
        constexpr  T Sin(T f) noexcept
        {
            return scast<T>(std::sin(f));
        }

        template<typename T>
        constexpr  T Asin(T f) noexcept
        {
            return scast<T>(std::asin(f));
        }

        template<typename T>
        constexpr  T Atan2(T y, T x) noexcept
        {
            return scast<T>(std::atan2(y, x));
        }

        template<typename T>
        constexpr  T Sqrt(T f) noexcept
        {
            return scast<T>(std::sqrt(f));
        }

        template<typename T>
        constexpr  T Approximately(T a, T b) noexcept
        {
            return Abs(b - a) < Max(scast<T>(0.000001) * Max(Abs(a), Abs(b)), Epsilon<T> *scast<T>(8));
        }

        template<typename T>
        constexpr  T Pow(T f, T p) noexcept
        {
            return scast<T>(std::pow(f, p));
        }

        template<typename T>
        constexpr  T Exp(T power) noexcept
        {
            return scast<T>(std::exp(power));
        }

        template<typename T>
        constexpr  T Log(T n, T b) noexcept
        {
            return scast<T>(std::log(n) / std::log(b));
        }

        template<typename T>
        constexpr  T Log(T f) noexcept
        {
            return scast<T>(std::log(f));
        }

        template<typename T>
        constexpr  T Log10(T f) noexcept
        {
            return scast<T>(std::log10(f));
        }

        template<typename T>
        constexpr  T Log2(T f) noexcept
        {
            return scast<T>(std::log2(f));
        }

        template<typename T>
        constexpr  T Ceil(T f) noexcept
        {
            return scast<T>(std::ceil(f));
        }

        template<typename T>
        constexpr  T Floor(T f) noexcept
        {
            return scast<T>(std::floor(f));
        }

        template<typename T>
        constexpr  T Round(T f) noexcept
        {
            return scast<T>(std::round(f));
        }

        template<typename T>
        constexpr  i32 RountToInt(T f) noexcept
        {
            return scast<i32>(std::lroundf(f));
        }

        template<typename T>
        constexpr  i32 CeilToInt(T f) noexcept
        {
            return RoundToInt(std::ceil(f));
        }

        template<typename T>
        constexpr  i32 FloorToInt(T f) noexcept
        {
            return RoundToInt(Floor(f));
        }

        template<typename T>
        constexpr  T Sign(T f) noexcept
        {
            return f >= 0.0 ? scast<T>(1.0) : scast<T>(-1.0);
        }

        template<typename T>
        constexpr  T Clamp(T f, T min, T max) noexcept
        {
            return std::clamp(f, min, max);
        }

        template<typename T>
        constexpr  T Clamp01(T f) noexcept
        {
            return Clamp(f, scast<T>(0.0), scast<T>(1.0));
        }

        template<typename T>
        constexpr  T Lerp(T start, T end, T t) noexcept
        {
            return start + (end - start) * Clamp01(t);
        }

        template<typename T>
        constexpr  T LerpUnclamped(T a, T b, T t) noexcept
        {
            return a + (b - a) * t;
        }

        template<typename T>
        constexpr  T MoveTowards(T start, T end, T maxDelta) noexcept
        {
            if (Abs(end - start) <= maxDelta)
            {
                return end;
            }
            return start + Sign(end) * maxDelta;
        }

        template<typename T>
        constexpr  T SmoothStep(T start, T end, T t) noexcept
        {
            t = Clamp01(t);
            t = -scast<T>(2.0) * t * t * t + scast<T>(3.0) * t * t;
            return end * t + start * (scast<T>(1.0) - t);
        }

        template<typename T>
        constexpr  T InverseLerp(T a, T b, T v) noexcept
        {
            if (a != b)
                return Clamp01((v - a) / (b - a));
            else
                return scast<T>(0.0);
        }

    }
}