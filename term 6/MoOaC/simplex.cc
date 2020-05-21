//
// Created by Nikita Pekurin on 4/18/20.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

#define endl '\n'
#define err do { cout << "Unbounded\n"; return 0; } while(false)

typedef std::vector<std::vector<double>> Matrix;

using namespace std;

Matrix multiply_matrices(const Matrix &A,
                         const Matrix &B) {
    const int n = A.front().size();
    const int m = B.front().size();
    Matrix ans(n, vector<double>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                ans[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return ans;
}

vector<double> multiply_vector_on_matrix(const vector<double> &A,
                                         const Matrix &B) {
    vector<double> ans(B[0].size());
    const int N = A.size();
    for (int i = 0; i < B[0].size(); ++i) {
        double cur_sum = 0.0;
        for (int j = 0; j < N; ++j) {
            cur_sum += A[j] * B[j][i];
        }
        ans[i] = cur_sum;
    }
    return ans;
}

vector<double> multiply_matrix_on_vector(const Matrix &A,
                                         const vector<double> &B) {
    const int N = A.size();
    vector<double> ans(N);
    for (int i = 0; i < N; ++i) {
        double cur_sum = 0.0;
        for (int j = 0; j < N; ++j) {
            cur_sum += A[i][j] * B[j];
        }
        ans[i] = cur_sum;
    }
    return ans;
}

Matrix find_inverse_matrix(const Matrix &A,
                           const Matrix &B,
                           const int pos,
                           const vector<double> &X) {
    const int n = A.size();
    Matrix ans(B.size(), vector<double>(B[0].size()));
    vector<double> l(n);
    l = multiply_matrix_on_vector(B, X);
    double val = l[pos];
    l[pos] = -1;
    for (int i = 0; i < l.size(); ++i) {
        l[i] *= -1.0 / val;
    }
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < B[0].size(); ++j) {
            ans[j][i] = l[j] * B[pos][i];
            if (j != pos) {
                ans[j][i] += B[j][i];
            }
        }
    }
    return ans;
}

Matrix find_inverse_matrix(const Matrix &A) {
    const int N = A.size();
    Matrix ans(N, vector<double>(N));
    Matrix A_(A);
    for (int i = 0; i < ans.size(); ++i) {
        ans[i][i] = 1.0;
    }
    for (int i = 0, j = 0; i < A_.size() && j < A_.size(); ++i, ++j) {
        int k = j;
        for (int idx = j; idx < A_.size(); ++idx) {
            if (fabs(A_[idx][i]) > fabs(A_[k][i]))
                k = idx;
        }
        A_[j].swap(A_[k]);
        ans[j].swap(ans[k]);
        for (int idx = 0; idx < A_.size(); ++idx) {
            if (idx != j) {
                double t = (A_[idx][i]) / A_[j][i];
                for (int r = 0; r < A_.size(); ++r) {
                    A_[idx][r] -= A_[j][r] * t;
                    ans[idx][r] -= ans[j][r] * t;
                }
            }
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[i].size(); ++j) {
            if (ans[i][j]) {
                ans[i][j] /= A_[i][i];
            }
        }
    }
    return ans;
}

Matrix transpose_matrix(const Matrix &x) {
    Matrix ans(x[0].size(), vector<double>(x.size()));
    for (int i = 0; i < x.size(); ++i) {
        for (int j = 0; j < x[0].size(); ++j) {
            ans[j][i] = x[i][j];
        }
    }
    return ans;
}

void print_matrix(const Matrix &in) {
    for (const auto &y: in) {
        for (const auto &x: y) {
            cout << x << " ";
        }
        cout << endl;
    }
}

pair<string, vector<double>> simplex_main(const int m,
                                          const int n,
                                          const Matrix &A,
                                          const vector<double> &C,
                                          const vector<double> &X_,
                                          const vector<double> &J_) {
    vector<double> X = vector<double>(X_);
    vector<double> J = vector<double>(J_);

    int col_index_to_replace = -1;

    int j0 = -1;
    vector<double> C_b(m);
    Matrix A_b(m, vector<double>(m));
    Matrix A_b_inverse(m, vector<double>(m));

    for (int i = 0; i < J.size(); ++i) {
        for (int row = 0; row < m; ++row) {
            A_b[row][i] = A[row][J[i] - 1];
        }
    }
    cout << fixed << setprecision(10);
    while (true) {
        for (int i = 0; i < J.size(); ++i) {
            C_b[i] = C[J[i] - 1];
        }

        if (col_index_to_replace == -1) {
            A_b_inverse = find_inverse_matrix(A_b);
        } else {
            Matrix new_A_b_inverse(m, vector<double>(m));
            vector<double> new_col(m);
            for (int i = 0; i < m; ++i) {
                new_col[i] = A[i][j0];
            }
            new_A_b_inverse = move(find_inverse_matrix(A_b, A_b_inverse, col_index_to_replace, new_col));
            A_b_inverse = new_A_b_inverse;
        }

        // u_hatch = C_b * A_b_inv
        vector<double> u_hatch(m);
        u_hatch = multiply_vector_on_matrix(C_b, A_b_inverse);

        // delta_hatch = u_hatch * A - c_hatch
        bool flag = true;
        vector<double> delta_hatch(n);
        delta_hatch = multiply_vector_on_matrix(u_hatch, A);
        for (int i = 0; i < n; ++i) {
            delta_hatch[i] -= C[i];
            if (delta_hatch[i] < 0.0 && fabs(delta_hatch[i]) > 1e-6) {
                flag = false;
                j0 = i;
                break;
            }
        }

        if (flag) {
            return make_pair("Bounded", X);
        }

        // z = A_b_inverse * A_j_0
        vector<double> z(m);
        vector<double> A_j_0(m);
        for (int i = 0; i < m; ++i) {
            A_j_0[i] = A[i][j0];
        }
        z = multiply_matrix_on_vector(A_b_inverse, A_j_0);

        pair<double, int> Q_0 = make_pair(INFINITY, -1);
        for (int i = 0; i < m; ++i) {
            double coef = INFINITY;
            if (z[i] > 0) coef = X[J[i] - 1] / z[i];
            if (Q_0.first > coef) Q_0 = make_pair(coef, i);
        }
        if (Q_0.first == INFINITY) {
            return make_pair("Unbounded", X);
        }

        col_index_to_replace = Q_0.second;
        J[Q_0.second] = j0 + 1;

        for (int i = 0; i < X.size(); ++i) {
            bool contains = false;
            for (int k = 0; k < J.size(); ++k) {
                if (i == J[k] - 1) {
                    contains = true;
                    if (i == j0) {
                        X[i] = Q_0.first;
                    } else {
                        X[i] = X[i] - Q_0.first * z[k];
                    }
                }
            }
            if (!contains) {
                X[i] = 0;
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> m;

    int n;
    cin >> n;

    Matrix A(m, vector<double>(n));
    vector<double> B(m);
    vector<double> C(n);
    vector<double> X(n);
    vector<double> J(m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < m; ++i) {
        cin >> B[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> C[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> X[i];
    }

    for (int i = 0; i < m; ++i) {
        cin >> J[i];
    }

    pair<string, vector<double>> ans = simplex_main(m, n, A, C, X, J);
    if (ans.first == "Unbounded") {
        err;
    } else {
        cout << "Bounded\n";
        for (const auto &e: ans.second) {
            cout << e << " ";
        }
    }

    return 0;
}

