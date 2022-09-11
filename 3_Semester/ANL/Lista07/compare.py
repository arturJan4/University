import numpy as np
import matplotlib.pyplot as plt
import matplotlib.backends.backend_pdf
pdf = matplotlib.backends.backend_pdf.PdfPages("compare.pdf")

# all_xk = np.linspace(-1, 1, (n+1)) # n+1 wezlow xk na przedziale (-1,1)
# print(all_xk)


def chebyshev_zeroes(n):
    return [np.cos((np.pi*(2*k-1))/(2*n)) for k in range(1, n+1)]


def pn_value_c(point_x, n):         # wezly Chebysheva
    all_xk = chebyshev_zeroes(n)
    point_y = []
    for x in point_x:
        product = 1
        for xk in all_xk:
            product *= (x-xk)
        point_y.append(product)
    return point_y


def pn_value_e(point_x, n):         # wezly rownoodlegle
    all_xk = np.linspace(-1, 1, n)  # dla pn, n punktów xk \in [-1 , .. , 1]
    point_y = []
    for x in point_x:
        product = 1
        for xk in all_xk:
            product *= (x-xk)
        point_y.append(product)
    return point_y


point_x = np.linspace(-1, 1, 100)
for n in range(4, 20):  # create all figures
    plt.figure(n)

    ax = plt.subplot()

    m = n + 1
    plt.suptitle("p_{}" .format(m))

    # plt.plot(point_x, (np.cos((m+1) * np.arccos(point_x)))/(pow(2, m)))
    plt.plot(point_x, pn_value_c(point_x, m))
    plt.plot(point_x, pn_value_e(point_x, m))

    plt.legend(["Chebyshev", "rownoodlegle"])

    ax.axhline(y=0, color='k')
    ax.axvline(x=0, color='k')

    pdf.savefig(n)  # save on the fly
    plt.close()  # close figure once saved

pdf.close()
