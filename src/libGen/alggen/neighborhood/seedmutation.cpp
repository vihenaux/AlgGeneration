#include "seedmutation.hpp"

namespace alggen
{
namespace mutation
{

SeedMutation::SeedMutation(std::uint32_t seed) : seed_(seed)
{

}

void SeedMutation::requiredForVTable() const
{

}

} // mutation namespace

namespace neighborhood
{

SeedNeighborhood::SeedNeighborhood()
{

}

bool SeedNeighborhood::neighborAvailable() const
{
    return true;
}

void SeedNeighborhood::setNewSolutionPvt(std::shared_ptr<alggen::base::Solution> const&)
{

}

std::shared_ptr<alggen::base::Mutation> SeedNeighborhood::nextNeighborPvt()
{
	return std::make_shared<alggen::mutation::SeedMutation>(rand());
}

void SeedNeighborhood::acceptMutationPvt(std::shared_ptr<alggen::base::Mutation> const&)
{

}

} // neighborhood namespace
} // alggen namespace
