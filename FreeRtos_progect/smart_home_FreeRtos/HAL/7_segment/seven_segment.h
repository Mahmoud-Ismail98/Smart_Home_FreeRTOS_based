/*
 * seven_segment.h
 *
 * Created: 25/10/2023 02:16:25 م
 *  Author: mahmoud ismail
 */ 


#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_
/*
#define numbe_seven_Segment 4
typedef struct {
	u8 Sev_SegPinA;
	u8 Sev_SegPinB;
	u8 Sev_SegPinC;
	u8 Sev_SegPinD;
}seven_segment_pin;

seven_segment_pin * ARR_SEV_SEG[4];
seven_segment_pin	sven_seg1={PORTA_PIN0,PORTA_PIN1,PORTA_PIN2,PORTA_PIN3};
seven_segment_pin	sven_seg2={PORTA_PIN4,PORTA_PIN5,PORTA_PIN6,PORTA_PIN7};
seven_segment_pin	sven_seg3={PORTB_PIN0,PORTB_PIN1,PORTB_PIN2,PORTB_PIN3};
seven_segment_pin	sven_seg4={PORTB_PIN4,PORTB_PIN5,PORTB_PIN6,PORTB_PIN7};

*/
#define numbe_seven_Segment 4
typedef struct {
	u8 Sev_SegPinA;
	u8 Sev_SegPinB;
	u8 Sev_SegPinC;
	u8 Sev_SegPinD;
}seven_segment_pin;

#define	START_PUTTON_PIN	PORTC_PIN0
#define	STOP_PUTTON_PIN	    PORTC_PIN1
#define	CLEAR_PUTTON_PIN    PORTC_PIN2

void init_four_sev_Seg(void);
void Sev_SegmentInit(seven_segment_pin* sev_seg);
void Sev_SegmentShow(u8 val,seven_segment_pin* sev_seg);
void Sev_SegmentCounter_up(u16 counter_value);
void sev_seg_stop_watch(void);	



#endif /* SEVEN_SEGMENT_H_ */