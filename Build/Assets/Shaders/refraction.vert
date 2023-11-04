#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;

out layout(location = 0) vec3 otexcoord;

uniform float ior = 1.49;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 vreflect(vec3 i, vec3 n)
{
	//reflect r = i - (n *dot(n, i)) * 2
	return i - (n * dot(n, i)) * 2;
};

void main()
{
	// transform vertex positoin/normal to world space
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	// inverse of view space >> puts it in world coords
	// last column of mat4 position
	vec3 viewPosition = inverse(view)[3].xyz; //view is essentially a double array
	vec3 viewDirection = normalize(position - viewPosition); 

	// reflect view direction about vertex normal using index of refraction
	otexcoord = refract(viewDirection, normal, 1.0 / ior);

	mat4 vp = projection * view * model;
	gl_Position = vp * vec4(vposition, 1.0);
}
