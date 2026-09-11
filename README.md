# CallAI

Projeto foda em C++ que consulta APIs de clima, piadas e Gemini.

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
