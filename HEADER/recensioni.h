#include "utenti.h"
#include "libri.h"

typedef struct {
    char testo [200];
    char username[20];
    char codice[10];
    char numero[10];
} recensioni;

struct nodo_recensione{
    recensioni recensione;
    struct nodo_recensione* next;
};

struct nodo_punt{
        struct nodo_recensione* indirizzo; //lista di puntatori ovvero il campo dati è un puntatore
        struct nodo_punt* next;
};

struct nodo_punt_libro{
    struct nodo_libro* indirizzo;
    struct nodo_punt_libro* next;
};

//inserimento in coda puntATORI
int inserimento_coda_puntatori (struct nodo_punt** head, struct nodo_punt** tail,struct nodo_recensione* indirizzo);

//inserimento in coda punt libri
int inserimento_coda_punt_libri (struct nodo_punt_libro** head, struct nodo_punt_libro** tail,struct nodo_libro* indirizzo);

//leggere il file lista_recensioni.txt
void leggifile_recensione(struct nodo_recensione** lista_recensioni, struct nodo_recensione** tail_recensione,
                          struct nodo_libro* lista_libri, struct nodo_utente* lista_utenti);

// funzione stampa RECENSIONI
void stampa_recensioni (struct nodo_libro* head_l, struct nodo_utente* head_u,char username[20], bool admin);

//inserimento in coda RECENSIONI
int inserimento_coda_recensioni (struct nodo_recensione** head,struct nodo_recensione** tail, recensioni recensione);

int scrivi_recensione (struct nodo_recensione** head, struct nodo_recensione** tail,char username[20], struct nodo_libro* lista_libri);

//scrittura su file lista_receensioni.txt
void scrivifile_recensioni(struct nodo_recensione* head);

void modifica_recensione(struct nodo_recensione* lista_recensioni, char username[20]);

void login(struct nodo_utente* lista_utenti, struct nodo_utente* tail_utente, struct nodo_libro** lista_libri,struct nodo_libro** tail_libro,
           struct nodo_recensione* lista_recensioni, struct nodo_recensione* tail_recensione);

