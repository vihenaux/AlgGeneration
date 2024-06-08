#include "testclasses.hpp"

// TEST MUTATION

TestMutation::TestMutation(std::int8_t m) : offset_(m)
{

}

std::int8_t TestMutation::getOffset() const
{
	return offset_;
}

void TestMutation::requiredForVTable() const
{

}

// TEST SOLUTION

TestSolution::TestSolution() : value_(0)
{
	randomize();
}

TestSolution::TestSolution(std::uint8_t const& v) : value_(v)
{

}

void TestSolution::copySolution(std::shared_ptr<alggen::base::Solution> const& s)
{
	value_ = std::dynamic_pointer_cast<TestSolution>(s)->value_;
}

std::shared_ptr<alggen::base::Solution> TestSolution::createSolutionCopy() const
{
	return std::make_shared<TestSolution>(value_);
}

void TestSolution::mutate(std::shared_ptr<alggen::base::Mutation> const& m)
{
	value_ += std::dynamic_pointer_cast<TestMutation>(m)->getOffset();
}

void TestSolution::reverseMutation(std::shared_ptr<alggen::base::Mutation> const& m)
{
	value_ -= std::dynamic_pointer_cast<TestMutation>(m)->getOffset();
}

void TestSolution::randomize()
{
	value_ = static_cast<uint8_t>(rand());
}

std::uint8_t TestSolution::getValue() const
{
	return value_;
}

// TEST FUNCTION

TestFunction::~TestFunction()
{

}

std::shared_ptr<alggen::base::Function> TestFunction::createFunctionCopy() const
{
	return std::make_shared<TestFunction>();
}

void TestFunction::copyFunction(std::shared_ptr<Function>)
{

}

std::shared_ptr<alggen::base::Solution> TestFunction::createSolution() const
{
	return std::make_shared<TestSolution>();
}

alggen::base::Fitness TestFunction::evaluate(std::shared_ptr<alggen::base::Solution> const& s) const
{
	return alggen::base::Fitness(std::dynamic_pointer_cast<TestSolution>(s)->getValue());
}

// TEST INCREMENTAL FUNCTIONS

void TestNonOverloadedIncrementalFunction::requiredForVTable()
{

}

void TestIncrementalFunction::setNewSolution(std::shared_ptr<alggen::base::Solution> const& s) const
{
	// We do not need a copy of the solution to do incremental evaluation
	//setNewSolutionPvt(std::dynamic_pointer_cast<TestSolution>(s));

	lastSolutionEvaluation_ = std::dynamic_pointer_cast<TestSolution>(s)->getValue();
}

void TestIncrementalFunction::mutateLastSolution(std::shared_ptr<alggen::base::Mutation> const& m) const
{
	lastSolutionEvaluation_ += static_cast<std::uint64_t>(std::dynamic_pointer_cast<TestMutation>(m)->getOffset());
}

alggen::base::Fitness TestIncrementalFunction::incremental_evaluation(std::shared_ptr<alggen::base::Mutation> const& m) const
{
	return lastSolutionEvaluation_ + static_cast<std::uint64_t>(std::dynamic_pointer_cast<TestMutation>(m)->getOffset());
}

// TEST NEIGHBORHOOD

TestNeighborhood::~TestNeighborhood()
{

}

void TestNeighborhood::setNewSolutionPvt(std::shared_ptr<alggen::base::Solution> const& s)
{
	rootSolution_->copySolution(s);
}

bool TestNeighborhood::neighborAvailable() const
{
	auto solVal = std::dynamic_pointer_cast<TestSolution>(rootSolution_)->getValue();

	// Two neighbors are available, and only 1 for limit values
	return (getNumberOfNeighborsDiscarded() < (2 - static_cast<std::uint8_t>((solVal == 255) || (solVal == 0))));
}

std::shared_ptr<alggen::base::Mutation> TestNeighborhood::nextNeighborPvt()
{
	auto m = std::make_shared<TestMutation>((nextNeighbor_) ? -1 : 1);
	nextNeighbor_ = !nextNeighbor_;
	return std::move(m);
}

void TestNeighborhood::acceptMutationPvt(std::shared_ptr<alggen::base::Mutation> const& m)
{
	rootSolution_->mutate(m);

	switch(std::dynamic_pointer_cast<TestSolution>(rootSolution_)->getValue())
	{
		case 127:
			nextNeighbor_ = false;
			break;
		case -128:
			nextNeighbor_ = true;
			break;
		default:
			nextNeighbor_ = static_cast<bool>(rand()%2);
			break;
	}
}

// TEST SEARCHALGORITHM

TestSearchAlgorithm::TestSearchAlgorithm(std::shared_ptr<alggen::base::Function> fobj, std::shared_ptr<alggen::base::Solution> s) : alggen::base::SearchAlgorithm(fobj,s)
{

}

alggen::base::Fitness TestSearchAlgorithm::search() const
{
	return (*fobj_)(sol_);
}
