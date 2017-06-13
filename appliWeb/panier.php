<?php
	require_once("./include/database.php");
    require_once("./include/functions.php");
    $page_en_cours = "panier";
	session_start();
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
	$erreur = false;
	if (isset($_POST['supprimer_panier'])) {
		supprimePanier();
	}
	if (isset($_GET['action'])) {
		if (!empty($_GET['action'])) {
			$action = htmlspecialchars($_GET['action']);
			if ($action == "soustraire") {
				if (isset($_GET['lot'])) {
					if (!empty($_GET['lot'])) {
						$lot = htmlspecialchars($_GET['lot']);
						soustraireQTeArticle($lot);
						header('Location : panier.php#');
					} else {
						die("Erreur");
					}
				} else {
					die("Erreur");
				}
			} elseif ($action == "ajouter") {
				if (isset($_GET['lot'])) {
					if (!empty($_GET['lot'])) {
						$lot = htmlspecialchars($_GET['lot']);
						ajouterQTeArticle($lot);
						header('Location : panier.php#');
					} else {
						die("Erreur");
					}
				} else {
					die("Erreur");
				}
			} elseif ($action == "supprimer") {
				if (isset($_GET['lot'])) {
					if (!empty($_GET['lot'])) {
						$lot = htmlspecialchars($_GET['lot']);
						supprimerArticle($lot);
						header('Location : panier.php#');
					} else {
						die("Erreur");
					}
				} else {
					die("Erreur");
				}
			}
		} else {
			die("Erreur");
		}
	}

    require_once("./view/panier.view.php");
 ?>