-----------------------------------------------------------------------------------------------
Note on BAT Rev.D

This revision D is equal to rev. C but with:
R37=33Ω and R65=15Ω
to have 36A current limit

-----------------------------------------------------------------------------------------------
Note on BAT Rev.C

Cambiamenti rispetto alla versione B
La versione precedente della scheda aveva solo i gerber. La versione C è stata ricostruita in PADS (scm + layout).
2) Rinforzate tutte le alimentazioni cambiando qualche posizione dei componenti per favorire un maggior flusso di corrente.
3) Cambiato il Micorcontrollore
4) Aggiunto J25 per comandarne lo spegnimento
5) Pull-up sul segnale di RESET per renderlo meno immune ai disturbi
6) Alzato di poco i connettori di potenza per problemi di interferenza
7) Alcuni spostamenti per rispettare i constraint sulle altezze massime

MB 19/7/22 Datapackage amended with gerber paste mask bot with added features for Q8-Q9 and L1 and L2 not present in the previous DP. See email on document

-----------------------------------------------------------------------------------------------
Note on BAT Rev.B 

- DL12 wrong mounted: turn it

- There were errors on property "NON MONTARE" components and they were mounted. The right property is "NonMontare". The components are the following:
FL3, FL6, FL9
C18, C19, C20
R60, R65, R66

- DL14 was not mounted, but it was on BOM

