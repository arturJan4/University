<?php

declare(strict_types=1);

namespace DoctrineMigrations;

use Doctrine\DBAL\Schema\Schema;
use Doctrine\Migrations\AbstractMigration;

/**
 * Auto-generated Migration: Please modify to your needs!
 */
final class Version20201205213117 extends AbstractMigration
{
    public function getDescription() : string
    {
        return '';
    }

    public function up(Schema $schema) : void
    {
        // this up() migration is auto-generated, please modify it to your needs
        $this->addSql('ALTER TABLE visits DROP FOREIGN KEY FK_444839EACEC3FD2F');
        $this->addSql('ALTER TABLE visits ADD CONSTRAINT FK_444839EACEC3FD2F FOREIGN KEY (patients_id) REFERENCES patients (id) ON DELETE CASCADE');
    }

    public function down(Schema $schema) : void
    {
        // this down() migration is auto-generated, please modify it to your needs
        $this->addSql('ALTER TABLE visits DROP FOREIGN KEY FK_444839EACEC3FD2F');
        $this->addSql('ALTER TABLE visits ADD CONSTRAINT FK_444839EACEC3FD2F FOREIGN KEY (patients_id) REFERENCES patients (id)');
    }
}
