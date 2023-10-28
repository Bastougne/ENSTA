from tkinter import *
from functools import partial
from plt_diversite import *
import generation_images as g_i
import julia
import mutation
import image_fractale as fract
import time
from creat_image import creer_julia
import calcul_diversite



# constantes de couleurs
BG_COLOUR = '#363636'
TEXT_COLOUR = '#000'
BUTTON_COLOUR = '#ECECEC'
ACTIVATED_BUTTON_COLOUR = '#9C9C9C'

# taille des images 
IMAGE_WIDTH = 300
IMAGE_HEIGHT = 300

# taille des images pour le rendu final
IMAGE_WIDTH_FINAL = 700
IMAGE_HEIGHT_FINAL = 700

# police d'ecriture
FONT = "Comic Sans MS"

#Enregistrer la meilleure sous format fond d'écran 1920x1080
WALLPAPER=False


# met à jour la note correspondant à la fractale dans le fichier notes.txt
def res_button(button_position):
	for k in range(6):
		# remise à la couleur d'origine des autres boutons du groupement (en cas de changement d'avis)
		buttons[button_position[0]][button_position[1]][k].config(bg=BUTTON_COLOUR)
	buttons[button_position[0]][button_position[1]][button_position[2]].config(bg=ACTIVATED_BUTTON_COLOUR)

	# écriture de la note dans le fichier (en lignes)
	fichierNotes = open('notes.txt', 'r')
	lignes = fichierNotes.readlines()
	# modification de la ligne correspondant à la note changée
	lignes[4*button_position[0] + button_position[1]] = str(button_position[2]) + '\n'
	fichierNotes.close()
	fichierNotes = open('notes.txt', 'w')
	fichierNotes.writelines(lignes)
	fichierNotes.close()


# renvoie les notes si elles ont toutes été données et que l'on a appuyé sur le bouton de validation
def refresh_page(fractales_t):
	fractales_t.SetNoteFromFile()
	#Un peu lent
	fractales_t.EnregistrerMeilleure(wallpaper=WALLPAPER)
	fractales_t.AjoutMeilleureAuFichier()
	fractales_t.NouvelleGeneration()
	calcul_diversite.actualiser_diversite(fractales_t)
	
	for i in range(2):
		for j in range(4):
			# reset des images
			images[i][j] = PhotoImage(file='fractale_'+str(i)+'_'+str(j)+'.png')
			canvas[i][j].create_image(IMAGE_WIDTH//2, IMAGE_HEIGHT//2, image=images[i][j])
			# reset de la couleur des boutons
			for k in range(6):
				buttons[i][j][k].config(bg=BUTTON_COLOUR)
	window.mainloop()


# efface tout et affiche la meilleure fractale finale (en argument : GroupeImage)
def fin(fractales_t):
	# suppression des deux cadres 
	centralframe.destroy()
	frame_validation_stop.destroy()

	# genere la nouvelle fenetre (image taille reelle + bouton d'arret definitif)
	frame_image_finale = Frame(window, bg=BG_COLOUR)
	image_finale = PhotoImage(file='best_fractale.png')
	canvas_image_finale = Canvas(frame_image_finale, bg=BG_COLOUR, width=IMAGE_WIDTH_FINAL, height=IMAGE_HEIGHT_FINAL)
	canvas_image_finale.create_image(IMAGE_WIDTH_FINAL//2, IMAGE_HEIGHT_FINAL//2, image=image_finale)
	canvas_image_finale.pack()

	frame_button = Frame(window, bg=BG_COLOUR)
	quit_button = Button(frame_button, text='Quitter', font=(FONT, 30), bg=BUTTON_COLOUR, fg=TEXT_COLOUR, command=arreter)
	quit_button.pack()

	frame_image_finale.pack(expand=YES)
	frame_button.pack(expand=YES)
	window.mainloop()


# arrete definitivement (accessible dans la fenetre d'affichage finale)
def arreter():
	window.destroy()



# INITIALISATION
fractales=[fract.ImageAleatoire() for i in range(8)]

#mutation.RandomMutation(fractales[1],0.02,70,0.8 , nb_bits=1)
fractales_t=g_i.GroupeImage(fractales)
#fractales_t.Mutation()
fractales_t.EnregistrerImages('fractale')



# GENERATION DES WIDGETS

# initialisation et personnalisation de la fenêtre
window = Tk()
window.title("Fractales génétiques")
window.geometry("1920x1080") # taille par défaut
img = PhotoImage(file='icone.png')  # logo fenêtre
window.tk.call('wm', 'iconphoto', window._w, img)
window.config(background='#363636')

# frame centrale contenant celles contenant les images et les boutons de notation 
centralframe = Frame(window, bg=BG_COLOUR)
# frames contenant les boutons de validation et d'arrêt
frame_validation_stop = Frame(window, bg=BG_COLOUR)

# frames contenant les images et les boutons de notation
frames = []
for i in range(4):
	frames.append([])
	for j in range(4):
		frames[i].append(Frame(centralframe, bg=BG_COLOUR))



# boutons validation finale, arrêt et affichage de la diversite
validation_button = Button(frame_validation_stop, text='Valider', font=(FONT, 30), bg=BUTTON_COLOUR, fg=TEXT_COLOUR, command=partial(refresh_page,fractales_t))
validation_button.grid(row=0, column=1, padx=50)
stop_button = Button(frame_validation_stop, text='Arrêter', font=(FONT, 30), bg=BUTTON_COLOUR, fg=TEXT_COLOUR, command=partial(fin,fractales_t))
stop_button.grid(row=0, column=0, padx=50)
stop_button = Button(frame_validation_stop, text='Visualiser la diversité', font=(FONT, 30), bg=BUTTON_COLOUR, fg=TEXT_COLOUR, command=afficher_diversite)
stop_button.grid(row=0, column=2, padx=50)

# boutons de notation
buttons = []
# les lignes 1 et 3 correspondent aux boutons
for i in [1,3]:
	buttons.append([])
	for j in range(4):
		# on se ramène à 0,1 correspondant aux positions dans les listes (1->0, 3->1)
		i_liste = (i-1)//2
		buttons[i_liste].append([])
		for k in range(6):
			buttons[i_liste][j].append(Button(frames[i][j], text=str(k), font=(FONT, 30), bg=BUTTON_COLOUR, fg=TEXT_COLOUR, activebackground=ACTIVATED_BUTTON_COLOUR, command=partial(res_button, [i_liste,j,k])))



# images 
images = []
canvas = []
# les lignes 0 et 2 correspondent aux images
for i in [0,2]:
	images.append([])
	canvas.append([])
	for j in range(4):
		# comme pour les buttons (ici : 0->0, 2->1)
		i_liste = i//2
		images[i_liste].append(PhotoImage(file='fractale_'+str(i_liste)+'_'+str(j)+'.png'))
		canvas[i_liste].append(Canvas(frames[i][j], bg=BG_COLOUR, width=IMAGE_WIDTH, height=IMAGE_HEIGHT))
		canvas[i_liste][j].create_image(IMAGE_WIDTH//2, IMAGE_HEIGHT//2, image=images[i_liste][j])



# AFFICHAGE DES WIDGETS
for i in range(2):
	for j in range(4):
		canvas[i][j].pack()

for i in range(2):
	for j in range(4):
		for k in range(6):
			buttons[i][j][k].grid(row=1, column=k)

for i in range(4):
	for j in range(4):
		frames[i][j].grid(row=i, column=j, padx=20, pady=20)

centralframe.pack(expand=YES)
frame_validation_stop.pack(expand=YES)

window.mainloop()
