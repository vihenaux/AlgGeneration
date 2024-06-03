#pragma once

#include <string>
#include <vector>
#include <alggen/base/function.hpp>
#include <alggen/solution/bitstring.hpp>

namespace alggen
{
namespace problem
{

class NK : public base::Function
{
    public:

    NK() = delete;
    NK(NK const& nk);
    NK(std::string const& file_path);
    NK(std::size_t n, std::size_t k);

    virtual void setNewSolution(std::shared_ptr<base::Solution> const& s) const final;
    virtual void mutateLastSolution(std::shared_ptr<base::Mutation> const& m) const final;

    virtual std::shared_ptr<base::Function> createCopy() const final;
    virtual void copy(std::shared_ptr<base::Function> f) final;

    virtual std::shared_ptr<base::Solution> createSolution() const final;

    virtual std::string to_string(base::Fitness const& x) const final;

    private:

    virtual base::Fitness evaluate(std::shared_ptr<base::Solution> const& s) const final;
    virtual base::Fitness incremental_evaluation(std::shared_ptr<base::Mutation> const& m) const final;

    std::size_t n_;
    std::size_t k_;
    std::size_t k1_;
    std::size_t pow2k1_;

    std::vector<std::uint32_t> matrix_;
    std::vector<std::uint16_t> links_;
    std::vector<std::vector<std::uint16_t>> var_in_links_;

    mutable base::Fitness score_{0};
    mutable solution::BitString sol_;
};

}
}
