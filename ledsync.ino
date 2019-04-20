#define TARGET_TIME (30 * 1000) //30sec. 

void setup(){
  Serial.begin(9600);
  pinMode(D7,OUTPUT);

}

void loop() {

  time_t lastSyncTimestamp;
  unsigned long lastSync = Particle.timeSyncedLast(lastSyncTimestamp);
  if (millis() - lastSync > TARGET_TIME) {
    unsigned long cur = millis();
    Serial.printlnf("Time was last synchronized %lu milliseconds ago", millis() - lastSync);
    if (lastSyncTimestamp > 0)
    {
      Serial.print("Time received from Cloud was: ");
      Serial.println(Time.timeStr(lastSyncTimestamp));
    }
    // Request time synchronization from Particle Device Cloud
    Particle.syncTime();
    // Wait until Photon receives time from Particle Device Cloud (or connection to Particle Device Cloud is lost)
    waitUntil(Particle.syncTimeDone);
    // Check if synchronized successfully
    if (Particle.timeSyncedLast() >= cur)
    {
        digitalWrite(D7,HIGH);
        delay(1000);
        digitalwrite(D7,LOW);
    }
  }
}