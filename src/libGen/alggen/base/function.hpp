#pragma once

#include <cstdint>
#include <atomic>
#include <memory>

class Solution;
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

	// Get the number of solution this function evaluated
	std::uint64_t getNumberOfCalls() const;

	// Assign an evaluation to the solution passed and stores the solution for mutation evaluation
	std::uint64_t operator()(std::shared_ptr<Solution> const& s) const;
	// Assign an evaluation to the mutation of the last solution evaluated
	std::uint64_t operator()(std::shared_ptr<Mutation> const& m) const;

	virtual void setNewSolution(std::shared_ptr<Solution> const& s) const;
	virtual void mutateLastSolution(std::shared_ptr<Mutation> const& m) const;

	virtual std::shared_ptr<Function> createCopy() const = 0;
	virtual void copy(std::shared_ptr<Function> f) = 0;

	private:

	void solutionEvaluated() const;
	virtual std::uint64_t evaluate(std::shared_ptr<Solution> const& s) const = 0;
	virtual std::uint64_t incremental_evaluation(std::shared_ptr<Mutation> const& m) const;

	mutable std::atomic<std::uint64_t> numberOfCalls_{0};

	mutable std::shared_ptr<Solution> lastSolutionEvaluated_{nullptr};
};

} // base namespace
} // alggen namespace
