<?php

namespace App\Entity;

use Symfony\Component\Validator\Constraints as Assert;

class Person
{
    /**
     * @Assert\NotBlank(message="Pole nie może być puste")
     */
    private $firstname;

    /**
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Length(
     *     min=3,
     *     minMessage="Za krótkie",
     *     max=40,
     *     maxMessage="Za długie"
     * )
     */
    private $lastname;

    /**
     * Set firstname
     *
     * @param string $firstname
     */
    public function setFirstname($firstname)
    {
        $this->firstname = $firstname;
    }

    /**
     * Get firstname
     *
     * @return string 
     */
    public function getFirstname()
    {
        return $this->firstname;
    }

    /**
     * Set lastname
     *
     * @param string $lastname
     */
    public function setLastname($lastname)
    {
        $this->lastname = $lastname;
    }

    /**
     * Get lastname
     *
     * @return string 
     */
    public function getLastname()
    {
        return $this->lastname;
    }
}