#include "raylib.h" // Inclusion de la bibliothèque raylib, qui est utilisée pour le développement de jeux et d'applications graphiques.
#include <vector>// Inclusion de la bibliothèque vector pour utiliser des vecteurs dynamiques.
#include <iostream> // Inclusion de la bibliothèque iostream pour les entrées/sorties standard.
#include <cstdlib>// Inclusion de la bibliothèque cstdlib pour des fonctions utilitaires générales, comme la génération de nombres aléatoires.
#include <cfloat> // Inclusion de la bibliothèque cfloat pour les constantes de type float, comme FLT_MAX.
#include <string>// Inclusion de la bibliothèque string pour manipuler des chaînes de caractères.
class Game {
public:
   // Texture pour l'image d'interface
    Texture2D interfaceImage; 
    // Texture pour le bouton "Démarrer"
    Texture2D startButtonImage;
     
    // Constructeur de la classe Game
    Game() {
        // Charger l'image d'interface depuis le chemin spécifié
        interfaceImage = LoadTexture("space background.png");
        // Charger l'image du bouton "Démarrer" depuis le chemin spécifié
        startButtonImage = LoadTexture("start_button.png"); 
    }
// Méthode pour afficher l'interface du jeu
    void displayInterface() {
        ClearBackground(RAYWHITE); // Effacer l'arrière-plan avec une couleur blanche
         // Obtenir les dimensions de la fenêtre
        int windowWidth = GetScreenWidth();
        int windowHeight = GetScreenHeight();
        // Dessiner l'image d'interface en l'adaptant à la taille de la fenêtre
      DrawTexturePro(
            interfaceImage, 
            (Rectangle){0, 0, (float)interfaceImage.width, (float)interfaceImage.height}, // Rectangle source (image entière)
            (Rectangle){0, 0, (float)windowWidth, (float)windowHeight},                  // Rectangle de destination (entière fenêtre)
            (Vector2){0, 0},                                                             // Point d'origine
            0.0f,                                                                        // Rotation
            WHITE                                                                         // Teinte
        );
        // dessiner l'image du bouton start
        int buttonWidth = 350; // Largeur du bouton
        int buttonHeight = 100;// hauteur du bouton
        float buttonX = windowWidth / 2 - buttonWidth / 2; // Position X centrée
        float buttonY = windowHeight / 2;// Position Y centrée
        DrawTexturePro(
            startButtonImage,
            (Rectangle){0, 0, (float)startButtonImage.width, (float)startButtonImage.height}, // Rectangle source (image entière)
            (Rectangle){(float)buttonX, (float)buttonY, (float)buttonWidth, (float)buttonHeight}, // Rectangle de destination
            (Vector2){0, 0}, // Point d'origine
            0.0f, // Rotation
            WHITE // Teinte
        );
    }
  // Méthode pour détecter un clic sur le bouton "Démarrer"
    bool detectStartClick() {
        // Obtenir les dimensions de la fenêtre
        int windowWidth = GetScreenWidth();
        int windowHeight = GetScreenHeight();
        int buttonWidth = 350; // Largeur du bouton
        int buttonHeight = 100; // Hauteur du bouton
       float buttonX = windowWidth / 2 - buttonWidth / 2; // Position X centrée
       float buttonY = windowHeight / 2;// Position Y centrée
        Vector2 mousePosition = GetMousePosition();// Obtenir la position de la souris
      // Vérifier si le bouton "Démarrer" a été cliqué
        return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && // Vérifier si le bouton gauche de la souris est pressé
               mousePosition.x >= buttonX && // Vérifier si la souris est à l'intérieur de la largeur du bouton
               mousePosition.x <= buttonX + buttonWidth &&
               mousePosition.y >= buttonY && // Vérifier si la souris est à l'intérieur de la hauteur du bouton
               mousePosition.y <= buttonY + buttonHeight;
    }
// Méthode pour afficher le menu de sélection de difficulté
void afficherMenu() {
    const int menuWidth = 200; // Largeur des rectangles
    const int menuHeight = 50; // Hauteur des rectangles
    const int spacing = 20; // Espacement entre les éléments du menu

    // Texte du menu
    const char* title = "Choisissez votre niveau de difficulte :";
    const char* easy = "Facile";
    const char* medium = "Moyen";
    const char* hard = "Difficile";

    // Calculer la position du titre
    int titleWidth = MeasureText(title, 20); // Largeur du titre
    int titleHeight = 20; // Hauteur du texte du titre
    int titleX = (GetScreenWidth() - titleWidth) / 2;

    // Calculer la position des boutons
    int buttonX = (GetScreenWidth() - menuWidth) / 2; // Position X centrée des boutons

    // Calculer la position Y pour centrer le menu
    int totalMenuHeight = titleHeight + (3 * menuHeight) + (2 * spacing); // Hauteur totale du menu
    int startY = (GetScreenHeight() - totalMenuHeight) / 2; // Position Y de départ pour centrer

    float easyY = startY + titleHeight + spacing; // Position du bouton "Facile"
    float mediumY = easyY + menuHeight + spacing; // Position du bouton "Moyen"
    int hardY = mediumY + menuHeight + spacing; // Position du bouton "Difficile"

    // Dessiner le titre en blanc et en gras
    DrawText(title, titleX, startY, 20, WHITE); // Texte normal
    DrawText(title, titleX + 1, startY + 1, 20, WHITE); // Texte décalé pour simuler le gras

    // Dessiner les boutons avec un effet de survol
    Vector2 mousePosition = GetMousePosition();
    Color buttonColor;
    Color borderColor;

    // Bouton "Facile"
    buttonColor = (mousePosition.x >= buttonX && mousePosition.x <= buttonX + menuWidth &&
                   mousePosition.y >= easyY && mousePosition.y <= easyY + menuHeight) ? 
                   (Color){0, 200, 0, 255} : (Color){0, 255, 0, 255}; // Vert clair au survol
    borderColor = (mousePosition.x >= buttonX && mousePosition.x <= buttonX + menuWidth &&
                   mousePosition.y >= easyY && mousePosition.y <= easyY + menuHeight) ? 
                   (Color){0, 150, 0, 255} : (Color){0, 200, 0, 255}; // Bordure plus foncée au survol
    DrawRectangleRounded((Rectangle){buttonX, easyY, menuWidth, menuHeight}, 0.2f, 10, borderColor); // Bordure
    DrawRectangleRounded((Rectangle){buttonX + 2, easyY + 2, menuWidth - 4, menuHeight - 4}, 0.2f, 10, buttonColor); // Bouton

    // Dessiner le texte du bouton "Facile" en blanc et en gras
    int textX = buttonX + (menuWidth - MeasureText(easy, 20)) / 2;
    int textY = easyY + 10;
    DrawText(easy, textX, textY, 20, WHITE); // Texte normal
    DrawText(easy, textX + 1, textY + 1, 20, WHITE); // Texte décalé pour simuler le gras

    // Bouton "Moyen"
    buttonColor = (mousePosition.x >= buttonX && mousePosition.x <= buttonX + menuWidth &&
                   mousePosition.y >= mediumY && mousePosition.y <= mediumY + menuHeight) ? 
                   (Color){255, 165, 0, 255} : (Color){255, 200, 0, 255}; // Orange clair au survol
    borderColor = (mousePosition.x >= buttonX && mousePosition.x <= buttonX + menuWidth &&
                   mousePosition.y >= mediumY && mousePosition.y <= mediumY + menuHeight) ? 
                   (Color){200, 130, 0, 255} : (Color){255, 165 , 0, 255}; // Bordure plus foncée au survol
    DrawRectangleRounded((Rectangle){buttonX, mediumY, menuWidth, menuHeight}, 0.2f, 10, borderColor); // Bordure
    DrawRectangleRounded((Rectangle){buttonX + 2, mediumY + 2, menuWidth - 4, menuHeight - 4}, 0.2f, 10, buttonColor); // Bouton

    // Dessiner le texte du bouton "Moyen" en blanc et en gras
    int mediumTextX = buttonX + (menuWidth - MeasureText(medium, 20)) / 2;
    int mediumTextY = mediumY + 10;
    DrawText(medium, mediumTextX, mediumTextY, 20, WHITE); // Texte normal
    DrawText(medium, mediumTextX + 1, mediumTextY + 1, 20, WHITE); // Texte décalé pour simuler le gras

    // Bouton "Difficile"
    buttonColor = (mousePosition.x >= buttonX && mousePosition.x <= buttonX + menuWidth &&
                   mousePosition.y >= hardY && mousePosition.y <= hardY + menuHeight) ? 
                   (Color){200, 0, 0, 255} : (Color){255, 0, 0, 255}; // Rouge clair au survol
    borderColor = (mousePosition.x >= buttonX && mousePosition.x <= buttonX + menuWidth &&
                   mousePosition.y >= hardY && mousePosition.y <= hardY + menuHeight) ? 
                   (Color){150, 0, 0, 255} : (Color){200, 0, 0, 255}; // Bordure plus foncée au survol
    DrawRectangleRounded((Rectangle){buttonX, hardY, menuWidth, menuHeight}, 0.2f, 10, borderColor); // Bordure
    DrawRectangleRounded((Rectangle){buttonX + 2, hardY + 2, menuWidth - 4, menuHeight - 4}, 0.2f, 10, buttonColor); // Bouton

    // Dessiner le texte du bouton "Difficile" en blanc et en gras
    int hardTextX = buttonX + (menuWidth - MeasureText(hard, 20)) / 2;
    int hardTextY = hardY + 10;
    DrawText(hard, hardTextX, hardTextY, 20, WHITE); // Texte normal
    DrawText(hard, hardTextX + 1, hardTextY + 1, 20, WHITE); // Texte décalé pour simuler le gras
}
// Méthode pour détecter un clic sur un bouton de difficulté
std::string detecterClicDifficulte() {
     // Vérifier si le bouton gauche de la souris est pressé
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Obtenir la position de la souris 
        Vector2 souris = GetMousePosition();
        // Vérifiez les positions des boutons
        if (souris.x >= (GetScreenWidth() / 2 - 100) && souris.x <= (GetScreenWidth() / 2 + 100)) {
             // Vérifier si le bouton "Facile" a été cliqué
            if (souris.y >= (GetScreenHeight() / 2 - 50) && souris.y <= (GetScreenHeight() / 2 - 50 + 50)) return "Facile";
             // Vérifier si le bouton "Moyen" a été cliqué
            if (souris.y >= (GetScreenHeight() / 2 + 20) && souris.y <= (GetScreenHeight() / 2 + 20 + 50)) return "Moyen";
             // Vérifier si le bouton "Difficile" a été cliqué
            if (souris.y >= (GetScreenHeight() / 2 + 90) && souris.y <= (GetScreenHeight() / 2 + 90 + 50)) return "Difficile";
        }
    }
    return "";  // Si aucun bouton n'a été cliqué, retourner une chaîne vide
}
};

