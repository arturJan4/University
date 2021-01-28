<?php

namespace App\Entity;

use Symfony\Component\Validator\Constraints as Assert;

class Position {
    public int $place;
    public int $points;
    public string $name;
    public string $surname;
    public string $city;
    public string $teamName;

    public function __construct(int $place, int $points, string $name, 
                                string $surname, string $city, string $teamName) {
        $this->place = $place;
        $this->points = $points;
        $this->name = $name;
        $this->surname = $surname;
        $this->city = $city;
        $this->teamName = $teamName;
    }
}