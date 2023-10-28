import numpy as np
import cv2

from matplotlib import pyplot as plt

def Harris( img, W, alpha ):
    ( h, w ) = img.shape;
    # Masques de Sobel
    hx = np.array( [[-1, 0, 1],[-2, 0, 2],[-1, 0, 1]] )
    hy = np.array( [[1, 2, 1], [0, 0, 0], [-1, -2, -1]] )
    # Estimations des dérivées premières
    Ix = cv2.filter2D( img, -1, hx )
    Iy = cv2.filter2D( img, -1, hy )
    # Définition de la fonction d'intérêt
    Theta = img * 0
    for i in range( h ):
        for j in range( w ):
            # Calcul de la matrice d'autocorrélation sur la fenêtre de taille W
            H = np.array( [[0, 0], [0, 0]] )
            for i1 in range( i - W, i + W +1 ):
                for j1 in range( j - W, j + W +1 ):
                    # Gestion des effets de bord
                    i2, j2 = min( max( 0, i1 ), h - 1 ), min( max( 0, j1 ), w - 1 )
                    H11 = Ix[i2, j2] * Ix[i2, j2]
                    H12 = Ix[i2, j2] * Iy[i2, j2]
                    H22 = Iy[i2, j2] * Iy[i2, j2]
                    H = H + np.array( [[H11, H12], [H12, H22]] )
            # Calcul de la fonction d'intérêt en ( i, j )
            Theta[i, j] = np.linalg.det( H ) - alpha * np.trace( H ) ** 2
    return Theta


#Lecture image en niveau de gris et conversion en float64
img=np.float64(cv2.imread('../Image_Pairs/Graffiti0.png',cv2.IMREAD_GRAYSCALE))
(h,w) = img.shape
print("Dimension de l'image :",h,"lignes x",w,"colonnes")
print("Type de l'image :",img.dtype)

#Début du calcul
t1 = cv2.getTickCount()
Theta = cv2.copyMakeBorder(img,0,0,0,0,cv2.BORDER_REPLICATE)
# Mettre ici le calcul de la fonction d'intérêt de Harris
Theta = Harris( Theta, 1, 0.06 )
# Calcul des maxima locaux et seuillage
Theta_maxloc = cv2.copyMakeBorder(Theta,0,0,0,0,cv2.BORDER_REPLICATE)
d_maxloc = 3
seuil_relatif = 0.01
se = np.ones((d_maxloc,d_maxloc),np.uint8)
Theta_dil = cv2.dilate(Theta,se)
#Suppression des non-maxima-locaux
Theta_maxloc[Theta < Theta_dil] = 0.0
#On néglige également les valeurs trop faibles
Theta_maxloc[Theta < seuil_relatif*Theta.max()] = 0.0
t2 = cv2.getTickCount()
time = (t2 - t1)/ cv2.getTickFrequency()
print("Mon calcul des points de Harris :",time,"s")
print("Nombre de cycles par pixel :",(t2 - t1)/(h*w),"cpp")

plt.subplot(131)
plt.imshow(img,cmap = 'gray')
plt.title('Image originale')

plt.subplot(132)
plt.imshow(Theta,cmap = 'gray')
plt.title('Fonction de Harris')

se_croix = np.uint8([[1, 0, 0, 0, 1],
[0, 1, 0, 1, 0],[0, 0, 1, 0, 0],
[0, 1, 0, 1, 0],[1, 0, 0, 0, 1]])
Theta_ml_dil = cv2.dilate(Theta_maxloc,se_croix)
#Relecture image pour affichage couleur
Img_pts=cv2.imread('../Image_Pairs/Graffiti0.png',cv2.IMREAD_COLOR)
(h,w,c) = Img_pts.shape
print("Dimension de l'image :",h,"lignes x",w,"colonnes x",c,"canaux")
print("Type de l'image :",Img_pts.dtype)
#On affiche les points (croix) en rouge
Img_pts[Theta_ml_dil > 0] = [255,0,0]
plt.subplot(133)
plt.imshow(Img_pts)
plt.title('Points de Harris')

plt.show()
