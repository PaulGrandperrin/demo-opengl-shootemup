varying vec3 normal, lightVec, eyeVec;

uniform sampler2D tex;

void main(void)
{
	normal=normalize(normal);
	eyeVec=normalize(eyeVec); //TODO a virer
	lightVec=normalize(lightVec);
	
	vec4 color=texture2D(tex,gl_TexCoord[0].st);

	
	vec4 al=gl_LightSource[0].ambient;
	vec4 dl= gl_LightSource[0].diffuse*max(dot(lightVec,normal),0.0);
	vec4 sl= gl_LightSource[0].specular*pow(max(dot(-normalize(eyeVec),reflect(lightVec,normal)),0.0),16)*2;

    gl_FragColor=color*(al+dl+sl)*4;

}