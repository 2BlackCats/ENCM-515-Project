/**
  ******************************************************************************
  * @file    BSP/Src/circularbuffer
  * @author  MCD Application Team
  * @brief   This example code shows how to use the STM324xG BSP Drivers
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  ******************************************************************************
  ******************************************************************************
  * This code was modified for use in ENCM 515 in 2022
  * B. Tan
  * Note: DO NOT REGENERATE CODE/MODIFY THE IOC
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define TEST_MODE  0 // Change according to README.md
#define CONFIG_MODE 5 // Change according to README.md
#define true 1
#define false 0


#if TEST_MODE == 1
	#define NUMBER_OF_TAPS 3
	#define FUNCTIONAL_TEST 0
	int16_t filter_coeffs[NUMBER_OF_TAPS] = {0, 10, 20};




	#if CONFIG_MODE == 0 // Testing with normal circular buffer
		#define BLOCK_PROCESSING 0
		#define BUFFER_SIZE 8
		#define MAX_FRAME_IDX 0
    	#define FRAME_SIZE 0
		#define MLA 0
	#elif CONFIG_MODE == 1 // Testing with circular buffer & MLA
		#define BLOCK_PROCESSING 0
		#define BUFFER_SIZE 8
		#define MAX_FRAME_IDX 0
    	#define FRAME_SIZE 0
		#define MLA 1
	#elif CONFIG_MODE == 2  // Testing with frame size of 3
    	#define BLOCK_PROCESSING 1
		#define BUFFER_SIZE 9
    	#define FRAME_SIZE 3
		#define MAX_FRAME_IDX 2
		#define MLA 0
	#elif CONFIG_MODE == 3 // Testing processing with frame size of 3 & MLA
    	#define BLOCK_PROCESSING 1
		#define BUFFER_SIZE 9
    	#define FRAME_SIZE 3
		#define MAX_FRAME_IDX 2
		#define MLA 1
	#endif

#endif

#if TEST_MODE == 0
	#define NUMBER_OF_TAPS 256
    #define BUFFER_SIZE 32
	#define FUNCTIONAL_TEST 0
	/* 256 */
	int16_t filter_coeffs[NUMBER_OF_TAPS] = {-3, -8, -8, -12, -13, -13, -12, -9, -4, 1, 6, 10, 11, 9, 5, 0, -6, -11, -13, -13, -9, -2, 6, 13, 17, 17, 13, 5, -5, -14, -21, -23, -19, -10, 2, 15, 25, 30, 27, 17, 2, -15, -29, -37, -36, -26, -8, 13, 33, 45, 47, 37, 17, -9, -35, -53, -59, -50, -28, 3, 36, 61, 73, 66, 43, 6, -34, -69, -88, -86, -61, -20, 30, 75, 104, 108, 85, 38, -22, -80, -122, -135, -114, -63, 9, 83, 142, 167, 152, 96, 11, -83, -163, -207, -200, -142, -41, 78, 187, 257, 266, 206, 87, -66, -217, -327, -362, -306, -163, 41, 259, 436, 522, 481, 303, 14, -331, -654, -866, -886, -661, -174, 543, 1416, 2336, 3176, 3818, 4164, 4164, 3818, 3176, 2336, 1416, 543, -174, -661, -886, -866, -654, -331, 14, 303, 481, 522, 436, 259, 41, -163, -306, -362, -327, -217, -66, 87, 206, 266, 257, 187, 78, -41, -142, -200, -207, -163, -83, 11, 96, 152, 167, 142, 83, 9, -63, -114, -135, -122, -80, -22, 38, 85, 108, 104, 75, 30, -20, -61, -86, -88, -69, -34, 6, 43, 66, 73, 61, 36, 3, -28, -50, -59, -53, -35, -9, 17, 37, 47, 45, 33, 13, -8, -26, -36, -37, -29, -15, 2, 17, 27, 30, 25, 15, 2, -10, -19, -23, -21, -14, -5, 5, 13, 17, 17, 13, 6, -2, -9, -13, -13, -11, -6, 0, 5, 9, 11, 10, 6, 1, -4, -9, -12, -13, -13, -12, -8, -8, -3};

	#if CONFIG_MODE == 0  // Processing with normal circular buffer

    	#define BLOCK_PROCESSING 0
		#define MAX_FRAME_IDX 0
    	#define FRAME_SIZE 0
		#define MLA 0

	#elif CONFIG_MODE == 1 // Processing with circular buffer & MLA
    	#define BLOCK_PROCESSING 0
		#define MAX_FRAME_IDX 0
    	#define FRAME_SIZE 0
		#define MLA 1


	#elif CONFIG_MODE == 2  // Block processing with frame size of 3
    	#define BLOCK_PROCESSING 1
    	#define FRAME_SIZE 3
		#define MAX_FRAME_IDX 2
		#define MLA 0

	#elif CONFIG_MODE == 3  // Block processing with frame size of 16
    	#define BLOCK_PROCESSING 1
    	#define FRAME_SIZE 16
		#define MAX_FRAME_IDX 15
		#define MLA 0



	#elif CONFIG_MODE == 4 // Block processing with frame size of 3 & MLA
    	#define BLOCK_PROCESSING 1
    	#define FRAME_SIZE 3
		#define MAX_FRAME_IDX 2
		#define MLA 1


	#elif CONFIG_MODE == 5 // Block processing with frame size of 16 & MLA
       	#define BLOCK_PROCESSING 1
    	#define FRAME_SIZE 16
		#define MAX_FRAME_IDX 15
		#define MLA 1



	#else
		#error "invalid configuration selected"
	#endif


