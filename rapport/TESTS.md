# 🧪 Scénarios de Tests — TP Arduino IoT INPT

> **Module :** Ingénierie des Applications IoT  
> **Équipe :** Bara Mouad, Estifa Zineb, Haroual Hafsa, Takiouat Laila  
> **Date :** Mai 2026

---

## Méthodologie de test

Chaque sketch a été testé manuellement via le **Serial Monitor** de l'Arduino IDE (9600 bauds, fin de ligne : Newline). Les tests couvrent les cas nominaux, les cas limites et les cas d'erreur.

**Légende :**
- ✅ PASS : Comportement conforme à l'attendu
- ❌ FAIL : Comportement non conforme
- ⚠️ PARTIAL : Partiellement conforme

---

## Exercice 1 — Communication série et contrôle LED

### Ex1_sketch_hello.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX1-01 | Affichage cyclique au démarrage | Aucune (reset carte) | "Salam alaykom" + "Azul Fellawn" + "Bonjour à tous" toutes les secondes | ✅ PASS |
| TEST-EX1-02 | Vérification de la période | Chronomètre | Messages espacés de ~1000ms | ✅ PASS |
| TEST-EX1-03 | Persistence après longue durée | Laisser tourner 5 min | Pas de blocage, messages continus | ✅ PASS |

---

### Ex1_LED_serial.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX1-04 | Allumage LED avec 'a' | Envoyer `a` | "LED allumee" + LED ON (broche 9) | ✅ PASS |
| TEST-EX1-05 | Extinction LED avec 'e' | Envoyer `e` | "LED eteinte" + LED OFF | ✅ PASS |
| TEST-EX1-06 | Caractère invalide | Envoyer `x` | Aucun affichage, LED inchangée | ✅ PASS |
| TEST-EX1-07 | Envoi rapide multiple | Envoyer `aaa` | Seul le premier 'a' est traité (delay 5000ms) | ✅ PASS |
| TEST-EX1-08 | Délai de 5 secondes | Envoyer `a` puis `e` rapidement | LED s'allume, attend 5s, puis s'éteint au prochain cycle | ✅ PASS |

---

### Ex1_commandes_textuelles.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX1-09 | Commande "allumer" | `allumer\n` | "LED allumee" + LED ON | ✅ PASS |
| TEST-EX1-10 | Commande "eteindre" | `eteindre\n` | "LED eteinte" + LED OFF | ✅ PASS |
| TEST-EX1-11 | Commande "inverser" (LED OFF→ON) | `inverser\n` | "Etat inverse" + LED ON | ✅ PASS |
| TEST-EX1-12 | Commande "inverser" (LED ON→OFF) | `inverser\n` | "Etat inverse" + LED OFF | ✅ PASS |
| TEST-EX1-13 | Commande "clignoter" | `clignoter\n` | "Mode clignotement actif" + LED clignote 500ms | ✅ PASS |
| TEST-EX1-14 | Arrêt clignotement par "allumer" | `clignoter\n` puis `allumer\n` | LED arrête de clignoter, reste ON | ✅ PASS |
| TEST-EX1-15 | Commande en majuscules "ALLUMER" | `ALLUMER\n` | "LED allumee" (toLowerCase appliqué) | ✅ PASS |
| TEST-EX1-16 | Commande avec espaces | `  allumer  \n` | "LED allumee" (trim appliqué) | ✅ PASS |
| TEST-EX1-17 | Commande invalide | `bonjour\n` | Aucun affichage, état inchangé | ✅ PASS |

---

### Ex1_deux_LEDs.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX1-18 | Clignotement par défaut | Reset carte | LED1 et LED2 clignotent à 1000ms | ✅ PASS |
| TEST-EX1-19 | Modifier P1 | `P1500\n` | "P1 mis a jour : 500" + LED1 clignote à 500ms | ✅ PASS |
| TEST-EX1-20 | Modifier P2 | `P22000\n` | "P2 mis a jour : 2000" + LED2 clignote à 2000ms | ✅ PASS |
| TEST-EX1-21 | P1 et P2 indépendants | `P1200\n` puis `P21500\n` | Les deux LED clignotent à des fréquences différentes | ✅ PASS |
| TEST-EX1-22 | Valeur invalide (0) | `P10\n` | Aucun changement (if v>0 échoue) | ✅ PASS |
| TEST-EX1-23 | Valeur négative | `P1-100\n` | Aucun changement | ✅ PASS |
| TEST-EX1-24 | Commande minuscule "p1500" | `p1500\n` | "P1 mis a jour : 500" (toUpperCase appliqué) | ✅ PASS |

---

## Exercice 2 — Capteurs et systèmes d'alarme

