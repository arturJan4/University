<?php
namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Annotation\Route;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Template;

class DefaultController extends AbstractController
{
    /**
     * @Route("/", name="default_index")
     */
    public function index(Request $r): Response
    {
        return $this->render('default/index.html.twig', [
            'header'=> 'Nagłówek',
            'footer' => "Stopka"
        ]);
    }

    /**
     * @Route("/params/{firstname}/{lastname}/{color}", name="default_params")
     */
    public function params(string $firstname, string $lastname, string $color): Response
    {
        return $this->render('default/params.html.twig', [
            'header'=>'Nagłówek',
            'footer' => "Stopka",
            'dane' => "$firstname $lastname, $color"
        ]);
    }
    
    /**
     * @Route("/redirect", name="default_redirect")
     */
    public function redirectToHome(): Response
    {
        return $this->redirect($this->generateUrl("default_index"));
    }
    
    /**
     * @Route("/forward", name="default_forward")
     */
    public function forwardToHome(): Response
    {
        return $this->forward("App\Controller\DefaultController::index");
    }
    
    /**
     * @Route("/number", name="default_number")
     */
    public function number(): Response
    {
        $number = random_int(0, 100);

        return new Response(
            '<html><body>Lucky number: '.$number.', <a href='.$this->generateUrl("default_index").'>Powrót</a></body></html>'
        );
    }
}