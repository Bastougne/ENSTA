import cmath
import numpy
from matplotlib.colors import ListedColormap, LinearSegmentedColormap
# Pour changer le paramètre c_x,c_y d'une image fractale, il y a trois fonctions :
"""	def SetParam_Complex(self,z):
	def SetParam_XY(self,x,y):
	def SetParam_tuple(self,tup):
"""
# Pour changer les couleurs, c'est à peu près la même chose :
"""	def SetCol_RGB(self,r,g,b,n):
	def SetCol_tuple(self,tup,n):
 
En notant :
n=0 => couleur de convergence en 0
n=1 => couleur de convergence en 1
n=2 => couleur de divergence en 1
n=3 => couleur de divergence en l'infini
 """

"""étude diversité, op de sélection"""
class ImageFractale:
	""" Exemple de fractale pas trop moche """
	def __init__(self,c3_x=0.5,c3_y=0.123,c2_x=0.42,c2_y=-1.4,c1_x=0.9,c1_y=-0.47,c_x=0.285,c_y=0.01,r_cv_0=200, g_cv_0=155, b_cv_0=155, r_cv_1=55, g_cv_1=190, b_cv_1=155,r_dv_1=50, g_dv_1=100, b_dv_1=0,r_dv_inf=0, g_dv_inf=100, b_dv_inf=50):
		self.c3_x=c3_x
		self.c3_y=c3_y

		self.c2_x=c2_x
		self.c2_y=c2_y

		self.c1_x=c1_x
		self.c1_y=c1_y

		self.c_x=c_x
		self.c_y=c_y

		self.r_cv_0=r_cv_0
		self.g_cv_0=g_cv_0
		self.b_cv_0=b_cv_0

		self.r_cv_1=r_cv_1
		self.g_cv_1=g_cv_1
		self.b_cv_1=b_cv_1

		self.r_dv_1=r_dv_1
		self.g_dv_1=g_dv_1
		self.b_dv_1=b_dv_1

		self.r_dv_inf=r_dv_inf
		self.g_dv_inf=g_dv_inf
		self.b_dv_inf=b_dv_inf

	def __str__(self):
		return str(self.GetParam_XY(3))+';'+str(self.GetParam_XY(2))+';'+str(self.GetParam_XY(1))+';'+str(self.GetParam_XY(0))+';'+str(self.GetCol(0))+';'+str(self.GetCol(1))+';'+str(self.GetCol(2))+';'+str(self.GetCol(3))+'\n'
	
	# Surcharge d'opérateur pour prendre le négatif d'une image : -img
	# Pas nécessairement optimal pour l'instant, je suppose
	def __neg__(self):
		return ImageFractale(self.c3_x,self.c3_y,self.c2_x,self.c2_y,self.c1_x,self.c1_y,self.c_x,self.c_y,255-self.r_cv_0,255-self.g_cv_0,255-self.b_cv_0,255-self.r_cv_1,255-self.g_cv_1,255-self.b_cv_1,255-self.r_dv_1,255-self.g_dv_1,255-self.b_dv_1,255-self.r_dv_inf,255-self.g_dv_inf,255-self.b_dv_inf)

	def Copy(self):
		return ImageFractale(self.c3_x,self.c3_y,self.c2_x,self.c2_y,self.c1_x,self.c1_y,self.c_x,self.c_y,self.r_cv_0,self.g_cv_0,self.b_cv_0,self.r_cv_1,self.g_cv_1,self.b_cv_1,self.r_dv_1,self.g_dv_1,self.b_dv_1,self.r_dv_inf,self.g_dv_inf,self.b_dv_inf)

	# Pour éviter de se trimballer des constantes
	def GetNumCol(self):
		return 4

	# Encapsulation
	def GetParam_Complex(self):
		return complex(self.c_x,self.c_y)

	def GetParam_XY(self,n=0):
		if(n==0):
			return self.c_x,self.c_y
		elif(n==1):
			return self.c1_x,self.c1_y
		elif(n==2):
			return self.c2_x,self.c2_y
		elif(n==3):
			return self.c3_x,self.c3_y

	def GetCol(self,n):
		if(n==0):
			return self.r_cv_0, self.g_cv_0, self.b_cv_0
		elif(n==1):
			return self.r_cv_1, self.g_cv_1, self.b_cv_1
		elif(n==2):
			return self.r_dv_1, self.g_dv_1, self.b_dv_1
		elif(n==3):
			return self.r_dv_inf, self.g_dv_inf, self.b_dv_inf
	
	def SetParam_Complex(self,z):
		self.c_x=z.real
		self.c_y=z.image

	def SetParam_XY(self,x,y,n=0):
		if(n==0):
			self.c_x=x
			self.c_y=y
		elif(n==1):
			self.c1_x=x
			self.c1_y=y
		elif(n==2):
			self.c2_x=x
			self.c2_y=y
		elif(n==3):
			self.c3_x=x
			self.c3_y=y

	def SetParam_tuple(self,tup,n=0):
		try:
			if(n==0):
				self.c_x=tup[0]
				self.c_y=tup[1]
			if(n==1):
				self.c1_x=tup[0]
				self.c1_y=tup[1]
			if(n==2):
				self.c2_x=tup[0]
				self.c2_y=tup[1]
			if(n==3):
				self.c3_x=tup[0]
				self.c3_y=tup[1]
		except ValueError:
			print("2-tuple expected")

	def SetCol_RGB(self,r,g,b,n):
		if(n==0): #Couleur de zone convergente totale
			self.r_cv_0=r
			self.g_cv_0=g
			self.b_cv_0=b
		elif(n==1): #Couleur de zone convergente frontière
			self.r_cv_1=r
			self.g_cv_1=g
			self.b_cv_1=b
		elif(n==2): #couleur de la zone divergente frontière
			self.r_dv_1=r
			self.g_dv_1=g
			self.b_dv_1=b
		elif(n==3): #couleur de la zone divergente infinie
			self.r_dv_inf=r
			self.g_dv_inf=g
			self.b_dv_inf=b
	def SetCol_tuple(self,tup,n):
		try:
			if(n==0):
				self.r_cv_0=tup[0]
				self.g_cv_0=tup[1]
				self.b_cv_0=tup[2]
			elif(n==1):
				self.r_cv_1=tup[0]
				self.g_cv_1=tup[1]
				self.b_cv_1=tup[2]
			elif(n==2):
				self.r_dv_1=tup[0]
				self.g_dv_1=tup[1]
				self.b_dv_1=tup[2]
			elif(n==3):
				self.r_dv_inf=tup[0]
				self.g_dv_inf=tup[1]
				self.b_dv_inf=tup[2]
		except ValueError:
			print('3-tuple expected (RGB-256)')

	# Méthodes
	def WriteToFile(self,file):
		with open(file, 'a') as f:
			f.write('#'+self.__str__())
		f.close()

	# Très mauvais génie logiciel, aïe
	# Interpolation des quatre couleurs.
	"""	def InterpolColour(self):
		c=[(0.0,0.0,0.0,1.0) for i in range(5)]	
		cpt=0
		while(cpt<4):
			c[cpt]=RGB2RGBA(self.GetCol(cpt))
			cpt+=1
		t_couleurs=[c[4] for i in range(256)]
		
		for i in range(10,64):
			t_couleurs[i]=tuple(((1-i/64)*c[4][0]+i/63*c[0][0],(1-i/64)*c[4][1]+i/64*c[0][1],(1-i/64)*c[4][2]+i/64*c[0][2],1.0))
		cpt=1
		while(cpt<4):
			for i in range(64):
				t_couleurs[i + 64*cpt]=tuple(((1-i/64)*c[cpt-1][0]+i/64*c[cpt][0],(1-i/64)*c[cpt-1][1]+i/64*c[cpt][1],(1-i/64)*c[cpt-1][2]+i/64*c[cpt][2],1.0))
			cpt+=1
		return ListedColormap(t_couleurs)
	"""

	def InterpolColour(self):
		colors=[(0.0,0.0,0.0,1.0) for i in range(4)]	
		cpt=0
		while(cpt<4):
			colors[cpt]=RGB2RGBA(self.GetCol(cpt))
			cpt+=1
		cmap1 = LinearSegmentedColormap.from_list("mycmap", colors)
		return cmap1



