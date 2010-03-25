#ifdef CPU
#include "emulate.cpp"
#else
uniform vec3 C;
varying vec3 D;
#endif

#include "geom.h"
#define surface(T) XYZ(torus,T)

void main() {
    // this interval is pretty much good enough!
    float t_low = 0.0;
    float t_high = 0.01;
    
    float xn_a = t_high;
    float xn_b = t_low;
    
    // use the secant method on this interval
    //const float epsilon = 0.00027; // sphere
    //const float epsilon = 0.003; // hyperboloid1
    //const float epsilon = 0.008; // hyperboloid2
    const float epsilon = 0.001;
    float d;
    for (int i = 0; i < 15; i++) {
        float f_a = surface(xn_a);
        float f_b = surface(xn_b);
        d = (xn_a - xn_b) / (f_a - f_b) * f_a;
        if (abs(f_a-f_b) < epsilon) break; // found an acceptable root
        xn_b = xn_a;
        xn_a -= d;
    }
    
    if (d != d) { // NaN
        gl_FragColor = vec4(1.0,1.0,0.0,0.0);
    }
    else if (abs(d) > epsilon) {
        gl_FragColor = vec4(0.0,1.0,0.0,1.0);
    }
    else {
        vec3 point = C + t_high * D; // point of intersection
        gl_FragColor = vec4(point.x,0.0,point.z,1.0);
    }
}
