#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 vertPos; //Vertex position in eye coords
out vec3 N; //Transformed normal
out vec3 lightPos; //Light position in eye coords



uniform vec3 LightPosition; // Light position 
uniform mat3 NormalMatrix;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{

   vertPos = vec3(View * Model * vec4(VertexPosition,1.0)); 
     
   lightPos = vec3(View * Model * vec4(LightPosition,1.0));  

   N = normalize( NormalMatrix * VertexNormal);
      
   gl_Position = gl_Position = Projection * View * Model * vec4(VertexPosition,1.0);
}