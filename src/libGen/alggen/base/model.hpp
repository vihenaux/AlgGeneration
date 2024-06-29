#pragma once

#include "solution.hpp"
#include "function.hpp"

namespace alggen
{
namespace base
{

class Model : public Solution, public Function
{
    public:

    Model() = delete;
    virtual ~Model() override = default;
};

}
}
