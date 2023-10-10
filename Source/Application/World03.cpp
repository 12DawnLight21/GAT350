#include "World03.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>

#define INTERLEAVE
//allows us to exclude code easily

namespace nc
{
    bool World03::Initialize()
    {

        m_program = GET_RESOURCE(Program, "shaders/unlit_color.prog");
        m_program->Use(); //sets opengl to use THIS program

#ifdef INTERLEAVE
        //vertex data 
        float vertexData[] = { //the data is interleaved, making it faster
             -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.8f,  0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
             -0.8f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
             -0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f
        };

        GLuint vbo;

        //position
        glGenBuffers(1, &vbo); 
        glBindBuffer(GL_ARRAY_BUFFER, vbo); 
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_vao); 
        glBindVertexArray(m_vao); 

        glBindVertexBuffer(0, vbo, 0, 6 * sizeof(GLfloat)); //its six cause we're storing XYZ RGB in the same stride

        //position
        glEnableVertexAttribArray(0); 
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0); //format is the newer version
        glVertexAttribBinding(0, 0);

        glEnableVertexAttribArray(1);
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
        glVertexAttribBinding(1, 0);

#else
        //vertex data 
        float positionData[] = { 
             -0.8f, -0.8f, 0.0f, //-0.8, -0.8, 0
             0.8f, -0.8f, 0.0f, //0.8, -0.8, 0
             0.8f,  0.8f, 0.0f,  //0.8, 0.8, 0
             -0.8f, 0.8f, 0.0f,
             -0.8f, -0.8f, 0.0f,
        };

        float colorData[] =
        {
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f
        };

        GLuint vbo[2];

        //position
        glGenBuffers(2, vbo); //vertex buffer object
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //"hey! this is current buffer + use this pls"
        glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW); //sizeof checks the size of arrays by the amount of bytes it is

        //colors
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); 
        glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
        
        glGenVertexArrays(1, &m_vao); //creates vertex array objecy
        glBindVertexArray(m_vao); //set vertex array object as current

        //position
        glEnableVertexAttribArray(0); //set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //3 floats per position
        glBindVertexBuffer(0, vbo[0], 0, 3 * sizeof(GLfloat)); //actually sets the buffer lol

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
        glBindVertexBuffer(3, vbo[1], 0, 3 * sizeof(GLfloat));
#endif

        m_transform.position.z = -10.0f;

        return true;
    }

    void World03::Shutdown()
    {
    }

    void World03::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();
        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0]);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0]);
        ImGui::End();

        m_transform.rotation.z += 180 * dt; // spinny spinns

        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * dt : 0;
        m_transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_Q) ? m_speed * -dt : 0;
        m_transform.position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_E) ? m_speed * dt : 0;
        m_time += dt;

        //model matrix
        m_program->SetUniform("model", m_transform.GetMatrix());

        //view matrix 
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 4, 5 }, glm::vec3{ 0, 0, 0 }, glm::vec3{0, 1, 0}); //make the -5 a 5 or else itll be weird!!!
        m_program->SetUniform("view", view);

        //projection
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f/600.0f, 0.01f, 100.0f);
        m_program->SetUniform("projection", projection);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World03::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render //uses normailzed coordinates
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
}
