#pragma once

#include <alggen/base/function.hpp>
#include <alggen/solution/bitstring.hpp>

namespace alggen
{
namespace problem
{

class OneMax : public base::Function
{
	public:

	OneMax() = delete;
	OneMax(std::size_t size);
	virtual ~OneMax() override = default;

	virtual void setNewSolution(std::shared_ptr<base::Solution> const& s) const final;
	virtual void mutateLastSolution(std::shared_ptr<base::Mutation> const& m) const final;

	virtual std::shared_ptr<base::Function> createFunctionCopy() const final;
	virtual void copyFunction(std::shared_ptr<base::Function> f) final;

	virtual std::shared_ptr<base::Solution> createSolution() const final;

	private:

	virtual base::Fitness evaluate(std::shared_ptr<base::Solution> const& s) const final;
	virtual base::Fitness incremental_evaluation(std::shared_ptr<base::Mutation> const& m) const final;

	std::size_t size_;
	mutable base::Fitness score_{0};
	mutable solution::BitString sol_;
};

}
}
