#pragma once

#include "mutation.hpp"

// This class will be the base class for every solution class
class Solution
{
	public:

	virtual ~Solution();

	// A solution has to be able to mutate and to reverse it
	virtual void mutate(Mutation const& m) = 0;
	virtual void reverseMutation(Mutation const& m) = 0;
};

