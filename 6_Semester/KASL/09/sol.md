# Lista 9
## Zad1
zadania systemu DOS:

• Czy DOS zarządza pamięcią?
Tak
https://en.wikipedia.org/wiki/DOS_memory_management

• Czy pamięć jest zwirtualizowana?
Nie

zamiast tego Bank switching (Expanded memory system)

• Czy jest w DOS-ie ochrona pamięci?
https://en.wikipedia.org/wiki/DOS_Protected_Mode_Interface

• Czym jest proces w DOS-ie?
Proces jest ładowany do pamięci i wykonywany w całości.

• Czy DOS dokonuje podziału czasu pomiędzy procesami?
Nie
Uniprogramming system: only supports a single process at a time. 

• Jak odbywa się zarządzanie procesami?
Załadowanie programu do pamięci, zainicjalizowanie rejestrów i skok do startu

po zakończeniu -> return i skok wskaźnika instrukcji do wcześniejszego miejsca

• Jak jest zorganizowana obsługa wywołań systemowych?
http://spike.scu.edu.au/~barry/interrupts.html

• Jak architektura procesora 8088 wpłynęła na strukturę systemu DOS?
"When the system is started or reset, program execution begins at address
OFFFFOH."

"The Intel 8086/8088 and
80286 microprocessors have four segment registers, which are essentially
used as pointers to these blocks"

Segmentowania pamięci, tzn podawania adresu logicznego w postaci dwóch liczb 16 bitowych.
segment + offset
