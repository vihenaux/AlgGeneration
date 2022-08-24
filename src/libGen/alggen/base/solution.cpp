#include "solution.hpp"

namespace alggen
{
namespace base
{

Solution::~Solution()
{

}

void Solution::print(std::ostream & out) const
{
	out << "The 'print' method have not been override\n";
}

} // base namespace
} // alggen namespace

std::ostream& operator<<(std::ostream & out, std::shared_ptr<alggen::base::Solution> sol)
{
	sol->print(out);
	return out;
}
