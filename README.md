# Turing Machine

Um simulador de Maquina de Turing Determinístico Reconhecedora de Linguagens.

## Como Compilar
```
$ cd turing-machine/
$ make all
```
## Run
```
$ ./tm Text_input.txt
```
## Rodando Com algum exemplo
```
$ ./tm exemplo/anbn.txt
```

## Exemplo do Texto_input Para o Teste
```
aaaaabbbbb
q0 a x r q1
q1 a a r q1
q1 y y r q1
q1 b y l q2
q2 a a l q2
q2 y y l q2
q2 x x r q0
q0 y y r q3
q3 y y r q3
q3 _ _ l q4
accept q4 q3
```

### 🔥 Fique a vontade para melhorar dando algum PR 🔥