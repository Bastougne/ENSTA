import time
import image_fractale as fract
import mutation as mt
import matplotlib
from matplotlib import colors
import matplotlib.pyplot as plt
import numpy as np
from julia import julia_set

def creer_julia(img,nom,xmin=-3,xmax=3,xn=375,ymin=-3,ymax=3,yn=375,maxiter=500, horizon=1099511627776.0,dpi=30,width=10,height=10):
	"""
	xmin, xmax, xn = -1.25, +1.25, 3000//8
	ymin, ymax, yn = -1.25, +1.25, 3000//8
	maxiter = 100
	horizon = 2.0 ** 40 # =1099511627776.0
	"""
	log_horizon = np.log(np.log(horizon))/np.log(2)
	cmap=(img).InterpolColour()
	c_x, c_y=img.GetParam_XY(0)
	c1_x, c1_y=img.GetParam_XY(1)
	c2_x, c2_y=img.GetParam_XY(2)
	c3_x, c3_y=img.GetParam_XY(3)
	if(c3_x==0 and c3_y==0):
		xmin=-2
		xmax=2
		ymin=-2
		ymax=2

	ymin=ymin*height/width
	ymax=ymax*height/width
	""" Ce qui prend le plus de temps de calcul """
	Z, N = julia_set(xmin, xmax, ymin, ymax, xn, yn, c3_x, c3_y,c2_x, c2_y,c1_x, c1_y,c_x, c_y, maxiter, horizon)
    
    # Normalized recount as explained in:
    # https://linas.org/art-gallery/escape/smooth.html
    # https://www.ibm.com/developerworks/community/blogs/jfp/entry/My_Christmas_Gift

    # This line will generate warnings for null values but it is faster to
    # process them afterwards using the nan_to_num
	with np.errstate(invalid='ignore'):
		M = np.nan_to_num(N + 1 -np.log(np.log(abs(Z)))/(np.log(2)) + log_horizon)
	"""
	dpi = 30
	width = 10
	height = 10
	"""
	fig = plt.figure(figsize=(width, height), dpi=dpi)
	ax = fig.add_axes([0.0, 0.0, 1.0, 1.0], frameon=False, aspect=1)

    # Shaded rendering
	light = colors.LightSource(azdeg=315, altdeg=10)
	#M = light.shade(M, cmap=plt.cm.hot, vert_exag=1.5, norm=colors.PowerNorm(0.3), blend_mode='hsv')
	M = light.shade(M, cmap=cmap) # or cmap=plt.cm.coolwarm
    #M = light.shade(M, cmap=plt.cm.coolwarm)
    # see https://matplotlib.org/examples/color/colormaps_reference.html
	plt.imshow(M, extent=[xmin, xmax, ymin, ymax], interpolation="bicubic")
	ax.set_xticks([])
	ax.set_yticks([])
	plt.savefig(nom)
	plt.close()
	#plt.show()

"""
img=fract.ImageFractale(0,0.25, 10,0,100,155,0,0,0,180,75,255,255,255)
print(img.__str__())
#img=-img
img=-img
print(mt.PoissonRGB(img,0.7,1))
mt.MutationCol(img,0.5)
print(img)
mt.MutationCol(img,0.5)
mt.MutationCol(img,0.5)
print(img)
creer_julia(img)"""
