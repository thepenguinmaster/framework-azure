/*
 * (C) 2005-2019 MediaTek Inc. All rights reserved.
 *
 * Copyright Statement:
 *
 * This MT3620 driver software/firmware and related documentation
 * ("MediaTek Software") are protected under relevant copyright laws.
 * The information contained herein is confidential and proprietary to
 * MediaTek Inc. ("MediaTek"). You may only use, reproduce, modify, or
 * distribute (as applicable) MediaTek Software if you have agreed to and been
 * bound by this Statement and the applicable license agreement with MediaTek
 * ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User"). If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE
 * PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS
 * ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO
 * LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED
 * HEREUNDER WILL BE ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY
 * RECEIVER TO MEDIATEK DURING THE PRECEDING TWELVE (12) MONTHS FOR SUCH
 * MEDIATEK SOFTWARE AT ISSUE.
 */


#ifndef __MHAL_ADC_H__
#define __MHAL_ADC_H__

#include "mhal_osai.h"

/**
 * @addtogroup M-HAL
 * @{
 * @addtogroup ADC
 * @{
 * This section describes the programming interfaces of the Analog-to-Digital
 * Converter (ADC) M-HAL driver, including terms and acronyms,
 * supported features, software architecture, details on how to
 * use this driver, ADC define, enums, functions, structures and typedef.
 *
 * @section MHAL_ADC_Terms_Chapter Terms and Acronyms
 *
 * |Terms		   |Details		|
 * |------------|-------------------------------------|
 * |\b ADC		 | ADC is an Analog-to-Digital Converter.|
 * |\b DMA		 | Direct Memory Access.|
 * |\b FIFO		 | First In, First Out.|
 *
 * @section MHAL_ADC_Features_Chapter Supported Features
 * The ADC is a Successive Approximation ADC and the resolution
 * of ADC is 12 bits.
 * - \b One \b Shot \b Mode: \n
 *   Get sample data using One shot mode.
 *
 * - \b Period \b Mode: \n
 *   Get sample data using Period mode.
 *
 * - \b DMA \b Node: \n
 *   Get sample data using DMA mode.
 *
 * @}
 * @}
 */

