#pragma once

#include <alggen/base/mutation.hpp>
#include <alggen/base/model.hpp>
#include <alggen/base/solution.hpp>
#include <alggen/problem/nk.hpp>
#include <string>
#include <alggen/utils/drawwithoutreplacement.hpp>

namespace alggen
{
namespace solution
{

// NK function as an algorithm generation solution
class NKModel : public base::Model
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
    virtual void print(std::ostream & out) const override;

    virtual void setNewSolution(std::shared_ptr<base::Solution> const& s) const final;
    virtual void mutateLastSolution(std::shared_ptr<base::Mutation> const& m) const final;

    virtual std::shared_ptr<base::Solution> createSolution() const final;

    virtual std::string to_string(base::Fitness const& x) const final;

    private:

    virtual base::Fitness evaluate(std::shared_ptr<base::Solution> const& s) const final;
    virtual base::Fitness incremental_evaluation(std::shared_ptr<base::Mutation> const& m) const final;

    problem::NK nk_;

    utils::DrawWithoutReplacement matrix_distribution_;
    utils::DrawWithoutReplacement links_distribution_;
};

} // solution namespace
} // alggen namespace
