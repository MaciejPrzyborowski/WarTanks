# WarTanks

Prezentacja gry: https://www.youtube.com/watch?v=zdRUibWN_gk

Gra posiada menu, które posiada następujące opcje:

Graj:

      rozpoczyna grę offline - 2 graczy każdy strzela na zmianę
      
Ustawienia:

      włącz/wyłącz licznik FPS
      
      włącz/wyłącz muzyke w grze
      
      włącz/wyłącz muzyke w menu
      
      włącz/wyłącz dźwięki w menu
      
Wyjście:

      zamyka grę

Po wejściu w aplikację WarTanks pokazuje się menu główne gry oraz odpala się muzyka. Po menu można poruszać się zarówno myszką (LPM wybiera daną opcje) jak i klawiaturą (nawigacja: strzałka w górę oraz strzałka w dół, enter aby wybrać). Wybrana przez nas opcja w menu będzie miała zmieniony odcień aby użytkownik wiedział co wybiera, przy każdej zmianie wyboru towarzyszy nam dźwięk "przeskoku" (typowy dla menu), który można wyłączyć w ustawieniach tak samo jak muzyka w menu czy w grze. W ustawieniach można włączyć również licznik klatek na sekundę, który wyświetla się w lewym górnym rogu.

Po wybraniu opcji "Graj" rozpoczyna się gra. Na mapie pojawiają się 2 czołgi (czerwony i niebieski) o losowej pozycji początkowej, ale zawsze czerwony po lewej, niebieski po prawej. Teren gry generuje się z wykorzystaniem szumu Perlina. Gracze strzelają na zmianę i każdy na oddanie strzału ma 15 sekund. W tym czasie mogą się poruszać, ustawić lufę pod odpowiednim kątem i oddać strzał. W momencie oddania strzału tura automatycznie się kończy i jest kolej drugiego gracza. Po nieoddanym strzale tura danego gracza kończy się.

Gracze mogą zarządzać siłą strzału, gdy przytrzymają strzałkę w górę siła strzału zwiększy się, analogicznie strzałka w dół - zmniejszy się. Siła strzału może wynosić minimalnie 0 i maksymalnie 100 - w zależności wartości zmienia się kolor paska siły, im większa siła tym pasek bardziej zielony, im mniejsza to pasek czerwony - ma to zwrócić uwagę gracza, że gdy wybierze małą siłę strzału to pocisk może uderzyć w jego samego i wiąże się z tym utrata punktów życia.

W rogach gry (lewy górny i prawy górny) pokazany jest pasek punktów życia danego gracza, który również zmienia kolor w zależności od liczby HP. Po środku, na górze ekranu widoczny jest łączny czas gry w sekundach, siła strzału oraz kąt nachylenia lufy. Na dole zaś jest napis, którego gracza jest teraz kolej oraz ile czasu ma na oddanie strzału.

Gracze mogą poruszać się czołgiem lewo (strzałka w lewo) i prawo (strzałka w prawo). Poruszanie nie jest możliwe dla dużych wzniesień i spadków terenu - maksymalny kąt pod który może wjechać czołg to 75 stopni, ale również czołg nie może zjechać gdy spadek wynosi więcej niż 75 stopni.

Aby ustawić kąt nachylenia lufy należy kliknąć LPM, mamy wtedy możliwość obracania jej w pełnym zakresie (360 stopni), gdy dostosujemy już kąt lufy ponownie klikamy LPM aby zaakceptować. W momencie ustawienia kąta lufy nie można się poruszać! Aby oddać strzał trzeba kliknąć spację. Jeżeli czołg znajdzie się w promieniu wybuchu strzału to straci on 25 punktów życia. W przypadku zderzenia się pocisku z ziemią będzie on niszczył teren w kształt okręgu oraz pokaże się animacja wybuchu, a wisząca ziemia będzie opadała.

Gra zostanie zakończona w momencie gdy jeden z graczy straci wszystkie punkty życia. Istnieją 2 zakończenia gry: wygra jeden z graczy lub będzie remis. W pierwszym przypadku na środku ekranu pokazuje się napis kto wygrał, nad przegranym pokazuje się animacja płomienia, nad zwycięzcą animacja z fajerwerkami i towarzyszyć będzie temu dźwięk wybuchu fajerwerków. W przypadku remisu nie pokazują się żadne animacje, ani nie ma dodatkowych dźwięków. W obu przypadkach po 2 sekundach od zakończenia gry na dole ekranu pokazuje się napis "Kliknij enter aby wrócić do menu".

# Klasy:
```
Animation
Bullet
Game
Globals
Interface
Land
Menu
Perlin
Tank
World
WorldObject
```
*w celu otworzenia pełnej gry należy wszystkie pliki z folderu "data" wrzucić do folderu build

Podział pracy:

Maciej Przyborowski:
```
      - poruszanie czołgiem
            - prędkość zależna od kąta nachylenia terenu
            - poruszanie nie jest możliwe dla dużych wzniesień i spadków (max 75 stopni)
      - wystrzeliwanie pocisku
            - akceleracja
            - przyśpieszenie
      - obsługa terenu
            - generowanie terenu z zastosowaniem szumu Perlina
            - niszczenie terenu przez pocisk w kształcie okręgu
            - obliczanie kąta nachylenia terenu
            - kolor terenu: gradient z zastosowaniem interpolacji liniowej
      - kolizja
            - czołg z czołgiem
            - pocisk z czołgiem
      - grawitacja
            - czołgu - gdy teren pod czołgiem się niszczy to czołg spada
            - pocisku - rzut ukośny
            - terenu - opadanie wiszącego terenu
      - zmiana tury graczy
            - obsługa czasu tury dla gracza
            - zmiana tury gdy skończy się czas lub wybuchnie pocisk
      - zmiana architektury gry
```            
Mateusz Kozłowski
```
      - interfejs:
            - menu
            - punkty życia
            - siła strzału
            - czas gry
            - czas tury
            - kąt nachlenia
            - FPS     
      - animacje
            - animacja wybuchu
            - fajerwerków
            - płomienia
      - grafiki
            - grafika menu
            - tło gry
            - wygląd czołgów oraz lufy
      - muzyka
            - muzyka w grze
            - muzyka w menu
            - dżwięk przy wyborze
            - dźwięk wystrzału
            - dźwięk wybuchu
            - dźwięk fajerwerków
      - zmienianie kąta lufy przez myszkę
      - dźwięki w grze
      - siła strzału
            - zmiana siły strzału zakres od 0 do 100
      - punkty życia
      - zakończenie gry
            - wygrywa jeden z graczy lub remis i pokazuje sie stosowny do tego napis
      - wdrożenie ustawień z menu do gry
            - licznik FPS
            - muzyka w menu
            - muzyka w grze
            - dźwięk w menu
```      
Wspólnie:
```
      - menu
      - obsługa zdarzeń wykonywanych przez gracza
            - spacja - strzał
            - strzałka w lewo lub prawo - poruszanie
            - strzałka w górę lub dół - siła strzału
            - sprawne poruszanie się myszką lub klawiaturą po menu
            - enter aby wrócić do menu (na koniec gry)
      - opisy funkcji
```

![menu](images/mainMenu.png)
![ustawienia](images/settingsMenu.png)
![gra](images/game.png)
![koniec1](images/endGame1.png)
![koniec2](images/endGame2.png)
