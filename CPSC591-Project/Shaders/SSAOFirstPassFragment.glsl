#version 410 core

layout (location = 0) out vec4 position;
layout (location = 1) out vec3 normal;
layout (location = 2) out vec4 color;
layout (location = 3) out vec4 specular;

in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec4 C;
    vec2 uv;
	vec3 positionCameraSpace;
} fs_in;

uniform vec3 specular_color = vec3(0.7);
uniform float specular_power = 128.0;

// Texture Mapping
uniform sampler2D TextureUniform;
uniform bool TextureValid;

const float NEAR = 1.f; // Projection matrix's near plane distance
const float FAR = 50000.f; // Projection matrix's far plane distance
float linearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));	
}

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

	//store variables to our textures
	position.xyz = fs_in.positionCameraSpace;
	//get the alpha for position
	position.a = linearizeDepth(gl_FragCoord.z);

	normal = N;

    // Calculate R locally
    vec3 R = reflect(-L, N);

    vec3 diffuse = max(dot(N, L), 0.3) * vec3(fs_in.C);
	float alpha;
	if (TextureValid) {
		vec4 texColor = texture(TextureUniform, fs_in.uv);
		diffuse *= vec3(texColor);
		color = vec4(diffuse, texColor.a);
		alpha = texColor.a;
	} else {
		color = vec4(diffuse, fs_in.C.a);
		alpha = fs_in.C.a;
	}

    vec3 spec = pow(max(dot(R, V), 0.0), specular_power) * specular_color;
	specular = vec4(spec, alpha);
}