// format
//
//Address Dump Label Mnemonic Parameter Comment Margin


//
// basic types
//
//  byte, 8-bit value
//  word, 16-bit value at an even address
//  code, executable code
//
//  symbols are actually the addresses of the variables, so "x" refers to the location at which
//  the value of x is stored, therefore an "@" is used instead of an "=" to assign the address
//  to the symbol
//

//
// I/O register names
//
ZERO         byte @ register 0;
LSO_DATA     byte @ register 2;
BIDIR_IO     byte @ register 3;
INT_MASK     byte @ register 8;
INT_PENDING  byte @ register 9;
IO_STATUS    byte @ register 10;
HSI_MASK     byte @ register 12;

AD_RESULT_LO byte @ src register 4;
AD_RESULT_HI byte @ src register 5;
HSI_SAMPLE   byte @ src register 11;
HSI_STATUS   byte @ src register 13;

AD_COMMAND   byte @ dst register 4;
WATCHDOG     byte @ dst register 5;
HSO_COMMAND  byte @ dst register 13;

ZERO         word @ register 0;
IO_TIMER     word @ register 6;
SP           word @ register 16;

HSI_TIME     word @ src register 14;

HSO_TIME     word @ dst register 14;

//
// application register names
//
IO_TIMER_EX  word @ register 18;
HSO_4_TIME   word @ register 40;
PAGE_ONE     word @ register 38;
AD_INDEX     word @ register 174;
JT1_INDEX    word @ register 146;
JT2_INDEX    byte @ register 119;

//assume PAGE_ONE = 0x0180;

// linefeed @ 0x2345;

//
// reserved symbols to set the limits of the disassembled region
//
ROM_START @ 0x2000;
ROM_LIMIT @ 0xa000;

//
// RAM constants
//
RAM_START @ 0x0100;
RAM_LIMIT @ 0x0900;


//fu function @ 0x2000 to 0x2100;

// func1 func "" @ 0x1234;

//
// reset entry point
//
reset code "

;***********************************************************************************************
;
; Reset entry point.
;
;  Following a reset, execution commences at the reset entry point.  The address of the reset
;  entry point varies and depends on the processor model.
;
;  Processor  Address
;  ---------  -------
;   MCS-96    0x2080
;   i8061     0x2000
;   i8065     0x2000
;
;***********************************************************************************************
" @ 0x2000;

//
// interrupt vector table
//
vector_table [8] * code "

;***********************************************************************************************
;
; i8061 interrupt vectors.  In address order.
;
;  Priority           Interrupt Source
;  --------    -------------------------------
;  Lowest      Hign-Speed Output #2
;     |        I/O Timer Overflow
;     |        A/D Conversion Done
;     |        Hign-Speed Input Data Available
;     |        External Input
;     |        Hign-Speed Output #1
;     |        Hign-Speed Input #1
;  Highest     Hign-Speed Input #0
;
;***********************************************************************************************
" @ 0x2010;

isr_hso_2           code "

;***********************************************************************************************
;
; High Speed Output #2
;
;***********************************************************************************************
" @ * vector_table[0];
isr_io_timer        code "

;***********************************************************************************************
;
; I/O Timer Overflow
;
;***********************************************************************************************
" @ * vector_table[1];
isr_ad_complete     code "

;***********************************************************************************************
;
; A/D Conversion Complete
;
;ad_commands:        dcw 0x0003,0x0004,0x0007,0x0008
;dcw 0x0009,0x000a,0x000b,0x000c
;dcw 0xffff
;***********************************************************************************************
" @ * vector_table[2];
isr_hsi_dav    code "

;***********************************************************************************************
;
; High Speed Input Data Available
;
;***********************************************************************************************
" @ * vector_table[3];
isr_ext_irq         code "

;***********************************************************************************************
;
; External Input
;
;***********************************************************************************************
" @ * vector_table[4];
isr_hso_1           code "

;***********************************************************************************************
;
; High Speed Output #1
;
;***********************************************************************************************
" @ * vector_table[5];
isr_hsi_1           code "

;***********************************************************************************************
;
; High Speed Input #1
;
;***********************************************************************************************
" @ * vector_table[6];
isr_hsi_0           code "

;***********************************************************************************************
;
; High Speed Input #0
;
;***********************************************************************************************
" @ * vector_table[7];


"

" @ 0x2004;

"

" @ 0x200e;


//
//
//
initialize code "

;
; Initialize stack pointer.
;
" @ 0x2020;

//
//
//
init_ram code "

;
; Initialize RAM.
;
" @ 0x202a;

//
zero_init code "

;
; Zero registers and RAM between the SFR registers and the bottom of the stack (0x0012 through
; 0x021B).  Skip the block of registers from r48 through r67.
;
" @ 0x202c;
zero_loop code "

" @ 0x2032;
zero_skip code @ 0x203f;

//
data_init code "

;
; Initialize selected data items in the first 512 bytes of memory (0x0000 through 0x01FF).  The
; initialization data table is made up of byte pairs.  The first byte is the LSB of the address
; and the second byte is or'ed into the location.
;
" @ 0x2044;
data_page_loop code "

" @ 0x2048;
data_loop code @ 0x2056;

data_page_end code @ 0x2069;

//
page_zero_init [] word "

" @ 0x75be;
byte @ page_zero_init + 4;
word @ 0x7614;
byte @ 0x7616;

page_one_init [] word "

" @ 0x761e;
byte @ page_one_init + 4;
word @ 0x7664;
byte @ 0x7666;

continue_init code "

" @ 0x2070;

//
// main loop
//
main_loop code "

;***********************************************************************************************
;
; Main loop.
;
;***********************************************************************************************
" @ 0x211c;

code "

" @ 0x2210;

r227_action_0 code @ 0x4412;
r227_action_1 code @ 0x218f;
r227_action_2a code @ 0x4861;
r227_action_2b code @ 0x48e5;
r227_action_2c code @ 0x48ef;
r227_action_3 code @ 0x629e;
r227_action_4 code @ 0x6421;
r227_action_5 code @ 0x6421;
r227_action_6 code @ 0x6426;
r227_action_7 code @ 0x41fa;

jt1_dispatch code "

;
; Jump indirect through jump table 1.
;
" @ 0x21a2;

//
//
//
byte "

; word align jump table
" @ 0x21a7;

//
//
//
JT1 [43] * code "

;
; Jump table 1.
;
" @ 0x21a8;

task100 code "

