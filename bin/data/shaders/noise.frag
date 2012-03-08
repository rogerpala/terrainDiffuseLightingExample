varying float intensity;

void main()
{
	vec4 color = vec4(0.0,1.0* intensity,1.0* intensity,1.0);
	/*if (intensity > 0.95)
		color = vec4(0.1,0.1,0.1,1.0);
	else if (intensity > 0.90)
		color = vec4(0.2,0.2,0.2,1.0);
	else if (intensity > 0.85)
		color = vec4(0.3,0.3,0.3,1.0);
	else if (intensity > 0.80)
		color = vec4(0.4,0.4,0.4,1.0);
	else if (intensity > 0.75)
		color = vec4(0.5,0.5,0.5,1.0);
	else if (intensity > 0.70)
		color = vec4(0.6,0.6,0.6,1.0);
	else if (intensity > 0.65)
		color = vec4(0.7,0.7,0.7,1.0);
	else if (intensity > 0.60)
		color = vec4(0.8,0.8,0.8,1.0);
	else if (intensity > 0.55)
		color = vec4(0.9,0.9,0.9,1.0);
	else if (intensity > 0.50)
		color = vec4(1.0,1.0,1.0,1.0);
	else if (intensity > 0.45)
		color = vec4(0.1,0.0,0.0,1.0);
	else if (intensity > 0.40)
		color = vec4(0.2,0.0,0.0,1.0);
	else if (intensity > 0.35)
		color = vec4(0.3,0.0,0.0,1.0);
	else if (intensity > 0.30)
		color = vec4(0.4,0.0,0.0,1.0);
	else if (intensity > 0.25)
		color = vec4(0.5,0.0,0.0,1.0);
	else if (intensity > 0.20)
		color = vec4(0.6,0.0,0.0,1.0);
	else if (intensity > 0.15)
		color = vec4(0.7,0.0,0.0,1.0);
	else if (intensity > 0.10)
		color = vec4(0.8,0.0,0.0,1.0);
	else if (intensity > 0.05)
		color = vec4(0.9,0.0,0.0,1.0);
	else
		color = vec4(1.0,0.0,0.0,1.0);*/
	gl_FragColor = color;
	gl_FragColor = gl_Color; ;
	

}
