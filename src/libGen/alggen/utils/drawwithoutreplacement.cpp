#include "drawwithoutreplacement.hpp"

namespace alggen
{
namespace utils
{

DrawWithoutReplacement::DrawWithoutReplacement(std::uint32_t min, std::uint32_t max) : min_(min), tab_size_(max-min), tab_(new std::uint32_t[tab_size_])
{
    for(std::uint32_t i(0); i < tab_size_; ++i)
    {
        tab_[i] = min_+i;
    }
}

DrawWithoutReplacement::~DrawWithoutReplacement()
{
    delete[] tab_;
}

std::uint32_t DrawWithoutReplacement::operator()(std::default_random_engine &generator)
{
    nb_generated_ %= tab_size_;

	std::uniform_int_distribution<unsigned int> distribution(nb_generated_, tab_size_-1);
    std::uint32_t generated = distribution(generator);

    std::uint32_t tmp = tab_[generated];
    tab_[generated] = tab_[nb_generated_];
    tab_[nb_generated_] = tmp;

    ++nb_generated_;

    return tmp;
}

void DrawWithoutReplacement::reset()
{
    nb_generated_ = 0;
}

}
}