#endif




/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

__IO uint8_t UserPressButton = 0;

/* Wave Player Pause/Resume Status. Defined as external in waveplayer.c file */
__IO uint32_t PauseResumeStatus = IDLE_STATUS;

/* Counter for User button presses */
__IO uint32_t PressCount = 0;

TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef   sConfig;
uint32_t uwPrescalerValue = 0;
uint32_t uwCapturedValue = 0;

volatile int32_t *raw_audio = 0x802002C; // ignore first 44 bytes of header
#define HISTORY_SIZE  (NUMBER_OF_TAPS + FRAME_SIZE)
int16_t history_l[HISTORY_SIZE];
int16_t history_r[HISTORY_SIZE];
volatile int overflow_count = 0;
volatile int underflow_count = 0;


/* 220 */
//int16_t filter_coeffs[NUMBER_OF_TAPS] = {0, 14, 15, 21, 26, 28, 27, 23, 15, 5, -6, -15, -20, -21, -16, -7, 4, 15, 23, 26, 22, 12, -2, -16, -27, -33, -30, -20, -3, 15, 31, 41, 41, 30, 11, -13, -35, -50, -53, -43, -21, 7, 37, 59, 67, 59, 36, 1, -37, -67, -83, -79, -54, -13, 33, 75, 101, 102, 77, 31, -27, -82, -120, -130, -107, -55, 15, 86, 140, 163, 145, 89, 5, -87, -163, -204, -194, -134, -34, 83, 189, 255, 261, 200, 80, -72, -220, -326, -358, -300, -156, 47, 263, 437, 520, 476, 297, 7, -337, -657, -865, -883, -655, -168, 549, 1420, 2336, 3174, 3812, 4158, 4158, 3812, 3174, 2336, 1420, 549, -168, -655, -883, -865, -657, -337, 7, 297, 476, 520, 437, 263, 47, -156, -300, -358, -326, -220, -72, 80, 200, 261, 255, 189, 83, -34, -134, -194, -204, -163, -87, 5, 89, 145, 163, 140, 86, 15, -55, -107, -130, -120, -82, -27, 31, 77, 102, 101, 75, 33, -13, -54, -79, -83, -67, -37, 1, 36, 59, 67, 59, 37, 7, -21, -43, -53, -50, -35, -13, 11, 30, 41, 41, 31, 15, -3, -20, -30, -33, -27, -16, -2, 12, 22, 26, 23, 15, 4, -7, -16, -21, -20, -15, -6, 5, 15, 23, 27, 28, 26, 21, 15, 14, 0};

