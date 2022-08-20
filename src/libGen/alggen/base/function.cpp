#include "function.hpp"

namespace alggen
{
namespace base
{

Function::~Function()
{
	
}

std::uint64_t Function::getNumberOfCalls() const
{
	return numberOfCalls_;
}

void Function::solutionEvaluated() const
{
	++numberOfCalls_;
}

std::uint64_t Function::operator()(std::shared_ptr<Solution> const& s) const
{
	setNewSolution(s);
	solutionEvaluated();

	return evaluate(s);
}

std::uint64_t Function::operator()(std::shared_ptr<Mutation> const& m) const
{
	solutionEvaluated();

	return incremental_evaluation(m);
}

void Function::setNewSolution(std::shared_ptr<Solution> const& s) const
{
	if(!lastSolutionEvaluated_)
	{
		lastSolutionEvaluated_ = s->createCopy();
	} else {
		lastSolutionEvaluated_->copy(s);
	}
}

void Function::mutateLastSolution(std::shared_ptr<Mutation> const& m) const
{
	lastSolutionEvaluated_->mutate(m);
}

std::uint64_t Function::incremental_evaluation(std::shared_ptr<Mutation> const& m) const
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
