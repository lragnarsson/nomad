//
// Created by Lage Ragnarsson on 12.09.21.
//

#include "world.h"

namespace world {

    void World::GetTerrainObjects(const int x, const int z, genom::GDevice &gDevice,
                                  genom::GGameObject::Map &results) {

        auto terrainChunk = world::Chunk(x, z);
        std::shared_ptr<genom::GModel> terrainModel = genom::GModel::createModelFromTerrain(gDevice,
                                                                                            terrainChunk);

        auto terrainObject = genom::GGameObject::createGameObject();
        terrainObject.model = terrainModel;
        terrainObject.transform.translation = {x, 0.f, z};
        terrainObject.transform.scale = glm::vec3{1.f, 1.f, 1.f};
        terrainObject.billboard = std::make_unique<genom::BillboardComponent>();
        terrainObject.billboard->size = glm::vec2{5.f, 5.f};
        //terrainChunk.heightMap

        results.emplace(terrainObject.getId(), std::move(terrainObject));
    }
}