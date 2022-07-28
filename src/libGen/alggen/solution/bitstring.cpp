#include "bitstring.hpp"
#include <alggen/neighborhood/oneflip.hpp>

namespace alggen
{
namespace solution
{

BitString::BitString(std::size_t size) : size_(size), sol_(new bool[size])
{
	randomize();
}

BitString::BitString(BitString const& bt) : size_(bt.size_), sol_(new bool[bt.size_])
{
	for(std::size_t i(0); i < size_; ++i)
	{
		sol_[i] = bt.sol_[i];
	}
}

BitString::~BitString()
{
	delete[] sol_;
}

void BitString::copy(std::shared_ptr<base::Solution> const& s)
{
	auto derivedSol = std::dynamic_pointer_cast<BitString>(s);

	if(derivedSol->size_ != size_)
	{
		delete[] sol_;
		sol_ = new bool[size_];
	}

	for(std::size_t i(0); i < size_; ++i)
	{
		sol_[i] = (*derivedSol)[i];
	}
}

std::shared_ptr<base::Solution> BitString::createCopy() const
{
	return std::make_shared<BitString>(*this);
}

void BitString::mutate(std::shared_ptr<base::Mutation> const& m)
{
	auto index = std::dynamic_pointer_cast<alggen::mutation::OneFlip>(m)->getBit();
	sol_[index] = !sol_[index];
}

void BitString::reverseMutation(std::shared_ptr<base::Mutation> const& m)
{
	// Two consecutive same mutations = no mutation
	mutate(m);
}

void BitString::randomize()
{
	for(std::size_t i(0); i < size_; ++i)
	{
		sol_[i] = static_cast<bool>(rand()%2);
	}
}

} // solution namespace
} // alggen namespace
