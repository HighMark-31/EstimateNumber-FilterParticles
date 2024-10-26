# Particle Filter Number Estimator 🎲

## Descrizione 📖

Questo programma implementa un filtro particellare per stimare un numero intero inserito dall'utente nell'intervallo da 1 a 10. Utilizza un insieme di particelle per rappresentare possibili valori e calcola una stima basata su pesi che riflettono la probabilità di ciascun valore in base all'input fornito.

## Funzionalità ✨

- **Stima del numero**: Chiede all'utente di inserire un numero tra 1 e 10 e fornisce una stima del numero inserito.
- **Resampling delle particelle**: Aggiorna e normalizza i pesi delle particelle ad ogni iterazione per migliorare la precisione della stima.
- **Debug**: Fornisce informazioni dettagliate durante il processo di stima per aiutare a comprendere il funzionamento interno.

## Come Funziona 🔍

1. **Inizializzazione delle particelle**: Viene creato un numero definito di particelle (1000) e ognuna di esse viene inizializzata con un valore casuale nell'intervallo specificato e un peso iniziale uniforme.
  
2. **Aggiornamento dei pesi**: I pesi delle particelle vengono aggiornati in base alla somiglianza con l'input dell'utente. Viene applicato un rumore gaussiano per simulare l'incertezza.

3. **Normalizzazione dei pesi**: I pesi vengono normalizzati per assicurarsi che la loro somma sia pari a 1.

4. **Resampling**: Le particelle vengono ri-campionate in base ai pesi aggiornati per ottenere una nuova generazione di particelle più rappresentativa dell'input dell'utente.

5. **Stima finale**: Viene calcolata la stima finale del numero basata sui valori delle particelle e i loro pesi.

## Tecnologie Utilizzate 💻

- **Linguaggio di programmazione**: C++
- **Librerie standard**: `<iostream>`, `<vector>`, `<random>`, `<algorithm>`

## Come Eseguire il Programma 🚀

1. Assicurati di avere un compilatore C++ installato.
2. Clona il repository o scarica il file sorgente.
3. Compila il programma:

   ```bash
   g++ -o particle_filter particle_filter.cpp

