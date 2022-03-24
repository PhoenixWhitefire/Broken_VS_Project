#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexColor;
layout (location = 3) in vec2 TexUV;

out vec3 FragIn_VertexColor;
out vec2 FragIn_UV;

out vec3 FragIn_VertexNormal;
out vec3 FragIn_CurrentPosition;

uniform mat4 CameraMatrix;

uniform float Time;
uniform vec3 Size;

uniform vec3 Position;

uniform float DeformVerticesScale;

void main() {
	//float Displace = (sin(Time) * -length(VertexPosition) * 0.5) * DeformVerticesScale;
	
	vec3 CurrentPosition = Position + (VertexPosition * Size);

	FragIn_CurrentPosition = CurrentPosition;

	FragIn_VertexNormal = VertexNormal;

	gl_Position = CameraMatrix * vec4(CurrentPosition, 1.0f);

	//gl_Position = vec4(Position, 1.0f);

	FragIn_VertexColor = VertexColor;
	FragIn_UV = TexUV;
}
