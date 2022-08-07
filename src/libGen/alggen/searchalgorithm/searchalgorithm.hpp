#pragma once

#include <cstdint>
#include <memory>

#include <alggen/base/function.hpp>
#include <alggen/base/solution.hpp>

namespace alggen
{
namespace searchalgorithm
{

class SearchAlgorithm
{
	public:
	
	SearchAlgorithm() = delete;
	SearchAlgorithm(base::Function * fobj, std::shared_ptr<base::Solution> s);
	SearchAlgorithm(std::shared_ptr<base::Function> fobj, std::shared_ptr<base::Solution> s);
	virtual ~SearchAlgorithm() = default;

	void changeObjecitveFunction(std::shared_ptr<base::Function> fobj);

	std::uint64_t operator()() const;
	std::uint64_t operator()(std::shared_ptr<base::Solution> s) const;

	void getResultCopy(std::shared_ptr<base::Solution> s) const;
	std::shared_ptr<base::Solution> getResultCopy() const;

	protected:

	std::shared_ptr<base::Function> fobj_;
	std::shared_ptr<base::Solution> sol_;

	private:

	virtual std::uint64_t search() const = 0;
	virtual void requiredForVTable() const;

};

}
}
