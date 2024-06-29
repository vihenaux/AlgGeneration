#pragma once

#include <vector>
#include <alggen/base/all.hpp>

namespace alggen
{
namespace selection
{

template<unsigned int percentage_kept_each_step>
std::vector<std::shared_ptr<base::Mutation>> tournament_selection(std::shared_ptr<base::Function> const& fobj, std::shared_ptr<base::SearchAlgorithm> & search, std::shared_ptr<base::Model> & falt, std::vector<std::shared_ptr<base::Mutation>> const& candidates, unsigned int number_to_select, unsigned int budget_of_fobj_calls);

}
}
