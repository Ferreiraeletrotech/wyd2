-- ########################################################################
-- # WYD2 MASTER DATABASE SETUP - CONSOLIDATED UPDATES
-- # Este script consolida todas as alterações necessárias para o banco de dados.
-- # Execute este arquivo uma única vez no seu gerenciador de banco de dados.
-- ########################################################################

-- 1. Atualização da Tabela de Contas (Accounts)
-- Adiciona campos para o Sistema VIP e Daily Reward
ALTER TABLE `accounts` 
ADD COLUMN IF NOT EXISTS `vip_type` INT DEFAULT 0,
ADD COLUMN IF NOT EXISTS `vip_time` BIGINT DEFAULT 0,
ADD COLUMN IF NOT EXISTS `daily_reward_last` BIGINT DEFAULT 0;

-- 2. Atualização da Tabela de Personagens (Characters/Mobs)
-- Adiciona campos para Títulos, Auto-Loot e Kill Counter
ALTER TABLE `mobs` 
ADD COLUMN IF NOT EXISTS `title_index` INT DEFAULT 0,
ADD COLUMN IF NOT EXISTS `autoloot_mode` INT DEFAULT 0,
ADD COLUMN IF NOT EXISTS `pvp_abates` INT DEFAULT 0;

-- 3. Criação da Tabela do Sistema de Leilão (Auction House)
CREATE TABLE IF NOT EXISTS `auction_house` (
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `seller_acc` VARCHAR(32) NOT NULL,
    `item_data` BLOB NOT NULL, -- Dados binários do STRUCT_ITEM
    `price` BIGINT NOT NULL,
    `end_time` BIGINT NOT NULL,
    `status` INT DEFAULT 0 -- 0: Ativo, 1: Vendido, 2: Expirado
);

-- 4. Criação das Tabelas do Novo Compositor (Alquimia)
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
);

CREATE TABLE IF NOT EXISTS `newcompositor` (
    `id` INT AUTO_INCREMENT PRIMARY KEY,
    `npc_id` INT NOT NULL,
    `comp_id` INT NOT NULL,
    `item_pos` INT NOT NULL,
    `req_index` INT NOT NULL,
    `req_eff1` INT, `req_val1` INT,
    `req_eff2` INT, `req_val2` INT,
    `req_eff3` INT, `req_val3` INT
);

-- 5. Atualização da Tabela de Guilds (Guerra de Castelo)
ALTER TABLE `guilds` 
ADD COLUMN IF NOT EXISTS `castle_owner` INT DEFAULT 0;

-- ########################################################################
-- # FIM DO SCRIPT MASTER_SETUP.sql
-- ########################################################################