// Classe Labyrinthe : Gère la grille et la génération du labyrinthe
class Labyrinthe {
private:
    int largeur, hauteur;
    std::vector<std::vector<int>> grille;
    int arriveeX, arriveeY;
    Texture2D arriveTexture; // Texture pour la sortie
public:
    // Constructeur qui initialise les dimensions du labyrinthe
    Labyrinthe(int largeur, int hauteur) : largeur(largeur), hauteur(hauteur) {
        grille.resize(hauteur, std::vector<int>(largeur, 1)); // Initialiser la grille avec des murs (1)
        generer();   // Générer le labyrinthe
        arriver();  // Définir la position de la sortie
         grille[1][0] = 0;  // Ouvrir l'entrée
        arriveTexture = LoadTexture("arrive.png");  // Charger la texture de la sortie
    }
    //méthodes Getter pour accès les dimensions du labyrinthe
    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }
     // Méthode de génération du labyrinthe
    void generer() {
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                grille[y][x] = 1;  // Initialiser toutes les cellules comme des murs
            }
        }
        std::vector<std::pair<int, int>> pathStack;// Pile pour le chemin
        int x = 1, y = 1;// Point de départ
        grille[y][x] = 0;  // Espace ouvert
        pathStack.push_back({x, y});// Ajouter le point de départ à la pile
        // Algorithme de génération de labyrinthe (recherche en profondeur aléatoire)
        while (!pathStack.empty()) {
            auto [cx, cy] = pathStack.back();
            std::vector<std::pair<int, int>> directions;
            // Vérifier les directions possibles pour avancer
            if (cy - 2 > 0 && grille[cy - 2][cx] == 1) directions.push_back({0, -2});
            if (cy + 2 < hauteur - 1 && grille[cy + 2][cx] == 1) directions.push_back({0, 2});
            if (cx - 2 > 0 && grille[cy][cx - 2] == 1) directions.push_back({-2, 0});
            if (cx + 2 < largeur - 1 && grille[cy][cx + 2] == 1) directions.push_back({2, 0});
            if (!directions.empty()) {
                // Choisir une direction aléatoire
                auto [dx, dy] = directions[GetRandomValue(0, directions.size() - 1)];
                int nx = cx + dx;
                int ny = cy + dy;
                 // Enlever le mur entre la cellule actuelle et la prochaine cellule
                grille[cy + dy / 2][cx + dx / 2] = 0; // Enlever le mur
                grille[ny][nx] = 0; // Marquer la prochaine cellule comme chemin
                pathStack.push_back({nx, ny});// Ajouter la nouvelle position à la pile
            } else {
                pathStack.pop_back(); // Reculer si aucun mouvement n'est possible
            }
        }
    }
    // Définir le point de sortie (coin inférieur droit ou un espace ouvert aléatoire)
    void arriver() {
        for (int y = hauteur - 2; y >= 1; y--) {
            for (int x = largeur - 2; x >= 1; x--) {
                if (grille[y][x] == 0) {  // Find an open space for the exit
                    arriveeX = x;
                    arriveeY = y;
                    return;
                }
            }
        }
    }
