#pragma once
#include "driver/i2s.h"
#include "arduinoFFT.h"

#define SAMPLES 128
#define BAND 16
#define SAMPLES_MAX_FREQ 16000
#define MAX_INTENSITY 1048576.00

double vReal[SAMPLES];
double vImag[SAMPLES];
double micGain = 1.0;
double takeBeat = 50.0;
double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int32_t getMIC_RAW()
{
  static int32_t lastSample = 0;
  int32_t sample = 0;
  int bytes_read = i2s_pop_sample(I2S_NUM_0, (char *)&sample, portMAX_DELAY); // no timeout

  // chỉ sử dụng 24 bit.
  sample = sample >> 8;
  sample = sample < 0 ? -sample : sample;
  if (bytes_read > 0)
  {
    lastSample = sample;
  }

  return lastSample;
}
double calcData()
{
  static uint32_t samplingTime;
  double ret = 0;
  samplingTime = micros();
  for (int i = 0; i < SAMPLES; i++)
  {
    double val = getMIC_RAW();
    vReal[i] = val;
    vImag[i] = 0;
    ret += val;
  }

  samplingTime = micros() - samplingTime;
  double samplingFrequency = 1000000.00 * double(SAMPLES) / double(samplingTime);
  arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, samplingFrequency);
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();
  return ret / double(SAMPLES);
}
double handleMicrophone(void (*onChangeMax)(double val, double freq) = NULL)
{
  static double lastFreq = 0;
  static double lastIntensity = 0;
  double curentIntensity = 0;
  curentIntensity = calcData();
  if (lastIntensity > 0)
    lastIntensity -= lastIntensity / (100 - takeBeat);

  double maxValByFreq = 0;
  double indexFreq = 0;
  double _val = 0;
  for (int i = 2; i < SAMPLES / 2; i += BAND)
  {
    _val = 0;
    for (int j = 0; j < BAND; j++)
    {
      _val += vReal[i + j];
    }
    _val /= BAND;
    if (_val > maxValByFreq)
    {
      maxValByFreq = _val;
      indexFreq = i;
    }
  }

  // if (abs(indexFreq - lastFreq)>8)
  // {
  //   lastFreq = indexFreq;
  //   log_d("maxValByFreq: %.2f", maxValByFreq);

  //   if (onChangeMax != NULL)
  //     onChangeMax(mapf(_val, 0.0, double(SAMPLES), 0.0, 100.0), maxValByFreq);
  // }

  /* Dùng để đo max intensity, giá trị này còn phụ thuộc vào SAMPLES
  static double maxcurentIntensity;
  if(curentIntensity>maxcurentIntensity){
    maxcurentIntensity=curentIntensity;
  log_d("curentIntensity: %2.f",maxcurentIntensity);
  }
  */
  double micVal = mapf(curentIntensity, 0.00, MAX_INTENSITY, 0.00, 100.00);
  double freqVal = mapf(maxValByFreq, 0.00, SAMPLES/2, 0.00, 100.00);
  micVal = micVal * micGain;
  micVal = constrain(micVal, 0.00, 100.00);
  if (curentIntensity > lastIntensity)
  {
    lastIntensity = curentIntensity;
    if (onChangeMax != NULL)
    {
      onChangeMax(micVal, freqVal);
    }
  }
  return mapf(micVal, 0.0, 2 ^ 24, 0.0, 100.0);
}
void setMicGain(double gain)
{
  micGain = gain;
  setValue("micGain_sld", String(gain));
}
double getMicGain()
{
  return micGain;
}
void setTakeBeat(double beat)
{
  takeBeat = beat;
  setValue("takeBeat_sld", String(beat));
}
double getTakeBeat()
{
  return takeBeat;
}

void setupMIC()
{
  esp_err_t err;

  // The I2S config as per the example
  const i2s_config_t i2s_config = {
      .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive, not transfer
      .sample_rate = SAMPLES_MAX_FREQ,                   // 16KHz
      .bits_per_sample = I2S_BITS_PER_SAMPLE_24BIT,      // could only get it to work with 32bits
      .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,      // use right channel
      .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // Interrupt level 1
      .dma_buf_count = 4,                       // number of buffers
      .dma_buf_len = SAMPLES                        // 8 samples per buffer (minimum)
  };

  // The pin config as per the setup
  const i2s_pin_config_t pin_config = {
      .bck_io_num = 26,                  // Serial Clock (SCK)
      .ws_io_num = 25,                   // Word Select (WS)
      .data_out_num = I2S_PIN_NO_CHANGE, // not used (only for speakers)
      .data_in_num = 33                  // Serial Data (SD)
  };

  // Configuring the I2S driver and pins.
  // This function must be called before any I2S driver read/write operations.
  err = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  if (err != ESP_OK)
  {
    log_d("Failed installing driver: %d", err);
    while (true)
      ;
  }
  err = i2s_set_pin(I2S_NUM_0, &pin_config);
  if (err != ESP_OK)
  {
    log_d("Failed setting pin: %d", err);
    while (true)
      ;
  }
  log_d("I2S driver installed.");
  // setMicGain(50);
  // setTakeBeat(50);
  setMicGain(getValue("micGain_sld", "25").toDouble());
  setTakeBeat(getValue("takeBeat_sld", "50").toDouble());
}