;***********************************************************************************************
;
; Task 100.
;
;***********************************************************************************************
" @ * JT1[0];
task101 code "

;***********************************************************************************************
;
; Task 101.
;
;***********************************************************************************************
" @ * JT1[1];
task102 code "

;***********************************************************************************************
;
; Task 102.
;
;***********************************************************************************************
" @ * JT1[2];
task103 code "

;***********************************************************************************************
;
; Task 103.
;
;***********************************************************************************************
" @ * JT1[3];
task104 code "

;***********************************************************************************************
;
; Task 104.
;
;***********************************************************************************************
" @ * JT1[4];
task105 code "

;***********************************************************************************************
;
; Task 105.
;
;***********************************************************************************************
" @ * JT1[5];
task106 code "

;***********************************************************************************************
;
; Task 106.
;
;***********************************************************************************************
" @ * JT1[6];
task107 code "

;***********************************************************************************************
;
; Task 107.
;
;***********************************************************************************************
" @ * JT1[7];
task108 code "

;***********************************************************************************************
;
; Task 108.
;
;***********************************************************************************************
" @ * JT1[8];
task109 code @ * JT1[9];
task110 code @ * JT1[10];
task111 code @ * JT1[11];
task112 code @ * JT1[12];
task113 code @ * JT1[13];
task114 code @ * JT1[14];
task115 code @ * JT1[15];
task116 code @ * JT1[16];
task117 code @ * JT1[17];
task118 code @ * JT1[18];
task119 code @ * JT1[19];
task120 code @ * JT1[20];
task121 code @ * JT1[21];
task122 code @ * JT1[22];
task123 code @ * JT1[23];
task124 code @ * JT1[24];
task125 code @ * JT1[25];
task126 code @ * JT1[26];
task127 code @ * JT1[27];
task128 code @ * JT1[28];
task129 code @ * JT1[29];
task130 code @ * JT1[30];
task131 code @ * JT1[31];
task132 code @ * JT1[32];
task133 code @ * JT1[33];
task134 code @ * JT1[34];
task135 code @ * JT1[35];
task136 code "

;***********************************************************************************************
;
; Task 136.
;
;***********************************************************************************************
" @ * JT1[36];
task137 code @ * JT1[37];
task138 code @ * JT1[38];
task139 code @ * JT1[39];
task140 code @ * JT1[40];
task141 code @ * JT1[41];
task142 code @ * JT1[42];


"

; Start A/D converter aquisition sequence.
" @ 0x2216;

"

" @ 0x221d;

//
// A/D command sequence
//
ad_commands [9] word "

;
; A/D converter command byte sequence.  Command bytes are stored on word boundaries so a common
; index can be used for the command and result.
;
" @ 0x21fe;

AD3_RESULT  word @ register 128;
VAT_RESULT  word @ register 130;
TPS_RESULT  word @ register 132;
ECT_RESULT  word @ register 134;
ACT_RESULT  word @ register 136;
AD10_RESULT word @ register 138;
AD11_RESULT word @ register 140;
VAF_RESULT word @ register 142;

vat_high_limit0  word @ 0x36ec;
vat_low_limit0   word @ 0x36ee;
vat_high_limit1  word @ 0x370e;
vat_low_limit1   word @ 0x3710;
vat_high_limit2  word @ 0x3712;
vat_low_limit2   word @ 0x3714;

tps_high_limit0  word @ 0x36dc;
tps_low_limit0   word @ 0x36de;
tps_low_limit1   word @ 0x36fa;
tps_high_limit1  word @ 0x36fc;
tps_low_limit2   word @ 0x36fe;
tps_high_limit2  word @ 0x3700;
tps_high_limit3  word @ 0x3702;
tps_low_limit3   word @ 0x3704;

ect_low_limit0   word @ 0x2f92;
ect_low_limit1   word @ 0x2f94;
ect_low_limit2   word @ 0x2fd2;
ect_high_limit3  word @ 0x36d6;
ect_low_limit3   word @ 0x36d8;
ect_high_limit4  word @ 0x36f0;
ect_low_limit4   word @ 0x36f2;
ect_high_limit5  word @ 0x36f4;
ect_low_limit5   word @ 0x36f6;

act_high_limit0  word @ 0x36d2;
act_low_limit0   word @ 0x36d4;
act_high_limit1  word @ 0x36e0;
act_low_limit1   word @ 0x36e2;
act_high_limit2  word @ 0x36e4;
act_low_limit2   word @ 0x36e6;

vaf_high_limit0 word @ 0x2a68;
vaf_low_limit0  word @ 0x2a6a;
vaf_high_limit1 word @ 0x2fb2;
vaf_high_limit2 word @ 0x36e8;
vaf_low_limit2  word @ 0x36ea;
vaf_low_limit3  word @ 0x3706;
vaf_high_limit3 word @ 0x3708;
vaf_low_limit4  word @ 0x370a;
vaf_high_limit4 word @ 0x370c;


//linefeed @ +0x2345;

//
//
//
byte "

; align
" @ 0x23c4;


r233_dispatch code "

;***********************************************************************************************
;
; r233 Action Dispatcher.
;
;***********************************************************************************************
" @ 0x39c6;


// 000039c6  32 e9 02 28 24           r233_dispatch:      scall.bs        R233, 2, r233_action_2


r233_nd2 code @ r233_dispatch + 5;
r233_nd0 code @ r233_dispatch + 10;
r233_nd4 code @ r233_dispatch + 15;
r233_nd1 code @ r233_dispatch + 20;
r233_nd5 code @ r233_dispatch + 25;
r233_nd7 code @ r233_dispatch + 30;
r233_nd3 code @ r233_dispatch + 35;
r233_nd6 code @ r233_dispatch + 40;

r233_action_0 code "

;***********************************************************************************************
;
; r233 Bit 0 Action.
;
;***********************************************************************************************
" @ 0x3b23;
r233_action_1 code "

;***********************************************************************************************
;
; r233 Bit 1 Action.
;
;***********************************************************************************************
" @ 0x3cc8;
r233_action_2 code "

;***********************************************************************************************
;
; r233 Bit 2 Action.
;
;***********************************************************************************************
" @ 0x39ef;
r233_action_3 code "

;***********************************************************************************************
;
; r233 Bit 3 Action.
;
;***********************************************************************************************
" @ 0x3d67;
r233_action_4 code "

;***********************************************************************************************
;
; r233 Bit 4 Action.
;
;***********************************************************************************************
" @ 0x3c48;
r233_action_5 code "

