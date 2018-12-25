g++ main.cpp Game.cpp Game_player.cpp Game_AI.cpp AI.cpp AI_hc.cpp AI_random.cpp tools.cpp Genetic_learning.cpp Learning_stats.cpp -std=c++0x -pthread


Il faut faire en sorte qui si il y a égalité il fasse le mouvement qui rapporte le plus après le premier coup

———————

2048 pour moi : 6 min
2048 pour l’ordi : 0.08s
-> 4500 fois + rapide

———————

Paramètres pour la comparaison
  int size = 4;
  int nbGeneration = 14;
  int nbIndiv = 20;
  int nbEvalPerIndiv = 75;
  float selectionRateBest = 0.3;
  float selectionRateOthers = 0.05;
  float mutationProba = 0.6;
  int nbrOfThreads = 4;


___________

évidemment c’était con de faire des biais, ils n’ont aucune influence car n’ont pas de « relation » avec la grille
