/*
**
** F[i] = (A[i] - B[i]) +(C[i] * D[i]), i = 1...8
**
*/

#include <random>
#include <iostream>
#include <immintrin.h>


const int N = 8;
const double EPS = 1e-11;


template<typename T>
T* read_elemets(int n){
    T* tmp = new T[n];
    for (int i = 0; i < n; ++i)
        std::cin >> tmp[i];
    return tmp;
}

template<typename T>
T* random_elements(int n){
    T* tmp  = new T[n];
    for (int i = 0; i < n; ++i)
        tmp[i] = static_cast <T> (rand()) / static_cast <T> (RAND_MAX) * 1000;
    return tmp;
}

double * ftod(float * arr, int n){
    double *tmp = new double[n];
    for (int i = 0; i < n; ++i)
        tmp[i] = static_cast<double>(arr[i]);
    return tmp;
}

void __cpuid(int* cpuinfo)
{
    asm(
        "cpuid;"
        :"=a" (cpuinfo[0]),
        "=D" (cpuinfo[1]),
        "=c" (cpuinfo[2]),
        "=d" (cpuinfo[3])
        :"0" (1)
        );
}

double * solve(float *a, float *b, float *c, double *d, int n){
    double *ans = new double[n];

    __m256 ma = _mm256_loadu_ps(a);
    __m256 mb = _mm256_loadu_ps(b);

    ma = _mm256_sub_ps(ma, mb);
    
    float tmp[n];
    _mm256_storeu_ps(tmp, ma);
    
    double *da = ftod(tmp, n);
    double *dc = ftod(c, n);
    
    __m256d md_1 = _mm256_loadu_pd(d);
    __m256d md_2 = _mm256_loadu_pd(&d[4]);
    
    __m256d tmp_1 = _mm256_loadu_pd(dc);
    __m256d tmp_2 = _mm256_loadu_pd(&dc[4]);
    
    md_1 = _mm256_mul_pd(md_1, tmp_1);
    md_2 = _mm256_mul_pd(md_2, tmp_2);
    
    tmp_1 = _mm256_loadu_pd(da);
    tmp_2 = _mm256_loadu_pd(&da[4]);
    
    md_1 = _mm256_add_pd(md_1, tmp_1);
    md_2 = _mm256_add_pd(md_2, tmp_2);
    
    _mm256_storeu_pd(ans, md_1);
    _mm256_storeu_pd(&ans[4], md_2);
    
    return ans;
}

double * cpp_solve(float *a, float *b, float *c, double *d, int n){
    float tmp[n];
    for (int i = 0; i < n; ++i){
        tmp[i] = a[i] - b[i];
    }
    
    double *dc = ftod(c, n);
    
    for (int i = 0; i < n; ++i)
        dc[i] *= d[i];
    
    double *ans = new double[n];
    for (int i = 0; i < n; ++i)
        ans[i] = tmp[i] + dc[i];
    
    return ans;
}

void test(double *ans, double *cpp_ans, int n){
    
    for (int i = 0; i < n; ++i){
        bool eq = (ans[i] - cpp_ans[i] < EPS);
        std::cout << "[" << i << "]: (CPP = " << cpp_ans[i];
        std::cout << ") == (AVX = " << ans[i] << ") : " << eq << std::endl;
    }
}

int main(int argc, char *argv[]){

    int cpuinfo[4];
    __cpuid(cpuinfo);
    
    bool avxSupportted = cpuinfo[2] & (1 << 28) || false;
    
    if (!avxSupportted){
        throw std::runtime_error("AVX is not supported");
    }

    float *a;
    float *b;
    float *c;
    
    double *d;

    bool random_flag = false;
    for (int i = 0; i < argc; ++i)
        random_flag |= strcmp(argv[i], "-r") == 0;

    if (random_flag){
        a = random_elements<float>(N);
        b = random_elements<float>(N);
        c = random_elements<float>(N);
        d = random_elements<double>(N);
    }
    else {
        a = read_elemets<float>(N);
        b = read_elemets<float>(N);
        c = read_elemets<float>(N);
        d = read_elemets<double>(N);
    }
    
    double *ans = solve(a, b, c, d, N);
    double *cpp_ans = cpp_solve(a, b, c, d, N);
    
    test(ans, cpp_ans, N);
    
    return 0;
}

