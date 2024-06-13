#include "function.hpp"

namespace alggen
{
namespace base
{

Fitness::Fitness(std::uint64_t x) : fitness_(x) {}
Fitness::Fitness(Fitness const& f) : fitness_(f.fitness_) {}

Fitness& Fitness::operator+=(std::uint64_t x)
{
    fitness_ += x;
    return *this;
}

Fitness& Fitness::operator+=(Fitness const &x)
{
    fitness_ += x.fitness_;
    return *this;
}

Fitness Fitness::operator+(std::uint64_t x) const
{
    return Fitness(fitness_ + x);
}

Fitness Fitness::operator+(Fitness const &x) const
{
    return Fitness(fitness_ + x.fitness_);
}

Fitness& Fitness::operator-=(std::uint64_t x)
{
    fitness_ -= x;
    return *this;
}

Fitness& Fitness::operator-=(Fitness const &x)
{
    fitness_ -= x.fitness_;
    return *this;
}

Fitness Fitness::operator-(std::uint64_t x) const
{
    return Fitness(fitness_ - x);
}

Fitness Fitness::operator-(Fitness const &x) const
{
    return Fitness(fitness_ - x.fitness_);
}

Fitness& Fitness::operator*=(std::uint64_t x)
{
    fitness_ *= x;
    return *this;
}

Fitness& Fitness::operator*=(Fitness const &x)
{
    fitness_ *= x.fitness_;
    return *this;
}

Fitness Fitness::operator*(std::uint64_t x) const
{
    return Fitness(fitness_ * x);
}

Fitness Fitness::operator*(Fitness const &x) const
{
    return Fitness(fitness_ * x.fitness_);
}

Fitness& Fitness::operator/=(std::uint64_t x)
{
    fitness_ /= x;
    return *this;
}

Fitness& Fitness::operator/=(Fitness const &x)
{
    fitness_ /= x.fitness_;
    return *this;
}

Fitness Fitness::operator/(std::uint64_t x) const
{
    return Fitness(fitness_ / x);
}

Fitness Fitness::operator/(Fitness const &x) const
{
    return Fitness(fitness_ / x.fitness_);
}

Fitness& Fitness::operator=(std::uint64_t x)
{
    fitness_ = x;
    return *this;
}

Fitness& Fitness::operator=(Fitness const &x)
{
    fitness_ = x.fitness_;
    return *this;
}

std::uint64_t Fitness::get_int() const
{
    return fitness_;
}


Function::~Function()
{
	
}

std::uint64_t Function::getNumberOfCalls() const
{
	return numberOfCalls_;
}

void Function::solutionEvaluated() const
{
	++numberOfCalls_;
}

Fitness Function::operator()(std::shared_ptr<Solution> const& s) const
{
	setNewSolution(s);
	solutionEvaluated();

	return evaluate(s);
}

Fitness Function::operator()(std::shared_ptr<Mutation> const& m) const
{
	solutionEvaluated();

	return incremental_evaluation(m);
}

void Function::setNewSolution(std::shared_ptr<Solution> const& s) const
{
	if(!lastSolutionEvaluated_)
	{
		lastSolutionEvaluated_ = s->createSolutionCopy();
	} else {
		lastSolutionEvaluated_->copySolution(s);
	}
}

void Function::mutateLastSolution(std::shared_ptr<Mutation> const& m) const
{
	lastSolutionEvaluated_->mutate(m);
}

std::string Function::to_string(Fitness const& x) const
{
    return std::to_string(x.get_int());
}

Fitness Function::incremental_evaluation(std::shared_ptr<Mutation> const& m) const
{
	// Evaluate the solution with the mutation
	lastSolutionEvaluated_->mutate(m);
	Fitness evalMutation = evaluate(lastSolutionEvaluated_);
	// Then reverse the mutation
	lastSolutionEvaluated_->reverseMutation(m);

	return evalMutation;
}

} // base namespace
} // alggen namespace
