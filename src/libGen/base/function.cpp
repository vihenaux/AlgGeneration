#include "function.hpp"

std::uint64_t Function::operator()(Solution const& s) const
{
	++numberOfCalls_;

	return evaluate(s);
}

std::uint64_t Function::getNumberOfCalls() const
{
	return numberOfCalls_;
}
