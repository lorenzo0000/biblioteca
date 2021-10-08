#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "recensioni.h"


struct nodo_utente* trova_utente(struct nodo_utente* head, char username[20]){
    struct nodo_utente* p;
    p=head;
    while((p!=NULL)&&(strcmp(p->account.username,username)!=0)){
            p=p->next;
    };
    return p;
};


struct nodo_libro* trova_libro(struct nodo_libro* head, char codice[10]){
    struct nodo_libro* p;
    p=head;
    while((p!=NULL)&&(strcmp(p->book.codice,codice)!=0)){
            p=p->next;
    };
    return p;
};


//inserimento in coda puntatori
int inserimento_coda_puntatori (struct nodo_punt** head, struct nodo_punt** tail,struct nodo_recensione* indirizzo){
    struct nodo_punt* p;
    struct nodo_punt* new_node;
    new_node = (struct nodo_punt*)malloc(sizeof(struct nodo_punt));
    //qualcosa e' andato storto
    if(new_node == NULL)
        return 1;
    new_node->indirizzo=indirizzo;
    new_node->next = NULL;
    p=*tail;
    if (p==NULL){
        p=new_node;
        *tail=new_node;
        *head=new_node;
        p->next=NULL;
    } else {
        p->next=new_node;
        *tail=new_node;
    }
};

//inserimento in coda punt libri
int inserimento_coda_punt_libri (struct nodo_punt_libro** head, struct nodo_punt_libro** tail,struct nodo_libro* indirizzo){
    struct nodo_punt_libro* p;
    struct nodo_punt_libro* new_node;
    new_node = (struct nodo_punt_libro*)malloc(sizeof(struct nodo_punt_libro));
    //qualcosa e' andato storto
    if(new_node == NULL) return 1;
    new_node->indirizzo=indirizzo;
    new_node->next = NULL;
    p=*tail;
    if (p==NULL){
        p=new_node;
        *tail=new_node;
        *head=new_node;
        p->next=NULL;
    } else {
        p->next=new_node;
        *tail=new_node;
    }
};


//leggere il file lista_recensioni.txt
void leggifile_recensione(struct nodo_recensione** lista_recensioni, struct nodo_recensione** tail_recensione,
                           struct nodo_libro* lista_libri, struct nodo_utente* lista_utenti) {
    recensioni recensione;
    struct nodo_utente* u;
    struct nodo_libro* l;

    FILE *f;
    f=fopen("lista_recensioni.txt","r");
    if(f==NULL){
		return;
    };
    while(!feof(f)){
        fgets(recensione.testo,200,f);
        recensione.testo[strlen(recensione.testo)-1]='\0';
        fgets(recensione.username,20,f);
        recensione.username[strlen(recensione.username)-1]='\0';
        fgets(recensione.codice,10,f);
        recensione.codice[strlen(recensione.codice)-1]='\0';
        fgets(recensione.numero,10,f);
        recensione.numero[strlen(recensione.numero)-1]='\0';

        if (!feof(f)){
            inserimento_coda_recensioni(lista_recensioni,tail_recensione,recensione);
            u=trova_utente(lista_utenti, recensione.username);
            inserimento_coda_puntatori(&u->account.my_recensioni,&u->account.my_recensioni_tail,*tail_recensione); //per le recensioni dell'utente
            l=trova_libro(lista_libri, recensione.codice);
            inserimento_coda_puntatori(&l->book.my_recensioni,&l->book.my_recensioni_tail,*tail_recensione); // per le recensioni del libro
        };
    };
    fclose(f);
};

// funzione stampa RECENSIONI
void stampa_recensioni (struct nodo_libro* head_l, struct nodo_utente* head_u,char username[20], bool admin){
    struct nodo_punt* p;
    struct nodo_libro* q;
    struct nodo_utente* u;
    char nome[20];
    q=head_l;
    u=head_u;

    int scelta;
    char codice[10];
    if (admin==false)
    	printf("\n1 LE MIE RECENSIONI\n2 RECENSIONE PER LIBRO\n\n");
    else
        printf("\n1 STAMPA RECENSIONI PER UTENTE\n2 RECENSIONE PER LIBRO\n\n");
    scanf("%d", &scelta);

    if (scelta==1){
    	if (admin) {
			printf ("inserisci utente di cui stampare le recensioni\n");
            while(strcmp(fgets(nome,20,stdin),"\n")==0);
      		nome[strlen(nome)-1]='\0';
            while ((u!=NULL)&&(strcmp(nome,u->account.username)!=0)) {
               	u=u->next;
			};
            if (u==NULL)  {
           		printf("username non trovato\n\n");
           		return;
   			};
            p=u->account.my_recensioni;
      		if (p==NULL)
 	      		 printf("nessuna recensione \n\n");
     		while (p!=NULL){
       	    	printf("UTENTE: %s\n", p->indirizzo->recensione.username);
        		printf("LIBRO: %s\n", p->indirizzo->recensione.codice);
       			printf("NUMERO RECENSIONE: %s\n", p->indirizzo->recensione.numero);
       			printf("RECENSIONE: %s\n\n", p->indirizzo->recensione.testo);
        		p=p->next;
        	};
		} else {
            while ((u!=NULL)&&(strcmp(username,u->account.username)!=0)){
                u=u->next;
        	};
        	if (u==NULL)  {
            	printf("username non trovato\n\n");
            	return;
        	};
        	p=u->account.my_recensioni;
    	};
	};
    if (scelta==2){
        printf("inserisci codice del libro\n");
        while(strcmp(fgets(codice,20,stdin),"\n")==0);
       		  codice[strlen(codice)-1]='\0';
        while ((q!=NULL)&&(strcmp(codice,q->book.codice)!=0)){
                q=q->next;
        };
        if (q==NULL)  {
            printf("codice non valido\n\n");
            return;
        };
        p=q->book.my_recensioni;
    }
    if (p==NULL)
        printf("nessuna recensione \n\n");
    while (p!=NULL){
        printf("NUMERO RECENSIONE: %s\n", p->indirizzo->recensione.numero);
        printf("UTENTE: %s\n", p->indirizzo->recensione.username);
        printf("LIBRO: %s\n", p->indirizzo->recensione.codice);
        printf("RECENSIONE: %s\n\n", p->indirizzo->recensione.testo);
        p=p->next;
    }
};

