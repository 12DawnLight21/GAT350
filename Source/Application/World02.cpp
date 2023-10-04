#include "World02.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

namespace nc
{
    bool World02::Initialize()
    {
        //shaders //what our text files will look like but EUGH whys it so GROSS
        const char* vertexShader =
            "#version 430\n"
            "layout (location=0) in vec3 position;" //IN come 3 floats at LOCATION 0
            "layout (location=1) in vec3 color;" //IN come 3 floats at LOCATION 1
            "layout (location=0) out vec3 ocolor;" //sends data OUT
            "void main() {"
            "  ocolor = color;"
            "  gl_Position = vec4(position, 1.0);"
            "}";

        const char* fragmentShader =
            "#version 430\n"
            "layout (location=0) in vec3 color;"
            "out vec4 ocolor;"
            "void main() {"
            "  ocolor = vec4(color, 1);"
            "}";

        GLuint vs = glCreateShader(GL_VERTEX_SHADER); //handle for our vertex shader
        glShaderSource(vs, 1, &vertexShader, NULL); //null makes it do the whole shader
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER); //handle for our fragment shader
        glShaderSource(fs, 1, &fragmentShader, NULL);
        glCompileShader(fs);

        GLuint program = glCreateProgram();
        glAttachShader(program, vs); //attaches vert shader
        glAttachShader(program, fs); //attaches frag shader
        glLinkProgram(program);
        glUseProgram(program); //uses the program where our shaders are stored

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

        return true;
    }

    void World02::Shutdown()
    {
    }

    void World02::Update(float dt)
    {
        m_angle += 180 * dt;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? dt : 0;
        m_time += dt;
    }

    void World02::Draw(Renderer& renderer)
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
