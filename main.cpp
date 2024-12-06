#include <iostream>
#include "Dizionario.cpp"

int main() {

    // Creazione del dizionario
    Dizionario<std::string> dict;

    // Inserimento di alcune coppie chiave-valore
    dict.inserisci("apple", "fruit");
    dict.inserisci("car", "vehicle");
    dict.inserisci("book", "object");

    // Test di recupero dei valori
    std::cout << "Valore per 'apple': " << dict.recupera("apple") << "\n";
    std::cout << "Valore per 'car': " << dict.recupera("car") << "\n";
    std::cout << "Valore per 'pen': " << dict.recupera("pen") << "\n";  // Chiave che non esiste

    // Inseriamo una chiave che causerà una collisione (supponendo che 'car' e 'cat' abbiano lo stesso hash)
    dict.inserisci("cat", "animal");

    // Stampa il contenuto del dizionario
    std::cout << "\nContenuto del dizionario:\n";
    dict.stampa();

    // Test della cancellazione
    dict.cancella("car");
    std::cout << "\nDopo aver cancellato 'car', contenuto del dizionario:\n";
    dict.stampa();

    // Test dell'appartenenza
    std::cout << "\nLa chiave 'apple' appartiene? " << (dict.appartiene("apple") ? "Sì" : "No") << "\n";
    std::cout << "La chiave 'car' appartiene? " << (dict.appartiene("car") ? "Sì" : "No") << "\n";

    return 0;
}
