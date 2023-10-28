package pour le robot principal ENSTAR 2021

package navTest_pkg:


utils.cpp : 

R_or_T_steps_service:
execute un nombre de step pour chasue moteur (un argument par moteur)
moteurgauche=moteur sur le port 0
moteur droit=moteur sur le port 1
(orientation donnée pour le robot vu de haut avec l'avant en haut)

SUIVI DE LIGNE
capteur gauche branché  sur le gpio23 (norme BCM) 
capteur droit : gpio24 

INTERRUPTEUR:
branché sur le gpio18

line_sensor_msg : message custom pour le topic /line_sensor
read_line_sensor_pkg:publie les données des capteurs de lignes dans le topic /line_sensor
Pour le lancer : rosrun read_line_sensor_pkg sensor_publisher.py 

stepper_control_msg : message d action custom pour le controle des steppers

stepper_control_pkg : creée l'action set_number_of_steps permettant de fixer un objectif en position aux steppers

compiler du C++ avec du code python: ajouter l'option -I/usr/include/python2.7 -lpython2.7
executer un script .py avec GPIO : sudo python exemple.py



