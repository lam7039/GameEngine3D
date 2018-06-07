#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <string>
#include "Renderer.h"
#include "Debug.h"
#include "Entity.h"
#include "Asset.h"
#include "Input.h"

namespace se {

	///
	/// Load assets, scenes from an XML file with this loader.
	///
	class SceneLoader {
	public:
		///
		/// Load the assets, scenes and entities within the scenes with the given path to the XML file that contains the data to load.
		///
		SceneLoader(const std::string &path, AbstractRenderer *renderer, AbstractInput *input);
	private:
		Debug m_logger;
		static AbstractRenderer *m_renderer;
		static AbstractInput *m_input;

		static Entity *CreateEntity(const std::string &type, const std::string &assetName, Vector3f position, Vector3f scale, Vector3f rotation);
		static AbstractAsset *CreateAsset(const std::string &type, const std::string &assetName, const std::string *sources);
	};

}

#endif