;***********************************************************************************************
;
; r233 Bit 5 Action.
;
;***********************************************************************************************
" @ 0x3cf9;
r233_action_6 code "

;***********************************************************************************************
;
; r233 Bit 6 Action.
;
;***********************************************************************************************
" @ 0x3de1;
r233_action_7 code "

;***********************************************************************************************
;
; r233 Bit 7 Action.
;
;***********************************************************************************************
" @ 0x3d53;


timer_func code "

;***********************************************************************************************
;
; Timer function.
;
;***********************************************************************************************
" @ 0x3e23;


timer_func2 code "

;***********************************************************************************************
;
; Timer function 2.
;
;***********************************************************************************************
" @ 0x3e7d;


"

;***********************************************************************************************
;
; BAP transfer function
;
;***********************************************************************************************
" @ 0x2fd8;


"

;***********************************************************************************************
;
; ECT/ACT transfer function
;
;***********************************************************************************************
" @ 0x2fec;


"

;***********************************************************************************************
;
; Air Mass Transfer function
;  Superchips mods 3036 = ff00
;
;***********************************************************************************************
" @ 0x3010;


vaf_xfer_u16_u16 word "

;***********************************************************************************************
;
; Vane Air Flow (VAF) transfer function.
;
;***********************************************************************************************
" @ 0x3038;


vat_xfer_u16_s16 word "

;***********************************************************************************************
;
; Vane Air Temperature (VAT) transfer function.
;
;***********************************************************************************************
" @ 0x309c;


tps_xfer_u16_u16 word "

;***********************************************************************************************
;
; Throttle Position Sensor (TPS) transfer function.
;
;***********************************************************************************************
" @ 0x30b8;


vaf_dead [] [11] byte "

;***********************************************************************************************
;
; Mass Air Estimate (VAF dead)
;
;***********************************************************************************************
" @ 0x30d4;


"

;***********************************************************************************************


;***********************************************************************************************
;
;
;
;***********************************************************************************************
" @ 0x5751;


"

;***********************************************************************************************


;***********************************************************************************************
;
;
;
;***********************************************************************************************
" @ 0x584b;


"

;***********************************************************************************************


;***********************************************************************************************
;
;
;
;***********************************************************************************************
" @ 0x587f;


ex_timer_en code "

" @ 0x42ef;

ex_timer_dis code "

" @ 0x42d8;

ex_timer code "

" @ 0x4dbd;

"

" @ 0x4ddc;

"

" @ 0x674d;

"

" @ 0x6773;

"

" @ 0x67b5;


////////////////////////////////////////////////////////////////////////////////////////////////
//
// 8-bit (byte) table lookup and linear interpolate
//
////////////////////////////////////////////////////////////////////////////////////////////////

// unsigned input, unsigned output
xlate8_uX_uY code @ 0x58a6;

// unsigned input, signed output
xlate8_uX_sY code @ 0x58a3;

// signed input, unsigned output
xlate8_sX_uY code @ 0x589b;

// signed input, signed output
xlate8_sX_sY code @ 0x58a0;

// local labels
x8_0 code @ 0x58B1;
x8_1 code @ 0x58B3;
x8_2 code "

" @ 0x58B9;
x8_3 code @ 0x58D2;
x8_4 code @ 0x58D4;
x8_5 code @ 0x58D9;
x8_6 code @ 0x58E4;

"

;***********************************************************************************************


;***********************************************************************************************
;
; Translate the 8-bit integer input value using a function represented by a table of points on a
; two-dimensional graph.  The input value of the function is the X dimension and the output
; value is the Y.  Translation occurs in two steps:
;
; Step 1) Locate a pair of points whose X values bracket the input value.  This step is
;         accomplished by a linear search of the table.
;
; Step 2) Perform a linear interpolation between the two points to find the Y value that
;         corresponds to the X input value.
;
; Points in the table are arranged in decreasing order of X.  The X value of the first point in
; the table must be the maximum value that can be represented by the data type of X, the value
; of the last point must be the minimum.
;
; Four variants of this API are provided to handle the four possible combinations of signed and
; unsigned, X and Y values.
;
; 8-bit entry points:
;
;  xlate8_uX_uY - unsigned input, unsigned output
;  xlate8_uX_sY - unsigned input, signed output
;  xlate8_sX_uY - signed input, unsigned output
;  xlate8_sX_sY - signed input, signed output
;
; Required first and last X values for all tables.
;
;      First             Last         X Data Type
; -------------------------------------------------
;  255   (0xFF)     0     (0x00)    8-bit unsigned
;  127   (0x7F)    -128   (0x80)    8-bit signed
;
; inputs:
;
;  r51:r50      table base address
;      r52      input value
;
; outputs:
;
;      r56      return value
;
; modifies:  r51:r50, r52, r54, r57:r56, r224[1:0]
;
;***********************************************************************************************

; Entry point for signed X and unsigned Y.
" @ xlate8_sX_uY;

"

; Entry point for signed X and signed Y.
" @ xlate8_sX_sY;

"

; Entry point for unsigned X and signed Y.
" @ xlate8_uX_sY;

"

; Entry point for unsigned X and unsigned Y.
" @ xlate8_uX_uY;


////////////////////////////////////////////////////////////////////////////////////////////////
//
// 16-bit (word) table lookup and linear interpolate
//
////////////////////////////////////////////////////////////////////////////////////////////////

// unsigned input, unsigned output
xlate16_uX_uY code @ 0x58fb;

// unsigned input, signed output
xlate16_uX_sY code @ 0x58f8;

// signed input, unsigned output
xlate16_sX_uY code @ 0x58f0;

// signed input, signed output
xlate16_sX_sY code @ 0x58f5;

// local labels
x16_0 code @ 0x5906;
x16_1 code @ 0x5908;
x16_2 code "

" @ 0x590E;
x16_3 code @ 0x5927;
x16_4 code @ 0x5929;
x16_5 code @ 0x592E;
x16_6 code @ 0x5939;

"

;***********************************************************************************************


