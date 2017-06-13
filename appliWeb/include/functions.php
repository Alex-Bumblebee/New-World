<?php

function url_custom_encode($titre) {
   $titre = htmlspecialchars($titre);
   $find = array('À', 'Á', 'Â', 'Ã', 'Ä', 'Å', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', 'Ø', 'Ù', 'Ú', 'Û', 'Ü', 'Ý', 'ß', 'à', 'á', 'â', 'ã', 'ä', 'å', 'æ', 'ç', 'è', 'é', 'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ö', 'ø', 'ù', 'ú', 'û', 'ü', 'ý', 'ÿ', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 'Œ', 'œ', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 'Š', 'š', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 'Ÿ', '?', '?', '?', '?', 'Ž', 'ž', '?', 'ƒ', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?');
     $replace = array('A', 'A', 'A', 'A', 'A', 'A', 'AE', 'C', 'E', 'E', 'E', 'E', 'I', 'I', 'I', 'I', 'D', 'N', 'O', 'O', 'O', 'O', 'O', 'O', 'U', 'U', 'U', 'U', 'Y', 's', 'a', 'a', 'a', 'a', 'a', 'a', 'ae', 'c', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'n', 'o', 'o', 'o', 'o', 'o', 'o', 'u', 'u', 'u', 'u', 'y', 'y', 'A', 'a', 'A', 'a', 'A', 'a', 'C', 'c', 'C', 'c', 'C', 'c', 'C', 'c', 'D', 'd', 'D', 'd', 'E', 'e', 'E', 'e', 'E', 'e', 'E', 'e', 'E', 'e', 'G', 'g', 'G', 'g', 'G', 'g', 'G', 'g', 'H', 'h', 'H', 'h', 'I', 'i', 'I', 'i', 'I', 'i', 'I', 'i', 'I', 'i', 'IJ', 'ij', 'J', 'j', 'K', 'k', 'L', 'l', 'L', 'l', 'L', 'l', 'L', 'l', 'l', 'l', 'N', 'n', 'N', 'n', 'N', 'n', 'n', 'O', 'o', 'O', 'o', 'O', 'o', 'OE', 'oe', 'R', 'r', 'R', 'r', 'R', 'r', 'S', 's', 'S', 's', 'S', 's', 'S', 's', 'T', 't', 'T', 't', 'T', 't', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'W', 'w', 'Y', 'y', 'Y', 'Z', 'z', 'Z', 'z', 'Z', 'z', 's', 'f', 'O', 'o', 'U', 'u', 'A', 'a', 'I', 'i', 'O', 'o', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'A', 'a', 'AE', 'ae', 'O', 'o', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?');
     $titre = str_replace($find, $replace, $titre);
   $titre = strtolower($titre);
   $mots = preg_split('/[^A-Z^a-z^0-9]+/', $titre);
   $encoded = "";
   foreach($mots as $mot) {
      if(strlen($mot) >= 3 OR str_replace(['0','1','2','3','4','5','6','7','8','9'], '', $mot) != $mot) {
         $encoded .= $mot.'-';
      }
   }
   $encoded = substr($encoded, 0, -1);
   return $encoded;
}

function creationPanier()
{
        if (!isset($_SESSION['panier']))
        {
            $_SESSION['panier'] = array();
            $_SESSION['panier']['lot'] = array();
            $_SESSION['panier']['qte'] = array();
            $_SESSION['panier']['nomLot'] = array();
            $_SESSION['panier']['nomProducteur'] = array();
            $_SESSION['panier']['prix'] = array();
            $_SESSION['panier']['verrou'] = false;
        }
   return true;
}

function ajouterArticle($lot, $qte, $prix, $nomLot, $nomProducteur){
 
   //Si le panier existe
   if (creationPanier() && !isVerrouille())
   {
      //Si le lot existe déjà on ajoute seulement la quantité
      $positionLot = array_search($lot,  $_SESSION['panier']['lot']);
 
      if ($positionLot !== false)
      {
         $_SESSION['panier']['qte'][$positionLot] += $qte ;
      }
      else
      {
         //Sinon on ajoute le lot
         array_push( $_SESSION['panier']['lot'],$lot);
         array_push( $_SESSION['panier']['qte'],$qte);
         array_push( $_SESSION['panier']['nomLot'],$nomLot);
         array_push( $_SESSION['panier']['nomProducteur'],$nomProducteur);
         array_push( $_SESSION['panier']['prix'],$prix);
      }
   }
   else
   echo "Un problème est survenu veuillez contacter l'administrateur du site.";
}

function isVerrouille(){
  if (creationPanier()) {
    if ($_SESSION['panier']['verrou'] == false){
      return false;
    } elseif ($_SESSION['panier']['verrou'] == true){
      return true;
    }
  }
}

function supprimerArticle($lot){
   //Si le panier existe
   if (creationPanier() && !isVerrouille())
   {
      $positionLot = array_search($lot, $_SESSION['panier']['lot']);
      if ($positionLot !== false){
          unset($_SESSION['panier']['lot'][$positionLot]);
          unset($_SESSION['panier']['qte'][$positionLot]);
          unset($_SESSION['panier']['nomLot'][$positionLot]);
          unset($_SESSION['panier']['nomProducteur'][$positionLot]);
          unset($_SESSION['panier']['prix'][$positionLot]);
      } else {
        echo "Un problème est survenu veuillez contacter l'administrateur du site.";
      }
   }
   else
   echo "Un problème est survenu veuillez contacter l'administrateur du site.";
}

function soustraireQTeArticle($lot){
   //Si le panier éxiste
  if (creationPanier() && !isVerrouille())
  {
      $positionLot = array_search($lot,  $_SESSION['panier']['lot']);
      if ($positionLot !== false){
        if ($_SESSION['panier']['qte'][$positionLot] > 1) {
          $_SESSION['panier']['qte'][$positionLot] = $_SESSION['panier']['qte'][$positionLot]-1;
        } else {
          supprimerArticle($lot);
        }
      } else {
        supprimerArticle($lot);
      } 
  } else {
   echo "Un problème est survenu veuillez contacter l'administrateur du site.";
  }
}

function ajouterQTeArticle($lot){
   //Si le panier éxiste
  if (creationPanier() && !isVerrouille())
  {
      $positionLot = array_search($lot,  $_SESSION['panier']['lot']);
      if ($positionLot !== false){
        if ($_SESSION['panier']['qte'][$positionLot] > 0) {
          $_SESSION['panier']['qte'][$positionLot] = $_SESSION['panier']['qte'][$positionLot]+1;
        } else {
          echo "Un problème est survenu veuillez contacter l'administrateur du site.";
        }
      } else {
        supprimerArticle($lot);
      } 
  } else {
   echo "Un problème est survenu veuillez contacter l'administrateur du site.";
  }
}
 
function MontantGlobal(){
   $total=0;
   for($i = 0; $i < count($_SESSION['panier']['lot']); $i++)
   {
      $total += $_SESSION['panier']['qte'][$i] * $_SESSION['panier']['prix'][$i];
   }
   return $total;
}

function TotalLot(){
  if (creationPanier()) {
    $total=count($_SESSION['panier']['lot']);
    return $total;
  }
}

 
function supprimePanier(){
   unset($_SESSION['panier']);
}



?>