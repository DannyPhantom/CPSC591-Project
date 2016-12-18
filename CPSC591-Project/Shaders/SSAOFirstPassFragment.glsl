#version 410 core

layout (location = 0) out vec3 normal;
layout (location = 1) out vec4 color;
layout (location = 2) out vec4 specular;

in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec4 C;
    vec2 uv;
} fs_in;

// Texture Mapping
uniform sampler2D TextureUniform;
uniform int TextureValid;

//color info
vec3 specular_color = vec3(0.7);
float specular_power = 128.0;

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

	normal = N;

    // Calculate R locally
    vec3 R = reflect(-L, N);

    vec3 diffuse = max(dot(N, L), 0.3) * vec3(fs_in.C);
	float alpha;
	vec4 textureColor = texture(TextureUniform, fs_in.uv);
	diffuse *= (1 - TextureValid) * vec3(1) + TextureValid * textureColor.rgb;
	alpha = (1 - TextureValid) * fs_in.C.a + TextureValid * textureColor.a;

    vec3 spec = pow(max(dot(R, V), 0.0), specular_power) * specular_color;
	
	color = vec4(diffuse, alpha);
	specular = vec4(spec, alpha);
}