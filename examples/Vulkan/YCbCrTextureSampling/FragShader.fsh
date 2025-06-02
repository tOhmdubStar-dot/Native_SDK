#version 320 es

layout (binding = 0) uniform highp sampler2D sBaseTex;

layout(location = 1) in mediump vec2 TexCoord;
layout(location = 0) out highp vec4 oColor;

void main()
{
	// Read base texture and perform gamma correction (sRGB to linear)
	// Vulkan spec 1.1-1.3 only supports unsigned normalised (UNORM) YCbCr formats
	highp vec3 texColor = pow(texture(sBaseTex, TexCoord).rgb, vec3(2.2));
	oColor = vec4(texColor, 1.0);
}
