# eng3D README
**Basic 3D viewing engine written in C++ using OpenGL**

This project is intended as a testbed of sort for me to experiment with different physics, shading, and gameplay concepts. 

Currently, I have only built and tested the project using Visual Studio on Windows so I can't confirm how well it will work on other systems. The program is 32 bit and requires GLEW, GLFW and glm.

# IMMEDIATE TO DO LIST
- Fix dependency issues with helper functions and move them back into appropriate header files
- Implement scene graph structure for maintaining list of objects
- Implement basic collision detection for player
- Refactor player/camera classes to be more sensical
