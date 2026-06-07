# Guia Passo a Passo: Instalação e Configuração das Melhorias no WYD2

Este guia detalha os procedimentos necessários para aplicar e configurar todas as otimizações e novas funcionalidades desenvolvidas para o seu servidor WYD2.

## 1. Aceitar o Pull Request no GitHub

O primeiro passo é integrar todas as modificações ao seu repositório principal. Isso garante que você tenha a versão mais recente do código-fonte.

1.  Acesse o link do Pull Request no GitHub:
    [Pull Request #3: Atualização Consolidada](https://github.com/richaferreira/wyd2/pull/3)
2.  Revise as alterações propostas. Se estiver de acordo, clique no botão verde **"Merge pull request"**.
3.  Confirme a mesclagem clicando em **"Confirm merge"**.

Após este passo, seu repositório local (`/home/ubuntu/wyd2`) precisará ser atualizado. Para isso, execute os seguintes comandos no terminal:

```bash
cd /home/ubuntu/wyd2
git checkout main
git pull origin main
```

## 2. Atualizar o Banco de Dados MySQL

Novos sistemas (Leilão, VIP, Daily Reward, Títulos) exigem novas tabelas e colunas no seu banco de dados. Você deve executar o script SQL fornecido para aplicar essas alterações.

1.  Localize o arquivo `update_tables.sql` no diretório `SOURCE SERVER/Code/DBSrv/` do seu repositório clonado.
2.  Abra o arquivo `update_tables.sql` com um editor de texto.
3.  Copie todo o conteúdo do arquivo.
4.  Abra seu gerenciador de banco de dados MySQL (ex: HeidiSQL, MySQL Workbench, phpMyAdmin).
5.  Conecte-se ao banco de dados do seu servidor WYD2.
6.  Execute o script SQL copiado. **Certifique-se de que não há erros durante a execução.**

## 3. Configurar o Arquivo `config.json`

As credenciais do banco de dados e outras configurações importantes foram movidas para um arquivo externo para maior segurança e facilidade de gerenciamento.

1.  Navegue até a pasta `SOURCE SERVER/Code/DBSrv/` e `SOURCE SERVER/Code/TMSrv/`.
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

## 5. Substituir os Arquivos Executáveis

Após a recompilação, os novos arquivos executáveis (`.exe`) e bibliotecas (`.dll`) serão gerados.

1.  Localize os novos executáveis nas pastas de saída do Visual Studio (geralmente `Release` ou `Debug` dentro de cada pasta de projeto, como `SOURCE SERVER/Code/TMSrv/Release/TMSrv.exe`).
2.  Substitua os arquivos antigos no seu servidor de jogo pelos novos executáveis e quaisquer `.dll` que tenham sido atualizadas.

## 6. Iniciar o Servidor

Com todas as etapas anteriores concluídas, você pode iniciar seu servidor.

1.  Execute o `DBSrv.exe`.
2.  Execute o `TMSrv.exe`.
3.  Inicie o cliente do jogo.

Verifique os logs do servidor para confirmar que não há erros e que os novos sistemas estão sendo inicializados corretamente. Teste as novas funcionalidades (comandos, leilão, áreas VIP, etc.) dentro do jogo para garantir que tudo está funcionando como esperado.
