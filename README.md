# 💣 Bomber Rush

<p align="center">
  <img src="assets/LOGO.png" alt="Logo do projeto" width="350"/>
</p>

# 💥 Bomber Rush

**Bomber Rush** é um modo original inspirado no clássico *Bomberman*, desenvolvido em **C** utilizando a biblioteca gráfica **Raylib** e com suporte a controles através da **SDL2**.

O jogo coloca **1 a 4 jogadores** em uma arena dinâmica onde o objetivo é simples e direto: **sobreviver o máximo de tempo possível**.

---

## 👥 Equipe de Desenvolvimento

- [**João Passos**](https://github.com/iampassos)
- [**Mircio Ferreira**](https://github.com/Mircio-Ferreira)
- [**Thiago Fernandes**](https://github.com/ThIagoMedeiros21)
- [**Gabriel Aniceto**](https://github.com/gabrielaniceto1)

---

## 🎬 Vídeos de Demonstração (YouTube)

- [**Demonstração do Gameplay — YouTube**](https://youtu.be/CFksENJ9CzU)  
- [**Demonstração Técnica (Modo Debug) — YouTube**](https://youtu.be/gXLOxB3hNz4)
- [**Link backup de vídeo via google drive**](https://drive.google.com/drive/folders/12B128QSV8odMmiVKKyRhX1gSiA0wLOK6?usp=sharing
)



---

## 🛠️ Compilando

Para jogar o **Bomber Rush**, é necessário ter **Raylib** e **SDL2** instaladas no sistema.  
O projeto funciona em **Windows** e **Linux**, e inclui **Makefiles específicos para cada plataforma**.

**Linux:**

*Abra seu terminal do Linux e siga as etapas:*
- instalação das bibliotecas basicas de copilação:
```bash
# Ubuntu:
sudo apt update
sudo apt install build-essential
```
- Instalação Git:
```bash
# Ubuntu:
sudo apt install git
```

- Instalação da Biblioteca de Controles SDL2:
 ```bash
# Ubuntu:
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```
- Instalação da Biblioteca grafica Raylib.h:
```bash
# Ubuntu:
sudo apt install cmake
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt install libwayland-dev wayland-protocols libxkbcommon-dev
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build
cd build
cmake ..
make
sudo make install



```
- Clone o Repositório:
```bash
git clone https://github.com/iampassos/bomber-rush.git
```

- Acesse a pasta do Repositório:
```bash
cd bomber-rush/
```
- Compile o jogo:
```bash
make
```
- rode o jogo
```bash
./game.out
```

**Windows:**

Siga estes passos para configurar o ambiente e executar o **Bomber Rush** no Windows:

### 1. Instalar o MSYS2

- Baixe e instale o MSYS2 a partir do site oficial:  
  https://www.msys2.org/

### 2. Abrir o Terminal MSYS2

- Após a instalação, abra o menu Iniciar do Windows e execute o terminal:  
  **MSYS2 UCRT64 (mingw64/ucrt64)**  
  (é importante usar o terminal UCRT64, pois é nele que instalaremos as dependências).

### 3. Instalar Ferramentas de Compilação

No terminal **UCRT64**, execute o comando abaixo para instalar GCC, Make e ferramentas essenciais:

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain git
```
### 4. Adicionar o GCC ao Path do Windows

1. No Windows, pesquise por “variáveis de ambiente” e abra
Editar as variáveis de ambiente do sistema.

2. Clique em Variáveis de Ambiente….

3. Em Variáveis do sistema, localize a variável Path e clique em Editar.

4. Adicione um novo caminho apontando para o diretório bin do UCRT64, por exemplo:

```text
C:\msys64\ucrt64\bin
```
5. Confirme todas as janelas com OK.

### 5. Instalar as Bibliotecas Raylib e SDL2

Ainda no terminal UCRT64, instale a Raylib:

```bash
pacman -S mingw-w64-ucrt-x86_64-raylib
```
Em seguida, instale a SDL2 e extensões usadas no projeto:
```bash
pacman -S mingw-w64-ucrt-x86_64-SDL2 \
          mingw-w64-ucrt-x86_64-SDL2_image \
          mingw-w64-ucrt-x86_64-SDL2_mixer \
          mingw-w64-ucrt-x86_64-SDL2_ttf
```
### 6. Clonar o Repositório

No mesmo terminal, escolha uma pasta de sua preferência e execute:
```bash
git clone https://github.com/iampassos/bomber-rush.git
cd bomber-rush
```
7. Compilar e Executar o Jogo

Dentro da pasta do projeto, use o Makefile específico de Windows:
```bash
mingw32-make -f MakeFileWindows clean && mingw32-make -f MakeFileWindows run
```
Se preferir rodar em comandos separados:
```bash
mingw32-make -f MakeFileWindows clean
mingw32-make -f MakeFileWindows run
```
Após a compilação, o jogo será iniciado automaticamente.
## 🎮 Jogabilidade

Durante a partida:

- 💣 **Bombas** surgem aleatoriamente pelo mapa.  
- 👾 **Inimigos** aparecem e podem se acumular se não forem derrotados.  
- ⭐ Cada bomba explodida ou inimigo derrotado pode gerar um **power-up**, facilitando sua sobrevivência.

---

## 📈 Escalonamento de Dificuldade

Com o passar do tempo, o jogo se torna progressivamente mais difícil:

- ⏳ Bombas aparecem em intervalos menores.  
- 🔥 As explosões ficam mais fortes.  
- ⚠️ Os inimigos se tornam mais perigosos e numerosos.

---

## 🧠 Estratégia

Você pode:

- 🎯 **Atrapalhar outros jogadores**,  
- 🤝 **Cooperar temporariamente**,  

No final, apenas uma regra importa:

**Sobreviva. Engane. Coopere. Traia.  
Faça o que for preciso para ser o último jogador de pé em *Bomber Rush*.**

---

## 🕹️ Como Jogar

Os jogadores são reconhecidos automaticamente pelo controle — basta conectar os controles para que os jogadores apareçam no mapa.

> ⚠️ **Observação:**  
> Os controles estão mapeados para um gamepad específico que simula o controle do **Super Nintendo**.  
> Portanto, é necessário usar esse tipo de controle para jogar via controle no momento.  
>  
> <img src="assets/readme_icons/controle_image.jpg" alt="Controle suportado" width="350"/>

### 🛠️ Controles — Modo Debug

Além dos controles padrão, o jogo possui teclas especiais para depuração, úteis para inspecionar o funcionamento interno durante o desenvolvimento:

- 🧩 **F1 — Debug de Entidades e Jogador:**  
  Exibe informações internas sobre entidades ativas e estado do jogador.

- 🧱 **F2 — Debug de Colisões:**  
  Mostra visualmente as colisões detectadas no mapa.

- 🗺️ **F3 — Debug da Matriz de Tiles:**  
  Revela a grade da matriz utilizada na lógica do mapa.

---

### ⌨️ Controles — Teclado (modo 1 jogador)

Mesmo não sendo o ideal (a diversão real é no multiplayer), é possível jogar sozinho usando teclado:

- 🕹️ **Movimentação:** `W`, `A`, `S`, `D`  
- 💣 **Colocar bomba:** `SPACE`  
- 🖥️ **Alternar Fullscreen:** `F11`

---

## 👾 Inimigos

Os inimigos aparecem na arena e se acumulam com o tempo, aumentando a pressão sobre os jogadores.  
Abaixo está a imagem demonstrando **um dos inimigos** (mais inimigos serão adicionados futuramente).

### **Ballom**  
Este é um inimigo básico do jogo. Ele se movimenta pelo mapa de forma aleatória e é derrotado com apenas um golpe.

<p align="center">
  <img src="assets/sprites/enemies/ballom/UP1.png" alt="Inimigo - Cima" width="100"/>
  <img src="assets/sprites/enemies/ballom/DOWN1.png" alt="Inimigo - Baixo" width="100"/>
  <img src="assets/sprites/enemies/ballom/LEFT1.png" alt="Inimigo - Esquerda" width="100"/>
  <img src="assets/sprites/enemies/ballom/RIGHT1.png" alt="Inimigo - Direita" width="100"/>
</p>

---

### 💣 Bomba Gerada pela Máquina

<p align="center">
  <img src="assets/sprites/maps/bomb_zone/BOMB_MACHINE1.png" alt="Bomba da máquina" width="120"/>
</p>

Bombas especiais colocadas automaticamente pela máquina.  
Elas aparecem em intervalos cada vez menores e possuem força de explosão crescente conforme o jogo progride.

---

## ⭐ Power-ups

A cada bomba explodida ou inimigo derrotado, existe a chance de surgir um **power-up**.

### 🔹 Vida Extra  
<img src="assets/sprites/power_ups/LIFE_1.png" alt="Power-up Vida" width="50"/>  

**Descrição:** Aumenta a vida do jogador.  
*(Máximo de 5 vidas)*

---

### 🔹 Aumento de Limite de Bombas
<img src="assets/sprites/power_ups/BOMB_1.png" alt="Power-up X" width="50"/>  

**Efeito:** Aumenta em **+1** a quantidade máxima de bombas que o jogador pode colocar simultaneamente no mapa (Máximo de 5 )
 

---

### 🔹 Aumento de Raio de Explosão  
<img src="assets/sprites/power_ups/RADIUS_1.png" alt="Power-up Raio +" width="50"/>  

**Descrição:** Aumenta o raio de explosão da bomba em **+1 nível**.

---

### 🔹 Raio de Explosão Máximo  
<img src="assets/sprites/power_ups/MAXIMUM_RADIUS_2.png" alt="Power-up Raio Máximo" width="50"/>  

**Descrição:** Um power-up **especial e muito raro**.  
Instantaneamente define o raio de explosão da bomba para o **nível máximo**.

---

### 🔹 Invencibilidade  
<img src="assets/sprites/power_ups/INVENCIBLE_1.png" alt="Power-up Invencível" width="50"/>  

**Descrição:** Torna o jogador **invencível por 7 segundos**.  
Durante o efeito, o personagem fica **piscando** como indicação visual.

---

### 🔹 Velocidade  
<img src="assets/sprites/power_ups/SPEED_UP_1.png" alt="Power-up Velocidade" width="50"/>  

**Descrição:** Aumenta a velocidade de movimentação do jogador.  
O efeito é **acumulativo** — quanto mais power-ups coletados, mais rápido o jogador se torna.

---
## 🗺️ Mapas

O jogo possui atualmente **8 mapas**, cada um com seu próprio visual.

---

### 🗺️ Mapa 1 — *BELT ZONE*
<p align="center">
  <img src="assets/sprites/maps/belt_zone/MAP.png" alt="Mapa 1" width="350"/>
</p>

---

### 🗺️ Mapa 2 — *BOMB ZONE*
<p align="center">
  <img src="assets/sprites/maps/bomb_zone/MAP.png" alt="Mapa 2" width="350"/>
</p>

---

### 🗺️ Mapa 3 — *DUEL ZONE*
<p align="center">
  <img src="assets/sprites/maps/duel_zone/MAP.png" alt="Mapa 3" width="350"/>
</p>

---

### 🗺️ Mapa 4 — *JUMP ZONE*
<p align="center">
  <img src="assets/sprites/maps/jump_zone/MAP.png" alt="Mapa 4" width="350"/>
</p>

---

### 🗺️ Mapa 5 — *LIGHT ZONE*
<p align="center">
  <img src="assets/sprites/maps/light_zone/MAP.png" alt="Mapa 5" width="350"/>
</p>

---

### 🗺️ Mapa 6 — *NORMAL ZONE*
<p align="center">
  <img src="assets/sprites/maps/normal_zone/MAP.png" alt="Mapa 6" width="350"/>
</p>

---

### 🗺️ Mapa 7 — *SPEED ZONE*
<p align="center">
  <img src="assets/sprites/maps/speed_zone/MAP.png" alt="Mapa 7" width="350"/>
</p>

---

### 🗺️ Mapa 8 — *WESTERN ZONE*
<p align="center">
  <img src="assets/sprites/maps/western_zone/MAP.png" alt="Mapa 8" width="350"/>
</p>

---