//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_G_GAME_OBJECT_H
#define NOMAD_G_GAME_OBJECT_H

#include "g_model.h"

#include <memory>

namespace genom {
    struct Transform2dComponent {
        glm::vec2 translation{}; // position offset
        glm::vec2 scale{1.f, 1.f};
        float rotation;

        glm::mat2 mat2() {
            const float s = glm::sin(rotation);
            const float c = glm::cos(rotation);
            glm::mat2 rotMatrix{{c,  s},
                                {-s, c}};
            
            glm::mat2 scaleMat{{scale.x, 0.f},
                               {0.f,     scale.y}};
            return rotMatrix * scaleMat;
        }
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

        Transform2dComponent transform2d{};
    private:
        GGameObject(id_t objId) : id{objId} {}

        id_t id;
    };
}

#endif //NOMAD_G_GAME_OBJECT_H