// Méthode pour afficher le labyrinthe, en utilisant la texture des murs
void afficher(float offsetX, float offsetY) {
    int cellSize = 40; // Taille d'une cellule
    int wallThickness = 2; // Épaisseur des murs
    Color wallColor = WHITE; // Couleur des murs
    // Dessiner les murs du labyrinthe
    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            if (grille[y][x] == 1) { // Si c'est un mur
                // Dessiner le mur supérieur
                if (y > 0 && grille[y - 1][x] == 0) {
                    for (int i = 0; i < wallThickness; i++) {
                        DrawLine(offsetX + x * cellSize, offsetY + y * cellSize + i, 
                                 offsetX + (x + 1) * cellSize, offsetY + y * cellSize + i, wallColor);
                    }
                }
                // Dessiner le mur gauche
                if (x > 0 && grille[y][x - 1] == 0) {
                    for (int i = 0; i < wallThickness; i++) {
                        DrawLine(offsetX + x * cellSize + i, offsetY + y * cellSize, 
                                 offsetX + x * cellSize + i, offsetY + (y + 1) * cellSize, wallColor);
                    }
                }
                // Dessiner le mur inférieur
                if (y < hauteur - 1 && grille[y + 1][x] == 0) {
                    for (int i = 0; i < wallThickness; i++) {
                        DrawLine(offsetX + x * cellSize, offsetY + (y + 1) * cellSize - i, 
                                 offsetX + (x + 1) * cellSize, offsetY + (y + 1) * cellSize - i, wallColor);
                    }
                }
                // Dessiner le mur droit
                if (x < largeur - 1 && grille[y][x + 1] == 0) {
                    for (int i = 0; i < wallThickness; i++) {
                        DrawLine(offsetX + (x + 1) * cellSize - i, offsetY + y * cellSize, 
                                 offsetX + (x + 1) * cellSize - i, offsetY + (y + 1) * cellSize, wallColor);
                    }
                }
            }
        }
    }
    // Dessiner la sortie (texture d'arrivée) à la position exacte de la sortie
    float smallWidth = 43;  // Largeur de la texture d'arrivée
    float smallHeight =59 ; // Hauteur de la texture d'arrivée
    DrawTexturePro(arriveTexture, 
        {0, 0, (float)arriveTexture.width, (float)arriveTexture.height}, // Source rectangle (entière image)
        {offsetX + arriveeX * cellSize, 
         offsetY + arriveeY * cellSize, // Position exacte de la sortie
         smallWidth, smallHeight}, // Destination rectangle (taille réduite)
        {0, 0}, // Point d'origine pour la rotation (coin supérieur gauche)
        0.0f, // Rotation
        WHITE); // Couleur de teinte
}
    //  méthodes Getter pour accès  les dimensions du labyrinthe
    int getArriveeX() const { return arriveeX; }
    int getArriveeY() const { return arriveeY; }
    // Méthode pour obtenir la valeur d'une case dans la grille
     int getCase(int x, int y) const {
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        return grille[y][x];
    }
    return 1;  // Hors limites, traiter comme un mur
}
};
// Classe Joueur : Gère le personnage contrôlé par le joueur
class Joueur {
private:
    int x, y;
    int taille;
    Texture2D texture;  // Texture utilisée pour représenter l'astronaute
public:
// Constructeur : initialise les coordonnées du joueur et charge la texture
  Joueur(int startX, int startY) : x(startX), y(startY), taille(40) { // Taille initialisée à 40
  texture = LoadTexture("debut.png");}  // Charge l'image de la texture
 // Méthode pour afficher le joueur à l'écran
 void afficher(int offsetX, int offsetY) {
    DrawTexturePro(
        texture, // Texture de l'astronaute
        (Rectangle){0, 0, (float)texture.width, (float)texture.height}, // Source rectangle (entière image)
        (Rectangle){offsetX + x * taille, offsetY + y * taille, 45, 49}, // Rectangle destination (position et taille)
        (Vector2){0, 0}, // Point d'origine
        0.0f, 
        WHITE // Couleur de teinte
    );
} // Méthode pour déplacer le joueur
    void deplacer(int dx, int dy, const Labyrinthe &labyrinthe) {
        int newX = x + dx; // Nouvelle position en X
        int newY = y + dy; // Nouvelle position en Y
        if (labyrinthe.getCase(newX, newY) == 0) {  // Check if the new position is a path
            x = newX;// Met à jour la position en X
            y = newY; // Met à jour la position en Y
        }
    }
 // Méthode pour vérifier si le joueur a atteint la sortie
    bool aGagne(const Labyrinthe &labyrinthe) {
         // Compare la position du joueur avec celle de la sortie
        return x == labyrinthe.getArriveeX() && y == labyrinthe.getArriveeY();  // Check if the player reached the exit
    }
    int getX() const { return x; } // Ajout de la méthode getX
    int getY() const { return y; } // Ajout de la méthode getY

};

class Niveau {
private:
    int tailleLabyrinthe; // Taille du labyrinthe
    std::string difficulte; // Niveau de difficulté : "Facile", "Moyen", ou "Difficile"
public:
 // Constructeur qui initialise le niveau de difficulté et définit la taille du labyrinthe
    Niveau(std::string niveauDifficulte) {
        difficulte = niveauDifficulte;
        definirTaille();// Appeler la méthode pour définir la taille du labyrinthe en fonction de la difficulté
    }
    // Méthode pour définir la taille du labyrinthe en fonction du niveau de difficulté
    void definirTaille() {
        if (difficulte == "Facile") {
            tailleLabyrinthe = 18;// Définir la taille du labyrinthe pour le niveau facile
        } else if (difficulte == "Moyen") {
            tailleLabyrinthe = 22;// Définir la taille du labyrinthe pour le niveau moyen
        } else if (difficulte == "Difficile") {
            tailleLabyrinthe = 26;// Définir la taille du labyrinthe pour le niveau difficile
        } 
    }
    // Méthode pour obtenir le nombre d'obstacles en fonction du niveau de difficulté
        int getNombreObstacles() const {
        if (difficulte == "Facile") {
            return 1; // 1 obstacles pour le niveau facile
        } else if (difficulte == "Moyen") {
            return 3; // 3 obstacles pour le niveau moyen
        } else if (difficulte == "Difficile") {
            return 4; // 4 obstacles pour le niveau difficile
        }
        return 0; // Par défaut
    }
    void augmenterDifficulte() {
        if (tailleLabyrinthe < 50) { // Limiter la taille maximale
            tailleLabyrinthe += 5;// Augmenter la taille du labyrinthe de 5
        }
    }
     // Méthode pour obtenir la taille du labyrinthe
    int getTailleLabyrinthe() const {
        return tailleLabyrinthe;
    }
     // Méthode pour obtenir le niveau de difficulté
    std::string getDifficulte() const {
        return difficulte;
    }
};
class Obstacle {
private:
    int x, y; // Position de l'obstacle
    int taille; // Taille de l'obstacle
    float vitesse; // Vitesse de déplacement de l'obstacle (en secondes)
    int direction; // Direction de déplacement 
    float tempsEcoule; // Temps écoulé depuis le dernier mouvement
    Texture2D texture; // Texture pour l'obstacle
     public:
     // Constructeur qui initialise la position, la vitesse et la taille de l'obstacle
     Obstacle(int startX, int startY, float speed) 
        : x(startX), y(startY), taille(40), vitesse(speed), tempsEcoule(0) { // Taille fixée à 30
        direction = GetRandomValue(0, 3); // Direction initiale aléatoire
        texture = LoadTexture("obstacle.png"); // Remplacez par le chemin de votre image d'obstacle
    }

