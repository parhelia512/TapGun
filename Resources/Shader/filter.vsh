#ifdef GL_ES
	precision highp float;
#else
	#version 120
#endif

uniform mat4 matProjection;
	
attribute vec4 vPos;
attribute vec2 vTex;

varying vec2 outTex;
			
void main(){
	gl_Position = matProjection * vPos;
	outTex = vTex;
}
