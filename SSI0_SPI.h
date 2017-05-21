#define SSI0_clk 2
#define SSI0_fss 3
#define SSI0_rx 4
#define SSI0_tx 5
//SSICR0
#define SCR 8  //8-bit 8:15
#define SPH 7
#define SPO 6
#define FRF 4  //2-bit 4:5
#define DSS 0  //4-bit 0:3
//SSICR0
#define EOT 4 
#define SOD 3 
#define MS  2
#define SSE 1 
#define LBM 0
//SSISR
#define BSY 4
#define RFF 3
#define RNE 2
#define TNF 1
#define TFE 0


void ssi0_spi_init(void);
void ssi0_spi_TR(unsigned char);
//void Nokia5110_Init(void);
