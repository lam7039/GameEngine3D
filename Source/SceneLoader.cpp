#include "SceneLoader.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "Camera.h"
#include "Terrain.h"
#include "Skybox.h"
#include "Model.h"

namespace se {

	AbstractRenderer *SceneLoader::m_renderer = nullptr;
	AbstractInput *SceneLoader::m_input = nullptr;

	SceneLoader::SceneLoader(AbstractRenderer *renderer, const std::string &path, AbstractInput *input) {
		m_logger.SelectLogger("engine.log");
		m_renderer = renderer;
		m_input = input;

		rapidxml::file<> xmlFile(path.c_str());
		rapidxml::xml_document<> document;
		document.parse<0>(xmlFile.data());

		rapidxml::xml_node<> *node = document.first_node("Assets");
		if (!node) {
			m_logger.Log(ERRORTYPE_WARNING, __FILE__, __LINE__, "Assets root does not exist");
		}
		else {
			for (rapidxml::xml_node<> *asset = node->first_node(); asset; asset = asset->next_sibling()) {
				std::string type = asset->first_node("Type")->value();

				std::string *sources;
				if (asset->first_node("HeightmapPath")) {
					sources = new std::string[2];
					sources[0] = asset->first_node("AssetPath")->value();
					sources[1] = asset->first_node("HeightmapPath")->value();
				}
				else {
					sources = new std::string[1];
					sources[0] = asset->first_node("AssetPath")->value();
				}

				AbstractAsset *createdAsset = CreateAsset(type, asset->first_node("AssetName")->value(), sources);
				if (sources) {
					delete[] sources;
				}
				if (createdAsset) {
					AssetManager::GetInstance()->AddAsset(asset->first_node("AssetName")->value(), createdAsset);
				}
			}
		}

		node = document.first_node("Scenes");
		if (!node) {
			m_logger.Log(ERRORTYPE_WARNING, __FILE__, __LINE__, "Scenes root does not exist");
		}
		else {
			for (rapidxml::xml_node<> *scene = node->first_node(); scene; scene = scene->next_sibling()) {
				SceneManager::GetInstance()->AddScene(scene->first_node()->value());
				for (rapidxml::xml_node<> *entity = scene->first_node("Entity"); entity; entity = entity->next_sibling()) {
					rapidxml::xml_node<> *entityNode;
					std::string::size_type size;
					std::string x;
					std::string y;
					std::string z;

					entityNode = entity->first_node("Position");
					Vector3f position;
					if (entityNode) {
						x = entityNode->first_node("x")->value();
						y = entityNode->first_node("y")->value();
						z = entityNode->first_node("z")->value();
						position.Set(std::stof(x, &size), std::stof(y, &size), std::stof(z, &size));
					}

					entityNode = entity->first_node("Scale");
					Vector3f scale(1.0f, 1.0f, 1.0f);
					if (entityNode) {
						x = entityNode->first_node("x")->value();
						y = entityNode->first_node("y")->value();
						z = entityNode->first_node("z")->value();
						scale.Set(std::stof(x, &size), std::stof(y, &size), std::stof(z, &size));
					}

					entityNode = entity->first_node("Rotation");
					Vector3f rotation;
					if (entityNode) {
						x = entityNode->first_node("x")->value();
						y = entityNode->first_node("y")->value();
						z = entityNode->first_node("z")->value();
						rotation.Set(std::stof(x, &size), std::stof(y, &size), std::stof(z, &size));
					}
					
					entityNode = entity->first_node("AssetName");
					std::string assetName = (entityNode) ? entityNode->value() : "";
					entityNode = entity->first_node("Type");
					std::string type = (entityNode) ? entityNode->value() : "";

					Entity *createdEntity = CreateEntity(type, assetName, position, scale, rotation);
					SceneManager::GetInstance()->GetScene(scene->first_node()->value())->AddEntity(createdEntity);
				}
			}
		}

	}

	Entity *SceneLoader::CreateEntity(const std::string &type, const std::string &assetName, Vector3f position, Vector3f scale, Vector3f rotation) {
		Entity *temp = new Entity();
		temp->SetAssetName(assetName);
		temp->SetPosition(position);
		temp->SetScale(scale);
		temp->SetRotation(rotation);
		if (type == "Skybox") {
			temp->SetEntityType(ENTITYTYPE_SKYBOX);
		}
		else if (type == "Terrain") {
			temp->SetEntityType(ENTITYTYPE_TERRAIN);
		}
		else if (type == "Model") {
			temp->SetEntityType(ENTITYTYPE_MODEL);
		}
		else if (type == "Camera") {
			delete temp;
			temp = new Camera(m_renderer, m_input, assetName);
			temp->SetEntityType(ENTITYTYPE_CAMERA);
		}
		return temp;
	}

	AbstractAsset *SceneLoader::CreateAsset(const std::string &type, const std::string &assetName, const std::string *sources) {
		if (type == "Skybox") {
			return new Skybox(m_renderer, assetName, sources[0]);
		}
		else if (type == "Terrain") {
			return new Terrain(m_renderer, assetName, sources[1], sources[0]);
		}
		else if (type == "Model") {
			return new Model(m_renderer, assetName, sources[0]);
		}
		return nullptr;
	}

}