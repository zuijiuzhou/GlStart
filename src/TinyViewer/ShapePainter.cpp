#include "ShapePainter.h"

using namespace TinyViewer;

void ShapePainter::init()
{
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

    if (m_isInitialized)
        return;

    m_isInitialized = true;
}

void ShapePainter::drawTriangle()
{
#ifdef __GL_FIXED_PIPLINE__
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, -1.0, 0.0);
    glEnd();
#else

    static GLfloat triangleData[] = {
        0.0f, 0.4f, 0.2f, 1.0f, 0.0f, 0.0f,
        0.3f, -0.2f, 0.4f, 0.0f, 1.0f, 0.0f,
        -0.5f, -.4f, .6f, .0f, 0.f, 1.0f};

    static GLuint triangleVaoId = 0, triangleVboId = 0;

    if (triangleVaoId == 0)
    {
        glGenVertexArrays(1, &triangleVaoId);
        glBindVertexArray(triangleVaoId);

        glGenBuffers(1, &triangleVboId);
        glBindBuffer(GL_ARRAY_BUFFER, triangleVboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const GLvoid *)(3 * sizeof(float)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    }

#endif
}