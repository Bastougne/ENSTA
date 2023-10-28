# Examen_machine_2022
Examen machine du 6 Janvier 2022 : compression d'image parallèle par série de Fourier

**Dans le Makefile, modifier les premières lignes en commentant ou décommentant pour prendre le fichier adapter à votre environnement !**

__Pour ceux en distanciel__ : Pour toute question, envoyer un mail à xjuvigny@gmail.com (plus rapide que juvigny@onera.fr)


-lscpu

Architecture :                          x86_64
Mode(s) opératoire(s) des processeurs : 32-bit, 64-bit
Boutisme :                              Little Endian
Address sizes:                          39 bits physical, 48 bits virtual
Processeur(s) :                         12
Liste de processeur(s) en ligne :       0-11
Thread(s) par cœur :                    2
Cœur(s) par socket :                    6
Socket(s) :                             1
Nœud(s) NUMA :                          1
Identifiant constructeur :              GenuineIntel
Famille de processeur :                 6
Modèle :                                165
Nom de modèle :                         Intel(R) Core(TM) i7-10750H CPU @ 2.60GHz
Révision :                              2
Vitesse du processeur en MHz :          2600.000
Vitesse maximale du processeur en MHz : 5000,0000
Vitesse minimale du processeur en MHz : 800,0000
BogoMIPS :                              5199.98
Virtualisation :                        VT-x
Cache L1d :                             192 KiB
Cache L1i :                             192 KiB
Cache L2 :                              1,5 MiB
Cache L3 :                              12 MiB
Nœud NUMA 0 de processeur(s) :          0-11
Vulnerability Itlb multihit:            KVM: Mitigation: VMX disabled
Vulnerability L1tf:                     Not affected
Vulnerability Mds:                      Not affected
Vulnerability Meltdown:                 Not affected
Vulnerability Spec store bypass:        Mitigation; Speculative Store Bypass disabled via prctl and seccomp
Vulnerability Spectre v1:               Mitigation; usercopy/swapgs barriers and __user pointer sanitization
Vulnerability Spectre v2:               Mitigation; Enhanced IBRS, IBPB conditional, RSB filling
Vulnerability Srbds:                    Not affected
Vulnerability Tsx async abort:          Not affected
Drapaux :                               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc a
                                        rt arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid ss
                                        e4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb invpcid_single ssbd ibrs ibpb stibp ibrs_enh
                                        anced tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid mpx rdseed adx smap clflushopt intel_pt xsaveopt xsavec xge
                                        tbv1 xsaves dtherm ida arat pln pts hwp hwp_notify hwp_act_window hwp_epp pku ospke md_clear flush_l1d arch_capabilities




0) Initialisation :

Se placer dans le dossier sources et lancer "make all"



1) Calcul du temps en séquentiel :

Lancer "./fourier_compression_seq.exe ./data/tiny_lena_gray.png 0.10"

Caracteristique de l'image : 64x64 => 4096 pixels.
durée encodage DFT : 437 ms
Nombre de coefficients de fourier restant : 409
durée sélection coefficients : 0 ms
durée reconstitution image compressée : 59 ms
Fin du programme...

Ce qui correspond à une durée totale de 0.496 s.

Lancer "./fourier_compression_seq.exe ./data/small_lena_gray.png 0.10"

Caracteristique de l'image : 256x256 => 65536 pixels.
durée encodage DFT : 112817 ms
Nombre de coefficients de fourier restant : 6553
durée sélection coefficients : 5 ms
durée reconstitution image compressée : 14576 ms
Fin du programme...

Ce qui correspond à une durée totale de 127.398 s.

Les temps de calcul gardent à peu près les mêmes proportionnalités entre tiny_lena_gray.png et small_lena_gray.png.
On constate donc que la fonction prenant le plus de temps est la fonction d'encodage DFT, qui est environ 7 fois plus lente que la reconstitution de l'image.
La fonction de sélection des coefficients est quant à elle presque instantannée (3000 fois plus rapide que la reconstitution).



2) Parallélisation de l'encodage DFT avec OpenMP

On a effectué une parallélisation OpenMP des 4 boucles qui composent discretTransformFourier, parallélisant ainsi la converion de chaque pixel en série de Fourrier (une valeur complexe).
(Remarque : on avait vu dans un td que la classe std::complex était plutôt lente, on aurait donc pu implémenter la notre afin de réduire les temps de calcul)
Cette fonction fait appel à des fonctions trigonométriques, qui sont très lentes : il est logique que ce soit cette fonction qui soit la plus lente. De plus, elle est constituée de plusieurs boucles for, les 2 premières n'agissant que sur une case du tableau et les 2 autres incrémentant une même case, ce qui permet une parallélisation efficace.

