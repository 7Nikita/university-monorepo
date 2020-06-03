import numpy as np

matrix = np.array(
    [[1., 0., 5.],
     [2., 1., 6.],
     [3., 4., 0.]]
)

inverse_matrix = np.array(
    [[-24., 20., -5.],
     [18., -15., 4.],
     [5., -4., 1.]]
)

position = 2

x = np.array(
    [[2.],
     [2.],
     [2.]]
)


def find_inverse_matrix(A, inv_A, position, x):
    l = inv_A @ x

    if l[position] == 0:
        print('The matrix is not invertible')
        return None

    l_wave = np.copy(l)
    l_wave[position] = -1.

    l_hat = -1. / l[position] * l_wave

    q = np.eye(len(A))
    q[:, position] = l_hat[:, 0]

    ans = q @ inv_A
    return ans


def main():
    ans = find_inverse_matrix(matrix, inverse_matrix, position - 1, x)
    if ans is not None:
        print(ans)
        new_matrix = np.copy(matrix)
        new_matrix[:, position - 1] = x[:, 0]
        print(new_matrix @ ans)


if __name__ == '__main__':
    main()
