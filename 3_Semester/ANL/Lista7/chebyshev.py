import matplotlib.backends.backend_pdf
pdf = matplotlib.backends.backend_pdf.PdfPages("chebyshev.pdf")
import numpy as np
import matplotlib.pyplot as plt

#all_xk = np.linspace(-1, 1, (n+1)) # n+1 wezlow xk na przedziale (-1,1)
#print(all_xk)


def chebyshev_zeroes(n):
    return [np.cos((np.pi)*((2*k-1)/(2*n))) for k in range(1, n+1)]


def pn_value(point_x, n):
    all_xk = chebyshev_zeroes(n)
    point_y = []
    for x in point_x:
        product = 1
        for xk in all_xk:
            product *= (x-xk)
        point_y.append(product)
    return point_y


point_x = np.linspace(-1, 1, 100)
for n in range(4, 21):  # create all figures
    plt.figure(n)
    plt.suptitle("p_{}" .format(n+1))

    plt.plot(point_x, pn_value(point_x, n))

    pdf.savefig(n)  # save on the fly
    plt.close()  # close figure once saved

pdf.close()