Par défaut, mon ordinateur utilise 12 threads avec OpenMP.

Lancer "./fourier_compression_omp.exe ./data/tiny_lena_gray.png 0.10"

Caracteristique de l'image : 64x64 => 4096 pixels.
durée encodage DFT : 84 ms
Nombre de coefficients de fourier restant : 409
durée sélection coefficients : 0 ms
durée reconstitution image compressée : 68 ms
Fin du programme...

Ce qui correspond à une durée totale de 0.152 s.
On a donc une accélération de 3.2 pour le programme total et de 5.2 pour l'encodage DFT.

Lancer "./fourier_compression_omp.exe ./data/small_lena_gray.png 0.10"

Caracteristique de l'image : 256x256 => 65536 pixels.
durée encodage DFT : 15209 ms
Nombre de coefficients de fourier restant : 6553
durée sélection coefficients : 7 ms
durée reconstitution image compressée : 14397 ms
Fin du programme...

Ce qui correspond à une durée totale de 29.613 s.
On a donc une accélération de 4.3 pour le programme total et de 7.4 pour l'encodage DFT.

Dans les 2 cas, on constate qu'on a une accélération importante, ce qui est cohérent avec nos prévisions. Évidemment, les accélérations sont plus élevées si on ne considère que la fonction parallélisée, mais les accélérations obtenues restent satisfaisantes au vu des ordres de grandeur des temps de calcul des différentes fonctions (cf 1).


3) Parallélisation avec MPI, première version

Par défaut, mon ordinateur utilise 6 processus avec MPI. N'ayant pas le temps de gérer les problèmes de divisibilité, on se contentera de forcer le nombre de procesus à 4.

Lancer "mpiexec -n 4 ./fourier_compression_mpi_1.exe ./data/tiny_lena_gray.png 0.10"

Caracteristique de l'image : 64x64 => 4096 pixels.
durée encodage DFT : 124 ms
Fin du programme...
durée encodage DFT : 124 ms
durée encodage DFT : 124 ms
Fin du programme...
durée encodage DFT : 124 ms
Fin du programme...
Nombre de coefficients de fourier restant : 409
durée sélection coefficients : 0 ms
durée reconstitution image compressée : 65 ms
Fin du programme...

Ce qui correspond à une durée totale de 0.189 s.
On a donc une accélération de 2.6 pour le programme total et de 3.5 pour l'encodage DFT.

Lancer "mpiexec -n 4 ./fourier_compression_mpi_1.exe ./data/small_lena_gray.png 0.10"

Caracteristique de l'image : 256x256 => 65536 pixels.
durée encodage DFT : 30593 ms
Fin du programme...
durée encodage DFT : 30593 ms
Fin du programme...
durée encodage DFT : 30593 ms
durée encodage DFT : 30593 ms
Fin du programme...
Nombre de coefficients de fourier restant : 6553
durée sélection coefficients : 5 ms
durée reconstitution image compressée : 15515 ms
Fin du programme...

Ce qui correspond à une durée totale de 46.113 s.
On a donc une accélération de 2.7 pour le programme total et de 3.7 pour l'encodage DFT.

Cette parallélisation est similaire à la précédente, on retrouve donc des efficacités similaires (l'accélération est inférieure pour cette version car on a moins de processus que dans la version 1).


3) Parallélisation avec MPI, deuxième version

Remarque : La première partie de l'énoncé me semble claire, il faut paralléliser la boucle portant sur n2. Cependant, la seconde partie est moins claire, et je crois qu'il y a une erreur mathématique derrière (les max d'un ensemble ne sont pas les max des max des sous-ensemble puisqu'on prend à chaque fois un nombre de max constant). Dans tous les cas, cette partie ne prend que 5 ms pour small_lena_gray donc ce n'est pas très important ...

Lancer "mpiexec -n 4 ./fourier_compression_mpi_2.exe ./data/tiny_lena_gray.png 0.10"

Caracteristique de l'image : 64x64 => 4096 pixels.
durée encodage DFT : 146 ms
Fin du programme...
durée encodage DFT : 146 ms
Fin du programme...
durée encodage DFT : 146 ms
Fin du programme...
durée encodage DFT : 146 ms
Nombre de coefficients de fourier restant : 409
durée sélection coefficients : 0 ms
durée reconstitution image compressée : 67 ms
Fin du programme...

Ce qui correspond à une durée totale de 0.213 s.
On a donc une accélération den 2.3 pour le programme total et de 3.0 pour l'encodage DFT.