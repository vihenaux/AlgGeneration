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
	SearchAlgorithm(std::shared_ptr<Function> fobj, std::shared_ptr<Solution> s);
	virtual ~SearchAlgorithm() = default;

	void changeObjectiveFunction(std::shared_ptr<Function> fobj);

	Fitness operator()() const;
	Fitness operator()(std::shared_ptr<Solution> s) const;

	void getResultCopy(std::shared_ptr<Solution> s) const;
	std::shared_ptr<Solution> getResultCopy() const;

	protected:

	std::shared_ptr<Function> fobj_;
	std::shared_ptr<Solution> sol_;

    virtual Fitness search() const = 0;

	private:

	virtual void requiredForVTable() const;

};

}
}
