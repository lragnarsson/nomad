//
// Created by Lage Ragnarsson on 06.09.21.
//

#include "g_model.h"

#include "../utils/hashing.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include <tiny_obj_loader.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>

#include <functional>
#include <unordered_map>

namespace std {
    template<>
    struct hash<genom::GVertex> {
        size_t operator()(genom::GVertex const &vertex) const {
            size_t seed = 0;
            utils::hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
            return seed;
        }
    };
}  // namespace std


namespace genom {

    /** Z forward, -Y up model coordinate convention */
    std::unique_ptr<GModel> GModel::createModelFromFile(GDevice &device, const std::string &filePath) {
        GModel::Builder builder{};
        builder.loadModel(filePath);
        return std::make_unique<GModel>(device, builder);
    }

    std::unique_ptr<GModel> GModel::createModelFromTerrain(GDevice &device, const world::Chunk &terrainChunk) {
        GModel::Builder builder{};
        builder.loadTerrain(terrainChunk);
        return std::make_unique<GModel>(device, builder);
    }

    void GModel::Builder::loadModel(const std::string &filePath) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str())) {
            throw std::runtime_error(warn + err);
        }

        vertices.clear();
        indices.clear();

        std::unordered_map<GVertex, uint32_t> uniqueVertices{};
        for (const auto &shape: shapes) {
            for (const auto &index: shape.mesh.indices) {
                GVertex vertex{};

                if (index.vertex_index >= 0) {
                    vertex.position = {
                            attrib.vertices[3 * index.vertex_index + 0],
                            attrib.vertices[3 * index.vertex_index + 1],
                            attrib.vertices[3 * index.vertex_index + 2],
                    };

                    vertex.color = {
                            attrib.colors[3 * index.vertex_index + 0],
                            attrib.colors[3 * index.vertex_index + 1],
                            attrib.colors[3 * index.vertex_index + 2],
                    };
                }

                if (index.normal_index >= 0) {
                    vertex.normal = {
                            attrib.normals[3 * index.normal_index + 0],
                            attrib.normals[3 * index.normal_index + 1],
                            attrib.normals[3 * index.normal_index + 2],
                    };
                }

                if (index.texcoord_index >= 0) {
                    vertex.uv = {
                            attrib.texcoords[2 * index.texcoord_index + 0],
                            attrib.texcoords[2 * index.texcoord_index + 1],
                    };
                }

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }
                indices.push_back(uniqueVertices[vertex]);
            }
        }
    }

    void GModel::Builder::loadTerrain(const world::Chunk &terrain) {
        vertices.clear();
        indices.clear();

        for (int i = 0; i < world::NUM_CHUNK_TILES; i++) {
            for (int j = 0; j < world::TILE_VERTICES; j++) {
                auto v = terrain.tiles[i].vertices[j];
                vertices.push_back(v);
                indices.push_back(world::TILE_VERTICES * i + terrain.tiles[i].indices[j]);
                // std::cout << v << "idx: " << idx << std::endl;
            }
        }
    }
}