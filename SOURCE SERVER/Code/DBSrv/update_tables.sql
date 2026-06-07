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
