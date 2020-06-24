#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include <stdio.h>
#include <string.h>
//ALIENTEKս��STM32������ʵ��9
//PWM���ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
//0.5ms->0�� pwmvall=249
//1.5ms->90�� pwmvall=749
//2.5ms->180�� pwmvall=	1249
//PA2Ϊ�ײ�������ƽţ�PA3Ϊ��������ͷ������ƽ�
u16 angle_to_pwm(float angle);
char order = 0;
float angle_top;
float angle_bot;
float angle_top2;
float angle_bot2;
u16 print_flat;
void TIM_PWM_Init(u16 arr,u16 psc);
//char order_string[20]={0};
int main(void)
{	


	u16 pwm_top;
	u16 pwm_bot;
	u16 pwm_top2;
	u16 pwm_bot2;
	print_flat = 0;
	delay_init(); //��ʱ������ʼ��
	NVIC_Configuration();
	uart_init(9600);
	TIM_PWM_Init(9999,143);//����Ƶ��PWM Ƶ��=72*10^6/(9999+1)/(143+1)=50Hz
	angle_top = 30;
	angle_bot = 90;
	angle_top2 = 30;
	angle_bot2 = 90;
	pwm_top =  angle_to_pwm(angle_top);
	pwm_bot =  angle_to_pwm(angle_bot);
	pwm_top2 =  angle_to_pwm(angle_top2);
	pwm_bot2 =  angle_to_pwm(angle_bot2);
	TIM_SetCompare3(TIM2,pwm_top);TIM_SetCompare4(TIM2,pwm_bot);
	TIM_SetCompare3(TIM3,pwm_top2);TIM_SetCompare4(TIM3,pwm_bot2);
	printf("ready");
	while(1)
	{
		//����ռ�ձ�pwmval1/(9999+1)

	//	memset(order_string,0,sizeof(order_string)*20);//��������
		//��������
//		scanf("%c\r\n",&order);
		
		//�޷������ƶ�������ͷ��λ��
		if(angle_top < 0)
			 angle_top = 0;
		if(angle_top > 135)
			 angle_top = 135;
		if(angle_bot < 0)
			 angle_bot = 0;
		if(angle_bot > 180)
			 angle_bot = 180;
		if(angle_top2 < 0)
			 angle_top2 = 0;
		if(angle_top2 > 135)
			 angle_top2 = 135;
		if(angle_bot2 < 0)
			 angle_bot2 = 0;
		if(angle_bot2 > 180)
			 angle_bot2 = 180;

		//ת��Ϊpwm���ֵ
		pwm_top =  angle_to_pwm(angle_top);
		pwm_bot =  angle_to_pwm(angle_bot);
		pwm_top2 =  angle_to_pwm(angle_top2);
		pwm_bot2 =  angle_to_pwm(angle_bot2);

		TIM_SetCompare3(TIM2,pwm_top);TIM_SetCompare4(TIM2,pwm_bot);
		TIM_SetCompare3(TIM3,pwm_top2);TIM_SetCompare4(TIM3,pwm_bot2);
		
		if(print_flat)
		{
			printf("%f,%f,%f,%f/n",angle_top,angle_bot,angle_top2,angle_bot2);
			print_flat = 0;
		}	
//		TIM_SetCompare3(TIM3,pwmval1);TIM_SetCompare4(TIM3,pwmval1);
//		TIM_SetCompare3(TIM4,pwmval1);TIM_SetCompare4(TIM4,pwmval1);
	}

}

u16 angle_to_pwm(float angle)
{
	u16 pwm_val;

	pwm_val = (u16)(50.0*angle/9.0+249.0); 
	return 	pwm_val;
}

//void SetJointAngle(u8 ID, float angle)
//{
//    switch(ID)
//    {
//        case 0:                                      //-90��~90��   
//            angle=angle+90.0;                      
//            angle=(u16)(50.0*angle/9.0+249.0);     
//            TIM_SetCompare1(TIM3,angle);        
//            break;
//                                                 //0��~180��
//        case 1:
//            angle=(u16)(4.175*angle+409.25);
//            TIM_SetCompare2(TIM3,angle);          
//            break;
// 
// 
//        case 2:                                    //-150��~0��
//            angle=-angle;
//            angle=(u16)(4.175*angle+480.0);
//            TIM_SetCompare1(TIM4,angle);
//            break;
// 
//        case 3:
//            angle=-180-angle;
//            angle=-angle;
//            angle=(u16)(4.175*angle+315.0);
//        
// 
//            TIM_SetCompare2(TIM4,angle);
//            break;
//                                              //-90��~90��
//        case 4:
//            angle=90.0+angle;
//            angle=(u16)(249.0+50.0*angle/9.0);
//            TIM_SetCompare3(TIM4,angle);            
//            break; 
// 
// 
//        default: break;
//    }    
//}
