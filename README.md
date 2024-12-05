# TP : Comparaison AES HW et AES SW
Ce projet compare les performances de deux implémentations du chiffrement AES-128 ECB : une implémentation logicielle et une implémentation matérielle. L'implémentation matérielle est configurée en tant qu'accélérateur matériel pour un processeur NIOS II intégré dans un FPGA.

## Table des matières
- [Prérequis](#Prérequis)
- [Installation](#Installation)
- [Configuration](#Configuration)
- [Utilisation](#Utilisation)
- [Tests et Comparaison](#Tests et Comparaison)
- [Ressources](#Ressources)
- [Licence](#Licence)

## Prérequis
Avant de commencer, assurez-vous d'avoir les éléments suivants :

Logiciels :
Quartus (version utilisée : Quartus 13.0sp1)
Drivers associés pour la carte FPGA.
Bibliothèque AES.
Matériel :
Une carte FPGA compatible avec Quartus.
Un processeur softcore NIOS II configuré sur le FPGA.

## Installation
Téléchargez et installez Quartus :

Téléchargez QuartusSetupWeb-13.0.1.232.exe et installez-le.
Préparez le projet matériel et logiciel :

Décompressez designs_start_0.rar dans C:/altera/13.0sp1/designs/.
Copiez le contenu de copier_dans_HW_SW_AES dans C:/altera/13.0sp1/designs/HW_SW_AES/.
Ajoutez les fichiers nécessaires :

Importez les fichiers de la bibliothèque AES dans C:/altera/13.0sp1/designs/HW_SW_AES/software/test_HW_SWAES.
Configuration
Matériel :

Ouvrez Quartus et chargez le projet HW_SW_AES.
Configurez les modules suivants dans Qsys :
On-Chip Memory
NIOS II CPU
JTAG UART
PIO (Parallel I/O)
Timer Interval
SysID
Module AES personnalisé
Performance Counter Unit
Assignez les adresses de base via System > Assign Base Address.
Logiciel :

Ouvrez le fichier hello_world_small.c et modifiez les instructions pour charger la clé, les données, et lire les résultats.
Configurez et compilez le projet via le menu Run As > NIOS II Hardware.

## Utilisation
Exécution initiale :

Chargez la configuration HW_SW_AES_time_limited.sof sur la carte FPGA.
Exécutez le programme NIOS II en connectant la carte et en choisissant la configuration dans la fenêtre "Target Connection".
Chiffrement logiciel et matériel :

L'implémentation matérielle est testée en interagissant avec les adresses de base spécifiées.
L'implémentation logicielle utilise la bibliothèque tiny-AES-c.

## Tests et Comparaison
Mesure des performances :

Initialisez le compteur de performance : PERF_START_MEASURING(PERF_CNTR_BASE).
Démarrez et arrêtez les mesures : PERF_BEGIN et PERF_END.
Récupérez le temps : perf_get_section_time(PERF_CNTR_BASE, 1).
Comparez les temps obtenus pour le chiffrement matériel et logiciel.

## Ressources
Hanewin AES Test Tool
AES Online Tool
Tiny AES Library

## Licence
Ce projet est fourni à des fins éducatives. Consultez les auteurs pour toute utilisation commerciale ou redistribution.