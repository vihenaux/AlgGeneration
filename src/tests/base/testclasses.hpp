#pragma once

#include <cstdlib>
#include <memory>
#include <base/all.hpp>

class TestMutation final : public Mutation
{
	public:

	TestMutation(std::int8_t m);

	std::int8_t getOffset() const;

	virtual void requiredForVTable() final;

	private:

	std::int8_t offset_{0};
};

class TestSolution final : public Solution
{
	public:

	TestSolution();
	TestSolution(std::uint8_t const& v);
	virtual ~TestSolution() final = default;

	virtual void copy(std::shared_ptr<Solution> const& s) final;

	virtual void mutate(std::shared_ptr<Mutation> const& m) final;
	virtual void reverseMutation(std::shared_ptr<Mutation> const& m) final;

	std::uint8_t getValue() const;

	private:

	std::uint8_t value_{0};
};

class TestFunction : virtual public Function
{
	public:

	virtual ~TestFunction() override;

	virtual std::shared_ptr<Solution> getRandomSolution() const final;

	protected:

	virtual std::uint64_t evaluate(std::shared_ptr<Solution> const& s) const final;
};

class TestNonOverloadedIncrementalFunction final : public IncrementalFunction, public TestFunction
{
	virtual void requiredForVTable() final;
};

class TestIncrementalFunction final : public IncrementalFunction, public TestFunction
{
	public:

	virtual void setNewSolution(std::shared_ptr<Solution> const& s) const final;
	virtual void mutateLastSolution(std::shared_ptr<Mutation> const& m) const final;

	protected:

	virtual std::uint64_t incremental_evaluation(std::shared_ptr<Mutation> const& m) const final;

	private:

	mutable std::uint64_t lastSolutionEvaluation_{0};
};

class TestNeighborhood final : public Neighborhood
{
	public:

	virtual ~TestNeighborhood() final;

	virtual bool neighborAvailable() const final;

	private:

	virtual void setNewSolutionPvt(std::shared_ptr<Solution> const& s) final;

	virtual std::shared_ptr<Mutation> nextNeighborPvt() final;
	virtual void acceptMutationPvt(std::shared_ptr<Mutation> const& m) final;

	std::shared_ptr<Solution> rootSolution_{new TestSolution()};
	bool nextNeighbor_{false};
};
