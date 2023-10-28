import image_fractale as fract
import mutation as mut
import creat_image as c_i
import numpy as np
import operator

#Variables globales
NB_FRACT=8
P_MUT=0.20
F_NOTES="notes.txt"
N_BEST="best_fractale.png"
N_BEST_TXT="best_fractale.txt"
MAX_NOTE=5

INDEX_ERROR="Wrong index, must be between 0 and "+str(NB_FRACT-1)

#Fonction de probabilité discrète 
def proba_survie(note):
	return (note+1)/(MAX_NOTE+2)
# 6/7
# 5/7
# 4/7
# 3/7
# 2/7
# 1/7 = 14.7%


"""Classe qui contient NB_FRACT ImageFractale sous forme d'un tableau et les notes"""
class GroupeImage:
	def __init__(self,img_fract_t=[fract.ImageFractale() for j in range(NB_FRACT)],img_fract_note_t=[0 for i in range(NB_FRACT)]):
		self.img_fract_t=img_fract_t
		self.img_fract_note_t=img_fract_note_t

	def GetImageFractale(self,n=-1):
		if(n>=0):
			try:
				return self.img_fract_t[n]
			except:
				print("GetImageFractale: ", INDEX_ERROR)
		return self.img_fract_t

	def SetImageFractale(self,img_fract,n=-1):
		if(n>=0):
			try:
				self.img_fract_t[n]=img_fract
			except:
				print("SetImageFractale: ",INDEX_ERROR)
		
		else:
			self.img_fract_t=img_fract
	def GetNote(self,n=-1):
		if(n>=0):
			try:
				return self.img_fract_note_t[n]
			except:
				print("GetNote: ", INDEX_ERROR)
		return self.img_fract_note_t

	"""note=0,n=-1 correspond à un reset """
	def SetNote(self,note=0,n=-1):
		if(n>=0):
			try:
				self.img_fract_note_t[n]=note
			except:
				print("SetNote: ", INDEX_ERROR)
		else:
			self.img_fract_note_t=[0 for i in range(NB_FRACT)]

	def SetNoteFromFile(self,nom=F_NOTES):
		with open(nom,'r') as f:
			i=0
			while(i<NB_FRACT):
				buff = f.read(1)
				if(buff.isdigit()):
					self.SetNote(int(buff),i)
					i+=1

	def Copy(self):
		return GroupeImage(self.GetImageFractale(),self.GetNote())

	#Sélection et crossover
	def Crossover(self,proba_note=proba_survie):
		import random
		np.random.seed()
		diviseur=2.0
		#SELECTION
		nb_survivants=0
		new_gen=self.Copy()
		for i in range(NB_FRACT):
			temp=np.random.random()
			#Survit
			if(temp<=proba_note(self.GetNote(i))):
				new_gen.SetImageFractale(self.GetImageFractale(i),nb_survivants)
				nb_survivants+=1

		#CROSSOVER:
		nb_remplis=nb_survivants #On veut une génération de NB_FRACT individus
		nb_bebes=(NB_FRACT-nb_remplis)//2
		nb_nouveaux=NB_FRACT-nb_bebes-nb_remplis
		i_bebes=0
		i_nouveaux=0
		while(i_bebes<nb_bebes):
			l,j=random.sample(range(nb_survivants),2)
			fract1=self.GetImageFractale(l)
			fract2=self.GetImageFractale(j)
			#Le bébé issu du crossover
			new_fract=fract1.Copy()
			#simple moyenne:
			for k in range(4):
				addition=tuple(map(operator.add,fract1.GetParam_XY(k),fract2.GetParam_XY(k)))
				new_fract.SetParam_tuple(tuple(map(lambda x: x/diviseur, addition)),k)
				#new_fract.SetCol_tuple()
			new_gen.SetImageFractale(new_fract,nb_remplis+i_bebes)
			i_bebes+=1
		while(i_nouveaux<nb_nouveaux):
			new_fract=fract.ImageAleatoire()
			new_gen.SetImageFractale(new_fract,nb_remplis+i_bebes+i_nouveaux)
			i_nouveaux+=1

		return new_gen

	def Mutation(self):
		np.random.seed()
		for i in range(NB_FRACT):
			mut.RandomMutation(self.img_fract_t[i],0.01,70,P_MUT,1)

	#Change l'ancienne génération en une nouvelle
	def NouvelleGeneration(self):
		new_gen = self.Crossover()
		new_gen.Mutation()
		self=new_gen
		self.EnregistrerImages("fractale")
		
	
	#ATTENTION: Pour l'instant, ne s'occupe pas de vérifier les doublons.
	def AjoutMeilleureAuFichier(self,nom=N_BEST_TXT):
		i_max=np.argmax(self.GetNote())
		best_fract=self.GetImageFractale(i_max)
		"""#Ajout au fichier texte:
		with open(nom, 'a') as f:
			f.write('#'+self.GetImageFractale(i_max).__str__()+'\n')
		f.close()"""
		self.GetImageFractale(i_max).WriteToFile(nom)

	#Enregistre les 8 fractales sous petit format
	def EnregistrerImages(self, nom):
		for i in range(NB_FRACT):
			fichier=nom+'_'+str(i//(NB_FRACT//2))+'_'+str(i%(NB_FRACT//2))
			c_i.creer_julia(self.GetImageFractale(i),fichier)

	#Enregistre la meilleure fractale de la dernière génération. On peut la faire sous former fond d'écran ou non
	def EnregistrerMeilleure(self,wallpaper=True):
		i_max=np.argmax(self.GetNote())
		best_fract=self.GetImageFractale(i_max)
		
		#Agrandissement :
		c_i.creer_julia(best_fract,nom=N_BEST,xn=700,yn=700,dpi=70)
		#fond d'écran :
		if(wallpaper):
			c_i.creer_julia(best_fract,nom="wallpaper.png",xn=3840,yn=2160,dpi=10,width=192,height=108)

"""
img_fract_t=[fract.ImageFractale() for i in range(NB_FRACT)]
gp=GroupeImage(img_fract_t)
gp.EnregistrerImages('fractale')"""