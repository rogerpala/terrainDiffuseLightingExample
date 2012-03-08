#version 120

uniform float timeValX = 1.0;
uniform float timeValY = 1.0;
uniform vec2 mouse;
varying vec3 normal;
varying vec3 vertex_to_light_vector;

uniform vec3 lightDirection;
uniform vec3 viewPosition;
uniform vec4 lightAmbientColor;
uniform vec4 lightDiffuseColor;
uniform vec4 lightSpecularColor;


uniform vec4 materialAmbientColor;
uniform vec4 materialDiffuseColor;
uniform vec4 materialSpecularColor;
uniform float shininess;

varying float intensity;

varying vec3 vNormal;
varying vec3 vVertex;

void main()
{
	/*vec3 normal, lightDir, viewVector, halfVector;
	vec3 lightHalfPlane;
	vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
	float NdotL,NdotHV;
	
	// first transform the normal into eye space and normalize the result 
	normal = normalize(gl_NormalMatrix * gl_Normal);
	
	// now normalize the light's direction. Note that according to the OpenGL specification, the light is stored in eye space. Also since we're talking about a directional light, the position field is actually direction 
	lightDir = normalize(vec3(lightDirection));
	
	lightHalfPlane = normalize(lightDirection + viewPosition); 
	
	// compute the cos of the angle between the normal and lights direction. The light is directional so the direction is constant for every vertex.Since these two are normalized the cosine is the dot product. We also need to clamp the result to the [0,1] range. 
	
	NdotL = max(dot(normal, lightDir), 0.0);
	
	// Compute the diffuse, ambient and globalAmbient terms 
	diffuse = materialDiffuseColor * lightDiffuseColor;
	ambient = materialAmbientColor * lightAmbientColor;
	//globalAmbient = gl_LightModel.ambient * materialAmbientColor;
	
	// compute the specular term if NdotL is  larger than zero 
	if (NdotL > 0.0) {

		NdotHV = max(dot(normal, lightHalfPlane),0.0);
		specular = materialSpecularColor * lightSpecularColor * pow(NdotHV, shininess);
	}
	
	gl_FrontColor = NdotL * diffuse + ambient + specular;
	//gl_FrontColor = globalAmbient + NdotL * diffuse + ambient + specular;
	
	gl_Position = ftransform();*/
	
	
	/*float ndotl, ndoth;
	vec3 lightHalfPlane = normalize(viewPosition + lightDirection); 
	vec4 computedColor = vec4(0.0, 0.0, 0.0, 1.0);
	
	ndotl = max(0.0, dot(normal, lightDirection));
	ndoth = max(0.0, dot(normal, lightHalfPlane));
	
	computedColor += (lightAmbientColor * materialAmbientColor);
	//computedColor += (ndotl * lightDiffuseColor * materialDiffuseColor);
	
	if(ndoth > 0.0){
		computedColor += (pow(ndoth, shininess) * materialSpecularColor * lightSpecularColor);
	}
	
	gl_FrontColor = computedColor;
	gl_Position = ftransform();*/
	
	//vec4 col = gl_Color;
	
	vec4 col = vec4(0.0,1.0,1.0,1.0);
	
	intensity = dot(normalize(lightDirection),gl_Normal);
	vec4 intColor = vec4(0.0,1.0* intensity,1.0* intensity,1.0);
	
	gl_FrontColor =  col + intColor;
	gl_Position = ftransform();
} 

