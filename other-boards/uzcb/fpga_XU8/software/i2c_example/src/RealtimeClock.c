/** \file RealtimeClock.c
 * \brief Implementation file for RTC functions.
 * \author Garry Jeromson
 * \date 02.07.15
 */

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "RealtimeClock.h"
#include "I2cInterface.h"
#include "UtilityFunctions.h"


//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

/**
 * \brief Enum for RTC device types, with I2C addresses assigned as values.
 */
typedef enum
{

    /// Intersil ISL12020
    ERtcDevice_ISL12020 = 0x6F,

    /// NXP PCF85063A
    ERtcDevice_NXPPCF85063A = 0x51,

} ERtcDevice_t;


/// Array of all possible RTC device addresses
const uint8_t RTC_DEVICE_ADDRESSES[2] = { ERtcDevice_ISL12020, ERtcDevice_NXPPCF85063A };

/// RTC device type for the detected RTC
ERtcDevice_t g_RtcDeviceType;


//-------------------------------------------------------------------------------------------------
// Register addresses
//-------------------------------------------------------------------------------------------------


//--------------------------------------
// ISL12020
//--------------------------------------


/// Register address for seconds
#define ISL12020_REGISTER_ADDRESS_SECONDS 0x00

/// Register address for minutes
#define ISL12020_REGISTER_ADDRESS_MINUTES 0x01

/// Register address for hours
#define ISL12020_REGISTER_ADDRESS_HOUR 0x02

/// Register address for day
#define ISL12020_REGISTER_ADDRESS_DAY 0x03

/// Register address for month
#define ISL12020_REGISTER_ADDRESS_MONTH 0x04

/// Register address for year
#define ISL12020_REGISTER_ADDRESS_YEAR 0x05

/// Register address for temperature value 0
#define ISL12020_REGISTER_ADDRESS_TEMPERATURE1 0x28

/// Register address for temperature value 1
#define ISL12020_REGISTER_ADDRESS_TEMPERATURE2 0x29


//--------------------------------------
// PCF85063A
//--------------------------------------

/// Register address for seconds
#define PCF85063A_REGISTER_ADDRESS_SECONDS 0x04

/// Register address for minutes
#define PCF85063A_REGISTER_ADDRESS_MINUTES 0x05

/// Register address for hours
#define PCF85063A_REGISTER_ADDRESS_HOUR 0x06

/// Register address for day
#define PCF85063A_REGISTER_ADDRESS_DAY 0x07

/// Register address for month
#define PCF85063A_REGISTER_ADDRESS_MONTH 0x09

/// Register address for year
#define PCF85063A_REGISTER_ADDRESS_YEAR 0x0A


uint8_t g_secondsRegisterAddress;
uint8_t g_minutesRegisterAddress;
uint8_t g_hourRegisterAddress;
uint8_t g_dayRegisterAddress;
uint8_t g_monthRegisterAddress;
uint8_t g_yearRegisterAddress;


//-------------------------------------------------------------------------------------------------
// Function definitions
//-------------------------------------------------------------------------------------------------


EN_RESULT IsRtcPresentAtDeviceAddress(uint8_t rtcI2cAddress, bool* pDeviceIsPresent)
{
    if (pDeviceIsPresent == NULL)
    {
        return EN_ERROR_NULL_POINTER;
    }

    // Perform any config/wake functions that are required for the device to be detected.
    switch (rtcI2cAddress)
    {
    case ERtcDevice_ISL12020:
    {
        // Try to read from address 0 to see if the device responds.
        uint8_t readBuffer;
        if (EN_FAILED(
                I2cRead(rtcI2cAddress, 0, EI2cSubAddressMode_OneByte, sizeof(readBuffer), (uint8_t*)&readBuffer)))
        {
            *pDeviceIsPresent = false;
        }
        else
        {
            *pDeviceIsPresent = true;
        }

        break;
    }
    case ERtcDevice_NXPPCF85063A:
    {
        // Try to read from address 0 to see if the device responds.
        uint8_t readBuffer;
        if (EN_FAILED(
                I2cRead(rtcI2cAddress, 0, EI2cSubAddressMode_OneByte, sizeof(readBuffer), (uint8_t*)&readBuffer)))
        {
            *pDeviceIsPresent = false;
        }
        else
        {
            *pDeviceIsPresent = true;
        }

        break;
    }
    default:
        break;
    }

    return EN_SUCCESS;
}

