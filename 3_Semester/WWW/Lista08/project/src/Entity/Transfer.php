<?php

namespace App\Entity;

use App\Repository\TransferRepository;
use DateTime;
use Symfony\Component\Validator\Constraints as Assert;
use Doctrine\ORM\Mapping as ORM;
use Symfony\Component\Validator\Constraints\Date;

/**
 * @ORM\Entity(repositoryClass=TransferRepository::class)
 */
class Transfer
{
    /**
     * @ORM\Id
     * @ORM\GeneratedValue
     * @ORM\Column(type="integer")
     */
    private $id;

    /**
     * @ORM\Column(type="string", length=40)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Regex(
     *  pattern="/^\d{2} 1234 9876 \d{4} \d{4} \d{4} \d{4}$/",
     *  message="Zły format numeru konta",
     *  )     
     */
    private string $KontoOd;

    /**
     * @ORM\Column(type="string", length=40)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Regex(
     *  pattern="/^\d{2} \d{4} \d{4} \d{4} \d{4} \d{4} \d{4}$/",
     *  message="Zły format numeru konta",
     *  )     
     */
    private string $KontoDo;

    /**
     * @ORM\Column(type="string", length=64)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Length(
     *     max=64,
     *     maxMessage="Za długie"
     * )
     */
    private string $ImieNazwisko;

    /**
     * @ORM\Column(type="string", length=64)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Length(
     *     max=64,
     *     maxMessage="Za długie"
     * )
     */
    private string $Ulica;

    /**
     * @ORM\Column(type="string", length=64)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Length(
     *     max=64,
     *     maxMessage="Za długie"
     * )
     */
    private string $Miejscowosc;

    /**
     * @ORM\Column(type="string", length=7)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Regex(
     *  pattern="/^\d\d-\d\d\d$/",
     *  message="Zły kod pocztowy"
     * )
     */
    private string $KodPocztowy;

    /**
     * @ORM\Column(type="string", length=40)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Regex(
     *  pattern="/^(0*)[0-9]+(,[0-9]{1,2})?$/",
     *  message="Niepoprawna kwota"
     * )
     */
    private string $Kwota;

    /**
     * @ORM\Column(type="string", length=128)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Length(
     *     max=128,
     *     maxMessage="Za długie"
     * )
     */
    private string $Tytulem;

    /**
     * @ORM\Column(type="date", length=32)
     * @Assert\NotBlank(message="Pole nie może być puste")
     * @Assert\Date
     */
    public string $DataWykonania;

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getKontoOd(): ?string
    {
        return $this->KontoOd;
    }

    public function setKontoOd(string $KontoOd): self
    {
        $this->KontoOd = $KontoOd;

        return $this;
    }

    public function getKontoDo(): ?string
    {
        return $this->KontoDo;
    }

    public function setKontoDo(string $KontoDo): self
    {
        $this->KontoDo = $KontoDo;

        return $this;
    }

    public function getImieNazwisko(): ?string
    {
        return $this->ImieNazwisko;
    }

    public function setImieNazwisko(string $ImieNazwisko): self
    {
        $this->ImieNazwisko = $ImieNazwisko;

        return $this;
    }

    public function getUlica(): ?string
    {
        return $this->Ulica;
    }

    public function setUlica(string $Ulica): self
    {
        $this->Ulica = $Ulica;

        return $this;
    }

    public function getMiejscowosc(): ?string
    {
        return $this->Miejscowosc;
    }

    public function setMiejscowosc(string $Miejscowosc): self
    {
        $this->Miejscowosc = $Miejscowosc;

        return $this;
    }

    public function getKodPocztowy(): ?string
    {
        return $this->KodPocztowy;
    }

    public function setKodPocztowy(string $KodPocztowy): self
    {
        $this->KodPocztowy = $KodPocztowy;

        return $this;
    }

    public function getKwota(): ?string
    {
        return $this->Kwota;
    }

    public function setKwota(string $Kwota): self
    {
        $this->Kwota = $Kwota;

        return $this;
    }

    public function getTytulem(): ?string
    {
        return $this->Tytulem;
    }

    public function setTytulem(string $Tytulem): self
    {
        $this->Tytulem = $Tytulem;

        return $this;
    }

    public function getDataWykonania(): ?string
    {
        return $this->DataWykonania;
    }

    public function setDataWykonania(string $DataWykonania): self
    {
        $this->DataWykonania = $DataWykonania;

        return $this;
    }

}
