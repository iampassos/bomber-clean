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

## 🎬 Vídeo Demonstrativo

- [**Link para o vídeo no YouTube**]() *(em breve)*

---

## 🛠️ Compilando

Para jogar o **Bomber Rush**, é necessário ter **Raylib** e **SDL2** instaladas no sistema.  
O projeto funciona em **Windows** e **Linux**, e inclui **Makefiles específicos para cada plataforma**.

---

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

### 🎮 Controles — Gamepad

- 🕹️ **Movimentação:** Setas do controle  
- 💣 **Colocar bomba:** Botão **Y** ou **B**  

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
