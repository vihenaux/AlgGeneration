#include "nkmodel.hpp"

namespace alggen
{
namespace solution
{

NKModel::NKModel(problem::NK const& nk) : base:Solution(), problem::NK(nk)
{

}

NKModel::NKModel(NKModel const& bt) : base::Solution(), problem::NK(bt)
{

}

NKModel::NKModel(std::string const& file_path) : base::Solution(), problem::NK(file_path)
{

}

NKModel::NKModel(std::size_t n, std::size_t k) : base::Solution(), problem::NK(n, k)
{

}

void NKModel::copy(std::shared_ptr<base::Solution> const& s)
{
	auto derivedSol = std::dynamic_pointer_cast<NKModel>(s);

    problem::NK::copy(derivedSol);
}

std::shared_ptr<base::Solution> NKModel::createCopy() const
{
	return std::make_shared<NKModel>(*this);
}

void NKModel::mutate(std::shared_ptr<base::Mutation> const& m)
{

}

void NKModel::reverseMutation(std::shared_ptr<base::Mutation> const& m)
{

}

void NKModel::randomize()
{
    problem::NK::randomize();
}

} // solution namespace
} // alggen namespace
