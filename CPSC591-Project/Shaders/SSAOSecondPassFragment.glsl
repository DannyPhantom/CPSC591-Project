#version 410 core

in vec2 texCoords;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D noiseTexture;

uniform vec3 samples[64];

// parameters
int kernelSize = 64;
float radius = 15.0;

// tile noise texture over screen based on screen dimensions divided by noise size
const vec2 noiseScale = vec2(1500.0f/4.0f, 900.0f/4.0f); 

uniform mat4 ProjectionMatrix;

void main()
{
    // Get input for SSAO algorithm
    vec3 position = texture(positionTexture, texCoords).xyz;
    vec3 normal = texture(normalTexture, texCoords).rgb;
    vec3 noiseVector = texture(noiseTexture, texCoords * noiseScale).xyz;

    // Create TBN change-of-basis matrix: from tangent-space to view-space
    vec3 tangent = normalize(noiseVector - normal * dot(noiseVector, normal));
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, normal, bitangent);

    // Iterate over the sample kernel and calculate occlusion factor
    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; i++)
    {
        // get sample position
        vec3 sampleVec = TBN * samples[i]; // From tangent to view-space
        sampleVec = position + sampleVec * radius + 0.1f * normal; 
        
        // project sample position (to sample texture) (to get position on screen/texture)
        vec4 offset = vec4(sampleVec, 1.0);
        offset = ProjectionMatrix * offset; // from view to clip-space
        offset.xyz /= offset.w; // perspective divide
        offset.xyz = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0
        
        // get sample depth
        float sampleDepth = -texture(positionTexture, offset.xy).w; // Get depth value of kernel sample
        
		if (sampleDepth > -2500) {
			// range check & accumulate
			float rangeCheck = smoothstep(0.0, 1.0, radius / abs(position.z - sampleDepth ));
			occlusion += (sampleDepth >= sampleVec.z ? 1.0 : 0.0) * rangeCheck;   
		}        
    }
    occlusion = 1 - (occlusion / kernelSize);
  
    gl_FragColor = vec4(occlusion, occlusion, occlusion, 1);
}

