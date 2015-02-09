uniform mat4 matWorld;
uniform mat4 matView;
uniform mat4 matProjection;
	
attribute vec4 vPos;
attribute vec3 vNormal;
attribute vec2 vTex;
attribute vec4 vColor;

varying vec2 outTex;
varying vec4 outColor;
varying vec4 outNormal; // 法線をピクセルに持っていく
			
void main(){
	gl_Position = matProjection *
	                  matView * matWorld * vPos;
	
	//	画面上での法線
	vec4 N = vec4( vNormal, 0 );
	outNormal = matView * matWorld * N;

	
	
	outTex   = vTex;

	vec4 color = vec4(1,1,1,1);

	vec3 light = vec3( 1, -1, 0 ); //	ライトの方向
	vec3 normal = vNormal; //	点の向き

	//	ベクトルの正規化（長さを１にする）
	light = normalize(light);
	normal = normalize(normal);
	//	内積deライト
	color.rgb = dot(normal, -light);
	color.rgb = max( color.rgb, 0 );//０で止める

	//	空からの光
	vec3 sky = vec3( 0.6, 0.8, 1.0 );
	color.rgb += (normal.y+1)/2 * sky;
	
	//	下から土の光
	vec3 gr = vec3( 0.3, 0.2, 0 );
	color.rgb += (-normal.y+1)/2 * gr;
	
	//	向き（法線）のZが小さいほどフチ（頂点版）
	//float rim = 1.0 - abs(normal.z); // abs=絶対値
	//color.rgb += rim;	// フチほど白
		
	outColor = vColor * color;
}