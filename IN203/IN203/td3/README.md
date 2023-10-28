

# TP3 de HUBERT Bastien

`pandoc -s --toc tp2.md --css=./github-pandoc.css -o tp2.html`


## lscpu

```
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
Nom de modèle :                         Intel(R) Core(TM) i7-10750H CPU @ 2.60GH
                                        z
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
Vulnerability Spec store bypass:        Mitigation; Speculative Store Bypass dis
                                        abled via prctl and seccomp
Vulnerability Spectre v1:               Mitigation; usercopy/swapgs barriers and
                                         __user pointer sanitization
Vulnerability Spectre v2:               Mitigation; Enhanced IBRS, IBPB conditio
                                        nal, RSB filling
Vulnerability Srbds:                    Not affected
Vulnerability Tsx async abort:          Not affected
Drapaux :                               fpu vme de pse tsc msr pae mce cx8 apic 
                                        sep mtrr pge mca cmov pat pse36 clflush 
                                        dts acpi mmx fxsr sse sse2 ss ht tm pbe 
                                        syscall nx pdpe1gb rdtscp lm constant_ts
                                        c art arch_perfmon pebs bts rep_good nop
                                        l xtopology nonstop_tsc cpuid aperfmperf
                                         pni pclmulqdq dtes64 monitor ds_cpl vmx
                                         est tm2 ssse3 sdbg fma cx16 xtpr pdcm p
                                        cid sse4_1 sse4_2 x2apic movbe popcnt ts
                                        c_deadline_timer aes xsave avx f16c rdra
                                        nd lahf_lm abm 3dnowprefetch cpuid_fault
                                         epb invpcid_single ssbd ibrs ibpb stibp
                                         ibrs_enhanced tpr_shadow vnmi flexprior
                                        ity ept vpid ept_ad fsgsbase tsc_adjust 
                                        bmi1 avx2 smep bmi2 erms invpcid mpx rds
                                        eed adx smap clflushopt intel_pt xsaveop
                                        t xsavec xgetbv1 xsaves dtherm ida arat 
                                        pln pts hwp hwp_notify hwp_act_window hw
                                        p_epp pku ospke md_clear flush_l1d arch_
                                        capabilities
```

*Des infos utiles s'y trouvent : nb core, taille de cache*



## Produit scalaire 

*Expliquer les paramètres, les fichiers, l'optimisation de compil, NbSamples, ...*

OMP_NUM    | samples=1024 | x
-----------|--------------|----------
séquentiel |  0.526566    | 1
1          |  0.532849    | 1
2          |  0.540836    | 1
3          |  0.536051    | 1
4          |  0.530526    | 1
8          | 0.539356     | 1


*Discuter sur ce qu'on observe, la logique qui s'y cache.*

On est memory bound donc on ne peut pas vraiment augmenter les performances avec de la parallélisation.


## Produit matrice-matrice



### Permutation des boucles

*Expliquer comment est compilé le code (ligne de make ou de gcc) : on aura besoin de savoir l'optim, les paramètres, etc. Par exemple :*

`make TestProductMatrix.exe && ./TestProductMatrix.exe 1024`


sans pragma omp parallel

  ordre           | time    | MFlops  | time (n=2048) | MFlops(n=2048) 
------------------|---------|---------|---------------|---------------
i,j,k (origine)   | 2.38049 | 902.117 | 78.7399       | 218.185
j,i,k             | 2.61483 | 821.269 | 77.0003       | 223.114
i,k,j             | 9.06208 | 236.975 | 274.439       | 62.6
k,i,j             | 8.81982 | 243.484 | 
j,k,i             | 0.67955 | 3071.45 | 6.72289       | 2555.43
k,j,i             | 0.73192 | 2934.04 | 7.09174       | 2422.52


avec pragma omp parallel

  ordre           | time    | MFlops  | time (n=2048) | MFlops(n=2048) 
------------------|---------|---------|---------------|---------------
i,j,k (origine)   | 0.71699 | 2995.14 | 29.1304       | 589.758
j,i,k             | 0.66693 | 3219.95 | 23.8999       | 718.827
i,k,j             | 2.57088 | 835.312 | 67.9874       | 252.692
k,i,j             | failed  | failed  | failed        | failed
k,i,j k not para  | 1.62073 | 1325.01 | 64.2422       | 267.423
j,k,i             | 0.15305 | 14031.6 | 0.96676       | 17770.6
k,j,i             | failed  | failed  | failed        | failed
k,j,i k not para  | 0,20296 | 8713.02 | 4.16808       | 4121.77


Il faut que la boucle en i soit à l'intérieur car le stockage des matrices se fait en colonne, donc si cette boucle
est externe, on va effectuer beaucoup de sauts de mémoire.

### OMP sur la meilleure boucle 

`make TestProductMatrix.exe && OMP_NUM_THREADS=8 ./TestProductMatrix.exe 1024`

  OMP_NUM         | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
------------------|---------|----------------|----------------|---------------
1                 | 3096.52 | 2586.97        | 2782.66        | 2458.19
2                 | 5996.55 | 5013.32        | 5323.24        | 4816.24
3                 | 8535.49 | 7523.53        | 6745.12        | 7374.68
4                 | 9253.18 | 9564.3         | 8384.64        | 9201.37
5                 | 10701.9 | 10947.3        | 6858.61        | 10761.7
6                 | 11351.4 | 11880.9        | 7942.76        | 11703.5
7                 | 10424.5 | 10632.1        | 9132.7         | 10107.3
8                 | 11292.2 | 11807.7        | 10554.7        | 11388.0


### Produit par blocs

`make TestProduct.exe && ./TestProduct.exe 1024`

  szBlock         | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
------------------|---------|----------------|----------------|---------------
origine (=max)    |  |
32                |  |
64                |  |
128               |  |
256               |  |
512               |  | 
1024              |  |




### Bloc + OMP



  szBlock      | OMP_NUM | MFlops  | MFlops(n=2048) | MFlops(n=512)  | MFlops(n=4096)
---------------|---------|---------|------------------------------------------------
A.nbCols       |  1      |         | 
512            |  8      |         | 







# Tips 

```
	env 
	OMP_NUM_THREADS=4 ./dot_product.exe
```

```
    $ for i in $(seq 1 4); do elap=$(OMP_NUM_THREADS=$i ./TestProductOmp.exe|grep "Temps CPU"|cut -d " " -f 7); echo -e "$i\t$elap"; done > timers.out
```