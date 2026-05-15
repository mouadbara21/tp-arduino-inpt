# ⚠️ Scénarios d'Erreur — TP Arduino IoT INPT

> Ce document recense les cas d'erreur critiques testés pour chaque sketch,
> les comportements attendus et les mécanismes de protection implémentés.

---

## Exercice 1 — Erreurs de communication série

### Ex1_LED_serial.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-01 | Envoi de caractères multiples rapides | Seul le premier est traité (delay 5000ms bloque) | ✅ Confirmé |
| ERR-02 | Envoi d'un caractère non reconnu ('z') | Aucune action, LED inchangée | ✅ Confirmé |
| ERR-03 | Buffer overflow (envoi de 100 caractères) | Arduino traite le premier, ignore le reste pendant le delay | ✅ Confirmé |
| ERR-04 | Baud rate incorrect (moniteur à 115200) | Caractères illisibles sur le moniteur | ✅ Confirmé |

### Ex1_commandes_textuelles.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-05 | Commande vide (juste Enter) | Aucune action (aucun if ne matche) | ✅ Confirmé |
| ERR-06 | Commande avec faute ("alumer") | Ignorée silencieusement | ✅ Confirmé |
| ERR-07 | Commande très longue (>64 chars) | Tronquée par le buffer série, ignorée | ✅ Confirmé |
| ERR-08 | Envoi sans newline (pas de \n) | readStringUntil timeout après 1s, commande traitée | ✅ Confirmé |

### Ex1_deux_LEDs.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-09 | P1 avec valeur 0 | Rejeté (if v>0 échoue), période inchangée | ✅ Confirmé |
| ERR-10 | P1 avec texte ("P1abc") | toInt() retourne 0, rejeté | ✅ Confirmé |
| ERR-11 | Commande sans préfixe P1/P2 ("X500") | Ignorée (aucun startsWith ne matche) | ✅ Confirmé |
| ERR-12 | Valeur extrême (P1=1, très rapide) | LED clignote très vite, pas de crash | ✅ Confirmé |
| ERR-13 | Valeur très grande (P1=999999) | Fonctionne, LED clignote très lentement | ✅ Confirmé |

---

## Exercice 2 — Erreurs capteurs

### Ex2_PIR_base.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-14 | PIR non connecté (broche flottante) | Lectures aléatoires HIGH/LOW (bruit) | ⚠️ Attendu — nécessite pull-down |
| ERR-15 | PIR en phase de calibration (30-60s) | Faux positifs possibles au démarrage | ⚠️ Attendu — attendre stabilisation |
| ERR-16 | Mouvement très bref (<1s) | Détecté si dans la fenêtre de lecture | ✅ Confirmé |

### Ex2_alarme.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-17 | Commande 'A' en minuscule ('a') | Non reconnue, système reste désarmé | ✅ Confirmé |
| ERR-18 | Double armement ('A' puis 'A') | Pas d'effet, reste armé | ✅ Confirmé |
| ERR-19 | Désarmement pendant alarme active | LED OFF + Buzzer OFF immédiatement | ✅ Confirmé |
| ERR-20 | Intrusion pendant buzzer actif | Pas de double déclenchement (alarmeActive=true) | ✅ Confirmé |
| ERR-21 | Buzzer après 3s sans nouveau mouvement | Buzzer s'arrête, alarme se réinitialise | ✅ Confirmé |

### Ex2_ultrason.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-22 | Aucun obstacle (distance > 400cm) | pulseIn peut timeout, distance aberrante | ⚠️ Connu — ajouter timeout à pulseIn |
| ERR-23 | Obstacle trop proche (<2cm) | Mesure imprécise (zone morte du HC-SR04) | ⚠️ Connu — limitation hardware |
| ERR-24 | Surface absorbante (tissu) | Écho faible, distance surestimée | ⚠️ Connu — limitation physique |
| ERR-25 | Câble trigPin/echoPin inversé | Aucune mesure (distance = 0) | ✅ Confirmé |

---

## Exercice 3 — Erreurs moteurs et actionneurs

