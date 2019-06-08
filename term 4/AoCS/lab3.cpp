#include <cstdio>
#include <iostream>
#include <stdexcept>
#include "xmmintrin.h"

float * solve_quadratic_equation(const float &a, const float &b, const float &c){
    
    if (!a) throw std::invalid_argument("A should not be zero.");

    __m128 vec = _mm_mul_ps(_mm_set_ps(b, a, a, a), _mm_set_ps(b, -4 * c, 2, -2));

    float roots[4];
    _mm_storer_ps(roots, vec);

    vec = _mm_add_ss(_mm_set_ss(roots[0]), _mm_set_ss(roots[1]));

    float sqrt_d;
    _mm_store_ss(&sqrt_d, _mm_sqrt_ss(vec));
    
    if (sqrt_d < 0) throw std::runtime_error("There are no roots: D < 0.");
    
    vec = _mm_div_ps(_mm_set_ps(b, sqrt_d, sqrt_d, 0), _mm_set_ps(roots[3], roots[3], roots[2], roots[2]));

    _mm_storer_ps(roots, vec);
    _mm_storer_ps(roots, _mm_add_ps(_mm_set_ps(roots[0], roots[0], 0, 0), _mm_set_ps(roots[1], roots[2], 0, 0)));
    
    return new float[2] {roots[0], roots[1]};
}

int main(){
    
    float a, b, c;
    scanf("%f%f%f", &a, &b, &c);
    
    float *ans = solve_quadratic_equation(a, b, c);

    printf("x1 = %f, x2 = %f\n", ans[0], ans[1]);

    return 0;
}

