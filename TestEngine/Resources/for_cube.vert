attribute vec4 Vertex;
uniform mat4 MatrixPos;

void main(void)
{
    gl_Position = MatrixPos * Vertex;
}