### Ex3_ventilateur_pwm.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-26 | Valeur 256 (hors plage) | Message d'erreur affiché | ✅ Confirmé |
| ERR-27 | Valeur -1 (négative) | Message d'erreur affiché | ✅ Confirmé |
| ERR-28 | Texte au lieu d'un nombre ("abc") | parseInt() retourne 0, moteur s'arrête | ⚠️ Effet de bord — 0 est valide |
| ERR-29 | Envoi rapide de plusieurs valeurs | Buffer vidé après chaque lecture (while Serial.read) | ✅ Confirmé |
| ERR-30 | Shield moteur non alimenté | Commande acceptée mais moteur ne tourne pas | ⚠️ Limitation hardware |

### Ex3_machine_etat.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-31 | Caractère '5' (hors 0-3) | "Erreur: Commande non reconnue..." | ✅ Confirmé |
| ERR-32 | Lettre 'A' | "Erreur: Commande non reconnue..." | ✅ Confirmé |
| ERR-33 | Retour chariot seul (\r) | Ignoré (return dans le switch) | ✅ Confirmé |
| ERR-34 | Passage OFF→OFF | "Mode : OFF -> Moteur arrete." (pas d'erreur) | ✅ Confirmé |

### Ex3_rampe.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-35 | Changement de cible pendant rampe | Nouvelle cible prise en compte, direction inversée | ✅ Confirmé |
| ERR-36 | Commande invalide pendant rampe | Ignorée, rampe continue | ✅ Confirmé |
| ERR-37 | Coupure alimentation pendant rampe | Moteur s'arrête, reprend à 0 au redémarrage | ✅ Confirmé |

### Ex3_securite.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-38 | Injection de caractères spéciaux ("!@#") | "ERREUR SECURITE" + buffer vidé | ✅ Confirmé |
| ERR-39 | Chiffre hors plage ('7') | "ERREUR SECURITE : Entree '7' rejetee." | ✅ Confirmé |
| ERR-40 | Séquence mixte "a2b3" | 'a' rejeté + buffer vidé, '3' perdu | ✅ Confirmé — sécurité prioritaire |
| ERR-41 | Flood de données (100 chars) | Un seul message d'erreur, buffer entièrement vidé | ✅ Confirmé |
| ERR-42 | Commande valide après flood | Acceptée normalement | ✅ Confirmé |

### Ex3_servo_stepper.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-43 | Angle servo négatif (S-10) | parseInt retourne -10, if échoue, pas d'action | ✅ Confirmé |
| ERR-44 | Angle servo > 180 (S200) | if échoue, servo ne bouge pas | ✅ Confirmé |
| ERR-45 | 'S' sans nombre après | parseInt timeout, retourne 0, servo va à 0° | ⚠️ Effet de bord |
| ERR-46 | Stepper bloqué mécaniquement | Moteur force, courant augmente, risque échauffement | ⚠️ Pas de protection logicielle |

### Ex3_PIR_porte.ino

| Scénario | Description | Comportement attendu | Résultat |
|----------|-------------|---------------------|----------|
| ERR-47 | Mouvement continu (ne s'arrête jamais) | Porte reste ouverte indéfiniment | ✅ Confirmé — by design |
| ERR-48 | Mouvement pendant fermeture (delay 3s) | Non détecté (delay bloquant) | ⚠️ Limitation — utiliser millis() |
| ERR-49 | PIR non connecté | Lectures aléatoires, ouvertures/fermetures erratiques | ⚠️ Pas de protection |
| ERR-50 | Stepper bloqué pendant ouverture | Programme bloqué sur stepper.step() | ⚠️ Limitation — pas de timeout |

---

## Synthèse des vulnérabilités

| Catégorie | Nombre | Criticité |
|-----------|--------|-----------|
| Erreurs gérées correctement | 35 | ✅ Faible |
| Effets de bord acceptables | 5 | ⚠️ Moyenne |
| Limitations hardware connues | 7 | ⚠️ Moyenne |
| Vulnérabilités non protégées | 3 | 🔴 Haute |

### Recommandations d'amélioration

1. **Ex2_ultrason** : Ajouter un timeout à `pulseIn()` pour éviter les blocages
2. **Ex3_PIR_porte** : Remplacer `delay(3000)` par une logique non-bloquante avec `millis()`
3. **Ex3_servo_stepper** : Ajouter une validation quand `parseInt()` retourne 0 par timeout
4. **Ex3_ventilateur_pwm** : Distinguer "0 saisi volontairement" de "parseInt a échoué"
5. **Général** : Ajouter un watchdog timer pour détecter les blocages