//inserimento in coda RECENSIONI
int inserimento_coda_recensioni (struct nodo_recensione** head,struct nodo_recensione** tail, recensioni recensione){
    struct nodo_recensione* p;
    struct nodo_recensione* new_node;
    new_node = (struct nodo_recensione*)malloc(sizeof(struct nodo_recensione));
    //qualcosa e' andato storto
    if(new_node == NULL) return 1;
    new_node->recensione = recensione;
    new_node->next = NULL;
    p= *tail;
    if (p==NULL){
            p=new_node;
            *tail=new_node;
            *head=new_node;
            p->next=NULL;
    }else{
            p->next=new_node;
            *tail=new_node;
    }
};

int scrivi_recensione (struct nodo_recensione** head, struct nodo_recensione** tail,char username[20], struct nodo_libro* lista_libri){
    recensioni recensione;
    int num=1;
    struct nodo_recensione* p;
    p=*tail;
    printf("inserisci codice del libro che vuoi recensire:\n");
    while (strcmp(fgets(recensione.codice,100,stdin),"\n")==0);
    recensione.codice[strlen(recensione.codice)-1]='\0';
    if (trova_libro(lista_libri,recensione.codice)==NULL){
        printf("codice inserito non valido\n\n");
        return 1; //errore
    };
    printf("scrivi una recensione\n");
    while (strcmp(fgets(recensione.testo,100,stdin),"\n")==0);
    recensione.testo[strlen(recensione.testo)-1]='\0';
    strcpy(recensione.username,username);
    if (*head==NULL){
        strcpy(recensione.numero,"1");
    } else {
        num=atoi(p->recensione.numero)+1;
        sprintf(recensione.numero,"%d",num);
    };
    printf("\nNUMERO RECENSIONE: %d\n\n", num);
    inserimento_coda_recensioni(head,tail, recensione);
            return 0; // tutto è andato a buon fine
};

//scrittura su file lista_receensioni.txt
void scrivifile_recensioni(struct nodo_recensione* head){
    struct nodo_recensione* p;
    p=head;
    FILE *f;
    f=fopen("lista_recensioni.txt","w");
    while (p!=NULL) {
        fprintf (f,"%s\n", p->recensione.testo);
        fprintf (f,"%s\n", p->recensione.username);
        fprintf (f,"%s\n", p->recensione.codice);
        fprintf (f,"%s\n", p->recensione.numero);
        p=p->next;
    };
    fclose(f);
};

//funzione che crea una lista UTENTI dal primo elemento
struct nodo_utente* crealista_utente(utente profilo, struct nodo_utente** tail_utente){
    struct nodo_utente* head;
    head=(struct nodo_utente*)malloc(sizeof(struct nodo_utente));
    head->account=profilo;
    head->next=NULL;
    *tail_utente=head;
    return head;

};


// funzione stampa UTENTI
void stampa_utenti(struct nodo_utente* lista_utenti) {
    struct nodo_utente* p;
    p=lista_utenti;
    if (p==NULL)
        printf("nessun utente registrato\n\n");
       while (p!=NULL){
        printf("%s\n", p->account.username);
        printf("%s\n\n", p->account.password);
        p=p->next;
    }
};

// funzione stampa LIBRI
void stampa_libri(bool admin, struct nodo_libro* lista_libri) {
    struct nodo_libro* p;
    p=lista_libri;
    if(p==NULL){
        printf("la lista e' vuota\n\n");
        return;
	};
    //scandisco tutta la lista, quando p punta a NULL esco dal while
    printf("\n");
    printf("%-15s", "GENERE");
    printf("%-26s", "TITOLO");
    printf("%-20s", "AUTORE");
    printf("%-10s", "CODICE");
    if(admin==true){
        printf("%-15s","USERNAME");
        printf("%-10s","PRENOTAZIONE");
    };
    printf("\n");
    while (p!=NULL){
        printf("%-15s", p->book.genere);
        printf("%-26s", p->book.titolo);
        printf("%-20s", p->book.autore);
        printf("%-10s", p->book.codice);

        //Soltanto l'admin puo' vedere username e data prenotazione
        if(admin==true){
            printf("%-15s",p->book.username);
            printf("%-10s",p->book.data_prenotazione);
        };
        p=p->next;
        printf("\n\n");
    }
};