    // Méthode pour définir la vitesse de l'obstacle
    void setVitesse(float newSpeed) {
        vitesse = newSpeed;
    }

  void deplacer(const Labyrinthe &labyrinthe, float deltaTime) {
    tempsEcoule += deltaTime; // Mettre à jour le temps écoulé

    // Déterminer le mouvement en fonction de la direction
    if (tempsEcoule >= vitesse) { // Vérifier si le temps écoulé est supérieur à la vitesse
        int dx = 0, dy = 0;

        switch (direction) {
            case 0: dy = -1; break; // Haut
            case 1: dy = 1; break;  // Bas
            case 2: dx = -1; break; // Gauche
            case 3: dx = 1; break;  // Droite
        }

        // Vérifier si le mouvement est valide
        int nx = x + dx;
int ny = y + dy;

if (nx > 0 && nx < labyrinthe.getLargeur() - 1 && ny > 0 && ny < labyrinthe.getHauteur() - 1 &&
    labyrinthe.getCase(nx, ny) == 0) {
    x = nx;
    y = ny;
} else {
    // Change de direction si le mouvement n'est pas possible
    direction = GetRandomValue(0, 3);
}
        tempsEcoule = 0; // Réinitialiser le temps écoulé
    }
}
  void afficher(float offsetX, float offsetY) const {
    DrawTexturePro(texture, 
        {0, 0, (float)texture.width, (float)texture.height}, // Source rectangle (entière image)
        {offsetX + x * taille, offsetY + y * taille, 45, 43}, // Destination rectangle (taille de 45x43 pixels)
        {0, 0}, // Point d'origine pour la rotation (coin supérieur gauche)
        0.0f, // Rotation
        WHITE); // Couleur de teinte
}
// Méthodes pour obtenir la position de l'obstacle
    int getX() const { return x; }
    int getY() const { return y; }
};
class Jeu {
public:
     // Variables pour stocker les meilleurs scores pour chaque niveau de difficulté
    float meilleurScoreFacile = FLT_MAX; // Meilleur score pour le niveau facile
    float meilleurScoreMoyen = FLT_MAX;  // Meilleur score pour le niveau moyen
    float meilleurScoreDifficile = FLT_MAX; // Meilleur score pour le niveau difficile
    float score; // Score actuel du joueur
    float tempsEcoule; // Temps écoulé depuis le début du jeu
    bool estEnPause = false; // Indique si le jeu est en pause

    Texture2D boutonPauseTexture; // Texture pour le bouton Pause
    Texture2D boutonReprendreTexture; // Texture pour le bouton "Reprendre"
    Texture2D boutonReinitialiserTexture; // Texture pour le bouton "Réinitialiser"

