#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec3 Gnormal;
out vec3 Gposition;
noperspective out vec3 GEdgeDistance;

in vec3 VNormal[];
in vec3 VPosition[] 
