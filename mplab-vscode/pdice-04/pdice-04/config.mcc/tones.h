#pragma once
#include "mcc_generated_files/system/system.h"


// Select which introduction music we want to play at poweron
#define introMusic()        introMusic_02()

// Select which sound to play after a dice roll
#define diceSound_1()       diceSound_Play1()
#define diceSound_2()       diceSound_Play2()
#define diceSound_3()       diceSound_Play3()
#define diceSound_4()       diceSound_Play4()
#define diceSound_5()       diceSound_Play5()
#define diceSound_6()       diceSound_Play6()

// Set the default buzzer frequency 
#define BUZZFREQ_DEFAULT    4000

// Set buzzer frequency and delay for dice rolls
#define BUZZFREQ_DICEROLLS  4000
#define BUZZDELAY_DICEROLLS 20

//
// Prototypes
//
void introMusic_01(void);               // Plays a melody (Beethoven)
void introMusic_02(void);               // Plays a melody (Star Wars)
void introMusic_03(void);               // Whoop up
void introMusic_04(void);               // Random
void introMusic_05(void);               // ?
void introMusic_06(void);               // ?
void introMusic_07(void);               // ?
void introMusic_08(void);               // ?
void introMusic_09(void);               // ?
void introMusic_10(void);               // ?

void diceSound_None(void);
void diceSound_Play1(void);
void diceSound_Play2(void);
void diceSound_Play3(void);
void diceSound_Play4(void);
void diceSound_Play5(void);
void diceSound_Play6(void);

void playNote(uint16_t period, uint16_t duration_ms);   // Play a note (from the table in music.h)
uint16_t freqToPwmPeriod(uint16_t freq);                // Convert a frequency to PWM reload value
inline void buzz(uint16_t duration_ms);                 // Buzz at default frequency for .. ms
void buzzNr(uint16_t nr);                               // Buzz specified number of times 
void buzzFreq(uint16_t freq, uint16_t duration_ms);     // Buzz at given freq for .. ms


// Buzzer macro functions
#define buzzOn()        PWM3_Start()
#define buzzOff()       PWM3_Stop()
#define buzzSetFreq(p)  PWM3_PeriodSet(freqToPwmPeriod(p))


/* 
    Musical notes to frequency table: https://www.liutaiomottola.com/formulae/freqtab.htm
    See MusicalNotes_to_PWM_reload_values.ods for calculations
    
Fosc	16.00E+06							
Prescaler	1							

PeriodCount = Fosc / (freq*prescaler) - 1

Note	    Octave	Freq Hz	    Period μs	Period Count	PRH	PRL		Real freq
NOTE_C  	5	    523.250	    1911.132	30577	        77	71		523.267
NOTE_C#	    5	    554.370	    1803.849	28861	        70	BC		554.389
NOTE_D  	5	    587.330	    1702.620	27241	        6A	68		587.352
NOTE_D#	    5	    622.250	    1607.071	25712	        64	70		622.274
NOTE_E  	5   	659.250	    1516.875	24269	        5E	CD		659.277
NOTE_F  	5	    698.460	    1431.721	22907	        59	7A		698.490
NOTE_F#	    5	    739.990	    1351.370	21621	        54	74		740.024
NOTE_G  	5	    783.990	    1275.526	20407	        4F	B7		784.028
NOTE_G#	    5	    830.610	    1203.934	19262	        4B	3D		830.653
NOTE_A  	5	    880.000	    1136.364	18181	        47	04		880.048
NOTE_A#	    5	    932.330	    1072.582	17160	        43	08		932.384
NOTE_B  	5	    987.770	    1012.381	16197	        3F	45		987.831

NOTE_C  	6  	    1046.502	955.564	    15288	        3B	B8		1046.570
NOTE_C#	    6  	    1108.731	901.932	    14430	        38	5D		1108.808
NOTE_D  	6  	    1174.659	851.311	    13620	        35	33		1174.745
NOTE_D#	    6  	    1244.508	803.530	    12855	        32	37		1244.605
NOTE_E  	6  	    1318.510	758.432	    12134	        2F	65		1318.619
NOTE_F  	6       1396.913	715.864	    11453	        2C	BC		1397.035
NOTE_F#	    6  	    1479.978	675.686	    10810	        2A	39		1480.115
NOTE_G  	6  	    1567.982	637.762	    10203	        27	DB		1568.136
NOTE_G#	    6  	    1661.219	601.968	    9630	        25	9E		1661.391
NOTE_A  	6  	    1760.000	568.182	    9090	        23	81		1760.194
NOTE_A#	    6  	    1864.655	536.292	    8580	        21	83		1864.872
NOTE_B  	6  	    1975.533	506.193	    8098	        1F	A2		1975.777
								
NOTE_C  	7  	    2093.005	477.782	    7644	        1D	DB		2093.279
NOTE_C#	    7  	    2217.461	450.966	    7214	        1C	2E		2217.768
NOTE_D  	7  	    2349.318	425.655	    6809	        1A	99		2349.663
NOTE_D#	    7  	    2489.016	401.765	    6427	        19	1B		2489.403
NOTE_E  	7  	    2637.021	379.216	    6066	        17	B2		2637.456
NOTE_F  	7  	    2793.826	357.932	    5726	        16	5D		2794.314
NOTE_F#	    7  	    2959.955	337.843	    5404	        15	1C		2960.503
NOTE_G  	7  	    3135.964	318.881	    5101	        13	ED		3136.579
NOTE_G#	    7  	    3322.438	300.984	    4815	        12	CE		3323.128
NOTE_A  	7  	    3520.000	284.091	    4544	        11	C0		3520.775
NOTE_A#	    7  	    3729.310	268.146	    4289	        10	C1		3730.179
NOTE_B  	7  	    3951.066	253.096	    4049	        0F	D0		3952.042
*/