/* 128 */
//int16_t filter_coeffs[NUMBER_OF_TAPS] = {1,2,2,3,3,1,-2,-5,-7,-6,-2,5,11,14,12,3,-10,-22,-27,-21,-3,20,40,46,32,0,-39,-69,-73,-45,10,71,112,110,57,-32,-123,-175,-156,-64,75,204,264,215,59,-152,-333,-397,-291,-31,297,557,617,404,-53,-610,-1043,-1113,-655,355,1774,3314,4617,5364,5364,4617,3314,1774,355,-655,-1113,-1043,-610,-53,404,617,557,297,-31,-291,-397,-333,-152,59,215,264,204,75,-64,-156,-175,-123,-32,57,110,112,71,10,-45,-73,-69,-39,0,32,46,40,20,-3,-21,-27,-22,-10,3,12,14,11,5,-2,-6,-7,-5,-2,1,3,3,2,2,1};

/* 32 */
//int16_t filter_coeffs[NUMBER_OF_TAPS] = {271, 403, 558, 602, 466, 124, -369, -877, -1212, -1183, -665, 344, 1701, 3143, 4351, 5040, 5040, 4351, 3143, 1701, 344, -665, -1183, -1212, -877, -369, 124, 466, 602, 558, 403, 271};
volatile int new_sample_flag = 0;
static int sample_count = 0;
int16_t newSampleL = 0;
int16_t newSampleR = 0;
int16_t filteredSampleL;
int16_t filteredSamplesLFrame [FRAME_SIZE];

int16_t filteredSampleR;
static int head = 0;
static int tail = 0;
static int samples_since_last_frame = 1;


static int16_t accumulators_16[FRAME_SIZE];
static volatile int32_t filteredOutBufferA[BUFFER_SIZE];
static volatile int32_t filteredOutBufferB[BUFFER_SIZE];
static volatile int bufchoice = 0;

extern I2S_HandleTypeDef       hAudioOutI2s;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void GPIOA_Init(void);
static int16_t ProcessSample(int16_t newsample, int16_t* history);
static int16_t ProcessSampleCircular(int16_t newsample, int16_t* history);
static int16_t ProcessSampleCircular2(int16_t newsample, int16_t* history);
static int ProcessBlock(int16_t newsample, int16_t* history);
static int ProcessBlock2(int16_t newsample, int16_t* history);
static void RunTestMode();



/* Private functions ---------------------------------------------------------*/





