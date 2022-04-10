#include "incrementalfunction.hpp"

std::uint64_t IncrementalFunction::operator()(Mutation const& m) const
{
	solutionEvaluated();

	return incremental_evaluation(m);
}

void IncrementalFunction::mutateLastSolution(Mutation const& m) const
{
	lastSolutionEvaluated_->mutate(m);
}

std::uint64_t IncrementalFunction::incremental_evaluation(Mutation const& m) const
{
	// Evaluate the solution with the mutation
	lastSolutionEvaluated_->mutate(m);
	std::uint64_t evalMutation = evaluate(*lastSolutionEvaluated_);
	// Then reverse the mutation
	lastSolutionEvaluated_->reverseMutation(m);

	return evalMutation;
}