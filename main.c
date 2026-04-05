#include <stdio.h>
#include <string.h>

#define MAX 100



struct Patient {
    int id;
    char nom[50];
    char prenom[50];
    char telephone[15];
    int actif;
};

struct RendezVous {
    int id;
    int idPatient;
    char date[15];
    int statut; // 0=Planifie 1=Confirme 2=Annule 3=Termine
};



struct Patient patients[MAX];
struct RendezVous rdv[MAX];

int nb_patients = 0, nb_rdv = 0;
int id_patient = 1, id_rdv = 1;

//  PATIENTS

void ajouter_patient() {
    if (nb_patients >= MAX) {
        printf("Tableau plein !\n");
        return;
    }

    struct Patient p;
    p.id = id_patient++;
    p.actif = 1;

    printf("Nom: ");
    scanf(" %[^\n]", p.nom);

    printf("Prenom: ");
    scanf(" %[^\n]", p.prenom);

    printf("Telephone: ");
    scanf("%s", p.telephone);

    patients[nb_patients++] = p;

    printf("Patient ajoute !\n");
}

void afficher_patients() {
    int i;
    for (i = 0; i < nb_patients; i++) {
        if (patients[i].actif == 1) {
            printf("ID:%d | %s %s | Tel:%s\n",
                   patients[i].id,
                   patients[i].prenom,
                   patients[i].nom,
                   patients[i].telephone);
        }
    }
}

int chercher_patient(int id) {
    int i;
    for (i = 0; i < nb_patients; i++) {
        if (patients[i].id == id && patients[i].actif == 1)
            return i;
    }
    return -1;
}

void supprimer_patient() {
    int id;
    printf("ID patient: ");
    scanf("%d", &id);

    int pos = chercher_patient(id);

    if (pos == -1) {
        printf("Introuvable\n");
        return;
    }

    patients[pos].actif = 0;
    printf("Supprime\n");
}

// RDV

void ajouter_rdv() {
    if (nb_rdv >= MAX) {
        printf("Tableau plein !\n");
        return;
    }

    int idP;
    printf("ID patient: ");
    scanf("%d", &idP);

    int pos = chercher_patient(idP);
    if (pos == -1) {
        printf("Patient inexistant\n");
        return;
    }

    struct RendezVous r;
    r.id = id_rdv++;
    r.idPatient = idP;
    r.statut = 0;

    printf("Date: ");
    scanf("%s", r.date);

    rdv[nb_rdv++] = r;

    printf("RDV ajoute\n");
}

void afficher_rdv() {
    int i;
    for (i = 0; i < nb_rdv; i++) {
        printf("ID:%d | Patient:%d | Date:%s | Statut:%d\n",
               rdv[i].id,
               rdv[i].idPatient,
               rdv[i].date,
               rdv[i].statut);
    }
}

//MENU
int main() {
    int choix;

    do {
        printf("\n1.Patient\n2.RDV\n0.Quitter\nChoix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_patient();
                afficher_patients();
                break;

            case 2:
                ajouter_rdv();
                afficher_rdv();
                break;
        }

    } while (choix != 0);

    return 0;
}
