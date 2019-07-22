#include "entity_transformer.h"

Entity* EntityTransformer::transform(EntityPlace *eplace)
{
	if (eplace->type == ENTITY_TYPE_PLATFORM) {
		Platform *platform = new Platform();
		platform->setX(eplace->x_coor);
		platform->setY(eplace->y_coor);
        platform->setWidth(8);
        platform->setHeight(8);
		return platform;
	}
	
	return new Entity();
}
