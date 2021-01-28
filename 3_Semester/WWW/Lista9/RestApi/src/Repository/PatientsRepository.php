<?php

namespace App\Repository;

use App\Entity\Patients;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;
use Symfony\Component\HttpKernel\Exception\NotFoundHttpException;
/**
 * @method Patients|null find($id, $lockMode = null, $lockVersion = null)
 * @method Patients|null findOneBy(array $criteria, array $orderBy = null)
 * @method Patients[]    findAll()
 * @method Patients[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class PatientsRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, Patients::class);
    }

    // /**
    //  * @return Patients[] Returns an array of Patients objects
    //  */
    /*
    public function findByExampleField($value)
    {
        return $this->createQueryBuilder('p')
            ->andWhere('p.exampleField = :val')
            ->setParameter('val', $value)
            ->orderBy('p.id', 'ASC')
            ->setMaxResults(10)
            ->getQuery()
            ->getResult()
        ;
    }
    */

    /*
    public function findOneBySomeField($value): ?Patients
    {
        return $this->createQueryBuilder('p')
            ->andWhere('p.exampleField = :val')
            ->setParameter('val', $value)
            ->getQuery()
            ->getOneOrNullResult()
        ;
    }
    */

    /**
    * @param $id
    *
    * @return Patients|null
    * @throws \Symfony\Component\HttpKernel\Exception\NotFoundHttpException
    *
    * public function findPatientById($id)
    * {
    *    $patient = $this->PatientRepository->find($id);
    *
    *    if (null === $patient) {
    *        throw new NotFoundHttpException();
    *}
    *
    *        return $patient;
    *}   
    */
}
