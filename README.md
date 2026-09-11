# CallAI

Projeto foda em C++ que consulta APIs de clima, piadas e Gemini.

[![Build](https://img.shields.io/badge/Build-passing-brightgreen?logo=githubactions)](https://github.com/opedro/aicall/actions)
[![Release](https://img.shields.io/badge/Release-v1.2.0-blue?logo=github)](https://github.com/opedro/aicall/releases/tag/v1.2.0)
[![Latest Release](https://img.shields.io/github/v/release/opedro/aicall?label=latest%20release&logo=github)](https://github.com/opedro/aicall/releases/latest)


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

## Contribuidores

- Alex Aguiar
- Alex Silva
- Pedro Ruiz
