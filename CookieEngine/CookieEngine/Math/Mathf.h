#pragma once
#include <Usings.h>
#include <utility>
#include <limits>
#include <numbers>
#include <algorithm>
#include <numbers>
namespace cookie
{
    namespace MathT
    {
        template<typename T>
        constexpr auto Epsilon = std::numeric_limits<T>::epsilon();
        constexpr auto Epsilonf = Epsilon<f32>;
        template<typename T>
        constexpr auto Infinity = std::numeric_limits<T>::infinity();
        constexpr auto Infinityf = Infinity<f32>;
        constexpr double PI = 3.141592653589793238463;
        constexpr auto Deg2Radf = PI * 2.0f / 360.0f;
        constexpr auto Rad2Degf = 1.0f / Deg2Radf;
        constexpr auto Deg2Rad = PI * 2.0 / 360.0;
        constexpr auto Rad2Deg = 1.0 / Deg2Rad;

        template<typename T>
        constexpr inline T Max(T a, T b)
        {
            return a > b ? a : b;
        }

        template<typename T>
        inline T Min(T a, T b)
        {
            return a < b ? a : b;
        }

        template<typename T>
        inline T Abs(T f)
        {
            return scast<T>(std::abs(f));
        }

        template<typename T>
        inline T Cos(T f)
        {
            return scast<T>(std::cos(f));
        }

        template<typename T>
        inline T Acos(T f)
        {
            return scast<T>(std::acos(f));
        }

        template<typename T>
        inline T Tan(T f)
        {
            return scast<T>(std::tan(f));
        }

        template<typename T>
        inline T Atan(T f)
        {
            return scast<T>(std::atan(f));
        }

        template<typename T>
        inline T Sin(T f)
        {
            return scast<T>(std::sin(f));
        }

        template<typename T>
        inline T Asin(T f)
        {
            return scast<T>(std::asin(f));
        }

        template<typename T>
        inline T Atan2(T y, T x)
        {
            return scast<T>(std::atan2(y, x));
        }

        template<typename T>
        inline T Sqrt(T f)
        {
            return scast<T>(std::sqrt(f));
        }

        template<typename T>
        inline T Approximately(T a, T b)
        {
            return Abs(b - a) < Max(scast<T>(0.000001) * Max(Abs(a), Abs(b)), Epsilon<T> *scast<T>(8));
        }

        template<typename T>
        inline T Pow(T f, T p)
        {
            return scast<T>(std::pow(f, p));
        }

        template<typename T>
        inline T Exp(T power)
        {
            return scast<T>(std::exp(power));
        }

        template<typename T>
        inline T Log(T n, T b)
        {
            return scast<T>(std::log(n) / std::log(b));
        }

        template<typename T>
        inline T Log(T f)
        {
            return scast<T>(std::log(f));
        }

        template<typename T>
        inline T Log10(T f)
        {
            return scast<T>(std::log10(f));
        }

        template<typename T>
        inline T Log2(T f)
        {
            return scast<T>(std::log2(f));
        }

        template<typename T>
        inline T Ceil(T f)
        {
            return scast<T>(std::ceil(f));
        }

        template<typename T>
        inline T Floor(T f)
        {
            return scast<T>(std::floor(f));
        }

        template<typename T>
        inline T Round(T f)
        {
            return scast<T>(std::round(f));
        }

        template<typename T>
        inline i32 RountToInt(T f)
        {
            return scast<i32>(std::lroundf(f));
        }

        template<typename T>
        inline i32 CeilToInt(T f)
        {
            return RoundToInt(Ceil(f));
        }

        template<typename T>
        inline i32 FloorToInt(T f)
        {
            return RoundToInt(Floor(f));
        }

        template<typename T>
        inline T Sign(T f)
        {
            return f >= 0.0 ? scast<T>(1.0) : scast<T>(-1.0);
        }

        template<typename T>
        inline T Clamp(T f, T min, T max)
        {
            return std::clamp(f, min, max);
        }

        template<typename T>
        inline T Clamp01(T f)
        {
            return Clamp(f, scast<T>(0.0), scast<T>(1.0));
        }

        template<typename T>
        inline T Lerp(T start, T end, T t)
        {
            return start + (end - start) * Clamp01(t);
        }

        template<typename T>
        inline T LerpUnclamped(T a, T b, T t)
        {
            return a + (b - a) * t;
        }

        template<typename T>
        inline T MoveTowards(T start, T end, T maxDelta)
        {
            if (Abs(end - start) <= maxDelta)
            {
                return end;
            }
            return start + Sign(end) * maxDelta;
        }

        template<typename T>
        inline T SmoothStep(T start, T end, T t)
        {
            t = Clamp01(t);
            t = -scast<T>(2.0) * t * t * t + scast<T>(3.0) * t * t;
            return end * t + start * (scast<T>(1.0) - t);
        }

        template<typename T>
        inline T InverseLerp(T a, T b, T v)
        {
            if (a != b)
                return Clamp01((v - a) / (b - a));
            else
                return scast<T>(0.0);
        }

        
    }
}