precision highp float;

uniform sampler2D texDecale;

varying vec2 outTex;
varying vec4 outColor;

varying float atari;	//当たり具合受け渡し用

void main(){
	//	テクスチャからピクセル
	vec4 t = texture2D( texDecale, outTex );
	//	当たり具合に応じて影
	if( atari < 0.4 ) t.rgb *= 0.3;

	gl_FragColor = t;
}    

