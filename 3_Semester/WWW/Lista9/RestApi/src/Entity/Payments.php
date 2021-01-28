<?php

namespace App\Entity;

use App\Repository\PaymentsRepository;
use Doctrine\Common\Collections\ArrayCollection;
use Doctrine\Common\Collections\Collection;
use Doctrine\ORM\Mapping as ORM;
use JMS\Serializer\Annotation\SerializedName;
use JMS\Serializer\Annotation as JMS;
use JMS\Serializer\Annotation\Expose;

/**
 * @ORM\Entity(repositoryClass=PaymentsRepository::class)
 * @JMS\ExclusionPolicy("all")
 */
class Payments
{
    /**
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="AUTO")
     * @ORM\Column(type="integer")
     * @JMS\Groups({"defaults"})
     * @Expose()
     */
    private $id;

    /**
     * @ORM\Column(type="string", length=255)
     * @SerializedName("created-at")
     * @JMS\Groups({"defaults"})
     * @Expose()
     */
    private $createdAt;

    /**
     * @ORM\Column(type="string", length=255)
     * @JMS\Groups({"defaults"})
     * @Expose()
     */
    private $ammount;

    /**
     * @ORM\Column(type="string", length=64)
     * @JMS\Groups({"defaults"})
     * @Expose()
     */
    private $status;

    /**
     * @ORM\ManyToOne(targetEntity=Visits::class, inversedBy="payments")
     * @ORM\JoinColumn(name="visits_id", referencedColumnName="id", nullable=false)
     */
    private $visits;

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getCreatedAt(): ?string
    {
        return $this->createdAt;
    }

    public function setCreatedAt(string $createdAt): self
    {
        $this->createdAt = $createdAt;

        return $this;
    }

    public function getAmmount(): ?string
    {
        return $this->ammount;
    }

    public function setAmmount(string $ammount): self
    {
        $this->ammount = $ammount;

        return $this;
    }

    public function getStatus(): ?string
    {
        return $this->status;
    }

    public function setStatus(string $status): self
    {
        $this->status = $status;

        return $this;
    }

    public function getVisits(): ?Visits
    {
        return $this->visits;
    }

    public function setVisits(?Visits $visits): self
    {
        $this->visits = $visits;

        return $this;
    }
}
