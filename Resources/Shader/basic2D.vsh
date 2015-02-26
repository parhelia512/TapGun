#ifdef GL_ES
	precision highp float;
#else
	#version 120
#endif

uniform mat4 matWorld;
//uniform mat4 matView;
uniform mat4 matProjection;

attribute vec4 vPos;
attribute vec2 vTex;
attribute vec4 vColor;

varying vec2 outTex;
varying vec4 outColor;

void main(){
	gl_Position = matProjection * matWorld * vPos;
	outTex   = vTex;
	outColor = vColor;
}


