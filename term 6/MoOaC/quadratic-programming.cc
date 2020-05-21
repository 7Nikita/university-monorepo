#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <unordered_set>
#include <iomanip>

#define endl '\n'

typedef std::vector<std::vector<double>> Matrix;

using namespace std;

const double EPS = 1e-6;

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

template<typename T>
void print_vector(const vector<T> &in) {
    for (const auto &e: in) {
        cout << e << " ";
    }
    cout << endl;
}

void main_phase(const int m,
                const int n,
                const int k,
                const Matrix &A,
                const vector<double> &C,
                const Matrix &D,
                vector<double> &X,
                vector<int> &J,
                vector<int> &Jex,
                vector<bool> &Jex_mark) {
    int j0 = -1;
    Matrix A_b(m, vector<double>(m));
    Matrix A_b_inv(m, vector<double>(m));
    Matrix A_b_ex(m, vector<double>(m));

    while (true) {
        vector<int> sJ(J);
        sort(sJ.begin(), sJ.end());
        for (int i = 0; i < sJ.size(); ++i) {
            for (int row = 0; row < m; ++row) {
                A_b[row][i] = A[row][sJ[i]];
            }
        }

        A_b_inv = find_inverse_matrix(A_b);

        vector<double> C_x = multiply_vector_on_matrix(X, D);
        for (int i = 0; i < n; ++i) {
            C_x[i] += C[i];
        }

        vector<double> C_b_x(J.size());
        vector<double> neg_C_b_x(J.size());
        for (int i = 0; i < J.size(); ++i) {
            C_b_x[i] = C_x[sJ[i]];
            neg_C_b_x[i] = -C_b_x[i];
        }
        vector<double> U_x = multiply_vector_on_matrix(neg_C_b_x, A_b_inv);

        vector<double> delta_x = multiply_vector_on_matrix(U_x, A);
        for (int i = 0; i < delta_x.size(); ++i) {
            delta_x[i] += C_x[i];
        }

        j0 = -1;
        bool flag = true;
        for (int i = 0; i < delta_x.size(); ++i) {
            if (delta_x[i] < 0.0) {
                flag = false;
                j0 = i;
                break;
            }
        }
        if (flag) {
            cout << "Bounded\n";
            print_vector(X);
            return;
        }

        vector<double> l(C.size());
        l[j0] = 1;

        for (int i = 0; i < J.size(); ++i) {
            for (int row = 0; row < m; ++row) {
                A_b_ex[row][i] = A[row][Jex[i] - 1];
            }
        }

        int lenDiv2 = J.size();
        Matrix h(lenDiv2 * 2, vector<double>(lenDiv2 * 2));
        Matrix dStar;
        Matrix abStar;


        for (int i = 0; i < D.size(); ++i) {
            vector<double> tmp;
            if (!Jex_mark[i]) continue;
            for (int j = 0; j < D[0].size(); ++j) {
                if (!Jex_mark[j]) continue;
                tmp.push_back(D[i][j]);
            }
            dStar.push_back(tmp);
        }

        for (int i = 0; i < A.size(); ++i) {
            vector<double> tmp;
            for (int j = 0; j < A[0].size(); ++j) {
                if (!Jex_mark[j]) continue;
                tmp.push_back(A[i][j]);
            }
            abStar.push_back(tmp);
        }

        vector<vector<double>> abStarTrans = transpose_matrix(abStar);

        for (int i = 0; i < lenDiv2; ++i) {
            for (int j = 0; j < lenDiv2; ++j) {
                h[i][j] = dStar[i][j];
            }
        }

        for (int i = 0; i < lenDiv2; ++i) {
            for (int j = 0; j < lenDiv2; ++j) {
                h[i + lenDiv2][j] = abStar[i][j];
            }
        }

        for (int i = 0; i < lenDiv2; ++i) {
            for (int j = 0; j < lenDiv2; ++j) {
                h[i][j + lenDiv2] = abStarTrans[i][j];
            }
        }

        vector<double> b;
        for (int i = 0; i < J.size(); ++i) {
            b.push_back(D[i][j0]);
        }
        for (int i = 0; i < A.size(); ++i) {
            b.push_back(A[i][j0]);
        }

        Matrix h_inv = find_inverse_matrix(h);

        vector<double> x_ = multiply_matrix_on_vector(h_inv, b);
        for (auto &e: x_) {
            e *= -1;
        }

        for (int i = 0; i < Jex.size(); ++i) {
            l[i] = x_[i];
        }

        double sigma = 0.0;
        vector<double> ld = multiply_vector_on_matrix(l, D);
        for (int i = 0; i < ld.size(); ++i) {
            sigma += l[i] * ld[i];
        }

        map<double, double> Q;
        if (sigma == 0.0 || fabs(sigma) < EPS) {
            Q[j0] = INFINITY;
        } else {
            Q[j0] = fabs(delta_x[j0]) / sigma;
        }
        for (const auto &j: Jex) {
            if (j != j0) {
                Q[j] = l[j] < 0 ? -X[j] / l[j] : INFINITY;
            }

        }

        pair<int, double> q0 = {j0, Q[j0]};
        for (const auto&[k, v]: Q) {
            if (v < q0.second) {
                q0 = {k, v};
            }
        }

        if (q0.second == INFINITY) {
            cout << "Unbounded\n";
            return;
        }

        for (int i = 0; i < X.size(); ++i) {
            X[i] += q0.second + l[i];
        }

        unordered_set<double> diff_J;
        set_difference(J.begin(), J.end(),
                       Jex.begin(), Jex.end(),
                       inserter(diff_J, diff_J.begin()));

        if (q0.first == j0) {
            Jex.push_back(q0.first);
            Jex_mark[Jex[Jex.size() - 1]] = true;
        } else if (diff_J.count(q0.first)) {
            int idx = -1;
            for (int i = 0; i < Jex.size(); ++i) {
                if (Jex[i] == q0.first) {
                    idx = i;
                    break;
                }
            }
            Jex_mark[Jex[idx]] = false;
            Jex.erase(Jex.begin() + idx);
        } else {
            int s = -1;
            for (int i = 0; i < J.size(); ++i) {
                if (J[i] == q0.first) {
                    s = i;
                    break;
                }
            }
            int j_ = -1;
            if (s != -1) {
                for (const auto &j: diff_J) {
                    vector<double> j_column;
                    for (int i = 0; i < A[j].size(); ++i) {
                        j_column.push_back(A[i][j]);
                    }
                    vector<double> tmp = multiply_matrix_on_vector(A, j_column);
                    if (tmp[s] != 0 && fabs(tmp[s]) > EPS) {
                        j_ = j;
                        break;
                    }

                }
                if (j_ != -1) {
                    J[s] = j_;
                    int idx = -1;
                    for (int i = 0; i < Jex.size(); ++i) {
                        if (Jex[i] == q0.first) {
                            idx = i;
                            break;
                        }
                    }
                    if (idx != -1) {
                        Jex_mark[Jex[idx]] = false;
                        Jex.erase(Jex.begin() + idx);
                    }
                }
            } else {
                J[s] = q0.first;
                int idx = -1;
                for (int i = 0; i < Jex.size(); ++i) {
                    if (Jex[i] == s) {
                        idx = i;
                        break;
                    }
                }
                if (idx != -1) {
                    Jex_mark[Jex[idx]] = false;
                    Jex[idx] = q0.first;
                    Jex_mark[Jex[idx]] = true;
                }
            }
        }
    }
}

int main() {
    freopen(SRC_PATH"/input.txt", "r", stdin);
    // freopen(SRC_PATH"/output.txt", "w", stdout);
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int m, n, k;
    cin >> m >> n >> k;

    Matrix A(m, vector<double>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }

    vector<double> B(m);
    for (int i = 0; i < m; ++i) {
        cin >> B[i];
    }

    vector<double> C(n);
    for (int i = 0; i < n; ++i) {
        cin >> C[i];
    }

    Matrix D(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> D[i][j];
        }
    }

    vector<double> X(n);
    for (int i = 0; i < n; ++i) {
        cin >> X[i];
    }

    vector<int> Jb(m);
    for (int i = 0; i < m; ++i) {
        cin >> Jb[i];
        --Jb[i];
    }

    vector<int> Jex(k);
    vector<bool> Jex_mark(600);
    for (int i = 0; i < k; ++i) {
        cin >> Jex[i];
        --Jex[i];
        Jex_mark[Jex[i]] = true;
    }
    cout << fixed << setprecision(10);
    main_phase(m, n, k, A, C, D, X, Jb, Jex, Jex_mark);
    return 0;
}