;***********************************************************************************************
;
; Translate the 16-bit integer input value using a function represented by a table of points on
; a two-dimensional graph.  The input value of the function is the X dimension and the output
; value is the Y.  Translation occurs in two steps:
;
; Step 1) Locate a pair of points whose X values bracket the input value.  This step is
;         accomplished by a linear search of the table.
;
; Step 2) Perform a linear interpolation between the two points to find the Y value that
;         corresponds to the X input value.
;
; Points in the table are arranged in decreasing order of X.  The X value of the first point in
; the table must be the maximum value that can be represented by the data type of X, the value
; of the last point must be the minimum.
;
; Four variants of this API are provided to handle the four possible combinations of signed and
; unsigned, X and Y values.
;
; 16-bit entry points:
;
;  xlate16_uX_uY - unsigned input, unsigned output
;  xlate16_uX_sY - unsigned input, signed output
;  xlate16_sX_uY - signed input, unsigned output
;  xlate16_sX_sY - signed input, signed output
;
; Required first and last X values for all tables.
;
;      First             Last         X Data Type
; -------------------------------------------------
;  65535 (0xFFFF)   0     (0x0000)  16-bit unsigned
;  32767 (0x7FFF)  -32768 (0x8000)  16-bit signed
;
; inputs:
;
;  r51:r50      table base address
;  r53:r52      input value
;
; outputs:
;
;  r57:r56      return value
;
; modifies:  r51:r50, r53:r52, r55:r54, r59:r58:r57:r56, r224[1:0]
;
;***********************************************************************************************

; Entry point for signed X and unsigned Y.
" @ xlate16_sX_uY;

"

; Entry point for signed X and signed Y.
" @ xlate16_sX_sY;

"

; Entry point for unsigned X and signed Y.
" @ xlate16_uX_sY;

"

; Entry point for unsigned X and unsigned Y.
" @ xlate16_uX_uY;


////////////////////////////////////////////////////////////////////////////////////////////////
//
// table lookup and bilinear interpolate
//
////////////////////////////////////////////////////////////////////////////////////////////////

//
xlate_2D code @ 0x5943;

// local labels
b_0 code @ 0x594e;
b_1 code @ 0x5972;

"

;***********************************************************************************************


;***********************************************************************************************
;
; Use the two input values to select a point in the grid.  Load
;
; Translate the 16-bit integer input value using a function represented by a table of points on
; a two-dimensional graph.  The input value of the function is the X dimension and the output
; value is the Y.  Translation occurs in two steps:
;
;
;  r49:r48 = X input value, 0x0000 to 0xnn00 where nn+1 is the number of columns in the table
;  r51:r50 = Y input value, 0x0000 to 0xnn00 where nn+1 is the number of rows in the table
;  r53:r52 = number of columns in table
;  r57:r56 = table base address
;
;***********************************************************************************************
" @ xlate_2D;


"

;***********************************************************************************************


;***********************************************************************************************
;
;
;
;***********************************************************************************************
" @ 0x5985;


"

;***********************************************************************************************


;***********************************************************************************************
;
;
;
;***********************************************************************************************
" @ 0x59bb;


"

;***********************************************************************************************


;***********************************************************************************************
;
;
;
;***********************************************************************************************
" @ 0x5ac9;


"

;***********************************************************************************************


;***********************************************************************************************
;
; no umps outsid of function 00006b5d to 00006c0d
;
;***********************************************************************************************
" @ 0x6b5d;

"

;***********************************************************************************************

" @ 0x6c0d;

jt2_dispatch code "

;
; Jump indirect through jump table 2.
;
" @ 0x47ca;

//
//
//
byte "

; word align jump table
" @ 0x47d5;

//
//
//
JT2 [18] * code "

;
; Jump table 2.
;
" @ 0x47d6;

task200 code @ * JT2[0];
task201 code @ * JT2[1];
task202 code @ * JT2[2];
task203 code @ * JT2[3];
task204 code @ * JT2[4];
task205 code @ * JT2[5];
task206 code @ * JT2[6];
task207 code @ * JT2[7];
task208 code @ * JT2[8];
task209 code @ * JT2[9];
task210 code @ * JT2[10];
task211 code @ * JT2[11];
task212 code @ * JT2[12];
task213 code @ * JT2[13];
task214 code @ * JT2[14];
task215 code @ * JT2[15];
task216 code @ * JT2[16];
task217 code @ * JT2[17];


r229_action_6 code "

;***********************************************************************************************
;
;
;
;***********************************************************************************************
" @ 0x5678;


jt3_dispatch code "

;
; Jump indirect through jump table 3.
;
" @ 0x6742;

jt3_0_dispatch code "

;
; Jump indirect through jump table 3, entry 0.
;
" @ 0x6b56;

//
//
//
byte "

; word align jump table
" @ 0x67ff;

//
//
//
JT3 [12] * code "

;
; Jump table 3.
;
" @ 0x6800;

task300 code "

;***********************************************************************************************
;
; Task 300.
;
;***********************************************************************************************
" @ * JT3[0];
task301 code "

;***********************************************************************************************
;
; Task 301.
;
;***********************************************************************************************
" @ * JT3[1];
task302 code "

;***********************************************************************************************
;
; Task 302.
;
;***********************************************************************************************
" @ * JT3[2];
task303 code "

;***********************************************************************************************
;
; Task 303.
;
;***********************************************************************************************
" @ * JT3[3];
task304 code "

;***********************************************************************************************
;
; Task 304.
;
;***********************************************************************************************
" @ * JT3[4];
task305 code "

;***********************************************************************************************
;
; Task 305.
;
;***********************************************************************************************
" @ * JT3[5];
task306 code "

;***********************************************************************************************
;
; Task 306.
;
;***********************************************************************************************
" @ * JT3[6];
task307 code "

;***********************************************************************************************
;
; Task 307.
;
;***********************************************************************************************
" @ * JT3[7];
task308 code "

;***********************************************************************************************
;
; Task 308.
;
;***********************************************************************************************
" @ * JT3[8];
task309 code "

;***********************************************************************************************
;
; Task 309.
;
;***********************************************************************************************
" @ * JT3[9];
task310 code "

;***********************************************************************************************
;
; Task 310.
;
;***********************************************************************************************
" @ * JT3[10];
task311 code "

;***********************************************************************************************
;
; Task 311.
;
;***********************************************************************************************
" @ * JT3[11];


jt4_dispatch code "

;
; Jump indirect through jump table 4.
;
" @ 0x676e;

//
//
//
JT4 [37] * code @ 0x6c52;

