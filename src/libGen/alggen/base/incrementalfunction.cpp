#include "incrementalfunction.hpp"

namespace alggen
{
namespace base
{

std::uint64_t IncrementalFunction::operator()(std::shared_ptr<Solution> const& s) const
{
	setNewSolution(s);
	return Function::operator()(s);
}

std::uint64_t IncrementalFunction::operator()(std::shared_ptr<Mutation> const& m) const
{
	solutionEvaluated();

	return incremental_evaluation(m);
}

void IncrementalFunction::setNewSolution(std::shared_ptr<Solution> const& s) const
{
	if(!lastSolutionEvaluated_)
	{
		lastSolutionEvaluated_ = s->createCopy();
	} else {
		lastSolutionEvaluated_->copy(s);
	}
}

void IncrementalFunction::mutateLastSolution(std::shared_ptr<Mutation> const& m) const
{
	lastSolutionEvaluated_->mutate(m);
}

std::uint64_t IncrementalFunction::incremental_evaluation(std::shared_ptr<Mutation> const& m) const
{
	// Evaluate the solution with the mutation
	lastSolutionEvaluated_->mutate(m);
	std::uint64_t evalMutation = evaluate(lastSolutionEvaluated_);
	// Then reverse the mutation
	lastSolutionEvaluated_->reverseMutation(m);

	return evalMutation;
}

} // base namespace
} // alggen namespace
