//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_G_GAME_OBJECT_H
#define NOMAD_G_GAME_OBJECT_H

#include "g_model.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <unordered_map>

namespace genom {
    struct TransformComponent {
        glm::vec3 translation{}; // position offset
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation{};

        glm::mat4 mat4();

        glm::mat3 normalMatrix();
    };

    struct PointLightComponent {
        float lightIntensity = 1.0f;
        float lightAttenuation = 0.1f;
    };

    class GGameObject {
    public:
        using id_t = unsigned int;
        using Map = std::unordered_map<id_t, GGameObject>;

        static GGameObject createGameObject() {
            static id_t currentId = 0;
            return GGameObject{currentId++};
        }

        static GGameObject makePointLight(float intensity = 10.f,
                                          float radius = 0.1f,
                                          glm::vec3 color = glm::vec3(1.f),
                                          float attenuation = 0.1f);

        GGameObject(const GGameObject &) = delete;

        GGameObject &operator=(const GGameObject &) = delete;

        GGameObject(GGameObject &&) = default;

        GGameObject &operator=(GGameObject &&) = default;

        id_t getId() { return id; }

        glm::vec3 color{};

        TransformComponent transform{};

        // Optional components
        std::shared_ptr<GModel> model{};
        std::unique_ptr<PointLightComponent> pointLight = nullptr;
    private:
        GGameObject(id_t objId) : id{objId} {}

        id_t id;
    };
}

#endif //NOMAD_G_GAME_OBJECT_H
