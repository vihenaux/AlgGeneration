#include "oneflip.hpp"

namespace alggen
{
namespace mutation
{

OneFlip::OneFlip(std::size_t bit) : bit_(bit)
{

}

void OneFlip::requiredForVTable() const
{

}

} // mutation namespace
namespace neighborhood
{

OneFlipNeighborhood::OneFlipNeighborhood(std::size_t stringLength) : length_(stringLength), current_(0), neighbors_(new std::size_t[stringLength])
{
	for(std::size_t i(0); i < length_; ++i)
	{
		neighbors_[i] = i;
	}
}

OneFlipNeighborhood::~OneFlipNeighborhood()
{
	delete[] neighbors_;
}

bool OneFlipNeighborhood::neighborAvailable() const
{
	return getNumberOfNeighborsDiscarded() < length_;
}

void OneFlipNeighborhood::setNewSolutionPvt(std::shared_ptr<alggen::base::Solution> const&)
{
	current_ = 0;
}

std::shared_ptr<alggen::base::Mutation> OneFlipNeighborhood::nextNeighborPvt()
{
	std::size_t index = (static_cast<std::size_t>(rand())%(length_-current_))+current_;
	std::size_t tmp = neighbors_[index];
	neighbors_[index] = neighbors_[current_];
	neighbors_[current_] = tmp;

	++current_;

	return std::make_shared<alggen::mutation::OneFlip>(tmp);
}

void OneFlipNeighborhood::acceptMutationPvt(std::shared_ptr<alggen::base::Mutation> const&)
{
	current_ = 0;
}

} // neighborhood namespace
} // alggen namespace
