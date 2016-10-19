#version 330 core

//layout(location = 0) out float fragmentdepth;


out vec4 color;
in vec2 UV;

uniform sampler2D depthMap;

void main()
{

     ///gl_FragDepth = gl_FragCoord.z;
        float depthValue = texture(depthMap, UV).r;
        color = vec4(vec3(depthValue), 1.0);
    //        fragmentdepth = gl_FragCoord.z;

}