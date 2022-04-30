#pragma once

#include <memory>
#include "mutation.hpp"

// This class will be the base class for every solution class
class Solution
{
	public:

	// /!\ The default constructor of a Solution derived class should construct a random solution
	Solution() = default;
	Solution(Solution const& s) = delete;

	virtual ~Solution();

	Solution& operator=(Solution const& s) = delete;

	virtual void copy(std::shared_ptr<Solution> const& s) = 0;

	// A solution has to be able to mutate and to reverse it
	virtual void mutate(std::shared_ptr<Mutation> const& m) = 0;
	virtual void reverseMutation(std::shared_ptr<Mutation> const& m) = 0;
};

