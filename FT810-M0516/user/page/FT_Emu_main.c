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

#include "FT_Platform.h"

#if (defined(MSVC_FT800EMU) || defined(ESD_SIMULATION))
#include <FT_Emulator.h>


FT8XXEMU_EmulatorMode Ft_GpuEmu_Mode();

void setup();
void loop();

ft_int32_t main(ft_int32_t argc,ft_char8_t *argv[])
{
	FT8XXEMU_EmulatorParameters params;
	

	FT8XXEMU_defaults(FT8XXEMU_VERSION_API, &params, Ft_GpuEmu_Mode());

	params.Flags &= (~FT8XXEMU_EmulatorEnableDynamicDegrade & ~FT8XXEMU_EmulatorEnableRegPwmDutyEmulation);
	params.Setup = setup;
	params.Loop = loop;
	// params.Graphics = graphics;
	FT8XXEMU_run(FT8XXEMU_VERSION_API, &params);
	return 0;
}

void Ft_GpuEmu_SPII2C_csLow()
{
	FT8XXEMU_cs(1);
}

void Ft_GpuEmu_SPII2C_csHigh()
{
	FT8XXEMU_cs(0);
}

void Ft_GpuEmu_SPII2C_begin()
{

}

void Ft_GpuEmu_SPII2C_end()
{

}


uint8_t Ft_GpuEmu_SPII2C_transfer(uint8_t data)
{
	return FT8XXEMU_transfer(data);
}


void  Ft_GpuEmu_SPII2C_StartRead(uint32_t addr)
{
	Ft_GpuEmu_SPII2C_csLow();
	Ft_GpuEmu_SPII2C_transfer((addr >> 16) & 0xFF);
	Ft_GpuEmu_SPII2C_transfer((addr >> 8) & 0xFF);
	Ft_GpuEmu_SPII2C_transfer(addr & 0xFF);

	Ft_GpuEmu_SPII2C_transfer(0); //Dummy Read Byte
}

void  Ft_GpuEmu_SPII2C_StartWrite(uint32_t addr)
{
	Ft_GpuEmu_SPII2C_csLow();
	Ft_GpuEmu_SPII2C_transfer(((addr >> 16) & 0xFF) | 0x80);
	Ft_GpuEmu_SPII2C_transfer((addr >> 8) & 0xFF);
	Ft_GpuEmu_SPII2C_transfer(addr & 0xFF);
	
}

FT8XXEMU_EmulatorMode Ft_GpuEmu_Mode(){
#if defined(FT_800_ENABLE)
		return FT8XXEMU_EmulatorFT800;
#elif defined(FT_801_ENABLE)
		return FT8XXEMU_EmulatorFT801;
#elif (defined(FT_810_ENABLE) || defined(FT_812_ENABLE))
		return FT8XXEMU_EmulatorFT810;
#elif (defined(FT_811_ENABLE) || defined(FT_813_ENABLE))
		return FT8XXEMU_EmulatorFT811;
#endif
		return FT8XXEMU_EmulatorFT800;
}


#endif