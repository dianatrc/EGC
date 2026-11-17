# 2D Heartstone Card Game (OpenGl / C++)
A 2D turn-based collectible card game inspired by **Heartstone**, built from scratch in **C++** using **OpenGL**, **GLM**, and **GLFW** on top of the university's **GFXFramework**.

## Gameplay and Features
- **Turn-Based Combat and Hand Cost System:** Players start with 5 cards in hand (25 in deck) and 1 hand cost, scaling up to 10 per turn. Each hero begins with 30HP (health points); the match ends when either hero's HP drops to 0.
- **Interactive Drag-and-Drop and Board Layout:** Smooth drag-and-drop card placement onto the player's half of the board with boundary validation, automatic return animations on invalid drops, and dynamic horizontal re-centering for both hand and board slots.
- **Attack Targeting and Enemy Attacks:** One-attack-per-turn rule with visual outline indicators for active cards, a dynamic targeting arrow following the cursor (`atan2f` orientation), and an automated opponent that plays cards and executes attacks during its turn.
- **Procedural Mathematical UI and Icons:** Custom 2D meshes generated procedurally using polar/parametric equations for card stats and visual indicators:
  - **Hearts (HP)**
  - **Swords (ATK)**
  * **Triangle, Circle, Star and Diamond Shapes**
- **Smooth Animations and Turn Timer:** Exponential hover/selection scaling interpolation, deck-to-hand draw translations, and a 30-second visual turn countdown bar that automatically ends the turn upon expiration.

## Project Structure
- assets/ 
    - fonts/               
    - models/               
    - shaders/
    - textures/                  
- deps/
    - api/
    - prebuilt/
- src/
    - components/
    - core/
    - lab_m1/
        - Tema1/            # Custom game implementation
        - lab_list.h        # Scene registration headers.
    - utils/                # Math helpers, GLM wrappers, and memory management utilities.
    - main.cpp              # Application entry point.
