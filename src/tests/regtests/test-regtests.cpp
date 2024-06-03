#include <libtest/test.hpp>
#include <alggen/neighborhood/oneflip.hpp>
#include <alggen/problem/onemax.hpp>
#include <alggen/problem/nk.hpp>
#include <alggen/searchalgorithm/localsearch.hpp>
#include <alggen/searchalgorithm/iteratedlocalsearch.hpp>
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

    // Local search reach the global optimum in onemax
    {
        Test t("Local search reach the global optimum in onemax");

        auto fobj = std::make_shared<alggen::problem::OneMax>(16384);
        auto neighborhood = std::make_shared<alggen::neighborhood::OneFlipNeighborhood>(16384);
        alggen::searchalgorithm::LocalSearch LS(fobj,fobj->createSolution(),neighborhood);

        t.expectEqual(LS().get_int(), 16384lu, "Global optimum reached");
    }

    // Local search on NK
    {
        Test t("NK regtests");

        auto fobj = std::make_shared<alggen::problem::NK>("test_files/nk_128_1.0");
        auto neighborhood = std::make_shared<alggen::neighborhood::OneFlipNeighborhood>(128);
        alggen::searchalgorithm::IteratedLocalSearch ILS(fobj,fobj->createSolution(),neighborhood,20,100000);

        auto optimum = std::make_shared<alggen::solution::BitString>("test_files/nk_128_1.optimum_solution");
        t.expectEqual((*fobj)(optimum).get_int(), 92738769lu, "Constant evaluation");

        alggen::base::Fitness ilsResult = ILS();
        t.expectTrue((ilsResult.get_int() <= 92738769lu), "Global optimum reached");
    }

	return 0;
}
