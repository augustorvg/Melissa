    
    CBLOCK
    TEMPORAL
    ENDC
 
MOSTRAR_VALOR
    CALL    BIN_a_BCD
    MOVF    BCD_Centenas,W
    CALL    LCD_Nibble
    MOVF    BCD_Decenas,W
    CALL    LCD_Nibble
    MOVF    BCD_Unidades,W
    CALL    LCD_Nibble
    RETURN



