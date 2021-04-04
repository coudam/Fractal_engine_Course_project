#version 430 core

uniform int power = 2; 
uniform int depth = 100;
uniform float m = 2.;
uniform float zoom = 5.0;
uniform vec2 tr;

in vec2 pos;
out vec4 FragColor;

vec2 complex_mul(vec2 z1, vec2 z2) {
    return vec2(z1.x*z2.x - z1.y*z2.y, z1.x*z2.y + z1.y*z2.x);
}

float complex_mod(vec2 z) {
    return sqrt(pow(z.x, 2) + pow(z.y, 2));
}

float mod(float a, float b) {
    return a - (b * floor(a/b));
}

void main(){
    vec2 p = vec2(((gl_FragCoord.x/1300.0 - 0.5) * 5.) * zoom, ((gl_FragCoord.y/1000.0 - 0.5 )* 5.) * zoom) + tr;
    vec2 z = vec2(0., 0.);
    FragColor = vec4(1);
    for (float i = 0; i < depth; ++i) {
        z = vec2 (pow(z.x,2) - pow(z.y,2) + p.x, 2*z.x*z.y + p.y);
        if (complex_mod(z) > m) {
            FragColor = vec4(0.,  mod(i, 255.)/(255), 0., 1.);
            break;
        }
    }    
}