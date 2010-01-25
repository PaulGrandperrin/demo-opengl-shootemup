uniform sampler2D rectTexture;
uniform float shadParam;
#extension GL_EXT_gpu_shader4 : enable
void main()
{


	vec3 color = texture2D(rectTexture, gl_TexCoord[0].st).rgb;

	if(color.r<0.25&& color.r>0.0)
		color.r=0.125;
	else if(color.r<0.5)
		color.r=0.375;
	else if(color.r<0.75)
		color.r=0.625;
	else if (color.r>=1.0)
		color.r=0.875;

	if(color.g<0.25&& color.g>0.0)
		color.g=0.125;
	else if(color.g<0.5)
		color.g=0.375;
	else if(color.g<0.75)
		color.g=0.625;
	else if (color.g>=1.0)
		color.g=0.875;

	if(color.b<0.25&& color.b>0.0)
		color.b=0.125;
	else if(color.b<0.5)
		color.b=0.375;
	else if(color.b<0.75)
		color.b=0.625;
	else if (color.b>=1.0)
		color.b=0.875;

	
	gl_FragColor = vec4(color,1);
}