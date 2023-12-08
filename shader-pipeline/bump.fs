// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  vec3 bump = bump_position(is_moon, sphere_fs_in);
  vec3 T, B;
  tangent(sphere_fs_in, T, B);
  float epsilon = 0.0001;
  vec3 normal_bump = normalize(cross((bump_position(is_moon, sphere_fs_in + epsilon * T) - bump) / epsilon, 
                          (bump_position(is_moon, sphere_fs_in + epsilon * B) - bump) / epsilon));

  mat4 model = model(is_moon, animation_seconds / 4);
  float theta = 2 * animation_seconds * (M_PI / 4);
  vec3 n = normalize(transpose(inverse(view)) * transpose(inverse(model)) * vec4(normal_bump, 1)).xyz;
  vec3 v = - normalize(view_pos_fs_in).xyz;
  vec4 light = view * vec4(cos(theta), 2.5, 2 * sin(theta), 1);
  vec3 l = normalize(light - view_pos_fs_in).xyz;

  float p;
  vec3 ka, kd, ks;
  if (is_moon) {
    p = 200;
    ka = vec3(0.1);
    kd = vec3(0.5);
    ks = vec3(1);
  } else {
    p = 1000;
    ka = vec3(0.08, 0.08, 0.24);
    kd = vec3(0.2, 0.2, 0.8);
    ks = vec3(1);
  }

  color = blinn_phong(ka, kd, ks, p, n, v, l);
}
