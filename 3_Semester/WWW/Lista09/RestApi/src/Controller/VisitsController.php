<?php

namespace App\Controller;

use App\Entity\Visits;
use App\Form\VisitsType;
use App\Repository\VisitsRepository;
use App\Repository\PatientsRepository;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;
use FOS\RestBundle\Controller\AbstractFOSRestController;
use FOS\RestBundle\Controller\Annotations as Rest;
use Doctrine\ORM\EntityManagerInterface;

/**
 * Visits controller
 * @Route("/api/patients/{patientID}/visits", name="api-visits")
 */
class VisitsController extends AbstractFOSRestController
{
  /**
  * @var EntityManagerInterface
  */
    private $entityManager;
  /**
  * @var VisitsRepository
  */
  private $visitsRepository;
  /**
  * @var PatientsRepository
  */
  private $patientsRepository;
  public function __construct(
        EntityManagerInterface $entityManager,
        VisitsRepository $visitsRepository,
        PatientsRepository $patientsRepository

  ) {
      $this->entityManager = $entityManager;
      $this->visitsRepository = $visitsRepository;
      $this->patientsRepository = $patientsRepository;
  }

  /**
  * Lists all visits
  * @Rest\Get("")
  * @Rest\View(serializerGroups={"defaults"})
  * @return \FOS\RestBundle\View\View
  */
  public function getVisitsAction(Request $request): Response
  {
    $patientId = $request->attributes->get('patientID');
    if (!$this->patientsRepository->find($patientId)) {
      throw $this->createNotFoundException(
          'No patient found for id '.$patientId
      );
    }

    // finds visits if patientID matches one in route
    $visits = $this->visitsRepository->findBy(['patients' => $patientId]); 
    
    return $this->handleView($this->view($visits, Response::HTTP_OK));
  }
  /**
  * Lists one visit
  * @Rest\Get("/{visitID}")
  * @Rest\View(serializerGroups={"defaults"})
  * @return \FOS\RestBundle\View\View
  */
  public function getPatientAction(Request $request): Response
  {
    $patientId = $request->attributes->get('patientID');
    if (!$this->patientsRepository->find($patientId)) {
      throw $this->createNotFoundException(
          'No patient found for id '.$patientId
      );
    }

    $id = $request->attributes->get('visitID');
    // findOneBy - returns entity instead of array liek findBy
    $visit = $this->visitsRepository->findOneBy(['id' => $id, 'patients' => $patientId]);
    
    if($visit == null)
      return $this->handleView($this->view("Error - no such visit", Response::HTTP_BAD_REQUEST));

    return $this->handleView($this->view($visit, Response::HTTP_OK));
  }
  /**
  * Posts visit
  * @Rest\Post("")
  *
  * @return Response
  */
  public function postVisitsAction(Request $request)
  {
    $patientId = $request->attributes->get('patientID');
    $patient = $this->patientsRepository->find($patientId);
    
    if (!$patient) {
      throw $this->createNotFoundException(
          'No patient found for id '.$patientId
      );
    }

    $newVisit = new Visits();
    $newVisit->setPatients($patient);
    $form = $this->createForm(VisitsType::class, $newVisit);
    
    $form->submit($request->request->all(), false);
    
    if ($form->isSubmitted() && $form->isValid()) {
      $this->entityManager->persist($form->getData());
      $this->entityManager->flush();

      return $this->handleView($this->view(['status' => 'ok', 'data' => $form->getData()], Response::HTTP_CREATED));
    }
    return $this->handleView($this->view($form->getErrors()));
  }
}
