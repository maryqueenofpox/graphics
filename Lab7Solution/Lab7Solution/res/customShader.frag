#version 330 core

uniform vec3 lightPosition;
uniform vec3 viewPosition;

float specularStrength = 0.5; //Strength of specular light

in vec3 fragPosition; //from customShader.vert
in vec4 normal; //from customShader.vert

uniform sampler2D texture; //texture of model
varying vec2 texCoord0;

out vec4 fragColor; //final colour of object

void main()
{ 

     vec3 lightDirection = normalize(lightPosition - fragPosition); //light direction from source to model
     vec3 normPos = normalize(fragPosition); //normal position of fragments

     /*
     Calculation for the diffuse lighting along the model
     */
     float diffuseAmount = max(dot(normPos, lightDirection), 0.2);
     vec3 diffuseLight = diffuseAmount * vec3(1.0, 1.0, 1.0);

     /*
     Setting the value for ambient lighting along the model
     */
     vec3 ambientLight = vec3(0.1, 0.1, 0.1);

     /*
     Calculating light intensity for toon-shading effect allowing for pop-in of texture colour
     */
     float lightIntensity;
	 vec4 objectColour;
     lightIntensity = dot(lightDirection, normPos);

	if (lightIntensity > 0.4)
		objectColour = vec4(1.0,1.0,0.1,1.0);
	else
		objectColour = vec4(0.5,0.2,0.0,1.0);

     /*
     Calculation for the specular light on the model
     */
     vec3 viewDirection = normalize(viewPosition - fragPosition);
     vec3 reflectDirection = reflect(lightDirection, normPos);
     float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), 2);

     vec3 specularLight = specularStrength * specularAmount * vec3(1.0, 1.0, 1.0);

     /*
     Calculation for the final ADS effect
     */
     vec3 combinedLight = (diffuseLight + ambientLight + specularLight);

     /*
     Final colour, multiplying toon-shading effect with ADS lighting effect, and the object's texture
     */
     fragColor = objectColour * (vec4(combinedLight, 1.0)) * texture2D(texture, texCoord0);   
}
