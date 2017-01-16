#version 130

in vec3 position;               //layout(location=0)
in vec3 vertexColor;            //layout(location=1)

uniform mat4 fullTransformMatrix;

out vec3 theColor;

void main()
{
   gl_Position = fullTransformMatrix * vec4(position, 1.0);
   theColor = vertexColor;
}