/**
 * @addtogroup M-HAL
 * @{
 * @addtogroup ADC
 * @{
 * @section MHAL_ADC_Driver_Usage_Chapter How to Use This Driver
 * - \b SW \b Architecture: \n
 *	See @ref MHAL_Overview_2_Chapter for details of the SW architecture.
 *	This section describes the definition of APIs and provides
 *	an example on FreeRTOS to show how to use these APIs to develop
 *	an OS-related driver.\n
 * - \b The \b OS-HAL \b FreeRTOS \b driver\n
 * \b sample \b code \b is \b as \b follows:\n
 *	- sample code (FreeRTOS doesn't have ADC framework,
 * so this sample code provides APIs to user application):
 *	  @code
 *	#define CM4_ADC_BASE					 0x38000000
 *	#define CM4_ADC_TOPCFGAON_CLK_RG		 0x30030208
 *
 *	struct mtk_adc_controller_rtos {
 *		struct mtk_adc_controller *	ctlr;
 *		QueueHandle_t rx_completion;
 *	};
 *	static struct adc_fsm_param adc_fsm_parameter;
 *
 *	static struct mtk_adc_controller adc_controller;
 *
 *	static struct mtk_adc_controller_rtos g_adc_ctlr_rtos;
 *
 *	static struct mtk_adc_controller_rtos *	_mtk_os_hal_adc_get_ctlr(void)
 *	{
 *			return &g_adc_ctlr_rtos;
 *	}
 *
 *	static int _mtk_os_hal_adc_config_gpio(void)
 *	{
 *		int ret = 0;
 *
 *		ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_41);
 *		if (ret != 0)
 *			  OS_DEBUG("request gpio[%d] fail\n",
 *				  OS_HAL_GPIO_41);
 *		ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_41,
 *					  OS_HAL_MODE_0);
 *		ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_41,
 *					  OS_HAL_GPIO_DIR_INPUT);
 *		if (ret != 0)
 *			  OS_DEBUG("config gpio[%d] fail\n",
 *				  OS_HAL_GPIO_41);
 *		ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_42);
 *		if (ret != 0)
 *			  OS_DEBUG("request gpio[%d] fail\n",
 *				  OS_HAL_GPIO_42);
 *		ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_42,
 *					  OS_HAL_MODE_0);
 *		ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_42,
 *					  OS_HAL_GPIO_DIR_INPUT);
 *		if (ret != 0)
 *			  OS_DEBUG("config gpio[%d] fail\n",
 *				  OS_HAL_GPIO_42);
 *		ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_43);
 *		if (ret != 0)
 *			  OS_DEBUG("request gpio[%d] fail\n",
 *				  OS_HAL_GPIO_43);
 *		ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_43,
 *					  OS_HAL_MODE_0);
 *		ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_43,
 *					  OS_HAL_GPIO_DIR_INPUT);
 *		if (ret != 0)
 *			  OS_DEBUG("config gpio[%d] fail\n",
 *				  OS_HAL_GPIO_43);
 *		ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_44);
 *		if (ret != 0)
 *			  OS_DEBUG("request gpio[%d] fail\n",
 *				  OS_HAL_GPIO_44);
 *		ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_44,
 *					  OS_HAL_MODE_0);
 *		ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_44,
 *					  OS_HAL_GPIO_DIR_INPUT);
 *		if (ret != 0)
 *			  OS_DEBUG("config gpio[%d] fail\n",
 *				  OS_HAL_GPIO_44);
 *		ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_45);
 *		if (ret != 0)
 *			  OS_DEBUG("request gpio[%d] fail\n",
 *				  OS_HAL_GPIO_45);
 *		ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_45,
 *					  OS_HAL_MODE_0);
 *		ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_45,
 *					  OS_HAL_GPIO_DIR_INPUT);
 *		if (ret != 0)
 *			  OS_DEBUG("config gpio[%d] fail\n",
 *				  OS_HAL_GPIO_45);
 *		ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_46);
 *		if (ret != 0)
 *			  OS_DEBUG("request gpio[%d] fail\n",
 *				  OS_HAL_GPIO_46);
 *		ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_46,
 *					  OS_HAL_MODE_0);
 *		ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_46,
 *					  OS_HAL_GPIO_DIR_INPUT);
 *		if (ret != 0)
 *			  OS_DEBUG("config gpio[%d] fail\n",
 *				  OS_HAL_GPIO_46);
 *		ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_47);
 *		if (ret != 0)
 *			  OS_DEBUG("request gpio[%d] fail\n",
 *				  OS_HAL_GPIO_47);
 *		ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_47,
 *					  OS_HAL_MODE_0);
 *		ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_47,
 *					  OS_HAL_GPIO_DIR_INPUT);
 *		if (ret != 0)
 *			  OS_DEBUG("config gpio[%d] fail\n",
 *				  OS_HAL_GPIO_47);
 *		ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_48);
 *		if (ret != 0)
 *			  OS_DEBUG("request gpio[%d] fail\n",
 *				  OS_HAL_GPIO_48);
 *		ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_48,
 *					  OS_HAL_MODE_0);
 *		ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_48,
 *					  OS_HAL_GPIO_DIR_INPUT);
 *		if (ret != 0)
 *			  OS_DEBUG("config gpio[%d] fail\n",
 *				  OS_HAL_GPIO_48);
 *
 *		return ret;
 *	}
 *
 *	static int _mtk_os_hal_adc_release_gpio(void)
 *	{
 *		int ret = 0;
 *
 *		ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_41);
 *		if (ret != 0)
 *			  OS_DEBUG("release gpio[%d] fail\n",
 *				  OS_HAL_GPIO_41);
 *		ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_42);
 *		if (ret != 0)
 *			  OS_DEBUG("release gpio[%d] fail\n",
 *				  OS_HAL_GPIO_42);
 *		ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_43);
 *		if (ret != 0)
 *			  OS_DEBUG("release gpio[%d] fail\n",
 *				  OS_HAL_GPIO_43);
 *		ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_44);
 *		if (ret != 0)
 *			  OS_DEBUG("release gpio[%d] fail\n",
 *				  OS_HAL_GPIO_44);
 *		ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_45);
 *		if (ret != 0)
 *			  OS_DEBUG("release gpio[%d] fail\n",
 *				  OS_HAL_GPIO_45);
 *		ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_46);
 *		if (ret != 0)
 *			  OS_DEBUG("release gpio[%d] fail\n",
 *				  OS_HAL_GPIO_46);
 *		ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_47);
 *		if (ret != 0)
 *			  OS_DEBUG("release gpio[%d] fail\n",
 *				  OS_HAL_GPIO_47);
 *		ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_48);
 *		if (ret != 0)
 *			  OS_DEBUG("release gpio[%d] fail\n",
 *				  OS_HAL_GPIO_48);
 *
 *		return ret;
 *	}
 *
 *	static int _mtk_os_hal_adc_irq_handler(struct mtk_adc_controller *
 *		ctlr)
 *	{
 *		if (!ctlr)
 *			  return -EPTR;
 *
 *		if (ctlr->adc_fsm_parameter->fifo_mode != ADC_FIFO_DIRECT)
 *			  return -EPARAMETER;
 *
 *		mtk_mhal_adc_fifo_handle_rx(ctlr);
 *
 *		return 0;
 *	}
 *
 *	static void _mtk_os_hal_adc_irq_event(void)
 *	{
 *		struct mtk_adc_controller_rtos *	ctlr_rtos =
 *			  _mtk_os_hal_adc_get_ctlr();
 *		struct mtk_adc_controller *	ctlr;
 *
 *		ctlr = ctlr_rtos->ctlr;
 *		_mtk_os_hal_adc_irq_handler(ctlr);
 *
 *	}
 *
 *	static int _mtk_os_hal_adc_request_irq(struct mtk_adc_controller *
 *			ctlr)
 *	{
 *		if (!ctlr)
 *			  return -EPTR;
 *
 *		CM4_Install_NVIC(CM4_IRQ_ADC, CM4_ADC_PRI, IRQ_LEVEL_TRIGGER,
 *			  _mtk_os_hal_adc_irq_event, TRUE);
 *
 *		return 0;
 *	}
 *
 *	static int _mtk_os_hal_adc_wait_for_completion_timeout(
 *					  struct mtk_adc_controller_rtos
 *					  *	ctlr_rtos, int time_ms)
 *	{
 *		if (pdTRUE != xSemaphoreTake(ctlr_rtos->rx_completion,
 *						   time_ms / portTICK_RATE_MS))
 *			  return -1;
 *
 *		return 0;
 *	}
 *
 *	static int _mtk_os_hal_adc_rx_done_callback(void *	data)
 *	{
 *		BaseType_t x_higher_priority_task_woken = pdFALSE;
 *		struct mtk_adc_controller_rtos *	ctlr_rtos = data;
 *
 *		xSemaphoreGiveFromISR(ctlr_rtos->rx_completion,
 *						&x_higher_priority_task_woken);
 *		portYIELD_FROM_ISR(x_higher_priority_task_woken);
 *
 *		return 0;
 *	}
 *
 *	int mtk_os_hal_adc_ctlr_init(adc_pmode pmode, adc_fifo_mode fifo_mode,
 *		u16 bit_map)
 *	{
 *		struct mtk_adc_controller_rtos *	ctlr_rtos;
 *		struct mtk_adc_controller *	ctlr;
 *		u32 channel_index = 0;
 *		int ret = 0;
 *
 *		ctlr_rtos = _mtk_os_hal_adc_get_ctlr();
 *		if (!ctlr_rtos)
 *			  return -EPTR;
 *
 *		if ((pmode != ADC_PMODE_ONE_TIME) &&
 *			(pmode != ADC_PMODE_PERIODIC))
 *			  return -EPARAMETER;
 *
 *		if ((fifo_mode != ADC_FIFO_DIRECT) &&
 *			(fifo_mode != ADC_FIFO_DMA))
 *			return -EPARAMETER;
 *
 *		ctlr_rtos->ctlr = &adc_controller;
 *
 *		if (!ctlr_rtos->ctlr)
 *			  return -EPTR;
 *
 *		ctlr = ctlr_rtos->ctlr;
 *
 *		ctlr->adc_fsm_parameter = &adc_fsm_parameter;
 *
 *		ctlr->base = (void __iomem *	)CM4_ADC_BASE;
 *		ctlr->cg_base = (void __iomem *	)CM4_ADC_TOPCFGAON_CLK_RG;
 *
 *		ret = _mtk_os_hal_adc_config_gpio();
 *		if (ret)
 *			  return ret;
 *
 *		ret = mtk_mhal_adc_enable_clk(ctlr);
 *		if (ret)
 *			  return ret;
 *
 *		ctlr->adc_fsm_parameter->pmode = pmode;
 *		ctlr->adc_fsm_parameter->avg_mode = ADC_AVG_32_SAMPLE;
 *		ctlr->adc_fsm_parameter->channel_map = bit_map;
 *		ctlr->adc_fsm_parameter->period = PMODE_PERIOD;
 *		ctlr->adc_fsm_parameter->fifo_mode = fifo_mode;
 *		ctlr->adc_fsm_parameter->ier_mode = ADC_FIFO_IER_RXFULL;
 *		if (ctlr->adc_fsm_parameter->fifo_mode == ADC_FIFO_DMA) {
 *			  ctlr->adc_fsm_parameter->dma_vfifo_len =
 *			  ADC_DMA_BUF_WORD_SIZE;
 *
 *			  ctlr->dma_channel = VDMA_ADC_RX_CH29;
 *			  ctlr->use_dma = 1;
 *			  OS_DEBUG("dma_vfifo_len == %d\n",
 *				  ctlr->adc_fsm_parameter->dma_vfifo_len);
 *			  OS_DEBUG("dma_vfifo_addr == %p\n",
 *				  ctlr->adc_fsm_parameter->dma_vfifo_addr);
 *		}
 *		OS_DEBUG("mtk os_hal_adc_ctlr_init ctlr->rx_buf == %p\n",
 *			  ctlr->rx_buf);
 *
 *		for (channel_index = 0; channel_index < ADC_CHANNEL_MAX;
 *				  channel_index++) {
 *			  ctlr->current_xfer[channel_index].count = 0;
 *			  ctlr->current_xfer[channel_index].write_point = 0;
 *			  ctlr->current_xfer[channel_index].read_point = 0;
 *		}
 *
 *		ret = mtk_mhal_adc_init(ctlr);
 *		if (ret)
 *			  return ret;
 *
 *		if (fifo_mode == ADC_FIFO_DIRECT) {
 *			  ctlr->use_dma = 0;
 *			  ret = _mtk_os_hal_adc_request_irq(ctlr);
 *			  if (ret)
 *				  return ret;
 *		}
 *		if (!ctlr_rtos->rx_completion)
 *			  ctlr_rtos->rx_completion = xSemaphoreCreateBinary();
 *
 *		ret = mtk_mhal_adc_rx_notify_callback_register(ctlr,
 *				_mtk_os_hal_adc_rx_done_callback,
 *				(void *	)ctlr_rtos);
 *		if (ret)
 *			  return ret;
 *
 *		ret = mtk_mhal_adc_fsm_param_set(ctlr, ctlr->adc_fsm_parameter);
 *		if (ret)
 *			  return ret;
 *
 *		if (ctlr->adc_fsm_parameter->pmode == ADC_PMODE_ONE_TIME) {
 *			  ret = mtk_mhal_adc_start_ch(ctlr_rtos->ctlr,
 *				  ctlr->adc_fsm_parameter->channel_map);
 *			  if (ret)
 *				  return ret;
 *		}
 *		OS_DEBUG("mtk os_hal_adc_ctlr_init success\n");
 *
 *		return ret;
 *	}
 *
 *	int mtk_os_hal_adc_start(void)
 *	{
 *		struct mtk_adc_controller_rtos *	ctlr_rtos =
 *			  _mtk_os_hal_adc_get_ctlr();
 *
 *		if (!ctlr_rtos)
 *			  return -EPTR;
 *
 *		return mtk_mhal_adc_start(ctlr_rtos->ctlr);
 *	}
 *
 *	int mtk_os_hal_adc_start_ch(u16 ch_bit_map)
 *	{
 *		struct mtk_adc_controller_rtos *	ctlr_rtos =
 *			  _mtk_os_hal_adc_get_ctlr();
 *
 *		if (!ctlr_rtos)
 *			  return -EPTR;
 *
 *		 return mtk_mhal_adc_start_ch(ctlr_rtos->ctlr, ch_bit_map);
 *	}
 *
 *	int mtk_os_hal_adc_ctlr_deinit(void)
 *	{
 *		int ret = 0;
 *		struct mtk_adc_controller_rtos *	ctlr_rtos =
 *			  _mtk_os_hal_adc_get_ctlr();
 *
 *		if (!ctlr_rtos)
 *			  return -EPTR;
 *
 *		if (!ctlr_rtos->ctlr)
 *			  return -EPTR;
 *
 *		if (ctlr_rtos->ctlr->adc_fsm_parameter->fifo_mode ==
 *			ADC_FIFO_DIRECT) {
 *			  NVIC_DisableIRQ((IRQn_Type)CM4_IRQ_ADC);
 *		}
 *		ret = mtk_mhal_adc_stop(ctlr_rtos->ctlr);
 *		if (ret)
 *			  return ret;
 *
 *		ret = mtk_mhal_adc_deinit(ctlr_rtos->ctlr);
 *		if (ret)
 *			  return ret;
 *
 *		ret = mtk_mhal_adc_disable_clk(ctlr_rtos->ctlr);
 *		if (ret)
 *			  return ret;
 *
 *		ret = _mtk_os_hal_adc_release_gpio();
 *		if (ret)
 *			  return ret;
 *
 *		return 0;
 *	}
 *
 *	int mtk_os_hal_adc_fsm_param_set(struct adc_fsm_param *
 *		adc_fsm_parameter)
 *	{
 *		struct mtk_adc_controller_rtos *	ctlr_rtos;
 *		struct mtk_adc_controller *	ctlr;
 *		u32 channel_index = 0;
 *		int ret = 0;
 *
 *		ctlr_rtos = _mtk_os_hal_adc_get_ctlr();
 *		if (!ctlr_rtos)
 *			  return -EPTR;
 *
 *		ctlr = ctlr_rtos->ctlr;
 *
 *		ctlr->adc_fsm_parameter->pmode = adc_fsm_parameter->pmode;
 *		ctlr->adc_fsm_parameter->avg_mode = adc_fsm_parameter->avg_mode;
 *		ctlr->adc_fsm_parameter->channel_map =
 *			adc_fsm_parameter->channel_map;
 *		ctlr->adc_fsm_parameter->period = adc_fsm_parameter->period;
 *		ctlr->adc_fsm_parameter->fifo_mode =
 *			adc_fsm_parameter->fifo_mode;
 *		ctlr->adc_fsm_parameter->ier_mode = adc_fsm_parameter->ier_mode;
 *
 *		if (ctlr->adc_fsm_parameter->fifo_mode == ADC_FIFO_DMA) {
 *			  ctlr->adc_fsm_parameter->dma_vfifo_len =
 *			  ADC_DMA_BUF_WORD_SIZE;
 *			  OS_DEBUG("dma_vfifo_len == %d\n",
 *				  ctlr->adc_fsm_parameter->dma_vfifo_len);
 *			  OS_DEBUG("dma_vfifo_addr == %p\n",
 *				  ctlr->adc_fsm_parameter->dma_vfifo_addr);
 *		}
 *
 *		for (channel_index = 0; channel_index < ADC_CHANNEL_MAX;
 *			  channel_index++) {
 *			  ctlr->current_xfer[channel_index].count = 0;
 *			  ctlr->current_xfer[channel_index].write_point = 0;
 *			  ctlr->current_xfer[channel_index].read_point = 0;
 *		}
 *
 *		ret = mtk_mhal_adc_fsm_param_set(ctlr, adc_fsm_parameter);
 *		if (ret)
 *			  return ret;
 *
 *		return 0;
 *	}
 *
 *	int mtk_os_hal_adc_one_shot_get_data(adc_channel sample_channel,
 *		u32 *	data)
 *	{
 *		struct mtk_adc_controller_rtos *	ctlr_rtos;
 *		struct mtk_adc_controller *	ctlr;
 *		int ret = 0;
 *
 *		ctlr_rtos = _mtk_os_hal_adc_get_ctlr();
 *		if (!ctlr_rtos)
 *			  return -EPTR;
 *
 *		ctlr = ctlr_rtos->ctlr;
 *
 *		if ((ctlr == NULL) || (ctlr->adc_fsm_parameter == NULL))
 *			return -EPTR;
 *
 *		if (sample_channel > ADC_CHANNEL_7)
 *			return -EPARAMETER;
 *
 *		if ((ctlr->adc_fsm_parameter->pmode != ADC_PMODE_ONE_TIME) ||
 *			(ctlr->adc_fsm_parameter->fifo_mode != ADC_FIFO_DIRECT))
 *			return -EPARAMETER;
 *
 *		OS_DEBUG("sample_channel->%d data point:%p\n",
 *			sample_channel, data);
 *
 *		ret = mtk_mhal_adc_one_shot_get_data(ctlr_rtos->ctlr,
 *		sample_channel, data);
 *		if (ret)
 *			return ret;
 *
 *		OS_DEBUG("one_shot_get_data sample_channel:->%d, data:%d\n",
 *			sample_channel, *	data);
 *
 *		return 0;
 *	}
 *
 *	int mtk_os_hal_adc_period_get_data(adc_channel sample_channel)
 *	{
 *		struct mtk_adc_controller_rtos *	ctlr_rtos;
 *		struct mtk_adc_controller *	ctlr;
 *		int ret = 0;
 *
 *		ctlr_rtos = _mtk_os_hal_adc_get_ctlr();
 *		if (!ctlr_rtos)
 *			return -EPTR;
 *
 *		ctlr = ctlr_rtos->ctlr;
 *		if ((ctlr == NULL) || (ctlr->adc_fsm_parameter == NULL))
 *			return -EPTR;
 *
 *		ret = mtk_mhal_adc_start(ctlr_rtos->ctlr);
 *		if (ret)
 *			return ret;
 *
 *		ret = _mtk_os_hal_adc_wait_for_completion_timeout(ctlr_rtos,
 *			1000);
 *		if (ret)
 *			OS_DEBUG("Take adc master Semaphore timeout!\n");
 *
 *		ret = mtk_mhal_adc_period_get_data(ctlr, sample_channel);
 *		if (ret)
 *			return ret;
 *
 *		ret = mtk_mhal_adc_stop(ctlr);
 *		if (ret)
 *			return ret;
 *
 *		if (ctlr->adc_fsm_parameter->fifo_mode == ADC_FIFO_DMA) {
 *			ret = mtk_mhal_adc_stop_dma(ctlr);
 *			if (ret)
 *				return ret;
 *		}
 *
 *		return 0;
 *	}
 *	@endcode
 *
 * - \b How \b to \b develop \b user \b application \b by \b using
 *    \b OS-HAL \b API: \n
 *  - sample code (this is the user application sample code on freeRTos):
 *	  @code
 *
 *    - ADC one shot mode:
 *      -Call mtk_os_hal_adc_ctlr_init() to initialize the ADC module.
 *      -Call mtk_os_hal_adc_fsm_param_set() to set one shot state
 *        machine parameters.
 *      -Call mtk_os_hal_adc_start() or mtk_os_hal_adc_start_ch() to start
 *        the ADC module.
 *      -Call mtk_os_hal_adc_one_shot_get_data() to retrieve
 *        sample data for a channel.
 *      -ADC hw is no longer in use, call mtk_os_hal_adc_ctlr_deinit() to return
 *        the ADC module back to its original state.
 *
 *    - ADC fifo mode:
 *      -Call mtk_os_hal_adc_ctlr_init() to initialize the ADC module.
 *      -Call mtk_os_hal_adc_fsm_param_set() to set fifo state
 *        machine parameters.
 *      -Call mtk_os_hal_adc_start() or mtk_os_hal_adc_start_ch() to start
 *        the ADC module.
 *      -Call mtk_os_hal_adc_period_get_data() to retrieve
 *        sample data for a channel.
 *      -Call mtk_os_hal_adc_stop() to stop ADC HW.
 *      -ADC hw is no longer in use, call mtk_os_hal_adc_ctlr_deinit() to return
 *        the ADC module back to its original state.
 *
 *    - ADC dma mode:
 *      -Call mtk_os_hal_adc_ctlr_init() to initialize the ADC module.
 *      -Call mtk_os_hal_adc_fsm_param_set() to set dma state
 *        machine parameters.
 *      -Call mtk_os_hal_adc_start() or mtk_os_hal_adc_start_ch() to start
 *        the ADC module.
 *      -Call mtk_os_hal_adc_period_get_data() to retrieve
 *        sample data for a channel.
 *      -ADC hw is no longer in use, call mtk_os_hal_adc_ctlr_deinit() to return
 *        the ADC module back to its original state.
 *	@endcode
 *
 * @}
 * @}
 */
