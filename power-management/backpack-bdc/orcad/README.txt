13/5/2015

Praticamente alla prima accensione dell'iCub viola completo, un transistor dell'HSM si è bruciato e le schede a 48V rimanevano sempre accese (quelle a 12V no perchè erano alimentate dal DC/DC). Queste le condizioni:
- la tensione dell'alimentatore era 42V
- la BDC aveva R22=110kohm per fissare il limite di potenza a 111W
- il robot differiva dall'iCub BLU su cui non si erano verificati mai problemi per 2 schede in più

Cambiando BDC, l'HSM andava in fault anche con una sola gamba collegata. Il waist collegato non dava problemi. Questa BDC però aveva la R22=180kohm che fissa Plimit=72W, troppo poco. 
Per risolvere temporaneamente il problema, ho sostituito la R22 con 120kohm (->Plimit=103W) e abbassato la tensione di alimentazione a 36V, così il robot si accende tutto senza andare in fault all'accensione.

Per migliorare la scheda, occorre cambiare i 4 transistor con altri più robusti e alzare il limite di potenza. Ad esempio:
- R22=110kohm -> Plimit=111W
- R22=100kohm -> Plimit=120W
I mosfet IITCODE 10127 hanno una SOA molto più vantaggiosa per i transitori, oltre ad avere una RDSon molto più bassa e stesso package/pinout. 
--------------