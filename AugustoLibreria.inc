;Libreria bien chingona
;Si no funciona es culpa de los Rusos espias que no quieren que se sepa la verdad

;    #define LED_ON PORTD,0
    
    CBLOCK  0x60
    ENDC
    
;CONFIGURACION			;Configuracion habitual de nuestro sistema
   ; MOVLW   0x60		;
  ;  MOVWF   OSCCON		;OSCCON=0x60 oscilador interno a 4MHz
 ;   SETF    TRISB		;Entradas
;    CLRF    TRISC		;Salidas
    ;CLRF    TRISD		;Salidas
   ; BCF	    INTCON2,7		;Pull-up activadas
  ;  CALL    LCD_Inicializa	;Incicializa el LCD
 ;   BSF	    LED_ON		;Indicador lumínico de que nuestro circuito, al menos, funciona
;    RETURN			;Para que regrese al programa original (creo)
    
IMPRIME				;imprime valor numericos en cen,dec y unidades
    CALL    BIN_a_BCD
    MOVF    BCD_Centenas,W
    CALL    LCD_Nibble
    MOVF    BCD_Decenas,W
    CALL    LCD_Nibble
    MOVF    BCD_Unidades,W
    CALL    LCD_Nibble
    RETURN