/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
 /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();

  /* Configure LED3, LED4, LED5 and LED6 */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);

  /* Configure the system clock to 100 MHz */
  SystemClock_Config();

  /* Configure GPIO so that we can probe PB2 with an Oscilloscope */
  GPIOA_Init();

  /* Configure the User Button in GPIO Mode */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

  /* Set TIMx instance */
  TimHandle.Instance = TIMx;

  /* Initialize TIM3 peripheral to toggle with a frequency of ~ 8 kHz
   * System clock is 100 MHz and TIM3 is counting at the rate of the system clock
   * so 100 M / 8 k is 12500
   */
  TimHandle.Init.Period = 12499;
  TimHandle.Init.Prescaler = 0;
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
	  /* Initialization Error */
	  Error_Handler();
  }

  ITM_Port32(30) = 0;
  if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
	  /* Starting Error */
	  Error_Handler();
  }


  /******************************************************************************
   ******************************************************************************
   ******************************************************************************
   * Init Complete
   * BEGIN LAB 2 CODE HERE
   ******************************************************************************
   ******************************************************************************
   ******************************************************************************
   */


	if (TEST_MODE){
		RunTestMode();
	}else{



	  static int i = 0;
	  static int k = 0;
	  static int start = 0;

	  while (1) {


	#ifdef FUNCTIONAL_TEST
			if (sample_count < 64000) {
				  newSampleL = (int16_t)raw_audio[sample_count];
				  newSampleR = (int16_t)(raw_audio[sample_count] >> 16);
				  sample_count++;
			  } else {
				  sample_count = 0;
			  }
	#endif

	#ifndef FUNCTIONAL_TEST
		if (new_sample_flag == 1) {
	#endif
			//  CONFIG_MODE involves Circular Buffer
			if (CONFIG_MODE == 0 ||CONFIG_MODE == 1){
				new_sample_flag = 0;
				if (MLA == 0){
					filteredSampleL = ProcessSampleCircular(newSampleL,history_l); // "L"

				} else{
					filteredSampleL = ProcessSampleCircular2(newSampleL,history_l); // "L"
				}
				new_sample_flag = 0;
				if (i < NUMBER_OF_TAPS-1) {
					filteredSampleL = 0;
					i++;
				} else {
					if (bufchoice == 0) {
						filteredOutBufferA[k] = ((int32_t)filteredSampleL << 16) + (int32_t)filteredSampleL; // copy the filtered output to both channels
					} else {
						filteredOutBufferB[k] = ((int32_t)filteredSampleL << 16) + (int32_t)filteredSampleL;
					}

					k++;
					if (k == BUFFER_SIZE){
						k = 0;
					}

				}



			//  CONFIG_MODE involves Frame Processing
			}else {

				new_sample_flag = 0;
				i++;
				if ((MLA == 0 && ProcessBlock(newSampleL,history_l))|| (MLA == 1 && ProcessBlock2(newSampleL,history_l))){
					if (i >= HISTORY_SIZE-1) {
						int frame_counter = 0;
						while (frame_counter < FRAME_SIZE) {
							if (k == BUFFER_SIZE) {
								k = 0;  // Reset k when it exceeds BUFFER_SIZE
							}

							if (bufchoice == 0) {
								filteredOutBufferA[k] = ((int32_t)accumulators_16[frame_counter] << 16) + (int32_t)accumulators_16[frame_counter];
							} else {
								filteredOutBufferB[k] = ((int32_t)accumulators_16[frame_counter] << 16) + (int32_t)accumulators_16[frame_counter];
							}

							k++;
							frame_counter++;
						}


					}
				}



			}




	#ifndef FUNCTIONAL_TEST
		}
	#endif

		// once a buffer is full, we can swap to fill up the other buffer
		// this is probably not going to be used in Lab2
		if (k == BUFFER_SIZE) {
			k = 0;
			bufchoice = bufchoice == 0 ? 1 : 0;
		}

	//    if(UserPressButton == 1) {
	//    	AudioPlay_Test();
	//    	UserPressButton = 0;
	//    }
	  }
		}
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 100000000
  *            HCLK(Hz)                       = 100000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 16
  *            PLL_N                          = 400
  *            PLL_P                          = 4
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (KEY_BUTTON_PIN == GPIO_Pin)
  {
    while (BSP_PB_GetState(BUTTON_KEY) != RESET);
    UserPressButton = 1;
  }
}

/**
  * @brief  Toggle LEDs
  * @param  None
  * @retval None
  */
void Toggle_Leds(void)
{
  BSP_LED_Toggle(LED3);
  HAL_Delay(100);
//  BSP_LED_Toggle(LED4);
//  HAL_Delay(100);
  BSP_LED_Toggle(LED5);
  HAL_Delay(100);
  BSP_LED_Toggle(LED6);
  HAL_Delay(100);
}

// This timer callback should trigger every 1/8000 Hz, and it emulates
// the idea of receiving a new sample peridiocally
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

//  BSP_LED_Toggle(LED4);
//  HAL_GPIO_TogglePin(SCOPE_CHECK_GPIO_Port, SCOPE_CHECK_Pin);

	// If we "miss" processing a sample, the new_sample_flag will still be
	// high on the trigger of the interrupt
	if (new_sample_flag == 1) {
		ITM_Port32(30) = 10;
	}

	// Otherwise, go to the raw audio in memory and "retrieve" a new sample every timer period
	// set the new_sample_flag high
#ifndef FUNCTIONAL_TEST
	if (sample_count < 64000) {
		newSampleL = (int16_t)raw_audio[sample_count];
		newSampleR = (int16_t)(raw_audio[sample_count] >> 16);
		sample_count++;

		if (sample_count >= 64000) sample_count = 0;
		new_sample_flag = 1;
  }
#endif
}


int _write(int file, char* ptr, int len) {
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		ITM_SendChar(*ptr++);
	}
	return len;
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* Turn LED5 on */
  BSP_LED_On(LED5);
  while(1)
  {
  }
}

static void GPIOA_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*Configure GPIO pin : SCOPE_CHECK_Pin */
	  GPIO_InitStruct.Pin = SCOPE_CHECK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(SCOPE_CHECK_GPIO_Port, &GPIO_InitStruct);

}

