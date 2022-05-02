#pragma once

#include <cstdint>
#include <memory>

#include "solution.hpp"
#include "mutation.hpp"

namespace alggen
{
namespace base
{

/* A class that represents a neighborhood.
 * A neighborhood must be able to generate neighbors/mutation
 * The number of neighbors generated between two accepted one.
 */
class Neighborhood
{
	public:

	virtual ~Neighborhood();

	void setNewSolution(std::shared_ptr<Solution> const& s);

	std::shared_ptr<Mutation> nextNeighbor();
	void acceptMutation(std::shared_ptr<Mutation> const& m);
	virtual bool neighborAvailable() const = 0;

	std::uint32_t getNumberOfNeighborsDiscarded() const;

	private:

	virtual void setNewSolutionPvt(std::shared_ptr<Solution> const& s) = 0;

	virtual std::shared_ptr<Mutation> nextNeighborPvt() = 0;
	virtual void acceptMutationPvt(std::shared_ptr<Mutation> const& m) = 0;

	std::uint32_t numberOfNeighborsDiscarded_{0};
};

} // base namespace
} // alggen namespace
