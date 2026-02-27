#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"

#include <glad/glad.h>
#include "helper/glslprogram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//lab 2 work
//#include "helper/torus.h"

//lab3 work
#include "helper/plane.h"
#include "helper/objmesh.h"

class SceneBasic_Uniform : public Scene
{
private:
    //GLuint vaoHandle; LAB1 LINE
   // Torus torus; 

    //lab3 plane and objmesh
    Plane plane; //plane surface
    std::unique_ptr<ObjMesh>mesh; //pig mesh
    std::unique_ptr<ObjMesh>mesh2; //for eye

    GLSLProgram prog;


    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

  //  float angle;LAB1 LINE
    //glm::mat4 rotationMatrix;LAB1 LINE


    void compile();

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);

    void setMatrices();//lab2 
};

#endif // SCENEBASIC_UNIFORM_H

