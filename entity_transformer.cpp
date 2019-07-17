#include "entity_transformer.h"

Entity* EntityTransformer::transform(EntityPlace *eplace)
{
	if (eplace->type == ENTITY_TYPE_PLATFORM) {
		Platform *platform = new Platform();
		platform->setX(eplace->x_coor);
		platform->setY(eplace->y_coor);
		return platform;
	}
	
	return new Entity();
}
