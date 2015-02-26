precision highp float;

uniform sampler2D texDecale;

varying vec2 outTex;
varying vec4 outColor;
varying vec4 outNormal; // ���_�V�F�[�_�[����@��

void main(){
	vec4 color = texture2D( texDecale, outTex ) * outColor;
	//	�@�����K���i�����P�j
	vec4 normal = normalize(outNormal);
	//	�����i�@���j��Z���������قǃt�`
	float rim = 1.0 - abs(normal.z); // abs=��Βl
	color.rgb += rim * vec3(1,0,0 );	// �t�`�قǔ�

	gl_FragColor = color;
}    

