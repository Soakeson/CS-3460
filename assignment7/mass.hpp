#include <compare>
#include <cstdint>
#include <ratio>

namespace usu
{
    template <typename T, typename S = std::uint64_t>
    class mass
    {
      public:
        using conversion = T;
        using storage = S;
        mass();
        mass(S data);
        S count() const { return m_data; };

      private:
        S m_data;
    };

    template <typename T, typename S>
    mass<T, S>::mass() :
        m_data(0){};

    template <typename T, typename S>
    mass<T, S>::mass(S data) :
        m_data(data){};

    template <typename T, typename S>
    T mass_cast(S const& conv)
    {
        double S_to_grams = static_cast<double>(S::conversion::num) / static_cast<double>(S::conversion::den) * static_cast<double>(conv.count());
        double grams_to_T = static_cast<double>(T::conversion::den) / static_cast<double>(T::conversion::num) * S_to_grams;
        return mass<typename T::conversion, typename T::storage>(static_cast<typename T::storage>(grams_to_T));
    };

    template <typename T, typename S>
    T operator+(T const& lhs, S const& rhs)
    {
        return mass<typename T::conversion, typename T::storage>(lhs.count() + mass_cast<T>(rhs).count());
    }

    template <typename T, typename S>
    T operator+=(T& lhs, S const& rhs)
    {
        lhs = mass<typename T::conversion, typename T::storage>(lhs.count() + mass_cast<T>(rhs).count());
        return lhs;
    }

    template <typename T, typename S>
    T operator-(T const& lhs, S const& rhs)
    {
        return mass<typename T::conversion, typename T::storage>(lhs.count() - mass_cast<T>(rhs).count());
    }

    template <typename T, typename S>
    T operator-=(T& lhs, S const& rhs)
    {
        lhs = mass<typename T::conversion, typename T::storage>(lhs.count() - mass_cast<T>(rhs).count());
        return lhs;
    }

    template <typename T, typename S>
    S operator*(T const& lhs, S const& rhs)
    {
        return mass<typename S::conversion, typename S::storage>(static_cast<typename S::storage>(lhs) * rhs.count());
    }

    template <typename T, typename S>
    T operator*(T& lhs, S const& rhs)
    {
        return mass<typename T::conversion, typename T::storage>(lhs.count() * static_cast<typename T::storage>(rhs));
    }

    template <typename T, typename S>
    T operator*=(T& lhs, S const& rhs)
    {
        lhs = mass<typename T::conversion, typename T::storage>(lhs.count() * rhs);
        return lhs;
    }

    template <typename T, typename S>
    T operator/(T& lhs, S const& rhs)
    {
        return mass<typename T::conversion, typename T::storage>(lhs.count() / static_cast<typename T::storage>(rhs));
    }

    template <typename T, typename S>
    T operator/=(T& lhs, S const& rhs)
    {
        lhs = mass<typename T::conversion, typename T::storage>(lhs.count() / rhs);
        return lhs;
    }

    template <typename T, typename S>
    bool operator==(T const& lhs, S const& rhs)
    {
        return lhs.count() == mass_cast<T>(rhs).count();
    }

    template <typename T, typename S>
    auto operator<=>(T const& lhs, S const& rhs)
    {
        auto converted = mass_cast<T>(rhs);
        if constexpr (std::is_integral<typename T::storage>::value)
        {
            if (lhs.count() == converted.count())
            {
                return std::strong_ordering::equal;
            }
            else if (lhs.count() > converted.count())
            {
                return std::strong_ordering::greater;
            }
            else
            {
                return std::strong_ordering::less;
            }
        }
        else
        {
            if (lhs.count() == converted.count())
            {
                return std::partial_ordering::equivalent;
            }
            else if (lhs.count() > converted.count())
            {
                return std::partial_ordering::greater;
            }
            else if (lhs.count() < converted.count())
            {
                return std::partial_ordering::less;
            }
            return std::partial_ordering::unordered;
        }
    }

    using kilogram = mass<std::ratio<1000, 1>, double>;
    using gram = mass<std::ratio<1, 1>>;
    using microgram = mass<std::ratio<1, 1000000>>;
    using ounce = mass<std::ratio<45359237, 1600000>, double>;
    using pound = mass<std::ratio<45359237, 100000>, double>;
    using ton = mass<std::ratio<45359237, 50>, double>;

} // namespace usu
