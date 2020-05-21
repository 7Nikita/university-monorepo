//
// Created by Nikita Pekurin on 4/26/20.
//


#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>

#define endl '\n'

typedef std::vector<std::vector<double>> Matrix;

using namespace std;

const double EPS = 1e-6;

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

double multyply_vector_on_vector(const vector<double>& A,
                                 const Matrix& B,
                                 const int pos) {
    double ans = 0;
    for (int i = 0; i < A.size(); ++i) {
        ans += A[i] * B[i][pos];
    }
    return ans;
}

int main() {
    freopen(SRC_PATH"/input.txt", "r", stdin);
    // freopen(SRC_PATH"/output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int m;
    cin >> m;

    int n;
    cin >> n;

    Matrix A(m, vector<double>(n));
    vector<double> B(m);
    vector<double> C(n);
    vector<int> J(m);

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

    for (int i = 0; i < m; ++i) {
        cin >> J[i];
        --J[i];
    }

    vector<double> C_b(m);
    Matrix A_b(m, vector<double>(m));

    for (int i = 0; i < J.size(); ++i) {
        for (int row = 0; row < m; ++row) {
            A_b[row][i] = A[row][J[i]];
        }
    }

    Matrix A_b_inverse = find_inverse_matrix(A_b);

    vector<double> y = multiply_vector_on_matrix(C_b, A_b_inverse);

    while(true) {
        vector<double> kappa_b = multiply_matrix_on_vector(A_b_inverse, B);
        vector<double> kappa(n);
        for (int i = 0; i < J.size(); ++i) {
            kappa[J[i]] = kappa_b[i];
        }

        int j = -1;
        bool flag = false;
        for (int i = kappa.size() - 1; i >= 0; --i) {
            if (kappa[i] < 0.0 && fabs(kappa[i]) > EPS) {
                for (int k = 0; k < J.size(); ++k) {
                    if (J[k] == i) {
                        j = k;
                        flag = true;
                        break;
                    }
                }
            }
            if (flag) {
                break;
            }
        }

        if (j == -1) {
            cout << "y:";
            for (const auto& e: y) {
                cout << " " << e;
            }
            cout << endl;
            cout << "Jb:";
            for (const auto& e: J) {
                cout << " " << e;
            }
            cout << endl;
            return 0;
        }

        vector<double> delta_y = A_b_inverse[j];

        unordered_set<int> Jb;
        for (const auto& e: J) Jb.insert(e);

        map<int, double> M;
        for (int i = 0; i < kappa.size(); ++i) {
            if (Jb.count(kappa[i]) == 0) {
                M[i] = multyply_vector_on_vector(delta_y, A, i);
            }
        }

        pair<int, double> Q_0 = {-1, INFINITY};
        vector<double> Q;
        map<int, double>::iterator it;
        for (it = M.begin(); it != M.end(); ++it) {
            if (it->second < 0.0 && fabs(it->second) > EPS) {
                double tmp = (C[it->first] - multyply_vector_on_vector(y, A, it->first)) / it->second;
                if (Q_0.second > tmp) {
                    Q_0 = {it->first, tmp};
                }
                Q.push_back(tmp);
            }
        }

        if (Q_0.second == INFINITY) {
            cout << "No solutions.";
            return 0;
        }

        J[j] = Q_0.first;
        for (int i = 0; i < delta_y.size(); ++i) {
            y[i] += delta_y[i] * Q_0.second;
        }

        for (int i = 0; i < J.size(); ++i) {
            for (int row = 0; row < m; ++row) {
                A_b[row][i] = A[row][J[i]];
            }
        }

        A_b_inverse = find_inverse_matrix(A_b);
    }

}