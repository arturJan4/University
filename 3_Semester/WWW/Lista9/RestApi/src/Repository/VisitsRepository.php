<?php

namespace App\Repository;

use App\Entity\Visits;
use Doctrine\Bundle\DoctrineBundle\Repository\ServiceEntityRepository;
use Doctrine\Persistence\ManagerRegistry;

/**
 * @method Visits|null find($id, $lockMode = null, $lockVersion = null)
 * @method Visits|null findOneBy(array $criteria, array $orderBy = null)
 * @method Visits[]    findAll()
 * @method Visits[]    findBy(array $criteria, array $orderBy = null, $limit = null, $offset = null)
 */
class VisitsRepository extends ServiceEntityRepository
{
    public function __construct(ManagerRegistry $registry)
    {
        parent::__construct($registry, Visits::class);
    }

    // /**
    //  * @return Visits[] Returns an array of Visits objects
    //  */
    /*
    public function findByExampleField($value)
    {
        return $this->createQueryBuilder('v')
            ->andWhere('v.exampleField = :val')
            ->setParameter('val', $value)
            ->orderBy('v.id', 'ASC')
            ->setMaxResults(10)
            ->getQuery()
            ->getResult()
        ;
    }
    */

    /*
    public function findOneBySomeField($value): ?Visits
    {
        return $this->createQueryBuilder('v')
            ->andWhere('v.exampleField = :val')
            ->setParameter('val', $value)
            ->getQuery()
            ->getOneOrNullResult()
        ;
    }
    */
}
