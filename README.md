Dans le module CPP09, la règle importante est la suivante :

> Un conteneur utilisé dans un exercice ne peut plus être utilisé dans les suivants.

Cela impose donc de choisir des conteneurs différents selon les exercices. En pratique, on trouve généralement :

* **ex00 : `std::map`**
* **ex01 : `std::stack`**
* **ex02 : `std::vector` et `std::deque`**

C'est d'ailleurs exactement ce que la majorité des implémentations 42 utilisent. ([GitHub][1])

---

# ex00 — BitcoinExchange

## Conteneur utilisé : `std::map`

```cpp
std::map<std::string, float> database;
```

La clé :

```cpp
"2011-01-03"
```

La valeur :

```cpp
0.30
```

---

## Fonctionnement

Une `map` stocke des paires :

```text
clé  -> valeur

2011-01-03 -> 0.30
2011-01-09 -> 0.32
2012-01-11 -> 7.10
```

Les éléments sont automatiquement triés par clé.

Comme les dates au format `YYYY-MM-DD` sont également triées alphabétiquement, cela fonctionne parfaitement.

On peut alors faire :

```cpp
database.lower_bound(date);
```

pour récupérer la date exacte ou la date immédiatement précédente demandée par le sujet. ([42 Tutor][2])

---

## Pourquoi `map` ?

Le sujet demande :

> Si la date n'existe pas, utiliser la date inférieure la plus proche.

Exemple :

```text
2011-01-08
```

n'existe pas.

On doit récupérer :

```text
2011-01-03
```

Avec :

```cpp
it = database.lower_bound(date);
```

cela devient très simple.

---

## Avantages

### 1. Tri automatique

Pas besoin de trier les dates.

---

### 2. Recherche rapide

Complexité :

```text
O(log n)
```

---

### 3. `lower_bound`

Fonction essentielle du sujet.

---

### 4. Une seule valeur par date

Impossible d'avoir deux fois :

```text
2011-01-03
```

---

## Inconvénients

### 1. Plus lent qu'un tableau

Accès :

```text
vector : O(1)
map    : O(log n)
```

---

### 2. Plus de mémoire

Chaque nœud contient plusieurs pointeurs.

---

### 3. Pas d'accès par indice

Impossible :

```cpp
database[5];
```

---

# ex01 — RPN

## Conteneur utilisé : `std::stack`

```cpp
std::stack<int> numbers;
```

Le sujet demande d'évaluer une expression polonaise inversée :

```text
8 9 * 9 - 9 -
```

---

## Fonctionnement

Une pile fonctionne selon le principe :

```text
LIFO
Last In First Out
```

Le dernier élément entré est le premier sorti.

---

Exemple :

```text
3 4 +
```

Pile :

```text
3
3 4
```

On rencontre :

```text
+
```

On retire :

```cpp
4
3
```

On calcule :

```cpp
3 + 4 = 7
```

On remet :

```text
7
```

---

## Pourquoi `stack` ?

Le RPN est littéralement conçu pour fonctionner avec une pile.

L'algorithme est :

* chiffre → push
* opérateur → pop deux nombres
* calcul
* push résultat

---

## Avantages

### 1. Code extrêmement simple

```cpp
stack.push();
stack.pop();
stack.top();
```

---

### 2. Correspond exactement au problème

Une RPN est naturellement une pile.

---

### 3. Opérations très rapides

```text
push : O(1)
pop  : O(1)
top  : O(1)
```

---

## Inconvénients

### 1. Pas d'itérateurs

Impossible :

```cpp
for (...)
```

---

### 2. Pas d'accès aux éléments internes

Impossible :

```cpp
stack[2];
```

---

### 3. Très spécialisé

Une pile ne sert qu'à certains problèmes.

---

# ex02 — PmergeMe

## Conteneurs utilisés :

```cpp
std::vector<int>
std::deque<int>
```

Le sujet impose explicitement :

> utiliser au moins deux conteneurs différents.

Le but est ensuite de comparer leurs performances. ([DeepWiki][3])

---

# 1. `std::vector`

```cpp
std::vector<int> vec;
```

---

## Fonctionnement

Les éléments sont stockés de façon contiguë en mémoire :

```text
[3][7][9][12][20]
```

Comme un tableau dynamique.

---

## Avantages

### Accès ultra rapide

```cpp
vec[i]
```

Complexité :

```text
O(1)
```

---

### Très bon cache processeur

Les éléments sont côte à côte.

Le CPU travaille donc très efficacement.

---

### Très rapide pour les algorithmes

C'est souvent le conteneur STL le plus rapide.

---

## Inconvénients

Insertion au milieu :

```cpp
vec.insert(...)
```

peut déplacer beaucoup d'éléments.

Complexité :

```text
O(n)
```

---

# 2. `std::deque`

```cpp
std::deque<int> deq;
```

---

## Fonctionnement

Une deque est constituée de plusieurs blocs mémoire.

Schématiquement :

```text
Bloc1 -> Bloc2 -> Bloc3
```

Les données ne sont pas forcément contiguës.

---

## Avantages

### Insertion au début rapide

```cpp
push_front()
```

en :

```text
O(1)
```

---

### Insertion à la fin rapide

```cpp
push_back()
```

---

### Taille flexible

Moins de réallocations qu'un vector.

---

## Inconvénients

### Moins bon cache CPU

Les données sont dispersées.

---

### Accès légèrement plus lent

```cpp
deq[i]
```

reste O(1), mais souvent un peu moins rapide.

---

# Pourquoi comparer vector et deque ?

Le sujet veut montrer qu'un même algorithme peut avoir des performances différentes selon le conteneur.

Souvent :

```text
vector : plus rapide
deque  : légèrement plus lente
```

car `vector` profite de la mémoire contiguë. ([DeepWiki][3])

---

# Résumé

| Exercice | Conteneur     | Pourquoi                            |
| -------- | ------------- | ----------------------------------- |
| ex00     | `std::map`    | recherche de dates et `lower_bound` |
| ex01     | `std::stack`  | calcul RPN basé sur une pile        |
| ex02     | `std::vector` | rapidité et accès mémoire           |
| ex02     | `std::deque`  | comparaison de performances         |

# Ce qu'il faut retenir pour la soutenance

### ex00

> J'utilise `std::map` car les dates sont automatiquement triées et `lower_bound()` permet de récupérer la date précédente demandée par le sujet.

### ex01

> J'utilise `std::stack` car une expression RPN se résout naturellement avec une pile LIFO.

### ex02

> J'utilise `std::vector` et `std::deque` pour implémenter le Ford–Johnson et comparer les performances des deux conteneurs. `vector` est généralement plus rapide grâce à sa mémoire contiguë.

[1]: https://github.com/aaron-22766/42_CPP?utm_source=chatgpt.com "GitHub - aaron-22766/42_CPP: Collection of modules for learning object-oriented programming and everything C++ · GitHub"
[2]: https://42tutor.com/solutions/09-module-solutions/?utm_source=chatgpt.com "Module 09 Solutions | 42 Tutor"
[3]: https://deepwiki.com/leske42/CPP09/2.5-performance-analysis?utm_source=chatgpt.com "Performance Analysis | leske42/CPP09 | DeepWiki"
