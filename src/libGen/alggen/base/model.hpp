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

    Model() = default;
    virtual ~Model() override = default;

    private:

    virtual void requiredForVTable() const;
};

}
}
