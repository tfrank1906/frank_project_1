# frank_project_1 - "processTree"

## Wichtige Information:
Sehr geehrter Herr Professor,

leider sind die **ersten 9 Commits** von mir ins falsche Repository gepusht worden.
Ich habe diese nun händisch übertragen. Ich hoffe das ist kein zu großes Problem.

Mit freundlichen Grüßen,
Tobias Frank

## Projektbeschreibung:
### Projektinhalt
Das Projekt umfasst das Programm "processTree".
Dieses erstellt Prozesse in einer Baumstruktur. Der Benutzer kann angeben wieviele Kinder der Hauptprozess haben soll und wieviele Kinder diese Kindprozesse haben sollen (Blätter des Baumes). Die beiden Werte dürfen nicht größer als 5 sein.

Ein somit erstellter "Prozessbaum" besten immer aus 3 Ebenen:
- Ebene mit Hauptprozess
- Ebene mit Kindern des Hauptprozess
- Ebene mit Kindern der Kinder also Blätter des Baumes



Das Beenden dieser Prozesse kann über 2 Arten vollbracht werden.

Die erste Art ist das die Kindprozesse Warten bis sich die Blätter beenden und danach selbst beenden.

Die zweite Art ist das der Hauptprozess an seine Kinder ein Signal an seine Kindprozesse schickt die wiederum das Signal an ihre Kinder (also die Blätter) weiterleiten. Wenn diese das Signal bekommen haben, beenden sie sich.


### Bedienung

Zum Sarten des Programmes werden 2 Parameter gebraucht. Zusätzlich können verschiedene Optionen mitgegeben werden.

`./processTree m n --killsignal --log --experiment`  

- m: Anzahl der Kindprozesse
- n: Anzahl der Blätterprozesse
- killsignal: Gibt den Beendigungmechanismus an, wenn angegeben: mit Signal, sonst beendet sich selbst.
- log: wenn angegeben, schreibt in log
- experiment: lässt zu, dass man mehr als 5 Kinder mit 5 Blättern erstellt. (verlassen des safe - modes)

