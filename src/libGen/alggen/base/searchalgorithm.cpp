#include "searchalgorithm.hpp"

namespace alggen
{
namespace base
{

SearchAlgorithm::SearchAlgorithm(Function * fobj, std::shared_ptr<Solution> s) : fobj_(fobj->createCopy()), sol_(s)
{

}

SearchAlgorithm::SearchAlgorithm(std::shared_ptr<Function> fobj, std::shared_ptr<Solution> s) : fobj_(fobj), sol_(s)
{

}

void SearchAlgorithm::changeObjecitveFunction(std::shared_ptr<Function> fobj)
{
	fobj_ = fobj;
}

std::uint64_t SearchAlgorithm::operator()() const
{
	sol_->randomize();
	return search();
}

std::uint64_t SearchAlgorithm::operator()(std::shared_ptr<Solution> s) const
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
