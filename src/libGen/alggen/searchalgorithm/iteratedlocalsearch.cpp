#include "iteratedlocalsearch.hpp"

namespace alggen
{
namespace searchalgorithm {

IteratedLocalSearch::IteratedLocalSearch(std::shared_ptr <base::Function> fobj, std::shared_ptr <base::Solution> s, std::shared_ptr <base::Neighborhood> n, unsigned int perturbations, unsigned int max_fobj_calls) : LocalSearch(fobj, s, n), perturbations_(perturbations), max_fobj_calls_(max_fobj_calls)
{

}

base::Fitness IteratedLocalSearch::search() const
{
    auto bestSolution = sol_->createCopy();
    base::Fitness best = (*fobj_)(sol_);

    while(fobj_->getNumberOfCalls() < max_fobj_calls_)
    {
        base::Fitness lsResult = LocalSearch::search();
        if(lsResult > best)
        {
            best = lsResult;
            bestSolution->copy(sol_);
        }

        neighborhood_->setNewSolution(sol_);
        for(unsigned int i(0); i < perturbations_; ++i)
        {
            auto neighbor = neighborhood_->nextNeighbor();
            sol_->mutate(neighbor);
            neighborhood_->acceptMutation(neighbor);
            fobj_->mutateLastSolution(neighbor);
        }
    }

    sol_->copy(bestSolution);
    return best;
}

}
}
