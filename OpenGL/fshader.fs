#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D textureA;
uniform sampler2D textureB;

uniform int orientation;

void main()
{
    switch(orientation)
    {
        case 1:
            if (TexCoord.y > 0.5) // Upper half
            {
                FragColor = texture(textureA, vec2(TexCoord.x, TexCoord.y * 2.0 - 1.0));
            }
            else // Lower half
            {
                FragColor = texture(textureB, vec2(TexCoord.x, TexCoord.y * 2.0));
            }
            break;
        case 2:
            if (TexCoord.x > 0.5) // Upper half
            {
                FragColor = texture(textureA, vec2(TexCoord.x * 2.0 - 1.0, TexCoord.y));
            }
            else // Lower half
            {
                FragColor = texture(textureB, vec2(TexCoord.x * 2.0, TexCoord.y));
            }
            break;
        case 3:
            if (TexCoord.y > 0.5) // Upper half
            {
                FragColor = texture(textureB, vec2(TexCoord.x, TexCoord.y * 2.0 - 1.0));
            }
            else // Lower half
            {
                FragColor = texture(textureA, vec2(TexCoord.x, TexCoord.y * 2.0));
            }
            break;
        case 4:
            if (TexCoord.x > 0.5) // Upper half
            {
                FragColor = texture(textureB, vec2(TexCoord.x * 2.0 - 1.0, TexCoord.y));
            }
            else // Lower half
            {
                FragColor = texture(textureA, vec2(TexCoord.x * 2.0, TexCoord.y));
            }
            break;
    }
}