/**
  * @addtogroup M-HAL
  * @{
  * @addtogroup ADC
  * @{
  */
/** @defgroup driver_adc_def Define
 * @{
 * M-HAL ADC define list information, including maximum channel
 *	number that ADC supports, ADC ring buffer size and error return value.
 */

#define EPTR		1
/**< Invalid argument, it means the pointer is NULL */
#define EPARAMETER	2
/**< Invalid argument, it means the parameter invalid */
#define ENOMEM		3
/**< Out of memory, it means memory malloc fail */
#define EFAULT		4
/**< Bad address */
#define EAGAIN		5
/**< Try again */

#define ADC_CH_ID_MASK  (BIT(0)|BIT(1)|BIT(2)|BIT(3))
/**< ADC channel id mask*/
#define ADC_DATA_MASK  (BITS(4, 15))
/**< ADC sample data mask*/
#define ADC_DATA_BIT_OFFSET     4
/**< ADC sample data bit offset*/

#define PMODE_PERIOD            16000
/**< clock cycle count period in periodic mode*/

#define ADC_RING_BUF_SIZE   32
/**< ADC ring buffer size */
#define ADC_DMA_BUF_WORD_SIZE  64
/**< ADC DMA buffer size */

/**
  *@}
  */

/***************************************************************************
   * enums
   **************************************************************************/
