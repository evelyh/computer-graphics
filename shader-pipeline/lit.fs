// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{

  float theta = 2 * animation_seconds * (M_PI / 4);

  vec3 n = normalize(normal_fs_in);
  vec3 v = normalize(view_pos_fs_in.xyz / view_pos_fs_in.w);
  vec4 light = view * vec4(cos(theta), 2.5, 2 * sin(theta), 1);
  vec3 l = normalize(light - view_pos_fs_in).xyz;

  float p;
  vec3 ka, kd, ks;
  if (is_moon) {
    p = 200;
    ka = vec3(0.03, 0.03, 0.09);
    kd = vec3(0.5);
    ks = vec3(1);
  } else {
    p = 1000;
    ka = vec3(0.03, 0.03, 0.09);
    kd = vec3(0.2, 0.2, 0.8);
    ks = vec3(1);
  }
  color = blinn_phong(ka, kd, ks, p, n, v, l);
}
