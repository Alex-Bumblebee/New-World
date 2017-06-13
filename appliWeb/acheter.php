<?php
	require_once("./include/database.php");
    require_once("./include/functions.php");
    $page_en_cours = "acheter";

	$requete_lot = $bdd->prepare("SELECT * FROM lot INNER JOIN produit ON lot.numero = produit.numero INNER JOIN utilisateur ON lot.identifiant = utilisateur.identifiant");
	$requete_lot->execute();
	$nombre_lot = $requete_lot->rowCount();

	session_start();

	if (isset($_POST['submit_add'])) {
		if (isset($_POST['lot_add'])) {
			if (!empty($_POST['lot_add'])) {
				$lotadd = htmlspecialchars($_POST['lot_add']);
				$req_lot = $bdd->prepare("SELECT * FROM lot INNER JOIN produit ON lot.numero = produit.numero INNER JOIN utilisateur ON lot.identifiant = utilisateur.identifiant WHERE nolot = ?");
    			$req_lot->execute(array($lotadd));
    			$lot_existe = $req_lot->rowCount();
    			if ($lot_existe == 1) {
    				$lot_info = $req_lot->fetch();
    				$quantitelot = $lot_info['quantiteLot'];
    				if ($quantitelot > 0) {
    					ajouterArticle($lotadd,1,$lot_info['quantiteProduit']*$lot_info['prixUnitaire'],"Lot de ".$lot_info['quantiteProduit']." ".$lot_info['libelle'],"".$lot_info['pseudo']);
    					$_SESSION['nw']['success'] = "Article ajouté !";
    				} else {
    					$_SESSION['nw']['error'] = "Il n'y a plus de stock disponible !";
    				}
    			} else {
    				die("Erreur");
    			}
				
			} else {
				die("Erreur");
			}
		} else {
			die("Erreur");
		}
		
	}

	if (isset($_SESSION['nw']['success']) AND (!empty($_SESSION['nw']['success']))){
		$success = $_SESSION['nw']['success'];
		unset($_SESSION['nw']['success']);
	}
	if (isset($_SESSION['nw']['error']) AND (!empty($_SESSION['nw']['error']))){
		$error = $_SESSION['nw']['error'];
		unset($_SESSION['nw']['error']);
	}
	if (isset($_SESSION['nw']['warning']) AND (!empty($_SESSION['nw']['warning']))){
		$warning = $_SESSION['nw']['warning'];
		unset($_SESSION['nw']['warning']);
	}
    require_once("./view/acheter.view.php");
 ?>