// Blue Nokia 5110
// ---------------
// Signal        (Nokia 5110) LaunchPad pin
// Reset         (RST, pin 1) connected to PA7
// SSI0Fss       (CE,  pin 2) connected to PA3
// Data/Command  (DC,  pin 3) connected to PA6
// SSI0Tx        (Din, pin 4) connected to PA5
// SSI0Clk       (Clk, pin 5) connected to PA2
// 3.3V          (Vcc, pin 6) power
// back light    (BL,  pin 7) not connected, consists of 4 white LEDs which draw ~80mA total
// Ground        (Gnd, pin 8) ground

#define dc  6
#define rst 7
#define contrast 0xbf 

void lcd_init(void);
void lcd_cmd_TR(unsigned char);
void lcd_data_TR(unsigned char);
void lcd_clear(void);
void lcd_SetCursor(int,int);
void lcd_Char_TR(char);
void lcd_Str_TR(char *);
void dis(char[],int);
void init_board(void);
void clear_board(void);
void cell(int,int,char);

