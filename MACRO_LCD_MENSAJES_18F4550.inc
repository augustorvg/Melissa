    CBLOCK
    NUM_LETRAS
    CUENTA_LETRA
    APUNTADOR_LETRA
    LCD_ApuntaCaracter		; Indica la posici�n del car�cter a visualizar
    ENDC
    
_8MHZ	MACRO
    MOVLW   070H
    MOVWF   OSCCON
    ENDM    
    
_4MHZ	MACRO
    MOVLW   060H
    MOVWF   OSCCON
    ENDM    
    
LCD_Mensaje MACRO Mensaje
    LOCAL OTRA_LETRA    
    LOCAL NO_ES_ULTIMO    
    LOCAL FIN_MACRO    

    movwf   LCD_Temp
    MOVLW   UPPER Mensaje
    MOVWF   TBLPTRU
    MOVLW   HIGH Mensaje
    MOVWF   TBLPTRH
    MOVLW   LOW Mensaje
    MOVWF   TBLPTRL
    TBLRD*+
OTRA_LETRA
    MOVF    TABLAT,W
    MOVWF   LCD_Temp
    TSTFSZ  LCD_Temp
    GOTO    NO_ES_ULTIMO
    GOTO    FIN_MACRO
NO_ES_ULTIMO
    MOVF    LCD_Temp,W
    CALL    LCD_Caracter
    TBLRD*+
    BRA	    OTRA_LETRA
FIN_MACRO
    ENDM

LCD_MensajeMovimientoLinea1 MACRO Mensaje
    LOCAL OTRA_LETRA_EN_M 
    LOCAL OTRA_LETRA_EN_M_2
    LOCAL NO_ES_ULTIMO_EN_M    
    LOCAL FIN_MACRO_EN_M    
    LOCAL CUENTA_OTRA_LETRA  
    LOCAL CONTINUA_MACRO
    LOCAL NO_ES_LA_ULTIMA
    LOCAL CAMBIA_LETRA
    LOCAL OTRO_DEC
    LOCAL MENOS_DE_16
    LOCAL MAS_DE_16
    
;LEE LA POSICION DONDE EMPIEZA EL MENSAJE
    CLRF    NUM_LETRAS
    movwf   LCD_Temp
    MOVLW   UPPER Mensaje
    MOVWF   TBLPTRU
    MOVLW   HIGH Mensaje
    MOVWF   TBLPTRH
    MOVLW   LOW Mensaje
    MOVWF   TBLPTRL
    TBLRD*+
CUENTA_OTRA_LETRA
    MOVF    TABLAT,W
    BTFSS   STATUS,Z
    GOTO    NO_ES_LA_ULTIMA
    GOTO    CONTINUA_MACRO
NO_ES_LA_ULTIMA
    INCF    NUM_LETRAS
    TBLRD*+
    BRA	    CUENTA_OTRA_LETRA
;YA SABE CUANTAS LETRAS SON
CONTINUA_MACRO
    MOVLW   LCD_CaracteresPorLinea
    CPFSGT  NUM_LETRAS
    GOTO    MENOS_DE_16
    GOTO    MAS_DE_16
MENOS_DE_16
    MOVLW   .16
    MOVWF   NUM_LETRAS
MAS_DE_16
    MOVLW   LCD_CaracteresPorLinea-1
    SUBWF   NUM_LETRAS,F
    CLRF    APUNTADOR_LETRA

    MOVLW   UPPER Mensaje
    MOVWF   TBLPTRU
    MOVLW   HIGH Mensaje
    MOVWF   TBLPTRH
    MOVLW   LOW Mensaje
    MOVWF   TBLPTRL
    TBLRD*+    
 ;AQU� VA A IMPRIMIR LAS LETRAS HASTA QUE SEA 00H
OTRA_LETRA_EN_M
    MOVF    TABLAT,W
    MOVWF   LCD_Temp
    TSTFSZ  LCD_Temp
    GOTO    NO_ES_ULTIMO_EN_M
    GOTO    CAMBIA_LETRA    ;MODIFICA EL MENSAJE QUE VA A IMPRIMIR
    ;IMPRIME LA LETRA S� NO ES LA �LTIMA
NO_ES_ULTIMO_EN_M
    MOVF    LCD_Temp,W
    CALL    LCD_Caracter
    TBLRD*+
    BRA	    OTRA_LETRA_EN_M
CAMBIA_LETRA
    CALL    Retardo_200ms;  DEFINE EL VALOR DE LA VELOCIDAD DE DESPLAZAMIENTO
    CALL    Retardo_200ms;  DEFINE EL VALOR DE LA VELOCIDAD DE DESPLAZAMIENTO
    INCF    APUNTADOR_LETRA
    MOVF    APUNTADOR_LETRA,W
    CPFSEQ  NUM_LETRAS
    BRA	    OTRA_LETRA_EN_M_2
    GOTO    FIN_MACRO_EN_M  ;S� SE IMPRIMIO EL NUEMRO DE LETRAS EL MENSAJE TEMINA
