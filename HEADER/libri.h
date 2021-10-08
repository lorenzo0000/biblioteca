

typedef struct {
    char titolo[40];
    char autore[40];
    char genere[40];
    char codice[10];
    char data_prenotazione[20];
    char data_restituzione[20];
    char username[20];
    struct nodo_punt* my_recensioni;
    struct nodo_punt* my_recensioni_tail;
} libro;

struct nodo_libro{
    libro book;
    struct nodo_libro* next;
};

struct nodo_libro* trova_libro(struct nodo_libro* head, char codice[10]);

// funzione stampa LIBRI
void stampa_libri(bool admin, struct nodo_libro* lista_libri);

//funzione cancellazione LIBRI
int cancellazione_libro(struct nodo_libro** lista_libri,struct nodo_libro** tail_libro);

//funzione cancellazione miei libRI
int cancellazione_my_libri(struct nodo_punt_libro** head, char codice[10]);

//inserimento in coda LIBRI
int inserimento_coda_libri (struct nodo_libro** lista_libri,struct nodo_libro** tail_libro,libro book);


void scrivi_my_libri(struct nodo_libro* indirizzo, char username[20],struct nodo_utente* lista_utenti);

void stampa_my_libri(char username[20], struct nodo_utente* lista_utenti);

//leggere il file lista_libri.txt
void leggifile_libro(struct nodo_libro** lista_libri, struct nodo_libro** tail_libro, struct nodo_utente* lista_utenti);

//scrivi su file lista_libri.txt
void scrivifile_libro(struct nodo_libro* lista_libri);

//funzione registrazione LIBRI
void registrazione_libri(struct nodo_libro** lista_libri, struct nodo_libro** tail_libro);

// prendi un libro
void prendi_libro(utente account, struct nodo_libro* lista_libri, struct nodo_utente* lista_utenti);

//funzione che modifica i campi username e data al momento della restituzione
void modifica(char codice[10], struct nodo_libro* lista_libri);


void restituisci_libro(utente account,char username[20], struct nodo_libro* lista_libri, struct nodo_utente* lista_utenti);

//scrivi su file lista_libri.txt
void scrivifile_storico(libro book);

