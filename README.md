# 🤖 TP Arduino — Ingénierie des Applications IoT

[![Arduino CI](https://github.com/VOTRE-USERNAME/tp-arduino-inpt/actions/workflows/arduino-ci.yml/badge.svg)](https://github.com/VOTRE-USERNAME/tp-arduino-inpt/actions/workflows/arduino-ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

> **Institut National des Postes et Télécommunications (INPT) — Rabat**  
> Filière ASEDS, 2ème année  
> Module : Ingénierie des Applications IoT  
> Année universitaire 2025–2026

---

## 📋 Description du projet

Ce dépôt contient l'ensemble des programmes Arduino réalisés dans le cadre du TP d'Ingénierie des Applications IoT. Le TP couvre trois axes principaux :

1. **Communication série et contrôle de LED** — Maîtrise du port série, commandes textuelles, clignotement paramétrable.
2. **Capteurs et systèmes d'alarme** — Capteur PIR, capteur ultrasonique HC-SR04, buzzer, logique d'armement/désarmement.
3. **Actionneurs et moteurs** — Contrôle PWM d'un ventilateur DC, machine d'états, rampe progressive, servomoteur, moteur pas-à-pas, porte automatique.

---

## 📁 Structure du dépôt

```
tp-arduino-inpt/
├── exercice1/
│   ├── Ex1_sketch_hello/          # Impression série cyclique
│   ├── Ex1_LED_serial/            # Contrôle LED par caractère 'a'/'e'
│   ├── Ex1_commandes_textuelles/  # Commandes allumer/eteindre/inverser/clignoter
│   └── Ex1_deux_LEDs/             # Deux LEDs avec périodes P1/P2 dynamiques
├── exercice2/
│   ├── Ex2_PIR_base/              # Détection de mouvement PIR basique
│   ├── Ex2_PIR_LED/               # PIR + LED indicatrice
│   ├── Ex2_alarme/                # Système d'alarme PIR + LED + Buzzer
│   └── Ex2_ultrason/              # HC-SR04 + alarme de proximité
├── exercice3/
│   ├── Ex3_ventilateur_pwm/       # Contrôle PWM direct (0-255)
│   ├── Ex3_machine_etat/          # Machine d'états OFF/ECO/NORMAL/TURBO
│   ├── Ex3_rampe/                 # Transition progressive entre modes
│   ├── Ex3_securite/              # Filtrage des entrées aberrantes
│   ├── Ex3_servo_stepper/         # Interface unifiée Servo + Stepper
│   └── Ex3_PIR_porte/             # Porte automatique PIR + Servo + Stepper
├── schemas/                       # Schémas Tinkercad et photos montages
├── rapport/                       # Rapport LaTeX + documents annexes
├── .github/workflows/
│   └── arduino-ci.yml             # Pipeline CI/CD GitHub Actions
├── .gitignore
└── README.md
```

---

## 🛠️ Matériel utilisé

| Composant | Rôle |
|-----------|------|
| Arduino Uno (ATmega328P) | Microcontrôleur principal |
| LED (rouge, verte, jaune) | Actionneurs visuels |
| Résistances 220Ω / 10kΩ | Limitation courant / Pull-down |
| Bouton-poussoir | Entrée numérique |
| Capteur PIR HC-SR501 | Détection de mouvement |
| Capteur ultrasonique HC-SR04 | Mesure de distance |
| Buzzer piézoélectrique | Alarme sonore |
| Motor Shield L293D | Pilotage moteurs DC/Stepper |
| Moteur DC (ventilateur) | Actionneur rotatif |
| Servomoteur SG90 | Positionnement angulaire |
| Moteur pas-à-pas 28BYJ-48 | Rotation précise |
| Breadboard + fils Dupont | Prototypage |

---

## ⚙️ Prérequis

- [Arduino IDE](https://www.arduino.cc/en/software) ≥ 2.0 ou `arduino-cli`
- Librairie **Adafruit Motor Shield** (`AFMotor`)
- Librairie **Servo** (incluse par défaut)
- Carte Arduino Uno + câble USB type A/B

---

## 🚀 Compilation rapide (arduino-cli)

```bash
# Installer la plateforme
arduino-cli core install arduino:avr

# Installer la librairie AFMotor
arduino-cli lib install "Adafruit Motor Shield library"

# Compiler un sketch
arduino-cli compile --fqbn arduino:avr:uno exercice1/Ex1_sketch_hello
```

---

## 🔄 CI/CD

Le workflow GitHub Actions (`.github/workflows/arduino-ci.yml`) compile automatiquement les 14 sketches à chaque push ou pull request sur `main` et `dev`. Un échec de compilation bloque le merge.

---

## 👥 Équipe

| Membre | Rôle principal |
|--------|---------------|
| **Bara Mouad** | Exercice 1 + CI/CD |
| **Estifa Zineb** | Exercice 2 (capteurs) |
| **Haroual Hafsa** | Exercice 3 (actionneurs) |
| **Takiouat Laila** | Rapport + intégration |

---

## 👨‍🏫 Encadrant

**Pr. Yann BEN MAISSA** — Module Ingénierie des Applications IoT, INPT Rabat

---

## 📄 Licence

Ce projet est réalisé dans un cadre académique à l'INPT. Tous droits réservés.
