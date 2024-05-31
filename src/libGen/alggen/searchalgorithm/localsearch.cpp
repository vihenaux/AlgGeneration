#include "localsearch.hpp"

namespace alggen
{
namespace searchalgorithm
{

LocalSearch::LocalSearch(std::shared_ptr<base::Function> fobj, std::shared_ptr<base::Solution> s, std::shared_ptr<base::Neighborhood> n) : base::SearchAlgorithm(fobj,s), neighborhood_(n)
{
	
}

base::Fitness LocalSearch::search() const
{
	neighborhood_->setNewSolution(sol_);
	base::Fitness score = (*fobj_)(sol_);

	while(neighborhood_->neighborAvailable())
	{
		auto neighbor = neighborhood_->nextNeighbor();
        base::Fitness tmpScore = (*fobj_)(neighbor);
		if(score < tmpScore)
		{
			score = tmpScore;
			sol_->mutate(neighbor);
			neighborhood_->acceptMutation(neighbor);
			fobj_->mutateLastSolution(neighbor);
		}
	}

	return score;
}

}
}
