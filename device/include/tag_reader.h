#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 25
#define RST_PIN 26
#define USERNAME_BLOCK 1
#define PASSWORD_BLOCK 2
#define DATA_LEN 16

MFRC522 rfid(SS_PIN, RST_PIN);

void TagReaderInit()
{
    SPI.begin();     // init SPI bus
    rfid.PCD_Init(); // init MFRC522
}

bool WriteCredentialsToTag(String username, String password)
{
    MFRC522::StatusCode status;
    MFRC522::MIFARE_Key key;

    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }

    /* Look for new cards */
    /* Reset the loop if no new card is present on RC522 Reader */
    while (!(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()))
    {
        Serial.println("**No card detected**");
        delay(1000);
    }

    byte usernameBuffer[DATA_LEN];
    byte passwordBuffer[DATA_LEN];

    for (int i = 0; i < DATA_LEN; i++)
    {
        if (i < username.length())
        {
            usernameBuffer[i] = username[i];
        }
        else
        {
            usernameBuffer[i] = '\0';
        }

        if (i < password.length())
        {
            passwordBuffer[i] = password[i];
        }
        else
        {
            passwordBuffer[i] = '\0';
        }
    }

    /* Authenticate and write username to the block */
    status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, USERNAME_BLOCK, &key, &(rfid.uid));
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Authentication failed for Username: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    status = rfid.MIFARE_Write(USERNAME_BLOCK, usernameBuffer, DATA_LEN);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Writing to Username Block failed: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    Serial.println("Username was written into Block successfully");

    /* Authenticate and write password to the block */
    status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, PASSWORD_BLOCK, &key, &(rfid.uid));
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Authentication failed for Password: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    status = rfid.MIFARE_Write(PASSWORD_BLOCK, passwordBuffer, DATA_LEN);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Writing to Password Block failed: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    Serial.println("Password was written into Block successfully");

    rfid.PICC_HaltA();      // halt PICC
    rfid.PCD_StopCrypto1(); // stop encryption on PCD
    return true;
}

bool ReadCredentialsFromTag(String &username, String &password)
{
    MFRC522::StatusCode status;
    MFRC522::MIFARE_Key key;
    byte bufferLen = DATA_LEN + 2;

    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }

    /* Look for new cards */
    /* Reset the loop if no new card is present on RC522 Reader */
    while (!(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()))
    {
        Serial.println("**No card detected**");
        delay(1000);
    }

    /* Authenticate and read username from the block */
    status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, USERNAME_BLOCK, &key, &(rfid.uid));
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Authentication failed for Username Read: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    byte usernameBuffer[bufferLen];
    status = rfid.MIFARE_Read(USERNAME_BLOCK, usernameBuffer, &bufferLen);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Reading from Username Block failed: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    username = String(reinterpret_cast<char *>(usernameBuffer));
    Serial.print("Username read from Block: ");
    Serial.println(username);

    /* Authenticate and read password from the block */
    status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, PASSWORD_BLOCK, &key, &(rfid.uid));
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Authentication failed for Password Read: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    byte passwordBuffer[bufferLen];

    status = rfid.MIFARE_Read(PASSWORD_BLOCK, passwordBuffer, &bufferLen);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Reading from Password Block failed: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }

    password = String(reinterpret_cast<char *>(passwordBuffer));
    Serial.print("Password read from Block: ");
    Serial.println(password);

    rfid.PICC_HaltA();      // halt PICC
    rfid.PCD_StopCrypto1(); // stop encryption on PCD
    return true;
}