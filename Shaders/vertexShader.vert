#version 430

in vec3 position;               //layout(location=0)
in vec3 vertexColor;            //layout(location=1)
in mat4 fullTransformMatrix;   //layout(location=2) // (2,3,4 and 5)

out vec3 theColor;

void main()
{
   vec4 v = vec4(position, 1.0);
   gl_Position = fullTransformMatrix * v;
   theColor = vertexColor;
}
