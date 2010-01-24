uniform sampler2D rectTexture;
uniform float shadParam;

void main()
{
	gl_FragColor=texture2D(rectTexture,gl_TexCoord[0].st);
}