task400 code @ * JT4[0];
task401 code @ * JT4[1];
task402 code @ * JT4[2];
task403 code @ * JT4[3];
task404 code @ * JT4[4];
task405 code @ * JT4[5];
task406 code @ * JT4[6];
task407 code @ * JT4[7];
task408 code @ * JT4[8];
task409 code @ * JT4[9];
task410 code @ * JT4[10];
task411 code @ * JT4[11];
task412 code @ * JT4[12];
task413 code @ * JT4[13];
task414 code @ * JT4[14];
task415 code @ * JT4[15];
task416 code @ * JT4[16];
task417 code @ * JT4[17];
task418 code @ * JT4[18];
task419 code @ * JT4[19];
task420 code @ * JT4[20];
task421 code @ * JT4[21];
task422 code @ * JT4[22];
task423 code @ * JT4[23];
task424 code @ * JT4[24];
task425 code @ * JT4[25];
task426 code @ * JT4[26];
task427 code @ * JT4[27];
task428 code @ * JT4[28];
task429 code @ * JT4[29];
task430 code @ * JT4[30];
task431 code @ * JT4[31];
task432 code @ * JT4[32];
task433 code @ * JT4[33];
task434 code @ * JT4[34];
task435 code @ * JT4[35];
task436 code @ * JT4[36];


jt5_dispatch code "

;
; Jump indirect through jump table 5.
;
" @ 0x6fc8;

"

" @ 0x6fd1;

//
//
//
JT5 [7] * code @ 0x7050;

task500 code @ * JT5[0];
task501 code @ * JT5[1];
task502 code @ * JT5[2];
task503 code @ * JT5[3];
task504 code @ * JT5[4];
task505 code @ * JT5[5];
task506 code @ * JT5[6];

DT5 [7] byte @ 0x705e;


jt6_dispatch code "

;
; Jump indirect through jump table 6.
;
" @ 0x67aa;

//
//
//
JT6 [51] * code @ 0x70c6;

task600 code @ * JT6[0];
task601 code @ * JT6[1];
task602 code @ * JT6[2];
task603 code @ * JT6[3];
task604 code @ * JT6[4];
task605 code @ * JT6[5];
task606 code @ * JT6[6];
task607 code @ * JT6[7];
task608 code @ * JT6[8];
task609 code @ * JT6[9];
task610 code @ * JT6[10];
task611 code @ * JT6[11];
task612 code @ * JT6[12];
task613 code @ * JT6[13];
task614 code @ * JT6[14];
task615 code @ * JT6[15];
task616 code @ * JT6[16];
task617 code @ * JT6[17];
task618 code @ * JT6[18];
task619 code @ * JT6[19];
task620 code @ * JT6[20];
task621 code @ * JT6[21];
task622 code @ * JT6[22];
task623 code @ * JT6[23];
task624 code @ * JT6[24];
task625 code @ * JT6[25];
task626 code @ * JT6[26];
task627 code @ * JT6[27];
task628 code @ * JT6[28];
task629 code @ * JT6[29];
task630 code @ * JT6[30];
task631 code @ * JT6[31];
task632 code @ * JT6[32];
task633 code @ * JT6[33];
task634 code @ * JT6[34];
task635 code @ * JT6[35];
task636 code @ * JT6[36];
task637 code @ * JT6[37];
task638 code @ * JT6[38];
task639 code @ * JT6[39];
task640 code @ * JT6[40];
task641 code @ * JT6[41];
task642 code @ * JT6[42];
task643 code @ * JT6[43];
task644 code @ * JT6[44];
task645 code @ * JT6[45];
task646 code @ * JT6[46];
task647 code @ * JT6[47];
task648 code @ * JT6[48];
task649 code @ * JT6[49];
task650 code @ * JT6[50];


"

;***********************************************************************************************
;* Group of parameters
;***********************************************************************************************
" @ 0x2400;


"

;***********************************************************************************************
;* RPM to Mass Air flow comparison function
;*  aka WOT MAF clip vs RPM
;***********************************************************************************************
" @ 0x240e;


"

;***********************************************************************************************
;* HEGO ECT transfer function data?
;*  aka time for N-D vs ECT
;***********************************************************************************************
" @ 0x242a;


"

;***********************************************************************************************
;* Group of parameters
;***********************************************************************************************
" @ 0x2435;


"

;***********************************************************************************************
;* failure mode MAF vs RPM
;***********************************************************************************************
" @ 0x2446;


"

;***********************************************************************************************
;* Group of parameters?
;***********************************************************************************************
" @ 0x2462;


"

;***********************************************************************************************
;* Open Loop RPM
;*  max load (lb of air per cylinder) for closed loop vs RPM
;*  boost starts about 0.001 #/cylinder (0x4194)
;***********************************************************************************************
" @ 0x2492;


"

;***********************************************************************************************
;* Underspeed RPM vs ECT
;***********************************************************************************************
" @ 0x24b6;


"

;***********************************************************************************************
;* Group of parameters?
;***********************************************************************************************
" @ 0x24ce;


"

;***********************************************************************************************
;* crank fuel reduction vs time
;***********************************************************************************************
" @ 0x24f0;


"

;***********************************************************************************************
;* Cranking fuel pulsewidth vs ECT
;*  EGR function?
;***********************************************************************************************
" @ 0x24fc;


"

;***********************************************************************************************
;* WOT pulsewidth multiplier (WOT enrichment vs RPM)
;***********************************************************************************************
" @ 0x252c;


"

;***********************************************************************************************
;* cold VAT fuel multiplier
;***********************************************************************************************
" @ 0x2554;


"

;***********************************************************************************************
;* Max Load vs RPM
;***********************************************************************************************
" @ 0x2560;


low_temp [] [8] byte "

;***********************************************************************************************
;* Low temp (ECT) fuel
;***********************************************************************************************
" @ 0x2580;


start_fuel [] [8] byte "

;***********************************************************************************************
;* Just Started fuel enrichment
;***********************************************************************************************
" @ 0x25b0;


base_fuel [] [11] byte "

;***********************************************************************************************
;* Base Fuel map
;*  0x80 = '1'
;***********************************************************************************************
" @ 0x25e0;


"

;***********************************************************************************************
;* Group of parameters
;***********************************************************************************************
" @ 0x269c;


acc_enrich [] [8] byte "

;***********************************************************************************************
;* Acceleration Enrichment
;***********************************************************************************************
" @ 0x26b3;


acc_vapor [] [8] byte "

;***********************************************************************************************
;* Acceleration fuel vapor time
;***********************************************************************************************
" @ 0x26e3;


dec_vapor [] [8] byte "

;***********************************************************************************************
;* De-acceleration fuel vapor time
;***********************************************************************************************
" @ 0x2713;


