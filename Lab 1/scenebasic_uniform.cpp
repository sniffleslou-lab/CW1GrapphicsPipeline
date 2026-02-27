#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <sstream>

#include <string>
#include <filesystem>

using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4; //lab2
using glm::vec4;

#include <glm/gtc/constants.hpp>


//below used to be angl(0.0f)

SceneBasic_Uniform::SceneBasic_Uniform() : plane (10.0f, 10.0f, 100, 100) {

    mesh = ObjMesh::load("media/pig_triangulated.obj", true);
}

void SceneBasic_Uniform::initScene()
{
    compile();

   
    glEnable(GL_DEPTH_TEST);
    //set the camera and the 3 lights 
    view = glm::lookAt(vec3(3.6f, 0.75f, 0.75f),
        vec3(0.0f, 0.1f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);
    // Single light for per-fragment Phong
    vec3 lightPosEye = vec3(view * vec4(-2.0f, 4.0f, 2.0f, 1.0f));
    prog.setUniform("LightPosition", lightPosEye);
    prog.setUniform("LightLa", vec3(0.2f));
    prog.setUniform("LightLd", vec3(0.8f));
    prog.setUniform("LightLs", vec3(0.8f));
    // specular

  
}

void SceneBasic_Uniform::compile()
{
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;
	try {
      

        prog.compileShader("shader/PerFragment_phong.vert");
        prog.compileShader("shader/PerFragment_phong.frag");

		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
	//update your angle here
  //  if (m_animate) {
    //    angle += 0.1f;
      //  if (angle >= 360.0f) angle -= 360.0f;
    //}

   

}

void SceneBasic_Uniform::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    prog.setUniform("Kd", 1.0f, 0.6f, 0.7f);
    prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Ka", 0.6f, 0.3f, 0.4f);
    prog.setUniform("Shininess", 200.0f);


    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    setMatrices();
    mesh->render();


    prog.setUniform("Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Shininess", 180.0f);


    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
    setMatrices();
    plane.render();
}

void SceneBasic_Uniform::setMatrices() 
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", 
        glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
}

void SceneBasic_Uniform::resize(int w, int h)
{
  //  width = w;
  //  height = h;
    glViewport(0,0,w,h);
    float aspect = (float)w / h;
    projection = glm::perspective(glm::radians(60.0f), aspect, 0.3f, 100.0f);
}
