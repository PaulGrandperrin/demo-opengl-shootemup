uniform sampler2D rectTexture;
uniform float shadParam;
#define ray 4.0
#define pas 2.0

void main()
{
	
	vec3 color=texture2D(rectTexture,gl_TexCoord[0].st).rgb;
	
	for( float x=-ray;x<=ray;x+=pas)
	{
		for(float y=-ray;y<=ray;y+=pas)
		{
			vec3 temp=texture2D(rectTexture, vec2(gl_TexCoord[0].s+x/400.0, gl_TexCoord[0].t+y/400.0)).rgb;
			if(temp.r >=1.0 && temp.g>=1.0 && temp.b>=1.0)
				color *= 1.5;
		}
	}

	gl_FragColor = vec4(color,1.0);
}