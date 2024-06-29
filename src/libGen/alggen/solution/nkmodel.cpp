#include "nkmodel.hpp"
#include <alggen/neighborhood/nkseedmutation.hpp>
#include <random>

namespace alggen
{
namespace solution
{

NKModel::NKModel(problem::NK const& nk) : nk_(nk), matrix_distribution_(0u, static_cast<std::uint32_t>(nk_.n_*nk_.pow2k1_-1)), links_distribution_(0u, static_cast<std::uint32_t>(nk_.n_*nk_.k_))
{

}

NKModel::NKModel(NKModel const& bt) : nk_(bt.nk_), matrix_distribution_(0u, static_cast<std::uint32_t>(nk_.n_*nk_.pow2k1_-1)), links_distribution_(0u, static_cast<std::uint32_t>(nk_.n_*nk_.k_))
{

}

NKModel::NKModel(std::string const& file_path) : nk_(file_path), matrix_distribution_(0u, static_cast<std::uint32_t>(nk_.n_*nk_.pow2k1_-1)), links_distribution_(0u, static_cast<std::uint32_t>(nk_.n_*nk_.k_))
{

}

NKModel::NKModel(std::size_t n, std::size_t k) : nk_(n, k), matrix_distribution_(0u, static_cast<std::uint32_t>(nk_.n_*nk_.pow2k1_-1)), links_distribution_(0u, static_cast<std::uint32_t>(nk_.n_*nk_.k_))
{

}

void NKModel::copySolution(std::shared_ptr<base::Solution> const& s)
{
	auto derivedSol = std::dynamic_pointer_cast<NKModel>(s);

    nk_.copyFunction(derivedSol);
    matrix_distribution_ = utils::DrawWithoutReplacement(0u, static_cast<std::uint32_t>(nk_.n_*nk_.pow2k1_-1));
    links_distribution_ = utils::DrawWithoutReplacement(0u, static_cast<std::uint32_t>(nk_.n_*nk_.k_));
}

void NKModel::copyFunction(std::shared_ptr<base::Function> f)
{
	copySolution(std::dynamic_pointer_cast<NKModel>(f));
    matrix_distribution_ = utils::DrawWithoutReplacement(0u, static_cast<std::uint32_t>(nk_.n_*nk_.pow2k1_-1));
    links_distribution_ = utils::DrawWithoutReplacement(0u, static_cast<std::uint32_t>(nk_.n_*nk_.k_));
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
    matrix_distribution_.reset();
    links_distribution_.reset();

    auto mutation = std::dynamic_pointer_cast<alggen::mutation::NKSeedMutation>(m);
	std::default_random_engine generator(mutation->getSeed());

	std::uniform_int_distribution<unsigned int> offset_mutation_matrix(1,1000000);
	std::uniform_int_distribution<unsigned int> offset_mutation_links(1,static_cast<std::uint32_t>(nk_.n_-1));

	for(unsigned int i(0); i < mutation->getMatrixMutation(); ++i)
	{
		unsigned int index = matrix_distribution_(generator);
		unsigned int tmp = nk_.matrix_[index];
		tmp += offset_mutation_matrix(generator);
		tmp %= 1000001;
        nk_.matrix_[index] = tmp;
	}

	for(unsigned int i(0); i < mutation->getLinksMutation(); ++i)
	{
		unsigned int index = links_distribution_(generator);

		for(unsigned int j(0); j < nk_.var_in_links_[nk_.links_[index]].size(); ++j)
		{
			if(nk_.var_in_links_[nk_.links_[index]][j] == index/nk_.k1_)
			{
                nk_.var_in_links_[nk_.links_[index]][j] = nk_.var_in_links_[nk_.links_[index]].back();
                nk_.var_in_links_[nk_.links_[index]].pop_back();

				break;
			}
		}

        nk_.links_[index] += offset_mutation_links(generator);
        nk_.links_[index] %= nk_.n_;

        nk_.var_in_links_[nk_.links_[index]].push_back(static_cast<std::uint16_t>(index/nk_.k1_));
	}
}

void NKModel::reverseMutation(std::shared_ptr<base::Mutation> const& m)
{
    matrix_distribution_.reset();
    links_distribution_.reset();

    auto mutation = std::dynamic_pointer_cast<alggen::mutation::NKSeedMutation>(m);
	std::default_random_engine generator(mutation->getSeed());

	std::uniform_int_distribution<unsigned int> offset_mutation_matrix(1,1000000);
	std::uniform_int_distribution<unsigned int> offset_mutation_links(1,static_cast<std::uint32_t>(nk_.n_-1));

	for(unsigned int i(0); i < mutation->getMatrixMutation(); ++i)
	{
		unsigned int index = matrix_distribution_(generator);
		unsigned int tmp = nk_.matrix_[index];
		tmp += 1000001-offset_mutation_matrix(generator);
		tmp %= 1000001;
        nk_.matrix_[index] = tmp;
	}

	for(unsigned int i(0); i < mutation->getLinksMutation(); ++i)
	{
		unsigned int index = links_distribution_(generator);

		for(unsigned int j(0); j < nk_.var_in_links_[nk_.links_[index]].size(); ++j)
		{
			if(nk_.var_in_links_[nk_.links_[index]][j] == index/nk_.k1_)
			{
                nk_.var_in_links_[nk_.links_[index]][j] = nk_.var_in_links_[nk_.links_[index]].back();
                nk_.var_in_links_[nk_.links_[index]].pop_back();

				break;
			}
		}

        nk_.links_[index] += nk_.n_ - offset_mutation_links(generator);
        nk_.links_[index] %= nk_.n_;

        nk_.var_in_links_[nk_.links_[index]].push_back(static_cast<std::uint16_t>(index/nk_.k1_));
	}
}

void NKModel::randomize()
{
    nk_.randomize();
}

void NKModel::print(std::ostream & out) const
{
    nk_.print(out);
}

void NKModel::setNewSolution(std::shared_ptr<base::Solution> const& s) const
{
    nk_.setNewSolution(s);
}

void NKModel::mutateLastSolution(std::shared_ptr<base::Mutation> const& m) const
{
    nk_.mutateLastSolution(m);
}

std::shared_ptr<base::Solution> NKModel::createSolution() const
{
    return nk_.createSolution();
}

std::string NKModel::to_string(base::Fitness const& x) const
{
    return nk_.to_string(x);
}

base::Fitness NKModel::evaluate(std::shared_ptr<base::Solution> const& s) const
{
    return nk_.evaluate(s);
}

base::Fitness NKModel::incremental_evaluation(std::shared_ptr<base::Mutation> const& m) const
{
    return nk_.incremental_evaluation(m);
}

} // solution namespace
} // alggen namespace