#if(0)
#define NOTE_C5	    30577
#define NOTE_CS5	28861
#define NOTE_D5	    27241
#define NOTE_DS5	25712
#define NOTE_E5	    24269
#define NOTE_F5	    22907
#define NOTE_FS5	21621
#define NOTE_G5  	20407
#define NOTE_GS5	19262
#define NOTE_A5  	18181
#define NOTE_AS5	17160
#define NOTE_B5  	16197

#define NOTE_C6     15288
#define NOTE_CS6    14430
#define NOTE_D6     13620
#define NOTE_DS6    12855
#define NOTE_E6     12134
#define NOTE_F6     11453
#define NOTE_FS6    10810
#define NOTE_G6     10203
#define NOTE_GS6    9630
#define NOTE_A6     9090
#define NOTE_AS6    8580
#define NOTE_B6     8098

#define NOTE_C7     7644
#define NOTE_CS7    7214
#define NOTE_D7     6809
#define NOTE_DS7    6427
#define NOTE_E7     6066
#define NOTE_F7     5726
#define NOTE_FS7    5404
#define NOTE_G7     5101
#define NOTE_GS7    4815
#define NOTE_A7     4544
#define NOTE_AS7    4289
#define NOTE_B7     4049
#endif


#define NOTE_C5     (uint16_t)((_XTAL_FREQ / (523.250 * 1)) - 1)
#define NOTE_C5  	(uint16_t)((_XTAL_FREQ / (523.250 * 1)) - 1)
#define NOTE_CS5	(uint16_t)((_XTAL_FREQ / (554.370 * 1)) - 1)
#define NOTE_D5  	(uint16_t)((_XTAL_FREQ / (587.330 * 1)) - 1)
#define NOTE_DS5	(uint16_t)((_XTAL_FREQ / (622.250 * 1)) - 1)
#define NOTE_E5  	(uint16_t)((_XTAL_FREQ / (659.250 * 1)) - 1)
#define NOTE_F5  	(uint16_t)((_XTAL_FREQ / (698.460 * 1)) - 1)
#define NOTE_FS5	(uint16_t)((_XTAL_FREQ / (739.990 * 1)) - 1)
#define NOTE_G5  	(uint16_t)((_XTAL_FREQ / (783.990 * 1)) - 1)
#define NOTE_GS5	(uint16_t)((_XTAL_FREQ / (830.610 * 1)) - 1)
#define NOTE_A5  	(uint16_t)((_XTAL_FREQ / (880.000 * 1)) - 1)
#define NOTE_AS5	(uint16_t)((_XTAL_FREQ / (932.330 * 1)) - 1)
#define NOTE_B5  	(uint16_t)((_XTAL_FREQ / (987.770 * 1)) - 1)

#define NOTE_C6  	(uint16_t)((_XTAL_FREQ / (1046.502 * 1)) - 1)
#define NOTE_CS6	(uint16_t)((_XTAL_FREQ / (1108.731 * 1)) - 1)
#define NOTE_D6  	(uint16_t)((_XTAL_FREQ / (1174.659 * 1)) - 1)
#define NOTE_DS6	(uint16_t)((_XTAL_FREQ / (1244.508 * 1)) - 1)
#define NOTE_E6  	(uint16_t)((_XTAL_FREQ / (1318.510 * 1)) - 1)
#define NOTE_F6  	(uint16_t)((_XTAL_FREQ / (1396.913 * 1)) - 1)
#define NOTE_FS6	(uint16_t)((_XTAL_FREQ / (1479.978 * 1)) - 1)
#define NOTE_G6  	(uint16_t)((_XTAL_FREQ / (1567.982 * 1)) - 1)
#define NOTE_GS6	(uint16_t)((_XTAL_FREQ / (1661.219 * 1)) - 1)
#define NOTE_A6  	(uint16_t)((_XTAL_FREQ / (1760.000 * 1)) - 1)
#define NOTE_AS6	(uint16_t)((_XTAL_FREQ / (1864.655 * 1)) - 1)
#define NOTE_B6  	(uint16_t)((_XTAL_FREQ / (1975.533 * 1)) - 1)
								
#define NOTE_C7  	(uint16_t)((_XTAL_FREQ / (2093.005 * 1)) - 1)
#define NOTE_CS7	(uint16_t)((_XTAL_FREQ / (2217.461 * 1)) - 1)
#define NOTE_D7  	(uint16_t)((_XTAL_FREQ / (2349.318 * 1)) - 1)
#define NOTE_DS7	(uint16_t)((_XTAL_FREQ / (2489.016 * 1)) - 1)
#define NOTE_E7  	(uint16_t)((_XTAL_FREQ / (2637.021 * 1)) - 1)
#define NOTE_F7  	(uint16_t)((_XTAL_FREQ / (2793.826 * 1)) - 1)
#define NOTE_FS7	(uint16_t)((_XTAL_FREQ / (2959.955 * 1)) - 1)
#define NOTE_G7  	(uint16_t)((_XTAL_FREQ / (3135.964 * 1)) - 1)
#define NOTE_GS7	(uint16_t)((_XTAL_FREQ / (3322.438 * 1)) - 1)
#define NOTE_A7  	(uint16_t)((_XTAL_FREQ / (3520.000 * 1)) - 1)
#define NOTE_AS7	(uint16_t)((_XTAL_FREQ / (3729.310 * 1)) - 1)
#define NOTE_B7  	(uint16_t)((_XTAL_FREQ / (3951.066 * 1)) - 1)

