<?php

namespace App\Form;

use App\Entity\Patients;
use Symfony\Bridge\Doctrine\Form\Type\EntityType;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;
use Symfony\Component\Form\Extension\Core\Type\TextType;

class PatientsType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        // property_path account for differences in recommended REST API naming conventions
        // and those in database, and in Entity classes (camelCase vs _ vs -)
        $builder
            ->add('name')
            ->add('surname')
            ->add('phone-number', TextType::class, ['property_path' => 'phoneNumber']) 
            ->add('email')
            ->add('pesel')
            ->add('zip-code', TextType::class, ['property_path' => 'zipCode'])
            ->add('address')
        ;
    }

    public function configureOptions(OptionsResolver $resolver)
    {
        $resolver->setDefaults([
            'data_class' => Patients::class,
            'csrf_protection' => false
        ]);
    }
}