//funzione cancellazione UTENTI
int cancellazione_utenti(struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente){
    char username[20];
    printf("scrivi utente da cancellare:\n");
    scanf("%s",username);
    struct nodo_utente* q=*lista_utenti; //next
    struct nodo_utente* r=*lista_utenti; //prec
    while ((q!=NULL)&&(strcmp(q->account.username,username)==1)){
        r=q;
        q=q->next;
    };
    if ((q==NULL)||(strcmp(q->account.username,username)<0)){
        printf("l'utente non e' registrato\n\n");
        return 1;
    };
    if (q==*lista_utenti)
        *lista_utenti=q->next;
    else
        r->next=q->next;
    free(q);
    printf("l'utente e' stato rimosso\n\n");
    if (r->next==NULL)
        *tail_utente=r;
    return 0;
}


//funzione cancellazione LIBRI
int cancellazione_libro(struct nodo_libro** lista_libri,struct nodo_libro** tail_libro){
    struct nodo_libro* q=*lista_libri; //next
    struct nodo_libro* r=*lista_libri; //prec
    char codice[10];
    printf("scrivi codice del libro da cancellare:\n");
    while (strcmp(fgets(codice,10,stdin),"\n")==0);
		  codice[strlen(codice)-1]='\0';
    while ((q!=NULL)&&(strcmp(q->book.codice,codice)!=0)){
        r=q;
        q=q->next;
    };
    if ((q==NULL)||(strcmp(q->book.codice,codice)!=0)){
        printf("l'elemento non c'e' oppure la lista e' vuota\n\n\n");
        return 1;
    }
    if (strcmp(q->book.username,"-")==0){
        if (q==*lista_libri)
            *lista_libri=q->next;
        else
            r->next=q->next;
        free(q);
        printf("il libro e' stato cancellato\n\n\n");
        if (r->next==NULL)
            *tail_libro=r;
        return 0;
    } else printf("il libro al momento e' preso in prestito da %s e non puo' essere rimosso\n\n",q->book.username);
    return 0;

};
//funzione cancellazione miei libRI
int cancellazione_my_libri(struct nodo_punt_libro** head, char codice[10]){
    struct nodo_punt_libro* q=*head; //next
    struct nodo_punt_libro* r=*head; //prec
    if (q==NULL){
        printf("l'elemento non c'e' oppure la lista e' vuota\n\n\n");
    };
    while ((q!=NULL)&&(strcmp(q->indirizzo->book.codice,codice)!=0)){
		r=q;
        q=q->next;
    };
    if (q==NULL){
        printf("l'elemento non c'e' oppure la lista e' vuota\n\n\n");
        return 1;
    };
    if (q==*head)
        *head=q->next;
    else
        r->next=q->next;
    free(q);
    return 0;
};

// inserimento in coda UTENTI
int inserimento_coda (utente account, struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente){
    struct nodo_utente* p;
    struct nodo_utente* new_node;
    new_node = (struct nodo_utente*)malloc(sizeof(struct nodo_utente));
    if(new_node == NULL) return 1;
    new_node->account = account;
    new_node->next = NULL;
    //se la lista e' vuota lui sara' anche il primo quindi la testa e la coda coincidono
    if(*lista_utenti==NULL){
        *lista_utenti=new_node;
        *tail_utente=new_node;
        //tutto e' andato a buon fine
        return 0;
    }
    //inizio a scorrere partendo dalla testa
    p = *tail_utente;
    p->next = new_node;
    *tail_utente = new_node;
};

//inserimento in coda LIBRI
int inserimento_coda_libri (struct nodo_libro** lista_libri,struct nodo_libro** tail_libro,libro book){
    struct nodo_libro* p;
    struct nodo_libro* new_node;
    new_node = (struct nodo_libro*)malloc(sizeof(struct nodo_libro));
    //qualcosa e' andato storto
    if(new_node == NULL) return 1;
    new_node->book = book;
    new_node->next = NULL;
    p=*tail_libro;
    if(p==NULL){
        *tail_libro=new_node;
        *lista_libri=new_node;
        return 0;
    }
    p= *tail_libro;
    while (p->next != NULL) {
        p = p->next;
    };
    p->next = new_node;
    *tail_libro=new_node;
    return 0;
};

//leggere il file lista_utenti.txt
void leggifile(struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente) {
    utente account;
    FILE *f;
    f=fopen("lista_utenti.txt","r");
    if(f==NULL){
        return;
    };
    while(!feof(f)){
        fgets(account.username,40,f);
        account.username[strlen(account.username)-1]='\0';
        fgets(account.password,40,f);
        account.password[strlen(account.password)-1]='\0';
        account.my_book=NULL;
        account.my_book_tail=NULL;
        account.my_recensioni=NULL;
        account.my_recensioni_tail=NULL;
        if (!feof(f))
            inserimento_coda(account,lista_utenti,tail_utente);
    };
    fclose(f);
};

//scrittura su file lista_utenti.txt
void scrivifile(struct nodo_utente* lista_utenti){
    struct nodo_utente* p;
    p=lista_utenti;
    FILE *f;
    f=fopen("lista_utenti.txt","w");
    while (p!=NULL) {
        fprintf (f,"%s\n", p->account.username);
        fprintf (f,"%s\n", p->account.password);
        p=p->next;
    };
    fclose(f);
    };


