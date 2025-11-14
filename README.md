# 💣 Bomber Rush

<img src="assets/LOGO.png" alt="Logo do projeto" width="350"/>

# 💥 Bomber Rush

**Bomber Rush** é um modo original inspirado no clássico *Bomberman*, desenvolvido em **C** utilizando a biblioteca gráfica **Raylib** e com suporte a controles através da **SDL2**.

O jogo coloca **1 a 4 jogadores** em uma arena dinâmica onde o objetivo é simples e direto: **sobreviver o máximo de tempo possível**.

## 👥 Equipe de Desenvolvimento

- [**João Passos**](https://github.com/iampassos)
- [**Mircio Ferreira**](https://github.com/Mircio-Ferreira)
- [**Thiago Fernandes**](https://github.com/ThIagoMedeiros21)
- [**Gabriel Aniceto**](https://github.com/gabrielaniceto1)

## 🎮 Jogabilidade

Durante a partida:

- 💣 **Bombas** surgem aleatoriamente pelo mapa.  
- 👾 **Inimigos** aparecem e podem se acumular se não forem derrotados.  
- ⭐ Cada bomba explodida ou inimigo derrotado pode gerar um **power-up**, facilitando sua sobrevivência.

## 📈 Escalonamento de Dificuldade

Com o passar do tempo, o jogo se torna progressivamente mais difícil:

- ⏳ Bombas aparecem em intervalos menores.  
- 🔥 As explosões ficam mais fortes.  
- ⚠️ Os inimigos se tornam mais perigosos e numerosos.

## 🧠 Estratégia

Você pode:

- 🎯 **Atrapalhar outros jogadores**,  
- 🤝 **Cooperar temporariamente**,  

No final, apenas uma regra importa:

**Sobreviva. Engane. Coopere. Traia.  
Faça o que for preciso para ser o último jogador de pé em *Bomber Rush*.**


## 🎬 Vídeo Demonstrativo

- [**Link para o vídeo no YouTube**]() *(em breve)*

## 🛠️ Compilando

### ✅ Instale a Raylib

ainda falta fazer



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



