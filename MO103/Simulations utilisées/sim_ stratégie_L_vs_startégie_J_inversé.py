import pygame as pg  
import math as mt

pi=mt.pi
sin=mt.sin
cos=mt.cos
tan=mt.tan
sqrt=mt.sqrt



Blanc=(255,255,255)
Noir=(0,0,0)
Bleu=(0,0,255)
Rouge=(255,0,0)

###paramètres de la sim
pas_de_temps=100#en ms
vitesse_trans= 9.47*4.8*pas_de_temps*0.001#en pixel par pas_de_temps (pensez que 480 pixels=100cm)
vitesse_rot = 2*pi/7.5*pas_de_temps*0.001#en radian par pas_de_temps
portée_capteur=96
###fin des paramètres



def f(x,y,theta,R):
	return (round(R*cos(theta)+x),round(R*sin(theta)+y))

def distance(p1,p2):
	x=p1[0]
	y=p1[1]
	w=p2[0]
	z=p2[1]

	return sqrt((x-w)**2+(y-z)**2)

def param_droite(x,y,theta):
	return (cos(theta),-sin(theta),sin(theta)*x-cos(theta)*y)


def inter_cercle_droite(R,a,b,c,x1,y1):
	
	c_bis=c+a*y1+b*x1
	delta_x=R**2*(b**2+a**2)-a**2*c_bis**2##j'ai divisé par 4a**2 le vrai determinant
	delta_y= delta_x+c_bis**2*(a**2-b**2)
	

	return (delta_x>=0 and delta_y>=0)

#####Les stratégies à étudier
## V_t est la vitesse de translation actuelle dans la direction du capteur; 
## V_r est la vitesse de rotation actuelle (orienté sens horaire)
##detection=1 si le capteur détecte l'autre robot dans sa portée, 0 sinon.
##sortie =1 si le capteur est en dehors du terrain
##save est un tableau où on peut stocker les variables de la stratégie
##Les fonctions renvoient la nouvelle vitesse de translation et de rotation 
## et les variables propres à la sim stocker dans save.

def strategie1(V_t,V_r,detection,sortie,save):
		
		vitesse_trans_lente = (3/4)*vitesse_trans 
		vitesse_rot_lente = (3/4)*vitesse_rot
		
		if len(save)==0:
			save=[0,0,0]
		
		
		if save[2]==0:##s'aligner au coté
			save[1]+=vitesse_rot_lente
			if save[1]>pi/4-vitesse_rot_lente:
				save[2]=1
				save[1]=0
			return 0,vitesse_rot_lente,save

		if save[2]==1:##avancer jusqu'à la moitié
			save[0]+=vitesse_trans

			if save[0]>120-vitesse_trans:###moitié du terrain à partir du depart ; (92,92) est la position de départ du robot
				save[2]=2
				save[0]=0
			return vitesse_trans,0,save

		if save[2]==2:##pivoter vers le centre
			save[1]-=vitesse_rot_lente
			if save[1]<-pi/2+vitesse_rot_lente:
				save[2]=3
				save[1]=0
			return 0,-vitesse_rot_lente,save


		if save[2]==3:##avancer jusqu'au centre
			save[0]+=vitesse_trans
			if save[0]>120-vitesse_trans:#idem a partir de l'ordonnée de depart
				save[2]=4
				

			if detection:
				save[2]=4
				save[0]=0
				

			return vitesse_trans,0,save##on garde la mesure de la distance parcourue pour que dans la phase assault on passe tout de suite au balayage
		
		
		if save[2]==4:##assault


			if sortie:
				return 0,0,[0,0,7]

			if detection:
				return vitesse_trans,0,[0,0,4]


			
			if save[0]<portée_capteur-vitesse_trans:
				save[0]+=vitesse_trans
				return vitesse_trans,0,save


			return 0,0,[0,0,6]




		if save[2]==5:##balayage gauche
			if detection:
				return 0,0,[0,0,4]

			if save[1]>-2*pi/2+vitesse_rot:
				save[1]-=vitesse_rot
				
			else:
				save[2]=4
				save[1]=0

			return 0,-vitesse_rot,save


		if save[2]==6:#balayage droite
			if detection:
				return 0,0,[0,0,4]

			if save[1]<pi/2-vitesse_rot:
				save[1]+=vitesse_rot
			else:
				save[2]=5
				save[1]=0

			return 0,vitesse_rot,save

		if save[2]==7:##sortie
			if save[0]>-portée_capteur/2+vitesse_trans:
				save[0]-=vitesse_trans
				return -vitesse_trans,0,save
			
			if save[1]>-pi+vitesse_rot:

				if detection:
					return vitesse_trans,0,[0,0,4]

				save[1]-=vitesse_rot
				return 0,-vitesse_rot,save
			

			

			

			return 0,0,[0,0,5]
	


