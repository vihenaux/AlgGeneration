#pragma once

#include <cstdint>
#include <atomic>
#include <memory>

#include "solution.hpp"

namespace alggen
{
namespace base
{

// A class that represents functions.
class Function
{
	public:

	virtual ~Function();

	// Assign an evaluation to the solution passed
	std::uint64_t operator()(std::shared_ptr<Solution> const& s) const;

	// Get the number of solution this function evaluated
	std::uint64_t getNumberOfCalls() const;

	// Needs to return a random solution to be a starting point
	virtual std::shared_ptr<Solution> getRandomSolution() const = 0;

	protected:

	void solutionEvaluated() const;
	virtual std::uint64_t evaluate(std::shared_ptr<Solution> const& s) const = 0;

	private:

	mutable std::atomic<std::uint64_t> numberOfCalls_{0};
};

} // base namespace
} // alggen namespace
