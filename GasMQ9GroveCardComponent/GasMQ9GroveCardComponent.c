#include "legato.h"
#include "interfaces.h"

#define ADC_SAMPLE_INTERVAL_IN_MILLISECONDS (5000)
//--------------------------------------------------------------------------------------------------
/**
* Timer handler  will publish the current ADC reading.
 */
//--------------------------------------------------------------------------------------------------
static void adcTimer
(
    le_timer_Ref_t adcTimerRef
)
{
    int32_t value;

    const le_result_t result = le_adc_ReadValue("EXT_ADC0", &value);

    if (result == LE_OK)
    {
        LE_INFO("gas_value is: %d",value);

        if(value <1000)
        {
        	LE_INFO("Not found gas leak");
        }
        else
        {
        	LE_INFO("Found gas leak");
        }
    }
    else
    {
    	LE_INFO("Couldn't get ADC value");
    }
}

COMPONENT_INIT
{
    LE_INFO("ADC Reading start");
	le_timer_Ref_t adcTimerRef = le_timer_Create("ADC Timer");
	le_timer_SetMsInterval(adcTimerRef, ADC_SAMPLE_INTERVAL_IN_MILLISECONDS);
	le_timer_SetRepeat(adcTimerRef, 0);
	le_timer_SetHandler(adcTimerRef, adcTimer);
	le_timer_Start(adcTimerRef);
}
