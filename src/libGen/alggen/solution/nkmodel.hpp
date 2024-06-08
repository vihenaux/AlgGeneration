#pragma once

#include <alggen/base/mutation.hpp>
#include <alggen/base/solution.hpp>
#include <alggen/problem/nk.hpp>
#include <string>
#include <alggen/utils/drawwithoutreplacement.hpp>

namespace alggen
{
namespace solution
{

// NK function as an algorithm generation solution
class NKModel : public base::Solution, public problem::NK
{
    public:

    NKModel() = delete;
    NKModel(problem::NK const& nk);
    NKModel(NKModel const& bt);
    NKModel(std::string const& file_path);
    NKModel(std::size_t n, std::size_t k);
    NKModel(base::Solution const& s) = delete;
    virtual ~NKModel() override = default;

    NKModel& operator=(base::Solution const& s) = delete;

    virtual void copySolution(std::shared_ptr<base::Solution> const& s) override;
    virtual void copyFunction(std::shared_ptr<base::Function> f) override;
    virtual std::shared_ptr<base::Solution> createSolutionCopy() const override;
    virtual std::shared_ptr<base::Function> createFunctionCopy() const override;

    virtual void mutate(std::shared_ptr<base::Mutation> const& m) override;
    virtual void reverseMutation(std::shared_ptr<base::Mutation> const& m) override;

    virtual void randomize() override;

    private:

    utils::DrawWithoutReplacement matrix_distribution_;
    utils::DrawWithoutReplacement links_distribution_;
};

} // solution namespace
} // alggen namespace
