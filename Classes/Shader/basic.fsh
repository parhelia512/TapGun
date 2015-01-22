precision highp float;

uniform sampler2D texDecale;

varying vec2 outTex;
varying vec4 outColor;

void main(){
	vec4 color = texture2D( texDecale, outTex ) * outColor;
	gl_FragColor = color;
}
