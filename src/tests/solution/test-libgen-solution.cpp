#include <libtest/test.hpp>
#include <alggen/neighborhood/oneflip.hpp>
#include <alggen/solution/bitstring.hpp>

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

	// 1flip mutation class tests

	{
		Test t("Oneflip mutation tests");

		std::size_t inputValue = static_cast<std::size_t>(static_cast<std::size_t>(rand()%256));

		alggen::mutation::OneFlip oneflip(inputValue);


		t.expectEqual(inputValue, oneflip.getBit(), "Mutation holds value");

		alggen::mutation::OneFlip copy(oneflip);

		t.expectEqual(oneflip.getBit(), copy.getBit(), "Mutation copy");
	}

	// Bitstring class tests

	{
		Test t("Bitstring tests");

		std::shared_ptr<alggen::solution::BitString> s1(new alggen::solution::BitString(256));
		std::shared_ptr<alggen::solution::BitString> s2(new alggen::solution::BitString(256));


		bool same = true;
		for(std::size_t i(0); i < 265; ++i)
		{
			same = same && ((*s1)[i] == (*s2)[i]);
		}

		t.expectFalse(same, "Default constructor is random");

		s2->copySolution(s1);
		std::shared_ptr<alggen::solution::BitString> s3 = std::dynamic_pointer_cast<alggen::solution::BitString>(s1->createSolutionCopy());

		same = true;
		bool createCopy = true;
		for(std::size_t i(0); i < 265; ++i)
		{
			same = same && ((*s1)[i] == (*s2)[i]);
			createCopy = createCopy && ((*s1)[i] == (*s3)[i]);
		}

		t.expectTrue(same, "Solution copy");
		t.expectTrue(same, "Solution create copy");

		std::shared_ptr<alggen::mutation::OneFlip> m(new alggen::mutation::OneFlip(rand()%256));
		s1->mutate(m);

		t.expectDifferent((*s1)[m->getBit()], (*s2)[m->getBit()], "Mutation works");

		s1->reverseMutation(m);

		t.expectEqual((*s1)[m->getBit()], (*s2)[m->getBit()], "Reverse Mutation works");

		s1->mutate(m);
		s2->mutate(m);

		t.expectEqual((*s1)[m->getBit()], (*s2)[m->getBit()], "Mutation is coherent");


		s1->randomize();
		s2->randomize();
		same = true;
		for(std::size_t i(0); i < 265; ++i)
		{
			same = same && ((*s1)[i] == (*s2)[i]);
		}

		t.expectFalse(same, "Randomize function is random");
	}


	return 0;
}
