#pragma once


namespace alggen
{
namespace base
{

/* Class that represents a mutation
 * A mutation holds the informations needed to mutate
 * a Solution (class) object.
 */
class Mutation
{
	public:

	virtual ~Mutation() = default;

	private:

	virtual void requiredForVTable() const;
};

} // base namespace
} // alggen namespace
