uniform sampler2D texture;

uniform float progress;

void main()
{
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    gl_FragColor = vec4(pixel.xyz, progress * pixel.w);
}