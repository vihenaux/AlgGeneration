#pragma once

#include <cstdint>
#include <atomic>
#include <memory>
#include <string>

namespace alggen { namespace base { class Solution; } }
#include "solution.hpp"

namespace alggen
{
namespace base
{

//typedef std::uint64_t Fitness;

// Represents the fitness of a solution
class Fitness
{
    public:

    Fitness() = default;
    Fitness(std::uint64_t x);
    Fitness(Fitness const& f);
    ~Fitness() = default;

    Fitness& operator+=(std::uint64_t x);
    Fitness& operator+=(Fitness const &x);
    Fitness operator+(std::uint64_t x) const;
    Fitness operator+(Fitness const &x) const;
    Fitness& operator-=(std::uint64_t x);
    Fitness& operator-=(Fitness const &x);
    Fitness operator-(std::uint64_t x) const;
    Fitness operator-(Fitness const &x) const;
    Fitness& operator*=(std::uint64_t x);
    Fitness& operator*=(Fitness const &x);
    Fitness operator*(std::uint64_t x) const;
    Fitness operator*(Fitness const &x) const;
    Fitness& operator/=(std::uint64_t x);
    Fitness& operator/=(Fitness const &x);
    Fitness operator/(std::uint64_t x) const;
    Fitness operator/(Fitness const &x) const;
    Fitness& operator=(std::uint64_t x);
    Fitness& operator=(Fitness const &x);

    inline bool operator<(std::uint64_t x) const { return fitness_ < x; }
    inline bool operator<(Fitness x) const { return fitness_ < x.fitness_; }
    inline bool operator<=(std::uint64_t x) const { return fitness_ <= x; }
    inline bool operator<=(Fitness x) const { return fitness_ <= x.fitness_; }
    inline bool operator>(std::uint64_t x) const { return fitness_ > x; }
    inline bool operator>(Fitness x) const { return fitness_ > x.fitness_; }
    inline bool operator>=(std::uint64_t x) const { return fitness_ >= x; }
    inline bool operator>=(Fitness x) const { return fitness_ >= x.fitness_; }
    inline bool operator==(std::uint64_t x) const { return fitness_ == x; }
    inline bool operator==(Fitness x) const { return fitness_ == x.fitness_; }
    inline bool operator!=(std::uint64_t x) const { return fitness_ != x; }
    inline bool operator!=(Fitness x) const { return fitness_ != x.fitness_; }

    std::uint64_t get_int() const;

    private:

    std::uint64_t fitness_{0};
};

// A class that represents functions.
class Function
{
	public:

	virtual ~Function();

	// Get the number of solution this function evaluated
	std::uint64_t getNumberOfCalls() const;

	// Assign an evaluation to the solution passed and stores the solution for mutation evaluation
    Fitness operator()(std::shared_ptr<Solution> const& s) const;
	// Assign an evaluation to the mutation of the last solution evaluated
    Fitness operator()(std::shared_ptr<Mutation> const& m) const;

	virtual void setNewSolution(std::shared_ptr<Solution> const& s) const;
	virtual void mutateLastSolution(std::shared_ptr<Mutation> const& m) const;

	virtual std::shared_ptr<Function> createFunctionCopy() const = 0;
	virtual void copyFunction(std::shared_ptr<Function> f) = 0;

	virtual std::shared_ptr<Solution> createSolution() const = 0;

    virtual std::string to_string(Fitness const& x) const;

	private:

	void solutionEvaluated() const;
	virtual Fitness evaluate(std::shared_ptr<Solution> const& s) const = 0;
	virtual Fitness incremental_evaluation(std::shared_ptr<Mutation> const& m) const;

	mutable std::atomic<std::uint64_t> numberOfCalls_{0};

	mutable std::shared_ptr<Solution> lastSolutionEvaluated_{nullptr};
};

} // base namespace
} // alggen namespace
