std::vector<std::vector<int>> GridGame::horizontal_check(std::vector<int> couple, int nbMinAlignes) {
    std::vector<std::vector<int> > aligneds;
    int x = couple[1];
    int y = couple[0];
    int color = this->tab[y][x]->getColor();
    int nbAlignes = 1;
    bool left = true;
    bool continuer = true;
    int decalage = 1;
    aligneds.push_back(couple);
    std::string chaine = "";

    while (continuer) {
        chaine += "-";
        if (left) {
            chaine += "left";
            if ((x - decalage) >= 0) {  // we are in the tab
                if (this->tab[y][x - decalage] != NULL) {
                    int c = this->tab[y][x - decalage]->getColor();
                    if (this->tab[y][x - decalage]->getColor() == color) {
                        chaine += "(ok) color=" + std::to_string(decalage) +  "   ";
                        std::vector<int> continuus;
                        continuus.push_back(y);
                        continuus.push_back(x - decalage);
                        aligneds.push_back(continuus);
                        decalage++;
                        nbAlignes++;
                    } else {  // not the same color
                        chaine += "(notok) color=" + std::to_string(c) +  "   ";
                        decalage = 1;
                        left = false;
                    }
                } else {  // NULL
                    decalage = 1;
                    left = false;
                    chaine += "NULL    ";
                }
            } else {  // outside the tab
                int n = x - decalage;
                chaine += "OUT(" + std::to_string(n)+")   ";
                decalage = 1;
                left = false;  // let's go to the right way ;)
            }
        } else {  // right
            chaine += "right";
            if ((x + decalage) < this->largeur) {
                if (this->tab[y][x + decalage] != NULL) {
                    if (this->tab[y][x + decalage]->getColor() == color) {
                        chaine += "(ok)   ";
                        std::vector<int> continuus;
                        continuus.push_back(y);
                        continuus.push_back(x + decalage);
                        aligneds.push_back(continuus);
                        decalage++;
                        nbAlignes++;
                    } else {
                        chaine += "diffcolor";
                        continuer = false;
                    }
                } else {
                    chaine += "NULL  ";
                    continuer = false;
                }
            } else {
                chaine += "OUT   ";
                continuer = false;
            }
        }
    }
    if (nbAlignes >= nbMinAlignes) {
        return aligneds;
        std::cout << "La case" << y << ", " << x << "est alignée horizontalement avec" << nbAlignes << "cases." << std::endl;
        std::cout << chaine << std::endl;
        std::cout << std::endl;
    }
    while (!aligneds.empty()) {
        aligneds.pop_back();
    }
    return aligneds;
}