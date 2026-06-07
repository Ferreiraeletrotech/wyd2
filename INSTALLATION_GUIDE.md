# Guia Passo a Passo: Instalação e Configuração das Melhorias no WYD2

Este guia detalha os procedimentos necessários para aplicar e configurar todas as otimizações e novas funcionalidades desenvolvidas para o seu servidor WYD2.

## 1. Sincronizar o Repositório Local

Como todos os Pull Requests anteriores foram mesclados, seu repositório principal (`main`) já deve conter todas as modificações. Para garantir que sua cópia local esteja atualizada, execute os seguintes comandos no terminal:

```bash
cd /home/ubuntu/wyd2
git checkout main
git pull origin main
```

## 2. Atualizar o Banco de Dados MySQL

Novos sistemas (Leilão, VIP, Daily Reward, Títulos, Bosses, Loot Box, Ranking, Loja de Cash) exigem novas tabelas e colunas no seu banco de dados. Você tem duas opções para aplicar essas alterações:

### Opção A: Instalação Completa (para novos servidores ou reinstalação)

Se você está configurando um servidor do zero ou deseja recriar seu banco de dados, utilize o script `FULL_INSTALL_DATABASE.sql`.

1.  Localize o arquivo `FULL_INSTALL_DATABASE.sql` no diretório `SOURCE SERVER/Code/DBSrv/`.
2.  Abra o arquivo com um editor de texto e copie todo o conteúdo.
3.  Abra seu gerenciador de banco de dados MySQL (ex: HeidiSQL, MySQL Workbench, phpMyAdmin).
4.  Conecte-se ao seu servidor MySQL e **crie um novo banco de dados** para o WYD2 (se ainda não tiver um).
5.  Execute o script SQL copiado. **Este script criará todas as tabelas e colunas necessárias.**

### Opção B: Atualização de Banco de Dados Existente (para servidores em funcionamento)

Se você já possui um servidor WYD2 em funcionamento e deseja apenas adicionar as novas funcionalidades sem perder dados, utilize o script `MASTER_SETUP.sql`.

1.  Localize o arquivo `MASTER_SETUP.sql` no diretório `SOURCE SERVER/Code/DBSrv/`.
2.  Abra o arquivo com um editor de texto e copie todo o conteúdo.
3.  Abra seu gerenciador de banco de dados MySQL e conecte-se ao banco de dados do seu servidor WYD2.
4.  Execute o script SQL copiado. **Este script adicionará apenas as novas tabelas e colunas, preservando seus dados existentes.**

**Importante:** Certifique-se de que não há erros durante a execução de qualquer um dos scripts SQL.

## 3. Configurar o Arquivo `config.json`

As credenciais do banco de dados e outras configurações importantes foram movidas para um arquivo externo para maior segurança e facilidade de gerenciamento.

1.  Navegue até as pastas `SOURCE SERVER/Code/DBSrv/` e `SOURCE SERVER/Code/TMSrv/`.
2.  Localize o arquivo `config.json` em ambas as pastas.
3.  Abra cada `config.json` com um editor de texto (ex: Bloco de Notas, Notepad++).
4.  Edite os campos `host`, `user`, `password` e `database` com as informações corretas do seu servidor MySQL.
    Exemplo de `config.json`:
    ```json
    {
      "database": {
        "host": "localhost",
        "user": "seu_usuario_mysql",
        "password": "sua_senha_mysql",
        "database": "seu_banco_de_dados"
      }
    }
    ```
5.  Salve as alterações em ambos os arquivos `config.json`.

## 4. Recompilar o Projeto no Visual Studio

Para que as alterações no código-fonte sejam aplicadas, você precisa recompilar os executáveis do servidor e do cliente.

1.  Abra o **Visual Studio** (versão 2019 ou superior é recomendada).
2.  Abra a solução do projeto WYD2 (geralmente um arquivo `.sln` na raiz do repositório ou em `SOURCE SERVER/Code/`).
3.  No **Solution Explorer**, clique com o botão direito na solução (o item superior) e selecione **"Rebuild Solution"** (Recompilar Solução).
    - Alternativamente, você pode recompilar os projetos `TMSrv` e `DBSrv` (localizados em `SOURCE SERVER/Code/`) e `TMProject` (localizado em `SOURCE GAME/Projects/TMProject/`) individualmente.
4.  Verifique a janela **Output** do Visual Studio para garantir que a compilação foi concluída com sucesso, sem erros.

## 5. Copiar os Recursos Visuais (Imagens da UI)

Para que as novas janelas e ícones apareçam corretamente no cliente, você precisará copiar os arquivos de imagem gerados.

1.  Localize os arquivos `.bmp` que foram gerados na pasta `SOURCE GAME/UI/` do seu repositório local:
    - `icon_boss.bmp`
    - `icon_rank.bmp`
    - `icon_shop.bmp`
    - `icon_auction.bmp`
    - `bg_boss.bmp`
    - `bg_rank.bmp`
    - `bg_shop.bmp`
    - `bg_auction.bmp`
2.  Copie esses arquivos para a pasta `UI` do seu cliente de jogo final (onde o `WYD.exe` está localizado).

## 6. Substituir os Arquivos Executáveis

Após a recompilação, os novos arquivos executáveis (`.exe`) e bibliotecas (`.dll`) serão gerados.

1.  Localize os novos executáveis nas pastas de saída do Visual Studio (geralmente `Release` ou `Debug` dentro de cada pasta de projeto, como `SOURCE SERVER/Code/TMSrv/Release/TMSrv.exe`).
2.  Substitua os arquivos antigos no seu servidor de jogo pelos novos executáveis e quaisquer `.dll` que tenham sido atualizadas.

## 7. Iniciar o Servidor

Com todas as etapas anteriores concluídas, você pode iniciar seu servidor.

1.  Execute o `DBSrv.exe`.
2.  Execute o `TMSrv.exe`.
3.  Inicie o cliente do jogo.

Verifique os logs do servidor para confirmar que não há erros e que os novos sistemas estão sendo inicializados corretamente. Teste as novas funcionalidades (comandos, leilão, áreas VIP, painéis de Boss/Ranking/Loja, etc.) dentro do jogo para garantir que tudo está funcionando como esperado.
