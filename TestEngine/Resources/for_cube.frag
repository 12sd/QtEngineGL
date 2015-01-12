uniform sampler2D IdTexture;
varying vec4 TexCoord;

void main(void)
{
    gl_FragColor = texture2D(IdTexture, TexCoord.st);
}
