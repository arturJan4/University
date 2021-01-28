<?php

namespace App\Entity;

use App\Repository\VisitsRepository;
use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;
use Doctrine\ORM\Mapping as ORM;
use Doctrine\ORM\Mapping\JoinColumn;
use JMS\Serializer\Annotation as JMS;
use JMS\Serializer\Annotation\Expose;
/**
 * @ORM\Entity(repositoryClass=VisitsRepository::class)
 * @JMS\ExclusionPolicy("all")
 */
class Visits
{
    /**
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="AUTO")
     * @ORM\Column(type="integer")
     * @JMS\Groups({"defaults"})
     * @Expose
     */
    private $id;

    /**
     * @ORM\Column(type="string", length=255)
     * @JMS\Groups({"defaults"})
     * @Expose
     */
    private $date;

    /**
     * @ORM\Column(type="string", length=255)
     * @JMS\Groups({"defaults"})
     * @Expose
     */
    private $doctor;
  
    /**
     * @ORM\ManyToOne(targetEntity=Patients::class, inversedBy="visits")
     * @JoinColumn(name="patients_id", referencedColumnName="id", onDelete="CASCADE")
     */
    private $patients;

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getDate(): ?string
    {
        return $this->date;
    }

    public function setDate(string $date): self
    {
        $this->date = $date;

        return $this;
    }

    public function getDoctor(): ?string
    {
        return $this->doctor;
    }

    public function setDoctor(string $doctor): self
    {
        $this->doctor = $doctor;

        return $this;
    }

    public function getPatients(): ?Patients
    {
        return $this->patients;
    }

    public function setPatients(?Patients $patients): self
    {
        $this->patients = $patients;

        return $this;
    }
}
