#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 50
#define FILENAME "Vols.txt"

// Structure de données pour un horaire de vol
struct FlightSchedule {
    int index;
    char DepartCity[20];
    char ArrivalCity[20];
    char DepartTime[6];
    char ArrivalTime[6];
};

// Fonction pour ajouter un vol
void AddFlight(struct FlightSchedule flight, struct FlightSchedule flights[], int *numFlights) {
    if (*numFlights >= MAX_FLIGHTS) {
        printf("Impossible d'ajouter plus de vols.\n");
        return;
    }
    flight.index = *numFlights;
    flights[*numFlights] = flight;
    *numFlights += 1;
    printf("Vol ajoute avec succes.\n");
}

// Fonction pour afficher la liste des vols
void ViewFlight(struct FlightSchedule flights[], int numFlights) {
    if (numFlights == 0) {
        printf("Il n'y a pas de vols.\n");
        return;
    }
    printf("Liste des vols :\n");
    for (int i = 0; i < numFlights; i++) {
        printf("%d. De %s a %s, Depart : %s, Arrivee : %s\n", flights[i].index, flights[i].DepartCity, flights[i].ArrivalCity, flights[i].DepartTime, flights[i].ArrivalTime);
    }
}

// Fonction pour supprimer un vol
void DeleteFlight(int index, struct FlightSchedule flights[], int *numFlights) {
    if (index < 0 || index >= *numFlights) {
        printf("Index invalide.\n");
        return;
    }
    for (int i = index; i < *numFlights - 1; i++) {
        flights[i] = flights[i+1];
        flights[i].index = i;
    }
    *numFlights -= 1;
    printf("Vol supprime avec succes.\n");
}

// Fonction de comparaison pour le tri des vols selon l'heure de départ
int CompareDepartTime(const void* a, const void* b) {
    const struct FlightSchedule *flightA = (struct FlightSchedule*) a;
    const struct FlightSchedule *flightB = (struct FlightSchedule*) b;
    return strcmp(flightA->DepartTime, flightB->DepartTime);
}

// Fonction pour trier la liste des vols selon l'heure de départ
void SortFlight(struct FlightSchedule flights[], int numFlights) {
    qsort(flights, numFlights, sizeof(struct FlightSchedule), CompareDepartTime);
    printf("Liste des vols triee avec succes selon l'heure de depart.\n");
}

// Fonction principale
int main() {
    struct FlightSchedule flights[MAX_FLIGHTS];
    int numFlights = 0;

    // Lecture des données de vol à partir du fichier "flight.txt"
    FILE *fp = fopen(FILENAME, "r");
    if (fp != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), fp) != NULL && numFlights < MAX_FLIGHTS) {
            struct FlightSchedule flight;
            sscanf(line, "%d %s %s %s %s", &flight.index, flight.DepartCity, flight.ArrivalCity, flight.DepartTime, flight.ArrivalTime);
            flights[numFlights] = flight;
            numFlights++;
        }
        fclose(fp);
        printf("%d vols ont ete lus a partir du fichier %s.\n", numFlights, FILENAME);
    } else {
        printf("Le fichier %s n'a pas pu être ouvert.\n", FILENAME);
    }

    // Menu principal
    while (1) {
        printf("\nMenu principal :\n");
        printf("1. Ajouter un vol\n");
        printf("2. Afficher la liste des vols\n");
        printf("3. Supprimer un vol\n");
        printf("4. Trier la liste des vols selon l'heure de depart\n");
        printf("5. Quitter\n");
        printf("Choisissez une option : ");
        int choice;
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice) {
            case 1:
                printf("\nAjouter un vol :\n");
                struct FlightSchedule newFlight;
                printf("Ville de depart : ");
                scanf("%s", newFlight.DepartCity);
                printf("Ville d'arrivee : ");
                scanf("%s", newFlight.ArrivalCity);
                printf("Heure de depart (hh:mm) : ");
                scanf("%s", newFlight.DepartTime);
                printf("Heure d'arrivee (hh:mm) : ");
                scanf("%s", newFlight.ArrivalTime);
                AddFlight(newFlight, flights, &numFlights);
                break;
            case 2:
                printf("\nAfficher la liste des vols :\n");
                ViewFlight(flights, numFlights);
                break;
            case 3:
                printf("\nSupprimer un vol :\n");
                printf("Index du vol a supprimer : ");
                int index;
                scanf("%d", &index);
                fflush(stdin);
                DeleteFlight(index, flights, &numFlights);
                break;
            case 4:
                printf("\nTrier la liste des vols selon l'heure de depart :\n");
                SortFlight(flights, numFlights);
                break;
            case 5:
                printf("\nAu revoir !\n");
                // Écriture des données de vol dans le fichier "Vols.txt"
                fp = fopen(FILENAME, "w");
                if (fp != NULL) {
                    for (int i = 0; i < numFlights; i++) {
                        fprintf(fp, "%d %s %s %s %s\n", flights[i].index, flights[i].DepartCity, flights[i].ArrivalCity, flights[i].DepartTime, flights[i].ArrivalTime);
                    }
                    fclose(fp);
                    printf("%d vols ont ete ecrits dans le fichier %s.\n", numFlights, FILENAME);
                } else {
                    printf("Le fichier %s n'a pas pu etre ouvert.\n", FILENAME);
                }
                return 0;
            default:
                printf("Option invalide.\n");
        }
    }

    return 0;
}
