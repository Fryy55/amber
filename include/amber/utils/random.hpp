#pragma once

#include <amber/prelude.hpp> // IWYU pragma: keep

#include <random>


namespace amber::utils {

template <typename T>
	requires std::is_arithmetic_v<T>
inline T random(T min, T max) {
	thread_local std::mt19937_64 mt{std::random_device{}()};

	if constexpr (std::is_integral_v<T>) {
		std::uniform_int_distribution<T> dist(min, max);
		return dist(mt);
	} else {
		std::uniform_real_distribution<T> dist(min, max);
		return dist(mt);
	}
}

} // namespace amber::utils