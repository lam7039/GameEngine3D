#ifndef ENTITYDERIVED_H
#define ENTITYDERIVED_H

#include "Entity.h"

namespace se {

	class EntityDerived : public Entity {
	public:
		EntityDerived();
		///
		/// Update the entity each frame.
		///
		void Update(float delta) override;
		///
		/// Render the entity model
		///
		void Render(AbstractRenderer *renderer) override;
	private:

	};

}

#endif