#version 120

varying vec3 normal;
varying vec3 vertex_to_light_vector;
uniform int applyLighting;

void main(){
	//this is the fragment shader
	//this is where the pixel level drawing happens
	//gl_FragCoord gives us the x and y of the current pixel its drawing
	
	//we grab the x and y and store them in an int
	//int xVal = int(gl_FragCoord.x);
	//int yVal = int(gl_FragCoord.y);
	
	//we use the mod function to only draw pixels if they are every 2 in x or every 4 in y
	//if( mod(xVal, 2) == 0 && mod(yVal, 4) == 0 ){
	
	if (applyLighting == 1) {
		// Defining The Material Colors
		vec4 AmbientColor = vec4(0.0, 0.0, 1.0, 1.0);
		const vec4 DiffuseColor = vec4(1.0, 0.0, 0.0, 1.0);
	 
		// Scaling The Input Vector To Length 1
		vec3 normalized_normal = normalize(normal);
		vec3 normalized_vertex_to_light_vector = normalize(vertex_to_light_vector);
	 
		// Calculating The Diffuse Term And Clamping It To [0;1]
		float DiffuseTerm = clamp(dot(normalized_normal, normalized_vertex_to_light_vector), 0.0, 1.0);
	 
		// Calculating The Final Color
		gl_FragColor = AmbientColor + DiffuseColor * DiffuseTerm;
	}else {
		gl_FragColor = gl_Color;
	}

	
	
	
	
	
	
		//gl_FragColor = gl_Color;    
    //}
	
}