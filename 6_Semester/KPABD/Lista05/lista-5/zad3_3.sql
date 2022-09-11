dbcc dropcleanbuffers; dbcc freeproccache;
GO

SET STATISTICS TIME ON

SELECT c.PESEL, c.Nazwisko
FROM Czytelnik c WHERE c.Czytelnik_ID IN
(SELECT w.Czytelnik_ID FROM Wypozyczenie w, Egzemplarz e, Ksiazka k
WHERE e.Egzemplarz_ID=w.Egzemplarz_ID
AND e.Ksiazka_ID=k.Ksiazka_ID)

SET STATISTICS TIME OFF