# -Image-Compression-Using-Quadtrees

## Descriere

Acest proiect constă în implementarea unui algoritm de compresie a imaginilor utilizând arbori cuaternari. Proiectul include atât compresia, cât și decompresia imaginilor color în format PPM.

### Scopul proiectului

Prin realizarea acestuia, am învățat să:
- Aplic arbori cuaternari pentru compresia imaginilor.
- Implementez operații standard de prelucrare a imaginilor.
- Dezvolt o metodă eficientă de stocare și reconstrucție a imaginilor folosind arbori cuaternari.

---

## Algoritm de compresie

1. **Construirea arborelui cuaternar**:
   - Se împarte imaginea în blocuri pătrate de dimensiune 2^N.
   - Fiecare nod al arborelui corespunde unei zone pătrate din imagine.
   - Dacă o zonă este uniformă (culoare medie calculată), aceasta devine nod terminal.
   - Dacă nu, zona este împărțită în 4 subzone, fiecare reprezentată de un nod fiu.

2. **Parcurgerea arborelui**:
   - Se efectuează o parcurgere pe nivel a arborelui pentru a genera fișierul de compresie.
   - Fiecare nod frunză conține valorile RGB medii pentru zona corespunzătoare.

3. **Decompresia**:
   - Se reconstruiește arborele cuaternar din fișierul binar comprimat.
   - Se generează imaginea PPM utilizând structura de arbore generată.

---

## Structura proiectului

```
.
├── src/
│   └── quadtree.cpp (codul sursă)
├── Makefile
└── README.md
```

---

## Compilare

Programul se compilează utilizând comanda:

```
make build
```

Acest lucru va genera un executabil numit `quadtree`.

Pentru a curăța fișierele generate la compilare, folosiți comanda:

```
make clean
```

---

## Rulare

Pentru a rula programul, folosiți următoarea comandă:

```
./quadtree [-c1 factor | -c2 factor | -d] [fisier_intrare] [fisier_iesire]
```

### Opțiuni
- **-c1 factor**: Construiește arborele și calculează statistici.
- **-c2 factor**: Realizează compresia imaginii.
- **-d**: Realizează decompresia imaginii.
- **fisier_intrare**: Numele fișierului PPM de intrare.
- **fisier_iesire**: Numele fișierului de ieșire (text sau binar).

### Exemplu

```
./quadtree -c1 10 image.ppm stats.txt
./quadtree -c2 15 image.ppm compressed.bin
./quadtree -d compressed.bin decompressed.ppm
```