<?php

declare(strict_types=1);

namespace DoctrineMigrations;

use Doctrine\DBAL\Schema\Schema;
use Doctrine\Migrations\AbstractMigration;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
final class Version20201205173019 extends AbstractMigration
{
    public function getDescription() : string
    {
        return '';
    }

    public function up(Schema $schema) : void
    {
        // this up() migration is auto-generated, please modify it to your needs
        $this->addSql('ALTER TABLE payments ADD visits_id INT NOT NULL');
        $this->addSql('ALTER TABLE payments ADD CONSTRAINT FK_65D29B32B4B7D41A FOREIGN KEY (visits_id) REFERENCES visits (id)');
        $this->addSql('CREATE INDEX IDX_65D29B32B4B7D41A ON payments (visits_id)');
        $this->addSql('ALTER TABLE visits DROP FOREIGN KEY FK_444839EA4C3A3BB');
        $this->addSql('DROP INDEX UNIQ_444839EA4C3A3BB ON visits');
        $this->addSql('ALTER TABLE visits DROP payment_id');
    }

    public function down(Schema $schema) : void
    {
        // this down() migration is auto-generated, please modify it to your needs
        $this->addSql('ALTER TABLE payments DROP FOREIGN KEY FK_65D29B32B4B7D41A');
        $this->addSql('DROP INDEX IDX_65D29B32B4B7D41A ON payments');
        $this->addSql('ALTER TABLE payments DROP visits_id');
        $this->addSql('ALTER TABLE visits ADD payment_id INT DEFAULT NULL');
        $this->addSql('ALTER TABLE visits ADD CONSTRAINT FK_444839EA4C3A3BB FOREIGN KEY (payment_id) REFERENCES payments (id)');
        $this->addSql('CREATE UNIQUE INDEX UNIQ_444839EA4C3A3BB ON visits (payment_id)');
    }
}
