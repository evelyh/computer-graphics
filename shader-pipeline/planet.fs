// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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

  float strength = 2; //noise strength
  float fq1 = 8; //noise frequency
  float fq2 = 2; 
  float noise = sin(fq1 * (sphere_fs_in.z + improved_perlin_noise(fq2 * sphere_fs_in))) / strength / 2;

  float p;
  vec3 ka, kd, ks;
  if (is_moon) {
    p = 200;
    ka = vec3(0.1);
    kd = vec3(0.5);
    ks = vec3(1);
  } else if (bump_height(is_moon, sphere_fs_in) < 0.005){
    p = 1000;
    ka = vec3(0.08, 0.08, 0.24);
    kd = mix(vec3(0.2, 0.2, 0.8), vec3(3), noise);
    ks = vec3(1);
  } else {
    p = 1000;
    ka = vec3(0.08, 0.24, 0.16);
    kd = mix(vec3(0.2, 0.2, 0.8), vec3(3), noise);
    ks = vec3(1);
  }

  color = blinn_phong(ka, kd, ks, p, n, v, l);
}
