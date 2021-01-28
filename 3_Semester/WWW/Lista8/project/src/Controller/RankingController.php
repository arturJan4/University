<?php

namespace App\Controller;

use App\Entity\Position;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;


class RankingController extends AbstractController
{
    /**
     * @Route("/ranking", name="ranking")
     */
    public function index()
    {
        $myArr = [new Position(1,20,'Dave','Random','Warszawa','Frugo'), 
                  new Position(2,18,'Robert','Mazurek','Warszawa','Frugo'),
                  new Position(3,17,'Franciszek', 'Piotrowski','Mama','Wroclaw','Zieloni'),
                  new Position(3,17,'Jacek','Laskowski','Wroclaw','Niebiescy'),
                  new Position(4,15,'Oskar','Tomaszewski','Kraków','Biali'),
                  new Position(5,14,'Eryk','Przybylski','Wroclaw','Niebiescy'),
                  new Position(6,9,'Alfred','Nowak','Kraków','Frugo'),
                  new Position(7,8,'Jędrzej','Maciejewski','Wroclaw','Czerwoni'),
                  new Position(8,7,'Joachim','Malinowski','Kraków','Biali'),
                  new Position(9,6,'Dawid','Lis','Wroclaw','Frugo'),
                  new Position(10,4,'Mateusz','Mazurek','Warszawa','Frugo'),
                  new Position(11,0,'Joe','Mama','Warszawa','Frugo'),
                  new Position(12,0,'Jan','Kowalski','Radom','Przegrani')];

        return $this->render('ranking/index.html.twig', [
            'controller_name' => 'RankingController',
            'arr' => $myArr
        ]);
    }
}
