precision highp float;

uniform sampler2D texDecale;

varying vec2 outTex;
varying vec4 outColor;

void main(){
	gl_FragColor = outColor;
}    

