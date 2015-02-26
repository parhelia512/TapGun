uniform mat4 matWorld;
uniform mat4 matView;
uniform mat4 matProjection;
	
attribute vec4 vPos;
attribute vec3 vNormal;
attribute vec2 vTex;
attribute vec4 vColor;

varying vec2 outTex;
varying vec4 outColor;
varying vec4 outNormal; // �@�����s�N�Z���Ɏ����Ă���
			
void main(){
	gl_Position = matProjection *
	                  matView * matWorld * vPos;
	
	//	��ʏ�ł̖@��
	vec4 N = vec4( vNormal, 0 );
	outNormal = matView * matWorld * N;

	
	
	outTex   = vTex;

	vec4 color = vec4(1,1,1,1);

	vec3 light = vec3( 1, -1, 0 ); //	���C�g�̕���
	vec3 normal = vNormal; //	�_�̌���

	//	�x�N�g���̐��K���i�������P�ɂ���j
	light = normalize(light);
	normal = normalize(normal);
	//	����de���C�g
	color.rgb = dot(normal, -light);
	color.rgb = max( color.rgb, 0 );//�O�Ŏ~�߂�

	//	�󂩂�̌�
	vec3 sky = vec3( 0.6, 0.8, 1.0 );
	color.rgb += (normal.y+1)/2 * sky;
	
	//	������y�̌�
	vec3 gr = vec3( 0.3, 0.2, 0 );
	color.rgb += (-normal.y+1)/2 * gr;
	
	//	�����i�@���j��Z���������قǃt�`�i���_�Łj
	//float rim = 1.0 - abs(normal.z); // abs=��Βl
	//color.rgb += rim;	// �t�`�قǔ�
		
	outColor = vColor * color;
}