/** @defgroup driver_adc_enum Enum
  * @{
  *	M-HAL ADC enumeration define list information, including
  *	define of the ADC one shot or periodic mode enumeration,
  *	define of the ADC finite state machine sampling times enumeration,
  *	define of the ADC operation mode enumeration(FIFO or DMA mode),
  *	define of the ADC channel number enumeration,
  *	define of the ADC dither function steps enumeration and
  *	define of the ADC enumeration DMA Rx status.
  */
 /** @brief This enum defines ADC one shot or periodic mode */
typedef enum {
	ADC_PMODE_ONE_TIME = 0,
	/**< ADC one shot mode*/
	ADC_PMODE_PERIODIC
	/**< ADC periodic mode*/
} adc_pmode;

 /** @brief This enum defines ADC finite state machine sampling times */
typedef enum {
	ADC_AVG_1_SAMPLE = 0,
	/**< ADC state machine samples 1 time*/
	ADC_AVG_2_SAMPLE,
	/**< ADC state machine samples 2 times*/
	ADC_AVG_4_SAMPLE,
	/**< ADC state machine samples 4 times*/
	ADC_AVG_8_SAMPLE,
	/**< ADC state machine samples 8 times*/
	ADC_AVG_16_SAMPLE,
	/**< ADC state machine samples 16 times*/
	ADC_AVG_32_SAMPLE,
	/**< ADC state machine samples 32 times*/
	ADC_AVG_64_SAMPLE
	/**< ADC state machine samples 64 times*/
} adc_avg_mode;

 /** @brief This enum defines ADC operation mode: FIFO or DMA mode */
