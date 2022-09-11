<?php

namespace App\Controller;

use App\Entity\Payments;
use App\Form\PaymentsType;
use App\Repository\PaymentsRepository;
use App\Repository\VisitsRepository;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;
use FOS\RestBundle\Controller\AbstractFOSRestController;
use FOS\RestBundle\Controller\Annotations as Rest;
use Doctrine\ORM\EntityManagerInterface;

/**
 * Payments controller
 * @Route("/api/patients/{patientID}/visits/{visitID}/payments", name="api-payments")
 */
class PaymentsController extends AbstractFOSRestController
{
  /**
  * @var EntityManagerInterface
  */
    private $entityManager;
  /**
  * @var PaymentsRepository
  */
  private $paymentsRepository;
  /**
  * @var VisitsRepository
  */
  private $visitsRepository;
  public function __construct(
        EntityManagerInterface $entityManager,
        VisitsRepository $visitsRepository,
        PaymentsRepository $paymentsRepository
  ) {
      $this->entityManager = $entityManager;
      $this->visitsRepository = $visitsRepository;
      $this->paymentsRepository = $paymentsRepository;
  }

  /**
  * Lists all payments
  * @Rest\Get("")
  * @Rest\View(serializerGroups={"defaults"})
  * @return \FOS\RestBundle\View\View
  */
  public function getPaymentsAction(Request $request): Response
  {   
    $visitId = $request->attributes->get('visitID');

    if (!$this->visitsRepository->find($visitId)) {
      throw $this->createNotFoundException(
          'No visit found for id '.$visitId
      );
    }

    $payments = $this->paymentsRepository->findBy(['visits' => $visitId]);

    return $this->handleView($this->view($payments, Response::HTTP_OK));
  }

  /**
  * Lists one payment
  * @Rest\Get("/{paymentID}")
  * @Rest\View(serializerGroups={"defaults"})
  * @return \FOS\RestBundle\View\View
  */
  public function getPaymentAction(Request $request): Response
  {
    $visitId = $request->attributes->get('visitID');
    $id = $request->attributes->get('paymentID');

    if (!$this->visitsRepository->find($visitId)) {
      throw $this->createNotFoundException(
          'No visit found for id '.$visitId
      );
    }

    $payment = $this->paymentsRepository->findOneBy(
      ['id' => $id, 
        'visits' => $visitId
      ]);
    
    if($payment == null)
      return $this->handleView($this->view("Error - no such payment", Response::HTTP_BAD_REQUEST));

    return $this->handleView($this->view($payment, Response::HTTP_OK));
  }

  /**
  * Lists one payment's status
  * @Rest\Get("/{paymentID}/status")
  * @Rest\View(serializerGroups={"defaults"})
  * @return \FOS\RestBundle\View\View
  */
  public function getPaymentStatusAction(Request $request): Response
  {
    $visitId = $request->attributes->get('visitID');
    $id = $request->attributes->get('paymentID');

    if (!$this->visitsRepository->find($visitId)) {
      throw $this->createNotFoundException(
          'No visit found for id '.$visitId
      );
    }

    $payment = $this->paymentsRepository->findOneBy(
      ['id' => $id, 
        'visits' => $visitId
      ]);
    
    if($payment == null)
      return $this->handleView($this->view("Error - no such payment", Response::HTTP_BAD_REQUEST));
    
    return $this->handleView($this->view($payment->getStatus(), Response::HTTP_OK));
  }

  /**
  * Posts payment
  * @Rest\Post("")
  *
  * @return Response
  */
  public function postPaymentsAction(Request $request)
  {
    $visitId = $request->attributes->get('visitID');
    $visit = $this->visitsRepository->find($visitId);
    if (!$visit) {
      throw $this->createNotFoundException(
          'No visit found for id '.$visitId 
      );
    }

    $newPayment = new Payments();
    $newPayment->setVisits($visit);
    $form = $this->createForm(PaymentsType::class, $newPayment);
    
    $form->submit($request->request->all(), false);
    
    if ($form->isSubmitted() && $form->isValid()) {
      $this->entityManager->persist($form->getData());
      $this->entityManager->flush();

      return $this->handleView($this->view(['status' => 'ok', 'data' => $form->getData()], Response::HTTP_CREATED));
    }
    return $this->handleView($this->view($form->getErrors()));
  }

  /**
  * patch payment
  * @Rest\Patch("/{paymentID}")
  *
  * @return Response
  */
  public function patchPaymentsAction(Request $request)
  {
    $id = $request->attributes->get('paymentID');
    $existing_payment = $this->paymentsRepository->find($id);
    
    if (!$existing_payment) {
      throw $this->createNotFoundException(
          'No payment found for id '.$id
      );
    }

    $form = $this->createForm(PaymentsType::class, $existing_payment);
    $form->submit($request->request->all(), false);  // clear-missing = false only difference between put
    if ($form->isSubmitted() && $form->isValid()) {
      $this->entityManager->flush();

      return $this->handleView($this->view(['status' => 'ok'], Response::HTTP_ACCEPTED));
    }

    return $this->handleView($this->view($form->getErrors()));
  }
}
