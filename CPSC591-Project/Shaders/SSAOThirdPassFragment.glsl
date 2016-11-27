#version 410 core

in vec2 texCoords;

uniform sampler2D ssaoTexture;
//size of the noise texture
uniform int blurSize;

void main() 
{
   vec2 texelSize = 1.0 / vec2(textureSize(ssaoTexture, 0));
   float result = 0.0;
   for (int x = 0; x < blurSize; x++) 
   {
      for (int y = 0; y < blurSize; y++) 
      {
         vec2 offset = (vec2(-blurSize/2.0) + vec2(x, y)) * texelSize;
         result += texture(ssaoTexture, texCoords + offset).r;
      }
   }
 
   float occlusion = result / float(blurSize * blurSize);
   gl_FragColor = vec4(occlusion, occlusion, occlusion, 1);
}