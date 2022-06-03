# School-Automation

## Entry
Within the scope of this project, dense index structure will be realized.
 An entry is stored in the index file for each record in the data file, which is realized as a binary file in this index structure.
 In the index file, the records are stored as <key address>.
 The address value indicates at which offset in the data file the information about the key is stored.
 Since there may be more than one record of the same key in the data file, there may be more than one record of the same key in the index file.
  
## What Can You Do  
You can add, delete and update student records.
  
  You save the student information in a file with the extension veri.bin, and you can view this file in a file with the extension index.txt.
  
## Functions
  
+ indexDosyasiOlustur : Assuming that a data file has not been indexed yet, an index file will be created for the records in the data file.
  
+ kayitEkle : A new record will be added to the data file. The new record should always be appended to the end of the data file. The index file must be updated after the record is added.

+ kayitBul : The first record in the data file for a given key will be displayed. Since there may be more than one record for the relevant key, the records of the key will be listed until the searched record is found. Binary search algorithm will be used to find the first record of the key in the index file.
 
+ kayitSil : For a given key, the corresponding correct record will be found (as in the FindRecord operation) and this record will be deleted. The deletion will also be reflected in the index file.
  
+ kayitGuncelle : The searched record for a key will be found and only the score field will be updated.
  
+ veriDosyasiniGoster : Lists all records in the data file.
  
+ indeksDosyasiniGoster : Shows all records in the index file.
  
+ indeksDosyasiniSil : İndeks dosyasını diskten siler.
  