typedef enum {
	ADC_FIFO_DIRECT = 0,
	/**< ADC FIFO sample*/
	ADC_FIFO_DMA
	/**< ADC DMA sample*/
} adc_fifo_mode;

/** @brief This enum defines ADC dither function steps*/
typedef enum {
	ADC_FIFO_IER_BOTH = 0,
	/**< ADC rxfull and  timeout interrupt enable */
	ADC_FIFO_IER_RXFULL,
	/**< ADC rxfull interrupt enable */
	ADC_FIFO_IER_TIMEOUT
	/**< ADC timeout interrupt enable */
} adc_fifo_ier_mode;

/** @brief This enum defines ADC DMA Rx status*/
typedef enum  {
	ADC_DMA_RX_START = 0,
	/**< ADC DMA rxstart */
	ADC_DMA_RX_RUNNING = 1,
	/**< ADC DMA rxrunning */
	ADC_DMA_RX_SHUTDOWN = 2
	/**< ADC DMA rxshutdown */
} adc_dma_rx_status;

/** @brief This enum defines ADC channel bit map*/
typedef enum {
	ADC_BIT0 = 0x0001,
	/**< ADC channel0 bit map*/
	ADC_BIT1 = 0x0002,
	/**< ADC channel1 bit map*/
	ADC_BIT2 = 0x0004,
	/**< ADC channel2 bit map*/
	ADC_BIT3 = 0x0008,
	/**< ADC channel3 bit map*/
	ADC_BIT4 = 0x0010,
	/**< ADC channel4 bit map*/
	ADC_BIT5 = 0x0020,
	/**< ADC channel5 bit map*/
	ADC_BIT6 = 0x0040,
	/**< ADC channel6 bit map*/
	ADC_BIT7 = 0x0080,
	/**< ADC channel7 bit map*/
} adc_channel_bit_map;

