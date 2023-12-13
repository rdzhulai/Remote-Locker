#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 25
#define RST_PIN 26

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

/* Set the block to which we want to write data */
/* Be aware of Sector Trailer Blocks */
#define BLOCK_NUM 2
/* Create an array of DATA_LEN Bytes and fill it with data */
/* This is the actual data which is going to be written into the card */

/* Create another array to read data from Block */
/* Legthn of buffer should be 2 Bytes more than the size of Block (DATA_LEN Bytes) */
#define DATA_LEN 16
byte bufferLen = 18;
byte blockData[DATA_LEN];
byte readBlockData[18];

MFRC522::StatusCode status;

void tag_reader_init()
{
    SPI.begin();     // init SPI bus
    rfid.PCD_Init(); // init MFRC522
}

void detect_tag()
{
    for (byte i = 0; i < 6; i++)
    {
        key.keyByte[i] = 0xFF;
    }
    /* Look for new cards */
    /* Reset the loop if no new card is present on RC522 Reader */
    while (!(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()))
    {
        Serial.println("**No card detected**");
        rfid.PICC_HaltA();      // halt PICC
        rfid.PCD_StopCrypto1(); // stop encryption on PCD
        delay(1000);
    }
}

String getReadData()
{
    String readData;
    int j = 0;
    for (; j < DATA_LEN; j++)
    {
        if (readBlockData[j] == '\n')
            break;
        readData += (char)readBlockData[j];
    }

    return readData;
}

bool setBlockData(String data)
{
    if (data.length() > DATA_LEN)
    {
        Serial.println("string length is bigger than the block");
        return false;
    }
    for (int j = 0; j < DATA_LEN; j++)
    {
        if (j <= data.length())
            blockData[j] = data[j];
        else
            blockData[j] = '\n';
    }
    return true;
}

bool read_tag()
{
    detect_tag();

    Serial.print("\n");
    Serial.println("**Card Detected**");
    /* Authenticating the desired data block for Read access using Key A */
    status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, BLOCK_NUM, &key, &(rfid.uid));

    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Authentication failed for Read: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }
    else
    {
        Serial.println("Authentication success");
    }

    /* Reading data from the Block */
    status = rfid.MIFARE_Read(BLOCK_NUM, readBlockData, &bufferLen);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Reading failed: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }
    else
    {
        Serial.println("Block was read successfully");
        return true;
    }

    rfid.PICC_HaltA();      // halt PICC
    rfid.PCD_StopCrypto1(); // stop encryption on PCD
}

bool write_to_tag()
{
    detect_tag();
    Serial.print("\n");
    Serial.println("**Card Detected**");
    /* Authenticating the desired data block for write access using Key A */
    status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, BLOCK_NUM, &key, &(rfid.uid));
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Authentication failed for Write: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }
    else
    {
        Serial.println("Authentication success");
    }

    /* Write data to the block */
    status = rfid.MIFARE_Write(BLOCK_NUM, blockData, DATA_LEN);
    if (status != MFRC522::STATUS_OK)
    {
        Serial.print("Writing to Block failed: ");
        Serial.println(rfid.GetStatusCodeName(status));
        return false;
    }
    Serial.println("Data was written into Block successfully");
    return true;

    rfid.PICC_HaltA();      // halt PICC
    rfid.PCD_StopCrypto1(); // stop encryption on PCD
}

void WriteDataToTag(String data)
{
    if (!(setBlockData(data) && write_to_tag()))
        throw;
}

String GetDataFromTag()
{
    if (!read_tag())
        throw;
    return getReadData();
}