# OpenlGL FPS Game - Final Project for Fundamentals of Computer Graphics

This is the final project for the Fundamentals of Computer Graphics course (INF/UFRGS), developed by Joao Francisco and Mario Augusto.

**Application Description:**


## Team Members

* **Joao Francisco Hirtenkauf Munhoz** - 00275634
* **Mario Augusto Brum da Silveira** - 00322868


## Application Screenshots

![Image Caption 1](path/to/your/image1.png)


## User Manual

### Game/Application Controls

| Key/Mouse          | Action                                           |
| ------------------ | ------------------------------------------------ |
| `W`, `A`, `S`, `D` | Move the main character/object.                  |
| `Arrow Keys`       | Control the free camera.                         |
| `Mouse`            | Controls the camera's orientation.               |
| `Left Mouse`       | Aim/Zoom.                                        |
| `Right Mouse`      | Shot.                                            |
| `C`                | Switch between camera types (Look-at / Free).    |
| `K`                | Start enemies spawn.                             |
| `J`                | Stop enemies spawn.                              |
| `N`                | Restart the game.                                |
| `Esc`              | Close the application.                          |


## Development Process

[Describe the overall development process here. Talk about the technologies chosen, the challenges you faced, the design decisions you made, and how you organized the work as a pair.]

### Member Contributions

* **[João Francisco]:** [List your main contributions here. E.g., Implemented the camera system, player physics, AABB-AABB collision detection, and texturing for objects X and Y.]
* **[Mario Augusto]:** [List your main contributions here. E.g., Implemented the lighting models (Gouraud/Phong), enemy movement with Bézier curves, loading of .obj models, and point-sphere collision detection.]

* * **[João Francisco]:** [Implemented the camera system, player movement, texturing for objects, implemented the lighting models (Gouraud/Phong), rat movement with Bézier curves, loading of .obj models.]
* **[Mario Augusto]:**  [Point-sphere,Sphere-sphere, Plane-sphere collision detection ,designed the camera aiming system, and developed orb movement mechanics.]

### Use of AI Tools (ChatGPT, Copilot, etc.)

[A short paragraph indicating whether the team used ChatGPT (or any other similar tool, like Claude, Gemini, LLaMa, Github Copilot, OpenAI Codex, etc.) for the project's development. Describe how the tool was used and for which parts of the project. The paragraph must also include a critical analysis describing how useful the team found the tool, where it helped, and where it did not provide adequate assistance.]


## Implementation of CG Concepts

Below, we detail how each technical requirement from the course was implemented in our application.

* **Complex Polygonal Meshes:**
    [Describe which complex models were used (e.g., `cow.obj` or others). Explain how these models (in .obj format) were loaded, mentioning the library used (e.g., `tinyobjloader`).]

* **Geometric Transformations:**
    [Explain which transformations (scale, rotation, translation) are applied and how the user can control them. For example: "The player can rotate the selected object using the Q and E keys, which updates the object's `Model matrix` every frame."]

* **Virtual Camera Control:**
    [Detail the two types of cameras implemented (e.g., a first-person camera and a look-at camera that orbits the scene). Explain how the user can switch between them and how each one works, mentioning the calculation of the `View` and `Projection` matrices.]

* **Object Instancing:**
    [Indicate which virtual object was instanced multiple times and how this was achieved. E.g., "The trees in the scene are all drawn from the same set of vertices. For each tree, a different `Model matrix` is sent to the shader, changing its position, scale, and rotation."]

* **Intersection Tests:**
    [List the three types of collision tests implemented (e.g., sphere-sphere, AABB-AABB, point-plane) and explain the purpose of each in the application. E.g., "AABB-AABB collision is used to prevent the player from passing through walls. Sphere-sphere collision detects when the player's projectile hits an enemy." Remember to mention that the implementation is in the `collisions.cpp` file.]

* **Lighting Models (Diffuse and Blinn-Phong):**
    [Describe how the lighting models were applied. E.g., "The scene lighting uses the Lambert (diffuse) model for a simpler look, while the main character uses the Blinn-Phong model for specular highlights that give its armor a more metallic appearance."]

* **Interpolation Models (Gouraud and Phong):**
    [Explain which objects use each interpolation model. E.g., "Scene objects are rendered with Gouraud shading (per-vertex calculation) for better performance, while the player character is rendered with Phong shading (per-fragment calculation) for smoother and more accurate lighting."]

* **Texture Mapping:**
    [State that all objects have been textured and list the texture images used. Comment on the process to avoid distortion. E.g., "All objects have textures. We used three distinct images: `brick.png` for the walls, `grass.png` for the ground, and `metal.png` for the enemies. UV coordinate mapping was done carefully to ensure textures did not appear stretched."]

* **Bézier Curves:**
    [Describe which object moves along a cubic Bézier curve and how the curve was defined. E.g., "The moving platforms follow a path predefined by a cubic Bézier curve. The curve's four control points define a smooth and continuous back-and-forth movement."]

* **Time-Based Animation:**
    [Explain how movement was decoupled from the framerate. E.g., "All animations and movements, including the camera and the player, are multiplied by a `delta_t` calculated each frame. This ensures that the speed is constant across different computers."]

### Extra Features (Optional)

[If you implemented any extra features, describe them here. For example: a particle system for explosions, a GUI with ImGui to display the score, or sound effects with miniaudio.]

## Building and Running

### Dependencies
To build and run this project, you will need:
* [List necessary libraries, e.g., OpenGL, Glad, GLFW, glm]
* [List the compiler and build system, e.g., g++, CMake]
* [Any other dependencies, e.g., Python for a script]

### Build Steps

**Linux:**
```bash
# Example steps to build on Linux
mkdir build
cd build
cmake ..
make
```

### Execution

After building, the executable will be in the `build` folder. To run:

**Linux:**
```bash
# From the root folder
./build/your_executable_name
```

## Presentation Video

You can watch a demonstration of our application on YouTube:

**[Link to your YouTube video]**
