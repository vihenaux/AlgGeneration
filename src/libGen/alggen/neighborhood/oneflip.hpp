#include <alggen/base/neighborhood.hpp>
#include <cstdlib>

namespace alggen
{
namespace mutation
{

// One flip mutation for bit string solutions
// This mutation contains the data to flip one bit of a solution
class OneFlip : public base::Mutation
{
	public:

	OneFlip(std::size_t bit);
	virtual ~OneFlip() override = default;

	inline std::size_t getBit() const { return bit_; }

	virtual void requiredForVTable() override;

	private:

	std::size_t bit_;
};

} // mutation namespace
namespace neighborhood
{

class OneFlipNeighborhood final : public alggen::base::Neighborhood
{
	public:

	OneFlipNeighborhood(std::size_t stringLength);
	virtual ~OneFlipNeighborhood() final;

	virtual bool neighborAvailable() const final;

	private:

	virtual void setNewSolutionPvt(std::shared_ptr<alggen::base::Solution> const& s) final;

	virtual std::shared_ptr<alggen::base::Mutation> nextNeighborPvt() final;
	virtual void acceptMutationPvt(std::shared_ptr<alggen::base::Mutation> const& m) final;

	std::size_t length_;
	std::size_t current_;
	std::size_t * neighbors_;
};

} // neighborhood namespace
} // alggen namespace
