# SO - Lista 13

## Materiały
### [1, 2.3 (2.3.5, 2.3.6)] - tannenbaum
### [2, 6.1 – 6.6] - silberschatz (os concepts)
### [3, 28, 31 i 32] - 3ez pcs

## 1
![](https://i.imgur.com/AqpZbGT.png)

### Kod
oparte na: Operating Systems: Three Easy Pieces 31.8
```c=
typedef struct Sem { 
  pthread_mutex_t mutex;  // muteks
  pthread_cond_t waiters; // zmienna warunkowa
  int value;              // nieujemna wartość 
} Sem_t;
```

![](https://i.imgur.com/xFRMTkw.png)
```c=
void sem_init(Sem_t* s, int value) {
    assert(value >= 0);
    s->value = value;
    pthread_cond_init(&s->waiters, NULL);
    pthread_mutex_init(&s->mutex, NULL);
}
```
inicjalizujemy muteks i zmienną warunkową z domyślnymi atrybutami (przekazane NULL)


![](https://i.imgur.com/tQTwro2.png)

```c=
void sem_wait(Sem_t* s) {
    pthread_mutex_lock(&s->mutex);
    while (s->value <= 0) {
        pthread_cond_wait(&s->waiters, &s->mutex);
    }
    s->value--;
    pthread_mutex_unlock(&s->mutex));
}
```
jeśli wartość spadła poniżej 1 to używamy zmiennej warunkowej (która odblokowuje mutex ale blokuje na waiters) i nie zmniejszamy dalej wartości

```c=
void sem_post(Sem_t* s) {
    pthread_mutex_lock(&s->mutex));
    s->value++;
    pthread_cond_signal(*s->waiters); // budzimy dokładnie jeden śpiący wątek
    pthread_mutex_unlock(&s->mutex));
}
```

## 3
![](https://i.imgur.com/c2yTTSq.png)

### Objaśnienie
```python
mutex = semaphore(1) # implementuje sekcję krytyczną
block = semaphore(0) # oczekiwanie na opuszczenie zasobu
active = 0           # liczba użytkowników zasobu
waiting = 0          # liczba użytkowników oczekujących na zasób
must_wait = False    # czy kolejni użytkownicy muszą czekać?

def acquire():
  mutex.wait()
  if must_wait: # czy while coś zmieni?
    waiting += 1
    mutex.post()
    block.wait()
    mutex.wait()
    waiting -= 1
  active += 1
  must_wait = (active == 3)
  mutex.post()

def release():
  mutex.wait()
  active -= 1
  if active == 0:
    n = min(waiting, 3);
    while n > 0:
      block.post()
      n -= 1
    must_wait = False
  mutex.post()
```

mutex jest wykorzystany do implementacji scieżki krytycznej dla procedur `acquire` i `release` (podnosimy na początku, zwalniamy na końcu)

acquire:
`must_wait` w acquire występuje gdy mamy 3 aktywne procesy działające na zasobie, wtedy zwiększamy liczbę oczekujących i zwalniamy mutex na czas `block.wait()` (tak by w release można było wejść do ścieżki krytycznej i przepuścić 1 oczekujący)
po odblokowaniu i przejściu proces oczekujący staje się aktywny i sprawdzamy liczbę aktywnych procesów

release:
zmniejszamy liczbę aktywnych o 1,
jeśli spadła do zera to odblokowujemy co najwyżej 3 wątki oczekujące i ustawiamy `must_wait` na False tak by przepuścić w `acquire`

Użycie:
```Python=
acquire()

// operacje na zasobie

release()
```

### Kontrprzykład
#### 1 - właściwość 1 i 4
załóżmy że mamy 3 procesy które mają już dostep do zasobu (przeszły `acquire()`) i conajmniej 3 które czekają (w linii 6)
```python=
acquire()
// 3 procesy
release()
```
active = 3, must_wait = True, waiting >= 3
3 aktywne procesy robią po kolei `release()`
w linii 18 ostatni wykonuje 3-krotnie `block.post()` i ustala `must_wait` na False
wtedy zanim wybudzimy wątki w linii 6 przychodzą nowi użytkownicy `acquire()` i omijają must_wait a dodatkowo 3 zostają wybudzone:
```pyton=
    mutex.post() 
    block.wait() // tu są 3 wybudzane wątki
```

mamy wtedy więcej niż 3 aktywnych użytkowników oraz zostanie naruszona kolejność FIFO, (dodatkowo must_wait sprawdza równość do 3 a mamy więcej)

#### 2 - właściwość 2
załóżmy że mamy 3 procesy które mają już dostep do zasobu (przeszły `acquire()`)
i teraz 3 procesy wchodzą do `acquire()` i po zwolnieniu muteksu w linii 5 a przed zablokowaniem w 6 zasypiają
teraz 3 procesy aktywne robią `release()`, 3 procesy się budzą w linii 5 i robią block.wait()