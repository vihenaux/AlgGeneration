#include "bitstring.hpp"
#include <alggen/neighborhood/oneflip.hpp>
#include <fstream>
#include <iostream>

namespace alggen
{
namespace solution
{

BitString::BitString(std::size_t size) : size_(size), sol_(new bool[size])
{
	BitString::randomize();
}

BitString::BitString(BitString const& bt) : size_(bt.size_), sol_(new bool[bt.size_])
{
	for(std::size_t i(0); i < size_; ++i)
	{
		sol_[i] = bt.sol_[i];
	}
}

BitString::BitString(std::string const& file_path) : size_(0), sol_(nullptr)
{
    std::ifstream input_file(file_path);

    if(!input_file.is_open())
    {
        std::cerr << "BitString file constructor : Error cannot open file at " << file_path << std::endl;
        return;
    }

    std::string line;
    std::getline(input_file, line);

    for(unsigned int i(0); i < line.size(); ++i)
    {
        if(line[i] == '0' || line[i] == '1')
        {
            ++size_;
        }
    }

    sol_ = new bool[size_];

    unsigned int fill_id = 0;
    for(unsigned int i(0); i < line.size(); ++i)
    {
        if(line[i] == '0' || line[i] == '1')
        {
            sol_[fill_id] = (line[i] == '1');
            ++fill_id;
        }
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
        size_ = derivedSol->size_;
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

void BitString::print(std::ostream & out) const
{
	for(std::size_t i(0); i < size_; ++i)
	{
		out << static_cast<std::uint32_t>(sol_[i]);
	}
	out << "\n";
}

} // solution namespace
} // alggen namespace
