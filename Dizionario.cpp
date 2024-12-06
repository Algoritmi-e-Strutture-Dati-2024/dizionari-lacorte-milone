#include <iostream>
#include <string>

template <typename T>
class Dizionario {
private:
    static const int TABLE_SIZE = 100; // Dimensione fissa della tabella hash
    struct Entry {
        std::string key;
        T value;
        bool isOccupied = false;
    };

    Entry table[TABLE_SIZE];

    // Funzione hash fornita dall'utente
    int hashFunction(const std::string& key) const {
        int hash = 0;
        for (char ch : key) {
            hash += static_cast<int>(ch); // Somma il valore intero di ogni carattere
        }
        return hash % TABLE_SIZE; // Modulo per limitare il valore nell'intervallo della tabella
    }

    // Funzione per trovare una posizione disponibile (gestione collisioni con linear probing)
    int findSlot(int index) const {
        int originalIndex = index;
        while (table[index].isOccupied) {
            index = (index + 1) % TABLE_SIZE; // Linear probing
            if (index == originalIndex) {
                return -1; // La tabella è piena
            }
        }
        return index;
    }

public:
    // Metodo per aggiungere una coppia chiave-valore
    void inserisci(const std::string key, const T value) {
        int index = hashFunction(key);

        // Se la posizione è occupata, cerchiamo una posizione libera con findSlot
        if (table[index].isOccupied) {
            index = findSlot(index);
            if (index == -1) {
                std::cerr << "La tabella è piena, impossibile inserire la chiave: " << key << "\n";
                return;
            }
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
    }

    // Metodo per ottenere il valore associato a una chiave
    T recupera(const std::string key) const {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % TABLE_SIZE; // Linear probing
            if (index == originalIndex) {
                break; // Abbiamo ciclato tutta la tabella
            }
        }
        throw std::runtime_error("Chiave non trovata!"); // Se non trovato, lanciamo un'eccezione
    }

    // Metodo per cancellare una coppia chiave-valore
    void cancella(const std::string key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                table[index].isOccupied = false;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                break; // Abbiamo ciclato tutta la tabella
            }
        }

        std::cerr << "Chiave " << key << " non trovata per la cancellazione.\n";
    }

    // Metodo per modificare il valore associato a una chiave
    void modifica(const std::string key, const T newValue) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                table[index].value = newValue;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                break; // Abbiamo ciclato tutta la tabella
            }
        }

        std::cerr << "Chiave " << key << " non trovata per la modifica.\n";
    }

    // Metodo per verificare se una chiave è presente nel dizionario
    bool appartiene(const std::string key) const {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].isOccupied) {
            if (table[index].key == key) {
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                break; // Abbiamo ciclato tutta la tabella
            }
        }

        return false;
    }

    // Metodo per stampare il contenuto del dizionario
    void stampa() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].isOccupied) {
                std::cout << "Index " << i << ": " << table[i].key << " => " << table[i].value << "\n";
            }
        }
    }
};
