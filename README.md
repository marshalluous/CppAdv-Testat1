# CppAdv-Testat1
## BoundedBuffer ^

In dieser Aufgabe erstellen Sie schrittweise die grundlegende Datenstruktur für einen BoundedBuffer. Ihre Implementation wird die erste Testatabgabe sein. Sie können das Testat in Gruppen von bis zu drei Studenten abgeben:

    Senden Sie dafür eine E-Mail an: Thomas Corbat & Peter Sommerlad
    Betreff: [C++A-testat-1] hsrname1 hsrname2 hsrname3
    Inhalt: BoundedBuffer.h (+ falls Sie eigene Tests haben: bounded_buffer_student_suite.cpp)
    Sie erhalten dann Feedback.
    Abgabefrist: Dienstag 27. März 2018 23:59 Uhr (MEZ) 

## Einführung ^

BoundedBuffers werden in einer Umgebung eingesetzt, in welcher Producer und Consumer eine gemeinsame Datenstruktur zur Austausch von Elementen verwenden. Der BoundedBuffer hat eine fixe Grösse und wird als FIFO-Queue implementiert. Für einen Consumer ist es wichtig, dass er nicht Daten aus einem leeren Buffer auslesen kann. Der Producer auf der anderen Seite darf nicht in einen vollen Buffer hineinschreiben.

Ihre Implementation wird auf einem Array (std::array) basieren und der Funktionsweise eines Circular Buffers entsprechen.

 

Folgende Member Funktionen muss ihr BoundedBuffer aufweisen:

    empty – dient der Abfrage ob der Buffer leer ist
    full – dient der Abfrage ob der Buffer voll ist
    size – gibt die Anzahl Elemente im Buffer zurück
    front – liefert das erste Element im Buffer zurück; dies kann veränderbar sein
    back – liefert das letzte Element im Buffer zurück; dies kann veränderbar sein
    push – fügt ein neues Element in den Buffer ein
    pop – entfernt das erste Element aus dem Buffer
    swap – tauscht den Inhalt mit einem anderen BoundedBuffer (Parameter) aus 

Folgende Member Typen muss ihr BoundedBuffer haben:

    value_type
    container_type
    reference
    const_reference
    size_type 

Sie erhalten für jede Aufgabe Test-Suiten. Wir empfehlen Ihnen jeweils nur einen einzelnen Test hinzuzunehmen (die nachfolgenden auskommentieren). Meistens wird dies zu einer Red-Bar führen. Implementieren Sie nur so viel Code, dass Sie wieder eine Green-Bar erhalten. Fügen Sie anschliessend den nächsten Test hinzu.

## Member Definitionen (Signaturen) ^

Implementieren Sie zuerst die Deklarationen der Member von BoundedBuffer ohne Logik, um einen kompilierfähigen BoundedBuffer Typ zu erhalten.

    Test-Suite: bounded_buffer_signatures_suite 

Tipp: Wenn Sie sich bei den Signaturen der Member Funktionen unsicher sind, können Sie sich bei denjenigen von Queue inspirieren lassen.

Anmerkung: Wir haben einige Tests zur Verfügung gestellt, welche nicht wirklich sinnvoll für ein reales Test-Szenario sind. Sie helfen Ihnen jedoch die Member direkt richtig zu deklarieren, so dass Sie sie später nicht mehr anpassen müssen. Diese Tests sind von Boost (type_index.hpp) abhängig. Entsprechend sollte die Boost-Library auf dem System installiert oder im Projekt eingebunden werden. Vorsicht! Die Boost-Headers eines CUTE Projekts (Häkchen im Wizard) reichen nicht für diese Test-Cases.

Verhalten eines default-konstruierten Buffers ^

Implementieren Sie nun das Verhalten der Member-Funktionen für einen default-konstruierten Buffer. Vermeiden Sie dabei Undefined Behavior!

    empty - gibt true zurück
    full – gibt false zurück, ausser wenn der Buffer mit Grösse 0 erstellt wurde
    size – liefert 0
    front – wirft eine Exception (std::logic_error)
    back – wirft eine Exception (std::logic_error)
    push – fügt ein Element hinzu, dies ist jedoch nicht ohne weiteres zu beobachten und das Abspeichern des Elements kann im Moment ignoriert werden. Für einen Buffer der Grösse 0 wird jedoch eine Exception (std::logic_error) geworfen, da der Buffer voll ist.
    pop – wirft eine Exception (std::logic_error)
    swap – bei leeren Buffern passiert hier nichts 

    Test-Suite: bounded_buffer_default_behavior_suite 

