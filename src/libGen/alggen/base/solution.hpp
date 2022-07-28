#pragma once

#include <memory>
#include "mutation.hpp"

class Function;
#include "function.hpp"

namespace alggen
{
namespace base
{

// This class will be the base class for every solution class
class Solution
{
	public:

	Solution() = default;
	Solution(Solution const& s) = delete;

	virtual ~Solution();

	Solution& operator=(Solution const& s) = delete;

	virtual void copy(std::shared_ptr<Solution> const& s) = 0;
	virtual std::shared_ptr<Solution> createCopy() const = 0;

	// A solution has to be able to mutate and to reverse it
	virtual void mutate(std::shared_ptr<Mutation> const& m) = 0;
	virtual void reverseMutation(std::shared_ptr<Mutation> const& m) = 0;

	virtual void randomize() = 0;
};

} // base namespace
} // alggen namespace