static int16_t ProcessSample(int16_t newsample, int16_t* history) {

	// set the new sample as the head
	history[0] = newsample;

	// set up and do our convolution
	int tap = 0;
	int32_t accumulator = 0;
	for (tap = 0; tap < NUMBER_OF_TAPS; tap++) {
		accumulator += (int32_t)filter_coeffs[tap] * (int32_t)history[tap];
	}

	// shuffle things along for the next one?
	for(tap = NUMBER_OF_TAPS-2; tap > -1; tap--) {
		history[tap+1] = history[tap];
	}

	if (accumulator > 0x3FFFFFFF) {
		accumulator = 0x3FFFFFFF;
		overflow_count++;
	} else if (accumulator < -0x40000000) {
		accumulator = -0x40000000;
		underflow_count++;
	}

	int16_t temp = (int16_t)(accumulator >> 15);

	return temp;
}

static int16_t ProcessSampleCircular(int16_t newsample, int16_t* history) {

	// set the new sample as the head
	history[head] = newsample;

	// set up and do our convolution
	int tap = 0; // indexing filter_coeffs
	int current = head; //  indexing history array
	int32_t accumulator = 0;
	for (tap = 0, current = head; tap < NUMBER_OF_TAPS; tap++, current--) {
		current = (current + NUMBER_OF_TAPS) % NUMBER_OF_TAPS;
		accumulator += (int32_t)filter_coeffs[tap] * (int32_t)history[current];
		}

	// assign new head and tail (if buffer full)
	head = (head + 1) % NUMBER_OF_TAPS;



	if (accumulator > 0x3FFFFFFF) {
		accumulator = 0x3FFFFFFF;
		overflow_count++;
	} else if (accumulator < -0x40000000) {
		accumulator = -0x40000000;
		underflow_count++;
	}

	int16_t temp;
	if (accumulator < 1000 && accumulator > -1000) {
		temp = (int16_t)accumulator;
	} else{
		temp = (int16_t)(accumulator >> 15);
	}
	return temp;
}



static int16_t ProcessSampleCircular2(int16_t newsample, int16_t* history) {

    // set the new sample as the head
    history[head] = newsample;

    // set up and do our convolution
    int tap = 0; // indexing filter_coeffs
    int current = head; // indexing history array
    int32_t accumulator = 0;

    // unrolling the loop to process two taps at a time
    for (tap = 0; tap < (NUMBER_OF_TAPS / 2) * 2; tap += 2) {

        current = (head - tap) % NUMBER_OF_TAPS;
        int history_idx_1 = (current + NUMBER_OF_TAPS - 1) % NUMBER_OF_TAPS;
        int history_idx_2 = (current + NUMBER_OF_TAPS) % NUMBER_OF_TAPS;

        // first tap (for tap)
        __asm volatile ("SMLABB %[result1], %[op1], %[op2], %[acc1]"
                        : [result1] "=r" (accumulator)
                        : [op1] "r" ((int32_t)filter_coeffs[tap]),
                          [op2] "r" ((int32_t)history[history_idx_2]),
                          [acc1] "r" (accumulator)
                        );

        // second tap (for tap+1)
        __asm volatile ("SMLABB %[result2], %[op1], %[op2], %[acc2]"
                        : [result2] "=r" (accumulator)
                        : [op1] "r" ((int32_t)filter_coeffs[tap + 1]),
                          [op2] "r" ((int32_t)history[history_idx_1]),
                          [acc2] "r" (accumulator)
                        );
    }

    // if NUMBER_OF_TAPS is odd, process the last tap
    if (NUMBER_OF_TAPS % 2 != 0) {
        current = (current + (NUMBER_OF_TAPS - 2)) % NUMBER_OF_TAPS;
        __asm volatile ("SMLABB %[result], %[op1], %[op2], %[acc]"
                        : [result] "=r" (accumulator)
                        : [op1] "r" ((int32_t)filter_coeffs[NUMBER_OF_TAPS - 1]),
                          [op2] "r" ((int32_t)history[current]),
                          [acc] "r" (accumulator)
                        );
    }

    // assign new head and tail (if buffer full)
    head = (head + 1) % NUMBER_OF_TAPS;

    // handle overflow/underflow
    if (accumulator > 0x3FFFFFFF) {
        accumulator = 0x3FFFFFFF;
        overflow_count++;
    } else if (accumulator < -0x40000000) {
        accumulator = -0x40000000;
        underflow_count++;
    }

    // convert accumulator to int16_t
    int16_t temp;
    if (accumulator < 1000 && accumulator > -1000) {
        temp = (int16_t)accumulator;
    } else {
        temp = (int16_t)(accumulator >> 15);
    }

    return temp;
}

