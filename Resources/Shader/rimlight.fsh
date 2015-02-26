precision highp float;

uniform sampler2D texDecale;

varying vec2 outTex;
varying vec4 outColor;
varying vec4 outNormal; // 頂点シェーダーから法線

void main(){
	vec4 color = texture2D( texDecale, outTex ) * outColor;
	//	法線正規化（長さ１）
	vec4 normal = normalize(outNormal);
	//	向き（法線）のZが小さいほどフチ
	float rim = 1.0 - abs(normal.z); // abs=絶対値
	color.rgb += rim * vec3(1,0,0 );	// フチほど白

	gl_FragColor = color;
}    