def strategie2(V_t,V_r,detection,sortie,save):

		if len(save) == 0:
			save = [0,0,0]
			
		if save[0]==0: ##save[0] = état dans lequel on est 
			if save[1] < pi/4 : ##save[1] = angle
				save[1] += vitesse_rot
				return 0,-vitesse_rot,save
			else:
				save[0] = 1 
				save[1] = 0
				return vitesse_trans,0,save
		
		elif save[0]==1: ##save[0] = état dans lequel on est 
			if save[2] < 300 : ##save[2] = distance
				save[2] += vitesse_trans
				return vitesse_trans,0,save
			else:
				save[0] = 2 
				save[2] = 0
				return 0,vitesse_rot,save
				
		elif save[0]==2: ##save[0] = état dans lequel on est 
			if save[1] < pi/2 : ##save[1] = angle
				save[1] += vitesse_rot
				return 0,vitesse_rot,save
			else:
				save[0] = 3 
				save[1] = 0
				return vitesse_trans,0,save
				
		elif save[0]==3: ##save[0] = état dans lequel on est 
			if save[2] < 180 : ##save[2] = distance
				save[2] += vitesse_trans
				return vitesse_trans,0,save
			else:
				save[0] = 4 
				save[2] = 0
				return 0,vitesse_rot,save
		
		elif save[0]==4: ##save[0] = état dans lequel on est 
			if save[1] < pi/2 : ##save[1] = angle
				save[1] += vitesse_rot
				return 0,vitesse_rot,save
			else:
				save[0] = 5 
				save[1] = 0
				return vitesse_trans,0,save
		
		elif save[0]==5: ##save[0] = état dans lequel on est 
			if save[2] < 180 : ##save[2] = distance
				save[2] += vitesse_trans
				return vitesse_trans,0,save
			else:
				save[0] = 6 
				save[2] = 0
				return 0,0,save
		
			
		return 0,0,save
#############




