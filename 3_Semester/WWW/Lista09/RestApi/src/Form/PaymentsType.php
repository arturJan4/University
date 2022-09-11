<?php

namespace App\Form;

use App\Entity\Payments;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;
use Symfony\Component\Form\Extension\Core\Type\TextType;

class PaymentsType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder
        // property_path account for differences in recommended REST API naming conventions
        // and those in database, and in Entity classes (camelCase vs _ vs -)
            ->add('created-at', TextType::class, ['property_path' => 'createdAt'])
            ->add('ammount')
            ->add('status')
        ;
    }

    public function configureOptions(OptionsResolver $resolver)
    {
        $resolver->setDefaults([
            'data_class' => Payments::class,
            'csrf_protection' => false
        ]);
    }
}
