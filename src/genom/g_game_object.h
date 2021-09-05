//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_G_GAME_OBJECT_H
#define NOMAD_G_GAME_OBJECT_H

#include "g_model.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace genom {
    struct TransformComponent {
        glm::vec3 translation{}; // position offset
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation{};

        glm::mat4 mat4();

        glm::mat3 normalMatrix();
    };

    class GGameObject {
    public:
        using id_t = unsigned int;

        static GGameObject createGameObject() {
            static id_t currentId = 0;
            return GGameObject{currentId++};
        }

        GGameObject(const GGameObject &) = delete;

        GGameObject &operator=(const GGameObject &) = delete;

        GGameObject(GGameObject &&) = default;

        GGameObject &operator=(GGameObject &&) = default;

        id_t getId() { return id; }

        std::shared_ptr<GModel> model{};

        glm::vec3 color{};

        TransformComponent transform{};
    private:
        GGameObject(id_t objId) : id{objId} {}

        id_t id;
    };
}

#endif //NOMAD_G_GAME_OBJECT_H
