# Instruções para execução do Job de empacotamento para Windows

1. Compile o jogo dentro da pasta build do repositório.

2. Após compilar o jogo no Windows e gerar o executável (.exe), faça o *push* do compilado.

3. Dentro da pasta "build" há um subdiretório chamado "libs", onde deverão ser colocadas as DLLs extras utilizadas na compilação do jogo. Note que as DLL padrões do SDL já estão lá dentro.


# Instruções para alteração das informações do instalador do jogo

1. Basta acessar o arquivo de configuração **config_windows_pack.nsh** e alterar os nomes das variáveis para os desejados. Atente-se às regras de nomenclatura em strings, pois as variáveis só aceitam valores que possuam caracteres númericos, alfanuméricos e "_".