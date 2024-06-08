#pragma once

#include <cstddef>
#include <memory>
#include <alggen/base/mutation.hpp>
#include <alggen/base/solution.hpp>
#include <string>

namespace alggen
{
namespace solution
{

// Bit string solution
class BitString : public base::Solution
{
	public:

	// Cannot construct without a size
	BitString() = delete;
	// size is the number of bits in the solution
	BitString(std::size_t size);
	BitString(base::Solution const& s) = delete;
	BitString(BitString const& bt);
    BitString(std::string const& file_path);

	virtual ~BitString() override;

	BitString& operator=(base::Solution const& s) = delete;

	virtual void copySolution(std::shared_ptr<base::Solution> const& s) override;
	virtual std::shared_ptr<base::Solution> createSolutionCopy() const override;

	virtual void mutate(std::shared_ptr<base::Mutation> const& m) override;
	virtual void reverseMutation(std::shared_ptr<base::Mutation> const& m) override;

	virtual void randomize() override;

	virtual void print(std::ostream & out) const override;

	// Get the value of the bit at index
	inline bool operator[](std::size_t index) const { return sol_[index]; }

	private:

	std::size_t size_;
	bool* sol_;
};

} // solution namespace
} // alggen namespace
