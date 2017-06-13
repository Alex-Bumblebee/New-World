<?php
	require_once("./include/database.php");
    require_once("./include/functions.php");
    $page_en_cours = "connexion";
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
	if (isset($_POST['submit_connexion'])) {
	  $pseudo_connect = htmlspecialchars($_POST['pseudo_connexion']);
	  $mdp_connect = htmlspecialchars($_POST['mdp1_connexion']);
	  if (!empty($pseudo_connect) AND !empty($mdp_connect)) {
	    $requete_user = $bdd->prepare("SELECT * FROM utilisateur WHERE pseudo = ?");
	    $requete_user->execute(array($pseudo_connect));
	    $user_existe = $requete_user->rowCount();
	    if ($user_existe == 1) {
	    	$user_info = $requete_user->fetch();
	    	if ($user_info['verifie'] == 1) {
		    	if (password_verify($mdp_connect,$user_info['motDePasse'])) {
		    		$_SESSION['nw']['compte']['ok'] = true;
				 	$_SESSION['nw']['compte']['identifiant'] = $user_info['identifiant'];
			      	$_SESSION['nw']['compte']['pseudo'] = $user_info['pseudo'];
			      	$_SESSION['nw']['compte']['email'] = $user_info['email'];
			      	$_SESSION['nw']['compte']['prenom'] = $user_info['prenom'];
			      	$_SESSION['nw']['compte']['nom'] = $user_info['nom'];
			      	$_SESSION['nw']['compte']['type'] = $user_info['id_typeUtilisateur'];
 			    	header("Location: index.php");
		    	} else {
		    		$_SESSION['nw']['error'] = "Mauvais Pseudo et/ou mot de passes";
		    	}
		    } else {
		    	$_SESSION['nw']['error'] = "Votre compte n'est pas confirmé";
		    }  
	    } else {
	      	$_SESSION['nw']['error']= "Mauvais Pseudo et/ou mot de passe";
	    }
	  } else {
	    $_SESSION['nw']['error'] = "Tous les champs doivent être complétés";
	  }
	}

    require_once("./view/connexion.view.php");
 ?>