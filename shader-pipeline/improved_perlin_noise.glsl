// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  vec3 i = floor(st);
  vec3 f = fract(st);

  vec3 i1, i2, i3, i4, i5, i6, i7, i8, f1, f2, f3, f4, f5, f6, f7, f8;

  i1 = random_direction(i);
  i2 = random_direction(vec3(1 + i.x, i.y, i.z));
  i3 = random_direction(vec3(i.x, 1 + i.y, i.z));
  i4 = random_direction(vec3(1 + i.x, 1 + i.y, i.z));
  i5 = random_direction(vec3(i.x, i.y, 1 + i.z));
  i6 = random_direction(vec3(1 + i.x, i.y, 1 + i.z));
  i7 = random_direction(vec3(i.x, 1 + i.y, 1 + i.z));
  i8 = random_direction(vec3(1 + i.x, 1 + i.y, 1 + i.z));

  f1 = f;
  f2 = vec3(f.x - 1, f.y, f.z);
  f3 = vec3(f.x, f.y - 1, f.z);
  f4 = vec3(f.x - 1, f.y - 1, f.z);
  f5 = vec3(f.x, f.y, f.z - 1);
  f6 = vec3(f.x - 1, f.y, f.z - 1);
  f7 = vec3(f.x, f.y - 1, f.z - 1);
  f8 = f - vec3(1);

  vec3 smoothed = improved_smooth_step(f);
  float x1, x2, x3, x4, y1, y2;
  // x noises
  x1 = mix(dot(i1, f1), dot(i2, f2), smoothed.x);
  x2 = mix(dot(i3, f3), dot(i4, f4), smoothed.x);
  x3 = mix(dot(i5, f5), dot(i6, f6), smoothed.x);
  x4 = mix(dot(i7, f7), dot(i8, f8), smoothed.x);

  //y noises
  y1 = mix(x1, x2, smoothed.y);
  y2 = mix(x3, x4, smoothed.y);

  //z noises
  return mix(y1, y2, smoothed.z);
}

