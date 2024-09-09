#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_VIOLET  "\x1b[35m"
#define COLOR_RESET   "\x1b[0m"

// structure d'une tache (id, titre, description, deadline, status)
typedef struct {
    char id[5];
    char titre[35];
    char description[255];
    __time_t deadline;
    char status[35]; // types: "a realiser", "en cours de realisation", "finalisee".
} Tache;

Tache taches[99];
int taille = 0;

// generer un id de 4 chiffres aleatoires
void generateID(int position){
    char chiffres[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    int nbre_chiffres = sizeof(chiffres);
    char id[5]; 
    int random;
    
    for(int i=0; i<4; i++){
        random = rand() % (nbre_chiffres - 0) + 1;
        id[i] = chiffres[random];
    }
    id[4] = '\0';
    strcpy(taches[position].id, id);
}

// fonction qui recherche par id et retourner position si trouver, -1 sinon
int rechercheParID(char id[]){
    for(int i=0; i<taille; i++){
        if(strcmp(id, taches[i].id) == 0){
            return i;
        }
    }
    return -1;
}

// fonction qui recherche par titre et retourner position si trouver, -1 sinon
int rechercheParTitre(char titre[]){
    for(int i=0; i<taille; i++){
        if(strcmp(titre, taches[i].titre) == 0){
            return i;
        }
    }
    return -1;
}

// fonction pour ajouter une tache
void ajouterTache(){
    system("clear");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                      ajouter une tache                       \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    int hours;
    printf("donner les informations de votre tache \n");
    printf("titre: "); scanf(" %[^\n]s", taches[taille].titre);
    printf("description: "); scanf(" %[^\n]s", taches[taille].description);
    printf("entrer un deadline en heures: "); scanf("%d", &hours);
    taches[taille].deadline = ( hours * 3600000 ) + time(NULL);
    strcpy(taches[taille].status, "a realiser");
    generateID(taille);

    printf(COLOR_GREEN "tache ajoutee sous l'idintifiant '%s' avec succes..\n" COLOR_RESET, taches[taille].id);
    // incrementer le nombre des taches
    taille = taille + 1;
}

// fonction pour ajouter plusieurs taches
void ajouterPlusieursTaches(){
    system("clear");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                   ajouter plusieurs tache                    \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    int nbre, hours;
    printf("combien de tache voulez-vous ajoutez? "); scanf("%d", &nbre);
    for(int i=0; i<nbre; i++){
        printf("donner les informations de votre tache \n");
        printf("titre: "); scanf(" %[^\n]s", taches[taille + i].titre);
        printf("description: "); scanf(" %[^\n]s", taches[taille + i].description);
        printf("entrer un deadline en heures: "); scanf("%d", &hours);
        taches[taille + i].deadline = ( hours * 3600000 ) + time(NULL);
        strcpy(taches[taille + i].status, "a realiser");
        generateID(taille + i);

        printf(COLOR_GREEN "tache ajoutee sous l'idintifiant '%s' avec succes..\n" COLOR_RESET, taches[taille + i].id);
    }
    // incremente le nombre des tache
    taille = taille + nbre;
}

// fonction pour afficher tous les taches
void afficherTaches(){
    system("clear");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     afficher les taches                      \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun tache availaible, esseyez d'ajoutez une\n" COLOR_RESET);
        return;
    }
    for(int i=0; i<taille; i++){
        printf(COLOR_VIOLET "--- tache %d ---\n" COLOR_RESET, i+1);
        printf("Idintifiant de tache: %s\n", taches[i].id);
        printf("titre: %s\n", taches[i].titre);
        printf("description: %s\n", taches[i].description);
        printf("status: %s\n", taches[i].status);
        printf("deadline: %ld\n", taches[i].deadline);
    }
}

// fonction pour rechercher une tache
void rechercherTache(){
    system("clear");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                    rechercher une tache                      \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun tache availaible maintenant..\n" COLOR_RESET);
        return;
    }
    char id[5], test_id[20], titre[35];
    int choice, position;
    do{
        printf(COLOR_YELLOW "1- rechercher par UID\n");
        printf("2- rechercher par titre\n");
        printf("0- retourner au menu principale\n" COLOR_RESET);
        printf("entrez votre choix: ");
        scanf("%d", &choice);

    switch(choice){
        case 1:
            printf("entrer l'identifiant de tache le rechercher (4 chiffres): "); 
            scanf(" %[^\n]s", test_id);

            strcpy(id, test_id);
            position = rechercheParID(id);
            if(position == -1){
                printf(COLOR_RED "tache ne pas trouvee..\n" COLOR_RESET);
                return;
            }
            else{
                printf(COLOR_VIOLET "--- tache ---\n" COLOR_RESET);
                printf("Idintifiant de tache: %s\n", taches[position].id);
                printf("titre: %s\n", taches[position].titre);
                printf("description: %s\n", taches[position].description);
                printf("status: %s\n", taches[position].status);
                printf("deadline: %ld\n", taches[position].deadline);
            }
            return; break;
        case 2: 
            printf("entrer le titre de tache pour le rechercher: "); 
            scanf(" %[^\n]s", titre);

            position = rechercheParTitre(titre);
            if(position == -1){
                printf(COLOR_RED "tache ne pas trouvee..\n" COLOR_RESET);
                return;
            }
            else{
                printf(COLOR_VIOLET "--- tache ---\n" COLOR_RESET);
                printf("Idintifiant de tache: %s\n", taches[position].id);
                printf("titre: %s\n", taches[position].titre);
                printf("description: %s\n", taches[position].description);
                printf("status: %s\n", taches[position].status);
                printf("deadline: %ld\n", taches[position].deadline);
            }
            return; break;
        case 0: return; break;
        default:
            printf(COLOR_RED "choix ne pas valid...\n" COLOR_RESET);
            break;
    }

    }while(choice != 2);
    
}

