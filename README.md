
### Popis aplikace
Tato aplikace je zaměřena na testování a trénink vizuálních schopností. Obsahuje následující klíčové funkce:

1. **Acuity testing (test ostrosti zraku):**
   - Měří schopnost oka rozlišit detaily a ostrost skrze zobrazení náhodných písmen o proměnné velikosti
   - Využívá simulaci písmen Snellenovy tabulky.
   - Test se standartně provádí ve vzdálenosti 10 stop (305 cm) za použití bezdrátové klávesnice
2. **Acuity training (trénink ostrosti zraku):**
   - Umožňuje trénink zrakové ostrosti s možností nastavení fontu i velikosti zobrazovaných písmen

### Jak používat aplikaci
Zdrojový kod aplikace byl napsán a otestován v prostředí Visual Studio 2022 s rozšířením a knihovnou funkcí pro CLR .NET framework. Tato aplikace je určená uživvatelům se základní znalostí Visual Studio 2022. 

Při spuštění aplikace se zobrazí hlavní okno aplikace, jehož klíčové prvky jsou naprogramovány v souboru MainMenuForm.h
Uživatel má možnost volit mezi dvěma možnostmi. Testem zrakové ostrosti a Tréninkem zrakové ostrosti.
   Deklarace funkcí a tlačítek programu testu zrakové ostrosti jsou uloženy v souboru MainForm.h
   Deklarace Tréninku ostrosti jsou v souboru VisualTrainingForm.h
   Spouštění aplikace se provádí v souboru MainForm.cpp

Po spuštění testu zrakové ostrosti je uživateli zobrazeno náhodné písmeno. Uživatel odpovídá zadáním písmene do pole odpovědi a stisknutím klávesy ENTER. Když odpoví 3x správně dojde ke zmenšení velikosti písmen. Pokud uživatel odpoví špatně více než 3x test by měl ukončit. Výsledkem testu je dosažená velikost písma. Test je možné opakovat, a tak sledovat případné zlepšení.

Pokud si uživatel v hlavním okně zvolí možnost Trénink zrakové ostrosti, otevře se tréninkové okno. Zde si uživatel nastavuje velikost a font písma, které se bude zobrazovat. Po stisknutí tlačítka nastavit font se nový font zobrazí. Pak stačí jen kliknout do pole odpovědí a zadat písmeno. Není vyžadován ENTER pro potvrzení odpovědi.


