uniform sampler2D rectTexture;
uniform float shadParam;

void main()
{
	vec3 color=vec3(0,0,0);;
	for( float x=-5;x<=5;x+=2)
	{
		for(float y=-5;y<=5;y+=2)
		{
			//float coef=exp(-x*x)*exp(-y*y);
			color += 0.04*texture2D(rectTexture, vec2(gl_TexCoord[0].s+x/400, gl_TexCoord[0].t+y/400)).rgb;
		}
	}

	gl_FragColor = vec4(color,1);
}