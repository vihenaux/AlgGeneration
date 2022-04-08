#pragma once

#include <cstdint>
#include <atomic>

#include "solution.hpp"

// A class that represents functions.
class Function
{
	public:

	// Assign an evaluation to the solution passed
	std::uint64_t operator()(Solution const& s) const;

	// Get the number of solution this function evaluated
	std::uint64_t getNumberOfCalls() const;

	private:

	virtual std::uint64_t evaluate(Solution const& s) const = 0;

	mutable std::atomic<std::uint64_t> numberOfCalls_{0};
};
