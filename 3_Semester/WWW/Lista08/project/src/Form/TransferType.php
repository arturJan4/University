<?php

namespace App\Form;

use App\Entity\Transfer;
use Symfony\Component\Form\AbstractType;
use Symfony\Component\Form\FormBuilderInterface;
use Symfony\Component\OptionsResolver\OptionsResolver;
use Symfony\Component\Form\Extension\Core\Type\SubmitType;
use Symfony\Component\Form\Extension\Core\Type\DateType;
use Symfony\Component\Form\Extension\Core\Type\TextType;


class TransferType extends AbstractType
{
    public function buildForm(FormBuilderInterface $builder, array $options)
    {
        $builder
            ->add('KontoOd', TextType::class, [
                'attr' => [
                        'placeholder' => 'XX XXXX XXXX XXXX XXXX XXXX XXXX'
                    ]
            ])
            ->add('KontoDo', TextType::class, [
                'attr' => [
                        'placeholder' => 'XX XXXX XXXX XXXX XXXX XXXX XXXX'
                    ]
            ])
            ->add('ImieNazwisko', TextType::class)
            ->add('Ulica', TextType::class)
            ->add('Miejscowosc', TextType::class)
            ->add('KodPocztowy', TextType::class, [
                'attr' => [
                        'placeholder' => 'XX-XXX'
                    ]
            ])
            ->add('Kwota', TextType::class)
            ->add('Tytulem', TextType::class)
            ->add('DataWykonania', DateType::class, [
                'widget' => 'single_text',
                // this is actually the default format for single_text
                'format' => 'yyyy-MM-dd',
                'input' => 'string'
            ])
            ->add('send', SubmitType::class, ['label' => 'Wyślij']
        );
            
    }

    public function configureOptions(OptionsResolver $resolver)
    {
        $resolver->setDefaults([
            'data_class' => Transfer::class,
        ]);
    }
}
