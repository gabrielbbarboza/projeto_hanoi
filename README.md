# **O Salão das Três Colunas: O Desafio Enigmático (Torre de Hanói)** #

Este projeto é uma implementação do clássico jogo Torre de Hanói em C, com um toque de RPG e um sistema de registro de crônicas (histórico de partidas). 
Desenvolvido para demonstrar o uso de estruturas de dados (pilhas e listas encadeadas), alocação dinâmica de memória e manipulação de arquivos.

### Funcionalidades ###

_``Desafio da Torre de Hanói:``_ Jogue o clássico quebra-cabeça com um número configurável de discos (de 2 a 10).

_``Interface no Terminal:``_ Exibição visual das torres e discos usando arte ASCII. 

_``Sistema de Crônicas (Histórico):``_ Registra o nome do aventureiro, número de movimentos, quantidade de discos e a data/hora de conclusão de cada partida vitoriosa.
Armazena as crônicas em uma lista encadeada na memória.

_``Persistência de Dados:``_ Salva e carrega o histórico de crônicas em um arquivo de texto (cronicas.txt), garantindo que suas aventuras não sejam esquecidas!

_``Consulta de Histórico:``_ Visualize todas as crônicas registradas.

_``Busca:``_ Encontre crônicas específicas por nome do aventureiro ou por data/hora.

_``Gestão de Memória:``_ Alocação e liberação de memória dinâmicas para as crônicas, prevenindo vazamentos de memória.

_``Como Compilar e Rodar``_ Este projeto pode ser compilado com um compilador C padrão, como o GCC.

_``Pré-requisitos``_ Um compilador C (ex: GCC)``_

## Estrutura do Projeto ##

### **``main.c``** ###

O Coração do Reino. Este arquivo contém a função main(), que atua como o menu principal, orquestrando a interação do usuário com o jogo e o histórico.

### **``cronicas.h:``** ###

O Pergaminho dos Registros Antigos. Definições da estrutura Cronica e protótipos das funções para gerenciar o histórico.

### **``cronicas.c:``** ###
 
A Biblioteca de Históricos do Guardião. Contém a implementação completa das funções de manipulação do histórico (adicionar, exibir, buscar, salvar, carregar, liberar).

### **``desafio_enigmatico.h:``** ###

O Pergaminho das Leis da Torre. Define a estrutura de um Pináculo e os protótipos das funções que governam a lógica do jogo Torre de Hanói.

### **``desafio_enigmatico.:c``** ###

O Salão de Três Colunas. Aqui se encontra a implementação detalhada do jogo da Torre de Hanói, desde a preparação dos pináculos até a verificação da vitória e a exibição visual.

### **``grimorio.h:``** ###

O Grimório da Sabedoria Antiga. Este cabeçalho contém protótipos para funções utilitárias de entrada de dados, como ´´decifrarNumero´´ e ´´obterTextoDoAventureiro´´, garantindo que as informações inseridas pelo aventureiro sejam válidas.

### **``grimorio.c:``** ###

Os Feitiços de Interação. Aqui estão as implementações das funções utilitárias que facilitam a interação com o jogador, tratando a entrada de dados de forma segura e validada.

![image](https://github.com/user-attachments/assets/367a8a2a-4662-4deb-a4a8-8ecd653f32d3)


#### Feitiços de Gratidão ####

**site utilizado utilizado para codar e compilar:** https://replit.com/~

Este projeto foi desenvolvido com base nos conhecimentos adquiridos em disciplinas de Estruturas de Dados e Programação em C. Agradeço especialmente a João Robson pela inspiração e suporte.

---
