#version 330 core

uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 fragmentColour;

in vec3 Position;
in vec3 fragmentPosition;

uniform sampler2D texture;
varying vec2 texCoord0;

in vec4 normal;

void main()
{ 
     float ambientStrength = 0.1;
     vec3 ambient = ambientStrength * lightColour;

     float intensity;
	 vec4 color;


     vec3 norm = normalize(Position);
     vec3 lightDirection = normalize(lightPosition - fragmentPosition);
     float diff = max(dot(norm, lightDirection), 0.2);
     vec3 diffuse = diff * lightColour;

     intensity = dot(lightDirection, norm);

	if (intensity > 0.4)
		color = vec4(1.0,1.0,0.1,1.0);
	else
		color = vec4(0.5,0.2,0.0,1.0);

     float specularStrength = 0.5;
     vec3 viewDirection = normalize(viewPosition - fragmentPosition);
     vec3 reflectDirection = reflect(lightDirection, norm);
     float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 1);
     vec3 specular = specularStrength * spec * lightColour;

     vec3 result = (ambient + diffuse + specular);
     fragmentColour = (vec4(result, 1.0)) * color * texture2D(texture, texCoord0);

   
}
