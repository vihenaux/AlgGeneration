#pragma once

#include <cstdlib>
#include <memory>
#include <alggen/base/all.hpp>

class TestMutation final : public alggen::base::Mutation
{
	public:

	TestMutation(std::int8_t m);

	std::int8_t getOffset() const;

	virtual void requiredForVTable() final;

	private:

	std::int8_t offset_{0};
};

class TestSolution final : public alggen::base::Solution
{
	public:

	TestSolution();
	TestSolution(std::uint8_t const& v);
	virtual ~TestSolution() final = default;

	virtual void copy(std::shared_ptr<alggen::base::Solution> const& s) final;

	virtual void mutate(std::shared_ptr<alggen::base::Mutation> const& m) final;
	virtual void reverseMutation(std::shared_ptr<alggen::base::Mutation> const& m) final;

	std::uint8_t getValue() const;

	private:

	std::uint8_t value_{0};
};

class TestFunction : virtual public alggen::base::Function
{
	public:

	virtual ~TestFunction() override;

	virtual std::shared_ptr<alggen::base::Solution> getRandomSolution() const final;

	protected:

	virtual std::uint64_t evaluate(std::shared_ptr<alggen::base::Solution> const& s) const final;
};

class TestNonOverloadedIncrementalFunction final : public alggen::base::IncrementalFunction, public TestFunction
{
	virtual void requiredForVTable() final;
};

class TestIncrementalFunction final : public alggen::base::IncrementalFunction, public TestFunction
{
	public:

	virtual void setNewSolution(std::shared_ptr<alggen::base::Solution> const& s) const final;
	virtual void mutateLastSolution(std::shared_ptr<alggen::base::Mutation> const& m) const final;

	protected:

	virtual std::uint64_t incremental_evaluation(std::shared_ptr<alggen::base::Mutation> const& m) const final;

	private:

	mutable std::uint64_t lastSolutionEvaluation_{0};
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
