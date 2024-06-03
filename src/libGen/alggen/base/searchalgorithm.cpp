#include "searchalgorithm.hpp"

namespace alggen
{
namespace base
{

SearchAlgorithm::SearchAlgorithm(std::shared_ptr<Function> fobj, std::shared_ptr<Solution> s) : fobj_(fobj), sol_(s)
{

}

void SearchAlgorithm::changeObjectiveFunction(std::shared_ptr<Function> fobj)
{
	fobj_ = fobj;
}

Fitness SearchAlgorithm::operator()() const
{
	sol_->randomize();
	return search();
}

Fitness SearchAlgorithm::operator()(std::shared_ptr<Solution> s) const
{
	sol_->copy(s);
	return search();
}

void SearchAlgorithm::getResultCopy(std::shared_ptr<Solution> s) const
{
	s->copy(sol_);
}

std::shared_ptr<Solution> SearchAlgorithm::getResultCopy() const
{
	return sol_->createCopy();
}

void SearchAlgorithm::requiredForVTable() const
{

}

}
}
