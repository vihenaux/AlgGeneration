#pragma once

#include <memory>

#include "function.hpp"
#include "solution.hpp"
#include "mutation.hpp"

class IncrementalFunction : virtual public Function
{
	public:

	// Needed to store the solution
	std::uint64_t operator()(std::shared_ptr<Solution> const& s) const;
	// Assign an evaluation to the mutation of the last solution evaluated
	std::uint64_t operator()(std::shared_ptr<Mutation> const& m) const;

	virtual void setNewSolution(std::shared_ptr<Solution> const& s) const;
	virtual void mutateLastSolution(std::shared_ptr<Mutation> const& m) const;

	protected:

	virtual std::uint64_t incremental_evaluation(std::shared_ptr<Mutation> const& m) const;

	private:

	mutable std::shared_ptr<Solution> lastSolutionEvaluated_{nullptr};
};
