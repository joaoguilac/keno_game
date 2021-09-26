[![Work in Repl.it](https://classroom.github.com/assets/work-in-replit-14baed9a392b3a25080506f3b7b6d57f295ec2978f6f33ec97e36a161684cbe9.svg)](https://classroom.github.com/online_ide?assignment_repo_id=433779&assignment_repo_type=GroupAssignmentRepo)

# Trabalho 03: O Jogo Keno
Nesse trabalho você vai desenvolver um pequeno jogo no terminal que simula um clássico [jogo de azar](https://pt.wikipedia.org/wiki/Jogo_de_azar) chamado [Keno](https://en.wikipedia.org/wiki/Keno).
Mais detalhes sobre o projeto você pode encontrar [aqui](docs/projeto_keno.pdf).

Não esqueça de preencher o arquivo [`autor.md`](author.md) antes de submeter seu projeto.

# Compilando e Executando

## Manualmente com g++

Para compilar e executar o programa manualmente basta digitar os seguintes comandos em seu terminal:

```
$ mkdir bin (caso não tenha uma pasta para os executáveis, você deve criá-la com esse comando)
$ g++ -Wall -std=c++11 -g source/src/main.cpp source/src/keno_bet.cpp source/src/game_manager.cpp -I source/include -o bin/keno (compilar)
$ ./bin/keno <diretório do arquivo com sua aposta> (executar)
```

## Cmake

Para compilar e executar o programa com o Cmake você precisa ter instalado pelo menos a versão 3.2. Em seguida, abra seu terminal e execute os seguintes comandos:

```
$ cmake -S source -B build (pede ao cmake para criar o diretório de compilação)
$ cmake --build build (compilar)
$ ./build/keno <diretório do arquivo com sua aposta> (executar)
```

Os arquivos com apostas devem ser salvos na pasta `data` (se isso for feito, para executar basta `./build/keno ./data/<arquivo com sua aposta>`. Já existem alguns exemplos de arquivos de aposta nesta pasta. É possível utilizá-los, mas você pode criar o seu próprio também.