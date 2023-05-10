Egy program, mely egy .txt kiterjesztésű fájlból beolvas egy szöveget, ami a karakterenkénti letárolást is jelenti. A beolvasott szöveg adatait strutúrákban tároljuk. Majd ASCII kód tábla szerint átalakítja azokat 10-es számrendszerbe, mivel az RSA kódoláshoz az lesz szükséges és számomra, így könnyebb vele számolni, és a struktúra egyik int tömbjében letárolja. Majd RSA kódolással lekódolja a karaktereket. Az RSA algoritmus prím számai és egyéb változói meg lesznek adva a programon belül. Ezeket egy függvény segítségével kiírja egy másik .txt fájlba. Egy másik függvény pedig a kódot vissza alakítja az eredeti formátumba, majd kiírja egy .txt fájlba.

A program C nyelven 
    szekvenciálisan, 
    szálakkal, 
    OpenMP-vel 
    és C# program nyelvben lévő szálak használatával
történő futási időt is dokumentálja. A C# program nyelven létrehozott szálakkal készült program futási idejét, a kódolás és a dekódolás idejét egy másik fájlba gyűjtöm ki, majd az összes adatot egy Excel fájlba egyesítem és diagram segítségével vizuálisan megjelenítem.