/** @brief This enum defines ADC channel number*/
typedef enum {
	ADC_CHANNEL_0 = 0,
	/**< ADC channel 0 */
	ADC_CHANNEL_1 = 1,
	/**< ADC channel 1 */
	ADC_CHANNEL_2 = 2,
	/**< ADC channel 2 */
	ADC_CHANNEL_3 = 3,
	/**< ADC channel 3 */
	ADC_CHANNEL_4 = 4,
	/**< ADC channel 4 */
	ADC_CHANNEL_5 = 5,
	/**< ADC channel 5*/
	ADC_CHANNEL_6 = 6,
	/**< ADC channel 6*/
	ADC_CHANNEL_7 = 7,
	/**< ADC channel 7*/
	ADC_CHANNEL_MAX
	/**< ADC max channel(invalid) */
} adc_channel;

/**
  * @}
  */

/** @defgroup driver_adc_typedef Typedef
  * @{
  *	M-HAL ADC typedef define list information, including
  *	define of the ADC OS-HAL user's callback API typedef.
  */

/** @brief	 This function is used to register user's callback to M-HAL.
 *	It's used for Rx transaction.
 *	While receiving expected data, an Rx interrupt is triggered and
 *	this callback is called in the interrupt service routine.
 *
 * @param [in] callback_param: An OS-HAL defined parameter provided
 *	by #mtk_mhal_adc_rx_notify_callback_register().
 * @return
 *	If return value is 0 , the callback API registers successfully.\n
 *	If return value is -#EPTR , it means ctlr is NULL.
 */