EN_RESULT DetermineRtcType()
{
    unsigned int addressCount = sizeof(RTC_DEVICE_ADDRESSES) / sizeof(RTC_DEVICE_ADDRESSES[0]);
    unsigned int addressIndex = 0;
    for (addressIndex = 0; addressIndex < addressCount; addressIndex++)
    {
        bool devicePresentAtI2cAddress = false;
        uint8_t deviceAddress = RTC_DEVICE_ADDRESSES[addressIndex];
        EN_RETURN_IF_FAILED(IsRtcPresentAtDeviceAddress(deviceAddress, &devicePresentAtI2cAddress));

        if (devicePresentAtI2cAddress)
        {
            g_RtcDeviceType = (ERtcDevice_t)deviceAddress;
            break;
        }

        if (addressIndex == addressCount - 1)
        {
            // If we get to this point, we haven't found a device.
            return EN_ERROR_RTC_DEVICE_NOT_DETECTED;
        }
    }

    return EN_SUCCESS;
}

void SetRegisterAddresses()
{
    switch (g_RtcDeviceType)
    {
    case ERtcDevice_ISL12020:
    {
        g_secondsRegisterAddress = ISL12020_REGISTER_ADDRESS_SECONDS;
        g_minutesRegisterAddress = ISL12020_REGISTER_ADDRESS_MINUTES;
        g_hourRegisterAddress = ISL12020_REGISTER_ADDRESS_HOUR;
        g_dayRegisterAddress = ISL12020_REGISTER_ADDRESS_DAY;
        g_monthRegisterAddress = ISL12020_REGISTER_ADDRESS_MONTH;
        g_yearRegisterAddress = ISL12020_REGISTER_ADDRESS_YEAR;
        break;
    }
    case ERtcDevice_NXPPCF85063A:
    {
        g_secondsRegisterAddress = PCF85063A_REGISTER_ADDRESS_SECONDS;
        g_minutesRegisterAddress = PCF85063A_REGISTER_ADDRESS_MINUTES;
        g_hourRegisterAddress = PCF85063A_REGISTER_ADDRESS_HOUR;
        g_dayRegisterAddress = PCF85063A_REGISTER_ADDRESS_DAY;
        g_monthRegisterAddress = PCF85063A_REGISTER_ADDRESS_MONTH;
        g_yearRegisterAddress = PCF85063A_REGISTER_ADDRESS_YEAR;
        break;
    }
    default:
        break;
    }
}

EN_RESULT Rtc_Initialise()
{
    EN_RETURN_IF_FAILED(DetermineRtcType());

    SetRegisterAddresses();

    switch (g_RtcDeviceType)
    {
    case ERtcDevice_ISL12020:
    {
#if _DEBUG == 1
        EN_PRINTF("Detected RTC ISL12020\r\n");
#endif
        // Enable write access
        // Disable Frequency Output
        uint8_t writeEnable = 0x40;
        EN_RETURN_IF_FAILED(I2cWrite(ERtcDevice_ISL12020, 0x08, EI2cSubAddressMode_OneByte, &writeEnable, 1));

        // Enable temp sense - read the register value, set bit 8, and write it back.
        uint8_t configRegister;
        EN_RETURN_IF_FAILED(I2cRead(ERtcDevice_ISL12020, 0x0D, EI2cSubAddressMode_OneByte, 1, &configRegister));

        configRegister = configRegister | 0x80;

        EN_RETURN_IF_FAILED(I2cWrite(ERtcDevice_ISL12020, 0x0D, EI2cSubAddressMode_OneByte, &configRegister, 1));
        break;
    }
    case ERtcDevice_NXPPCF85063A:
    {
#if _DEBUG == 1
        EN_PRINTF("Detected RTC NXPPCF85063A\r\n");
#endif
        // Enable 24-hour mode and set oscillator capacity
        uint8_t configRegister = 0;
        EN_RETURN_IF_FAILED(I2cRead(ERtcDevice_NXPPCF85063A, 0x00, EI2cSubAddressMode_OneByte, 1, &configRegister));

        configRegister = configRegister | 0x01;

        EN_RETURN_IF_FAILED(I2cWrite(ERtcDevice_NXPPCF85063A, 0x00, EI2cSubAddressMode_OneByte, &configRegister, 1));

        break;
    }
    default:
        break;
    }


    return EN_SUCCESS;
}

EN_RESULT Rtc_ReadTime(int* pHour, int* pMinutes, int* pSeconds)
{
    if (pHour == NULL || pMinutes == NULL || pSeconds == NULL)
    {
        return EN_ERROR_NULL_POINTER;
    }

    uint8_t binaryCodedSeconds;
    EN_RETURN_IF_FAILED(
        I2cRead(g_RtcDeviceType, g_secondsRegisterAddress, EI2cSubAddressMode_OneByte, 1, &binaryCodedSeconds));
    *pSeconds = ConvertBinaryCodedDecimalToDecimal(binaryCodedSeconds);

    uint8_t binaryCodedMinutes;
    EN_RETURN_IF_FAILED(
        I2cRead(g_RtcDeviceType, g_minutesRegisterAddress, EI2cSubAddressMode_OneByte, 1, &binaryCodedMinutes));
    *pMinutes = ConvertBinaryCodedDecimalToDecimal(binaryCodedMinutes);

    uint8_t binaryCodedHour;
    EN_RETURN_IF_FAILED(
        I2cRead(g_RtcDeviceType, g_hourRegisterAddress, EI2cSubAddressMode_OneByte, 1, &binaryCodedHour));

    /// \todo Comment on why this mask is required.
    *pHour = ConvertBinaryCodedDecimalToDecimal(binaryCodedHour & 0x3F);

    return EN_SUCCESS;
}

