uniform sampler2D rectTexture;
uniform float shadParam;

void main()
{


	vec3 color = texture2D(rectTexture, gl_TexCoord[0].st).rgb;

	float c=(color.r+color.g+color.b)/3;

	gl_FragColor = vec4(c,c,c,1);
}