"

;***********************************************************************************************
;* Group of parameters
;***********************************************************************************************
" @ 0x2744;


"

;***********************************************************************************************
;* Cold ECT idle speed adder
;***********************************************************************************************
" @ 0x2752;


"

;***********************************************************************************************
;* idle speed adder vs ECT at start
;***********************************************************************************************
" @ 0x2772;


"

;***********************************************************************************************
;* idle speed adder vs time in neutral
;***********************************************************************************************
" @ 0x2796;


"

;***********************************************************************************************
;* more parameters
;***********************************************************************************************
" @ 0x27a4;


"

;***********************************************************************************************
;* IAC (air bypass) duty cycle vs flow setpoint
;***********************************************************************************************
" @ 0x27d4;


"

;***********************************************************************************************
;* ISC (drive) function?
;*  aka Decel ISC air flow
;***********************************************************************************************
" @ 0x27fc;


"

;***********************************************************************************************
;* ISC (idle) function
;*  aka Decel air mass vs RPM (neutral)
;***********************************************************************************************
" @ 0x2818;


"

;***********************************************************************************************
;* idle air mass vs RPM setpoint (drive)
;***********************************************************************************************
" @ 0x2834;


"

;***********************************************************************************************
;* Idle air mass vs RPM setpoint (neutral)
;***********************************************************************************************
" @ 0x2850;


"

;***********************************************************************************************
;* Desired air mass multiplier vs ECT
;*  aka ISC multiplier cold ECT
;***********************************************************************************************
" @ 0x286c;


"

;***********************************************************************************************
;* Crank air duty cycle vs ECT
;***********************************************************************************************
" @ 0x2888;


"

;***********************************************************************************************
;* Air flow multiplier vs VAT
;***********************************************************************************************
" @ 0x2894;


"

;***********************************************************************************************
;* Constants for JT1[18] and JT1[19]
;***********************************************************************************************
" @ 0x28b0;


"

;***********************************************************************************************
;* Load to row #
;***********************************************************************************************
" @ 0x28d0;


"

;***********************************************************************************************
;* throttle to column #
;***********************************************************************************************
" @ 0x28ec;


"

;***********************************************************************************************
;* bypass clutch slip multiplier
;***********************************************************************************************
" @ 0x2908;


min_speed_3rd [] [7] byte "

;***********************************************************************************************
;* Min speed to enable start lock in 3rd
;***********************************************************************************************
" @ 0x2920;


stay_speed_3rd [] [7] byte "

;***********************************************************************************************
;* Max speed to stay locked in 3rd
;***********************************************************************************************
" @ 0x2951;


min_speed_4th [] [7] byte "

;***********************************************************************************************
;* Min speed to enable start lock in 4th
;***********************************************************************************************
" @ 0x2982;


stay_speed_4th [] [7] byte "

;***********************************************************************************************
;* Max speed to stay locked in 4th
;***********************************************************************************************
" @ 0x29b3;


min_speed_3_4 [] [7] byte "

;***********************************************************************************************
;* Min. speed to enable 3-4 shift
;***********************************************************************************************
" @ 0x29e4;


max_speed_4th [] [7] byte "

;***********************************************************************************************
;* Max. speed to exit 4th gear
;***********************************************************************************************
" @ 0x2a15;


"

;***********************************************************************************************
;*
;***********************************************************************************************
" @ 0x2a48;


"

;***********************************************************************************************
;* VS to row #
;***********************************************************************************************
" @ 0x2A70;


"

;***********************************************************************************************
;* time to column #
;***********************************************************************************************
" @ 0x2A9C;


"

;***********************************************************************************************
;* Wastegate gain vs Throttle
;***********************************************************************************************
" @ 0x2AB4;


"

;***********************************************************************************************
;* Wastegate gain vs ECT
;***********************************************************************************************
" @ 0x2AC2;


"

;***********************************************************************************************
;* Wastegate % vs RPM
;***********************************************************************************************
" @ 0x2AD0;


"

;***********************************************************************************************
;*
;***********************************************************************************************
" @ 0x2ADC;


wg_ld_adder [] byte "

;***********************************************************************************************
;* Wastegate load adder vs ACT
;***********************************************************************************************
" @ 0x2AF0;


wg_cntl_knock [] [11] byte "

;***********************************************************************************************
;* Wastegate Control (knock detected)
;*  These values need to be lower than the Load values
;*  measured by the VAM during Open Loop boost control
;***********************************************************************************************
" @ 0x2B06;


wg_cntl [] [11] byte "

;***********************************************************************************************
;* Wastegate Control (no knock detected)
;***********************************************************************************************
" @ 0x2B69;


wg_rpm_cntl [] [5] byte "

;***********************************************************************************************
;* Wastegate RPM Control
;***********************************************************************************************
" @ 0x2BCC;


wg_cntl_load [] [5] byte "

;***********************************************************************************************
;* Wastegate control vs Load
;***********************************************************************************************
" @ 0x2BE5;


"

;***********************************************************************************************
;*
;***********************************************************************************************
" @ 0x2BFE;


"

;***********************************************************************************************
;* Load scaling
;***********************************************************************************************
" @ 0x2C08;


"

;***********************************************************************************************
;* ECT Ignition Advance (part throttle)
;***********************************************************************************************
" @ 0x2C48;


"

;***********************************************************************************************
;* ACT Ignition Advance (part throttle)
;***********************************************************************************************
" @ 0x2C56;


"

;***********************************************************************************************
;* ECT Ignition Advance (WOT)
;***********************************************************************************************
" @ 0x2C64;


"

;***********************************************************************************************
;* VAT Ignition Advance (WOT)
;***********************************************************************************************
" @ 0x2C72;


"
;***********************************************************************************************
;* Idle spark subtracter vs time
;*  Superchips mods 2c8b = c2
;***********************************************************************************************
" @ 0x2C80;


high_oct_ign [] [11] byte "

;***********************************************************************************************
;* High Octane Ignition map
;***********************************************************************************************
" @ 0x2C8C;


low_oct_ign [] [11] byte "

;***********************************************************************************************
;* Low Octane Ignition map
;***********************************************************************************************
" @ 0x2D47;


ign_adv [] [11] byte "

;***********************************************************************************************
;* Ignition Advance vs Engine Acceleration
;***********************************************************************************************
" @ 0x2E02;


"

;***********************************************************************************************
;* Group of parameters
;***********************************************************************************************
" @ 0x2E66;


