#pragma once

#include <alggen/base/neighborhood.hpp>
#include <alggen/searchalgorithm/localsearch.hpp>

namespace alggen
{
namespace searchalgorithm
{

class IteratedLocalSearch : public LocalSearch
{
    public:

    IteratedLocalSearch() = delete;
    IteratedLocalSearch(std::shared_ptr<base::Function> fobj, std::shared_ptr<base::Solution> s, std::shared_ptr<base::Neighborhood> n, unsigned int perturbations, unsigned int max_fobj_calls);
    ~IteratedLocalSearch() override = default;

    private:

    unsigned int perturbations_;
    unsigned int max_fobj_calls_;

    virtual base::Fitness search() const override;
};

}
}
