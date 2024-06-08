#include "onemax.hpp"
#include <alggen/neighborhood/oneflip.hpp>

namespace alggen
{
namespace problem
{

OneMax::OneMax(std::size_t size) : size_(size), sol_(size) {}

void OneMax::setNewSolution(std::shared_ptr<base::Solution> const& s) const
{
	sol_.copySolution(s);
}

void OneMax::mutateLastSolution(std::shared_ptr<base::Mutation> const& m) const
{
	score_ = operator()(m);
	sol_.mutate(m);
}

std::shared_ptr<base::Function> OneMax::createFunctionCopy() const
{
	return std::make_shared<OneMax>(size_);
}

void OneMax::copyFunction(std::shared_ptr<base::Function> f)
{
	size_ = std::dynamic_pointer_cast<OneMax>(f)->size_;
}

std::shared_ptr<base::Solution> OneMax::createSolution() const
{
	return std::make_shared<solution::BitString>(size_);
}

base::Fitness OneMax::evaluate(std::shared_ptr<base::Solution> const&) const
{
	score_ = 0;
	for(std::size_t i(0); i < size_; ++i)
	{
		score_ += sol_[i];
	}
	return score_;
}

base::Fitness OneMax::incremental_evaluation(std::shared_ptr<base::Mutation> const& m) const
{
	bool bitValue = sol_[std::dynamic_pointer_cast<mutation::OneFlip>(m)->getBit()];
	return score_ - bitValue + !bitValue;
}

}
}
