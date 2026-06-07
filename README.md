# WYD2 Server & Client - Modernização e Novas Funcionalidades

Este repositório contém o código-fonte de um servidor e cliente WYD2, que passou por um processo extensivo de modernização, otimização de segurança e implementação de novas funcionalidades. O objetivo é fornecer uma base estável, segura e rica em recursos para a criação de um servidor de jogo de alta qualidade.

## Visão Geral das Melhorias

O projeto foi aprimorado em diversas frentes, abrangendo desde a infraestrutura de código até a experiência de jogo do usuário.

### 1. Otimizações de Infraestrutura e Segurança

-   **Logs Assíncronos:** Implementação de um sistema de log não-bloqueante que opera em uma thread separada, eliminando gargalos de I/O e melhorando a performance geral do servidor.
-   **Prepared Statements:** Proteção robusta contra ataques de SQL Injection em todas as interações críticas com o banco de dados (Login, Donate, Leilão, etc.), garantindo a integridade e segurança dos dados.
-   **Configuração Externa:** Migração de credenciais de banco de dados e outras configurações sensíveis para arquivos `config.json` externos, facilitando a gestão do ambiente e aumentando a segurança.
-   **Modernização C++:** Refatoração de classes e estruturas de dados críticas para utilizar padrões C++ modernos (C++17/20), como `std::string` e `Smart Pointers` (`std::unique_ptr`, `std::shared_ptr`), reduzindo significativamente os riscos de vazamentos de memória e buffer overflows.

### 2. Novos Sistemas de Jogo (Gameplay)

-   **Sistema de Leilão (Auction House):** Um mercado completo onde jogadores podem listar itens para venda (por lance ou compra direta), com persistência em banco de dados e uma interface de usuário dedicada no cliente.
-   **Guerra de Castelo (Castle War):** Um motor de guerra automatizado que gerencia o estado do castelo, cronogramas de batalha (ex: domingos às 21h) e a persistência do dono do castelo no banco de dados.
-   **Sistema de Bosses:** Implementação de um sistema de spawn agendado para chefes mundiais, com anúncios globais e recompensas dinâmicas para os jogadores.
-   **Sistema VIP e Áreas VIP:** Status VIP com benefícios exclusivos (bônus de EXP/Drop) e acesso a mapas especiais via comando `/areavip`, proporcionando uma experiência premium.
-   **Arenas PvP (Arena Real):** Um sistema de combate PvP por equipes com horários automáticos, registro de jogadores e premiações em itens e honra.
-   **Sistema de Títulos:** Títulos customizáveis que os jogadores podem equipar, concedendo bônus de atributos reais ao personagem.
-   **Novas Composições (Crafting System):** Base para um sistema de alquimia/composição de itens, permitindo a criação de novos equipamentos a partir de receitas específicas.

### 3. Funcionalidades e Comandos (Qualidade de Vida - QoL)

-   **Auto-Loot Seletivo:** Comando `/autoloot` que permite aos jogadores configurar a coleta automática de ouro ou de todos os itens.
-   **Daily Reward:** Sistema de recompensa diária para incentivar o login recorrente dos jogadores.
-   **Comandos Administrativos:** Novos comandos para GMs, como `/notice` global e ferramentas de gestão de inventário (`/limparinv`).
-   **Kill Counter:** Monitoramento e exibição de abates PvP em tempo real para os jogadores.
-   **Comando `/ping`:** Exibe o IP do jogador e o status de conexão.

### 4. Interface e Experiência do Usuário (UI/UX)

-   **Novas Janelas de Interface:** Desenvolvimento de janelas visuais no cliente para o Sistema de Leilão e o sistema de Composições, melhorando a interação do usuário.
-   **Feedback Visual:** Integração de anúncios globais e sinais de sistema para uma comunicação mais eficaz com os jogadores.

## Como Instalar e Configurar

Para aplicar todas as melhorias e novas funcionalidades, siga o guia detalhado:

-   **[Guia de Instalação e Configuração Completo](INSTALLATION_GUIDE.md)**

Este guia aborda desde a aceitação do Pull Request no GitHub até a recompilação do projeto e a configuração do banco de dados.

## Estrutura do Repositório

-   `SOURCE SERVER/Code/DBSrv/`: Código-fonte do servidor de banco de dados.
-   `SOURCE SERVER/Code/TMSrv/`: Código-fonte do servidor de gerenciamento de jogo.
-   `SOURCE GAME/Projects/TMProject/`: Código-fonte do cliente do jogo.
-   `INSTALLATION_GUIDE.md`: Guia passo a passo para instalação e configuração.
-   `README.md`: Este arquivo.

## Contribuição

Sinta-se à vontade para explorar o código, sugerir melhorias ou reportar problemas. Este projeto é um esforço contínuo para modernizar e aprimorar a experiência do WYD2.

---

**Desenvolvido por Manus AI**
