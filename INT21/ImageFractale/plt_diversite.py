from tkinter import *


# CORRESPOND A UNE FENETRE ANNEXE DESTINEE A VISUALISER LA DIVERSITE



# constante de couleur
BG_COLOUR = '#363636'
BUTTON_COLOUR = '#ECECEC'
TEXT_COLOUR = '#000'

# constante taille des plots
IMAGE_WIDTH_DIVERSITE = 640
IMAGE_HEIGHT_DIVERSITE = 480

# police d'écriture
FONT = "Comic Sans MS"





# GENERATION DES WIDGETS

def afficher_diversite():


	# permet de quitter la fenetre d'affichage de la diversite
	def quitter_diversite():
		window_diversite.destroy()



	# initialisation et personnalisation de la fenêtre
	window_diversite = Toplevel()
	window_diversite.title("Visualisation de la diversité")
	window_diversite.geometry("1920x1080") # taille par défaut
	window_diversite.config(background='#363636')


	main_frame = Frame(window_diversite, bg=BG_COLOUR)
	# frame diversité du génome
	frame1 = Frame(main_frame, bg=BG_COLOUR)
	canvas1 = Canvas(frame1, bg=BG_COLOUR, width=IMAGE_WIDTH_DIVERSITE, height=IMAGE_HEIGHT_DIVERSITE)
	image1 = PhotoImage(file='diversite_genome.png')
	canvas1.create_image(IMAGE_WIDTH_DIVERSITE//2, IMAGE_HEIGHT_DIVERSITE//2, image=image1)
	canvas1.pack(expand=YES)
	# frame diversité du fitness
	frame2 = Frame(main_frame, bg=BG_COLOUR)
	canvas2 = Canvas(frame2, bg=BG_COLOUR, width=IMAGE_WIDTH_DIVERSITE, height=IMAGE_HEIGHT_DIVERSITE)
	image2 = PhotoImage(file='diversite_fitness.png')
	canvas2.create_image(IMAGE_WIDTH_DIVERSITE//2, IMAGE_HEIGHT_DIVERSITE//2, image=image2)
	canvas2.pack(expand=YES)


	# bouton de sortie 
	frame_button_quit = Frame(window_diversite, bg=BG_COLOUR)
	quit_button = Button(frame_button_quit, text='Quitter', font=(FONT, 30), bg=BUTTON_COLOUR, fg=TEXT_COLOUR, command=quitter_diversite)
	quit_button.pack()


	# affichage
	frame1.grid(row=0, column=0, padx=85)
	frame2.grid(row=0, column=1, padx=85)


	main_frame.pack(expand=YES)
	frame_button_quit.pack(expand=YES)


	window_diversite.mainloop()







