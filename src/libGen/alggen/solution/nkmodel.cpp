#include "nkmodel.hpp"
#include <alggen/neighborhood/nkseedmutation.hpp>
#include <random>

namespace alggen
{
namespace solution
{

NKModel::NKModel(problem::NK const& nk) : base::Solution(), problem::NK(nk), matrix_distribution_(0u, static_cast<std::uint32_t>(n_*pow2k1_-1)), links_distribution_(0u, static_cast<std::uint32_t>(n_*k_))
{

}

NKModel::NKModel(NKModel const& bt) : base::Solution(), problem::NK(bt), matrix_distribution_(0u, static_cast<std::uint32_t>(n_*pow2k1_-1)), links_distribution_(0u, static_cast<std::uint32_t>(n_*k_))
{

}

NKModel::NKModel(std::string const& file_path) : base::Solution(), problem::NK(file_path), matrix_distribution_(0u, static_cast<std::uint32_t>(n_*pow2k1_-1)), links_distribution_(0u, static_cast<std::uint32_t>(n_*k_))
{

}

NKModel::NKModel(std::size_t n, std::size_t k) : base::Solution(), problem::NK(n, k), matrix_distribution_(0u, static_cast<std::uint32_t>(n_*pow2k1_-1)), links_distribution_(0u, static_cast<std::uint32_t>(n_*k_))
{

}

void NKModel::copySolution(std::shared_ptr<base::Solution> const& s)
{
	auto derivedSol = std::dynamic_pointer_cast<NKModel>(s);

    problem::NK::copyFunction(derivedSol);
    matrix_distribution_ = utils::DrawWithoutReplacement(0u, static_cast<std::uint32_t>(n_*pow2k1_-1));
    links_distribution_ = utils::DrawWithoutReplacement(0u, static_cast<std::uint32_t>(n_*k_));
}

void NKModel::copyFunction(std::shared_ptr<base::Function> f)
{
	copySolution(std::dynamic_pointer_cast<NKModel>(f));
    matrix_distribution_ = utils::DrawWithoutReplacement(0u, static_cast<std::uint32_t>(n_*pow2k1_-1));
    links_distribution_ = utils::DrawWithoutReplacement(0u, static_cast<std::uint32_t>(n_*k_));
}

std::shared_ptr<base::Solution> NKModel::createSolutionCopy() const
{
	return std::make_shared<NKModel>(*this);
}

std::shared_ptr<base::Function> NKModel::createFunctionCopy() const
{
	return std::make_shared<NKModel>(*this);
}

void NKModel::mutate(std::shared_ptr<base::Mutation> const& m)
{
    auto mutation = std::dynamic_pointer_cast<alggen::mutation::NKSeedMutation>(m);
	std::default_random_engine generator(mutation->getSeed());

	std::uniform_int_distribution<unsigned int> offset_mutation_matrix(1,1000000);
	std::uniform_int_distribution<unsigned int> offset_mutation_links(1,static_cast<std::uint32_t>(n_-1));

	for(unsigned int i(0); i < mutation->getMatrixMutation(); ++i)
	{
		unsigned int index = matrix_distribution_(generator);
		unsigned int tmp = matrix_[index];
		tmp += offset_mutation_matrix(generator);
		tmp %= 1000001;
		matrix_[index] = tmp;
	}

	for(unsigned int i(0); i < mutation->getLinksMutation(); ++i)
	{
		unsigned int index = links_distribution_(generator);

		for(unsigned int j(0); j < var_in_links_[links_[index]].size(); ++j)
		{
			if(var_in_links_[links_[index]][j] == index/k1_)
			{
				var_in_links_[links_[index]][j] = var_in_links_[links_[index]].back();
				var_in_links_[links_[index]].pop_back();

				break;
			}
		}

		links_[index] += offset_mutation_links(generator);
		links_[index] %= n_;

		var_in_links_[links_[index]].push_back(static_cast<std::uint16_t>(index/k1_));
	}
}

void NKModel::reverseMutation(std::shared_ptr<base::Mutation> const& m)
{
    auto mutation = std::dynamic_pointer_cast<alggen::mutation::NKSeedMutation>(m);
	std::default_random_engine generator(mutation->getSeed());

	std::uniform_int_distribution<unsigned int> offset_mutation_matrix(1,1000000);
	std::uniform_int_distribution<unsigned int> offset_mutation_links(1,static_cast<std::uint32_t>(n_-1));

	for(unsigned int i(0); i < mutation->getMatrixMutation(); ++i)
	{
		unsigned int index = matrix_distribution_(generator);
		unsigned int tmp = matrix_[index];
		tmp += 1000001-offset_mutation_matrix(generator);
		tmp %= 1000001;
		matrix_[index] = tmp;
	}

	for(unsigned int i(0); i < mutation->getLinksMutation(); ++i)
	{
		unsigned int index = links_distribution_(generator);

		for(unsigned int j(0); j < var_in_links_[links_[index]].size(); ++j)
		{
			if(var_in_links_[links_[index]][j] == index/k1_)
			{
				var_in_links_[links_[index]][j] = var_in_links_[links_[index]].back();
				var_in_links_[links_[index]].pop_back();

				break;
			}
		}

		links_[index] += n_ - offset_mutation_links(generator);
		links_[index] %= n_;

		var_in_links_[links_[index]].push_back(static_cast<std::uint16_t>(index/k1_));
	}
}

void NKModel::randomize()
{
    problem::NK::randomize();
}

} // solution namespace
} // alggen namespace
