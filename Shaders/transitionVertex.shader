varying vec4 vert_pos;

void main()
{
    gl_Position = ftransform();

    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

}