def sim(R1=41,R2=41):

	pg.init()

	screen = pg.display.set_mode((480,480)) #480=100cm
	clock_prece= pg.time.get_ticks()
	clock=clock_prece

	continuer=True
	
	posX1=round(130/sqrt(2))
	posY1=round(130/sqrt(2))
	vX1=0
	vY1=0

	posX2=480-round(130/sqrt(2))
	posY2=480-round(130/sqrt(2))
	vX2=0
	vY2=0

	or1=pi/4 #attention en python ça tourne dans le sens  horaire
	or2=-3*pi/4

	detection1=0
	detection2=0
	sortie1=0
	sortie2=0

	### save robot
	save1=[]
	save2=[]

	#déclaration des vitesses
		
	vit_tr_1=0
	vit_tr_2=0
	vit_rot_1=0
	vit_rot_2=0

	#condition de contact	
	
			
	while(continuer):

		

		for event in pg.event.get():

			if event.type== pg.QUIT:
				continuer=False

		
		if distance((posX1,posY1),(posX2,posY2))<=R1+R2:

			print("\ncontact\n")
			while(continuer):

				for event in pg.event.get():

					if event.type== pg.QUIT:
						continuer=False


			
		

		#condition de sortie
		if posX1+R1<0 or posX1-R1>480 or posY1+R1<0 or posY1-R1>480:

				
				print("\nR1 perd\n")
				while(continuer):

					for event in pg.event.get():

						if event.type== pg.QUIT:
							continuer=False


		if posX2+R2<0 or posX2-R2>480 or posY2+R2<0 or posY2-R2>480:

				
				print("\nR2 perd\n")
				while(continuer):

					for event in pg.event.get():

						if event.type== pg.QUIT:
							continuer=False


		###detection de l'autre
		if distance((posX1,posY1),(posX2,posY2))<=R1+R2+portée_capteur:
			a1,b1,c1 = param_droite(posX1,posY1,or1)
			a2,b2,c2 = param_droite(posX2,posY2,or2)

			
			if(inter_cercle_droite(R2,a1,b1,c1,posX2,posY2) and (cos(or1)*(posX2-posX1)>=0 and sin(or1)*(posY2-posY1)>=0 ) ):
				detection1=1
			
			else:
				detection1=0

			if(inter_cercle_droite(R1,a2,b2,c2,posX1,posY1) and (cos(or2)*(posX1-posX2)>=0 and sin(or2)*(posY1-posY2)>=0 ) ):
				detection2=1

			else:
				detection2=0

		else:
				detection1=0
				detection2=0

			
		##.

		##detection de sortie
		if posX1+R1*cos(or1)<0 or posX1+R1*cos(or1)>480 or posY1+R1*sin(or1)<0 or posY1+R1*sin(or1)>480:

				sortie1=1
		else:
				sortie1=0

		
		if posX2+R2*cos(or2)<0 or posX2+R2*cos(or2)>480 or posY2+R2*sin(or2)<0 or posY2+R2*sin(or2)>480:

				sortie2=1
		else:
				sortie2=0
		##



		clock=pg.time.get_ticks()
		
		if(clock-clock_prece>pas_de_temps):
			clock_prece=clock

			vit_tr_1, vit_rot_1,save1= strategie1(vit_tr_1, vit_rot_1,detection1,sortie1,save1)
			vit_tr_2, vit_rot_2,save2= strategie2(vit_tr_2, vit_rot_2,detection2,sortie2,save2)

			vX1=vit_tr_1*cos(or1)
			vY1=vit_tr_1*sin(or1)
			vX2=vit_tr_2*cos(or2)
			vY2=vit_tr_2*sin(or2)
			

			posX1+=vX1
			posY1+=vY1
			posX2+=vX2
			posY2+=vY2

			or1+=vit_rot_1
			or1=or1%(2*pi)
			
			or2+=vit_rot_2
			or2=or2%(2*pi)
			


		screen.fill(Blanc)
		pg.draw.circle(screen,Bleu,(round(posX1),round(posY1)) ,R1) #robot circulaire de 10cm de diam
		pg.draw.line(screen,Rouge,(round(posX1),round(posY1)), f(posX1,posY1,or1,R1)) 
		pg.draw.circle(screen,Noir,(round(posX2),round(posY2)),R2) #robot circulaire de 10cm de diam
		pg.draw.line(screen,Rouge,(round(posX2),round(posY2)), f(posX2,posY2,or2,R2)) 
		pg.draw.line(screen,Rouge,(round(posX1)+R1*cos(or1),round(posY1)+R1*sin(or1)), f(posX1,posY1,or1+pi/4,96))
		pg.draw.line(screen,Rouge,(round(posX1)+R1*cos(or1),round(posY1)+R1*sin(or1)), f(posX1,posY1,or1-pi/4,96))
		pg.display.flip()
		

	pg.quit()

sim()


