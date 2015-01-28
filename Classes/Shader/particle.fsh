precision highp float;

uniform sampler2D texDecale;

varying vec2 outTex;

vec4 color = vec4( 1.0, 1.0, 1.0, 1.0 );

void main(){
	gl_FragColor = texture2D( texDecale, outTex );
	gl_FragColor *= color;
}    