typedef int (*adc_rx_done_callback) (void *callback_param);

/**
  * @}
  */
/** @defgroup driver_adc_struct Struct
  * @{
  *	M-HAL ADC structure list information, including
  *	ADC controller state machine related parameters,
  *	ADC DMA mode related parameters,
  *	ADC controller structure which used to store the hardware register
  *	base address, clock, Rx done callback API.
  */

/** @brief This structure defines ADC related parameters,
  * such as ADC mode, sample times, channel map, and interrupt mode.
  */
struct adc_fsm_param {
	adc_pmode	pmode;
	/**< ADC mode, one shot or periodic mode*/
	adc_avg_mode avg_mode;
	/**< ADC finite state machine sampling times*/
	u16 channel_map;
	/**< ADC bit map, REG_CH_MAP[7:0]=8'0000_0011, enable CH0 & CH1*/
	u32 period;
	/**< ADC clock cycle count period, unit as clock cycle*/
	adc_fifo_mode fifo_mode;
	/**< ADC operation mode: FIFO or DMA mode*/
	u32 dma_vfifo_addr[ADC_DMA_BUF_WORD_SIZE];
	/**< ADC DMA Virtual FIFO address*/
	u32 dma_vfifo_len;
	/**< ADC DMA Virtual FIFO length*/
	adc_fifo_ier_mode ier_mode;
	/**< ADC interrupt mode*/
};
/** @brief This structure used to pass arguments between OS-HAL/M-HAL,
  * such as DMA physical address, Rx status, Rx running status.
  */
struct mtk_adc_transfer {
	/**	ADC Ring buffer write point */
	u32	 write_point;
	/**	ADC Ring buffer read point */
	u32	 read_point;
	/**	ADC Ring buffer data count */
	u32	 count;
	/**	ADC Ring buffer */
	u32	 ring_buf[ADC_RING_BUF_SIZE];
};

/** @brief Interface to ADC, used to store the hardware register base address,
 * clock, Rx done callback API, etc.
 */
struct mtk_adc_controller {
/** ADC controller base address */
void __iomem *base;
/** Clock gate base address */
void __iomem *cg_base;
/** ADC fsm related parameters */
struct adc_fsm_param *adc_fsm_parameter;
/** ADC  channels in using */
u32 channel_count;
/** Sample voltage */
u16		voltage;
/** ADC hardware is sampling data */
u16 adc_processing;
/** ADC transfer structure */
struct mtk_adc_transfer	current_xfer[ADC_CHANNEL_MAX];
/** Rx DMA physical address */
dma_addr_t	rx_addr;
/** Used for Rx buf  */
u32	rx_buf[ADC_RING_BUF_SIZE];
/** Rx length */
u32	rx_size;
/** ADC support FIFO & DMA mode, 0:FIFO, 1: DMA */
u32	use_dma;
/** ADC DMA channel number */
u8  dma_channel;
/**	ADC DMA Rx status */
adc_dma_rx_status	adcrxstatus;
/** Rx_done_callback param.*/
void	*callback_param;
/** OS-HAL defined API rx_done_callback.*/
adc_rx_done_callback rx_done_callback;
};

/**
  * @}
  */


/** @defgroup driver_adc_function Function
  * @{
  *	M-HAL ADC function list information, including
  *	ADC controller allocating and releasing,
  *	ADC hardware initializing and de-initializing,
  *	setting and getting ADC state machine,
  *	enabling and disabling PWM hardware output,
  *	gets ADC sample data using FIFO mode,
  *	gets ADC sample data using DMA mode,
  *	registers OS-HAL callback API to M-HAL,
  *	enabling and disabling clock.
  */

/**
  * @brief  This function is used to initialize an ADC hardware controller.
  * @brief Usage: The main sequence is as bellow:\n
  *  1.Call this function after allocating ADC controller.\n
  *  2.Before operating ADC hardware, this API should be called firstly.
  * @param [in] ctlr : Abstract an ADC controller.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
  */
int mtk_mhal_adc_init(struct mtk_adc_controller *ctlr);

/**
  * @brief  This function is used to de-initialize an ADC
  *  hardware controller.
  * @brief Usage: This function should be called before releasing ADC
  *  controller.
  * @param [in] ctlr : Abstract an ADC controller.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
  */
int mtk_mhal_adc_deinit(struct mtk_adc_controller *ctlr);
/**
  * @brief  This function is used to configure  ADC controller parameters.
  * @brief Usage: OS-HAL calls this API to set ADC hardware,
  *  and this function should be called before ADC start or
  *  ADC start channel.
  * @param [in] ctlr : Abstract an ADC controller.
  * @param [in] adc_fsm_parameter : ADC parameter information.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.\n
  *  If return value is -#EPARAMETER , it means parameter invalid.
  */

