#pragma once

/* Class that represents a mutation
 * A mutation holds the informations needed to mutate
 * a Solution (class) object.
 */
class Mutation
{
	public:

	virtual ~Mutation() = default;

	virtual void requiredForVTable();
};
