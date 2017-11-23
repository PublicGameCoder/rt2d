#ifndef GRIDENTITY_H
#define GRIDENTITY_H

#include <rt2d/entity.h>

/// @brief The MyScene class is the Scene implementation.
class GridEntity : public Entity
{
public:
	/// @brief Constructor
	GridEntity();
	/// @brief Destructor
	virtual ~GridEntity();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

};

#endif // !GRIDENTITY_H