// fonction modifier une tache, modifier la description, deadline ey status
void modifierTache(){
    system("clear");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                     modifier une tache                       \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun tache availaible maintenant..\n" COLOR_RESET);
        return;
    }
    int position;
    char id[5], test_id[30];

    printf("entrer l'identifiant de tache pour le rechercher (4 chiffres): "); 
    scanf(" %[^\n]s", test_id);

    strcpy(id, test_id);
    position = rechercheParID(id);
    if(position == -1){
        printf(COLOR_RED "tache ne pas trouvee..\n" COLOR_RESET);
        return;
    }
    else{
        int modification_type, hours;
        printf(COLOR_YELLOW "1- modifier la description\n");
        printf("2- modifier le status\n");
        printf("3- modifier le deadline\n");
        printf("4- modifier tous ces informations\n" COLOR_RESET);
        printf("entrer votre choix: "); scanf("%d", &modification_type);

        switch(modification_type){
            case 1:
                printf("entrer la nouvelle description: "); 
                scanf(" %[^\n]s", taches[position].description);
                printf(COLOR_GREEN "tache a ete modifiee avec succes..\n" COLOR_RESET);
                break;
            case 2:
                printf("entrer le nouveau status: "); 
                scanf(" %[^\n]s", taches[position].status);
                printf(COLOR_GREEN "tache a ete modifiee avec succes..\n" COLOR_RESET);
                break;
            case 3:
                printf("entrer le nouveau deadline: "); scanf("%d", &hours);
                taches[position].deadline = ( hours * 3600000 ) + time(NULL);
                printf(COLOR_GREEN "tache a ete modifiee avec succes..\n" COLOR_RESET);
                break;
            case 4:
                printf("entrer la nouvelle description: "); 
                scanf(" %[^\n]s", taches[position].description);
                printf("entrer le nouveau status: "); 
                scanf(" %[^\n]s", taches[position].status);
                printf("entrer le nouveau deadline: "); scanf("%d", &hours);
                taches[position].deadline = ( hours * 3600000 ) + time(NULL);
                printf(COLOR_GREEN "tache a ete modifiee avec succes..\n" COLOR_RESET);
                break;
        }
    }
}

// fonction supprimer une tache par ID, avec une confirmation pour suppression
void supprimerTache(){
    system("clear");
    printf(COLOR_YELLOW "--------------------------------------------------------------\n");
    printf("                    supprimer une tache                       \n");
    printf("--------------------------------------------------------------\n" COLOR_RESET);
    if(taille == 0){
        printf(COLOR_RED "aucun tache availaible maintenant..\n" COLOR_RESET);
        return;
    }
    int position;
    char id[5], test_id[30], confirmation[10];

    printf("entrer l'identifiant de tache pour le rechercher (4 chiffres): "); 
    scanf(" %[^\n]s", test_id);

    strcpy(id, test_id);
    position = rechercheParID(id);
    if(position == -1){
        printf(COLOR_RED "tache ne pas trouvee..\n" COLOR_RESET);
        return;
    }
    else{
        printf("confirmer votre demande pour supprimer (oui/non)? "); scanf("%s", confirmation);
        if(strcmp(confirmation, "oui") == 0){
            for(int i=position; i<taille; i++){
                taches[i] = taches[i + 1];
            }
            printf(COLOR_GREEN "tache effaces avec succes\n" COLOR_RESET);
            taille = taille - 1;
        }
        else{
            return;
        }
    }

}

void menu(){
    int choice;
    do{
        printf(COLOR_BLUE "--------------------------------------------------------------\n");
        printf("                      menu principale                         \n");
        printf("--------------------------------------------------------------\n" COLOR_RESET);
        printf("1- ajouter une tache\n");
        printf("2- ajouter plusieurs taches\n");
        printf("3- afficher la list des taches\n"); // trier par titre, par deadline, 
        printf("4- modifier une tache\n"); // modifier description, status, deadline  
        printf("5- rechercher une tache\n"); // rechercher par id, par titre
        printf("6- supprimer une tache\n"); // supprimer par id
        printf("7- afficher statistiques\n"); // nombre total des taches, nombre des taches complete et incomplete, nombre de jour restants jusqu'au delai de chaque tache.
        printf("0- sortir de menu principale\n"); 
        printf(COLOR_BLUE "--------------------------------------------------------------\n");
        printf("entrez votre choix: "); scanf("%d", &choice);
        printf("--------------------------------------------------------------\n" COLOR_RESET);


        switch(choice){
            case 1: ajouterTache(); break;
            case 2: ajouterPlusieursTaches(); break;
            case 3: afficherTaches(); break;
            case 4: modifierTache(); break;
            case 5: rechercherTache(); break;
            case 6: supprimerTache(); break;
            case 0:
                printf(COLOR_GREEN "merci pour votre visit..\n\n" COLOR_RESET);
                exit(1);
                break;
            default:
                printf(COLOR_RED "choix ne pas valid...\n" COLOR_RESET);
                break;
        }

    }
    while(choice != 7);
}

int main(){
    menu();

    printf("\n");
    return 0;
}