### Ex2_PIR_base.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX2-01 | Détection de mouvement | Mouvement devant PIR | "Mouvement detecte!" + "1" | ✅ PASS |
| TEST-EX2-02 | Fin de mouvement | Arrêt mouvement | "Mouvement termine!" + "0" | ✅ PASS |
| TEST-EX2-03 | Pas de double détection | Mouvement continu | Un seul message "detecte" (pas de spam) | ✅ PASS |
| TEST-EX2-04 | Transition rapide | Mouvement bref | "detecte" suivi de "termine" | ✅ PASS |

---

### Ex2_PIR_LED.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX2-05 | LED allumée sur détection | Mouvement devant PIR | "SIGNAL HAUT : LED Allumee" + LED13 ON | ✅ PASS |
| TEST-EX2-06 | LED éteinte au repos | Pas de mouvement | "SIGNAL BAS : LED Eteinte" + LED13 OFF | ✅ PASS |
| TEST-EX2-07 | Message d'initialisation | Reset carte | "Observation de la duree d allumage..." | ✅ PASS |
| TEST-EX2-08 | Fréquence des messages | Observer Serial Monitor | Un message toutes les 100ms | ✅ PASS |

---

### Ex2_alarme.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX2-09 | Message d'initialisation | Reset carte | "Systeme pret. 'A' pour Armer, 'D' pour Desarmer." | ✅ PASS |
| TEST-EX2-10 | Armement du système | Envoyer `A` | ">>> SYSTEME ARME" | ✅ PASS |
| TEST-EX2-11 | Intrusion détectée (système armé) | `A` + mouvement PIR | "!!! ALERTE : INTRUSION DETECTEE !!!" + LED ON + Buzzer 2kHz | ✅ PASS |
| TEST-EX2-12 | Durée max buzzer (3s) | Attendre après intrusion | Buzzer s'arrête après 3000ms | ✅ PASS |
| TEST-EX2-13 | Désarmement | Envoyer `D` | ">>> SYSTEME DESARME" + LED OFF + Buzzer OFF | ✅ PASS |
| TEST-EX2-14 | Mouvement sans armement | Mouvement PIR (sans 'A') | Aucune alarme déclenchée | ✅ PASS |
| TEST-EX2-15 | Réarmement après désarmement | `A` → mouvement → `D` → `A` → mouvement | Nouvelle alarme déclenchée | ✅ PASS |

---

### Ex2_ultrason.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX2-16 | Objet proche (<100cm) | Placer main à ~30cm | "Distance: 30 cm" + LED ON + Buzzer 1kHz | ✅ PASS |
| TEST-EX2-17 | Objet loin (>100cm) | Rien devant le capteur | "Distance: XXX cm" + LED OFF + Buzzer OFF | ✅ PASS |
| TEST-EX2-18 | Distance limite (100cm) | Objet à exactement 100cm | LED ON + Buzzer ON (<=100) | ✅ PASS |
| TEST-EX2-19 | Variation de distance | Approcher/éloigner main | Distance varie en temps réel, LED/Buzzer réagissent | ✅ PASS |
| TEST-EX2-20 | Fréquence de mesure | Observer timestamps | Une mesure toutes les ~60ms | ✅ PASS |

---

## Exercice 3 — Moteurs et actionneurs

### Ex3_ventilateur_pwm.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX3-01 | Message d'accueil | Reset carte | "=== Controle du Ventilateur ===" + instructions | ✅ PASS |
| TEST-EX3-02 | Vitesse 0 (arrêt) | `0\n` | "Vitesse reglee sur : 0" + moteur arrêté | ✅ PASS |
| TEST-EX3-03 | Vitesse 128 (50%) | `128\n` | "Vitesse reglee sur : 128" + moteur tourne | ✅ PASS |
| TEST-EX3-04 | Vitesse 255 (max) | `255\n` | "Vitesse reglee sur : 255" + moteur plein régime | ✅ PASS |
| TEST-EX3-05 | Valeur hors plage (300) | `300\n` | "Erreur : Veuillez entrer une valeur entre 0 et 255." | ✅ PASS |
| TEST-EX3-06 | Valeur négative | `-10\n` | "Erreur : Veuillez entrer..." | ✅ PASS |

---

### Ex3_machine_etat.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX3-07 | Mode OFF | `0` | "Mode : OFF -> Moteur arrete." + moteur RELEASE | ✅ PASS |
| TEST-EX3-08 | Mode ECO | `1` | "Mode : ECO -> Vitesse 100." + moteur 100 | ✅ PASS |
| TEST-EX3-09 | Mode NORMAL | `2` | "Mode : NORMAL -> Vitesse 180." + moteur 180 | ✅ PASS |
| TEST-EX3-10 | Mode TURBO | `3` | "Mode : TURBO -> Vitesse 255." + moteur 255 | ✅ PASS |
| TEST-EX3-11 | Commande invalide | `5` | "Erreur: Commande non reconnue. Entrez 0, 1, 2 ou 3." | ✅ PASS |
| TEST-EX3-12 | Transition ECO→TURBO | `1` puis `3` | Passage direct à 255 | ✅ PASS |

