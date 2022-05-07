#include "bitstring.hpp"

namespace alggen
{
namespace mutation
{

OneFlip::OneFlip(std::size_t bit) : bit_(bit)
{

}

std::size_t OneFlip::getBit() const
{
	return bit_;
}

void OneFlip::requiredForVTable()
{

}

} // mutation namespace

namespace solution
{

BitString::BitString(std::size_t size) : size_(size), sol_(new bool[size])
{
	for(std::size_t i(0); i < size_; ++i)
	{
		sol_[i] = static_cast<bool>(rand()%2);
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

void BitString::mutate(std::shared_ptr<base::Mutation> const& m)
{
	auto index = std::dynamic_pointer_cast<mutation::OneFlip>(m)->getBit();
	sol_[index] = !sol_[index];
}

void BitString::reverseMutation(std::shared_ptr<base::Mutation> const& m)
{
	// Two consecutive same mutations = no mutation
	mutate(m);
}

bool BitString::operator[](std::size_t index) const
{
	return sol_[index];
}

} // solution namespace
} // alggen namespace