static int  ProcessBlock(int16_t newsample, int16_t* history) {

	history[head] = newsample;
	if (samples_since_last_frame++ < FRAME_SIZE - 1 ){
		head = (head + 1) % HISTORY_SIZE;

		return false;
		// returning false means that there are not enough samples to for the frame to be processed
	}
	samples_since_last_frame = 0;


	// processing the frame
	int tap, current;
	int32_t accumulators [FRAME_SIZE] = {0}; // accumulator[2] corresponds to the newest sample
	for (tap = 0, current = head; tap < NUMBER_OF_TAPS; tap++, current--) {
			int32_t coeff = (int32_t)filter_coeffs[tap]; // loading the coefficient once

			int base_idx = (current - MAX_FRAME_IDX + HISTORY_SIZE) % HISTORY_SIZE;

			for (int i = 0; i < FRAME_SIZE; i++){
				int history_idx = (base_idx + i) % HISTORY_SIZE;
				accumulators[i] += coeff * (int32_t)history[history_idx];
			}

			}


	head = (head + 1) % HISTORY_SIZE; // moving the head


	for (int i = 0; i < FRAME_SIZE; i++){
		if (accumulators[i] > 0x3FFFFFFF) {
				accumulators[i]= 0x3FFFFFFF;
				overflow_count++;
			} else if (accumulators[i] < -0x40000000) {
				accumulators[i] = -0x40000000;
				underflow_count++;
			}

		if (accumulators[i] < 1000 && accumulators[i] > -1000) {
			accumulators_16[i] = (int16_t)accumulators[i];
		} else{
			accumulators_16[i]= (int16_t)(accumulators[i] >> 15);
		}


	}


	return true;


}



static int ProcessBlock2(int16_t newsample, int16_t* history) {
    // Set the new sample as the head
    history[head] = newsample;

    if (samples_since_last_frame++ < FRAME_SIZE - 1) {
        head = (head + 1) % HISTORY_SIZE;
        return false;
    }

    samples_since_last_frame = 0;

    // Processing the frame
    int current = head;
    int32_t accumulators[FRAME_SIZE] = {0};  // accumulator[2] corresponds to the newest sample
    int tap;

    // Unrolling the outer loop to process multiple taps at once
    for (tap = 0; tap < (NUMBER_OF_TAPS / 2) * 2; tap += 2, current-=2) {
        int32_t coeff1 = (int32_t)filter_coeffs[tap];     // First tap coefficient
        int32_t coeff2 = (int32_t)filter_coeffs[tap + 1]; // Second tap coefficient
		current = (current + HISTORY_SIZE) % HISTORY_SIZE;

        int base_idx = (current - FRAME_SIZE + HISTORY_SIZE) % HISTORY_SIZE;

        for (int i = 0; i < FRAME_SIZE; i++) {
            int history_idx_1 = (base_idx + i) % HISTORY_SIZE;
            int history_idx_2 = (base_idx + i + 1) % HISTORY_SIZE;

            // Separate the assembly instructions for each tap
            __asm volatile(
                "SMLABB %[result1], %[op1], %[op2], %[acc1];"
                : [result1] "=r" (accumulators[i])
                : [op1] "r" (coeff1),
                  [op2] "r" ((int32_t)history[history_idx_2]),
                  [acc1] "r" (accumulators[i])
            );

            __asm volatile(
                "SMLABB %[result2], %[op1], %[op2], %[acc2];"
                : [result2] "=r" (accumulators[i])
                : [op1] "r" (coeff2),
                  [op2] "r" ((int32_t)history[history_idx_1]),
                  [acc2] "r" (accumulators[i])
            );
        }
    }

    // If NUMBER_OF_TAPS is odd, process the last tap
    if (NUMBER_OF_TAPS % 2 != 0) {
        int32_t coeff = (int32_t)filter_coeffs[NUMBER_OF_TAPS - 1];
        int base_idx = (current - MAX_FRAME_IDX + HISTORY_SIZE) % HISTORY_SIZE;

        for (int i = 0; i < FRAME_SIZE; i++) {
            int history_idx = (base_idx + i) % HISTORY_SIZE;

            // Accumulate for the last tap
            __asm volatile(
                "SMLABB %[result], %[op1], %[op2], %[acc];"
                : [result] "=r" (accumulators[i])
                : [op1] "r" (coeff),
                  [op2] "r" ((int32_t)history[history_idx]),
                  [acc] "r" (accumulators[i])
            );
        }
    }

    // Moving the head to the next position
    head = (head + 1) % HISTORY_SIZE;

    // Handling overflow/underflow and updating the accumulator values
    for (int i = 0; i < FRAME_SIZE; i++) {
        if (accumulators[i] > 0x3FFFFFFF) {
            accumulators[i] = 0x3FFFFFFF;
            overflow_count++;
        } else if (accumulators[i] < -0x40000000) {
            accumulators[i] = -0x40000000;
            underflow_count++;
        }

        if (accumulators[i] < 1000 && accumulators[i] > -1000) {
            accumulators_16[i] = (int16_t)accumulators[i];
        } else {
            accumulators_16[i] = (int16_t)(accumulators[i] >> 15);
        }
    }

    return true;
}


