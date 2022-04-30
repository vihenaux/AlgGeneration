#pragma once

#include <memory>

#include "function.hpp"
#include "solution.hpp"
#include "mutation.hpp"

class IncrementalFunction : public Function
{
	public:

	// Needed to store the solution
	std::uint64_t operator()(std::shared_ptr<Solution> const& s) const;
	// Assign an evaluation to the mutation of the last solution evaluated
	std::uint64_t operator()(std::shared_ptr<Mutation> const& m) const;

	// Needs to call 'setNewSolutionPvt' with the right template
	virtual void setNewSolution(std::shared_ptr<Solution> const& s) const = 0;

	// The following method should be overridden to avoid a copy of the mutation if possible
	virtual void mutateLastSolution(std::shared_ptr<Mutation> const& m) const;

	protected:

	// Force a specific last solution evaluated
	template<class DerivedFromSolution>
	void setNewSolutionPvt(std::shared_ptr<Solution> const& s)
	{
		std::shared_ptr<DerivedFromSolution> newSolution{new DerivedFromSolution(std::dynamic_pointer_cast<DerivedFromSolution>(s))};
		lastSolutionEvaluated_ = newSolution;
	}

	private:

	virtual std::uint64_t incremental_evaluation(std::shared_ptr<Mutation> const& s) const;

	mutable std::shared_ptr<Solution> lastSolutionEvaluated_{nullptr};
};