void scrivi_my_libri(struct nodo_libro* indirizzo, char username[20],struct nodo_utente* lista_utenti){
    struct nodo_utente* q;
    q=lista_utenti;
    while((q!=NULL)&&(strcmp(q->account.username,username)!=0)){
        q=q->next;
    };
    if (q==NULL)
        return;
    inserimento_coda_punt_libri(&q->account.my_book,&q->account.my_book_tail,indirizzo);
};

void stampa_my_libri(char username[20], struct nodo_utente* lista_utenti){
    struct nodo_utente* q;
    struct nodo_punt_libro* p;
    q=lista_utenti;
//facciamo un ciclo while per scandire la lista utenti che contiene user password e puntatore a head di una lista dentro la lista (lista concatenata)
    while (strcmp(q->account.username,username)!=0){
        q=q->next;
    };
    //quando esce significa che u sta puntando all'utente che stiamo cercando ovvero quello con cui abbiammo fatto l'accesso quindi dobbiamo scandire l'altra lista
    //l e' un puntatore che punta al al campo my book della variabile account di tipo utente
    p=q->account.my_book;
    //printf("p acccount user %s", q->account.username);
    printf("\t\tI MIEI LIBRI\n\n");
    if (p==NULL){
        printf("la lista e' vuota\n\n");
        return;
    }
    else

        printf("%-15s", "GENERE");
        printf("%-26s", "TITOLO");
        printf("%-20s", "AUTORE");
        printf("%-10s", "CODICE");
        printf("%-10s","PRENOTAZIONE");
        printf("\n");
while(p!=NULL){
        printf("%-15s%-26s%-20s%-10s%-10s\n",p->indirizzo->book.genere,p->indirizzo->book.titolo,p->indirizzo->book.autore,
                                             p->indirizzo->book.codice,p->indirizzo->book.data_prenotazione);
        p=p->next;
    };
    printf("\n");
};

//leggere il file lista_libri.txt
void leggifile_libro(struct nodo_libro** lista_libri, struct nodo_libro** tail_libro, struct nodo_utente* lista_utenti) {
    libro book;
    FILE *f;
    f=fopen("lista_libri.txt","r");
    if(f==NULL){
		return;
    };
    while(!feof(f)){
        fgets(book.genere,40,f);
        book.genere[strlen(book.genere)-1]='\0';
        fgets(book.titolo,40,f);
        book.titolo[strlen(book.titolo)-1]='\0';
        fgets(book.autore,40,f);
        book.autore[strlen(book.autore)-1]='\0';
        fgets(book.codice,10,f);
        book.codice[strlen(book.codice)-1]='\0';
        fgets(book.data_prenotazione,20,f);
        book.data_prenotazione[strlen(book.data_prenotazione)-1]='\0';
        fgets(book.username,20,f);
        book.username[strlen(book.username)-1]='\0';
        book.my_recensioni=NULL;
        book.my_recensioni_tail=NULL;
        if (!feof(f)){
            inserimento_coda_libri(lista_libri,tail_libro,book);
            if (strcmp(book.username,"-")!=0){
            scrivi_my_libri(*tail_libro,book.username, lista_utenti);
            }
        };
    };
    fclose(f);
};

//scrivi su file lista_libri.txt
void scrivifile_libro(struct nodo_libro* lista_libri){
    struct nodo_libro* p;
    p=lista_libri;
    FILE *f;
    f=fopen("lista_libri.txt","w");
    while (p!=NULL) {
        fprintf(f,"%s\n", p->book.genere);
        fprintf(f,"%s\n", p->book.titolo);
        fprintf(f,"%s\n", p->book.autore);
        fprintf(f,"%s\n", p->book.codice);
        fprintf(f,"%s\n", p->book.data_prenotazione);
        fprintf(f,"%s\n", p->book.username);
        p=p->next;
    };
    fclose(f);
};

//inserisce un elemento ordinatamente in lista
int inserimento_ordinato (utente account, struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente){
    struct nodo_utente* r = *lista_utenti; //precedente (rosso)
    struct nodo_utente* q = *lista_utenti; //successivo (blu)
    struct nodo_utente* p;
    p = (struct nodo_utente*)malloc(sizeof(struct nodo_utente));
    //qualcosa e' andato storto
    if(p == NULL) return 1;
    p->account = account;
    while ((q != NULL) && (strcmp(p->account.username,q->account.username)>0)){
    // quando r raggiunge q, q va avanti di uno
        r = q;
        q = q->next;
    };

    if(q==*lista_utenti){
        p->next = *lista_utenti;
        *lista_utenti=p;
        *tail_utente=p;
    } else {
        //il precedente deve puntare al nuovo nodo, il nuovo nodo deve puntare al successivo
        r->next = p;
        p->next = q;
    }
    if(p->next==NULL)
        *tail_utente=p;
    //tutto e' andato a buon fine
    return 0;
};

// funzione di controllo username e password corretti
bool trova(utente account, struct nodo_utente* lista_utenti){

    struct nodo_utente* p=lista_utenti;
    while ((p!=NULL)&&
           ((strcmp(p->account.username,account.username)!=0)||
           (strcmp(p->account.password,account.password)!=0))
          ){
        p=p->next;
    };
    if (p==NULL){

        return false;
    }
        else return true;
};

