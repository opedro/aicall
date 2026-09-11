# CallAI

Projeto foda em C++ que consulta APIs de clima, piadas e Gemini.

[![Build Status](https://img.shields.io/github/actions/workflow/status/opedro/aicall?branch=main&logo=github)](https://github.com/opedro/aicall/actions)
[![Latest Release](https://img.shields.io/github/v/release/opedro/aicall?logo=github)](https://github.com/opedro/aicall/releases/latest)
[![Contributors](https://img.shields.io/github/contributors/opedro/aicall?logo=github)](https://github.com/opedro/aicall/graphs/contributors)

## Dependências

No Linux, execute:

```bash
./dependencies.sh
```


## Compilação

```bash
./compile.sh
```

## Uso

```bash
./callAI clima
./callAI piada
./callAI gemini
```

Também é possível usar os números:

```bash
./callAI 1
./callAI 2
```

## Chave da API

Antes de usar o Gemini, abra `callai.cpp` e substitua:

```cpp
string api_key = "APIKEY AQUI";
```

pela sua chave da API.

## Docker

Instale e inicie o Docker Desktop. Depois, na pasta do projeto, crie a imagem:

```bash
docker build -t callai .
```

Execute o clima:

```bash
docker run --rm callai clima
```

O modo `clima` não é interativo e apenas mostra a temperatura.

Execute a piada:

```bash
docker run --rm -it callai piada
```

O modo `piada` é interativo e aguarda sua resposta. No Docker, o áudio fica desativado por padrão porque o container normalmente não tem acesso a uma placa de som.

Execute o Gemini:

```bash
docker run --rm -it callai gemini
```

O modo `gemini` também é interativo: digite o prompt quando o programa perguntar.

`--rm` remove o container ao terminar. A opção `-it` permite interagir com o programa pelo terminal.

Em um host Linux com ALSA, é possível habilitar o áudio assim:

```bash
docker run --rm -it --device /dev/snd -e CALLAI_AUDIO=1 callai piada
```


