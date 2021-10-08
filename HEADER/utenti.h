


typedef struct {
    char username[20];
    char password[20];
    struct nodo_punt_libro* my_book; //faccio una lista di liste
    struct nodo_punt_libro* my_book_tail; //
    struct nodo_punt* my_recensioni; //lista di liste
    struct nodo_punt* my_recensioni_tail;
} utente;

struct nodo_utente{
    utente account;
    struct nodo_utente* next;
};
struct nodo_utente* trova_utente(struct nodo_utente* head, char username[20]);

//funzione che crea una lista UTENTI dal primo elemento
struct nodo_utente* crealista_utente(utente profilo, struct nodo_utente** tail_utente);

// funzione stampa UTENTI
void stampa_utenti(struct nodo_utente* lista_utenti);

//funzione cancellazione UTENTI
int cancellazione_utenti(struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente);

// inserimento in coda UTENTI
int inserimento_coda (utente account, struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente);

//scrittura su file lista_utenti.txt
void scrivifile(struct nodo_utente* lista_utenti);

//leggere il file lista_utenti.txt
void leggifile(struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente);
// scrive su file la lista utenti

//inserisce un elemento ordinatamente in lista
int inserimento_ordinato (utente account, struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente);

bool trova(utente account, struct nodo_utente* lista_utenti);

//funzione registrazione UTENTI
void registrazione(struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente);

void modifica_password(struct nodo_utente* lista_utenti);


void stampa_storico(char username[20]);

//controllo username e controllo data
int cerca_storico_utente (struct nodo_utente* lista_utenti);
// funzione login
