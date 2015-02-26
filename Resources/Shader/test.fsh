varying vec2        v_texCoord;
uniform sampler2D   u_texture;
uniform vec2        u_texSize;
uniform int         u_mosaicLevel;
 
void main() {
    vec4 color;
    if(u_mosaicLevel > 1){
            vec2 target;
            target.x = float(int(v_texCoord.x / float(u_mosaicLevel) * u_texSize.x + 0.5)) * float(u_mosaicLevel) / u_texSize.x;
            target.y = float(int(v_texCoord.y / float(u_mosaicLevel) * u_texSize.y + 0.5)) * float(u_mosaicLevel) / u_texSize.y;
        color = texture2D(u_texture, target);
        }else{
            color = texture2D(u_texture, v_texCoord);
    }
        gl_FragColor = color;
}