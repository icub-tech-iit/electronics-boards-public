2FOC board FW
- 2FOC: main FW development branch
 Revision history
  
  rev 2.7: - Fixed ADC cal. (removed remaining offset)
           - Added command to retrigger ADC cal.
           - Set PWM to 50% for all chs when in initialization
           - Moved ADC sample point to PWM centre
           - Fixed SVGen was writing PDC registers with overrange/underrange values
           - Fixed negs executed on 0x8000 in some Microchip DSP code
           - Introduced PWM limit parameter in userparm.h
           - Changed WPID and IPID commands to contains also I limit val
           - On fault now status message is TXed
           - Fixed partial fault reset when entering OperationDisable and OperationEnable again
           - Reworked HES code to be consistent with other encoders
           - Activated encoder read and turn cound even when PWM disabled
           - Fixed turn count
           - A lot of optimizations
           - Added HES invalid seq check
           - Fixed fault handling when fault happen during initialization
           - No more bagpipes :) (do not accept torque setpoints when in speed loop)
           - Introduced SW position limits
           - Fixed ADC cal did not worked correctly in some cases
  
  rev 2.6: - Introduced new debug feature: Gulp hi-res history buffer for off-line trace
           - Get fault status command now sends out also status periodic message (gulp sees it because it has the same ID of regular periodic messages)
           - Fix PID I limit did not worked
           - Added PID I limit to userparams

 - Digital filters used in 2FOC code  

 * modifiche necessarie per aumentare la sicurezza per utilizzo 'medicale':
  - aggiungere protezione OverVelocity
  - aggiungere limitazione sul set point massimo di coppia/velocità  
  - rimuovere i comandi potenzialmente dannosi tipo EncSyncPulsePosition, Toggle, Parametri PID
  - inserimento parametri in eeprom e relativa protezione
  - aggiungere sonde di hall per fasatura senza movimento
  - aggiungere controllo di perdita delle sonde di hall/encoder runtime
  - aggiungere(?) su EMS il controllo di perdita del bus di comunicazione (Rete e CAN) 
  - aggiungere/abilitare il controllo della cadenza dei setpoint
  - aggiungere il controllo della ricezione dei messaggi di posizione/velocità (chiusura loop)
  - aggiungere un selftest iniziale (program memory, eeprom, offset correnti, ecc..) da fare ad ogni accensione
  - aggiungere un allarme sulla dinamica massima dei setpoint
  - aggiungere watchdog HW
  