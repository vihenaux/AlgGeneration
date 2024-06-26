#pragma once

#include <iostream>
#include <memory>
#include "mutation.hpp"
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

	virtual void copySolution(std::shared_ptr<Solution> const& s) = 0;
	virtual std::shared_ptr<Solution> createSolutionCopy() const = 0;

	// A solution has to be able to mutate and to reverse it
	virtual void mutate(std::shared_ptr<Mutation> const& m) = 0;
	virtual void reverseMutation(std::shared_ptr<Mutation> const& m) = 0;

	virtual void randomize() = 0;

	virtual void print(std::ostream & out) const;
};

} // base namespace
} // alggen namespace

std::ostream& operator<<(std::ostream & out, std::shared_ptr<alggen::base::Solution> sol);
