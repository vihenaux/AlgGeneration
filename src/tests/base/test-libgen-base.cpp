#include <libtest/test.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <memory>

#include "testclasses.hpp"

int main(int argc, char **argv)
{
	unsigned int seed = 0;
	switch(argc)
	{
		case 1:
			seed = static_cast<unsigned int>(time(nullptr));
			break;
		case 2:
			seed = static_cast<unsigned int>(std::stoi(std::string(argv[1])));
			break;
		default:
			std::cerr << "Usage : " << argv[0] << " seed (int optional)" << std::endl;
			return 1;
	}
	srand(seed);

	std::cout << "Reproductible with : " << argv[0] << " " << seed << std::endl;

	// Mutation class tests

	{
		Test t("Mutation tests");

		std::int8_t inputValue = static_cast<std::int8_t>(static_cast<std::int16_t>(rand()%256)-128);

		TestMutation tm(inputValue);


		t.expectEqual(static_cast<std::int16_t>(inputValue), static_cast<std::int16_t>(tm.getOffset()), "Mutation holds value");

		TestMutation copy(tm);

		t.expectEqual(static_cast<std::int16_t>(tm.getOffset()), static_cast<std::int16_t>(copy.getOffset()), "Mutation copy");
	}

	// Solution class tests

	{
		Test t("Solution tests");

		bool isConstructorRandom = false;
		for(unsigned int i(0); i < 100; ++i)
		{
			TestSolution s1,s2;
			if(s1.getValue() != s2.getValue())
			{
				isConstructorRandom = true;
				break;
			}
		}

		t.expectTrue(isConstructorRandom, "Default constructor is random");

		std::shared_ptr<TestSolution> s1(new TestSolution());
		std::shared_ptr<TestSolution> s2(new TestSolution());
		s2->copy(std::dynamic_pointer_cast<Solution>(s1));

		t.expectEqual(static_cast<std::uint16_t>(s1->getValue()), static_cast<std::uint16_t>(s2->getValue()), "Solution copy");

		t.expectEqual(static_cast<std::uint16_t>(s1->getValue()), static_cast<std::uint16_t>(s1->getValue()), "Solution is coherent");


		std::shared_ptr<TestMutation> m(new TestMutation(1));
		s1->mutate(m);

		t.expectDifferent(static_cast<std::uint16_t>(s1->getValue()), static_cast<std::uint16_t>(s2->getValue()), "Mutation works");

		s1->reverseMutation(m);

		t.expectEqual(static_cast<std::uint16_t>(s1->getValue()), static_cast<std::uint16_t>(s2->getValue()), "Reverse Mutation works");

		s1->mutate(m);
		s2->mutate(m);

		t.expectEqual(static_cast<std::uint16_t>(s1->getValue()), static_cast<std::uint16_t>(s2->getValue()), "Mutation is coherent");
	}

	// Function class tests

	{
		Test t("Function tests");

		TestFunction f;

		t.expectEqual(f.getNumberOfCalls(), 0ul, "Start function with no previous calls");

		std::shared_ptr<TestSolution> s(new TestSolution());

		t.expectEqual(static_cast<std::uint64_t>(s->getValue()), f(s), "f(x) = x");
		t.expectEqual(f(s), f(s), "f(x) = f(x) (consistency)");

		t.expectEqual(f.getNumberOfCalls(), 3ul, "Function called 3 times");

		auto sr1 = f.getRandomSolution();
		auto sr2 = f.getRandomSolution();

		t.expectDifferent(	static_cast<std::uint16_t>(std::dynamic_pointer_cast<TestSolution>(sr1)->getValue()),
							static_cast<std::uint16_t>(std::dynamic_pointer_cast<TestSolution>(sr2)->getValue()),
							"Function generates random solutions");
	}

	// Neighborhood class tests

	{
		Test t("Neighborhood tests");

		TestNeighborhood n;
		std::shared_ptr<TestSolution> s1(new TestSolution(255));
		std::shared_ptr<TestSolution> s2(new TestSolution(0));
		std::shared_ptr<TestSolution> s3(new TestSolution(static_cast<std::uint8_t>((rand()%254)+1)));


		// Base tests
		t.expectEqual(n.getNumberOfNeighborsDiscarded(), 0u, "Start Neighborhood with no neighbor discarded");
		t.expectTrue(n.neighborAvailable(), "Start Neighborhood with available neighbors");


		// Tests for a non limit solution
		n.setNewSolution(s3);
		auto m1(n.nextNeighbor());

		t.expectTrue(n.neighborAvailable(), "Apart from limit values solutions have 2 neighbors");
		t.expectEqual(n.getNumberOfNeighborsDiscarded(), 1u, "One call to nextNeighbor, one neighbor discarded");

		auto m2(n.nextNeighbor());

		t.expectFalse(n.neighborAvailable(), "Two neighbors only");
		t.expectEqual(n.getNumberOfNeighborsDiscarded(), 2u, "Two call to nextNeighbor, two neighbor discarded");
		t.expectDifferent(	static_cast<std::int16_t>(std::dynamic_pointer_cast<TestMutation>(m1)->getOffset()),
							static_cast<std::int16_t>(std::dynamic_pointer_cast<TestMutation>(m2)->getOffset()),
							"Neighbors are different");

		t.expectEqual(std::max(	static_cast<std::int16_t>(std::dynamic_pointer_cast<TestMutation>(m1)->getOffset()),
								static_cast<std::int16_t>(std::dynamic_pointer_cast<TestMutation>(m2)->getOffset())),
								static_cast<std::int16_t>(1), "One neighbor is 1");

		t.expectEqual(std::min(	static_cast<std::int16_t>(std::dynamic_pointer_cast<TestMutation>(m1)->getOffset()),
								static_cast<std::int16_t>(std::dynamic_pointer_cast<TestMutation>(m2)->getOffset())),
								static_cast<std::int16_t>(-1), "The other is -1");


		// Tests for a mutation
		n.acceptMutation(m1);

		t.expectEqual(n.getNumberOfNeighborsDiscarded(), 0u, "No neighbor discarded after mutation acceptation");
		t.expectTrue(n.neighborAvailable(), "New neighbor available after mutation acceptation");


		// Tests for the first limit solution
		n.setNewSolution(s2);
		t.expectTrue(n.neighborAvailable(), "One neighbor available for limit values");
		auto m3 = n.nextNeighbor();
		t.expectFalse(n.neighborAvailable(), "Only one neighbor available for limit values");

		// Tests for thesecond limit solution
		n.setNewSolution(s1);
		t.expectTrue(n.neighborAvailable(), "One neighbor available for limit values");
		auto m4 = n.nextNeighbor();
		t.expectFalse(n.neighborAvailable(), "Only one neighbor available for limit values");
	}

	// Incremental Function class tests

	{
		Test t("Incremental Function tests");

		TestNonOverloadedIncrementalFunction f1;
		TestIncrementalFunction f2;

		TestNeighborhood n;

		auto s(f1.getRandomSolution());
		n.setNewSolution(s);

		auto m(n.nextNeighbor());

		t.expectDifferent(f1(s), f1(m), "Mutation has a different evaluation");
		t.expectEqual(f1(s), f2(s), "Different implementations but same result");
		t.expectEqual(f1(m), f2(m), "Different implementations but same result");

		auto mutationEvaluation = f1(m);

		f1.mutateLastSolution(m);
		f2.mutateLastSolution(m);

		s->mutate(m);
		m = n.nextNeighbor();

		t.expectEqual(f1(s), mutationEvaluation, "Function coherent between solution and mutation evaluation");
		t.expectEqual(f1(s), f2(s), "Implementations coherent after mutation");
	}

	return 0;
}
