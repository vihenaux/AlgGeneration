#include "neighborhood.hpp"

Neighborhood::~Neighborhood()
{

}

Mutation Neighborhood::nextNeighbor()
{
	return nextNeighborPvt();
}

void Neighborhood::acceptMutation(Mutation const& m)
{
	numberOfNeighborsDiscarded_ = 0;

	acceptMutationPvt(m);
}

std::uint32_t Neighborhood::getNumberOfNeighborsDiscarded() const
{
	return numberOfNeighborsDiscarded_;
}