/*

RunTestMode() and main() share the same logic but differ in input handling.
It uses predefined test inputs for controlled testing.

 */

static void RunTestMode() {
    static int i = 0;
    static int k = 0;
    int fail = 0;

    if (CONFIG_MODE == 0 || CONFIG_MODE == 1) {
        int16_t test_inputs[] = {10, 20, 30, 10, 20, 30, 10, 20, 30, 10};
        int16_t expected_outputs[] = {400, 700, 700, 400, 700, 700, 400, 700};
        int16_t test_outputs[BUFFER_SIZE];

        while (k < BUFFER_SIZE) {
            newSampleL = test_inputs[i];

            if (MLA == 0) {
                filteredSampleL = ProcessSampleCircular(newSampleL, history_l);
            } else {
                filteredSampleL = ProcessSampleCircular2(newSampleL, history_l);
            }

            if (i < NUMBER_OF_TAPS - 1) {
                filteredSampleL = 0;
                i++;
            } else {
                test_outputs[k] = filteredSampleL;
                k++;
                i++;
            }
        }


        // Verify test outputs
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (test_outputs[j] != expected_outputs[j]) {
                fail++;
            }
        }
        if (fail>0){
        	printf("\nTest failed.\n");

        }else{
        	printf("\nTest passed.\n");
        }


    } else {
    	 int16_t test_inputs[] = {10, 20, 30, 10, 20, 30, 10, 20, 30, 10, 20};
    	 int16_t expected_outputs[] = {400, 700, 700, 400, 700, 700, 400, 700, 700};
    	 int16_t test_outputs[BUFFER_SIZE];

    	while (k < BUFFER_SIZE){
            newSampleL = test_inputs[i];
            i++;

			if ((MLA == 0 && ProcessBlock(newSampleL,history_l))|| (MLA == 1 && ProcessBlock2(newSampleL,history_l))){
				if (i >= HISTORY_SIZE-1){

					int frame_counter = 0;
					while (frame_counter < FRAME_SIZE) {


						test_outputs[k] = accumulators_16[frame_counter];

						k++;
						frame_counter++;
					}


				}
			}


    	}

    	// Verify test outputs
    	for (int j = 0; j < BUFFER_SIZE; j++) {
    	        if (test_outputs[j] != expected_outputs[j]) {
    	                fail++;
    	            }
    	        }
    	        if (fail>0){
    	        	printf("\nTest failed.\n");

    	        }else{
    	        	printf("\nTest passed.\n");
    	        }

		}
    while (1)
      {
    	//infinite loop to "stop" the code from running further
      }

}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
