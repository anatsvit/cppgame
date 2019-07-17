#ifndef ENTITY_TRANSFORMER_H
#define ENTITY_TRANSFORMER_H

#include "entity.h"
#include "game_structs.h"
#include "platform.h"

class EntityTransformer
{
	public:
		static Entity* transform(EntityPlace *eplace);
};
#endif
