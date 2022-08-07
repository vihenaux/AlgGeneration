#pragma once

#include <cstdint>
#include <memory>

#include "function.hpp"
#include "solution.hpp"

namespace alggen
{
namespace base
{

class SearchAlgorithm
{
	public:
	
	SearchAlgorithm() = delete;
	SearchAlgorithm(Function * fobj, std::shared_ptr<Solution> s);
	SearchAlgorithm(std::shared_ptr<Function> fobj, std::shared_ptr<Solution> s);
	virtual ~SearchAlgorithm() = default;

	void changeObjecitveFunction(std::shared_ptr<Function> fobj);

	std::uint64_t operator()() const;
	std::uint64_t operator()(std::shared_ptr<Solution> s) const;

	void getResultCopy(std::shared_ptr<Solution> s) const;
	std::shared_ptr<Solution> getResultCopy() const;

	protected:

	std::shared_ptr<Function> fobj_;
	std::shared_ptr<Solution> sol_;

	private:

	virtual std::uint64_t search() const = 0;
	virtual void requiredForVTable() const;

};

}
}