//funzione registrazione UTENTI
void registrazione(struct nodo_utente** lista_utenti, struct nodo_utente** tail_utente){
    struct nodo_utente* p=*lista_utenti;
    utente profilo;
    printf("inserire username:");
    while (strcmp(fgets(profilo.username,20,stdin),"\n")==0);
    profilo.username[strlen(profilo.username)-1]='\0';
    while ((p!=NULL)&&
        (strcmp(p->account.username,profilo.username)!=0)){
        p=p->next;
    };
    if (p!=NULL){
        printf("username gia' esistente\n\n");
        return;
    };
    printf("inserire password:");
    while (strcmp(fgets(profilo.password,20,stdin),"\n")==0);
    profilo.password[strlen(profilo.password)-1]='\0';
    printf("\n");
    profilo.my_book=NULL;
    profilo.my_book_tail=NULL;
    profilo.my_recensioni=NULL;
    profilo.my_recensioni_tail=NULL;
    printf("username=%s\npassword=%s\n\nREGISTRAZIONE EFFETTUATA\n\n\n",profilo.username,profilo.password);
    if (*lista_utenti==NULL)
        *lista_utenti=crealista_utente(profilo, tail_utente);
    else inserimento_ordinato(profilo, lista_utenti, tail_utente);
};

//funzione registrazione LIBRI
void registrazione_libri(struct nodo_libro** lista_libri, struct nodo_libro** tail_libro){
    libro dati;
    struct nodo_libro* p;
    p=*tail_libro;
    int num;
    strcpy(dati.codice,"1");
    printf("inserire genere:\n");
    while (strcmp(fgets(dati.genere,40,stdin),"\n")==0);
    dati.genere[strlen(dati.genere)-1]='\0';
    printf("inserire titolo:\n");
    while (strcmp(fgets(dati.titolo,40,stdin),"\n")==0);
    dati.titolo[strlen(dati.titolo)-1]='\0';
    printf("inserire autore:\n");
    while (strcmp(fgets(dati.autore,40,stdin),"\n")==0);
    dati.autore[strlen(dati.autore)-1]='\0';
    strcpy(dati.data_prenotazione,"-");
    strcpy(dati.username,"-");
    dati.my_recensioni=NULL;
    dati.my_recensioni_tail=NULL;
    if (*lista_libri==NULL){
        strcpy(dati.codice,"1");
    } else {
        num=atoi(p->book.codice)+1;
        sprintf(dati.codice,"%d",num);
    };
    inserimento_coda_libri(lista_libri, tail_libro,dati);
    printf("genere=%s\ttitolo=%s\tautore=%s\tcodice=%s\nREGISTRAZIONE EFFETTUATA\n\n\n",dati.genere,dati.titolo,dati.autore,dati.codice);
};

// prendi un libro
void prendi_libro(utente account, struct nodo_libro* lista_libri, struct nodo_utente* lista_utenti){
    char tipo[20];
    char geti[3][20]={"genere","titolo","autore"};
    int scelta;
    char codice[10];
	char controllo[10];
    bool trovato=false;
    struct nodo_libro* p;
    struct nodo_utente* q;
    while(1){
        printf("cerca un libro per:\n1 genere\n2 titolo\n3 autore\n\n4 annulla\n\n");
        scanf("%d",&scelta);
		switch (scelta) {
			case 1: case 2: case 3:
    			printf("inserisci %s del libro che stai cercando\n",geti[scelta-1]);
    			while (strcmp(fgets(tipo,20,stdin),"\n")==0);
    			tipo[strlen(tipo)-1]='\0';
    			printf("\n");
				break;

			case 4:return;

			default: printf("\n RIPROVA!\n\n\n");
			// per evitare il loop infinito, controlla il carattere invio e ripulisce il buffer di tastiera
        	while(strcmp(fgets(controllo,10,stdin),"\n")==0);
		};

        p=lista_libri;
        if (p==NULL)
            printf("la lista e' vuota\n\n");
        while (p!=NULL){
            if(

                ((strcmp(p->book.genere,tipo)==0)&& (scelta==1))||
                ((strcmp(p->book.titolo,tipo)==0)&& (scelta==2))||
                ((strcmp(p->book.autore,tipo)==0)&& (scelta==3))
            ) {
                printf("genere:%-15stitolo:%-26sautore:%-20scodice:%-5s",p->book.genere,p->book.titolo,p->book.autore,p->book.codice);
                if (strcmp(p->book.username,"-")==0)
                    printf("disponibile\n\n");
                else printf("non disponibile\n\n");
                trovato=true;
            };
            p=p->next;
        };
        if (trovato==false){
            printf("%s non trovato\n\n",tipo);
        } else {
            printf("inserisci codice del libro che vuoi prendere in prestito\n");
            while (strcmp(fgets(codice,10,stdin),"\n")==0);
            codice[strlen(codice)-1]='\0';
            p=lista_libri;
            while (p!=NULL){
                if(strcmp(p->book.codice,codice)==0){
                    if(strcmp(p->book.username,"-")!=0){
                        printf("\nlibro non disponibile!\n\n");
                        break;
                    } else
                        printf("confermi la tua scelta?\n1 SI\n2 NO\n");
                    scanf("%d",&scelta);
                    if (scelta==1){
                        printf("inserisci data\n");
                        while (strcmp(fgets(p->book.data_prenotazione,20,stdin),"\n")==0);
                        p->book.data_prenotazione[strlen(p->book.data_prenotazione)-1]='\0';
                        printf("\nil libro e' stato preso in prestito\n\n");
                        strcpy(p->book.username,account.username);
                        printf("prenotazione data:%s\n",p->book.data_prenotazione);
                        printf("username:%s\n\n",p->book.username);
                        scrivifile_libro(lista_libri);
                        scrivi_my_libri(p,account.username,lista_utenti);
                    };
                };
                p=p->next;
            };
        };
        break;
    };
};
void modifica(char codice[10], struct nodo_libro* lista_libri){
    struct nodo_libro* p;
    p=lista_libri;
    while (strcmp(p->book.codice,codice)!=0){
        p=p->next;
    }
        strcpy(p->book.username,"-");
        strcpy(p->book.data_prenotazione,"-");
    };


