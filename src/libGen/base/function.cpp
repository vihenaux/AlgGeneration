#include "function.hpp"

namespace alggen
{
namespace base
{

Function::~Function()
{
	
}

std::uint64_t Function::operator()(std::shared_ptr<Solution> const& s) const
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

} // base namespace
} // alggen namespace
