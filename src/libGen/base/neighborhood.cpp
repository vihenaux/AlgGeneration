#include "neighborhood.hpp"

Neighborhood::~Neighborhood()
{

}

void Neighborhood::setNewSolution(std::shared_ptr<Solution> const& s)
{
	numberOfNeighborsDiscarded_ = 0;

	setNewSolutionPvt(s);
}

std::shared_ptr<Mutation> Neighborhood::nextNeighbor()
{
	++numberOfNeighborsDiscarded_;
	return nextNeighborPvt();
}

void Neighborhood::acceptMutation(std::shared_ptr<Mutation> const& m)
{
	numberOfNeighborsDiscarded_ = 0;

	acceptMutationPvt(m);
}

std::uint32_t Neighborhood::getNumberOfNeighborsDiscarded() const
{
	return numberOfNeighborsDiscarded_;
}