OTRA_LETRA_EN_M_2
    CALL    LCD_Linea1
    MOVLW   UPPER Mensaje
    MOVWF   TBLPTRU
    MOVLW   HIGH Mensaje
    MOVWF   TBLPTRH
    MOVLW   LOW Mensaje
    MOVWF   TBLPTRL
    TBLRD*+    
    MOVFF   APUNTADOR_LETRA,CUENTA_LETRA
OTRO_DEC
    TBLRD*+    
    DECFSZ  CUENTA_LETRA
    GOTO    OTRO_DEC
    GOTO    OTRA_LETRA_EN_M
FIN_MACRO_EN_M    
    endm
    
LCD_MensajeMovimientoLinea2 MACRO Mensaje
    LOCAL OTRA_LETRA_EN_M 
    LOCAL OTRA_LETRA_EN_M_2
    LOCAL NO_ES_ULTIMO_EN_M    
    LOCAL FIN_MACRO_EN_M    
    LOCAL CUENTA_OTRA_LETRA  
    LOCAL CONTINUA_MACRO
    LOCAL NO_ES_LA_ULTIMA
    LOCAL CAMBIA_LETRA
    LOCAL OTRO_DEC
    LOCAL MENOS_DE_16
    LOCAL MAS_DE_16

;LEE LA POSICION DONDE EMPIEZA EL MENSAJE
    CLRF    NUM_LETRAS
    movwf   LCD_Temp
    MOVLW   UPPER Mensaje
    MOVWF   TBLPTRU
    MOVLW   HIGH Mensaje
    MOVWF   TBLPTRH
    MOVLW   LOW Mensaje
    MOVWF   TBLPTRL
    TBLRD*+
CUENTA_OTRA_LETRA
    MOVF    TABLAT,W
    BTFSS   STATUS,Z
    GOTO    NO_ES_LA_ULTIMA
    GOTO    CONTINUA_MACRO
NO_ES_LA_ULTIMA
    INCF    NUM_LETRAS
    TBLRD*+
    BRA	    CUENTA_OTRA_LETRA
;YA SABE CUANTAS LETRAS SON
CONTINUA_MACRO
    MOVLW   LCD_CaracteresPorLinea
    CPFSGT  NUM_LETRAS
    GOTO    MENOS_DE_16
    GOTO    MAS_DE_16
MENOS_DE_16
    MOVLW   .16
    MOVWF   NUM_LETRAS
MAS_DE_16
    MOVLW   LCD_CaracteresPorLinea-1
    SUBWF   NUM_LETRAS,F
    CLRF    APUNTADOR_LETRA

    MOVLW   UPPER Mensaje
    MOVWF   TBLPTRU
    MOVLW   HIGH Mensaje
    MOVWF   TBLPTRH
    MOVLW   LOW Mensaje
    MOVWF   TBLPTRL
    TBLRD*+    
 ;AQU� VA A IMPRIMIR LAS LETRAS HASTA QUE SEA 00H
OTRA_LETRA_EN_M
    MOVF    TABLAT,W
    MOVWF   LCD_Temp
    TSTFSZ  LCD_Temp
    GOTO    NO_ES_ULTIMO_EN_M
    GOTO    CAMBIA_LETRA    ;MODIFICA EL MENSAJE QUE VA A IMPRIMIR
    ;IMPRIME LA LETRA S� NO ES LA �LTIMA
NO_ES_ULTIMO_EN_M
    MOVF    LCD_Temp,W
    CALL    LCD_Caracter
    TBLRD*+
    BRA	    OTRA_LETRA_EN_M
CAMBIA_LETRA
    CALL    Retardo_200ms;  DEFINE EL VALOR DE LA VELOCIDAD DE DESPLAZAMIENTO
    CALL    Retardo_200ms;  DEFINE EL VALOR DE LA VELOCIDAD DE DESPLAZAMIENTO
    INCF    APUNTADOR_LETRA
    MOVF    APUNTADOR_LETRA,W
    CPFSEQ  NUM_LETRAS
    BRA	    OTRA_LETRA_EN_M_2
    GOTO    FIN_MACRO_EN_M  ;S� SE IMPRIMIO EL NUEMRO DE LETRAS EL MENSAJE TEMINA
OTRA_LETRA_EN_M_2
    CALL    LCD_Linea2
    MOVLW   UPPER Mensaje
    MOVWF   TBLPTRU
    MOVLW   HIGH Mensaje
    MOVWF   TBLPTRH
    MOVLW   LOW Mensaje
    MOVWF   TBLPTRL
    TBLRD*+    
    MOVFF   APUNTADOR_LETRA,CUENTA_LETRA
OTRO_DEC
    TBLRD*+    
    DECFSZ  CUENTA_LETRA
    GOTO    OTRO_DEC
    GOTO    OTRA_LETRA_EN_M
FIN_MACRO_EN_M    
    endm