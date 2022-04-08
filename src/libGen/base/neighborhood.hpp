#pragma once

#include <cstdint>

#include "mutation.hpp"

/* A class that represents a neighborhood.
 * A neighborhood must be able to generate neighbors/mutation
 * The number of neighbors generated between two accepted one.
 */
class Neighborhood
{
	public:

	Mutation nextNeighbor();
	void acceptMutation(Mutation const& m);
	virtual bool neighborAvailable() const = 0;

	std::uint32_t getNumberOfNeighborsDiscarded() const;

	private:

	virtual Mutation nextNeighborPvt() = 0;
	virtual void acceptMutationPvt(Mutation const& m) = 0;

	std::uint32_t numberOfNeighborsDiscarded_{0};
};
