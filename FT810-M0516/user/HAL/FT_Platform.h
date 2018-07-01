/**
* This source code ("the Software") is provided by Bridgetek Pte Ltd
* ("Bridgetek") subject to the licence terms set out
*   http://brtchip.com/BRTSourceCodeLicenseAgreement/ ("the Licence Terms").
* You must read the Licence Terms before downloading or using the Software.
* By installing or using the Software you agree to the Licence Terms. If you
* do not agree to the Licence Terms then do not download or use the Software.
*
* Without prejudice to the Licence Terms, here is a summary of some of the key
* terms of the Licence Terms (and in the event of any conflict between this
* summary and the Licence Terms then the text of the Licence Terms will
* prevail).
*
* The Software is provided "as is".
* There are no warranties (or similar) in relation to the quality of the
* Software. You use it at your own risk.
* The Software should not be used in, or for, any medical device, system or
* appliance. There are exclusions of Bridgetek liability for certain types of loss
* such as: special loss or damage; incidental loss or damage; indirect or
* consequential loss or damage; loss of income; loss of business; loss of
* profits; loss of revenue; loss of contracts; business interruption; loss of
* the use of money or anticipated savings; loss of information; loss of
* opportunity; loss of goodwill or reputation; and/or loss of, damage to or
* corruption of data.
* There is a monetary cap on Bridgetek's liability.
* The Software may have subsequently been amended by another user and then
* distributed by that other user ("Adapted Software").  If so that user may
* have additional licence terms that apply to those amendments. However, Bridgetek
* has no liability in relation to those amendments.
*/

#ifndef _FT_PLATFORM_H_
#define _FT_PLATFORM_H_

#define ARDUINO_PLATFORM
#define    ARDUINO_PLATFORM_SPI
// #define    MSVC_FT800EMU
#define   ME810A_WH50R





#ifdef VM800B43_50
#define FT_8XX_MODULE								(1)
#define FT_800_ENABLE								(1)
#define DISPLAY_RESOLUTION_WQVGA					(1)
#define ENABLE_SPI_SINGLE							(1)
#define RESISTANCE_THRESHOLD						(1200)
#endif /* VM800B43_50 */

#ifdef VM800B35
#define FT_8XX_MODULE								(1)
#define FT_800_ENABLE								(1)
#define DISPLAY_RESOLUTION_QVGA						(1)
#define ENABLE_SPI_SINGLE							(1)
#define RESISTANCE_THRESHOLD						(1200)
#endif /* VM800B35 */

#ifdef VM801B43_50
#define FT_8XX_MODULE								(1)
#define FT_801_ENABLE								(1)
#define DISPLAY_RESOLUTION_WQVGA					(1)
#define ENABLE_SPI_SINGLE							(1)
#define RESISTANCE_THRESHOLD						(1200)
#endif /* VM801B43_50 */

#ifdef ME800A_HV35R
#define FT_8XX_MODULE								(1)
#define ENABLE_SPI_SINGLE							(1)
#define FT_800_ENABLE								(1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT			(1)
#define ENABLE_ILI9488_HVGA_PORTRAIT				(1)
#define RESISTANCE_THRESHOLD						(1800)
#endif /* ME800A_HV35R */

#ifdef ME810A_HV35R
#define FT_8XX_MODULE								(1)
#define ENABLE_SPI_QUAD								(1)
#define FT_810_ENABLE								(1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT			(1)
#define ENABLE_ILI9488_HVGA_PORTRAIT				(1)
#define RESISTANCE_THRESHOLD						(1800)
#endif /* ME810A_HV35R */

#ifdef ME813A_WV7C
#define FT_8XX_MODULE								(1)
#define ENABLE_SPI_QUAD								(1)
#define FT_813_ENABLE								(1)
#define DISPLAY_RESOLUTION_WVGA						(1)
#define RESISTANCE_THRESHOLD						(1800)
#endif /* ME813A_WV7C */

#ifdef ME810A_WH50R//////////////////////
#define FT_8XX_MODULE								(1)
#define ENABLE_SPI_SINGLE								(1)
#define FT_810_ENABLE								(1)
#define DISPLAY_RESOLUTION_WVGA						(1)
#define RESISTANCE_THRESHOLD						(1800)
#endif /* ME812A_WH50R */

#ifdef CLEO35
#define FT_8XX_MODULE								(1)
#define ENABLE_SPI_QUAD								(1)
#define FT_810_ENABLE								(1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT			(1)
#define ENABLE_ILI9488_HVGA_PORTRAIT				(1)
#define RESISTANCE_THRESHOLD						(1800)
#endif /* CLEO35 */

#ifdef CLEO50
#define FT_8XX_MODULE								(1)
#define ENABLE_SPI_QUAD								(1)
#define FT_812_ENABLE								(1)
#define DISPLAY_RESOLUTION_WVGA						(1)
#define RESISTANCE_THRESHOLD						(1200)
#endif /* CLEO50 */


#ifdef PANL35
#define ENABLE_SPI_QUAD								(1)
#define FT_811_ENABLE								(1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT			(1)
#define ENABLE_KD2401_HVGA_PORTRAIT					(1)
#endif

#if defined(FT_800_ENABLE) || defined(FT_801_ENABLE)
#define FT_80X_ENABLE								(1)
#endif

#if defined(FT_810_ENABLE) || defined(FT_811_ENABLE) || defined(FT_812_ENABLE) || defined(FT_813_ENABLE)
#define FT_81X_ENABLE								(1)
#endif


#include "Ft_Esd.h"



/* Standard C libraries */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

//#include <Windows.h>
//#include <direct.h>
//#include <time.h>
//#include <io.h>
/* HAL inclusions */
#include "FT_DataTypes.h"

//#include "FT_EmulatorMain.h"
#include "FT_Gpu_Hal.h"
#include "FT_Gpu.h"
#include "FT_CoPro_Cmds.h"
#include "FT_Hal_Utils.h"
// #define BUFFER_OPTIMIZATION

#define FT800_SEL_PIN   0
#define FT800_PD_N      7


#endif 



/* Nothing beyond this*/
