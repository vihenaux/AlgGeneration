#include <libtest/test.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <memory>

#include <alggen/problem/nk.hpp>
#include <alggen/neighborhood/oneflip.hpp>

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

    // Incremental Function class tests

    {
        Test t("Incremental NK tests");

        alggen::problem::NK f(128, 2);

        auto neighborhood = std::make_shared<alggen::neighborhood::OneFlipNeighborhood>(128);

        auto s(f.createSolution());
        neighborhood->setNewSolution(s);

        auto m(neighborhood->nextNeighbor());


        t.expectDifferent(f(s).get_int(), f(m).get_int(), "Mutation has a different evaluation");

        auto mutationEvaluation = f(m);

        f.mutateLastSolution(m);

        s->mutate(m);

        t.expectEqual(f(s).get_int(), mutationEvaluation.get_int(), "Implementations coherent after mutation");
    }

    return 0;
}
