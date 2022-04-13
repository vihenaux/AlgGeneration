#pragma once

#include <memory>

#include "function.hpp"
#include "mutation.hpp"

class IncrementalFunction : public Function
{
	public:

	// Needed to store the solution
	template<class DerivedFromSolution>
	std::uint64_t operator()(DerivedFromSolution const& s) const
	{
		setNewSolution(s);
		Function::operator()(s);
	}
	// Assign an evaluation to the mutation of the last solution evaluated
	std::uint64_t operator()(Mutation const& m) const;

	// Force a specific last solution evaluated
	template<class DerivedFromSolution>
	void setNewSolution(Solution const& s) const
	{
		std::unique_ptr<DerivedFromSolution> newSolution{new DerivedFromSolution(s)};
		lastSolutionEvaluated_ = newSolution;
	}
	void mutateLastSolution(Mutation const& m) const;

	private:

	virtual std::uint64_t incremental_evaluation(Mutation const& s) const;

	mutable std::unique_ptr<Solution> lastSolutionEvaluated_{nullptr};
};
