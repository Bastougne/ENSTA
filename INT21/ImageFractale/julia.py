"""
===================================
Shaded & power normalized rendering
===================================

The Mandelbrot set rendering can be improved by using a normalized recount
associated with a power normalized colormap (gamma=0.3). Rendering can be
further enhanced thanks to shading.

The `maxiter` gives the precision of the computation. `maxiter=200` should
take a few seconds on most modern laptops.
"""
import numpy as np
import image_fractale as fract
import mutation as mt
def julia_set(xmin, xmax, ymin, ymax, xn, yn, c3x, c3y,c2x, c2y,c1x, c1y,cx, cy, maxiter, horizon=2.0):
    X = np.linspace(xmin, xmax, xn).astype(np.float32)
    Y = np.linspace(ymin, ymax, yn).astype(np.float32)
    Z = X + Y[:, None] * 1j
    N = np.zeros_like(Z, dtype=int)
    C = complex(cx, cy)
    C1 = complex(c1x, c1y)
    C2 = complex(c2x, c2y)
    C3 = complex(c3x, c3y) 

    for n in range(maxiter):
        I = np.less(abs(Z), horizon)
        N[I] = n
        # ancienne version, sans Hörner
        # Z[I] = C3*Z[I]**3 +C2*Z[I]**2 + C1*Z[I] + C
        # Hörner ordre 3, pour éviter les puissances :
        Z[I] = C+ Z[I]*(C1 + Z[I]*(C2 + Z[I]*C3/10))
    N[N == maxiter-1] = 0
    return Z, N
