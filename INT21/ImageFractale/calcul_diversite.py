import matplotlib.pyplot as plt

liste_fitness = []
liste_fitness_X = []
liste_moyenne = []
liste_moyenne_X = []
GENERATION = 0


def actualiser_diversite(fractales):
	global GENERATION
	plt.close("all")
	plt.rcParams.update({"axes.edgecolor":"w", "xtick.color":"w", "ytick.color":"w"})
	plt.figure(0)
	couleur = ["ko","bo","ro","go"]
	for i in range(8):
		coefs_x = []
		coefs_y = []
		for n in range(4):
			(x, y) = fractales.GetImageFractale(i).GetParam_XY(n)
			plt.plot(x, y,couleur[n])

	plt.title("Diversité génome", color="w")
	plt.legend(["coefficient de degré 0", "coefficient de degré 1", "coefficient de degré 2", "coefficient de degré 3"])
	plt.xlim([-2,2])
	plt.ylim([-2,2])
	plt.xlabel("partie réelle", color="w")
	plt.ylabel("partie imaginaire", color="w")
	plt.savefig("diversite_genome.png", facecolor=(0, 0, 0, 0))

	plt.figure(1)
	fichierNotes = open("notes.txt","r")
	lignes = fichierNotes.readlines()
	for i in range(8):
		liste_fitness.append(int(lignes[i][0]))
		liste_fitness_X.append(GENERATION)
	liste_moyenne.append(sum(liste_fitness)/len(liste_fitness))
	liste_moyenne_X.append(GENERATION)
	plt.plot(liste_fitness_X, liste_fitness, "bo")
	plt.plot(liste_moyenne_X, liste_moyenne, "r-")

	plt.title("Diversité fitness", color="w")
	plt.legend(["fitness", "moyenne"])
	plt.xlim([-1,GENERATION + 1])
	plt.ylim([-1,6])
	plt.xlabel("génération", color="w")
	plt.ylabel("fitness", color="w")
	plt.savefig("diversite_fitness.png", facecolor=(0, 0, 0, 0))
	plt.close("all")

	GENERATION += 1