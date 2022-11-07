float BME280_Humidity;
float BME280_Pressure;
float BME280_Temperature;
float BME280_Altitude;

void UpdateBME280 ()
{
    BME280_Humidity = bme280.readHumidity();
    Serial.print("Humidity = ");
    Serial.print(BME280_Humidity);
    Serial.println(" %");

    BME280_Pressure = (bme280.readPressure()/1000);
    Serial.print("Pressure = ");
    Serial.print(BME280_Pressure);
    Serial.println(" kPa");

    BME280_Temperature = bme280.readTemperature();
    Serial.print("Temperature = ");
    Serial.print(BME280_Temperature);
    Serial.println(" *C");
    Serial.print("Temperature = ");
    Serial.print((BME280_Temperature * 9 / 5) + 32);
    Serial.println(" *f");

//  BME280_Altitude = bme280.readAltitude(SEALEVELPRESSURE_HPA);
    Serial.print("Approx. Altitude = ");
    Serial.print(BME280_Altitude);
    Serial.println(" m");
//
  Serial.println();
}
