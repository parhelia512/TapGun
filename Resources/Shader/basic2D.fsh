#ifdef GL_ES
	precision highp float;
#else
	#version 120
#endif

uniform sampler2D texDecale;

varying vec2 outTex;
varying vec4 outColor;

void main(){
	gl_FragColor = texture2D( texDecale, outTex );// * outColor;
}    