"

;***********************************************************************************************
;* PIP multiplier for knock window #1
;***********************************************************************************************
" @ 0x2E8E;


"

;***********************************************************************************************
;* PIP multiplier for knock window #2
;***********************************************************************************************
" @ 0x2EAA;


"

;***********************************************************************************************
;* Knock retard vs RPM
;***********************************************************************************************
" @ 0x2EBE;


"

;***********************************************************************************************
;* Spark hold time vs RPM
;***********************************************************************************************
" @ 0x2ECA;


"

;***********************************************************************************************
;* Automatic transmission controls
;***********************************************************************************************
" @ 0x2EE4;


"

;***********************************************************************************************
;* LUS ECT function
;*  aka Shift light ECT modifier
;***********************************************************************************************
" @ 0x2EEA;


"

;***********************************************************************************************
;* LUS Load function
;*  aka Shift light Load modifier
;***********************************************************************************************
" @ 0x2F06;


"
;***********************************************************************************************
" @ 0x2F22;

//                    HEDF_on
//2F24  6E                  byte  $6E                         ;110 DegC
//                    HEDF_off
//2F25  05                  byte  $05                         ;105 DegC
//                    EDF_on
//2F26  64                  byte  $64                         ;100 DegC
//                    EDF_off
//2F27  05                  byte  $05                         ;95 DegC


"
;***********************************************************************************************
" @ 0x2F38;


"

;***********************************************************************************************
;* Continous Test Structure
;*  Fault THRESHOLD Value
;***********************************************************************************************
" @ 0x2F3E;


"

;***********************************************************************************************
;* Continous Test Structure
;*  Fault UPCOUNT Value
;***********************************************************************************************
" @ 0x2F4F;


"

;***********************************************************************************************
;* RPM scaling (RPM scaling TCI for spark tables)
;***********************************************************************************************
" @ 0x3124;


"

;***********************************************************************************************
;* Group of parameters
;***********************************************************************************************
" @ 0x3158;

//                    Injector_size
//3178  419F                word  $9F41                       ;Injector size


"

;***********************************************************************************************
;*  ECT to column # (ECT scaling TCI for fuel tables)
;***********************************************************************************************
" @ 0x317E;


"

;***********************************************************************************************
;* time to row #
;***********************************************************************************************
" @ 0x31A6;


"

;***********************************************************************************************
;*  Load to row # (Load scaling TRI for fuel tables)
;***********************************************************************************************
" @ 0x31C2;


"

;***********************************************************************************************
;* EGO bias vs Mass Air
;***********************************************************************************************
" @ 0x31D8;


pulse_delay [] [4] byte "

;***********************************************************************************************
;* Exhaust Gas Pulse Delay
;***********************************************************************************************
" @ 0x31F0;


q_table [] [4] byte "

;***********************************************************************************************
;* Parameters - possible table
;***********************************************************************************************
" @ 0x3208;


"

;***********************************************************************************************
;
; ECT to row # (TCI ECT for ISC)
;
;***********************************************************************************************
" @ 0x3226;


"

;
; time to row # (TRI ISC time since start)
;
" @ 0x324E;


startup_isc [] [8] byte "

;
; Startup ISC
;
" @ 0x327A;


"

;***********************************************************************************************
;* ??? some sort of wastgate transfer function?
;***********************************************************************************************
" @ 0x32D2;


"

;***********************************************************************************************
;* ???
;***********************************************************************************************
" @ 0x32EA;


"

;***********************************************************************************************
;* part of boost control
;***********************************************************************************************
" @ 0x3302;


"

;***********************************************************************************************
;* part of boost control
;***********************************************************************************************
" @ 0x330E;


"

;***********************************************************************************************
;* part of boost control (RPM duty cycle adder)
;***********************************************************************************************
" @ 0x331A;


"

;***********************************************************************************************
;* part of boost control (VAT duty cycle adder)
;***********************************************************************************************
" @ 0x3342;


"

;***********************************************************************************************
;* part of boost control (BAP duty cycle adder)
;***********************************************************************************************
" @ 0x3352;


base_timing [] [11] byte "

;***********************************************************************************************
;* Base Timing map (knock sensed)
;***********************************************************************************************
" @ 0x3362;


"

;***********************************************************************************************
;* Group of parameters
;***********************************************************************************************
" @ 0x341D;


"

;***********************************************************************************************
;* (RPM is the X-axis)
;***********************************************************************************************
" @ 0x3424;


"

;***********************************************************************************************
;* ACT to column #
;***********************************************************************************************
" @ 0x3450;


"

;***********************************************************************************************
;* Closed throttle Ignition timing vs RPM
;***********************************************************************************************
" @ 0x3478;


"

;***********************************************************************************************
;* Closed throttle Ignition timing vs ECT
;***********************************************************************************************
" @ 0x348C;


"

;***********************************************************************************************
;*
;***********************************************************************************************
" @ 0x349A;


"

;***********************************************************************************************
;*
;***********************************************************************************************
" @ 0x34AE;


"

;***********************************************************************************************
;* KAM initialization data (spark table)
;***********************************************************************************************
" @ 0x34C0;


act_v_load [] [8] byte"

;***********************************************************************************************
;* ACT vs load
;***********************************************************************************************
" @ 0x3518;


act_v_load2 [] [8] byte "

;***********************************************************************************************
;* 3518 clone function - ACT vs load
;***********************************************************************************************
" @ 0x35A0;


"

;***********************************************************************************************
;*  Group of parameters
;***********************************************************************************************
" @ 0x3628;


"

;***********************************************************************************************
;* load to row # (coastdown fuel shutoff)
;***********************************************************************************************
" @ 0x362C;


"

;***********************************************************************************************
;* Adaptive Ignition timing (ECT)
;***********************************************************************************************
" @ 0x3658;


"

;***********************************************************************************************
;* VAT to column # (or VAT scaling TCI for EGR)
;***********************************************************************************************
" @ 0x366E;


egr_load_dis [] [11] byte "
;***********************************************************************************************
;* EGR Load disable
;*  INPUTS:
;*   scaled VAT, scaled ECT, Load
;***********************************************************************************************
" @ 0x368E;


"

;***********************************************************************************************
;*
;***********************************************************************************************
" @ 0x36B6;


"

;***********************************************************************************************
;*  DTC-related parameters
;***********************************************************************************************
" @ 0x36D2;

