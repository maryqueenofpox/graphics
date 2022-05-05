#version 330 core

uniform vec3 lightColour;
uniform vec3 objectColour;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 fragmentColour;

in vec3 Position;
in vec3 fragmentPosition;

void main()
{ 
     float ambientStrength = 0.1;
     vec3 ambient = ambientStrength * lightColour;

     vec3 norm = normalize(Position);
     vec3 lightDirection = normalize(lightPosition - fragmentPosition);
     float diff = max(dot(norm, lightDirection), 0.2);
     vec3 diffuse = diff * lightColour;

     float specularStrength = 0.5;
     vec3 viewDirection = normalize(viewPosition - fragmentPosition);
     vec3 reflectDirection = reflect(-lightDirection, norm);
     float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
     vec3 specular = specularStrength * spec * lightColour;

     vec3 result = (ambient + diffuse + specular) * objectColour;
     fragmentColour = vec4(result, 1.0);
}