#Fonctions/Procédures :
#Créer une ImageFractale à partir du n-ème génome du fichier
def NewFromFile(file,n=1):
	i=0
	with open(file,'r') as f:
		while(i<n):
			buff = f.readline()
			if(buff[0]=='#'):
				i+=1
	#Traitement de la chaine de caractères
	tab=buff[1:].split(';') #On exclut le premier caractère de détection
	img=ImageFractale()
	print(eval(tab[0]))
	img.SetParam_tuple(eval(tab[0]),3)
	img.SetParam_tuple(eval(tab[1]),2)
	img.SetParam_tuple(eval(tab[2]),1)
	img.SetParam_tuple(eval(tab[3]),0)
	img.SetCol_tuple(eval(tab[4]),0)
	img.SetCol_tuple(eval(tab[5]),1)
	img.SetCol_tuple(eval(tab[6]),2)
	img.SetCol_tuple(eval(tab[7]),3)
	f.close()
	return img

#Le format pour matplotlib
def RGB2RGBA(rgb_tuple):
	return rgb_tuple[0]/256,rgb_tuple[1]/256,rgb_tuple[2]/256,1

def ImageAleatoire():
	import numpy.random as rd
	rd.seed()
	temp=rd.randint(2)
	c_x,c_y=rd.uniform(-2,2,[2,1])
	c1_x,c1_y=rd.uniform(-2,2,[2,1])
	c2_x,c2_y=rd.uniform(-2,2,[2,1])
	if(temp==0):
		c3_x,c3_y=rd.uniform(-2,2,[2,1])
	else:
		c3_x,c3_y=(0,0)
		
	r_cv_0=rd.randint(256)
	g_cv_0=rd.randint(256)
	b_cv_0=rd.randint(256)

	r_cv_1=rd.randint(256)
	g_cv_1=rd.randint(256)
	b_cv_1=rd.randint(256)

	r_dv_1=rd.randint(256)
	g_dv_1=rd.randint(256)
	b_dv_1=rd.randint(256)

	r_dv_inf=rd.randint(256)
	g_dv_inf=rd.randint(256)
	b_dv_inf=rd.randint(256)

	return ImageFractale(c3_x,c3_y,c2_x,c2_y,c1_x,c1_y,c_x,c_y,r_cv_0,g_cv_0,b_cv_0,r_cv_1,g_cv_1,b_cv_1,r_dv_1,g_dv_1,b_dv_1,r_dv_inf,g_dv_inf,b_dv_inf)

