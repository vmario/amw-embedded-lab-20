---
title: "Ćwiczenie 20: Gra sterowana czujnikiem ruchu"
subtitle: "Instrukcja laboratorium"
footer-left: "Instrukcja laboratorium"
author: [Mariusz Chilmon <<mariusz.chilmon@ctm.gdynia.pl>>]
lang: "pl"
titlepage: yes
titlepage-logo: "logo.png"
logo-width: "70mm"
colorlinks: yes
header-includes: |
  \usepackage{awesomebox}
  \usepackage{algorithm}
  \usepackage{algpseudocode}
  \usepackage{tikz}
  \usetikzlibrary{automata, positioning, arrows, shapes, patterns}
  \usepackage{tikz-timing}
  \usepackage{xfrac}
  \usepackage{ellipsis}
  \usetikzlibrary{positioning}
  \usepackage[raster]{tcolorbox}
  \usepackage{lcd}
  \LCDcolors[MidnightBlue]{MidnightBlue!10}{MidnightBlue!80}
...

\lstset{language=[11]C++}
\tikzset{
    >=stealth',
    node distance=2.8cm,
    every state/.style={thick, fill=gray!20, align=center, text width=1.1cm},
    auto,
    font=\footnotesize,
}

> Talk is cheap. Show me the code.
>
> — _Linus Torvalds_

# Cel ćwiczenia

Celem ćwiczenia jest praktyczne ćwiczenie umiejętności odnajdywania w kodzie źródłowym implementacji poszczególnych funkcji systemu mikroprocesorowego i ich poprawy.

# Uruchomienie programu wyjściowego

1. Podłącz płytkę _LCD Keypad Shield_ do _Arduino Uno_.
1. Podłącz akcelerometr.
1. W pierwszej linii wyświetlacza widoczny jest licznik zdobytych punktów.
1. W drugiej linii wyświetlacza na pierwszej pozycji znajduje się statek kosmiczny, który jest bohaterem gry, a na prawo od niego wrogie pojazdy, których należy unikać, aby kontynuować grę. Zderzenie kończy rozgrywkę.
1. Program wyjściowy nie pozwala poruszać statkiem.

\DefineLCDchar{player}{00000011001101001001110100110000000}
\DefineLCDchar{enemy}{00000111111101110101110111111100000}
\begin{center}
\LCD{2}{16}
    |           01042|
    |{player}     {enemy}      {enemy}  |
\captionof{figure}{Przykładowy stan gry. Uwagę przykuwają, mimo rachitycznej grafiki, znakomicie zamodelowani bohaterowie i bezkompromisowa wizualizacja świata z gatunku \textit{space opera}.}
\end{center}

# Zadanie podstawowe

Celem zadania podstawowego jest sterowanie pojazdem kosmicznym przez obrót czujnika.

## Wymagania funkcjonalne

1. Obrót czujnika powoduje skok pojazdu do góry. Po chwili pojazd automatycznie powraca na pozycję wyjściową.

## Modyfikacja programu

W metodzie `Game::loop()` odczytaj pomiar z żyroskopu za pomocą wywołania `gyroscope.measure()`. Określ wartość graniczną prędkości kątowej, przy której uznasz, że należy wykonać skok główną postacią gry, ustawiając zmienną `hop` na wartość `HOP_UP`.

\awesomebox[teal]{2pt}{\faCode}{teal}{Pamiętaj o użyciu bloku \lstinline{ATOMIC\_BLOCK(ATOMIC\_RESTORESTATE) \{ \}}, aby uniknąć problemów z operacjami na zmiennych współdzielonych między pętlą główną, a przerwaniami.}

# Zadanie rozszerzone

Celem zadania rozszerzonego jest umożliwienie wznowienia rozgrywki po wciśnięciu przycisku _RIGHT_.

## Wymagania funkcjonalne

1. Przyciskiem _RIGHT_ można rozpocząć nową rozgrywkę.

## Modyfikacja programu

W metodzie `Game::loop()` odczytaj stan klawiatury i przy wciśniętym przycisku _RIGHT_ wywołaj metodę `start()`. Dodatkowo możesz sprawdzać stan zmiennej `stop` (zerowanej przez `start()`) , aby przytrzymanie przycisku nie powodowowało wielokrotnego wywoływania restartu gry.

\awesomebox[violet]{2pt}{\faBook}{violet}{Odczytaj ze schematów ideowych, do którego pinu mikrokontrolera podłączona jest klawiatura.}

\awesomebox[purple]{2pt}{\faMicrochip}{purple}{Nie musisz korzystać z ADC, aby sprawdzić stan przycisku. Ponieważ inne przyciski nie będą wykorzystywane, wystarczy odróżnić stan niski od wysokiego, nie ma potrzeby mierzyć dokładnego napięcia z klawiatury.}