void restituisci_libro(utente account,char username[20], struct nodo_libro* lista_libri, struct nodo_utente* lista_utenti) {
    int scelta;
    char codice[10];
    struct nodo_libro* p=lista_libri;
    struct nodo_utente* q=lista_utenti;

	while ((q!=NULL)&&(strcmp(q->account.username,username)!=0)){
		q=q->next;
	};

	if (p==NULL) {
   		printf("la tua lista e' vuota\n\n\n");
        return;
    } else {
		stampa_my_libri(username, lista_utenti);
		printf("inserisci codice del libro che vuoi restituire:\n");
	    while (strcmp(fgets(codice,10,stdin),"\n")==0);
		codice[strlen(codice)-1]='\0';
    };
	while ((p!=NULL) && (strcmp(codice,p->book.codice)!=0)){
		p=p->next;
	};
	if (p==NULL){
		printf("codice non valido\n\n");
		return;
	};
    if ((strcmp(codice,p->book.codice)==0)&&(strcmp(p->book.username,username)==0)){
            /*questo and nell'if risolve il problema che permetteva ad un utente di restituire un libro
            che non aveva mai preso in prestito (oltre a verificare il codice bisogna infatti controllare il nome*/
        printf("libro trovato\n");
        printf("%s\n%s\n%s\n%s\n%s\n",p->book.genere,p->book.titolo,p->book.autore,p->book.codice,p->book.data_prenotazione);
        printf("confermi la tua scelta?\n1 SI\n2 NO\n");
        scanf("%d",&scelta);
        if(scelta==1){
            printf("inserisci data odierna\n");
            while (strcmp(fgets(p->book.data_restituzione,20,stdin),"\n")==0);
            p->book.data_restituzione[strlen(p->book.data_restituzione)-1]='\0';
            printf("libro restituito\n\n");
            scrivifile_storico(p->book);
            modifica(codice, lista_libri);
            cancellazione_my_libri(&q->account.my_book,codice);
            scrivifile_libro(lista_libri);
            return;
        } else return;
    } else printf("libro non trovato\n\n");
};


void modifica_password(struct nodo_utente* lista_utenti){
	struct nodo_utente* p;
	char password[20];
	utente account;
	p=lista_utenti;
    printf("inserisci password attuale\n");
    while (strcmp(fgets(password,20,stdin),"\n")==0);
    password[strlen(password)-1]='\0';
    while ((p!=NULL) && (strcmp(p->account.password,password)!=0)){
        p=p->next;
    }
    if (p==NULL){
    	printf("\n\nPASSWORD ERRATA\n\n");
		return;
	};
	printf("inserisci nuova password\n");
	while (strcmp(fgets(p->account.password,20,stdin),"\n")==0);
    p->account.password[strlen(p->account.password)-1]='\0';
    scrivifile(lista_utenti);
    printf("\n\n\tPASSWORD MODIFICATA!\n\n");
};

void modifica_recensione(struct nodo_recensione* lista_recensioni, char username[20]){
struct nodo_recensione* p;
char recensione[10];
p=lista_recensioni;
    printf("inserisci numero di recensione\n");
     while (strcmp(fgets(recensione,10,stdin),"\n")==0);
    recensione[strlen(recensione)-1]='\0';
    while ((p!=NULL) && (strcmp(p->recensione.numero,recensione)!=0)){
        p=p->next;
    }
    if (p==NULL){
        printf("numero inserito non valido\n");
        return;
    }
    if (strcmp(p->recensione.username,username)!=0){
        printf("non puoi modificare questa recensione\n\n");
        return;
    };
    printf("inserisci nuova recensione\n");
    fgets(p->recensione.testo,200,stdin);
    p->recensione.testo[strlen(p->recensione.testo)-1]='\0';
    scrivifile_recensioni(lista_recensioni);
    printf("recensione modificata\n\n");
};


//scrivi su file lista_libri.txt
void scrivifile_storico(libro book){
    FILE *f;
    f=fopen("storico.txt","a");
        fprintf(f,"%s\n", book.genere);
        fprintf(f,"%s\n", book.titolo);
        fprintf(f,"%s\n", book.autore);
        fprintf(f,"%s\n", book.codice);
        fprintf(f,"%s\n", book.data_prenotazione);
        fprintf(f,"%s\n", book.data_restituzione);
        fprintf(f,"%s\n", book.username);
    fclose(f);
    };

