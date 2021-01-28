<?php

namespace App\Controller;

use App\Entity\Patients;
use App\Form\PatientsType;
use App\Repository\PatientsRepository;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;
use FOS\RestBundle\Controller\AbstractFOSRestController;
use FOS\RestBundle\Controller\Annotations as Rest;
use Symfony\Component\Routing\Annotation\Route;
use Doctrine\ORM\EntityManagerInterface;


/**
 * Patients controller
 * @Route("/api/patients", name="api-patients")
 */
class PatientsController extends AbstractFOSRestController
{
  /**
  * @var EntityManagerInterface
  */
    private $entityManager;
  /**
  * @var PatientsRepository
  */
  private $patientsRepository;
  public function __construct(
      EntityManagerInterface $entityManager,
      PatientsRepository $patientsRepository
  ) {
      $this->entityManager = $entityManager;
      $this->patientsRepository = $patientsRepository;
  }

  /**
  * Lists all patients
  * @Rest\Get("")
  *
  * @return \FOS\RestBundle\View\View
  */
  public function getPatientsAction(): Response
  {
    $patients = $this->patientsRepository->findall();
  
    return $this->handleView($this->view($patients, Response::HTTP_OK));
  }

  /**
  * Lists one patient
  * @Rest\Get("/{patientID}")
  *
  * @return \FOS\RestBundle\View\View
  */
  public function getPatientAction(Request $request): Response
  {
    $id = $request->attributes->get('patientID');     // getting id from route
    $patient = $this->patientsRepository->find($id);  // finding patient in DB given patientID
    
    if($patient === null)
      return $this->handleView($this->view("Error - no such patient", Response::HTTP_BAD_REQUEST));

    return $this->handleView($this->view($patient, Response::HTTP_OK));
  }
  /**
  * Posts patient
  * @Rest\Post("")
  *
  * @return Response
  */
  public function postPatientsAction(Request $request)
  {
    $form = $this->createForm(PatientsType::class, new Patients());
    $form->submit($request->request->all());    // clearMissing, default = true

    if ($form->isSubmitted() && $form->isValid()) {
      $this->entityManager->persist($form->getData());
      $this->entityManager->flush();

      // returns 201 HTTP CODE, and created object in 'data' (for testing purposes)
      return $this->handleView($this->view(['status' => 'ok', 'data' => $form->getData()], Response::HTTP_CREATED));
    }
    return $this->handleView($this->view($form->getErrors()));
  }
  /**
  * patch patient
  * @Rest\Patch("/{patientID}")
  *
  * @return Response
  */
  public function patchPatientsAction(Request $request)
  {
    $id = $request->attributes->get('patientID');
    $existing_patient = $this->patientsRepository->find($id);
    
    if (!$existing_patient) {
      throw $this->createNotFoundException(
          'No patient found for id '.$id
      );
    }

    $form = $this->createForm(PatientsType::class, $existing_patient);
    $form->submit($request->request->all(), false);  // clear-missing = false only difference between put
    if ($form->isSubmitted() && $form->isValid()) {
      $this->entityManager->flush();

      return $this->handleView($this->view(['status' => 'ok'], Response::HTTP_ACCEPTED));
    }

    return $this->handleView($this->view($form->getErrors()));
  }
   /**
   * Delete patient
   * @Rest\Delete("/{patientID}")
   *
   * @return Response
   */
  public function deletePatientsAction(Request $request)
  {
    $id = $request->attributes->get('patientID');
    $patient = $this->patientsRepository->find($id);
    
    if (!$patient) {
      throw $this->createNotFoundException(
          'No patient found for id '.$id
      );
    }

    $this->entityManager->remove($patient);
    $this->entityManager->flush();

    return $this->handleView($this->view(['status' => 'ok'], Response::HTTP_ACCEPTED));
  }
}