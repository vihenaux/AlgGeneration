#include "function.hpp"

std::uint64_t Function::operator()(Solution const& s) const
{
	solutionEvaluated();

	return evaluate(s);
}

std::uint64_t Function::getNumberOfCalls() const
{
	return numberOfCalls_;
}

void Function::solutionEvaluated() const
{
	++numberOfCalls_;
}
