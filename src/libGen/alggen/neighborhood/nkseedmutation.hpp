#pragma once

#include "seedmutation.hpp"
#include <vector>
#include <random>

namespace alggen
{
namespace mutation
{

class NKSeedMutation : public SeedMutation
{
	public:

	NKSeedMutation(std::uint32_t seed, std::uint32_t matrix_mutation, std::uint32_t links_mutation);
	virtual ~NKSeedMutation() override = default;

    inline std::uint32_t getMatrixMutation() const { return matrix_mutation_; }
    inline std::uint32_t getLinksMutation() const { return links_mutation_; }

	private:

	virtual void requiredForVTable() const override;

    std::uint32_t matrix_mutation_;
    std::uint32_t links_mutation_;
};

} // mutation namespace
namespace neighborhood
{

class NKSeedNeighborhood : public SeedNeighborhood
{
	public:

	NKSeedNeighborhood(std::uint32_t matrix_mutation_default_value, std::uint32_t links_mutation_default_value, std::uint32_t n, std::uint32_t k);
	virtual ~NKSeedNeighborhood() override = default;

	private:

	virtual void setNewSolutionPvt(std::shared_ptr<alggen::base::Solution> const& s) override;
	virtual std::shared_ptr<alggen::base::Mutation> nextNeighborPvt() override;
	virtual void acceptMutationPvt(std::shared_ptr<alggen::base::Mutation> const& m) override;

    std::uint32_t matrix_mutation_parameter_;
    std::uint32_t links_mutation_parameter_;
    std::uint32_t matrix_size_;
    std::uint32_t links_size_;
	std::default_random_engine generator_;
};

} // neighborhood namespace
} // alggen namespace
