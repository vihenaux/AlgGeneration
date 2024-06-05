#pragma once

#include <alggen/base/neighborhood.hpp>

namespace alggen
{
namespace mutation
{

// seed mutation for any random based solution mutation
class SeedMutation : public base::Mutation
{
	public:

	SeedMutation(std::uint32_t seed);
	virtual ~SeedMutation() override = default;

	inline std::size_t getSeed() const { return seed_; }

	private:

	virtual void requiredForVTable() const override;

	std::uint32_t seed_;
};

} // mutation namespace
namespace neighborhood
{

class SeedNeighborhood final : public alggen::base::Neighborhood
{
	public:

	SeedNeighborhood();
	virtual ~SeedNeighborhood() final = default;

	virtual bool neighborAvailable() const final;

	private:

	virtual void setNewSolutionPvt(std::shared_ptr<alggen::base::Solution> const& s) final;
	virtual std::shared_ptr<alggen::base::Mutation> nextNeighborPvt() final;
	virtual void acceptMutationPvt(std::shared_ptr<alggen::base::Mutation> const& m) final;
};

} // neighborhood namespace
} // alggen namespace
