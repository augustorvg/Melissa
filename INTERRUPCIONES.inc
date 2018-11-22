;Subrutina para guardar y recuperar registros al entrar a una interrupción
;se debe utilizar junto con la subrutina de Retardos.INC

	CBLOCK
	Temp_ContA
	Temp_ContB
	Temp_ContC
	GUARDA_W
	GUARDA_STATUS
	BSR_TEMP
	ENDC

Guardar_Registros
    MOVWF   GUARDA_W
    MOVFF   STATUS,GUARDA_STATUS    ;Cambia STATUS a W sin alterar el registro STATUS
    MOVFF   BSR,BSR_TEMP
    MOVFF   R_ContA,Temp_ContA	    ; CONTADORES PARA LOS RETARDOS.
    MOVFF   R_ContB,Temp_ContB	    ; CONTADORES PARA LOS RETARDOS.
    MOVFF   R_ContC,Temp_ContC	    ; CONTADORES PARA LOS RETARDOS.
    RETURN


Recuperar_Registros
    MOVFF   Temp_ContA,R_ContA	    ; CONTADORES PARA LOS RETARDOS.
    MOVFF   Temp_ContB,R_ContB	    ; CONTADORES PARA LOS RETARDOS.
    MOVFF   Temp_ContC,R_ContC	    ; CONTADORES PARA LOS RETARDOS.
    MOVFF   BSR_TEMP,BSR
    MOVF    GUARDA_W,W
    MOVFF   GUARDA_STATUS,STATUS
    RETURN
