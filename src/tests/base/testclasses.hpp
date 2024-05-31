#pragma once

#include <cstdlib>
#include <memory>
#include <alggen/base/all.hpp>

class TestMutation final : public alggen::base::Mutation
{
	public:

	TestMutation(std::int8_t m);

	std::int8_t getOffset() const;

	private:

	virtual void requiredForVTable() const final;

	std::int8_t offset_{0};
};

class TestSolution final : public alggen::base::Solution
{
	public:

	TestSolution();
	TestSolution(std::uint8_t const& v);
	virtual ~TestSolution() final = default;

	virtual void copy(std::shared_ptr<alggen::base::Solution> const& s) final;
	virtual std::shared_ptr<alggen::base::Solution> createCopy() const final;

	virtual void mutate(std::shared_ptr<alggen::base::Mutation> const& m) final;
	virtual void reverseMutation(std::shared_ptr<alggen::base::Mutation> const& m) final;

	virtual void randomize() override;

	std::uint8_t getValue() const;

	private:

	std::uint8_t value_{0};
};

class TestFunction : virtual public alggen::base::Function
{
	public:

	virtual ~TestFunction() override;

	virtual std::shared_ptr<alggen::base::Function> createCopy() const final;
	virtual void copy(std::shared_ptr<Function> f) final;

	virtual std::shared_ptr<alggen::base::Solution> createSolution() const final;

	protected:

	virtual alggen::base::Fitness evaluate(std::shared_ptr<alggen::base::Solution> const& s) const final;
};

class TestNonOverloadedIncrementalFunction final : public TestFunction
{
	virtual void requiredForVTable() final;
};

class TestIncrementalFunction final : public TestFunction
{
	public:

	virtual void setNewSolution(std::shared_ptr<alggen::base::Solution> const& s) const final;
	virtual void mutateLastSolution(std::shared_ptr<alggen::base::Mutation> const& m) const final;

	protected:

	virtual alggen::base::Fitness incremental_evaluation(std::shared_ptr<alggen::base::Mutation> const& m) const final;

	private:

	mutable alggen::base::Fitness lastSolutionEvaluation_{0};
};

class TestNeighborhood final : public alggen::base::Neighborhood
{
	public:

	virtual ~TestNeighborhood() final;

	virtual bool neighborAvailable() const final;

	private:

	virtual void setNewSolutionPvt(std::shared_ptr<alggen::base::Solution> const& s) final;

	virtual std::shared_ptr<alggen::base::Mutation> nextNeighborPvt() final;
	virtual void acceptMutationPvt(std::shared_ptr<alggen::base::Mutation> const& m) final;

	std::shared_ptr<alggen::base::Solution> rootSolution_{new TestSolution()};
	bool nextNeighbor_{false};
};

class TestSearchAlgorithm final : public alggen::base::SearchAlgorithm
{
	public:

	TestSearchAlgorithm(std::shared_ptr<alggen::base::Function> fobj, std::shared_ptr<alggen::base::Solution> s);

	private:

	virtual alggen::base::Fitness search() const final;
};
