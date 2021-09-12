//
// Created by Lage Ragnarsson on 12.09.21.
//

#include "world.h"

namespace world {

    void World::GetTerrainObjects(const int x, const int z, genom::GDevice &gDevice,
                                  std::vector<genom::GGameObject> &results) {
        auto terrainChunk = world::Chunk(0, 0, DESERT_CHUNK);
        std::shared_ptr<genom::GModel> terrainModel = genom::GModel::createModelFromTerrain(gDevice, terrainChunk);

        auto terrainObject = genom::GGameObject::createGameObject();
        terrainObject.model = terrainModel;
        terrainObject.transform.translation = {0.f, 0.f, 0.f};
        terrainObject.transform.scale = glm::vec3{1.f, 1.f, 1.f};
        results.push_back(std::move(terrainObject));

        auto terrainChunk2 = world::Chunk(-1, 0, PLAINS_CHUNK);
        std::shared_ptr<genom::GModel> terrainModel2 = genom::GModel::createModelFromTerrain(gDevice, terrainChunk2);

        auto terrainObject2 = genom::GGameObject::createGameObject();
        terrainObject2.model = terrainModel2;
        terrainObject2.transform.translation = {-CHUNK_WIDTH, 0.f, 0.f};
        terrainObject2.transform.scale = glm::vec3{1.f, 1.f, 1.f};

        results.push_back(std::move(terrainObject2));
    }
}