from cProfile import label
from cmath import sin
from distutils import extension
import numpy as np
from skimage.morphology import black_tophat, binary_opening
from skimage.morphology import reconstruction,skeletonize, convex_hull_image, thin
from skimage.morphology import square, diamond, octagon, rectangle, star, disk
from skimage.filters import apply_hysteresis_threshold
from skimage.filters.rank import entropy, enhance_contrast_percentile
from PIL import Image
from scipy import ndimage as ndi
from skimage.util import img_as_ubyte
import math
from skimage import data, filters
from matplotlib import pyplot as plt

numero = '37'
extension = 'ODN'

def points_cercle( rayon ): # Bresenham 8-symétrie
    taille = 2 * rayon + 1
    r2 = rayon * rayon
    x1, y1 = rayon, rayon
    points = []
    points.append( ( x1, y1 + rayon ) )
    points.append( ( x1, y1 - rayon ) )
    points.append( ( x1 + rayon, y1 ) )
    points.append( ( x1 - rayon, y1 ) )

    x2, y2 = 1, rayon
    while ( x2 < y2 ):
        points.append( ( x1 + x2, y1 + y2 ) )
        points.append( ( x1 + x2, y1 - y2 ) )
        points.append( ( x1 - x2, y1 + y2 ) )
        points.append( ( x1 - x2, y1 - y2 ) )
        points.append( ( x1 + y2, y1 + x2 ) )
        points.append( ( x1 + y2, y1 - x2 ) )
        points.append( ( x1 - y2, y1 + x2 ) )
        points.append( ( x1 - y2, y1 - x2 ) )
        x2 += 1
        y2 = int( np.sqrt( r2 - x2 * x2 ) )
    return points


def points_droite( x1, y1, x2, y2 ):
    dx, dy = abs( x2 - x1 ), -abs( y2 - y1 )
    sx = 1 if ( x1 < x2 ) else -1
    sy = 1 if ( y1 < y2 ) else -1
    points = []
    
    error = dx + dy
    x, y = x1, y1
    while True:
        points.append( ( x, y ) )
        if ( x, y ) == ( x2, y2 ): break
        e2 = 2 * error
        if e2 >= dy:
            if x == x2: break
            error += dy
            x+= sx
        if e2 <= dx:
            if y == y2: break
            error += dx
            y+= sy
    return points


def my_segmentation( img, img_mask, taille ):

    # constantes
    elem_tophat = square( 10 )
    ratio_seuil = 0.9
    taille_seg = taille #30

    # pré-traitement
    img_epuree = black_tophat( img, elem_tophat ) # le black tophat "inverse" les couleurs
    mini, maxi = np.amin( img_epuree ), np.amax( img_epuree )
    img_epuree = -img_epuree + mini + maxi # on rétablit ici "l'ordre" des couleurs
    img_epuree = ( img_epuree < ( mini + maxi ) * ratio_seuil ) & img_mask

    # recherche de segments
    img_seed = img < 0
    x1, y1 = taille_seg, taille_seg
    i, points = 0, points_cercle( taille_seg )
    for x2, y2 in points:
        elem = np.zeros( ( 2 * taille_seg + 1, 2 * taille_seg + 1 ) )
        for x, y in points_droite( x1, y1, x2, y2 ):
            elem[x][y] = 1
        img_seed = img_seed | binary_opening( img_epuree, elem )
        i = i + 1
        # print( i, "/", len( points ) )
    #img_segments = reconstruction( img_seed, img_epuree ).astype(np.bool_)

    return img_seed


def evaluate(img_out, img_GT):
    GT_skel  = thin(img_GT, max_num_iter = 15) # On suppose que la demie épaisseur maximum
    img_out_skel  = thin(img_out, max_num_iter = 15) # d'un vaisseau est de 15 pixels...
    TP = np.sum(img_out_skel & img_GT) # Vrais positifs
    FP = np.sum(img_out_skel & ~img_GT) # Faux positifs (relaxes)
    FN = np.sum(GT_skel & ~img_out) # Faux negatifs (relaxes)

    ACCU = TP / (TP + FP) # Precision
    RECALL = TP / (TP + FN) # Rappel
    return ACCU, RECALL, img_out_skel, GT_skel


# Ouvrir l'image originale en niveau de gris
img =  np.asarray(Image.open('./images_IOSTAR/star'+numero+'_'+extension+'.jpg')).astype(np.uint8)
print(img.shape)

nrows, ncols = img.shape
row, col = np.ogrid[:nrows, :ncols]

# On ne considere que les pixels dans le disque inscrit
img_mask = (np.ones(img.shape)).astype(np.bool_)
invalid_pixels = ((row - nrows/2)**2 + (col - ncols/2)**2 > (nrows / 2)**2)
img_mask[invalid_pixels] = 0


# Partie plot
# X = []
# accuracy_list = []
# recall_list = []
# norm_list = []

# for i in range(51):
i = 28
img_out = my_segmentation( img, img_mask, i )

#Ouvrir l'image Verite Terrain en booleen
img_GT =  np.asarray(Image.open('./images_IOSTAR/GT_'+str(numero)+'.png')).astype(np.bool_)

ACCU, RECALL, img_out_skel, GT_skel = evaluate(img_out, img_GT)
print('Taille =', str( i ), ', Accuracy =', ACCU,', Recall =', RECALL)

# X.append( i )
# accuracy_list.append( ACCU )
# recall_list.append( RECALL )
# norm_list.append( math.sqrt( ACCU**2 + RECALL**2 ) )


plt.subplot(231)
plt.imshow(img,cmap = 'gray')
plt.title('Image Originale')
plt.subplot(232)
plt.imshow(img_out)
plt.title('Segmentation')
plt.subplot(233)
plt.imshow(img_out_skel)
plt.title('Segmentation squelette')
plt.subplot(235)
plt.imshow(img_GT)
plt.title('Verite Terrain')
plt.subplot(236)
plt.imshow(GT_skel)
plt.title('Verite Terrain Squelette')
plt.show()


""""
plt.plot( X, accuracy_list, 'o-', label='Accuracy' )
plt.plot( X, recall_list, 'o-', label='Recall' )
plt.plot( X, norm_list, 'o-', label='Norm' )
plt.legend()
plt.show()
"""
