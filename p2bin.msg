AS Message Catalog - not readable
???^ib2pEN         S   DE h     1   ?   ?   ?   ?   ?   ?     (  H  ]  ?  ?  ?  ?  ?  ?      #  Z  p  calling convention:  invalid file header invalid record header invalid record length warning : file mask   does not fit to any file! invalid environment parameter:  invalid parameter :  destination file specification missing! automatic range setting failed! warning: overlapping memory allocation! program terminated .p checksum:   <source file(s)> <target file> [options] Byte Bytes 
options: -f <header list>  :  records to filter out
         -r <start>-<stop> :  address range to filter out
         ($ = first resp. last occuring address)
         -segment <name>   :  select source segment
         -l <8-bit-number> :  set filler value for unused cells
         -s                :  put checksum into file
         -m <mode>         :  EPROM-mode (odd,even,byte0..byte3)
         -e <address>      :  set entry address
         -S [L|B]<length>  :  prepend entry address to image
         -k                :  automatically erase source files
 Deduced address range Warning: no data transferred, wrong/missing -r option?
 ?      9  Y  o  ?  ?  ?  ?    7  G  J  [  ?  ?  ?  ?  	  Aufruf:  ung&uuml;ltiger Dateikopf ung&uuml;ltiger Datensatzkopf fehlerhafte Datensatzl&auml;nge Warnung : Dateimaske   pa&szlig;t auf keine Datei! Fehlerhafter Environment-Parameter :  Fehlerhafter Parameter :  Zieldateiangabe fehlt! automatische Bereichserkennung fehlgeschlagen! Warnung: &uuml;berlappende Belegung! Programmabbruch .p Pr&uuml;fsumme:   <Quelldatei(en)> <Zieldatei> [Optionen] byte bytes 
Optionen: -f <Headerliste>  :  auszufilternde Records
          -r <Start>-<Stop> :  auszufilternder Adre&szlig;bereich
          ($ = erste bzw. letzte auftauchende Adresse)
          -segment <Name>   :  Quellsegment w&auml;hlen
          -l <8-Bit-Zahl>   :  Inhalt unbenutzter Speicherzellen festlegen
          -s                :  Pr&uuml;fsumme in Datei ablegen
          -m <Modus>        :  EPROM-Modus (odd,even,byte0..byte3)
          -e <Adresse>      :  Startadresse festlegen
          -S [L|B]<L&auml;nge>   :  Startadresse voranstellen
          -k                :  Quelldateien automatisch l&ouml;schen
 Ermittelter Adre&szlig;bereich Warnung: keine Daten &uuml;bertragen, falsche/fehlende -r Option?
 