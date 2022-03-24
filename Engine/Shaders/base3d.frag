#version 330 core

uniform sampler2D Diffuse0;
uniform sampler2D Specular0;

uniform int HasDiffuse = 0;
uniform int HasSpecular = 0;

uniform vec3 LightPosition;
uniform vec3 LightColor;

out vec4 FragColor;

in vec3 FragIn_VertexColor;
in vec2 FragIn_UV;

in vec3 FragIn_VertexNormal;
in vec3 FragIn_CurrentPosition;

float MAX_SPECULAR_LIGHT = 0.5f;
float LIGHT_AMBIENT = 0.2f;

uniform vec3 CameraPosition;

float PointLight(vec3 Direction) {
	float Distance = length(Direction) * 0.1f;

	float a = 0.01f;
	float b = 0.01f;

	float Intensity = 1.0f / (a * Distance * Distance + b * Distance + 1.0f);

	return Intensity;
}

float SpotLight(vec3 Direction) {
	float OuterCone = 90.0f;
	float InnerCone = 95.0f;

	float Angle = dot(vec3(0.0f, -1.0f, 0.0f), -normalize(Direction));

	return clamp(Angle + (OuterCone / InnerCone) * (Angle * OuterCone), 0.0f, 1.0f);
}

void main() {
	vec3 VertexNormal_Normalized = normalize(FragIn_VertexNormal);

	vec3 Direction = LightPosition - FragIn_CurrentPosition;

	vec3 LightDirection = normalize(vec3(1.0f, 1.0f, 0));
	vec3 ViewDirection = normalize(CameraPosition - FragIn_CurrentPosition);
	vec3 Reflection = reflect(-LightDirection, VertexNormal_Normalized);

	float Specular = pow(max(dot(ViewDirection, Reflection), 0.0f), 16.0f) * MAX_SPECULAR_LIGHT;

	float Diffuse = max(dot(VertexNormal_Normalized, LightDirection), 0.0f);
	
	float Multiplier = 1.0f;

	if (HasDiffuse == 0) {
		FragColor = vec4(FragIn_VertexColor, 1.0f) * vec4(LightColor, 1.0f) * (Diffuse * Multiplier + LIGHT_AMBIENT) + (Specular * Multiplier);
	}
	else {
		if (HasSpecular == 1) {
			float SpecularMultiplier = texture(Specular0, FragIn_UV).r;
			
			FragColor = texture(Diffuse0, FragIn_UV) * vec4(LightColor, 1.0f) * (Diffuse * Multiplier + LIGHT_AMBIENT) + (SpecularMultiplier * Specular * Multiplier);
		}
		else {
			FragColor = texture(Diffuse0, FragIn_UV) * vec4(LightColor, 1.0f) * (Diffuse * Multiplier + LIGHT_AMBIENT) + (Specular * Multiplier);
		}
	}

	//FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
