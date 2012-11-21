uniform sampler2D u_texture;

uniform vec4 color;
varying vec2 o_texture;

uniform int use_color;

void main() {
	
	if (use_color == 1)
	{
		gl_FragColor = vec4(color);
	} else {
		gl_FragColor = vec4(texture2D(u_texture, o_texture).rgb, 1.0f);
	}
}