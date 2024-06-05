#include "nk.hpp"
#include <unordered_set>
#include <alggen/neighborhood/oneflip.hpp>
#include <fstream>
#include <iostream>

namespace alggen
{
namespace problem
{

NK::NK(NK const& nk) : n_(nk.n_), k_(nk.k_), k1_(nk.k1_), pow2k1_(nk.pow2k1_), matrix_(nk.matrix_), links_(nk.links_), var_in_links_(nk.var_in_links_), sol_(nk.n_)
{

}

NK::NK(std::string const& file_path) : n_(1), k_(0), k1_(1), pow2k1_(2), matrix_(2), links_(1), var_in_links_(1), sol_(1)
{
    std::ifstream input_file(file_path);

    if(!input_file.is_open())
    {
        std::cerr << "NK construct from file : Error cannot open file \"" << file_path << "\"" << std::endl;
        return;
    }

    input_file >> n_ >> k_;
    k1_ = k_ + 1;
    pow2k1_ = 1 << k1_;

    matrix_.resize(n_*pow2k1_);
    links_.resize(n_*k1_);
    var_in_links_.resize(n_);
    sol_.copy(createSolution());

    for(unsigned int i(0); i < n_; ++i)
    {
        for(unsigned int j(0); j < k1_; ++j)
        {
            unsigned int tmp;
            input_file >> tmp;
            links_[k1_*i+j] = static_cast<std::uint16_t>(tmp);

            var_in_links_[tmp].push_back(static_cast<std::uint16_t>(i));
        }
    }

    for(unsigned int i(0); i < n_*pow2k1_; ++i)
    {
        matrix_[i] = 0;

        char tmp;
        input_file.get(tmp);
        while(tmp != '0' && tmp != '1')
            input_file.get(tmp);

        matrix_[i] += static_cast<std::uint8_t>(tmp-'0');
        input_file.get(tmp);

        if(tmp == '.')
        {
            input_file >> tmp;
            for(unsigned int j(0); j < 6; ++j)
            {
                matrix_[i] *= 10;
                if(tmp >= '0' && tmp <= '9')
                {
                    matrix_[i] += static_cast<std::uint8_t>(tmp-'0');
                    input_file.get(tmp);
                }
            }
        }
    }
}

NK::NK(std::size_t n, std::size_t k) : n_(n), k_(k), k1_(k+1), pow2k1_(1 << k1_), matrix_(n_*pow2k1_), links_(n_*k1_), var_in_links_(n_), sol_(n_)
{
    randomize();
}

void NK::setNewSolution(std::shared_ptr<base::Solution> const& s) const
{
    sol_.copy(s);
}

void NK::mutateLastSolution(std::shared_ptr<base::Mutation> const& m) const
{
    score_ = operator()(m);
    sol_.mutate(m);
}

std::shared_ptr<base::Function> NK::createCopy() const
{
    return std::make_shared<NK>(*this);
}

void NK::copy(std::shared_ptr<base::Function> f)
{
    std::shared_ptr<NK> nk = std::dynamic_pointer_cast<NK>(f);
    n_ = nk->n_;
    k_ = nk->k_;
    k1_ = nk->k1_;
    pow2k1_ = nk->pow2k1_;
    matrix_ = nk->matrix_;
    links_ = nk->links_;
    var_in_links_ = nk->var_in_links_;
}

std::shared_ptr<base::Solution> NK::createSolution() const
{
    return std::make_shared<solution::BitString>(n_);
}

std::string NK::to_string(base::Fitness const& x) const
{
    return std::to_string(static_cast<double>(x.get_int()) / static_cast<double>(n_*1000000));
}

void NK::randomize()
{
    for(unsigned int i(0); i < n_*pow2k1_; ++i)
    {
        matrix_[i] = static_cast<std::uint32_t>(rand()%1000000);
    }

    for(unsigned int i(0); i < n_; ++i)
    {
        var_in_links_[i].clear();
    }

    for(unsigned int i(0); i < n_; ++i)
    {
        for(unsigned int j(0); j < k1_; ++j)
        {
            std::uint16_t var = static_cast<std::uint16_t>(static_cast<std::uint16_t>(rand())%n_);
            links_[i*k1_+j] = var;
            var_in_links_[var].push_back(static_cast<std::uint16_t>(i));
        }
    }
}

base::Fitness NK::evaluate(std::shared_ptr<base::Solution> const& /*s Unused because the solution is set before*/) const
{
    score_ = 0.;
    for(unsigned int i(0); i < n_; ++i)
    {
        unsigned int tmp = 0;
        for(unsigned int j(0); j < k1_; ++j)
        {
            tmp += static_cast<unsigned int>(sol_[links_[k1_*i+j]] << j);
        }
        score_ += matrix_[pow2k1_*i+tmp];
    }
    return score_;
}

base::Fitness NK::incremental_evaluation(std::shared_ptr<base::Mutation> const& m) const
{
    base::Fitness score = score_;
    auto bitValue = std::dynamic_pointer_cast<mutation::OneFlip>(m)->getBit();
    std::unordered_set<std::uint16_t> excluded;

    for(unsigned int i(0); i < var_in_links_[bitValue].size(); ++i)
    {
        std::uint16_t link_id = var_in_links_[bitValue][i];
        if(!excluded.count(link_id))
        {
            excluded.insert(link_id);
            unsigned int tmp = 0;
            for(unsigned int j(0); j < k1_; ++j)
            {
                tmp += static_cast<unsigned int>(sol_[links_[k1_*link_id+j]] << j);
            }
            score -= matrix_[pow2k1_*link_id+tmp];

            sol_.mutate(m);

            tmp = 0;
            for(unsigned int j(0); j < k1_; ++j)
            {
                tmp += static_cast<unsigned int>(sol_[links_[k1_*link_id+j]] << j);
            }
            score += matrix_[pow2k1_*link_id+tmp];

            sol_.reverseMutation(m);
        }
    }

    return score;
}

}
}