    std::vector<Obstacle> obstacles; // Liste d'obstacles dans le jeu
      // Constructeur de la classe Jeu
    Jeu(const Labyrinthe &labyrinthe, const Niveau &niveau) : score(0), tempsEcoule(0) {    
        // Charger l'image du bouton Pause
        boutonPauseTexture = LoadTexture("pause.png"); 
        boutonReprendreTexture = LoadTexture("reprendre.png"); 
        boutonReinitialiserTexture = LoadTexture("reinitialiser.png"); 
        int nombreObstacles = niveau.getNombreObstacles(); // Obtenez le nombre d'obstacles en fonction du niveau
        // Créer des obstacles avec une vitesse de 1 seconde
        for (int i = 0; i < nombreObstacles; ++i) {
            int obstacleX, obstacleY;
            // Générer des coordonnées aléatoires pour les obstacles
            do {
                obstacleX = GetRandomValue(1, labyrinthe.getLargeur() - 2); // Garder les coordonnées dans les limites
                obstacleY = GetRandomValue(1, labyrinthe.getHauteur() - 2);
            } while (labyrinthe.getCase(obstacleX, obstacleY) != 0); // Vérifier que la case est vide (0)
             // Ajouter un nouvel obstacle à la liste
            obstacles.emplace_back(obstacleX, obstacleY, 0.3f);
        }
    }
    // Méthode pour réinitialiser les obstacles
 void reinitialiserObstacles(const Niveau &niveau, const Labyrinthe &labyrinthe) {
        obstacles.clear(); // Vider la liste d'obstacles
        int nombreObstacles = niveau.getNombreObstacles(); // Obtenez le nombre d'obstacles en fonction du niveau
        // Créer des obstacles avec une vitesse de 1 seconde
        for (int i = 0; i < nombreObstacles; ++i) {
            int obstacleX, obstacleY;
             // Générer des coordonnées aléatoires pour les obstacles
            do {
                obstacleX = GetRandomValue(1, labyrinthe.getLargeur() - 2); // Garder les coordonnées dans les limites
                obstacleY = GetRandomValue(1, labyrinthe.getHauteur() - 2);
            } while (labyrinthe.getCase(obstacleX, obstacleY) != 0); // Vérifier que la case est vide (0)
        // Ajouter un nouvel obstacle à la liste
            obstacles.emplace_back(obstacleX, obstacleY, 1.0f);
        }
    }
    // Méthode pour afficher le bouton de réinitialisation
    void afficherBoutonReinitialiser() {
    // Position du bouton
    int posX = 1240; // Décalage par rapport bord gauche
    int posY = 10; // Décalage par rapport bord supérieur
    // Définir une échelle pour réduire la taille du bouton
    float scaleX = 0.8f; // Échelle en X (70% de la taille originale)
    float scaleY = 0.8f; // Échelle en Y (70% de la taille originale)

    // Dessiner l'image du bouton
    DrawTextureEx(boutonReinitialiserTexture, (Vector2){posX, posY}, 0.0f, scaleX, WHITE);
}
// Méthode pour détecter un clic sur le bouton de réinitialisation
bool detecterClicReinitialiser() {
    const float buttonWidth = boutonReinitialiserTexture.width * 0.8f; // Largeur ajustée
    const float buttonHeight = boutonReinitialiserTexture.height * 0.8f; // Hauteur ajustée

    int posX = 1240; // Décalage de 10 pixels du bord gauche
    int posY = 10; // Décalage de 10 pixels du bord supérieur

    Vector2 mousePosition = GetMousePosition();// Obtenir la position de la souris
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&  // Vérifier si le bouton gauche de la souris est pressé
           mousePosition.x >= posX && mousePosition.x <= posX + buttonWidth && // Vérifier si la souris est dans la zone du bouton
           mousePosition.y >= posY && mousePosition.y <= posY + buttonHeight; // Vérifier si la souris est dans la zone du bouton
}
// Méthode pour mettre à jour la position des obstacles
 void mettreAJourObstacles(const Labyrinthe &labyrinthe, float deltaTime) {
        for (auto &obstacle : obstacles) {
            obstacle.deplacer(labyrinthe, deltaTime); // Passer le labyrinthe et le temps écoulé
        }
    }
     // Méthode pour détecter les collisions avec les obstacles
    bool detecterCollisionAvecObstacles(const Joueur &joueur) {
        for (const auto &obstacle : obstacles) {
            if (obstacle.getX() == joueur.getX() && obstacle.getY() == joueur.getY()) {
                return true; // Collision détectée
            }
        }
        return false; // Aucune collision détectée
    }
     // Méthode pour mettre à jour le meilleur score
    void mettreAJourMeilleurScore(const std::string& difficulte, float temps) {
        if (difficulte == "Facile" && temps < meilleurScoreFacile) {
            meilleurScoreFacile = temps; // Mettre à jour le meilleur score pour le niveau facile
        } else if (difficulte == "Moyen" && temps < meilleurScoreMoyen) {
            meilleurScoreMoyen = temps;  // Mettre à jour le meilleur score pour le niveau moyen
        } else if (difficulte == "Difficile" && temps < meilleurScoreDifficile) {
            meilleurScoreDifficile = temps; // Mettre à jour le meilleur score pour le niveau difficile
        }
    }
     // Méthode pour afficher le temps écoulé
   void afficherTemps(int x, int y) {
    int minutes = (int)(tempsEcoule / 60); // Calculer les minutes
    int secondes = (int)(tempsEcoule) % 60; // Calculer les secondes
    char buffer[50]; // Buffer pour le texte
    snprintf(buffer, sizeof(buffer), "Temps : %02d:%02d", minutes, secondes); // Formater le texte
    // Ajustez la position Y pour descendre le texte
    int offset = 50; // Décalage vers le bas
    int textSize = 35; // Taille de la police
    // Dessiner l'ombre
    DrawText(buffer, x + 2, y + offset + 2, textSize, DARKGRAY); // Ombre
    // Dessiner le texte principal
    DrawText(buffer, x, y + offset, textSize, WHITE); // Texte
}
     // Méthode pour afficher le menu de pause
void afficherMenuPause() {
    // Position des boutons
    float buttonWidth = 200; // Largeur des boutons
    float buttonHeight = 60; // Hauteur des boutons
    int posY = 10; // Position Y pour les boutons (aligné avec le bouton Pause)

    float scaleX = 0.8f; // Échelle en X pour réduire la taille
    float scaleY = 0.8f; // Échelle en Y pour réduire la taille

    // Positionner le bouton "Reprendre" à droite du bouton "Pause"
    int posXPause = GetScreenWidth() - boutonPauseTexture.width * scaleX - 15; // Position X du bouton "Pause"
    DrawTextureEx(boutonReprendreTexture, (Vector2){posXPause - buttonWidth +120, posY}, 0.0f, scaleX, WHITE); // 10 pixels d'écart
}
// Méthode pour afficher le bouton Pause
void afficherBoutonPause() {
    // Redimensionner l'image si nécessaire
    float scaleX = 0.8f; // Échelle en X (ajustez selon vos besoins)
    float scaleY = 0.8f; // Échelle en Y (ajustez selon vos besoins)

    // Calculer la largeur et la hauteur du bouton
    float buttonWidth = boutonPauseTexture.width * scaleX;
    float buttonHeight = boutonPauseTexture.height * scaleY;

    // Positionner le bouton en haut à droite
    int posX = GetScreenWidth() - buttonWidth - 10; // 10 pixels d'écart du bord droit
    int posY = 10; // Position Y: 10px du haut

    // Dessiner le bouton
    DrawTextureEx(boutonPauseTexture, (Vector2){posX, posY}, 0.0f, scaleX, WHITE);
}
 // Méthode pour détecter un clic sur le bouton Pause
bool detecterClicPause() {
    float scaleX = 0.8f; // Échelle en X
    float scaleY = 0.8f; // Échelle en Y

    // Calculer la largeur et la hauteur du bouton
    float buttonWidth = boutonPauseTexture.width * scaleX;
    float buttonHeight = boutonPauseTexture.height * scaleY;

    // Positionner le bouton en haut à droite
    int posX = GetScreenWidth() - buttonWidth - 10; // 10 pixels d'écart du bord droit
    int posY = 10; // Position Y: 10px du haut

    Vector2 souris = GetMousePosition(); // Obtenir la position de la souris
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && // Vérifier si le bouton gauche de la souris est pressé
           souris.x >= posX && souris.x <= posX + buttonWidth && // Vérifier si la souris est dans la zone du bouton
           souris.y >= posY && souris.y <= posY + buttonHeight;  // Vérifier si la souris est dans la zone du bouton
}
// Méthode pour détecter un clic sur le bouton Reprendre
bool detecterClicReprendre() {
    float scaleX = 0.8f; // Échelle en X
    float scaleY = 0.8f; // Échelle en Y

    // Calculer la largeur et la hauteur du bouton
    float buttonWidth = 200; // Largeur du bouton "Reprendre"
    float buttonHeight = 50; // Hauteur du bouton "Reprendre"

    // Positionner le bouton "Reprendre" à gauche du bouton "Pause"
    int posXPause = GetScreenWidth() - boutonPauseTexture.width * scaleX - 10; // Position X du bouton "Pause"
    int posXReprendre = posXPause - buttonWidth - 10; // Position X du bouton "Reprendre"
    int posY = 10; // Position Y: 10px du haut

    Vector2 souris = GetMousePosition(); // Obtenir la position de la souris
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && // Vérifier si le bouton gauche de la souris est pressé
           souris.x >= posXReprendre && souris.x <= posXReprendre + buttonWidth && // Vérifier si la souris est dans la zone du bouton
           souris.y >= posY && souris.y <= posY + buttonHeight; // Vérifier si la souris est dans la zone du bouton
}
// Méthode pour afficher un message de perte
void afficherMessagePerte(int &buttonsY, int buttonHeight) {
    const char* message = "Vous avez perdu !"; // Message à afficher
    int messageWidth = MeasureText(message, 30);  // Largeur du message
    int messageX = (GetScreenWidth() - messageWidth) / 2; // Centrer le message

    // Afficher le message
    DrawText(message, messageX, 300, 30, RED); // Position Y ajustée

    // Bouton "Rejouer"
    int replayX = (GetScreenWidth() - 200) / 2; // Centrer le bouton "Rejouer"
    buttonsY = 400; // Position Y pour le bouton

    // Vérifier si la souris est au-dessus du bouton
    Vector2 mousePosition = GetMousePosition(); // Obtenir la position de la souris
    bool isMouseOver = mousePosition.x >= replayX && mousePosition.x <= replayX + 200 &&
                       mousePosition.y >= buttonsY && mousePosition.y <= buttonsY + buttonHeight;

    // Couleurs
    Color buttonColor = isMouseOver ? (Color){255, 165, 0, 255} : (Color){255, 140, 0, 255}; // Couleur du bouton (orange clair au survol)
    Color borderColor = isMouseOver ? (Color){255, 100, 0, 255} : (Color){200, 100, 0, 255}; // Couleur de la bordure (orange foncé au survol)

    // Dessiner la bordure arrondie (rectangle légèrement plus grand)
    float roundness = 0.2f; // Ajustez cette valeur pour modifier le degré d'arrondi
    DrawRectangleRounded((Rectangle){replayX - 2, buttonsY - 2, 204, buttonHeight + 4}, roundness, 10, borderColor); // Bordure
    DrawRectangleRounded((Rectangle){replayX, buttonsY, 200, buttonHeight}, roundness, 10, buttonColor); // Bouton

    // Afficher le texte du bouton
    DrawText("Rejouer", replayX + (200 - MeasureText("Rejouer", 20)) / 2, buttonsY + 10, 20, BLACK);
}
// Méthode pour afficher la fin du jeu
void afficherFinJeu(float tempsEcoule, const Niveau &niveau, Jeu &jeu, int &buttonsY, int buttonHeight) {
    int windowWidth = GetScreenWidth(); // Largeur de la fenêtre
    int windowHeight = GetScreenHeight(); // Hauteur de la fenêtre

    // Message de victoire
    const char* messageVictoire = "Vous avez gagne !"; // Message à afficher
    int messageWidth = MeasureText(messageVictoire, 30); // Largeur du message
    int messageHeight = 30; // Hauteur du texte
    int messageX = (windowWidth - messageWidth) / 2;  // Centrer le message
    int messageY = (windowHeight - messageHeight) / 2 - 50; // Décalage vers le haut

    // Afficher le message
    DrawText(messageVictoire, messageX, messageY, 30, GREEN);

    // Afficher le temps écoulé
    int minutes = (int)(tempsEcoule / 60); // Calculer les minutes
    int secondes = (int)(tempsEcoule) % 60; // Calculer les secondes
    char buffer[50]; // Buffer pour le texte
    snprintf(buffer, sizeof(buffer), "Temps : %02d:%02d", minutes, secondes); // Formater le texte
    int timeWidth = MeasureText(buffer, 20); // Largeur du texte
    DrawText(buffer, (windowWidth - timeWidth) / 2, messageY + 40, 20, WHITE); // Afficher le temps
 // Afficher le meilleur score
    float meilleurScoreActuel = (niveau.getDifficulte() == "Facile") ? jeu.meilleurScoreFacile :
                                 (niveau.getDifficulte() == "Moyen") ? jeu.meilleurScoreMoyen :
                                 jeu.meilleurScoreDifficile; // Obtenir le meilleur score en fonction de la difficulté
    int meilleurMinutes = (int)(meilleurScoreActuel / 60); // Calculer les minutes du meilleur score
    int meilleurSecondes = (int)(meilleurScoreActuel) % 60; // Calculer les secondes du meilleur score
    char meilleurBuffer[50]; // Buffer pour le meilleur score
    snprintf(meilleurBuffer, sizeof(meilleurBuffer), "Meilleur Score : %02d:%02d", meilleurMinutes, meilleurSecondes); // Formater le meilleur score
        int meilleurWidth = MeasureText(meilleurBuffer, 20); // Largeur du meilleur score
        DrawText(meilleurBuffer, (windowWidth - meilleurWidth) / 2, messageY + 70, 20, WHITE); // Afficher le meilleur score

   // Boutons
    const char* replayText = "Rejouer";
    const char* quitText = "Quitter";
    const char* nextText = "Suivant";

    int buttonWidth = 200; // Largeur des boutons
    buttonsY = messageY + 100; // Décalage vers le bas

    // Vérifier si la souris est au-dessus des boutons
    Vector2 mousePosition = GetMousePosition(); // Obtenir la position de la souris
    Color buttonColor;
    Color borderColor;

    // Rejouer Button
    buttonColor = (mousePosition.x >= (windowWidth - buttonWidth) / 2 && mousePosition.x <= (windowWidth - buttonWidth) / 2 + buttonWidth &&
                   mousePosition.y >= buttonsY && mousePosition.y <= buttonsY + buttonHeight) ? 
                   (Color){255, 165, 0, 255} : (Color){255, 140, 0, 255}; // Orange clair au survol
    borderColor = (mousePosition.x >= (windowWidth - buttonWidth) / 2 && mousePosition.x <= (windowWidth - buttonWidth) / 2 + buttonWidth &&
                   mousePosition.y >= buttonsY && mousePosition.y <= buttonsY + buttonHeight) ? 
                   (Color){255, 100, 0, 255} : (Color){200, 100, 0, 255}; // Bordure plus foncée au survol
    DrawRectangleRounded((Rectangle){(windowWidth - buttonWidth) / 2, buttonsY, buttonWidth, buttonHeight}, 0.2f, 10, borderColor); // Bordure
    DrawRectangleRounded((Rectangle){(windowWidth - buttonWidth) / 2 + 2, buttonsY + 2, buttonWidth - 4, buttonHeight - 4}, 0.2f, 10, buttonColor); // Bouton
    DrawText(replayText, (windowWidth - buttonWidth) / 2 + (buttonWidth - MeasureText(replayText, 20)) / 2, buttonsY + 10, 20, WHITE); // Texte

    // Quitter Button
    buttonColor = (mousePosition.x >= (windowWidth - buttonWidth) / 2 && mousePosition.x <= (windowWidth - buttonWidth) / 2 + buttonWidth &&
                   mousePosition.y >= buttonsY + buttonHeight + 20 && mousePosition.y <= buttonsY + buttonHeight + 20 + buttonHeight) ? 
                   (Color){255, 165, 0, 255} : (Color){255, 140, 0, 255}; // Orange clair au survol
    borderColor = (mousePosition.x >= (windowWidth - buttonWidth) / 2 && mousePosition.x <= (windowWidth - buttonWidth) / 2 + buttonWidth &&
                   mousePosition.y >= buttonsY + buttonHeight + 20 && mousePosition.y <= buttonsY + buttonHeight + 20 + buttonHeight) ? 
                   (Color){255, 100, 0, 255} : (Color){200, 100, 0, 255}; // Bordure plus foncée au survol
    DrawRectangleRounded((Rectangle){(windowWidth - buttonWidth) / 2, buttonsY + buttonHeight + 20, buttonWidth, buttonHeight}, 0.2f, 10, borderColor); // Bordure
    DrawRectangleRounded((Rectangle){(windowWidth - buttonWidth) / 2 + 2, buttonsY + buttonHeight + 22, buttonWidth - 4, buttonHeight - 4}, 0.2f, 10, buttonColor); // Bouton
    DrawText(quitText, (windowWidth - buttonWidth) / 2 + (buttonWidth - MeasureText(quitText, 20)) / 2, buttonsY + buttonHeight + 20 + 10, 20, WHITE); // Texte

    // Suivant Button (si applicable)
    if (niveau.getDifficulte() != "Difficile") {
        buttonColor = (mousePosition.x >= (windowWidth - buttonWidth) / 2 && mousePosition.x <= (windowWidth - buttonWidth) / 2 + buttonWidth &&
                       mousePosition.y >= buttonsY + 2 * (buttonHeight + 20) && mousePosition.y <= buttonsY + 2 * (buttonHeight + 20) + buttonHeight) ? 
                       (Color){255, 165, 0, 255} : (Color){255, 140, 0, 255}; // Orange clair au survol
        borderColor = (mousePosition.x >= (windowWidth - buttonWidth) / 2 && mousePosition.x <= (windowWidth - buttonWidth) / 2 + buttonWidth &&
                       mousePosition.y >= buttonsY + 2 * (buttonHeight + 20) && mousePosition.y <= buttonsY + 2 * (buttonHeight + 20) + buttonHeight) ? 
                       (Color){255, 100, 0, 255} : (Color){200, 100, 0, 255}; // Bordure plus foncée au survol
        DrawRectangleRounded((Rectangle){(windowWidth - buttonWidth) / 2, buttonsY + 2 * (buttonHeight + 20), buttonWidth, buttonHeight}, 0.2f, 10, borderColor); // Bordure
        DrawRectangleRounded((Rectangle){(windowWidth - buttonWidth) / 2 + 2, buttonsY + 2 * (buttonHeight + 20) + 2, buttonWidth - 4, buttonHeight - 4}, 0.2f, 10, buttonColor); // Bouton
        DrawText(nextText, (windowWidth - buttonWidth) / 2 + (buttonWidth - MeasureText(nextText, 20)) / 2, buttonsY + 2 * (buttonHeight + 20) + 10, 20, WHITE); // Texte
    }
}
// Fonction qui détecte si le bouton "Rejouer" a été cliqué par l'utilisateur
bool detecterClicRejouer(int buttonsY, int buttonHeight) {
    // Récupère la position actuelle de la souris
    Vector2 souris = GetMousePosition();
    
    // Calcule la position X du bouton "Rejouer"
    // Le bouton a une largeur de 200 pixels et est centré horizontalement sur l'écran
    int replayX = (GetScreenWidth() - 200) / 2; 
    
    // Vérifie si le bouton gauche de la souris a été pressé
    // et si la position de la souris est à l'intérieur des limites du bouton "Rejouer"
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && // Vérifie si le bouton gauche est pressé
           souris.x >= replayX && souris.x <= replayX + 200 && // Vérifie la position X
           souris.y >= buttonsY && souris.y <= buttonsY + buttonHeight; // Vérifie la position Y
}

// Fonction qui détecte si le bouton "Quitter" a été cliqué par l'utilisateur
bool detecterClicQuitter(int buttonsY, int buttonHeight) {
    // Récupère la position actuelle de la souris
    Vector2 souris = GetMousePosition();
    
    // Calcule la position X du bouton "Quitter"
    // Le bouton a une largeur de 200 pixels et est centré horizontalement sur l'écran
    int quitX = (GetScreenWidth() - 200) / 2; 
    
    // Vérifie si le bouton gauche de la souris a été pressé
    // et si la position de la souris est à l'intérieur des limites du bouton "Quitter"
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && // Vérifie si le bouton gauche est pressé
           souris.x >= quitX && souris.x <= quitX + 200 && // Vérifie la position X
           souris.y >= buttonsY + buttonHeight + 20 && // Vérifie la position Y avec un espacement de 20 pixels
           souris.y <= buttonsY + buttonHeight + 20 + buttonHeight; // Vérifie la position Y pour la hauteur du bouton
}

// Fonction qui détecte si le bouton "Suivant" a été cliqué par l'utilisateur
bool detecterClicSuivant(int buttonsY, int buttonHeight) {
    // Récupère la position actuelle de la souris
    Vector2 souris = GetMousePosition();
    
    // Calcule la position X du bouton "Suivant"
    // Le bouton a une largeur de 200 pixels et est centré horizontalement sur l'écran
    int nextX = (GetScreenWidth() - 200) / 2; 
    
    // Vérifie si le bouton gauche de la souris a été pressé
    // et si la position de la souris est à l'intérieur des limites du bouton "Suivant"
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && // Vérifie si le bouton gauche est pressé
           souris.x >= nextX && souris.x <= nextX + 200 && // Vérifie la position X
           souris.y >= buttonsY + 2 * (buttonHeight + 20) && // Vérifie la position Y avec un espacement de 20 pixels entre les boutons
           souris.y <= buttonsY + 2 * (buttonHeight + 20) + buttonHeight; // Vérifie la position Y pour la hauteur du bouton
}

};