//C0E9                word  $E9C0                       ;ECT low limit
//36D4  400C                word  $0C40                       ;ECT high limit
//36D6  C0E9                word  $E9C0
//36D8  000A                word  $0A00
//36DA  0200                word  Low_Speed_Output
//36DC  80F7                word  $F780                       ;WOT setpoint
//36DE  000A                word  $0A00                       ;idle setpoint
//36E0  00B1                word  $B100                       ;ACT 50 DegF setpoint
//36E2  0010                word  $1000                       ;ACT 220 DegF setpoint
//36E4  00B1                word  $B100                       ;ACT 50 DegF setpoint
//36E6  0010                word  $1000                       ;ACT 220 DegF setpoint
//36E8  00FA                word  $FA00                       ;continuous VAF max raw value
//36EA  C008                word  $08C0                       ;continuous VAF min raw value
//36EC  C0E9                word  $E9C0                       ;VAT 240 DegF setpoint
//36EE  000A                word  $0A00                       ;VAT -35 DegF setpoint
//36F0  00B4                word  $B400                       ;ECT 45 DegF setpoint
//36F2  0010                word  $1000                       ;ECT 220 DegF setpoint
//36F4  803C                word  $3C80                       ;ECT 150 DegF setpoint
//36F6  0010                word  $1000                       ;ECT 220 DegF setpoint
//36F8  3CFF                word  $FF3C                       ;VAT snapshot setpoint
//36FA  C023                word  $23C0                       ;TPS low setpoint
//36FC  8042                word  $4280                       ;TPS high setpoint
//36FE  C023                word  $23C0                       ;TPS setpoint
//3700  8042                word  $4280                       ;TPS setpoint
//3702  007D                word  $7D00                       ;TPS setpoint
//3704  0046                word  $4600                       ;TPS setpoint
//3706  C008                word  $08C0                       ;KOEO VAF lower limit (DTC 15)
//3708  0019                word  $1900                       ;KOEO VAT setpoint
//370A  4038                word  $3840                       ;KOER VAF lower limit
//370C  C076                word  $76C0                       ;KOER VAF upper limit
//370E  00B1                word  $B100                       ;VAT setpoint
//3710  8014                word  $1480                       ;VAT setpoint
//3712  00B1                word  $B100                       ;VAT upper limit
//3714  8014                word  $1480                       ;VAT lower limit


//
//
//
r48_lu [] word @ 0x34c0;
lu00_u16_u16 [] word @ 0x2E8E;
lu01_u16_u16 [] word @ 0x2EAA;
lu02_u8_u8 []   byte @ 0x2796;
lu04_u16_s16 [] word @ 0x2FEC;
lu06_s8_u8 []   byte @ 0x242A;
lu07_u16_u16 [] word @ 0x3010;
lu09_u16_u16 [] word @ 0x240E;
lu11_u16_u16 [] word @ 0x2446;
lu12_u16_u16 [] word @ 0x2FD8;
lu13_u16_u16 [] word @ 0x3124;
lu14_s16_s16 [] word @ 0x24B6;
lu15_u16_u16 [] word @ 0x2492;
lu16_s16_u16 [] word @ 0x24FC;
lu17_u8_u8 []   byte @ 0x24F0;
lu18_s16_s16 [] word @ 0x317E;
lu19_u16_u16 [] word @ 0x31C2;
lu20_u16_u16 [] word @ 0x31A6;
lu21_u16_u16 [] word @ 0x2C08;
lu22_s8_u8 []   byte @ 0x2554;
lu23_u16_u16 [] word @ 0x252C;
lu24_u16_u16 [] word @ 0x2560;
lu25_u16_s16 [] word @ 0x31D8;
lu27_s16_u16 [] word @ 0x2752;
lu28_s16_u16 [] word @ 0x2772;
lu30_s8_u8 []   byte @ 0x2888;
lu31_s16_s16 [] word @ 0x3226;
lu32_u16_u16 [] word @ 0x324E;
lu33_u16_u16 [] word @ 0x2834;
lu34_u16_u16 [] word @ 0x2850;
lu35_s16_s16 [] word @ 0x286C;
lu36_s8_u8 []   byte @ 0x2894;
lu37_u16_u16 [] word @ 0x27FC;
lu38_u16_u16 [] word @ 0x2818;
lu41_u16_u16 [] word @ 0x27D4;
lu42_u16_u16 [] word @ 0x2908;
lu43_u16_u16 [] word @ 0x28D0;
lu44_u16_u16 [] word @ 0x28EC;
lu46_u16_u16 [] word @ 0x2A9C;
lu47_s16_u16 [] word @ 0x32D2;
lu48_s16_u16 [] word @ 0x32EA;
lu49_u16_u16 [] word @ 0x2A70;
lu50_s8_s8 []   byte @ 0x2AF0;
lu51_u16_u16 [] word @ 0x331A;
lu52_s8_s8 []   byte @ 0x3342;
lu53_u8_s8 []   byte @ 0x3352;
lu54_u16_u16 [] word @ 0x2AD0;
lu55_u8_u8 []   byte @ 0x330E;
lu56_u8_u8 []   byte @ 0x3302;
lu57_u8_u8 []   byte @ 0x2AB4;
lu58_s8_u8 []   byte @ 0x2AC2;
lu59_s8_s8 []   byte @ 0x348C;
lu60_s16_s16 [] word @ 0x3478;
lu61_u8_s8 []   byte @ 0x34AE;
lu62_u8_u8 []   byte @ 0x2C80;
lu64_u16_u16 [] word @ 0x362C;
lu65_u16_u16 [] word @ 0x3424;
lu66_s16_u16 [] word @ 0x3450;
lu67_s8_s8 []   byte @ 0x2C56;
lu68_s8_s8 []   byte @ 0x2C72;
lu69_s8_s8 []   byte @ 0x2C64;
lu70_s8_s8 []   byte @ 0x2C48;
lu71_u16_u16 [] word @ 0x349A;
lu72_u8_u8 []   byte @ 0x2ECA;
lu73_u8_u8 []   byte @ 0x2EBE;
lu74_s16_s16 [] word @ 0x3658;
lu75_s16_s16 [] word @ 0x366E;
lu76_s16_s16 [] word @ 0x2EEA;
lu77_u16_u16 [] word @ 0x2F06;

lookup1 [] word @ 0x6c0e;
lookup2 [] byte @ 0x6c38;
lookup3 [] byte @ 0x6c4d;
lookup4 [] word @ 0x6e56;

