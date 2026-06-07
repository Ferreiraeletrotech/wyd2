-- Atualização para o Sistema VIP, Daily Reward e Títulos
-- Atualização para o Sistema VIP, Daily Reward e Títulos

-- Tabela de Contas (Accounts)
ALTER TABLE `accounts` 
ADD COLUMN `vip_type` INT DEFAULT 0,
ADD COLUMN `vip_time` DATETIME DEFAULT NULL,
ADD COLUMN `daily_reward_last` DATE DEFAULT NULL;

-- Tabela de Logs
CREATE TABLE IF NOT EXISTS `log_commands` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `account` VARCHAR(16),
  `character` VARCHAR(16),
  `command` VARCHAR(255),
  `date` DATETIME DEFAULT CURRENT_TIMESTAMP
);
121	

-- Sistema de Leilão (Auction House)
CREATE TABLE IF NOT EXISTS `auction_items` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `seller_name` VARCHAR(16) NOT NULL,
  `item_index` INT NOT NULL,
  `item_effect1` INT DEFAULT 0,
  `item_value1` INT DEFAULT 0,
  `item_effect2` INT DEFAULT 0,
  `item_value2` INT DEFAULT 0,
  `item_effect3` INT DEFAULT 0,
  `item_value3` INT DEFAULT 0,
  `price` BIGINT NOT NULL,
  `currency_type` INT DEFAULT 0, -- 0: Gold, 1: Donate
  `status` INT DEFAULT 0, -- 0: Active, 1: Sold, 2: Expired/Cancelled
  `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP,
  `expires_at` DATETIME
);