EN_RESULT Rtc_SetTime(int hour, int minutes, int seconds)
{
    uint8_t binaryCodedHour = ConvertDecimalToBinaryCodedDecimal(hour);
    uint8_t binaryCodedMinutes = ConvertDecimalToBinaryCodedDecimal(minutes);
    uint8_t binaryCodedSeconds = ConvertDecimalToBinaryCodedDecimal(seconds);

    binaryCodedHour |= 0x80; // enable 24h format

    EN_RETURN_IF_FAILED(
        I2cWrite(g_RtcDeviceType, g_secondsRegisterAddress, EI2cSubAddressMode_OneByte, &binaryCodedSeconds, 1));

    EN_RETURN_IF_FAILED(
        I2cWrite(g_RtcDeviceType, g_minutesRegisterAddress, EI2cSubAddressMode_OneByte, &binaryCodedMinutes, 1));

    EN_RETURN_IF_FAILED(
        I2cWrite(g_RtcDeviceType, g_hourRegisterAddress, EI2cSubAddressMode_OneByte, &binaryCodedHour, 1));

    return EN_SUCCESS;
}

EN_RESULT Rtc_ReadDate(int* pDay, int* pMonth, int* pYear)
{
    if (pDay == NULL || pMonth == NULL || pYear == NULL)
    {
        return EN_ERROR_NULL_POINTER;
    }

    uint8_t binaryCodedDay;
    EN_RETURN_IF_FAILED(I2cRead(g_RtcDeviceType, g_dayRegisterAddress, EI2cSubAddressMode_OneByte, 1, &binaryCodedDay));
    *pDay = ConvertBinaryCodedDecimalToDecimal(binaryCodedDay);

    uint8_t binaryCodedMonth;
    EN_RETURN_IF_FAILED(
        I2cRead(g_RtcDeviceType, g_monthRegisterAddress, EI2cSubAddressMode_OneByte, 1, &binaryCodedMonth));
    *pMonth = ConvertBinaryCodedDecimalToDecimal(binaryCodedMonth);

    uint8_t binaryCodedYear;
    EN_RETURN_IF_FAILED(
        I2cRead(g_RtcDeviceType, g_yearRegisterAddress, EI2cSubAddressMode_OneByte, 1, &binaryCodedYear));
    *pYear = ConvertBinaryCodedDecimalToDecimal(binaryCodedYear);

    return EN_SUCCESS;
}

EN_RESULT Rtc_SetDate(int day, int month, int year)
{

    uint8_t binaryCodedDay = ConvertDecimalToBinaryCodedDecimal(day);
    uint8_t binaryCodedMonth = ConvertDecimalToBinaryCodedDecimal(month);
    uint8_t binaryCodedYear = ConvertDecimalToBinaryCodedDecimal(year);

    EN_RETURN_IF_FAILED(
        I2cWrite(g_RtcDeviceType, g_dayRegisterAddress, EI2cSubAddressMode_OneByte, &binaryCodedDay, 1));

    EN_RETURN_IF_FAILED(
        I2cWrite(g_RtcDeviceType, g_monthRegisterAddress, EI2cSubAddressMode_OneByte, &binaryCodedMonth, 1));

    EN_RETURN_IF_FAILED(
        I2cWrite(g_RtcDeviceType, g_yearRegisterAddress, EI2cSubAddressMode_OneByte, &binaryCodedYear, 1));

    return EN_SUCCESS;
}

EN_RESULT Rtc_ReadTemperature(int* pTemperatureCelsius)
{
    if (pTemperatureCelsius == NULL)
    {
        return EN_ERROR_NULL_POINTER;
    }

    if (g_RtcDeviceType == ERtcDevice_NXPPCF85063A)
    {
        return EN_ERROR_RTC_FEATURE_NOT_SUPPORTED;
    }

    uint8_t value0;
    uint8_t value1;

    EN_RETURN_IF_FAILED(
        I2cRead(g_RtcDeviceType, ISL12020_REGISTER_ADDRESS_TEMPERATURE1, EI2cSubAddressMode_OneByte, 1, &value0));
    EN_RETURN_IF_FAILED(
        I2cRead(g_RtcDeviceType, ISL12020_REGISTER_ADDRESS_TEMPERATURE2, EI2cSubAddressMode_OneByte, 1, &value1));

    *pTemperatureCelsius = (value0 + value1 * 256) / 2 - 273;

    return EN_SUCCESS;
}