void stampa_storico(char username[20]){
    libro book;
    bool trovato=false;
    FILE *f;
    f=fopen("storico.txt","r");
    if(f==NULL){
        printf("lo storico e' vuoto\n\n");
		return;
    };

    while(!feof(f)){
        fgets(book.genere,40,f);
        book.genere[strlen(book.genere)-1]='\0';
        fgets(book.titolo,40,f);
        book.titolo[strlen(book.titolo)-1]='\0';
        fgets(book.autore,40,f);
        book.autore[strlen(book.autore)-1]='\0';
        fgets(book.codice,10,f);
        book.codice[strlen(book.codice)-1]='\0';
        fgets(book.data_prenotazione,20,f);
        book.data_prenotazione[strlen(book.data_prenotazione)-1]='\0';
        fgets(book.data_restituzione,20,f);
        book.data_restituzione[strlen(book.data_restituzione)-1]='\0';
        fgets(book.username,20,f);
        book.username[strlen(book.username)-1]='\0';
        if (!feof(f))
            if (strcmp(book.username,username)==0){
                if(!trovato){
                     printf("%-15s", "GENERE");
                     printf("%-26s", "TITOLO");
                     printf("%-20s", "AUTORE");
                     printf("%-10s", "CODICE");
                     printf("%-15s","DATA PRESTITO");
                     printf("%-15s","DATA RESO");
                     printf("%-15s","USERNAME");
                     printf("\n\n");
                };
                trovato = true;
                printf("%-15s",book.genere);
                printf("%-26s",book.titolo);
                printf("%-20s",book.autore);
                printf("%-10s",book.codice);
                printf("%-15s",book.data_prenotazione);
                printf("%-15s",book.data_restituzione);
                printf("%-15s",book.username);
                printf("\n\n");
            };
    };
    if (!trovato)
        printf("lo storico di %s e' vuoto\n\n", username);
};

//controllo username e controllo data
int cerca_storico_utente (struct nodo_utente* lista_utenti){
    char username[20];
    struct nodo_utente* p=lista_utenti;
    printf("inserisci username dell'utente di cui vedere lo storico\n");
    while (strcmp(fgets(username,20,stdin),"\n")==0);
    username[strlen(username)-1]='\0';
    while ((p!=NULL)&&
        (strcmp(p->account.username,username)!=0))
          {
        p=p->next;
    };
    if (p==NULL){
        printf("utente non trovato\n\n");
        return 1;
    }
        else printf("utente trovato\n\n");
        stampa_storico(username);

};
// funzione login
void login(struct nodo_utente* lista_utenti, struct nodo_utente* tail_utente, struct nodo_libro** lista_libri,struct nodo_libro** tail_libro,
           struct nodo_recensione* lista_recensioni, struct nodo_recensione* tail_recensione) {
    int scelta;
    char riga[10];
    char* temp;
    char controllo[10];
    utente account;
    struct nodo_utente* u;
    struct nodo_libro* l;
    while(1) {
		printf("\n1 login utente\n2 login amministratore\n3 exit\n");
    	scelta=0;
    	scanf("%d", &scelta);
    	struct nodo_utente* p=lista_utenti;
    	switch (scelta) {
        	case 1: printf("inserisci nome:");
        	  while (strcmp(fgets(account.username,20,stdin),"\n")==0);
			  account.username[strlen(account.username)-1]='\0';
        	  printf("inserisci password:");
        	  while (strcmp(fgets(account.password,20,stdin),"\n")==0);
			  account.password[strlen(account.password)-1]='\0';
        	  if (trova(account, lista_utenti)){
          		printf("\n\nACCESSO EFFETTUATO CON SUCCESSO!\n\n\n\tMENU' UTENTE\n\n\n");
            	while (1) {
                            	printf("1  PRENDI IN PRESTITO UN LIBRO\n"
                            	"2  RESTITUISCI LIBRO\n"
                            	"3  VISUALIZZA LISTA LIBRI\n"
                            	"4  I MIEI LIBRI\n"
                            	"5  STORICO\n"
                            	"6  MODIFICA PASSWORD\n"
                            	"7  SCRIVI UNA RECENSIONE\n"
                            	"8  MODIFICA RECENSIONE\n"
                            	"9  CERCA RECENSIONI\n"
                            	"\n10 exit\n\n");
                            	scelta=0;
                            	scanf("%d", &scelta);
                            	switch (scelta){
                            	case 1: prendi_libro(account, *lista_libri, lista_utenti);
                                    	break;
                            	case 2:
                                	restituisci_libro(account,account.username, *lista_libri, lista_utenti);
                                	break;
                            	case 3: stampa_libri(false, *lista_libri);
                                    	break;
                            	case 4:stampa_my_libri(account.username, lista_utenti);
                                	   break;
                            	case 5: stampa_storico(account.username);
                                	break;
                            	case 6: modifica_password(lista_utenti);
                                    	break;
                            	case 7: if (scrivi_recensione(&lista_recensioni,&tail_recensione,account.username, *lista_libri)==1){
                                        	break;
                                    	};
                                    	scrivifile_recensioni(lista_recensioni);
                                    	u=trova_utente(lista_utenti, account.username);
                                    	inserimento_coda_puntatori(&u->account.my_recensioni,&u->account.my_recensioni_tail,tail_recensione); //per le recensioni per utente
                                    	l=trova_libro(*lista_libri, tail_recensione->recensione.codice);
                                    	inserimento_coda_puntatori(&l->book.my_recensioni,&l->book.my_recensioni_tail,tail_recensione); // per le recensioni per libro
                                    	break;

                            	case 8: modifica_recensione(lista_recensioni, account.username);
                                    	break;

                            	case 9: stampa_recensioni(*lista_libri,lista_utenti,account.username,false);
                                    	break;
                            	case 10:printf("\nARRIVEDERCI!\n\n\n");
                            			return;
								default: printf("\n RIPROVA!\n\n\n");
                           				 while(strcmp(fgets(controllo,10,stdin),"\n")==0);
                            	}
                        	}
                	  } else {
                    	printf("accesso negato\n");
                	  };
                	  break;

        	case 2: printf("inserisci codice di accesso:");
                	  strcpy(account.username,"admin");
                	  while(strcmp(fgets(account.password,20,stdin),"\n")==0);
       		    	  account.password[strlen(account.password)-1]='\0';
                	  printf("\n\n");
                	  if (strcmp(account.password,"0000")==0){
                    	  printf("\n\nACCESSO EFFETTUATO CON SUCCESSO!\n\n\n\t\tMENU' ADMIN\n\n\n");
                    	  while (1) {
                            	printf(
                                	"1  STAMPA LISTA LIBRI\n"
                                	"2  INSERISCI LIBRO\n"
                                	"3  CANCELLA LIBRO\n"
                                	"4  CANCELLA UTENTE\n"
                                	"5  STAMPA LISTA UTENTI\n"
                                	"6  STAMPA STORICO\n"
                                	"7  STAMPA RECENSIONI\n"
                                	"\n8 exit\n\n");
                                	scelta=0;
                                	scanf("%d", &scelta);
                                	switch (scelta) {
                                    	case 1: stampa_libri(true, *lista_libri);
                                            	break;
                                    	case 2: registrazione_libri(lista_libri, tail_libro);
                                            	scrivifile_libro(*lista_libri);
                                            	break;
                                    	case 3: cancellazione_libro(lista_libri, tail_libro);
                                            	scrivifile_libro(*lista_libri);
                                            	break;
                                    	case 4: cancellazione_utenti(&lista_utenti, &tail_utente);
                                            	scrivifile(lista_utenti);
                                            	break;
                                    	case 5: stampa_utenti(lista_utenti);
                                            	break;
                                    	case 6:  cerca_storico_utente(lista_utenti);
                                                	break;
                                    	case 7: stampa_recensioni(*lista_libri,lista_utenti,account.username,true);
                                        	break;
                                    	case 8: printf("\nARRIVEDERCI!\n\n\n");
                                        	return;
										default: printf("\n RIPROVA!\n\n\n");
                                    	while(strcmp(fgets(controllo,10,stdin),"\n")==0);
                                	};
                        	};
                    	} else {
                    		printf("accesso negato\n");
                    	};
					case 3: return;

					default: printf("\n RIPROVA!\n\n\n");
                	while(strcmp(fgets(controllo,10,stdin),"\n")==0);
		};
    };
};

