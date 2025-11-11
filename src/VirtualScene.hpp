#ifndef VIRTUAL_SCENE_H
#define VIRTUAL_SCENE_H

struct SceneObject
{
    std::string  name;
    size_t       first_index;
    size_t       num_indices;
    GLenum       rendering_mode;
    GLuint       vertex_array_object_id;
    glm::vec3    bbox_min;
    glm::vec3    bbox_max;
};

#endif