---

### Ex3_rampe.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX3-13 | Rampe OFF→ECO | `1` | "Cible : ECO" + vitesse monte progressivement 0→100 | ✅ PASS |
| TEST-EX3-14 | Rampe ECO→TURBO | `3` | "Cible : TURBO" + vitesse monte 100→255 | ✅ PASS |
| TEST-EX3-15 | Rampe TURBO→OFF | `0` | "Cible : OFF" + vitesse descend 255→0 progressivement | ✅ PASS |
| TEST-EX3-16 | Changement pendant rampe | `3` puis immédiatement `0` | Vitesse s'inverse avant d'atteindre 255 | ✅ PASS |
| TEST-EX3-17 | Fluidité de la rampe | Observer LED moteur | Pas de saccade, transition douce (delay 10ms/step) | ✅ PASS |

---

### Ex3_securite.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX3-18 | Commande valide '2' | `2` | "Cible: NORMAL" | ✅ PASS |
| TEST-EX3-19 | Entrée invalide 'a' | `a` | "ERREUR SECURITE : Entree 'a' rejetee." | ✅ PASS |
| TEST-EX3-20 | Entrée invalide '9' | `9` | "ERREUR SECURITE : Entree '9' rejetee." | ✅ PASS |
| TEST-EX3-21 | Entrée spéciale '!' | `!` | "ERREUR SECURITE : Entree '!' rejetee." | ✅ PASS |
| TEST-EX3-22 | Vidage du buffer après erreur | `abc` | Un seul message d'erreur (buffer vidé) | ✅ PASS |
| TEST-EX3-23 | Commande valide après erreur | `x` puis `1` | Erreur pour 'x', puis "Cible: ECO" pour '1' | ✅ PASS |
| TEST-EX3-24 | Retour chariot ignoré | `\r\n` | Aucun message d'erreur | ✅ PASS |

---

### Ex3_servo_stepper.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX3-25 | Servo à 0° | `S0` | "Servo (SER2) -> 0" + servo à 0° | ✅ PASS |
| TEST-EX3-26 | Servo à 90° | `S90` | "Servo (SER2) -> 90" + servo à 90° | ✅ PASS |
| TEST-EX3-27 | Servo à 180° | `S180` | "Servo (SER2) -> 180" + servo à 180° | ✅ PASS |
| TEST-EX3-28 | Servo angle invalide (200) | `S200` | Aucune action (if angle>=0 && <=180 échoue) | ✅ PASS |
| TEST-EX3-29 | Stepper avant | `F` | "Stepper -> Marche AVANT" + 100 pas FORWARD | ✅ PASS |
| TEST-EX3-30 | Stepper arrière | `B` | "Stepper -> Marche ARRIERE" + 100 pas BACKWARD | ✅ PASS |
| TEST-EX3-31 | Commande inconnue | `X` | Aucune action | ✅ PASS |

---

### Ex3_PIR_porte.ino

| ID | Description | Entrée | Sortie attendue | Résultat |
|----|-------------|--------|-----------------|----------|
| TEST-EX3-32 | Message d'initialisation | Reset carte | "Systeme Pret : Servo sur SER2, PIR sur A0" | ✅ PASS |
| TEST-EX3-33 | Détection → ouverture | Mouvement devant PIR | ">>> MOUVEMENT !" + Servo 90° + Stepper 500 pas | ✅ PASS |
| TEST-EX3-34 | Confirmation ouverture | Après détection | "Porte Ouverte. En attente de fin de mouvement..." | ✅ PASS |
| TEST-EX3-35 | Calme → fermeture (3s) | Plus de mouvement | ">>> Calme detecte. Fermeture dans 3s..." après délai | ✅ PASS |
| TEST-EX3-36 | Retour position initiale | Après fermeture | Servo 0° + Stepper 500 pas BACKWARD | ✅ PASS |
| TEST-EX3-37 | Cycle complet | Mouvement → arrêt → mouvement | Ouverture → Fermeture → Ouverture (cycle correct) | ✅ PASS |

---

## Résumé global

| Exercice | Sketches | Tests | PASS | FAIL |
|----------|----------|-------|------|------|
| Exercice 1 | 4 | 24 | 24 | 0 |
| Exercice 2 | 4 | 20 | 20 | 0 |
| Exercice 3 | 6 | 25 | 25 | 0 |
| **TOTAL** | **14** | **69** | **69** | **0** |

> ✅ **Tous les tests passent avec succès.**
