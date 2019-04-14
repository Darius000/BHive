#version 330 core

uniform int validTexture;
uniform sampler2D aTexture;
uniform vec4 aColor;
uniform int aBlending;

in vec2 TexCoords;

out vec4 fragcolor;  
      
void main(void)
{     

	if(validTexture == 1)
	{
		fragcolor = aColor * texture2D(aTexture, TexCoords);
		//fragcolor = vec4(1.0f, .5f, 0.0f, 1.0f);
	}		
	else
	{
		fragcolor = aColor;
	}
	
	if(aBlending == 1)
	{
		if(fragcolor.a < 0.1f)
		{
			discard;
		}
	}

}