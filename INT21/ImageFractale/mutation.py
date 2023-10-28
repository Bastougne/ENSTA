import image_fractale as fract
import numpy.random as rd

PROBA_CHANGT_ESPECE=0.05

#Utilise une loi de Poisson pour modifier les couleurs
#Mutation trop faible?
def PoissonRGB(img,lam,n):
	rd.seed()
	nbCol=rd.randint(3)
	r,g,b=img.GetCol(n)
	if(nbCol==0):
		r=(r+rd.poisson(lam))%256
	if(nbCol==1):
		g=(g+rd.poisson(lam))%256
	if(nbCol==2):
		g=(g+rd.poisson(lam))%256	
	img.SetCol_RGB(r,g,b,n)


# Modifie aléatoirement une des quatre couleurs
def MutationCol(img,lam):
	col=rd.randint(4)
	PoissonRGB(img,lam,col)

# Modifie le paramètre c selon une gaussienne
def MutationParameter(img,lam):
	rd.seed()
	n=rd.randint(4)
	c_x,c_y=img.GetParam_XY(n)

	#Pas de changement d'espèce?
	if(c_x!=0 or c_y!=0):
		img.SetParam_XY(c_x+rd.normal(lam),c_y+rd.normal(lam),n)
	else:
		if(rd.rand()<=PROBA_CHANGT_ESPECE):
			img.SetParam_XY(c_x+rd.normal(lam),c_y+rd.normal(lam),n)

#à utiliser si besoin:
#invert={"0":"1","1":"0"}
def invert(n):
	out=0
	if(n==0):
		out=1
	return out

# Choisit aléatoirement au plus n bits à modifier uniformément / 8 bits * 3 = 24 bits
def BitWiseMutation(img,n):
	nb=rd.randint(4)
	r,g,b=img.GetCol(nb)
	r_b=format(r,"08b") # 8 bits chacun
	g_b=format(g,"08b")	
	b_b=format(b,"08b")
	dna = r_b+g_b+b_b # 24 bits
	new_dna=dna
	i=0
	#Faire les opérations ici :
	while(i<n):
		index=rd.randint(24)
		new_dna=dna[0:index-1]+str(invert(dna[index]))+dna[index+1:24] #Inversion : 0 devient 1 et 1 devient 0
		i+=1
	#On remet tout dans r,g,b:
	r=int(new_dna[0:7],2)
	g=int(new_dna[8:15],2)
	b=int(new_dna[16:23],2)
	img.SetCol_RGB(r,g,b,n)

# Fonction qui regroupe ce qu'il faut pour faire muter l'image
def RandomMutation(img,lam_normale,lam_poisson, p_mutation, nb_bits=1):
	rd.seed()
	rand_float=rd.random()
	if(p_mutation>rand_float):
		MutationCol(img,lam_poisson)
		MutationParameter(img,lam_normale)
	if(p_mutation>rand_float*4):
		BitWiseMutation(img,nb_bits)
"""
 Quelques tests :
img=fract.ImageFractale(1,2)
print(img.__str__())
img=-img
img.InterpolColour()"""
