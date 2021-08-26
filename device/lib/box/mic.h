#pragma once
#include "driver/i2s.h"
#include "arduinoFFT.h"

const uint16_t SAMPLES = 256;
double vReal[SAMPLES];
double vImag[SAMPLES];
double micGain = 1.0;
double mapf(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void setupMIC() {
  esp_err_t err;

  // The I2S config as per the example
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive, not transfer
    .sample_rate = 32000,                         // 16KHz
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, // could only get it to work with 32bits
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT, // use right channel
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,     // Interrupt level 1
    .dma_buf_count = 4,                           // number of buffers
    .dma_buf_len = 256                              // 8 samples per buffer (minimum)
  };

  // The pin config as per the setup
  const i2s_pin_config_t pin_config = {
    .bck_io_num = 26,   // Serial Clock (SCK)
    .ws_io_num = 25,    // Word Select (WS)
    .data_out_num = I2S_PIN_NO_CHANGE, // not used (only for speakers)
    .data_in_num = 33   // Serial Data (SD)
  };

  // Configuring the I2S driver and pins.
  // This function must be called before any I2S driver read/write operations.
  err = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  if (err != ESP_OK) {
    Serial.printf("Failed installing driver: %d\n", err);
    while (true);
  }
  err = i2s_set_pin(I2S_NUM_0, &pin_config);
  if (err != ESP_OK) {
    Serial.printf("Failed setting pin: %d\n", err);
    while (true);
  }
  Serial.println("I2S driver installed.");
}
int32_t getMIC_RAW() {
    static int32_t lastSample = 0;
    int32_t sample = 0;
    int bytes_read = i2s_pop_sample(I2S_NUM_0, (char *)&sample, portMAX_DELAY); // no timeout
    sample=sample<0?-sample:sample;
    if(bytes_read>0){
      lastSample = sample;
      return sample;
    }
    return lastSample;
}
void calcData(){
  static uint32_t samplingTime;
  samplingTime = micros();
  for (int i = 0; i < SAMPLES; i++) {
    double val = getMIC_RAW();
    val = val < 0 ? -val : val;
    vReal[i] = val;
    vImag[i] = 0;
  }
  samplingTime = micros() - samplingTime;
  //  Serial.println(String(" samplingTime ") + (samplingTime)); // 3.6ms
  double samplingFrequency = 1000000.00*double(SAMPLES)/double(samplingTime);
  arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, samplingFrequency);
  FFT.DCRemoval();
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();
}
double getValByFreq(void(*onChangeMax)(double val, double freq) = NULL){
  static double ret = 1;
  if(ret>SAMPLES*3/4)
    ret -=32;
  else if(ret>SAMPLES/2)
    ret -=16;
  else
    ret -=8;
  if(ret < 0)
    ret = 0;
  calcData();
  double maxValByFreq = 0;
  double _freq = 0;
  for (int i = 2; i < SAMPLES/2; i++) {
    if(vReal[i]>maxValByFreq){
      maxValByFreq = vReal[i];
      _freq = i;
    }
  }  
  if(maxValByFreq<100000000.0)
    maxValByFreq=0;
  maxValByFreq = mapf(maxValByFreq,0.0, 5000000000.0/micGain,0.0,double(SAMPLES));
  if(maxValByFreq > ret){
    ret=maxValByFreq;
    if(onChangeMax != NULL)
      onChangeMax(mapf(ret,0.0,double(SAMPLES),0.0,100.0),_freq);

  }
  return mapf(ret,0.0,double(SAMPLES),0.0,100.0);
}
void setMicGain(double gain){
  micGain = gain;
}
double getMicGain(){
  return micGain;
}
