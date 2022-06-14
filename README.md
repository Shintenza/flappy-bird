# Flappy Bird - Projekt zaliczeniowy z języka C++

## Spis treści:
1. [Kilka słów o projekcie](#kilka-słów-o-projekcie)
2. [Zależności](#zależności)
3. [Kompilacja i użytkowanie](#kompilacja-i-użytkowanie)

## Kilka słów o projekcie
Projekt ten jest próbą odtworzenia kultowej gry na urządzenia mobilne, jaką jest Flappy Bird. Gra powstała w oparciu o takie biblioteki jak SFML, czy sqlite3.
Projekt testowany (i pisany) był na systemie GNU/Linux, więc nie wiem, czy działa na systemie Windows. 

## Zależności
Do poprawnego działania gry, wymagane są poniższe zależności:
- [SFML](https://www.sfml-dev.org/)
- [sqlite3](https://www.sqlite.org/index.html)
- [make](https://www.gnu.org/software/make/)

## Kompilacja i użytkowanie
Przed rozpoczęciem procesu kompilacji programu upewnij się, że masz zainstalowane wszystkie, wymagane zależności:

ArchLinux:
> sudo pacman -S sqlite sfml make g++

Fedora:
> sudo dnf install sqlite sqlite-devel SFML SFML-devel make g++

Debian:
> sudo apt install libsqlite3-dev libsfml-dev make g++

### Uruchamianie/kompilowanie
Będąc w katalogu projektu, uruchom polecenie `make run`