// funzione main
int main(){
    struct nodo_utente* lista_utenti=NULL;
    struct nodo_utente* tail_utente=NULL;
    struct nodo_recensione* lista_recensioni=NULL;
    struct nodo_recensione* tail_recensione=NULL;
    struct nodo_libro* lista_libri=NULL;
    struct nodo_libro* tail_libro=NULL;
    int scelta;
    char username [20];
	char controllo[10];

    leggifile(&lista_utenti, &tail_utente);
    leggifile_libro(&lista_libri,&tail_libro, lista_utenti);
    leggifile_recensione(&lista_recensioni, &tail_recensione, lista_libri, lista_utenti);
    while (1) {
        printf( "\t _____   _   _____   _       _   _____   _____   _____   _____   _____   \n   "
                "\t|  _  | | | |  _  | | |     | | |  _  | |_   _| | ____| |  ___| |  _  |  \n   "
                "\t| |_| | | | | |_| | | |     | | | | | |   | |   | |_    | |     | |_| |  \n   "
                "\t|  _ <  | | |  _ <  | |     | | | | | |   | |   |  _|   | |     |  _  |  \n   "
                "\t| |_| | | | | |_| | | |___  | | | |_| |   | |   | |___  | |___  | | | |  \n   "
                "\t|_____/ |_| |_____/ |_____| |_| |_____|   |_|   |_____| |_____| |_| |_|  \n   ");

        printf("\n\n\n\t\t\t\t MENU PRINCIPALE\n \t\t\t1 login\t\t\t 2 registrazione\n\n\t\t\t3 exit\n");
        scelta=0;
        scanf("%d", &scelta);
        switch (scelta){

            case 1:
            login(lista_utenti, tail_utente, &lista_libri, &tail_libro, lista_recensioni, tail_recensione);
            break;

            case 2:
            registrazione(&lista_utenti, &tail_utente);
            scrivifile(lista_utenti);
            break;

            case 3:printf("\nARRIVEDERCI!\n\n\n");
                exit(0);

            default: printf("\n RIPROVA!\n\n\n");
            while(strcmp(fgets(controllo,10,stdin),"\n")==0);
        };
    }
    return 0;
};

