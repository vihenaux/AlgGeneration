#include "tournamentselection.hpp"

namespace alggen
{
namespace selection
{

template<unsigned int percentage_kept_each_step>
std::vector<std::shared_ptr<base::Mutation>> tournament_selection(std::shared_ptr<base::Function> &const fobj, std::shared_ptr<base::SearchAlgorithm> & search, std::shared_ptr<base::Model> & falt, std::vector<std::shared_ptr<Mutation>> &const candidates, unsigned int number_to_select, unsigned int budget_of_fobj_calls)
{
    // Find tournament parameters
    unsigned int candidates_count = candidates.size();
    unsigned int fobj_calls_round_count = candidates_count;
    while(candidates_count != number_to_select)
    {
        candidates_count *= percentage_kept_each_step;
        candidates_count /= 100;
        candidates_count = (candidates_count < number_to_select) ? number_to_select : candidates_count;

        fobj_calls_round_count += candidates_count;
    }
    unsigned int fobj_calls_per_round_per_candidate = budget/fobj_calls_round_count;

    std::vector<std::shared_ptr<base::Mutation>> current_selection(candidates);

    // Tournament
    while(current_selection.size() != number_to_select)
    {
        // Fitness estimations
        std::vector<alggen::Fitness> fitness_estimations(current_selection.size(), 0);
        for(unsigned int i(0); i < current_selection.size(); ++i)
        {
            falt->mutate(current_selection[i]);
            search->changeObjectiveFunction(falt);
            for(unsigned int j(0); j < fobj_calls_per_round_per_candidate; ++j)
            {
                fitness_estimation[i] += fobj((*search)());
            }
            falt->reverseMutation(current_selection[i]);
        }

        // Selection
        unsigned int to_select = (current_selection.size() * percentage_kept_each_step)/100;
        to_select = (to_select < number_to_select) ? number_to_select : to_select;
        for(unsigned int i(0); i < current_selection.size() - to_select; ++i)
        {
            unsigned int index_min = 0;
            for(unsigned int j(1); j < current_selection.size(); ++j)
            {
                if(fitness_estimation[j] > fitness_estimation[index_min])
                {
                    index_min = j;
                }
            }
            fitness_estimation.erase(index_min);
            current_selection(index_min);
        }
    }

    return current_selection;
}

}
}