int mtk_mhal_adc_fsm_param_set(struct mtk_adc_controller *ctlr,
		struct adc_fsm_param *adc_fsm_parameter);

/**
  * @brief  This function is used to get the configuration parameters of ADC
  *  controller.
  * @brief Usage: OS-HAL calls this API to get current ADC hardware parameters.
  * @param [in] ctlr : Abstract an ADC controller.
  * @param [out] adc_fsm_parameter : Store ADC state machine parameters
  *  information.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
  */

int mtk_mhal_adc_fsm_param_get(struct mtk_adc_controller *ctlr,
		struct adc_fsm_param *adc_fsm_parameter);

/**
  * @brief  This function is used to start all channels of ADC controller
  *  in one group.
  * @brief Usage: OS-HAL calls this API to start ADC hardware,
  *  and this function should be called after setting ADC parameters.
  * @param [in] ctlr : Abstract an ADC controller.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
  */
int mtk_mhal_adc_start(struct mtk_adc_controller *ctlr);
/**
  * @brief  This function is used to start ADC controller according to
  *	the channel bitmap information.
  * @brief Usage: OS-HAL calls this API to start ADC hardware
  *	according to the channel bitmap information, and this function should be
  *	called after setting ADC parameters.
  * @param [in] ctlr : Abstract an ADC controller.
  * @param [in] ch_bit_map : ADC channel bit map information.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.\n
  *  If return value is -#EPARAMETER , it means parameter invalid.
  */

int  mtk_mhal_adc_start_ch(struct mtk_adc_controller *ctlr,
		u16 ch_bit_map);
/**
  * @brief  This function is used to stop ADC controller.
  * @brief Usage: The main sequence of the API is as bellow:\n
  *  1.This function should be called after setting ADC parameters.\n
  *  2.This function should be called before ADC de-initializing.
  * @param [in] ctlr : Abstract an ADC controller.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
  */
int mtk_mhal_adc_stop(struct mtk_adc_controller *ctlr);

/**
  * @brief  This function is used to sample ADC channel voltage
  *  using one shot FIFO mode.
  * @param [in] ctlr : Abstract an ADC controller.
  * @param [in] channel : ADC channel number(0~7).
  * @param [out] data : ADC sample data.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.\n
  *  If return value is -#EPARAMETER , it means parameter invalid.
  */

int mtk_mhal_adc_one_shot_get_data(struct mtk_adc_controller *ctlr,
		adc_channel channel, u32 *data);

/**
  * @brief  This function is used to sample ADC channel voltage
  *  using period mode.
  * @param [in] ctlr : Abstract an ADC controller.
  * @param [in] sample_channel : Sample channel number.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
  */

int mtk_mhal_adc_period_get_data(struct mtk_adc_controller *ctlr,
		adc_channel channel);

/**
 *@brief	 This function is used to register user's callback to M-HAL.
 *	It's used for Rx transaction.
 *	While expected data are received, Rx interrupt is triggered
 *	and this callback is called in the interrupt service routine.
 * @param [in] ctlr : Abstract an ADC controller.
 * @param [in] callback : The callback function given by OS-HAL.
 *	The function will be called at ADC Rx interrupt service routine.
 * @param [in] callback_param : A parameter given by OS-HAL and it will
 *	be passed to user when the callback function is called.
 * @return
 *	If return value is 0, it means success.\n
 *	If return value is -#EPTR , it means ctlr is NULL.\n
 *	If return value is -#EPARAMETER , it means parameter invalid.
 */
int mtk_mhal_adc_rx_notify_callback_register(struct mtk_adc_controller *ctlr,
						adc_rx_done_callback callback,
						void *callback_param);

/**
 * @brief This function is used to enable ADC clock.
 * @brief Usage: It must be called before operating hardware;
 *	otherwise, the access to ADC register will fail. The function should
 *	be called in the sequence as bellow:
 *	alloc_controller-> enable_clk->adc_init.
 * @param [in] ctlr :  Abstract an ADC controller.
 * @return
 *	If return value is 0, it means success.\n
 *	If return value is -#EPTR , it means ctlr is NULL.
 */
int mtk_mhal_adc_enable_clk(struct mtk_adc_controller *ctlr);

/**
  * @brief This function is used to disable ADC clock.
  * @brief Usage: When Hardware is not in use, advise to disable clock.
  * @param [in] ctlr :  Abstract an ADC controller.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
 */
int mtk_mhal_adc_disable_clk(struct mtk_adc_controller *ctlr);
/**
  * @brief This function is used to read FIFO data from HW.
  * @brief Usage: It must be called in irq function with FIFO mode.
  * @param [in] ctlr :  Abstract an ADC controller.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
 */
int mtk_mhal_adc_fifo_handle_rx(struct mtk_adc_controller *ctlr);
/**
  * @brief This function is used to stop ADC rx dma.
  * @brief Usage: It must be called after stop ADC HW.
  * @param [in] ctlr :  Abstract an ADC controller.
  * @return
  *  If return value is 0, it means success.\n
  *  If return value is -#EPTR , it means ctlr is NULL.
 */
int mtk_mhal_adc_stop_dma(struct mtk_adc_controller *ctlr);

/**
  * @}
  */

/**
 * @}
 * @}
 */

/**
* @}
* @}
*/
#endif /* __MHAL_ADC_H__ */

