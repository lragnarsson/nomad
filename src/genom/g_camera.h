//
// Created by Lage Ragnarsson on 05.09.21.
//

#ifndef NOMAD_G_CAMERA_H
#define NOMAD_G_CAMERA_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>

namespace genom {
    class GCamera {
    public:
        void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);

        void setPerspectiveProjection(float fovy, float aspect, float near, float far);

        void setViewDirection(
                glm::vec3 position, glm::vec3 diration, glm::vec3 up = glm::vec3{0.f, -1.f, 0.f});

        void setViewTarget(
                glm::vec3 position, glm::vec3 diration, glm::vec3 up = glm::vec3{0.f, -1.f, 0.f});

        void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

        
        const glm::mat4 getProjection() const { return projectionMatrix; }

        const glm::mat4 getView() const { return viewMatrix; }

    private:
        glm::mat4 projectionMatrix{1.f};
        glm::mat4 viewMatrix{1.f};
    };
}
#endif //NOMAD_G_CAMERA_H
