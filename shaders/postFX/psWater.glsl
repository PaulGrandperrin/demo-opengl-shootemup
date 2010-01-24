uniform sampler2D rectTexture;
uniform float shadParam;

void main()
{
	gl_FragColor=texture2D(rectTexture,
						vec2(gl_TexCoord[0].s+0.01*sin(gl_TexCoord[0].t*100+shadParam/100),
							 gl_TexCoord[0].t+0.01*cos(gl_TexCoord[0].s*100+shadParam/100)));
}