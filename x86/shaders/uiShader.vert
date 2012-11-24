attribute vec4 a_position;
attribute vec2 a_texture;

uniform vec2 u_resolution;

varying vec2 o_texture;

void main() {
	vec2 pixel_coords = a_position.xy / u_resolution * 2.0;
	pixel_coords.y = 1.0 - pixel_coords.y;
	pixel_coords.x -= 1.0;

	gl_Position = vec4(pixel_coords.xy, 0.0, 1.0);
	o_texture = a_texture;
}

