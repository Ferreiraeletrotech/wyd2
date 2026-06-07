# Guia de Comandos do Servidor WYD2

Este documento lista todos os comandos disponíveis no servidor, divididos entre comandos para jogadores comuns e comandos exclusivos para Administradores/Game Masters (GMs).

## Comandos de Jogador (Player Commands)

Estes comandos estão disponíveis para todos os jogadores dentro do jogo. Para utilizá-los, basta digitar no chat normal (tecla Enter).

| Comando | Parâmetro | Descrição | Exemplo de Uso |
| :--- | :--- | :--- | :--- |
| `/limparinv` | Nenhum | Apaga **todos** os itens do inventário do personagem. Use com cuidado! | `/limparinv` |
| `/ping` | Nenhum | Exibe o seu endereço IP atual e o status da conexão com o servidor. | `/ping` |
| `/autoloot` | `[0, 1, 2]` | Configura a coleta automática de itens. `0` = Desligado, `1` = Apenas Ouro, `2` = Todos os itens. | `/autoloot 2` |
| `/titulo` | `[0 a 10]` | Equipa um título visual no personagem que concede bônus de atributos. | `/titulo 5` |
| `/abates` | Nenhum | Exibe a quantidade de abates PvP (jogadores mortos) na sessão atual. | `/abates` |
| `/areavip` | Nenhum | Teleporta o jogador para a Área VIP exclusiva. Requer status VIP ativo na conta. | `/areavip` |
| `/arena` | Nenhum | Registra o jogador para participar da próxima Arena Real. | `/arena` |
| `/leilao` | Nenhum | Abre a interface visual do Sistema de Leilão (Auction House). | `/leilao` |
| `/guildon` | Nenhum | Ativa a exibição do emblema e nome da Guilda. | `/guildon` |
| `/guildoff` | Nenhum | Oculta a exibição do emblema e nome da Guilda. | `/guildoff` |

## Comandos Administrativos (GM / Admin Commands)

Estes comandos são restritos a contas que possuem o nível de privilégio de Administrador (`Admin > 0` no banco de dados).

| Comando | Parâmetro | Descrição | Exemplo de Uso |
| :--- | :--- | :--- | :--- |
| `/notice` | `[Mensagem]` | Envia uma mensagem global em destaque (cor amarela/vermelha) para todos os jogadores online no servidor. | `/notice Evento de EXP em dobro iniciado!` |

### Como conceder privilégios de Administrador (GM)

Para que uma conta possa usar o comando `/notice` e futuros comandos administrativos, você deve alterar o nível de acesso dela diretamente no banco de dados MySQL.

1. Abra o seu gerenciador de banco de dados (ex: HeidiSQL).
2. Acesse a tabela `accounts`.
3. Encontre a linha correspondente ao nome da conta desejada.
4. Altere o valor da coluna `Admin` (ou similar, dependendo da estrutura exata da sua base legada) de `0` para `1` (ou um valor superior, dependendo da hierarquia do seu servidor).
5. O jogador precisará deslogar e logar novamente para que os privilégios sejam aplicados.

---
**Nota:** A lista de comandos administrativos atuais é enxuta, focada na comunicação global. O sistema de comandos (`_MSG_MessageChat.cpp`) foi estruturado de forma modular, facilitando a adição de novos comandos (como `/ban`, `/kick`, `/item`) no futuro, bastando adicionar novas verificações `else if (strcmp(szCmd, "comando") == 0 && pUser[conn].Admin > 0)`.
