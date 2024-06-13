#include "nkseedmutation.hpp"

namespace alggen
{
namespace mutation
{

NKSeedMutation::NKSeedMutation(std::uint32_t seed, std::uint32_t matrix_mutation, std::uint32_t links_mutation) : SeedMutation(seed), matrix_mutation_(matrix_mutation), links_mutation_(links_mutation)
{

}

void NKSeedMutation::requiredForVTable() const
{

}

} // mutation namespace
namespace neighborhood
{

NKSeedNeighborhood::NKSeedNeighborhood(std::uint32_t matrix_mutation_default_value, std::uint32_t links_mutation_default_value, std::uint32_t n, std::uint32_t k) : SeedNeighborhood(), matrix_mutation_parameter_(matrix_mutation_default_value), links_mutation_parameter_(links_mutation_default_value), matrix_size_(n*(1 << (k+1))), links_size_(n*(k+1)), generator_(static_cast<unsigned int>(rand()))
{

}

void NKSeedNeighborhood::setNewSolutionPvt(std::shared_ptr<alggen::base::Solution> const&)
{

}

std::shared_ptr<alggen::base::Mutation> NKSeedNeighborhood::nextNeighborPvt()
{
	std::binomial_distribution<unsigned int> distribution_matrix_mutation(matrix_size_,static_cast<double>(matrix_mutation_parameter_)/static_cast<double>(matrix_size_));
	std::binomial_distribution<unsigned int> distribution_links_mutation(links_size_,static_cast<double>(links_mutation_parameter_)/static_cast<double>(links_size_));

	std::uint32_t matrix_mutation = 0;
	std::uint32_t links_mutation = 0;
    while(matrix_mutation == 0 && links_mutation == 0)
    {
        matrix_mutation = distribution_matrix_mutation(generator_);
        links_mutation = distribution_links_mutation(generator_);
    }

	return std::make_shared<alggen::mutation::NKSeedMutation>(static_cast<std::uint32_t>(rand()), matrix_mutation, links_mutation);
}

void NKSeedNeighborhood::acceptMutationPvt(std::shared_ptr<alggen::base::Mutation> const& m)
{
    auto mutation = std::dynamic_pointer_cast<alggen::mutation::NKSeedMutation>(m);

    matrix_mutation_parameter_ = mutation->getMatrixMutation();
    links_mutation_parameter_ = mutation->getLinksMutation();
}

} // neighborhood namespace
} // alggen namespace
