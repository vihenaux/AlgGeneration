#include <libtest/test.hpp>
#include <alggen/neighborhood/oneflip.hpp>
#include <alggen/neighborhood/nkseedmutation.hpp>
#include <alggen/solution/bitstring.hpp>
#include <alggen/solution/nkmodel.hpp>
#include <vector>
#include <unordered_set>

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

    // NK model tests

    {
		Test t("NK model tests");

        unsigned int n = 8;
        unsigned int k = 1;
    	auto nk_model = std::make_shared<alggen::solution::NKModel>(n,k);
    	auto solution = nk_model->createSolution();
    	auto nk_neighborhood = std::make_shared<alggen::neighborhood::NKSeedNeighborhood>(5,5,n,k);
    	auto solution_neighborhood = std::make_shared<alggen::neighborhood::OneFlipNeighborhood>(n);
    	auto nk_mutation = nk_neighborhood->nextNeighbor();
    	auto solution_mutation = solution_neighborhood->nextNeighbor();

        alggen::base::Fitness evaluations[9];
    	evaluations[0] = (*nk_model)(solution);
    	evaluations[1] = (*nk_model)(solution_mutation);

    	solution->mutate(solution_mutation);
    	evaluations[2] = (*nk_model)(solution);
    	solution->reverseMutation(solution_mutation);

    	nk_model->mutate(nk_mutation);
    	evaluations[3] = (*nk_model)(solution);
    	evaluations[4] = (*nk_model)(solution_mutation);

    	solution->mutate(solution_mutation);
    	evaluations[5] = (*nk_model)(solution);
    	solution->reverseMutation(solution_mutation);

    	nk_model->reverseMutation(nk_mutation);
    	evaluations[6] = (*nk_model)(solution);
    	evaluations[7] = (*nk_model)(solution_mutation);

    	solution->mutate(solution_mutation);
    	evaluations[8] = (*nk_model)(solution);

    	std::vector<std::unordered_set<unsigned int>> expected_true = {{0,6},{1,2,7,8},{1,2,7,8},{3},{4,5},{4,5},{0,6},{1,2,7,8},{1,2,7,8}};

        for(unsigned int i(0); i < 9; ++i)
        {
            for(unsigned int j(0); j < 9; ++j)
            {
                if(expected_true[i].count(j) != 0)
    		        t.expectEqual(evaluations[i].get_int(), evaluations[j].get_int(), "Same evaluation (" + std::to_string(i) + "," + std::to_string(j) + ")");
    		    else
    		        t.expectDifferent(evaluations[i].get_int(), evaluations[j].get_int(), "Different evaluation (" + std::to_string(i) + "," + std::to_string(j) + ")");
            }
        }
    }

	return 0;
}
