#pragma once

#include <random>

namespace alggen
{
namespace utils
{

class DrawWithoutReplacement
{
    public:

    DrawWithoutReplacement(std::uint32_t min, std::uint32_t max);
    ~DrawWithoutReplacement();

    std::uint32_t operator()(std::default_random_engine &generator);
    void reset();

    private:

    std::uint32_t min_;
    std::uint32_t nb_generated_{0};
    std::uint32_t tab_size_;
    std::uint32_t *tab_;
};

}
}
