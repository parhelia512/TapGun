precision highp float;

uniform sampler2D texDecale;

varying vec2 outTex;
varying vec4 outColor;

varying float atari;	//�������󂯓n���p

void main(){
	//	�e�N�X�`������s�N�Z��
	vec4 t = texture2D( texDecale, outTex );
	//	�������ɉ����ĉe
	if( atari < 0.4 ) t.rgb *= 0.3;

	gl_FragColor = t;
}    

