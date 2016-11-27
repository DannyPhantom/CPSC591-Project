#version 410 core

in vec2 texCoords;

uniform sampler2D colorTexture;
uniform sampler2D specularTexture;
uniform sampler2D ssaoTexture;

void main()
{             
    // Retrieve data from g-buffer
    vec3 diffuseColor = texture(colorTexture, texCoords).rgb;
	vec3 specColor = texture(specularTexture, texCoords).rgb;
    float ambientOcclusion = texture(ssaoTexture, texCoords).r;

    gl_FragColor = vec4(ambientOcclusion * (vec3(0.1, 0.1, 0.1) + diffuseColor + specColor), 1.0);
}