int main() {
     // Initialiser la fenêtre du jeu
    InitWindow(1500, 980, "Jeu de Labyrinthe");
    SetTargetFPS(60);
    // Load different background images for menu and game
    Texture2D menuBackground = LoadTexture("MENU_BACKGROUND.png"); // Image de fond pour l'écran de menu
    Texture2D gameBackground = LoadTexture("GAME_BACKGROUND.png"); // Image de fond pour l'écran de jeu
    // Récupérer les dimensions de la fenêtre
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    // Créer une instance de la classe Game
    Game game;
    std::string niveauSelectionne = "";
    bool startScreen = true;
    int buttonsY; // Position verticale des boutons
    int buttonHeight = 50; // Hauteur des boutons
   // Boucle principale du programme
    while (!WindowShouldClose()) {
        if (startScreen) {
            BeginDrawing();
             // Dessiner l'image de fond du menu redimensionnée pour remplir la fenêtre
            DrawTexturePro(menuBackground, 
                {0, 0, (float)menuBackground.width, (float)menuBackground.height}, 
                {0, 0, (float)windowWidth, (float)windowHeight}, 
                {0, 0}, 0.0f, WHITE);
            game.displayInterface(); // Afficher l'interface d'accueil
            if (game.detectStartClick()) {
                startScreen = false;// Passer à l'écran du menu de sélection
            }
            EndDrawing();
        } else if (niveauSelectionne == "") {
            // Afficher le menu de sélection des niveaux
            BeginDrawing();
              // Dessiner l'image de fond du menu
            DrawTexturePro(menuBackground, 
                {0, 0, (float)menuBackground.width, (float)menuBackground.height}, 
                {0, 0, (float)windowWidth, (float)windowHeight}, 
                {0, 0}, 0.0f, WHITE);
            game.afficherMenu(); // Afficher les options de niveau
            niveauSelectionne = game.detecterClicDifficulte(); // Détecter la sélection de niveau
            EndDrawing();
        } else {
            // Initialiser le niveau, le labyrinthe et le joueur
            Niveau niveau(niveauSelectionne);
            Labyrinthe labyrinthe(niveau.getTailleLabyrinthe(), niveau.getTailleLabyrinthe());
            Joueur joueur(1, 1);
            Jeu jeu(labyrinthe, niveau);  // Créer l'instance du jeu avec les paramètres actuels
            bool jeuTermine = false;// Variable pour indiquer si le jeu est terminé
            bool joueurPerdu = false; // Variable pour indiquer si le joueur a perdu
            float tempsDebut = GetTime();
            int cellSize = 40;// Taille d'une cellule du labyrinthe en pixels
           // Calculer le décalage pour centrer le labyrinthe dans la fenêtre
            int offsetX = (GetScreenWidth() - (labyrinthe.getLargeur() * cellSize)) / 2;
            int offsetY = (GetScreenHeight() - (labyrinthe.getHauteur() * cellSize)) / 2;
           // Boucle principale du jeu
            while (!WindowShouldClose()) {
            float deltaTime = GetFrameTime(); // Calculer deltaTime
             // Gérer la pause
            if (!jeu.estEnPause && jeu.detecterClicPause()) {
                    jeu.estEnPause = true; // Mettre le jeu en pause
                }
               
                if (!jeu.estEnPause && !jeuTermine) {
                     // Gérer les mouvements du joueur
                    if (IsKeyDown(KEY_RIGHT)) joueur.deplacer(1, 0, labyrinthe);
                    if (IsKeyDown(KEY_LEFT)) joueur.deplacer(-1, 0, labyrinthe);
                    if (IsKeyDown(KEY_UP)) joueur.deplacer(0, -1, labyrinthe);
                    if (IsKeyDown(KEY_DOWN)) joueur.deplacer(0, 1, labyrinthe);

                    // Mettre à jour les obstacles
                    jeu.mettreAJourObstacles(labyrinthe, deltaTime);

                    // Vérifier les collisions avec les obstacles
                    if (jeu.detecterCollisionAvecObstacles(joueur)) {
                        joueurPerdu = true; 
                        jeuTermine = true; // Terminer le jeu si collision
                    }
                     // Vérifier si le joueur a gagné
                    if (joueur.aGagne(labyrinthe)) {
                        jeuTermine = true; // Marquer le jeu comme terminé
                        jeu.score = jeu.tempsEcoule;  // Enregistrer le score
                        jeu.mettreAJourMeilleurScore(niveau.getDifficulte(), jeu.tempsEcoule);// Mettre à jour le meilleur score
                    }
                    jeu.tempsEcoule += deltaTime; // Mettez à jour le temps écoulé seulement si le jeu n'est pas en pause
                }
                // Détecter le clic pour réinitialiser le jeu
             if (jeu.detecterClicReinitialiser()) {
               joueur = Joueur(1, 1); // Réinitialiser le joueur
                labyrinthe = Labyrinthe(niveau.getTailleLabyrinthe(), niveau.getTailleLabyrinthe()); // Générer un nouveau labyrinthe
                 tempsDebut = GetTime(); // Réinitialiser le temps
                }
                BeginDrawing();
                // Dessiner l'image de fond du jeu
                DrawTexturePro(gameBackground, 
                    {0, 0, (float)gameBackground.width, (float)gameBackground.height}, 
                    {0, 0, (float)windowWidth, (float)windowHeight}, 
                    {0, 0}, 0.0f, WHITE);
                if (!jeuTermine) {
                     // Afficher le bouton de réinitialisation
                    jeu.afficherBoutonReinitialiser(); // Afficher le bouton de réinitialisation
                      // Vérifier si le joueur a cliqué sur le bouton de réinitialisation
                if (jeu.detecterClicReinitialiser()) {
                  joueur = Joueur(1, 1); // Réinitialiser le joueur
                  labyrinthe = Labyrinthe(niveau.getTailleLabyrinthe(), niveau.getTailleLabyrinthe()); // Générer un nouveau labyrinthe
                  jeu.tempsEcoule=0;
                  tempsDebut = GetTime(); // Réinitialiser le temps
                 }
                 // Afficher le labyrinthe et le joueur
                    labyrinthe.afficher(offsetX, offsetY);
                    joueur.afficher(offsetX, offsetY);
                    jeu.afficherTemps(10, 10);// Afficher le temps écoulé
                 jeu.afficherBoutonPause(); // Afficher le bouton Pause
                  // Afficher les obstacles
                    for (const auto &obstacle : jeu.obstacles) {
                        obstacle.afficher(offsetX, offsetY);
                    }
                } else {
                    if (joueurPerdu) {
                        // Afficher le message de perte
                       jeu.afficherMessagePerte(buttonsY, buttonHeight); 
                        // Vérifier si le joueur a cliqué sur le bouton de rejouer
                        if (jeu.detecterClicRejouer(buttonsY, buttonHeight)) {
                            joueur = Joueur(1, 1);// Réinitialiser la position du joueur
                            labyrinthe = Labyrinthe(niveau.getTailleLabyrinthe(), niveau.getTailleLabyrinthe());
                            jeu.tempsEcoule=0;// Réinitialiser le temps écoulé
                            tempsDebut = GetTime();// Réinitialiser le temps de début
                            jeuTermine = false;// Réinitialiser l'état du jeu
                            joueurPerdu = false; // Réinitialiser la variable de perte
                            
                        }
                    } else {
                        // Afficher l'écran de fin de jeu
                        jeu.afficherFinJeu(jeu.tempsEcoule, niveau, jeu,buttonsY,buttonHeight);
                        // Logique du bouton de rejouer
                        if (jeu.detecterClicRejouer(buttonsY, buttonHeight)) {
                            joueur = Joueur(1, 1); // Réinitialiser la position du joueur
                            labyrinthe = Labyrinthe(niveau.getTailleLabyrinthe(), niveau.getTailleLabyrinthe());// Générer un nouveau labyrinthe
                            jeu.tempsEcoule=0;// Réinitialiser le temps écoulé
                            tempsDebut = GetTime(); // Réinitialiser le temps de début
                            jeuTermine = false;// Réinitialiser l'état du jeu
                            joueurPerdu = false;// Réinitialiser l'état de perte
                        }
                    }
                }

                // Logique de progression de difficulté
                if (niveau.getDifficulte() != "Difficile" && jeu.detecterClicSuivant(buttonsY, buttonHeight)) {
                     // Augmenter la difficulté du niveau
                    if (niveau.getDifficulte() == "Facile") {
                        niveau = Niveau("Moyen");
                    } else if (niveau.getDifficulte() == "Moyen") {
                        niveau = Niveau("Difficile");
                    }
                     // Réinitialiser le joueur et le labyrinthe
                    joueur = Joueur(1, 1);
                    labyrinthe = Labyrinthe(niveau.getTailleLabyrinthe(), niveau.getTailleLabyrinthe());
                    jeu.tempsEcoule=0;
                    jeu = Jeu(labyrinthe, niveau); // Créer une nouvelle instance de Jeu
                    // Recalculer les offsets pour centrer le labyrinthe
                    offsetX = (GetScreenWidth() - (labyrinthe.getLargeur() * cellSize)) / 2;
                    offsetY = (GetScreenHeight() - (labyrinthe.getHauteur() * cellSize)) / 2;
                    tempsDebut = GetTime();
                    jeuTermine = false;
                }

                // Logique de sortie du jeu
                if (jeu.detecterClicQuitter(buttonsY, buttonHeight)) {
                    CloseWindow();  // Fermer la fenêtre et quitter le jeu
                }
               // Logique du menu de pause
               if (jeu.estEnPause) {
               jeu.afficherMenuPause();// Afficher le menu de pause
               // Vérifier si le joueur a cliqué pour reprendre
               if (jeu.detecterClicReprendre()) {
                jeu.estEnPause = false; // Reprendre le jeu
                }
                }
                EndDrawing();
            }
        }
    }
    
    UnloadTexture(menuBackground); // Décharger la texture du menu
    UnloadTexture(gameBackground); // Décharger la texture du jeu
    CloseWindow();// Terminer et fermer la fenêtre créée par Raylib
    return 0;
}