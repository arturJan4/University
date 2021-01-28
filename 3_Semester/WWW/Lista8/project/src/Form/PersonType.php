<?php

namespace App\Form;

use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\Validator\Constraints\NotBlank;
use Symfony\Component\Validator\Constraints\MinLength;
use \Symfony\Component\Validator\Constraints\Collection;
use Symfony\Component\Form\Extension\Core\Type\SubmitType;
use Symfony\Component\Form\Extension\Core\Type\TextType;

class PersonType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder
            ->add('firstname',TextType::class, ['label' => 'Imię:'])
            ->add('lastname',TextType::class, ['label' => 'Nazwisko:'])
			->add('save', SubmitType::class)
        ;
    }

    public function getName()
    {
        return 'Person';
    }
}