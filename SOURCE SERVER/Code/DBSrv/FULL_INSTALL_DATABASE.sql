-- ########################################################################
-- # WYD2 FULL DATABASE INSTALLATION SCRIPT
-- # Este script cria o banco de dados completo, do zero, incluindo
-- # todas as tabelas originais e as novas funcionalidades implementadas.
-- ########################################################################

-- 1. Criação do Banco de Dados
CREATE DATABASE IF NOT EXISTS `banco_wyd1` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `banco_wyd1`;

-- 2. Tabela de Contas (Accounts)
-- Inclui estrutura original + campos VIP e Daily Reward
CREATE TABLE IF NOT EXISTS `accounts` (
    `Login` VARCHAR(32) NOT NULL PRIMARY KEY,
    `Pass` VARCHAR(32) NOT NULL,
    `NumericToken` VARCHAR(10) DEFAULT '-1',
    `RealName` VARCHAR(64),
    `Email` VARCHAR(128),
    `Telephone` VARCHAR(32),
    `Address` VARCHAR(255),
    `SSN1` INT DEFAULT 0,
    `SSN2` INT DEFAULT 0,
    `Donate` INT DEFAULT 0,
    `Honra` INT DEFAULT 0,
    `Admin` INT DEFAULT 0,
    `Banned` INT DEFAULT 0,
    `MuteChat` INT DEFAULT 0,
    -- Campos Adicionados pela Modernização
    `vip_type` INT DEFAULT 0,
    `vip_time` BIGINT DEFAULT 0,
    `daily_reward_last` BIGINT DEFAULT 0
) ENGINE=InnoDB;

-- 3. Tabela de Personagens (Mobs/Characters)
-- Inclui estrutura original + Títulos, Auto-Loot e Kill Counter
CREATE TABLE IF NOT EXISTS `mobs` (
    `Name` VARCHAR(32) NOT NULL PRIMARY KEY,
    `Account` VARCHAR(32) NOT NULL,
    `Slot` INT NOT NULL,
    `Level` INT DEFAULT 1,
    `Exp` BIGINT DEFAULT 0,
    `Guild` INT DEFAULT 0,
    `GuildLevel` INT DEFAULT 0,
    `Class` INT DEFAULT 0,
    `Coin` BIGINT DEFAULT 0,
    `X` INT DEFAULT 2100,
    `Y` INT DEFAULT 2100,
    `HP` INT DEFAULT 100,
    `MP` INT DEFAULT 100,
    `Str` INT DEFAULT 10,
    `Int` INT DEFAULT 10,
    `Dex` INT DEFAULT 10,
    `Con` INT DEFAULT 10,
    -- Campos Adicionados pela Modernização
    `title_index` INT DEFAULT 0,
    `autoloot_mode` INT DEFAULT 0,
    `pvp_abates` INT DEFAULT 0,
    INDEX (`Account`)
) ENGINE=InnoDB;

-- 4. Tabela de Guildas (Guilds)
CREATE TABLE IF NOT EXISTS `guilds` (
    `ID` INT NOT NULL PRIMARY KEY,
    `Name` VARCHAR(32) NOT NULL,
    `Leader` VARCHAR(32),
    `Level` INT DEFAULT 1,
    `Experience` BIGINT DEFAULT 0,
    `Gold` BIGINT DEFAULT 0,
    -- Campos Adicionados pela Modernização
    `castle_owner` INT DEFAULT 0
) ENGINE=InnoDB;

-- 5. Tabela do Sistema de Leilão (Auction House)
CREATE TABLE IF NOT EXISTS `auction_house` (
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `seller_acc` VARCHAR(32) NOT NULL,
    `item_data` BLOB NOT NULL, -- Dados binários do STRUCT_ITEM
    `price` BIGINT NOT NULL,
    `end_time` BIGINT NOT NULL,
    `status` INT DEFAULT 0 -- 0: Ativo, 1: Vendido, 2: Expirado
) ENGINE=InnoDB;

-- 6. Tabelas do Novo Compositor (Alquimia/Composições)
CREATE TABLE IF NOT EXISTS `ncompositorinfo` (
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `npc_id` INT NOT NULL,
    `comp_id` INT NOT NULL,
    `rate` INT NOT NULL,
    `gold_req` INT NOT NULL,
    `res_index` INT NOT NULL,
    `res_eff1` INT, `res_val1` INT,
    `res_eff2` INT, `res_val2` INT,
    `res_eff3` INT, `res_val3` INT
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS `newcompositor` (
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `npc_id` INT NOT NULL,
    `comp_id` INT NOT NULL,
    `item_pos` INT NOT NULL,
    `req_index` INT NOT NULL,
    `req_eff1` INT, `req_val1` INT,
    `req_eff2` INT, `req_val2` INT,
    `req_eff3` INT, `req_val3` INT
) ENGINE=InnoDB;

-- 7. Tabela de Logs (Sistema Original)
CREATE TABLE IF NOT EXISTS `log` (
    `ID` INT AUTO_INCREMENT PRIMARY KEY,
    `Conta` VARCHAR(32),
    `Char` VARCHAR(32),
    `Mensagem` TEXT,
    `Data` VARCHAR(64),
    `Tipo` VARCHAR(32)
) ENGINE=InnoDB;

-- ########################################################################
-- # FIM DO SCRIPT FULL_INSTALL_DATABASE.sql
-- ########################################################################
