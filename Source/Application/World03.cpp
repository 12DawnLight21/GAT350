#include "World03.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

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

        return true;
    }

    void World03::Shutdown()
    {
    }

    void World03::Update(float dt)
    {
        m_angle += 180 * dt;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? dt : 0;
        m_time += dt;

        GLint uniform = glGetUniformLocation(m_program->m_program, "time");
        glUniform1f(uniform, m_time);
    }

    void World03::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render //uses normailzed coordinates
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);

        // post-render
        renderer.EndFrame();
    }
}
