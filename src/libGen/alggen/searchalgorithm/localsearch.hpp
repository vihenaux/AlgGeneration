#pragma once

#include <alggen/base/searchalgorithm.hpp>
#include <alggen/base/neighborhood.hpp>

namespace alggen
{
namespace searchalgorithm
{

class LocalSearch : public base::SearchAlgorithm
{
	LocalSearch() = delete;
	LocalSearch(std::shared_ptr<base::Function> fobj, std::shared_ptr<base::Solution> s, std::shared_ptr<base::Neighborhood> n);
	~LocalSearch() override = default;

	private:

	std::shared_ptr<base::Neighborhood> neighborhood_;

	virtual std::uint64_t search() const override;
};

}
}
