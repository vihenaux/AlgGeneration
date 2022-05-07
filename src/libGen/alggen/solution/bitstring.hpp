#pragma once

#include <cstddef>
#include <memory>
#include <alggen/base/mutation.hpp>
#include <alggen/base/solution.hpp>

namespace alggen
{
namespace mutation
{

// One flip mutation for bit string solutions
// This mutation contains the data to flip one bit of a solution
class OneFlip : public base::Mutation
{
	public:

	OneFlip(std::size_t bit);
	virtual ~OneFlip() override = default;

	inline std::size_t getBit() const;

	virtual void requiredForVTable() override;

	private:

	std::size_t bit_;
};

} // mutation namespace

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

	virtual ~BitString() override;

	BitString& operator=(base::Solution const& s) = delete;

	virtual void copy(std::shared_ptr<base::Solution> const& s) override;

	virtual void mutate(std::shared_ptr<base::Mutation> const& m) override;
	virtual void reverseMutation(std::shared_ptr<base::Mutation> const& m) override;

	virtual void randomize() override;

	// Get the value of the bit at index
	inline bool operator[](std::size_t index) const;

	private:

	std::size_t size_;
	bool* sol_;
};

} // solution namespace
} // alggen namespace
