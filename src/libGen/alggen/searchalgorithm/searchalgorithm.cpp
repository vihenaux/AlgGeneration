#include "searchalgorithm.hpp"

namespace alggen
{
namespace searchalgorithm
{

SearchAlgorithm::SearchAlgorithm(base::Function * fobj, std::shared_ptr<base::Solution> s) : fobj_(fobj->createCopy()), sol_(s->createCopy())
{

}

SearchAlgorithm::SearchAlgorithm(std::shared_ptr<base::Function> fobj, std::shared_ptr<base::Solution> s) : fobj_(fobj->createCopy()), sol_(s->createCopy())
{

}

void SearchAlgorithm::changeObjecitveFunction(std::shared_ptr<base::Function> fobj)
{
	fobj_ = fobj;
}

std::uint64_t SearchAlgorithm::operator()() const
{
	sol_->randomize();
	return search();
}

std::uint64_t SearchAlgorithm::operator()(std::shared_ptr<base::Solution> s) const
{
	sol_->copy(s);
	return search();
}

void SearchAlgorithm::getResultCopy(std::shared_ptr<base::Solution> s) const
{
	s->copy(sol_);
}

std::shared_ptr<base::Solution> SearchAlgorithm::getResultCopy() const
{
	return sol_->createCopy();
}

void SearchAlgorithm::requiredForVTable() const
{

}

}
}
