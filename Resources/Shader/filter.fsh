#ifdef GL_ES
	precision highp float;
#else
	#version 120
#endif

uniform sampler2D texDecale;
varying vec2 outTex;

uniform float contrast;
uniform float saturate;
uniform vec3 screenColor;

void main()
{
	vec4 color = texture2D( texDecale, outTex );
	//	コントラスト
	color.rgb = (color.rgb-0.5) * contrast + 0.5;

	//	彩度
	float g = (color.r + color.g + color.b) / 3.0;
	color.rgb = (color.rgb-g) * saturate + g;

	//	色調整
	color.rgb *= screenColor;
	gl_FragColor = color;
}    
