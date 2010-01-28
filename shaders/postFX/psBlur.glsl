uniform sampler2D rectTexture;
uniform float shadParam;

void main()
{
	vec3 color=vec3(0,0,0);
	for( float x=-5;x<=5;x+=2)
	{
		for(float y=-5;y<=5;y+=2)
		{
   //float coef=exp(-x*x)*exp(-y*y);
			color += 0.025*texture2D(rectTexture, vec2(gl_TexCoord[0].s+x/shadParam, gl_TexCoord[0].t+y/shadParam*1.05)).rgb;
		}
	}

	gl_FragColor = vec4(color,1);
}