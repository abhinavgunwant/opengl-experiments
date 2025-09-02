#version 330 core

out vec4 FragColor;
in vec3 sharedColor;

uniform float opacity;
uniform vec2 resolution;
uniform float time;

vec3 palette(float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1, 1, 1);
    vec3 d = vec3(0.263, 0.416, 0.557);

    return a + b * cos(6.23318 * (c * t + d));
}

void main() {
    vec2 uv = gl_FragCoord.xy / resolution * 2 - 1;
    vec2 uv0 =  uv;
    vec3 finalColor = vec3(0, 0, 0);

    for (int i=0; i<4; ++i) {
        uv = fract(uv * 1.5) - 0.5;

        float d = length(uv) * exp(-length(uv0));

        vec3 col = palette(length(uv0) + time * 0.5);
        
        d = sin(d * 8 + time) / 8;
        d = abs(d);
        d = smoothstep(0, 0.1, d);

        d = 0.01/d;

        finalColor += col * d;
    }

    FragColor = vec4(finalColor, 1);
}

