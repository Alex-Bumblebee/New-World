<?php
	require_once("./include/database.php");
    require_once("./include/functions.php");
    $page_en_cours = "parametres";
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
	if (!isset($_SESSION['nw']['compte']['ok'])){
		header('Location: index.php');
	}

	if(isset($_SESSION['nw']['compte']['type']) AND ($_SESSION['nw']['compte']['type'] == 4)) {
	  if (($_SESSION['nw']['compte']['type'] == 4) OR ($_SESSION['nw']['compte']['type'] == 4)){
	  	
	    if (isset($_POST['submit_add_pdv'])) {
	    	if (isset($_POST['nom'],$_POST['adresse'],$_POST['cp'],$_POST['tel'],$_POST['activite'],$_POST['ville'])) {
	    		if (!empty($_POST['nom']) AND !empty($_POST['adresse']) AND !empty($_POST['cp']) AND !empty($_POST['tel']) AND !empty($_POST['activite']) AND !empty($_POST['ville'])) {
	    			$nom = htmlspecialchars($_POST['nom']);
	    			$adresse = htmlspecialchars($_POST['adresse']);
	    			$cp = htmlspecialchars($_POST['cp']);
	    			$tel = htmlspecialchars($_POST['tel']);
	    			$activite = htmlspecialchars($_POST['activite']);
	    			$ville = htmlspecialchars($_POST['ville']);
	    			$requete_nombre = $bdd->prepare("SELECT no_pdv FROM pointdevente ORDER BY no_pdv DESC LIMIT 1");
                    $requete_nombre->execute();
                    $nombre_pdv = $requete_nombre->fetch();
                    if ($nombre_pdv['no_pdv'] == null) {
                        $id_pdv = 1;
                    } else {
                        $id_pdv = $nombre_pdv['no_pdv'] + 1;
                    }
                    $requete_insertion = $bdd->prepare("INSERT INTO pointdevente(`no_pdv`, `adresse`, `codePostal`, `nom`, `activite`, `ville`, `tel`, `responsable`) VALUES(?,?,?,?,?,?,?,?)");
                    $requete_insertion->execute(array($id_pdv,$adresse,$cp,$nom,$activite,$ville,$tel,$_SESSION['nw']['compte']['identifiant']));

	    		} else {
	    			$erreur = "Tout les champs necessaire ne sont pas remplis !";
	    		}
	    	} else {
	    		die("Erreur");
	    	}
	    }

	    require_once("./view/distribuer.view.php");
	  } else {
	    header("Location: ./pas-acces.php");
	  }
	} else {
	  header("Location: ./pas-acces.php");
	}

	

    
 ?>