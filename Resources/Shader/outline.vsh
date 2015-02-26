uniform mat4 matWorld;
uniform mat4 matView;
uniform mat4 matProjection;
	
attribute vec4 vPos;
attribute vec3 vNormal;
attribute vec2 vTex;
attribute vec4 vColor;

varying vec2 outTex;
varying vec4 outColor;
			
void main()
{
	vec3 N = normalize(vNormal); // –@ü(=ˆÚ“®•ûŒü)
	vec4 V = vec4( vPos.xyz + N * 1.0, 1 );	//	–@ü•ûŒü‚ÉˆÚ“®

	gl_Position = matProjection * matView * matWorld * V;
	
	outColor = vec4(0,0,0,1);	//	•s“§–¾‚Ì•
}

