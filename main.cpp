/*
    Matteo Manià, CL 4IA.
    Consegna:
    Il testo può essere copiato/incollato da qualsiasi "fonte" adatta (un articolo, porzione di un libro, ecc.);
    va copiato in notepad (blocco note) e salvato con estensione ".txt".

    -Fase 1: individuare le parole separate da spazi e mostrarle sulla console.
    -Fase 2: individuare le parole separate da punteggiatura (delimitatori) qualsiasi e mostrarle sulla console.
    -Fase 3: inserire da console il nome del testo da analizzare.
    -Fase 4: trovare numero di parole, numero di caratteri (tutti e senza delimitatori),
            numero di paragrafi (gruppi di lettere terminati con un "a capo" - es. '\n'),
            numero di frasi (gruppi di lettere terminati con un terminatore - es . ;).
    -Fase 5: archiviare le parole (non ripetute) in un vettore di stringhe.
    Fase 6: contare le occorrenze di ciascuna parola in un vettore parallelo di interi.  //ogni parola ripetuta, aumenta IL SUO contatore.
    Fase 7: effettuare un'analisi statistica sulle informazioni raccolte per determinare la "natura" del testo (consulenza da parte dell'insegnate di lettere).
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;


FILE *fp;           //File.
string word = "";   //allocazione caratteri.
int DIM = 0;        //per le parole dell'array.
int DIMc = 0;       //per i caratteri.
const int PNT = 14; //costante per il contenitore di punteggiatura.
int lunghezzaParole = 0, caratteriTot = 0;


void ParoleSeparate(char c, string s_dim[], int z, int contatore, char caract[], int contaPnt, int j, string paroleCopia[]) {
    //calcolo media lunghezza.
    //somma parole con i contatori esistenti.
    int sommaParagrafi = 0;
    float mediaParole = 0, mediaFrasi = 0, mediaParagrafi = 0;

    //ciclo per la conta.
    while ((c = fgetc(fp)) != EOF) {
        if (c != ' ') {
            DIMc++;
            caratteriTot++;
        }
    }

    //riporta il puntatore a 0.
    fseek(fp, 0, SEEK_SET);

    while ((c = fgetc(fp)) != EOF) {
        if (c != ' ') {
            z++;              //contatore caratteri.
            word += c;        //aggiunge il caract. alla stringa.
            caract[DIMc] = c; //copia il carattere in un vettore parallelo.

            if (c == '\n' || c == '. ' || c == '; ')
                j++;         //contatore frasi (con a capo).

            if (c == ':' || c == ';' || c == ':' || c == '.' || c == ',' || c == '!' || c == '?' || c == '/' || c == '|')
                contaPnt++;  //conta punteggiatura.

            if (c == '. ')
                sommaParagrafi++;

        } else {
            cout << word;
            word = " ";    //parole spaziate.
            contatore++;   //contatore parole.
        }
    }

    if(word != "") {  //eventuali parole.
        cout << word << endl;
        word = " ";
        contatore++;
    }

    //output
    cout << "\n-Conta parole: " << contatore;
    cout << "\n-I caratteri sono: " << z; //stampa la conta dei caratteri.
    cout << "\n-Le parole con la punteggiatura sono: " << contaPnt;
    cout << "\n-Le frasi con il ritorno a capo sono: " << j;

    //calcolo medie (3)
    if (z != 0 && contatore != 0) {
        mediaParole = z/contatore;
        cout << "\n-La lunghezza media delle parole e\': " << mediaParole;
    }
    if (contatore != 0 && j != 0) {
        mediaFrasi = contatore/j;
        cout << "\n-La lunghezza media delle frasi e\': " << mediaFrasi;
    }
    if (sommaParagrafi != 0 && contatore != 0) {
        mediaParagrafi = sommaParagrafi/contatore;
        cout << "\n-La lunghezza media dei paragrafi e\': " << mediaParagrafi;
    }

    //memorizzo le parole totali.
    lunghezzaParole = contatore;
}


//ricerca parole uguali
void ricerca_uguali(string s_dim[], int caratteriTot, string paroleCopia[], char c){
    int k = 0, i = 0, j = 0;

    for (int i = 0; i < lunghezzaParole; i++) {
        if (paroleCopia[DIM] != "") {  //controllo
            if (paroleCopia[DIM] == word) { //se è uguale
                k++; //aumenta
            }
        } else  //se la parole non è presente, la aggiunge(finisce la parola, inizia un altra).
            paroleCopia[DIM] = word;
    }

    cout << "\n-le parole uguali non archiviate sono: " << k << endl;
}


int main() {
    string nome_file;
    char c;                                                 //caratteri.
    int i = 0, contatore = 0, v = 0, z = 0, contaPnt = 0;   //variabili contatore per lunghezza(punteggiatura, caratteri e parole).
    int j = 0, k = 0;                                       //variabili contatore per frasi e paragrafi.
    string s_dim[DIM], paroleCopia[lunghezzaParole];        //DIM è la conta di parole.
    int vetInteri[DIM];                                     //stessa dimensione delle parole.
    char caract[DIMc];
    int contatorePr = 0, f, contaPar[DIM];                  //parole archiviate.

    cout << "\nInserisci il nome del file da aprire: (file.txt)" << endl;
    cin >> nome_file;

    //apertura file.
    if (nome_file == "file.txt") {
        fp = fopen("file.txt", "r");

        //secondo controllo.
        if (!fp)
            cout << "File non trovato /o errore di digitazione. \n";

        //codice dove avvengono le varie fasi.
        else {
            //funzione per unire le parole separate da uno spazio / caratteri / punteggiatura.
            cout << "\ntesto: " << endl;
            ParoleSeparate(c, s_dim, z, contatore, caract, contaPnt, j, paroleCopia);

            //procedura (fase5) archiviare parole non ripetute(uguale) in un vettore di stringhe.
            fseek(fp, 0, SEEK_SET); //puntatore all'inizio.
            ricerca_uguali(s_dim, contatorePr, paroleCopia, c);
        }

    } else
        cout << "File non trovato /o errore di battitura." << endl;  //segnala l'errore.

    fclose(fp); // chiusura file di testo.

    return 0;
}
