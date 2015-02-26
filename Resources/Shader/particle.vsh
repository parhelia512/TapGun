precision highp float;

uniform mat4 matView;
uniform mat4 matProjection;
	
attribute vec4 vPos;
attribute vec2 vTex;

varying vec2 outTex;
			
void main(){
	gl_Position = matProjection * matView * vPos;
	outTex = vTex;
}
