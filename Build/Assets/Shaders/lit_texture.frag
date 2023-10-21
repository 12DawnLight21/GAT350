#version 430
//location must = location in the .vert
in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
//in layout(location = 2) vec2 ftexcoord; 
//in layout(location = 3) vec4 fcolor; //flat in layout - doesnt interpolate values per vertex OLD SCHOOL LIGHTING

out layout(location = 0) vec4 ocolor;
 
layout(binding = 0) uniform sampler2D tex;

uniform vec3 lightPos;
uniform vec3 ambientLight;

uniform struct Material
{
	vec3 diffuse;
	vec3 specular;
	float shininess;
 
	vec2 offset;
	vec2 tiling;
} material;
 
uniform struct Light
{
	vec3 position;
	vec3 color;
} light;
 
 
vec3 ads(in vec3 position, in vec3 normal)
{
	// AMBIENT
	vec3 ambient = ambientLight;
 
	// DIFFUSE
	vec3 lightDir = normalize(light.position - position);
	float intensity = max(dot(lightDir, normal), 0);
	vec3 diffuse = material.diffuse * (light.color * intensity);
 
	// SPECULAR
	vec3 specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-lightDir, normal);
		vec3 viewDir = normalize(-position);
		intensity = max(dot(reflection, viewDir), 0);
		intensity = pow(intensity, material.shininess);
		specular = material.specular * intensity;
	}
 
	return ambient + diffuse + specular;
}


void main() 
{
	ocolor = vec4(ads(fposition, fnormal), 1);
}	