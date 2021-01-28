<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;

use App\Entity\Transfer;
use App\Form\TransferType;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Template;
use Symfony\Component\VarDumper\Cloner\Data;
use Symfony\Component\VarDumper\VarDumper;

class TransferController extends AbstractController
{
    /**
     * @Route("/transfer/form", name="form")
     * @Template()
     */
    public function formAction(Request $request) {
        
        $form = $this->createForm(TransferType::class, new Transfer());

        $form->handleRequest($request);
        if ($form->isSubmitted() && $form->isValid()) {
            // perform some action, such as saving the task to the database

            return $this->forward('App\Controller\TransferController::success_payment', ['form' => $form]);
        }

        return array('controller_name'=>'TransferController', 'form' => $form->createView());
    }

    /**
     * @Route("/", name="success_payment")
     * @Template()
     */
    public function success_payment($form) {
        $data = array();
        $data['KontoOd'] = $form->getData()->getKontoOd();
        $data['KontoDo'] = $form->getData()->getKontoDo();     
        $data['ImieNazwisko'] = $form->getData()->getImieNazwisko();   
        $data['Ulica'] = $form->getData()->getUlica();   
        $data['Miejscowosc'] = $form->getData()->getMiejscowosc();   
        $data['KodPocztowy'] = $form->getData()->getKodPocztowy();
        $data['Kwota'] = $form->getData()->getKwota();
        $data['Tytulem'] = $form->getData()->getTytulem(); 
        $data['DataWykonania'] = $form->getData()->getDataWykonania(); 

        $contents = $this->renderView('transfer/success_payment.html.twig', ['data' => $data]);

        return new Response($contents);
    }

}