## Inhalt des Buffers ^

Da das Buffer-Interface jetzt steht, können Sie die benötigte Logik implementieren. Sie haben beim Array-basierten zirkulären Buffer zwei Möglichkeiten, wie sie diesen realisieren. Dies wissen Sie jedoch bereits aus Algorithmen & Datenstrukturen. Eine kurze Zusammenfassung:

    Entweder arbeiten Sie mit Zeigern (in unserem Fall Indizes des Arrays) für die Start- und End-Position. Die Start-Position zeigt auf das erste Element und die End-Position hinter das letzte Element. Wenn Start- und End-Position auf das gleiche Element zeigen, ist der der Buffer leer. Dies reduziert jedoch die mögliche Anzahl Elemente des Buffers um eins, da ein voller Buffer denselben (Zeiger-)Zustand hätte. Also müsste Ihr Array um eins grösser sein, um der Kapazität zu entsprechen, welche als Argument bei der Deklaration angegeben wurde.
    Oder Sie haben nur einen Index für das erste Element und einen Zähler für die Anzahl der Elemente im Buffer. Dann können Sie ein Array verwenden, welches dieselbe Grösse wie der Buffer hat. 

Die letztere Variante ist einfacher zu implementieren und verständlicher zu lesen. Sie können aber auch die erste Variante nehmen, dann müssen Sie den Test, welcher den Typ BoundedBuffer::container prüft aber anpassen.

Ansonsten sollte das Verhalten des Buffers selbsterklärend sein:

    Solange der Buffer nicht voll ist kann man Elemente einfügen, sonst gibt es beim Versuch eine Exception.
    Solange der Buffer nicht leer ist kann man Elemente auslesen und entfernen, sonst gibt es beim Versuch eine Exception.
    Der Buffer funktioniert nach dem FIFO-Prinzip. Sprich Das zuerst eingefügte Element (push()) wird auch zuerst wieder entfernt (pop()). Das zuerst eingefügte Element kann mit front() geholt werden und back() liefert das zuletzt eingefügte Element zurück.
    swap() vertauscht den Inhalt mit dem Argument-Buffer 

Verwenden Sie für den Elementzugriff vom Array möglichst die at()-Funktion, damit Sie sehen, falls Sie versehentlich auf ein Element ausserhalb des gültigen Bereichs zugreifen.

    Test-Suite: bounded_buffer_content_suite 

Weiter gibt es noch eine Test-Suite, welche sicherstellt, dass die Elemente mit den richtigen Operationen verschoben und kopiert werden. Diese Suite arbeitet mit einem Objekt welches die Memory-Operationen aufzeichnet und schlussendlich prüft, ob die erwarteten Copy/Move-Operationen verwendet wurden.

    Test-Suite: bounded_buffer_semantic_suite 

## Konstruktoren ^

Die impliziten-Konstruktoren genügen für die Implementation bis anhin. Implementieren diese nun selber, so dass jeweils die passende Operation auf die Elemente angewendet wird, so wie es die impliziten Konstruktoren auch machen. Implementieren Sie die folgenden Special Member Functions:

    Default-Konstruktor
    Copy-Konstruktor
    Move-Konstruktor
    Copy-Assignment-Operator
    Move-Assignment-Operator 

Später werden wir den BoundedBuffer abändern, so dass er mit Heap-Memory arbeitet und dann werden wir die eigenen Konstruktoren benötigen.

## Vorgaben ^

Da Sie nun alles durchgelesen haben, hier ist das Archiv mit den vorgegeben Dateien:

https:files/Vorgabe_BoundedBuffer.zip

Erstellen Sie ein neues CUTE Executable Projekt und legen Sie die Dateien des Archivs im src-Verzeichnis ab. Die Datei BoundedBuffer.h müssen Sie selber erstellen. 
