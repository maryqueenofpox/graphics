#version 330 core

uniform vec3 lightPosition;
uniform vec3 lightColour;
uniform vec3 viewPosition;

float specularStrength = 0.5;
float ambientStrength = 0.1;

in vec3 Position;
in vec3 fragPosition;
in vec4 normal;

uniform sampler2D texture;
varying vec2 texCoord0;

out vec4 fragColor;

void main()
{ 

     float lightIntensity;
	 vec4 color;

     vec3 normPos = normalize(Position);
     vec3 lightDirection = normalize(lightPosition - fragPosition);
     float diff = max(dot(normPos, lightDirection), 0.2);


     vec3 diffuseLight = lightColour * diff;
     vec3 ambientLight = lightColour * ambientStrength;

     lightIntensity = dot(lightDirection, normPos);

	if (lightIntensity > 0.4)
		color = vec4(1.0,1.0,0.1,1.0);
	else
		color = vec4(0.5,0.2,0.0,1.0);

     vec3 viewDirection = normalize(viewPosition - fragPosition);
     vec3 reflectDirection = reflect(lightDirection, normPos);
     float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 2);

     vec3 specularLight = specularStrength * spec * lightColour;

     vec3 result = (diffuseLight + ambientLight + specularLight);
     fragColor = (vec4(result, 1.0)) * color * texture2D(texture, texCoord0);   
}
