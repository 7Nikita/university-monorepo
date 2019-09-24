#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include "xmmintrin.h"

float * solve_quadratic_equation(const float &a, const float &b, const float &c){
    
    if (!a) throw std::invalid_argument("\'A\' should not be a zero.");

    __m128 vec = _mm_mul_ps(_mm_set_ps(b, a, a, a), _mm_set_ps(b, -4 * c, 2, -2));

    float roots[4];
    _mm_storer_ps(roots, vec);

    vec = _mm_add_ss(_mm_set_ss(roots[0]), _mm_set_ss(roots[1]));

    float sqrt_d;
    _mm_store_ss(&sqrt_d, _mm_sqrt_ss(vec));

    if (sqrt_d < 0 || isnan(sqrt_d)) throw std::runtime_error("There are no roots: D < 0.");
    
    vec = _mm_div_ps(_mm_set_ps(b, sqrt_d, sqrt_d, 0), _mm_set_ps(roots[3], roots[3], roots[2], roots[2]));

    _mm_storer_ps(roots, vec);
    _mm_storer_ps(roots, _mm_add_ps(_mm_set_ps(roots[0], roots[0], 0, 0), _mm_set_ps(roots[1], roots[2], 0, 0)));
    
    return new float[2] {roots[0], roots[1]};
}

int main(){

    printf("a * x^2 + b * x + c = 0\n");

    float a, b, c;

    printf("Enter \'a\': ");
    scanf("%f", &a);
    
    printf("Enter \'b\': ");
    scanf("%f", &b);

    printf("Enter \'c\': ");
    scanf("%f", &c);
    
    printf("\n%f * x^2 + %f * b + %f = 0\n\n", a, b, c);

    float *ans = solve_quadratic_equation(a, b, c);

    printf("%f * %f ^ 2 + %f * %f + %f = 0\n", a, ans[0], b, ans[0], c);
    printf("%f * %f ^ 2 + %f * %f + %f = 0\n", a, ans[1], b, ans[1], c);
    
    return 0;
}
