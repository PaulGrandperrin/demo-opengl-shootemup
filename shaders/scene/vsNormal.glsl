varying vec3 normal, lightVec, eyeVec;

void main(void)
{

	normal = gl_NormalMatrix * gl_Normal;

	eyeVec=-vec3(gl_ModelViewMatrix * gl_Vertex);
	
	lightVec = gl_LightSource[0].position.xyz;
	
    gl_Position = ftransform();
	
	gl_TexCoord[0]=gl_MultiTexCoord0;

}